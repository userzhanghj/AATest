// SFRSettingDlg.cpp: 实现文件
//

#include "pch.h"
#include "ProjectAA.h"
#include "SFRSettingDlg.h"
#include "afxdialogex.h"


// CSFRSettingDlg 对话框

IMPLEMENT_DYNAMIC(CSFRSettingDlg, CDialogEx)

CSFRSettingDlg::CSFRSettingDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_SFR, pParent)
	, m_nMtfPer(0)
	, m_dFreq(0)
	, m_bUseMtf(FALSE)
	, m_bOpenFieldA(FALSE)
	, m_nRoiW0(0)
	, m_nRoiH0(0)
	, m_nSearchW0(0)
	, m_nSearchH0(0)
	, m_nPattern0(0)
	, m_nDistance0(0)
	, m_nRoiW1(0)
	, m_nRoiH1(0)
	, m_nSearchW1(0)
	, m_nSearchH1(0)
	, m_nPattern1(0)
	, m_nDistance1(0)
	, m_nCenterSpec(0)
	, m_dAngleSpec(0)
	, m_dCenterSfrSpec(0)
	, m_dFieldASfrSpec(0)
	, m_bLeft0(FALSE)
	, m_bLeft1(FALSE)
	, m_bLeft2(FALSE)
	, m_bLeft3(FALSE)
	, m_bLeft4(FALSE)
	, m_bTop0(FALSE)
	, m_bTop1(FALSE)
	, m_bTop2(FALSE)
	, m_bTop3(FALSE)
	, m_bTop4(FALSE)
	, m_bRight0(FALSE)
	, m_bRight1(FALSE)
	, m_bRight2(FALSE)
	, m_bRight3(FALSE)
	, m_bRight4(FALSE)
	, m_bButton0(FALSE)
	, m_bButton1(FALSE)
	, m_bButton2(FALSE)
	, m_bButton3(FALSE)
	, m_bButton4(FALSE)
	, m_nBin0(0)
	, m_nBin1(0)
	, m_nBin2(0)
	, m_nBin3(0)
	, m_nBin4(0)
	, m_bDisplay(FALSE)
	, m_nStartX0(0)
	, m_nStartX1(0)
	, m_nStartX2(0)
	, m_nStartX3(0)
	, m_nStartX4(0)
	, m_nStartY0(0)
	, m_nStartY1(0)
	, m_nStartY2(0)
	, m_nStartY3(0)
	, m_nStartY4(0)
	, m_nCenterX(0)
	, m_nCenterY(0)
	, m_bDrawLine(FALSE)
	, m_dCenterSfrSpec2(0)
	, m_dFieldASfrSpec2(0)
{

}

CSFRSettingDlg::~CSFRSettingDlg()
{
}

void CSFRSettingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_MTF, m_nMtfPer);
	DDX_Text(pDX, IDC_EDIT_FREQ, m_dFreq);
	DDX_Check(pDX, IDC_CHECK_USE_MTF, m_bUseMtf);
	DDX_Check(pDX, IDC_CHECK_OPEN_FIELDA, m_bOpenFieldA);
	DDX_Text(pDX, IDC_EDIT_ROI_W0, m_nRoiW0);
	DDX_Text(pDX, IDC_EDIT_ROI_H0, m_nRoiH0);
	DDX_Text(pDX, IDC_EDIT_SWARCH_W0, m_nSearchW0);
	DDX_Text(pDX, IDC_EDIT_SEARCH_H0, m_nSearchH0);
	DDX_Text(pDX, IDC_EDIT_PATTERN0, m_nPattern0);
	DDX_Text(pDX, IDC_EDIT_DISTANCE0, m_nDistance0);
	DDX_Text(pDX, IDC_EDIT_ROI_W1, m_nRoiW1);
	DDX_Text(pDX, IDC_EDIT_ROI_H1, m_nRoiH1);
	DDX_Text(pDX, IDC_EDIT_SEARCH_W1, m_nSearchW1);
	DDX_Text(pDX, IDC_EDIT_SEARCH_H1, m_nSearchH1);
	DDX_Text(pDX, IDC_EDIT_PATTERN1, m_nPattern1);
	DDX_Text(pDX, IDC_EDIT_DISTANCE1, m_nDistance1);
	DDX_Text(pDX, IDC_EDIT_CENTER_DIF, m_nCenterSpec);
	DDX_Text(pDX, IDC_EDIT_ANGLE_DIF, m_dAngleSpec);
	DDX_Text(pDX, IDC_EDIT_CENTER_SFR, m_dCenterSfrSpec);
	DDX_Text(pDX, IDC_EDIT_FIELDA_SFR, m_dFieldASfrSpec);
	DDX_Check(pDX, IDC_CHECK_LEFT0, m_bLeft0);
	DDX_Check(pDX, IDC_CHECK_LEFT1, m_bLeft1);
	DDX_Check(pDX, IDC_CHECK_LEFT2, m_bLeft2);
	DDX_Check(pDX, IDC_CHECK_LEFT3, m_bLeft3);
	DDX_Check(pDX, IDC_CHECK_LEFT4, m_bLeft4);
	DDX_Check(pDX, IDC_CHECK_TOP0, m_bTop0);
	DDX_Check(pDX, IDC_CHECK_TOP1, m_bTop1);
	DDX_Check(pDX, IDC_CHECK_TOP2, m_bTop2);
	DDX_Check(pDX, IDC_CHECK_TOP3, m_bTop3);
	DDX_Check(pDX, IDC_CHECK_TOP4, m_bTop4);
	DDX_Check(pDX, IDC_CHECK_RIGHT0, m_bRight0);
	DDX_Check(pDX, IDC_CHECK_RIGHT1, m_bRight1);
	DDX_Check(pDX, IDC_CHECK_RIGHT2, m_bRight2);
	DDX_Check(pDX, IDC_CHECK_RIGHT3, m_bRight3);
	DDX_Check(pDX, IDC_CHECK_RIGHT4, m_bRight4);
	DDX_Check(pDX, IDC_CHECK_BUTTON0, m_bButton0);
	DDX_Check(pDX, IDC_CHECK_BUTTON1, m_bButton1);
	DDX_Check(pDX, IDC_CHECK_BUTTON2, m_bButton2);
	DDX_Check(pDX, IDC_CHECK_BUTTON3, m_bButton3);
	DDX_Check(pDX, IDC_CHECK_BUTTON4, m_bButton4);
	DDX_Text(pDX, IDC_EDIT_BIN0, m_nBin0);
	DDX_Text(pDX, IDC_EDIT_BIN1, m_nBin1);
	DDX_Text(pDX, IDC_EDIT_BIN2, m_nBin2);
	DDX_Text(pDX, IDC_EDIT_BIN3, m_nBin3);
	DDX_Text(pDX, IDC_EDIT_BIN4, m_nBin4);
	DDX_Check(pDX, IDC_CHECK_DISPLAY, m_bDisplay);
	DDX_Control(pDX, IDC_COMBO_COUNT, m_comboCount);
	DDX_Text(pDX, IDC_EDIT_START_X0, m_nStartX0);
	DDX_Text(pDX, IDC_EDIT_START_X1, m_nStartX1);
	DDX_Text(pDX, IDC_EDIT_START_X2, m_nStartX2);
	DDX_Text(pDX, IDC_EDIT_START_X3, m_nStartX3);
	DDX_Text(pDX, IDC_EDIT_START_X4, m_nStartX4);
	DDX_Text(pDX, IDC_EDIT_START_Y0, m_nStartY0);
	DDX_Text(pDX, IDC_EDIT_START_Y1, m_nStartY1);
	DDX_Text(pDX, IDC_EDIT_START_Y2, m_nStartY2);
	DDX_Text(pDX, IDC_EDIT_START_Y3, m_nStartY3);
	DDX_Text(pDX, IDC_EDIT_START_Y4, m_nStartY4);
	DDX_Control(pDX, IDC_SPIN1, m_spinStartX0);
	DDX_Control(pDX, IDC_SPIN2, m_spinStartX1);
	DDX_Control(pDX, IDC_SPIN3, m_spinStartX2);
	DDX_Control(pDX, IDC_SPIN4, m_spinStartX3);
	DDX_Control(pDX, IDC_SPIN5, m_spinStartX4);
	DDX_Control(pDX, IDC_SPIN6, m_spinStartY0);
	DDX_Control(pDX, IDC_SPIN7, m_spinStartY1);
	DDX_Control(pDX, IDC_SPIN8, m_spinStartY2);
	DDX_Control(pDX, IDC_SPIN9, m_spinStartY3);
	DDX_Control(pDX, IDC_SPIN10, m_spinStartY4);
	DDX_Text(pDX, IDC_EDIT_CENTER_X, m_nCenterX);
	DDX_Text(pDX, IDC_EDIT_CENTER_Y, m_nCenterY);
	DDX_Check(pDX, IDC_CHECK_DRAWLINE, m_bDrawLine);
	DDX_Text(pDX, IDC_EDIT_CENTER_SFR2, m_dCenterSfrSpec2);
	DDX_Text(pDX, IDC_EDIT_FIELDA_SFR2, m_dFieldASfrSpec2);
}


