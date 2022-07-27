// IOControlDlg.cpp: 实现文件
//

#include "pch.h"
#include "ProjectAA.h"
#include "IOControlDlg.h"
#include "afxdialogex.h"


// CIOControlDlg 对话框

IMPLEMENT_DYNAMIC(CIOControlDlg, CDialogEx)

CIOControlDlg::CIOControlDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1_IO, pParent)
{

}

CIOControlDlg::~CIOControlDlg()
{
}

void CIOControlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CIOControlDlg, CDialogEx)
	ON_WM_CLOSE()
	ON_CONTROL_RANGE(BN_CLICKED, IDC_CHECK_Y0, IDC_CHECK_Y31, &CIOControlDlg::OnBnClickedOption)
	ON_WM_CONTEXTMENU()
	ON_WM_DESTROY()
	ON_WM_RBUTTONDOWN()
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CIOControlDlg 消息处理程序

void CIOControlDlg::SetIoStatus()
{
	CButton* pCheck = nullptr;
	pCheck = (CButton*)GetDlgItem(IDC_CHECK_S0);   pCheck->SetCheck(gSystemMgr.S00);
	pCheck = (CButton*)GetDlgItem(IDC_CHECK_S1);   pCheck->SetCheck(gSystemMgr.S01);
	pCheck = (CButton*)GetDlgItem(IDC_CHECK_S2);   pCheck->SetCheck(gSystemMgr.S02);
	pCheck = (CButton*)GetDlgItem(IDC_CHECK_S3);   pCheck->SetCheck(gSystemMgr.S03);
	pCheck = (CButton*)GetDlgItem(IDC_CHECK_S4);   pCheck->SetCheck(gSystemMgr.S04);
	pCheck = (CButton*)GetDlgItem(IDC_CHECK_S5);   pCheck->SetCheck(gSystemMgr.S05);
	pCheck = (CButton*)GetDlgItem(IDC_CHECK_S6);   pCheck->SetCheck(gSystemMgr.S06);
	pCheck = (CButton*)GetDlgItem(IDC_CHECK_S7);   pCheck->SetCheck(gSystemMgr.S07);
	pCheck = (CButton*)GetDlgItem(IDC_CHECK_S8);   pCheck->SetCheck(gSystemMgr.S08);
	pCheck = (CButton*)GetDlgItem(IDC_CHECK_S9);   pCheck->SetCheck(gSystemMgr.S09);
	pCheck = (CButton*)GetDlgItem(IDC_CHECK_S10);  pCheck->SetCheck(gSystemMgr.S10);
	pCheck = (CButton*)GetDlgItem(IDC_CHECK_S11);  pCheck->SetCheck(gSystemMgr.S11);
	pCheck = (CButton*)GetDlgItem(IDC_CHECK_S12);  pCheck->SetCheck(gSystemMgr.S12);
	pCheck = (CButton*)GetDlgItem(IDC_CHECK_S13);  pCheck->SetCheck(gSystemMgr.S13);
	pCheck = (CButton*)GetDlgItem(IDC_CHECK_S14);  pCheck->SetCheck(gSystemMgr.S14);
	pCheck = (CButton*)GetDlgItem(IDC_CHECK_S15);  pCheck->SetCheck(gSystemMgr.S15);
	pCheck = (CButton*)GetDlgItem(IDC_CHECK_S16);  pCheck->SetCheck(gSystemMgr.S16);
	pCheck = (CButton*)GetDlgItem(IDC_CHECK_S17);  pCheck->SetCheck(gSystemMgr.S17);
	pCheck = (CButton*)GetDlgItem(IDC_CHECK_S18);  pCheck->SetCheck(gSystemMgr.S18);
	pCheck = (CButton*)GetDlgItem(IDC_CHECK_S19);  pCheck->SetCheck(gSystemMgr.S19);
	pCheck = (CButton*)GetDlgItem(IDC_CHECK_S20);  pCheck->SetCheck(gSystemMgr.S20);
	pCheck = (CButton*)GetDlgItem(IDC_CHECK_S21);  pCheck->SetCheck(gSystemMgr.S21);
	pCheck = (CButton*)GetDlgItem(IDC_CHECK_S22);  pCheck->SetCheck(gSystemMgr.S22);
	pCheck = (CButton*)GetDlgItem(IDC_CHECK_S23);  pCheck->SetCheck(gSystemMgr.S23);
	pCheck = (CButton*)GetDlgItem(IDC_CHECK_S24);  pCheck->SetCheck(gSystemMgr.S24);
	pCheck = (CButton*)GetDlgItem(IDC_CHECK_S25);  pCheck->SetCheck(gSystemMgr.S25);
	pCheck = (CButton*)GetDlgItem(IDC_CHECK_S26);  pCheck->SetCheck(gSystemMgr.S26);
	pCheck = (CButton*)GetDlgItem(IDC_CHECK_S27);  pCheck->SetCheck(gSystemMgr.S27);
	pCheck = (CButton*)GetDlgItem(IDC_CHECK_S28);  pCheck->SetCheck(gSystemMgr.S28);
	pCheck = (CButton*)GetDlgItem(IDC_CHECK_S29);  pCheck->SetCheck(gSystemMgr.S29);
	pCheck = (CButton*)GetDlgItem(IDC_CHECK_S30);  pCheck->SetCheck(gSystemMgr.S30);
	pCheck = (CButton*)GetDlgItem(IDC_CHECK_S31);  pCheck->SetCheck(gSystemMgr.S31);

	pCheck = (CButton*)GetDlgItem(IDC_CHECK_Y0);  pCheck->SetCheck(gSystemMgr.Y00);
	pCheck = (CButton*)GetDlgItem(IDC_CHECK_Y1);  pCheck->SetCheck(gSystemMgr.Y01);
	pCheck = (CButton*)GetDlgItem(IDC_CHECK_Y2);  pCheck->SetCheck(gSystemMgr.Y02);
	pCheck = (CButton*)GetDlgItem(IDC_CHECK_Y3);  pCheck->SetCheck(gSystemMgr.Y03);
	pCheck = (CButton*)GetDlgItem(IDC_CHECK_Y4);  pCheck->SetCheck(gSystemMgr.Y04);
	pCheck = (CButton*)GetDlgItem(IDC_CHECK_Y5);  pCheck->SetCheck(gSystemMgr.Y05);
	pCheck = (CButton*)GetDlgItem(IDC_CHECK_Y6);  pCheck->SetCheck(gSystemMgr.Y06);
	pCheck = (CButton*)GetDlgItem(IDC_CHECK_Y7);  pCheck->SetCheck(gSystemMgr.Y07);
	pCheck = (CButton*)GetDlgItem(IDC_CHECK_Y8);  pCheck->SetCheck(gSystemMgr.Y08);
	pCheck = (CButton*)GetDlgItem(IDC_CHECK_Y9);  pCheck->SetCheck(gSystemMgr.Y09);
	pCheck = (CButton*)GetDlgItem(IDC_CHECK_Y10);  pCheck->SetCheck(gSystemMgr.Y10);
	pCheck = (CButton*)GetDlgItem(IDC_CHECK_Y11);  pCheck->SetCheck(gSystemMgr.Y11);
	pCheck = (CButton*)GetDlgItem(IDC_CHECK_Y12);  pCheck->SetCheck(gSystemMgr.Y12);
	pCheck = (CButton*)GetDlgItem(IDC_CHECK_Y13);  pCheck->SetCheck(gSystemMgr.Y13);
	pCheck = (CButton*)GetDlgItem(IDC_CHECK_Y14);  pCheck->SetCheck(gSystemMgr.Y14);
	pCheck = (CButton*)GetDlgItem(IDC_CHECK_Y15);  pCheck->SetCheck(gSystemMgr.Y15);

	pCheck = (CButton*)GetDlgItem(IDC_CHECK_Y16);  pCheck->SetCheck(gSystemMgr.Y16);
	pCheck = (CButton*)GetDlgItem(IDC_CHECK_Y17);  pCheck->SetCheck(gSystemMgr.Y17);
	pCheck = (CButton*)GetDlgItem(IDC_CHECK_Y18);  pCheck->SetCheck(gSystemMgr.Y18);
	pCheck = (CButton*)GetDlgItem(IDC_CHECK_Y19);  pCheck->SetCheck(gSystemMgr.Y19);
	pCheck = (CButton*)GetDlgItem(IDC_CHECK_Y20);  pCheck->SetCheck(gSystemMgr.Y20);
	pCheck = (CButton*)GetDlgItem(IDC_CHECK_Y21);  pCheck->SetCheck(gSystemMgr.Y21);
	pCheck = (CButton*)GetDlgItem(IDC_CHECK_Y22);  pCheck->SetCheck(gSystemMgr.Y22);
	pCheck = (CButton*)GetDlgItem(IDC_CHECK_Y23);  pCheck->SetCheck(gSystemMgr.Y23);
	pCheck = (CButton*)GetDlgItem(IDC_CHECK_Y24);  pCheck->SetCheck(gSystemMgr.Y24);
	pCheck = (CButton*)GetDlgItem(IDC_CHECK_Y25);  pCheck->SetCheck(gSystemMgr.Y25);
	pCheck = (CButton*)GetDlgItem(IDC_CHECK_Y26);  pCheck->SetCheck(gSystemMgr.Y26);
	pCheck = (CButton*)GetDlgItem(IDC_CHECK_Y27);  pCheck->SetCheck(gSystemMgr.Y27);
	pCheck = (CButton*)GetDlgItem(IDC_CHECK_Y28);  pCheck->SetCheck(gSystemMgr.Y28);
	pCheck = (CButton*)GetDlgItem(IDC_CHECK_Y29);  pCheck->SetCheck(gSystemMgr.Y29);
	pCheck = (CButton*)GetDlgItem(IDC_CHECK_Y30);  pCheck->SetCheck(gSystemMgr.Y30);
	pCheck = (CButton*)GetDlgItem(IDC_CHECK_Y31);  pCheck->SetCheck(gSystemMgr.Y31);

}


