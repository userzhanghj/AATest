// LightTestDlg.cpp: 实现文件
//

#include "pch.h"
#include "ProjectAA.h"
#include "LightTestDlg.h"
#include "afxdialogex.h"


// CLightTestDlg 对话框

IMPLEMENT_DYNAMIC(CLightTestDlg, CDialogEx)

CLightTestDlg::CLightTestDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_STD, pParent)
	, LightFlag(FALSE)
	, LightX0(0)
	, LightX1(0)
	, LightX2(0)
	, LightX3(0)
	, LightX4(0)
	, LightY0(0)
	, LightY1(0)
	, LightY2(0)
	, LightY3(0)
	, LightY4(0)
	, LightSpec0(0)
	, LightSpec1(0)
	, LightSpec2(0)
	, LightSpec3(0)
	, LightSpec4(0)
	, LightW(0)
	, LightH(0)
{

}

CLightTestDlg::~CLightTestDlg()
{
}

void CLightTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_CHECK1, LightFlag);
	DDX_Text(pDX, IDC_EDIT1, LightX0);
	DDX_Text(pDX, IDC_EDIT4, LightX1);
	DDX_Text(pDX, IDC_EDIT7, LightX2);
	DDX_Text(pDX, IDC_EDIT9, LightX3);
	DDX_Text(pDX, IDC_EDIT11, LightX4);
	DDX_Text(pDX, IDC_EDIT2, LightY0);
	DDX_Text(pDX, IDC_EDIT5, LightY1);
	DDX_Text(pDX, IDC_EDIT8, LightY2);
	DDX_Text(pDX, IDC_EDIT10, LightY3);
	DDX_Text(pDX, IDC_EDIT12, LightY4);
	DDX_Text(pDX, IDC_EDIT13, LightSpec0);
	DDX_Text(pDX, IDC_EDIT14, LightSpec1);
	DDX_Text(pDX, IDC_EDIT15, LightSpec2);
	DDX_Text(pDX, IDC_EDIT16, LightSpec3);
	DDX_Text(pDX, IDC_EDIT17, LightSpec4);
	DDX_Text(pDX, IDC_EDIT18, LightW);
	DDX_Text(pDX, IDC_EDIT19, LightH);
}


BEGIN_MESSAGE_MAP(CLightTestDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CLightTestDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CLightTestDlg 消息处理程序


BOOL CLightTestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	ReadConfigIni();

	return TRUE;
}


void CLightTestDlg::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类

	CDialogEx::OnCancel();
}

void CLightTestDlg::ReadConfigIni()
{
	LightFlag = gSystemMgr.LightnessFlag;

	LightX0 = gSystemMgr.LightX[0];
	LightX1 = gSystemMgr.LightX[1];
	LightX2 = gSystemMgr.LightX[2];
	LightX3 = gSystemMgr.LightX[3];
	LightX4 = gSystemMgr.LightX[4];

	LightY0 = gSystemMgr.LightY[0];
	LightY1 = gSystemMgr.LightY[1];
	LightY2 = gSystemMgr.LightY[2];
	LightY3 = gSystemMgr.LightY[3];
	LightY4 = gSystemMgr.LightY[4];

	LightSpec0 = gSystemMgr.LightSpec[0];
	LightSpec1 = gSystemMgr.LightSpec[1];
	LightSpec2 = gSystemMgr.LightSpec[2];
	LightSpec3 = gSystemMgr.LightSpec[3];
	LightSpec4 = gSystemMgr.LightSpec[4];

	LightW = gSystemMgr.LightRoiW;
	LightH = gSystemMgr.LightRoiH;

	UpdateData(FALSE);
}