BEGIN_MESSAGE_MAP(CSFRSettingDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CSFRSettingDlg::OnBnClickedButtonSave)
	ON_EN_CHANGE(IDC_EDIT_START_X0, &CSFRSettingDlg::OnEnChangeEditStartX0)
	ON_EN_CHANGE(IDC_EDIT_START_X1, &CSFRSettingDlg::OnEnChangeEditStartX1)
	ON_EN_CHANGE(IDC_EDIT_START_X2, &CSFRSettingDlg::OnEnChangeEditStartX2)
	ON_EN_CHANGE(IDC_EDIT_START_X3, &CSFRSettingDlg::OnEnChangeEditStartX3)
	ON_EN_CHANGE(IDC_EDIT_START_X4, &CSFRSettingDlg::OnEnChangeEditStartX4)
	ON_EN_CHANGE(IDC_EDIT_START_Y0, &CSFRSettingDlg::OnEnChangeEditStartY0)
	ON_EN_CHANGE(IDC_EDIT_START_Y1, &CSFRSettingDlg::OnEnChangeEditStartY1)
	ON_EN_CHANGE(IDC_EDIT_START_Y2, &CSFRSettingDlg::OnEnChangeEditStartY2)
	ON_EN_CHANGE(IDC_EDIT_START_Y3, &CSFRSettingDlg::OnEnChangeEditStartY3)
	ON_EN_CHANGE(IDC_EDIT_START_Y4, &CSFRSettingDlg::OnEnChangeEditStartY4)
	ON_CBN_SELCHANGE(IDC_COMBO_COUNT, &CSFRSettingDlg::OnCbnSelchangeComboCount)
	ON_BN_CLICKED(IDC_CHECK_DISPLAY, &CSFRSettingDlg::OnBnClickedCheckDisplay)
END_MESSAGE_MAP()


// CSFRSettingDlg 消息处理程序


void CSFRSettingDlg::ReadConfigIni()
{
	m_nMtfPer = gSystemMgr.m_nMtfPer;
	m_dFreq = gSystemMgr.m_dFreq;
	m_bUseMtf = gSystemMgr.m_bUseMTF;
	m_bOpenFieldA = gSystemMgr.m_bOpenFieldA;
	m_nRoiW0 = gSystemMgr.m_nRoiW[0];
	m_nRoiH0 = gSystemMgr.m_nRoiH[0];
	m_nSearchW0 = gSystemMgr.m_nSearchW[0];
	m_nSearchH0 = gSystemMgr.m_nSearchH[0];
	m_nPattern0 = gSystemMgr.m_nPattern[0];
	m_nDistance0 = gSystemMgr.m_nDistance[0];
	m_nRoiW1 = gSystemMgr.m_nRoiW[1];
	m_nRoiH1 = gSystemMgr.m_nRoiH[1];
	m_nSearchW1 = gSystemMgr.m_nSearchW[1];
	m_nSearchH1 = gSystemMgr.m_nSearchH[1];
	m_nPattern1 = gSystemMgr.m_nPattern[1];
	m_nDistance1 = gSystemMgr.m_nDistance[1];
	m_nCenterSpec = gSystemMgr.m_nSpecCenter;
	m_dAngleSpec = gSystemMgr.m_dSpecAAAngle;
	m_dCenterSfrSpec = gSystemMgr.m_dSpecSfr[0];
	m_dFieldASfrSpec = gSystemMgr.m_dSpecSfr[1];
	m_bLeft0 = gSystemMgr.m_nRoiEnable[0][3];
	m_bLeft1 = gSystemMgr.m_nRoiEnable[1][3];
	m_bLeft2 = gSystemMgr.m_nRoiEnable[2][3];
	m_bLeft3 = gSystemMgr.m_nRoiEnable[3][3];
	m_bLeft4 = gSystemMgr.m_nRoiEnable[4][3];
	m_bTop0 = gSystemMgr.m_nRoiEnable[0][2];
	m_bTop1 = gSystemMgr.m_nRoiEnable[1][2];
	m_bTop2 = gSystemMgr.m_nRoiEnable[2][2];
	m_bTop3 = gSystemMgr.m_nRoiEnable[3][2];
	m_bTop4 = gSystemMgr.m_nRoiEnable[4][2];
	m_bRight0 = gSystemMgr.m_nRoiEnable[0][1];
	m_bRight1 = gSystemMgr.m_nRoiEnable[1][1];
	m_bRight2 = gSystemMgr.m_nRoiEnable[2][1];
	m_bRight3 = gSystemMgr.m_nRoiEnable[3][1];
	m_bRight4 = gSystemMgr.m_nRoiEnable[4][1];
	m_bButton0 = gSystemMgr.m_nRoiEnable[0][0];
	m_bButton1 = gSystemMgr.m_nRoiEnable[1][0];
	m_bButton2 = gSystemMgr.m_nRoiEnable[2][0];
	m_bButton3 = gSystemMgr.m_nRoiEnable[3][0];
	m_bButton4 = gSystemMgr.m_nRoiEnable[4][0];
	m_nBin0 = gSystemMgr.m_nBin[0];
	m_nBin1 = gSystemMgr.m_nBin[1];
	m_nBin2 = gSystemMgr.m_nBin[2];
	m_nBin3 = gSystemMgr.m_nBin[3];
	m_nBin4 = gSystemMgr.m_nBin[4];
	//BOOL m_bDisplay;
	//CComboBox m_comboCount;
	m_nStartX0 = gSystemMgr.m_nStartX[0];
	m_nStartX1 = gSystemMgr.m_nStartX[1];
	m_nStartX2 = gSystemMgr.m_nStartX[2];
	m_nStartX3 = gSystemMgr.m_nStartX[3];
	m_nStartX4 = gSystemMgr.m_nStartX[4];
	m_nStartY0 = gSystemMgr.m_nStartY[0];
	m_nStartY1 = gSystemMgr.m_nStartY[1];
	m_nStartY2 = gSystemMgr.m_nStartY[2];
	m_nStartY3 = gSystemMgr.m_nStartY[3];
	m_nStartY4 = gSystemMgr.m_nStartY[4];

	m_nCenterX = gSystemMgr.m_nTargetX;
	m_nCenterY = gSystemMgr.m_nTargetY;
	m_bDrawLine = gSystemMgr.m_bDrawLine;

	m_dCenterSfrSpec2 = gSystemMgr.m_dSpecSfrUV[0];
	m_dFieldASfrSpec2 = gSystemMgr.m_dSpecSfrUV[1];

	UpdateData(FALSE);
}

