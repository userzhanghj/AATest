// RS232SetDlg.cpp: 实现文件
//

#include "pch.h"
#include "ProjectAA.h"
#include "RS232SetDlg.h"
#include "afxdialogex.h"


// CRS232SetDlg 对话框

IMPLEMENT_DYNAMIC(CRS232SetDlg, CDialogEx)

CRS232SetDlg::CRS232SetDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_COM, pParent)
	, m_nComNo2(0)
	, m_nPort2(0)
	, m_BRs232Auto(FALSE)
	, m_nLinkFlag(FALSE)
	, m_nPowerCom(0)
	, m_nPowerPort(0)
	, m_fValSet0(0)
	, m_fCurrentSet0(0)
	, m_fValSet1(0)
	, m_fCurrentSet1(0)
	, m_bPassRfid(FALSE)
{

}

CRS232SetDlg::~CRS232SetDlg()
{
}

void CRS232SetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_COM2, m_nComNo2);
	DDX_Text(pDX, IDC_EDIT_PORT2, m_nPort2);
	DDX_Check(pDX, IDC_CHECK_AUTO, m_BRs232Auto);
	DDX_Check(pDX, IDC_CHECK_POWERLINK, m_nLinkFlag);
	DDX_Text(pDX, IDC_EDIT_COM3, m_nPowerCom);
	DDX_Text(pDX, IDC_EDIT_PORT3, m_nPowerPort);
	DDX_Text(pDX, IDC_EDIT_VAL0, m_fValSet0);
	DDX_Text(pDX, IDC_EDIT_CURRENT0, m_fCurrentSet0);
	DDX_Text(pDX, IDC_EDIT_VAL1, m_fValSet1);
	DDX_Text(pDX, IDC_EDIT_CURRENT1, m_fCurrentSet1);
	DDX_Check(pDX, IDC_CHECK_AUTO2, m_bPassRfid);
}


BEGIN_MESSAGE_MAP(CRS232SetDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CRS232SetDlg::OnBnClickedButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_CONNECT2, &CRS232SetDlg::OnBnClickedButtonConnect2)
	ON_BN_CLICKED(IDC_BUTTON3, &CRS232SetDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON6, &CRS232SetDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &CRS232SetDlg::OnBnClickedButton7)
END_MESSAGE_MAP()


// CRS232SetDlg 消息处理程序


BOOL CRS232SetDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	ReadConfigIni();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CRS232SetDlg::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类

	CDialogEx::OnCancel();
}

void CRS232SetDlg::ReadConfigIni()
{
	m_nComNo2 = gSystemMgr.m_nComNo2;
	m_nPort2 = gSystemMgr.m_nComPort2;
	m_BRs232Auto = gSystemMgr.m_bAutoFlag_RS232;
	m_bPassRfid = gSystemMgr.m_nPassRfidFlag;

	m_nLinkFlag = gSystemMgr.m_nPowerFlag;
	m_nPowerCom = gSystemMgr.m_nPowerPort;
	m_nPowerPort = gSystemMgr.m_nPowerBaudrate;
	m_fValSet0 = gSystemMgr.voltage_val[0];
	m_fCurrentSet0 = gSystemMgr.current_limit[0];
	m_fValSet1 = gSystemMgr.voltage_val[1];
	m_fCurrentSet1 = gSystemMgr.current_limit[1];

	UpdateData(FALSE);
}