BOOL CIOControlDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SetTimer(TIMER_ID_IO_CONTROL_STATUS, 50, NULL);
	ChangeIoTextIn();

	ChangeIoTextOut();
	SetIoStatus();
	return TRUE;  
}


void CIOControlDlg::OnCancel()
{
	KillTimer(TIMER_ID_IO_CONTROL_STATUS);
	CDialogEx::OnCancel();
}


void CIOControlDlg::OnClose()
{

	CDialogEx::OnClose();
}

void CIOControlDlg::ChangeIoTextIn()
{
	std::vector<IO_MODULE> vIoMap;
	vIoMap = *gConfigMgr.GetIOInputSetting();
	for (int i = 0; i < 32; i++)
	{
		int cnt;
		cnt = i * 2 - i % 2;
		CWnd * pStatic = nullptr;
		pStatic = (CWnd*)GetDlgItem(IDC_STATIC_S0 + cnt);//控件编号问题
		CString cstr;
		cstr.Format(L"%d_", i);
		cstr.Append(vIoMap[i].m_cstrDescription);
		pStatic->SetWindowTextW(cstr);
	}
}

void CIOControlDlg::ChangeIoTextOut()
{
	std::vector<IO_MODULE> vIoMap;
	vIoMap = *gConfigMgr.GetIOOutputSetting();
	for (int i = 0; i < 32; i++)
	{
		int cnt;
		cnt = i * 2;
		CWnd * pStatic = nullptr;
		pStatic = (CWnd*)GetDlgItem(IDC_STATIC_Y0 + cnt);//控件编号问题
		CString cstr;
		cstr.Format(L"%d_", i);
		cstr.Append(vIoMap[i].m_cstrDescription);
		pStatic->SetWindowTextW(cstr);

	}
}