void CSFRSettingDlg::SaveEditValueToConfig()
{
	UpdateData(TRUE);

	CString cstr;
	gSystemMgr.m_nMtfPer = m_nMtfPer;
	cstr.Format(L"%d", gSystemMgr.m_nMtfPer); gSystemMgr.m_cCaptureConfigIni.SaveConfigIni(L"SfrSetting", L"m_nMtfPer", cstr);
	gSystemMgr.m_dFreq = m_dFreq;
	cstr.Format(L"%.3f", gSystemMgr.m_dFreq); gSystemMgr.m_cCaptureConfigIni.SaveConfigIni(L"SfrSetting", L"m_dFreq", cstr);
	gSystemMgr.m_bUseMTF = m_bUseMtf;
	cstr.Format(L"%d", gSystemMgr.m_bUseMTF); gSystemMgr.m_cCaptureConfigIni.SaveConfigIni(L"SfrSetting", L"m_bUseMTF", cstr);
	gSystemMgr.m_bOpenFieldA = m_bOpenFieldA;
	cstr.Format(L"%d", gSystemMgr.m_bOpenFieldA); gSystemMgr.m_cCaptureConfigIni.SaveConfigIni(L"SfrSetting", L"m_bOpenFieldA", cstr);
	gSystemMgr.m_nRoiW[0] = m_nRoiW0;
	cstr.Format(L"%d", gSystemMgr.m_nRoiW[0]); gSystemMgr.m_cCaptureConfigIni.SaveConfigIni(L"SfrSetting", L"m_nRoiW[0]", cstr);
	gSystemMgr.m_nRoiH[0] = m_nRoiH0;
	cstr.Format(L"%d", gSystemMgr.m_nRoiH[0]); gSystemMgr.m_cCaptureConfigIni.SaveConfigIni(L"SfrSetting", L"m_nRoiH[0]", cstr);
	gSystemMgr.m_nSearchW[0] = m_nSearchW0;
	cstr.Format(L"%d", gSystemMgr.m_nSearchW[0]); gSystemMgr.m_cCaptureConfigIni.SaveConfigIni(L"SfrSetting", L"m_nSearchW[0]", cstr);
	gSystemMgr.m_nSearchH[0] = m_nSearchH0;
	cstr.Format(L"%d", gSystemMgr.m_nSearchH[0]); gSystemMgr.m_cCaptureConfigIni.SaveConfigIni(L"SfrSetting", L"m_nSearchH[0]", cstr);
	gSystemMgr.m_nPattern[0] = m_nPattern0;
	cstr.Format(L"%d", gSystemMgr.m_nPattern[0]); gSystemMgr.m_cCaptureConfigIni.SaveConfigIni(L"SfrSetting", L"m_nPattern[0]", cstr);
	gSystemMgr.m_nDistance[0] = m_nDistance0;
	cstr.Format(L"%d", gSystemMgr.m_nDistance[0]); gSystemMgr.m_cCaptureConfigIni.SaveConfigIni(L"SfrSetting", L"m_nDistance[0]", cstr);
	gSystemMgr.m_nRoiW[1] = m_nRoiW1;
	cstr.Format(L"%d", gSystemMgr.m_nRoiW[1]); gSystemMgr.m_cCaptureConfigIni.SaveConfigIni(L"SfrSetting", L"m_nRoiW[1]", cstr);
	gSystemMgr.m_nRoiH[1] = m_nRoiH1;
	cstr.Format(L"%d", gSystemMgr.m_nRoiH[1]); gSystemMgr.m_cCaptureConfigIni.SaveConfigIni(L"SfrSetting", L"m_nRoiH[1]", cstr);
	gSystemMgr.m_nSearchW[1] = m_nSearchW1;
	cstr.Format(L"%d", gSystemMgr.m_nSearchW[1]); gSystemMgr.m_cCaptureConfigIni.SaveConfigIni(L"SfrSetting", L"m_nSearchW[1]", cstr);
	gSystemMgr.m_nSearchH[1] = m_nSearchH1;
	cstr.Format(L"%d", gSystemMgr.m_nSearchH[1]); gSystemMgr.m_cCaptureConfigIni.SaveConfigIni(L"SfrSetting", L"m_nSearchH[1]", cstr);
	gSystemMgr.m_nPattern[1] = m_nPattern1;
	cstr.Format(L"%d", gSystemMgr.m_nPattern[1]); gSystemMgr.m_cCaptureConfigIni.SaveConfigIni(L"SfrSetting", L"m_nPattern[1]", cstr);
	gSystemMgr.m_nDistance[1] = m_nDistance1;
	cstr.Format(L"%d", gSystemMgr.m_nDistance[1]); gSystemMgr.m_cCaptureConfigIni.SaveConfigIni(L"SfrSetting", L"m_nDistance[1]", cstr);
	gSystemMgr.m_nSpecCenter = m_nCenterSpec;
	cstr.Format(L"%d", gSystemMgr.m_nSpecCenter); gSystemMgr.m_cCaptureConfigIni.SaveConfigIni(L"SfrSetting", L"m_nSpecCenter", cstr);
	gSystemMgr.m_dSpecAAAngle = m_dAngleSpec;
	cstr.Format(L"%.3f", gSystemMgr.m_dSpecAAAngle); gSystemMgr.m_cCaptureConfigIni.SaveConfigIni(L"SfrSetting", L"m_dSpecAAAngle", cstr);
	gSystemMgr.m_dSpecSfr[0] = m_dCenterSfrSpec;
	cstr.Format(L"%.3f", gSystemMgr.m_dSpecSfr[0]); gSystemMgr.m_cCaptureConfigIni.SaveConfigIni(L"SfrSetting", L"m_dSpecSfr[0]", cstr);
	gSystemMgr.m_dSpecSfr[1] = m_dFieldASfrSpec;
	cstr.Format(L"%.3f", gSystemMgr.m_dSpecSfr[1]); gSystemMgr.m_cCaptureConfigIni.SaveConfigIni(L"SfrSetting", L"m_dSpecSfr[1]", cstr);
	gSystemMgr.m_nRoiEnable[0][3] = m_bLeft0;
	cstr.Format(L"%d", gSystemMgr.m_nRoiEnable[0][3]); gSystemMgr.m_cCaptureConfigIni.SaveConfigIni(L"SfrSetting", L"m_nRoiEnable[0][3]", cstr);
	gSystemMgr.m_nRoiEnable[1][3] = m_bLeft1;
	cstr.Format(L"%d", gSystemMgr.m_nRoiEnable[1][3]); gSystemMgr.m_cCaptureConfigIni.SaveConfigIni(L"SfrSetting", L"m_nRoiEnable[1][3]", cstr);
	gSystemMgr.m_nRoiEnable[2][3] = m_bLeft2;
	cstr.Format(L"%d", gSystemMgr.m_nRoiEnable[2][3]); gSystemMgr.m_cCaptureConfigIni.SaveConfigIni(L"SfrSetting", L"m_nRoiEnable[2][3]", cstr);
	gSystemMgr.m_nRoiEnable[3][3] = m_bLeft3;
	cstr.Format(L"%d", gSystemMgr.m_nRoiEnable[3][3]); gSystemMgr.m_cCaptureConfigIni.SaveConfigIni(L"SfrSetting", L"m_nRoiEnable[3][3]", cstr);
	gSystemMgr.m_nRoiEnable[4][3] = m_bLeft4;
	cstr.Format(L"%d", gSystemMgr.m_nRoiEnable[4][3]); gSystemMgr.m_cCaptureConfigIni.SaveConfigIni(L"SfrSetting", L"m_nRoiEnable[4][3]", cstr);
	gSystemMgr.m_nRoiEnable[0][2] = m_bTop0;
	cstr.Format(L"%d", gSystemMgr.m_nRoiEnable[0][2]); gSystemMgr.m_cCaptureConfigIni.SaveConfigIni(L"SfrSetting", L"m_nRoiEnable[0][2]", cstr);
	gSystemMgr.m_nRoiEnable[1][2] = m_bTop1;
	cstr.Format(L"%d", gSystemMgr.m_nRoiEnable[1][2]); gSystemMgr.m_cCaptureConfigIni.SaveConfigIni(L"SfrSetting", L"m_nRoiEnable[1][2]", cstr);
	gSystemMgr.m_nRoiEnable[2][2] = m_bTop2;
	cstr.Format(L"%d", gSystemMgr.m_nRoiEnable[2][2]); gSystemMgr.m_cCaptureConfigIni.SaveConfigIni(L"SfrSetting", L"m_nRoiEnable[2][2]", cstr);
	gSystemMgr.m_nRoiEnable[3][2] = m_bTop3;
	cstr.Format(L"%d", gSystemMgr.m_nRoiEnable[3][2]); gSystemMgr.m_cCaptureConfigIni.SaveConfigIni(L"SfrSetting", L"m_nRoiEnable[3][2]", cstr);
	gSystemMgr.m_nRoiEnable[4][2] = m_bTop4;
	cstr.Format(L"%d", gSystemMgr.m_nRoiEnable[4][2]); gSystemMgr.m_cCaptureConfigIni.SaveConfigIni(L"SfrSetting", L"m_nRoiEnable[4][2]", cstr);
	gSystemMgr.m_nRoiEnable[0][1] = m_bRight0;
	cstr.Format(L"%d", gSystemMgr.m_nRoiEnable[0][1]); gSystemMgr.m_cCaptureConfigIni.SaveConfigIni(L"SfrSetting", L"m_nRoiEnable[0][1]", cstr);
	gSystemMgr.m_nRoiEnable[1][1] = m_bRight1;
	cstr.Format(L"%d", gSystemMgr.m_nRoiEnable[1][1]); gSystemMgr.m_cCaptureConfigIni.SaveConfigIni(L"SfrSetting", L"m_nRoiEnable[1][1]", cstr);
	gSystemMgr.m_nRoiEnable[2][1] = m_bRight2;
	cstr.Format(L"%d", gSystemMgr.m_nRoiEnable[2][1]); gSystemMgr.m_cCaptureConfigIni.SaveConfigIni(L"SfrSetting", L"m_nRoiEnable[2][1]", cstr);
	gSystemMgr.m_nRoiEnable[3][1] = m_bRight3;
	cstr.Format(L"%d", gSystemMgr.m_nRoiEnable[3][1]); gSystemMgr.m_cCaptureConfigIni.SaveConfigIni(L"SfrSetting", L"m_nRoiEnable[3][1]", cstr);
	gSystemMgr.m_nRoiEnable[4][1] = m_bRight4;
	cstr.Format(L"%d", gSystemMgr.m_nRoiEnable[4][1]); gSystemMgr.m_cCaptureConfigIni.SaveConfigIni(L"SfrSetting", L"m_nRoiEnable[4][1]", cstr);
	gSystemMgr.m_nRoiEnable[0][0] = m_bButton0;
	cstr.Format(L"%d", gSystemMgr.m_nRoiEnable[0][0]); gSystemMgr.m_cCaptureConfigIni.SaveConfigIni(L"SfrSetting", L"m_nRoiEnable[0][0]", cstr);
	gSystemMgr.m_nRoiEnable[1][0] = m_bButton1;
	cstr.Format(L"%d", gSystemMgr.m_nRoiEnable[1][0]); gSystemMgr.m_cCaptureConfigIni.SaveConfigIni(L"SfrSetting", L"m_nRoiEnable[1][0]", cstr);
	gSystemMgr.m_nRoiEnable[2][0] = m_bButton2;
	cstr.Format(L"%d", gSystemMgr.m_nRoiEnable[2][0]); gSystemMgr.m_cCaptureConfigIni.SaveConfigIni(L"SfrSetting", L"m_nRoiEnable[2][0]", cstr);
	gSystemMgr.m_nRoiEnable[3][0] = m_bButton3;
	cstr.Format(L"%d", gSystemMgr.m_nRoiEnable[3][0]); gSystemMgr.m_cCaptureConfigIni.SaveConfigIni(L"SfrSetting", L"m_nRoiEnable[3][0]", cstr);
	gSystemMgr.m_nRoiEnable[4][0] = m_bButton4;
	cstr.Format(L"%d", gSystemMgr.m_nRoiEnable[4][0]); gSystemMgr.m_cCaptureConfigIni.SaveConfigIni(L"SfrSetting", L"m_nRoiEnable[4][0]", cstr);
	gSystemMgr.m_nBin[0] = m_nBin0;
	cstr.Format(L"%d", gSystemMgr.m_nBin[0]); gSystemMgr.m_cCaptureConfigIni.SaveConfigIni(L"SfrSetting", L"m_nBin[0]", cstr);
	gSystemMgr.m_nBin[1] = m_nBin1;
	cstr.Format(L"%d", gSystemMgr.m_nBin[1]); gSystemMgr.m_cCaptureConfigIni.SaveConfigIni(L"SfrSetting", L"m_nBin[1]", cstr);
	gSystemMgr.m_nBin[2] = m_nBin2;
	cstr.Format(L"%d", gSystemMgr.m_nBin[2]); gSystemMgr.m_cCaptureConfigIni.SaveConfigIni(L"SfrSetting", L"m_nBin[2]", cstr);
	gSystemMgr.m_nBin[3] = m_nBin3;
	cstr.Format(L"%d", gSystemMgr.m_nBin[3]); gSystemMgr.m_cCaptureConfigIni.SaveConfigIni(L"SfrSetting", L"m_nBin[3]", cstr);
	gSystemMgr.m_nBin[4] = m_nBin4;
	cstr.Format(L"%d", gSystemMgr.m_nBin[4]); gSystemMgr.m_cCaptureConfigIni.SaveConfigIni(L"SfrSetting", L"m_nBin[4]", cstr);
	gSystemMgr.m_nStartX[0] = m_nStartX0;
	cstr.Format(L"%d", gSystemMgr.m_nStartX[0]); gSystemMgr.m_cCaptureConfigIni.SaveConfigIni(L"SfrSetting", L"m_nStartX[0]", cstr);
	gSystemMgr.m_nStartX[1] = m_nStartX1;
	cstr.Format(L"%d", gSystemMgr.m_nStartX[1]); gSystemMgr.m_cCaptureConfigIni.SaveConfigIni(L"SfrSetting", L"m_nStartX[1]", cstr);
	gSystemMgr.m_nStartX[2] = m_nStartX2;
	cstr.Format(L"%d", gSystemMgr.m_nStartX[2]); gSystemMgr.m_cCaptureConfigIni.SaveConfigIni(L"SfrSetting", L"m_nStartX[2]", cstr);
	gSystemMgr.m_nStartX[3] = m_nStartX3;
	cstr.Format(L"%d", gSystemMgr.m_nStartX[3]); gSystemMgr.m_cCaptureConfigIni.SaveConfigIni(L"SfrSetting", L"m_nStartX[3]", cstr);
	gSystemMgr.m_nStartX[4] = m_nStartX4;
	cstr.Format(L"%d", gSystemMgr.m_nStartX[4]); gSystemMgr.m_cCaptureConfigIni.SaveConfigIni(L"SfrSetting", L"m_nStartX[4]", cstr);
	gSystemMgr.m_nStartY[0] = m_nStartY0;
	cstr.Format(L"%d", gSystemMgr.m_nStartY[0]); gSystemMgr.m_cCaptureConfigIni.SaveConfigIni(L"SfrSetting", L"m_nStartY[0]", cstr);
	gSystemMgr.m_nStartY[1] = m_nStartY1;
	cstr.Format(L"%d", gSystemMgr.m_nStartY[1]); gSystemMgr.m_cCaptureConfigIni.SaveConfigIni(L"SfrSetting", L"m_nStartY[1]", cstr);
	gSystemMgr.m_nStartY[2] = m_nStartY2;
	cstr.Format(L"%d", gSystemMgr.m_nStartY[2]); gSystemMgr.m_cCaptureConfigIni.SaveConfigIni(L"SfrSetting", L"m_nStartY[2]", cstr);
	gSystemMgr.m_nStartY[3] = m_nStartY3;
	cstr.Format(L"%d", gSystemMgr.m_nStartY[3]); gSystemMgr.m_cCaptureConfigIni.SaveConfigIni(L"SfrSetting", L"m_nStartY[3]", cstr);
	gSystemMgr.m_nStartY[4] = m_nStartY4;
	cstr.Format(L"%d", gSystemMgr.m_nStartY[4]); gSystemMgr.m_cCaptureConfigIni.SaveConfigIni(L"SfrSetting", L"m_nStartY[4]", cstr);

	gSystemMgr.m_nTargetX = m_nCenterX;
	cstr.Format(L"%d", gSystemMgr.m_nTargetX); gSystemMgr.m_cCaptureConfigIni.SaveConfigIni(L"SfrSetting", L"m_nTargetX", cstr);
	gSystemMgr.m_nTargetY = m_nCenterY;
	cstr.Format(L"%d", gSystemMgr.m_nTargetY); gSystemMgr.m_cCaptureConfigIni.SaveConfigIni(L"SfrSetting", L"m_nTargetY", cstr);

	gSystemMgr.m_bDrawLine = m_bDrawLine;
	cstr.Format(L"%d", gSystemMgr.m_bDrawLine); gSystemMgr.m_cCaptureConfigIni.SaveConfigIni(L"SfrSetting", L"m_bDrawLine", cstr);

	gSystemMgr.m_dSpecSfrUV[0] = m_dCenterSfrSpec2;
	cstr.Format(L"%.3f", gSystemMgr.m_dSpecSfrUV[0]); gSystemMgr.m_cCaptureConfigIni.SaveConfigIni(L"SfrSetting", L"m_dSpecSfrUV[0]", cstr);
	gSystemMgr.m_dSpecSfrUV[1] = m_dFieldASfrSpec2;
	cstr.Format(L"%.3f", gSystemMgr.m_dSpecSfrUV[1]); gSystemMgr.m_cCaptureConfigIni.SaveConfigIni(L"SfrSetting", L"m_dSpecSfrUV[1]", cstr);
}

