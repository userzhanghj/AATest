// LogDlg.cpp: 实现文件
//

#include "pch.h"
#include "ProjectAA.h"
#include "LogDlg.h"
#include "afxdialogex.h"
#include "SystemLog.h"

extern CSystemLog     gSystemLog;


// CLogDlg 对话框

IMPLEMENT_DYNAMIC(CLogDlg, CDialogEx)

CLogDlg::CLogDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_LOG, pParent)
	, m_logBuffer(500)
{

}

CLogDlg::~CLogDlg()
{
}

void CLogDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_LOG, m_listLog);
}


BEGIN_MESSAGE_MAP(CLogDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(WM_SEND_LOG_MSG_TO_MAIN_UI, &CLogDlg::OnReceiveAndDisplaySystemLog)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_LIST_LOG, &CLogDlg::OnNMCustomdrawListLog)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_LOG, &CLogDlg::OnLvnItemchangedListLog)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_LOG, &CLogDlg::OnNMDblclkListLog)
END_MESSAGE_MAP()


// CLogDlg 消息处理程序

void CLogDlg::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类

	CDialogEx::OnCancel();
}


BOOL CLogDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	LONG lStyle;
	m_listLog.SetBkColor(RGB(200, 220, 250));
	//m_logList.SetBkColor(TRANSPARENT);
	//m_logList.SetTextColor(RGB(250, 250, 250));
	lStyle = GetWindowLong(m_listLog.m_hWnd, GWL_STYLE);
	lStyle &= ~LVS_TYPEMASK;
	lStyle |= LVS_REPORT;
	SetWindowLong(m_listLog.m_hWnd, GWL_STYLE, lStyle);
	m_listLog.ShowWindow(SW_SHOW);
	DWORD dwStyle = m_listLog.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;
	dwStyle |= LVS_EX_GRIDLINES;
	dwStyle |= LVS_EX_INFOTIP;

	m_listLog.SetExtendedStyle(dwStyle);
	m_listLog.SetFont(&gSystemMgr.m_logFont);
	m_listLog.EnableWindow(TRUE);
	m_listLog.InsertColumn(0, L"当前时刻", LVCFMT_LEFT, 90);
	m_listLog.InsertColumn(1, L"日志详细描述", LVCFMT_LEFT, 2000);
	m_listLog.ShowWindow(SW_HIDE);
	m_listLog.EnableWindow(TRUE);
	m_listLog.Invalidate();
	m_listLog.ShowWindow(SW_SHOW);
	m_listLog.BringWindowToTop();

	SetUiHandle();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

LRESULT CLogDlg::OnReceiveAndDisplaySystemLog(WPARAM wParam, LPARAM lParam)
{
	eEVENT_LEVEL   logLevel = LV_EVENT;;
	CString cstrp = (BSTR)wParam;
	SysFreeString((BSTR)wParam);
	switch (lParam)
	{
	case(LV_EVENT):
		logLevel = LV_EVENT;
		break;
	case(LV_WARNING):
		logLevel = LV_WARNING;
		break;
	case(LV_ERROR):
		logLevel = LV_ERROR;
		break;
	default:
		break;
	}
	wstring wstrLogMsg = cstrp.GetString();
	std::vector<wstring> vLogItem = _utils::SplitString(wstrLogMsg, L"#");
	if (vLogItem.size() != 2)
	{
		return 0;
	}
	wstring wstrTime = vLogItem[0];
	wstring wstrMsg = vLogItem[1];
	int nIndexItem = m_listLog.GetItemCount();
	m_listLog.InsertItem(0, L"");
	m_listLog.SetItemText(0, 0, wstrTime.c_str());
	m_listLog.SetItemText(0, 1, wstrMsg.c_str());
	LOG_PACKAGE logPackage;
	logPackage.m_level = logLevel;
	logPackage.m_wstrTime = wstrTime;
	logPackage.m_wstrMsg = wstrMsg;
	m_logBuffer.push_back(logPackage);
	m_listLog.Invalidate();
	if (nIndexItem >= 500)
	{
		m_listLog.DeleteItem(500);
	}

	return 0;
}

void CLogDlg::OnNMCustomdrawListLog(NMHDR * pNMHDR, LRESULT * pResult)
{
	NMLVCUSTOMDRAW* lplvcd = reinterpret_cast<NMLVCUSTOMDRAW*>(pNMHDR);
	int nIRow = int(lplvcd->nmcd.dwItemSpec);
	if (lplvcd->nmcd.dwDrawStage == CDDS_PREPAINT)
	{
		*pResult = CDRF_NOTIFYITEMDRAW;
		return;
	}
	if (lplvcd->nmcd.dwDrawStage == CDDS_ITEMPREPAINT)
	{
		lplvcd->clrTextBk = RGB(200, 220, 250);
		//lplvcd->clrTextBk =TRANSPARENT;
		*pResult = CDRF_NOTIFYSUBITEMDRAW;
		return;
	}
	else if (lplvcd->nmcd.dwDrawStage == (CDDS_SUBITEM | CDDS_PREPAINT | CDDS_ITEMPREPAINT))
	{
		COLORREF crText = RGB(10, 10, 10);
		if (lplvcd->iSubItem == 1)
		{
			LOG_PACKAGE logPackage;
			logPackage = m_logBuffer.at(m_listLog.GetItemCount() - nIRow - 1);
			switch (logPackage.m_level)
			{
			case(LV_ERROR):
				crText = RGB(250, 0, 0);
				break;
			case(LV_WARNING):
				crText = RGB(150, 150, 0);
				break;
			case(LV_EVENT):
				crText = RGB(50, 50, 50);
				break;
			default:
				break;
			}
			lplvcd->clrText = crText;
			*pResult = CDRF_DODEFAULT;
			return;
		}
	}
	*pResult = 0;
}

void CLogDlg::SetUiHandle()
{
	gSystemLog.m_hUiHandle = this->GetSafeHwnd();

}

void CLogDlg::OnLvnItemchangedListLog(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}


BOOL CLogDlg::PreTranslateMessage(MSG* pMsg)
{
	WPARAM param = pMsg->wParam;
	if (param == VK_ESCAPE || param == VK_RETURN || param == VK_SPACE)
		return TRUE;
	if (pMsg->message == WM_SYSKEYDOWN && param == VK_F4)
		return TRUE;

	return CDialogEx::PreTranslateMessage(pMsg);
}

void CLogDlg::OnNMDblclkListLog(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	m_listLog.DeleteAllItems();
	*pResult = 0;
}
