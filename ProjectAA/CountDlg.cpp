// CountDlg.cpp: 实现文件
//

#include "pch.h"
#include "CountDlg.h"
#include "ProjectAA.h"
#include "afxdialogex.h"


// CCountDlg 对话框

IMPLEMENT_DYNAMIC(CCountDlg, CDialogEx)

CCountDlg::CCountDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_COUNT, pParent)
{

}

CCountDlg::~CCountDlg()
{
}

void CCountDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CCountDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CCountDlg::OnBnClickedButton1)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CCountDlg 消息处理程序


void CCountDlg::OnBnClickedButton1()
{
	if (IDYES == AfxMessageBox(L"确定清空 AA 站统计数据吗？", MB_YESNO))
	{
		CString cstr;
		cstr.Format(L"AA旧数据[%s]: %d,%d,%d,%d,%d", gSystemMgr.AATime, gSystemMgr.m_nAAAll, gSystemMgr.m_nAAOK, gSystemMgr.m_nAANG1, gSystemMgr.m_nAANG2, gSystemMgr.m_nAANG3);
		gSystemMgr.m_nAAAll = 0;
		gSystemMgr.m_nAAOK = 0;
		gSystemMgr.m_nAANG1 = 0;
		gSystemMgr.m_nAANG2 = 0;
		gSystemMgr.m_nAANG3 = 0;
		SYSTEMTIME st;
		GetLocalTime(&st);
		gSystemMgr.AATime.Format(L"%04d%02d%02d-%02d%02d%02d", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);
		gSystemLog.DisplayLogAndSave(L"AA 站统计数据清除成功。", LV_ERROR);
	}
}


BOOL CCountDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SetTimer(TIMER_CONTROL_COUNT, 500, NULL);

	return TRUE;
}


void CCountDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == TIMER_CONTROL_COUNT)
	{
		CString cstr;
		gSystemMgr.m_nAAAll = gSystemMgr.m_nAAOK + gSystemMgr.m_nAANG1 + gSystemMgr.m_nAANG2 + gSystemMgr.m_nAANG3;
		if (gSystemMgr.m_nAAAll != 0)
			gSystemMgr.m_dAAOKPer = double(gSystemMgr.m_nAAOK*100.0) / gSystemMgr.m_nAAAll;
		else
			gSystemMgr.m_dAAOKPer = 0;
		cstr.Format(L"%d", gSystemMgr.m_nAAAll); SetDlgItemText(IDC_STATIC_71, cstr.GetBuffer());
		cstr.Format(L"%d", gSystemMgr.m_nAAOK); SetDlgItemText(IDC_STATIC_70, cstr.GetBuffer());
		cstr.Format(L"%d", gSystemMgr.m_nAANG1); SetDlgItemText(IDC_STATIC_73, cstr.GetBuffer());
		cstr.Format(L"%d", gSystemMgr.m_nAANG2); SetDlgItemText(IDC_STATIC_75, cstr.GetBuffer());
		cstr.Format(L"%d", gSystemMgr.m_nAANG3); SetDlgItemText(IDC_STATIC_59, cstr.GetBuffer());
		cstr.Format(L"%.1f", gSystemMgr.m_dAAOKPer); SetDlgItemText(IDC_STATIC_77, cstr.GetBuffer());
		SetDlgItemText(IDC_STATIC_78, gSystemMgr.AATime.GetBuffer());

	}

	CDialogEx::OnTimer(nIDEvent);
}


void CCountDlg::OnCancel()
{
	KillTimer(TIMER_CONTROL_COUNT);

	CDialogEx::OnCancel();
}