BOOL CSFRSettingDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	ReadConfigIni();
	m_spinStartX0.SetRange(0, 2000);
	m_spinStartX1.SetRange(0, 2000);
	m_spinStartX2.SetRange(0, 2000);
	m_spinStartX3.SetRange(0, 2000);
	m_spinStartX4.SetRange(0, 2000);
	m_spinStartY0.SetRange(0, 2000);
	m_spinStartY1.SetRange(0, 2000);
	m_spinStartY2.SetRange(0, 2000);
	m_spinStartY3.SetRange(0, 2000);
	m_spinStartY4.SetRange(0, 2000);

	m_comboCount.ResetContent();
	m_comboCount.AddString(L"0");
	m_comboCount.AddString(L"1");
	m_comboCount.AddString(L"2");
	m_comboCount.AddString(L"3");
	m_comboCount.AddString(L"4");
	m_comboCount.SetCurSel(0);

	m_nInitFlag = 1;

	gSystemMgr.m_ptrSFRSettingDlg = this;
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CSFRSettingDlg::OnCancel()
{
	m_nInitFlag = 0;
	gSystemMgr.m_bDisplayFlag = 0;
	gSystemMgr.m_nDisplayCnt = 0;
	CDialogEx::OnCancel();
}


void CSFRSettingDlg::OnBnClickedButtonSave()
{
	SaveEditValueToConfig();
}