void CRS232SetDlg::SaveValueToConfig()
{
	UpdateData(TRUE);

	gSystemMgr.m_nComNo2 = m_nComNo2;
	gSystemMgr.m_nComPort2 = m_nPort2;
	gSystemMgr.m_bAutoFlag_RS232 = m_BRs232Auto;
	gSystemMgr.m_nPassRfidFlag = m_bPassRfid;

	gSystemMgr.m_nPowerPort = m_nPowerCom;
	gSystemMgr.m_nPowerBaudrate = m_nPowerPort;
	gSystemMgr.m_nPowerFlag = m_nLinkFlag;
	gSystemMgr.current_limit[0] = m_fCurrentSet0;
	gSystemMgr.voltage_val[0] = m_fValSet0;
	gSystemMgr.current_limit[1] = m_fCurrentSet1;
	gSystemMgr.voltage_val[1] = m_fValSet1;

	CString cstr;
	cstr.Format(L"%d", gSystemMgr.m_nComNo2);
	gSystemMgr.m_cRS232ConfigIni.SaveConfigIni(L"RS232", L"m_nComNo2", cstr);

	cstr.Format(L"%d", gSystemMgr.m_nComPort2);
	gSystemMgr.m_cRS232ConfigIni.SaveConfigIni(L"RS232", L"m_nComPort2", cstr);

	cstr.Format(L"%d", gSystemMgr.m_bAutoFlag_RS232);
	gSystemMgr.m_cRS232ConfigIni.SaveConfigIni(L"RS232", L"m_bAutoFlag_RS232", cstr);

	cstr.Format(L"%d", gSystemMgr.m_nPassRfidFlag);
	gSystemMgr.m_cRS232ConfigIni.SaveConfigIni(L"RS232", L"m_nPassRfidFlag", cstr);

	cstr.Format(L"%d", gSystemMgr.m_nPowerPort);
	gSystemMgr.m_cRS232ConfigIni.SaveConfigIni(L"Power", L"m_nPowerPort", cstr);

	cstr.Format(L"%d", gSystemMgr.m_nPowerBaudrate);
	gSystemMgr.m_cRS232ConfigIni.SaveConfigIni(L"Power", L"m_nPowerBaudrate", cstr);

	cstr.Format(L"%d", gSystemMgr.m_nPowerFlag);
	gSystemMgr.m_cRS232ConfigIni.SaveConfigIni(L"Power", L"m_nPowerFlag", cstr);

	cstr.Format(L"%.2f", gSystemMgr.current_limit[0]);
	gSystemMgr.m_cRS232ConfigIni.SaveConfigIni(L"Power", L"current_limit[0]", cstr);

	cstr.Format(L"%.2f", gSystemMgr.current_limit[1]);
	gSystemMgr.m_cRS232ConfigIni.SaveConfigIni(L"Power", L"current_limit[1]", cstr);

	cstr.Format(L"%.2f", gSystemMgr.voltage_val[0]);
	gSystemMgr.m_cRS232ConfigIni.SaveConfigIni(L"Power", L"voltage_val[0]", cstr);

	cstr.Format(L"%.2f", gSystemMgr.voltage_val[1]);
	gSystemMgr.m_cRS232ConfigIni.SaveConfigIni(L"Power", L"voltage_val[1]", cstr);


	gSystemLog.DisplayLogAndSave(L"RS232保存数据完成", LV_EVENT);
}

void CRS232SetDlg::OnBnClickedButtonSave()
{
	SaveValueToConfig();
}


void CRS232SetDlg::OnBnClickedButtonConnect2()
{
	if (gSystemMgr.m_cRfidComm2.get_com_port() == NULL) {
		int err = gSystemMgr.m_cRfidComm2.com_open(gSystemMgr.m_nComNo2, gSystemMgr.m_nComPort2, EVENPARITY);
		if (err != 1)
			gSystemMgr.Com2ConnectFlag = 0;
		else
			gSystemMgr.Com2ConnectFlag = 1;
	}
}


void CRS232SetDlg::OnBnClickedButton3()
{
	gSystemMgr.m_nButtonValue = 33;
	return;
}


void CRS232SetDlg::OnBnClickedButton6()
{
	gSystemMgr.m_nButtonValue = 34;
	return;
}


void CRS232SetDlg::OnBnClickedButton7()
{
	gSystemMgr.m_nButtonValue = 35;
	return;
}