BOOL CIOControlDlg::PreTranslateMessage(MSG* pMsg)
{
	WPARAM param = pMsg->wParam;
	if (param == VK_ESCAPE || param == VK_RETURN || param == VK_SPACE)
		return TRUE;
	if (pMsg->message == WM_SYSKEYDOWN && param == VK_F4)
		return TRUE;

	return CDialogEx::PreTranslateMessage(pMsg);
}

void CIOControlDlg::OnBnClickedOption(UINT nID)
{
	int nPort = nID - IDC_CHECK_Y0;
	nPort = nPort / 2;
	CString cstr;
	cstr.Format(L"%d", nPort);

	CButton* pCheckBox = (CButton*)GetDlgItem(nID);
	int nFlag = pCheckBox->GetCheck();
	if (nFlag == BST_CHECKED)
	{
		gSystemMgr.m_cIo.SetOutputIo(nPort, ON);
		//cstr.Append(L"选中");
		//gSystemLog.DisplayLogAndSave(cstr.GetBuffer(), LV_EVENT);
	}
	if (nFlag == BST_UNCHECKED)
	{
		gSystemMgr.m_cIo.SetOutputIo(nPort, OFF);
		//cstr.Append(L"取消");
		//gSystemLog.DisplayLogAndSave(cstr.GetBuffer(), LV_EVENT);
	}
} 

void CIOControlDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == TIMER_ID_IO_CONTROL_STATUS)
	{
		SetIoStatus();
	}

	CDialogEx::OnTimer(nIDEvent);
}