void CSFRSettingDlg::OnEnChangeEditStartX0()
{
	if (!m_nInitFlag)return;
	UpdateData(TRUE);

	gSystemMgr.m_nStartX[0] = m_nStartX0;
}


void CSFRSettingDlg::OnEnChangeEditStartX1()
{
	if (!m_nInitFlag)return;
	UpdateData(TRUE);

	gSystemMgr.m_nStartX[1] = m_nStartX1;
}


void CSFRSettingDlg::OnEnChangeEditStartX2()
{
	if (!m_nInitFlag)return;
	UpdateData(TRUE);

	gSystemMgr.m_nStartX[2] = m_nStartX2;
}


void CSFRSettingDlg::OnEnChangeEditStartX3()
{
	if (!m_nInitFlag)return;
	UpdateData(TRUE);

	gSystemMgr.m_nStartX[3] = m_nStartX3;
}


void CSFRSettingDlg::OnEnChangeEditStartX4()
{
	if (!m_nInitFlag)return;
	UpdateData(TRUE);

	gSystemMgr.m_nStartX[4] = m_nStartX4;
}


void CSFRSettingDlg::OnEnChangeEditStartY0()
{
	if (!m_nInitFlag)return;
	UpdateData(TRUE);

	gSystemMgr.m_nStartY[0] = m_nStartY0;
}


void CSFRSettingDlg::OnEnChangeEditStartY1()
{
	if (!m_nInitFlag)return;
	UpdateData(TRUE);

	gSystemMgr.m_nStartY[1] = m_nStartY1;
}


void CSFRSettingDlg::OnEnChangeEditStartY2()
{
	if (!m_nInitFlag)return;
	UpdateData(TRUE);

	gSystemMgr.m_nStartY[2] = m_nStartY2;
}


void CSFRSettingDlg::OnEnChangeEditStartY3()
{
	if (!m_nInitFlag)return;
	UpdateData(TRUE);

	gSystemMgr.m_nStartY[3] = m_nStartY3;
}


void CSFRSettingDlg::OnEnChangeEditStartY4()
{
	if (!m_nInitFlag)return;
	UpdateData(TRUE);

	gSystemMgr.m_nStartY[4] = m_nStartY4;
}


void CSFRSettingDlg::OnCbnSelchangeComboCount()
{
	if (!m_nInitFlag)return;
	gSystemMgr.m_nDisplayCnt= m_comboCount.GetCurSel();
}


void CSFRSettingDlg::OnBnClickedCheckDisplay()
{
	UpdateData(TRUE);
	gSystemMgr.m_bDisplayFlag = m_bDisplay;
}