void CLightTestDlg::SaveValueToConfig()
{
	UpdateData(TRUE);

	gSystemMgr.LightnessFlag = LightFlag;

	gSystemMgr.LightX[0] = LightX0;
	gSystemMgr.LightX[1] = LightX1;
	gSystemMgr.LightX[2] = LightX2;
	gSystemMgr.LightX[3] = LightX3;
	gSystemMgr.LightX[4] = LightX4;

	gSystemMgr.LightY[0] = LightY0;
	gSystemMgr.LightY[1] = LightY1;
	gSystemMgr.LightY[2] = LightY2;
	gSystemMgr.LightY[3] = LightY3;
	gSystemMgr.LightY[4] = LightY4;

	gSystemMgr.LightSpec[0] = LightSpec0;
	gSystemMgr.LightSpec[1] = LightSpec1;
	gSystemMgr.LightSpec[2] = LightSpec2;
	gSystemMgr.LightSpec[3] = LightSpec3;
	gSystemMgr.LightSpec[4] = LightSpec4;

	gSystemMgr.LightRoiW = LightW;
	gSystemMgr.LightRoiH = LightH;

	CString cstr;
	cstr.Format(L"%d", gSystemMgr.LightnessFlag);gSystemMgr.m_cLightConfigIni.SaveConfigIni(L"Light", L"LightnessFlag", cstr);

	cstr.Format(L"%d", gSystemMgr.LightX[0]); gSystemMgr.m_cLightConfigIni.SaveConfigIni(L"Light", L"LightX[0]", cstr);
	cstr.Format(L"%d", gSystemMgr.LightX[1]); gSystemMgr.m_cLightConfigIni.SaveConfigIni(L"Light", L"LightX[1]", cstr);
	cstr.Format(L"%d", gSystemMgr.LightX[2]); gSystemMgr.m_cLightConfigIni.SaveConfigIni(L"Light", L"LightX[2]", cstr);
	cstr.Format(L"%d", gSystemMgr.LightX[3]); gSystemMgr.m_cLightConfigIni.SaveConfigIni(L"Light", L"LightX[3]", cstr);
	cstr.Format(L"%d", gSystemMgr.LightX[4]); gSystemMgr.m_cLightConfigIni.SaveConfigIni(L"Light", L"LightX[4]", cstr);

	cstr.Format(L"%d", gSystemMgr.LightY[0]); gSystemMgr.m_cLightConfigIni.SaveConfigIni(L"Light", L"LightY[0]", cstr);
	cstr.Format(L"%d", gSystemMgr.LightY[1]); gSystemMgr.m_cLightConfigIni.SaveConfigIni(L"Light", L"LightY[1]", cstr);
	cstr.Format(L"%d", gSystemMgr.LightY[2]); gSystemMgr.m_cLightConfigIni.SaveConfigIni(L"Light", L"LightY[2]", cstr);
	cstr.Format(L"%d", gSystemMgr.LightY[3]); gSystemMgr.m_cLightConfigIni.SaveConfigIni(L"Light", L"LightY[3]", cstr);
	cstr.Format(L"%d", gSystemMgr.LightY[4]); gSystemMgr.m_cLightConfigIni.SaveConfigIni(L"Light", L"LightY[4]", cstr);

	cstr.Format(L"%d", gSystemMgr.LightSpec[0]); gSystemMgr.m_cLightConfigIni.SaveConfigIni(L"Light", L"LightSpec[0]", cstr);
	cstr.Format(L"%d", gSystemMgr.LightSpec[1]); gSystemMgr.m_cLightConfigIni.SaveConfigIni(L"Light", L"LightSpec[1]", cstr);
	cstr.Format(L"%d", gSystemMgr.LightSpec[2]); gSystemMgr.m_cLightConfigIni.SaveConfigIni(L"Light", L"LightSpec[2]", cstr);
	cstr.Format(L"%d", gSystemMgr.LightSpec[3]); gSystemMgr.m_cLightConfigIni.SaveConfigIni(L"Light", L"LightSpec[3]", cstr);
	cstr.Format(L"%d", gSystemMgr.LightSpec[4]); gSystemMgr.m_cLightConfigIni.SaveConfigIni(L"Light", L"LightSpec[4]", cstr);

	cstr.Format(L"%d", gSystemMgr.LightRoiW); gSystemMgr.m_cLightConfigIni.SaveConfigIni(L"Light", L"LightRoiW", cstr);
	cstr.Format(L"%d", gSystemMgr.LightRoiH); gSystemMgr.m_cLightConfigIni.SaveConfigIni(L"Light", L"LightRoiH", cstr);
	gSystemLog.DisplayLogAndSave(L"保存数据完成", LV_EVENT);
}

void CLightTestDlg::OnBnClickedButton1()
{
	SaveValueToConfig();
}
