// AAControlDlg.cpp: 实现文件
//

#include "pch.h"
#include "ProjectAA.h"
#include "AAControlDlg.h"
#include "afxdialogex.h"


// CAAControlDlg 对话框

IMPLEMENT_DYNAMIC(CAAControlDlg, CDialogEx)

CAAControlDlg::CAAControlDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_AA, pParent)
	, m_dAngleLimitSpec(0)
	, m_nUVTime(0)
	, m_nCapWaitTime(0)
	, m_nPeakDiff(0.0f)
	, m_nPeakSpec(0.0f)
	, m_dPixelSize(0)
	, m_nReturnStep(0)
	, m_nSearchZCnt(0)
	, m_dSearchZSiepDis_1(0)
	, m_dSearchZSpec_1(0)
	, m_dSearchZSiepDis_2(0)
	, m_dSearchZSpec_2(0)
	, m_nAAStepCnt(0)
	, m_dAAStepDis(0)
	, m_dOffsetZ(0)
	, m_bOpenOffset(FALSE)
	, m_nPosTableX0(0)
	, m_nPosTableX1(0)
	, m_nPosTableZ0(0)
	, m_nPosTableZ1(0)
	, m_nPosTableZ2(0)
	, m_nPosX0(0)
	, m_nPosX1(0)
	, m_nPosY0(0)
	, m_nPosY1(0)
	, m_nPosZ0(0)
	, m_nPosZ1(0)
	, m_nPosXt0(0)
	, m_nPosXt1(0)
	, m_nPosYt0(0)
	, m_nPosYt1(0)
	, m_nStepWait(0)
	, m_dCenterPer(0)
	, m_dFieldSfrDiffSpec(0)
	, m_dCurrentLimit(0)
	, m_nDelay(0.0f)
	, m_bManual(FALSE)
	, OpenNGBaojing(FALSE)
	, m_bOffsetXYFlag(FALSE)
	, OffsetX(0)
	, OffsetY(0)
	, UseMirrorFlag(FALSE)
	, OpenDongtaiFlag(FALSE)
	, ChartFlag(FALSE)
	, ChartPos(0)
	, CalibrationLimit(0)
	, AAImgFlag(FALSE)
	, UVImgFlag(FALSE)
	, XFlag(FALSE)
	, YFlag(FALSE)
{

}

CAAControlDlg::~CAAControlDlg()
{
}

void CAAControlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_FS_ANGLELIMIT, m_dAngleLimitSpec);
	DDX_Text(pDX, IDC_EDIT_UV_TIME, m_nUVTime);
	DDX_Text(pDX, IDC_EDIT_CAP_WAIT, m_nCapWaitTime);
	DDX_Text(pDX, IDC_EDIT_PEAK_DIFF, m_nPeakDiff);
	DDX_Text(pDX, IDC_EDIT_PEAK_MIN, m_nPeakSpec);
	DDX_Text(pDX, IDC_EDIT_PIXEL_SIZE, m_dPixelSize);
	DDX_Text(pDX, IDC_EDIT_RETURN_CNT, m_nReturnStep);
	DDX_Text(pDX, IDC_EDIT_SEARCHZ_CNT, m_nSearchZCnt);
	DDX_Text(pDX, IDC_EDIT_SEARCHZ_STEP1, m_dSearchZSiepDis_1);
	DDX_Text(pDX, IDC_EDIT_SEARCHZ_SPEC1, m_dSearchZSpec_1);
	DDX_Text(pDX, IDC_EDIT_SEARCHZ_STEP2, m_dSearchZSiepDis_2);
	DDX_Text(pDX, IDC_EDIT_SEARCHZ_SPEC2, m_dSearchZSpec_2);
	DDX_Text(pDX, IDC_EDIT_AA_CNT, m_nAAStepCnt);
	DDX_Text(pDX, IDC_EDIT_AA_STEP, m_dAAStepDis);
	DDX_Text(pDX, IDC_EDIT_Z_OFFSET, m_dOffsetZ);
	DDX_Check(pDX, IDC_CHECK_OFFSET, m_bOpenOffset);
	DDX_Text(pDX, IDC_EDIT_TABLEX0, m_nPosTableX0);
	DDX_Text(pDX, IDC_EDIT_TABLEX1, m_nPosTableX1);
	DDX_Text(pDX, IDC_EDIT_TABLEZ0, m_nPosTableZ0);
	DDX_Text(pDX, IDC_EDIT_TABLEZ1, m_nPosTableZ1);
	DDX_Text(pDX, IDC_EDIT_TABLEZ2, m_nPosTableZ2);
	DDX_Text(pDX, IDC_EDIT_X0, m_nPosX0);
	DDX_Text(pDX, IDC_EDIT_X1, m_nPosX1);
	DDX_Text(pDX, IDC_EDIT_Y0, m_nPosY0);
	DDX_Text(pDX, IDC_EDIT_Y1, m_nPosY1);
	DDX_Text(pDX, IDC_EDIT_Z0, m_nPosZ0);
	DDX_Text(pDX, IDC_EDIT_Z1, m_nPosZ1);
	DDX_Text(pDX, IDC_EDIT_Xt0, m_nPosXt0);
	DDX_Text(pDX, IDC_EDIT_Xt1, m_nPosXt1);
	DDX_Text(pDX, IDC_EDIT_Yt0, m_nPosYt0);
	DDX_Text(pDX, IDC_EDIT_Yt1, m_nPosYt1);
	DDX_Text(pDX, IDC_EDIT_STEP_WAIT, m_nStepWait);
	DDX_Text(pDX, IDC_EDIT_CNETER_PER, m_dCenterPer);
	DDX_Text(pDX, IDC_EDIT_FIELD_SFRDIFF, m_dFieldSfrDiffSpec);
	DDX_Text(pDX, IDC_EDIT_STEP_WAIT2, m_dCurrentLimit);
	DDX_Text(pDX, IDC_EDIT_AA_DELAY, m_nDelay);
	DDX_Check(pDX, IDC_CHECK_MANUAL, m_bManual);
	DDX_Check(pDX, IDC_CHECK_MANUAL2, OpenNGBaojing);
	DDX_Check(pDX, IDC_CHECK_OFFSET2, m_bOffsetXYFlag);
	DDX_Control(pDX, IDC_COMBO2, OffsetID);
	DDX_Text(pDX, IDC_EDIT_X_OFFSET, OffsetX);
	DDX_Text(pDX, IDC_EDIT_Y_OFFSET, OffsetY);
	DDX_Check(pDX, IDC_CHECK_MANUAL3, UseMirrorFlag);
	DDX_Check(pDX, IDC_CHECK_MANUAL4, OpenDongtaiFlag);
	DDX_Check(pDX, IDC_CHECK_OFFSET3, ChartFlag);
	DDX_Text(pDX, IDC_EDIT_X_OFFSET2, ChartPos);
	DDX_Text(pDX, IDC_EDIT_AA_DELAY2, CalibrationLimit);
	DDX_Check(pDX, IDC_CHECK_AAIMG, AAImgFlag);
	DDX_Check(pDX, IDC_CHECK_UVIMG, UVImgFlag);
	DDX_Check(pDX, IDC_CHECK3, XFlag);
	DDX_Check(pDX, IDC_CHECK4, YFlag);
}


BEGIN_MESSAGE_MAP(CAAControlDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CAAControlDlg::OnBnClickedButtonSave)
	ON_BN_CLICKED(IDC_BUTTON1, &CAAControlDlg::OnBnClickedButton1)
	ON_CBN_SELCHANGE(IDC_COMBO2, &CAAControlDlg::OnCbnSelchangeCombo2)
	ON_BN_CLICKED(IDC_BUTTON2, &CAAControlDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CAAControlDlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// CAAControlDlg 消息处理程序


BOOL CAAControlDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	OffsetID.ResetContent();
	OffsetID.AddString(L"0");
	OffsetID.AddString(L"1");
	OffsetID.AddString(L"2");
	OffsetID.AddString(L"3");
	OffsetID.AddString(L"4");
	OffsetID.AddString(L"5");
	OffsetID.AddString(L"6");
	OffsetID.AddString(L"7");
	OffsetID.AddString(L"8");
	OffsetID.AddString(L"9");
	OffsetID.SetCurSel(0);

	ReadConfigIni();


	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

void CAAControlDlg::ReadConfigIni()
{
	m_dAngleLimitSpec = gSystemMgr.m_dAngleLimitSpec;
	m_nUVTime = gSystemMgr.m_nUVTime;
	m_nCapWaitTime = gSystemMgr.m_nCaptureWaitTime;
	m_nPeakDiff = gSystemMgr.m_nPeakDiff;
	m_nPeakSpec = gSystemMgr.m_nPeakMin;
	m_dPixelSize = gSystemMgr.m_dPixelSize;
	m_nReturnStep = gSystemMgr.m_nReturnStepCnt;
	m_nSearchZCnt = gSystemMgr.m_nSearchZStepMaxCnt;
	m_dSearchZSiepDis_1 = gSystemMgr.m_dSearchZStep_1;
	m_dSearchZSpec_1 = gSystemMgr.m_dSearchZSpec_1;
	m_dSearchZSiepDis_2 = gSystemMgr.m_dSearchZStep_2;
	m_dSearchZSpec_2 = gSystemMgr.m_dSearchZSpec_2;
	m_nAAStepCnt = gSystemMgr.m_nAAStepMaxCnt;
	m_dAAStepDis = gSystemMgr.m_dAAStep;
	m_dOffsetZ = gSystemMgr.m_dOffsetZ;
	m_bOpenOffset = gSystemMgr.m_bOffsetFlag;
	m_nPosTableX0 = gSystemMgr.m_nPositionTableX[0];
	m_nPosTableX1 = gSystemMgr.m_nPositionTableX[1];
	m_nPosTableZ0 = gSystemMgr.m_nPositionTableZ[0];
	m_nPosTableZ1 = gSystemMgr.m_nPositionTableZ[1];
	m_nPosTableZ2 = gSystemMgr.m_nPositionTableZ[2];
	m_nPosX0 = gSystemMgr.m_nPositionX[0];
	m_nPosX1 = gSystemMgr.m_nPositionX[1];
	m_nPosY0 = gSystemMgr.m_nPositionY[0];
	m_nPosY1 = gSystemMgr.m_nPositionY[1];
	m_nPosZ0 = gSystemMgr.m_nPositionZ[0];
	m_nPosZ1 = gSystemMgr.m_nPositionZ[1];
	m_nPosXt0 = gSystemMgr.m_nPositionXt[0];
	m_nPosXt1 = gSystemMgr.m_nPositionXt[1];
	m_nPosYt0 = gSystemMgr.m_nPositionYt[0];
	m_nPosYt1 = gSystemMgr.m_nPositionYt[1];

	m_nStepWait = gSystemMgr.m_nStepWait;

	m_dCenterPer = gSystemMgr.m_dCenterPer;
	m_dFieldSfrDiffSpec = gSystemMgr.m_dFieldSfrDiffSpec;
	m_dCurrentLimit = gSystemMgr.m_dCurrentLimit;

	m_nDelay = gSystemMgr.m_nDelay;

	m_bManual = gSystemMgr.m_bManualFlag;
	OpenNGBaojing = gSystemMgr.OpenNGBaojing;

	OffsetX = gSystemMgr.m_dOffsetX[OffsetID.GetCurSel()];
	OffsetY = gSystemMgr.m_dOffsetY[OffsetID.GetCurSel()];
	m_bOffsetXYFlag = gSystemMgr.m_bOpenOffsetXY;

	UseMirrorFlag = gSystemMgr.UseMirrorFlag;
	OpenDongtaiFlag = gSystemMgr.OpenDongtaiFlag;

	ChartFlag = gSystemMgr.ChartOpenFlag;
	ChartPos = gSystemMgr.ChartPos;

	CalibrationLimit = gSystemMgr.CalibrationLimit;
	AAImgFlag = gSystemMgr.AAImgFlag;
	UVImgFlag = gSystemMgr.UVImgFlag;

	XFlag = gSystemMgr.XFlag;
	YFlag = gSystemMgr.YFlag;

	UpdateData(FALSE);
}

void CAAControlDlg::SaveValueToConfig()
{
	UpdateData(TRUE);
	CString cstr;

	gSystemMgr.XFlag = XFlag;
	cstr.Format(L"%d", gSystemMgr.XFlag);
	gSystemMgr.m_cAAConfigIni.SaveConfigIni(L"AA", L"XFlag", cstr);
	gSystemMgr.YFlag = YFlag;
	cstr.Format(L"%d", gSystemMgr.YFlag);
	gSystemMgr.m_cAAConfigIni.SaveConfigIni(L"AA", L"YFlag", cstr);

	gSystemMgr.AAImgFlag = AAImgFlag;
	cstr.Format(L"%d", gSystemMgr.AAImgFlag);
	gSystemMgr.m_cAAConfigIni.SaveConfigIni(L"AA", L"AAImgFlag", cstr);
	gSystemMgr.UVImgFlag = UVImgFlag;
	cstr.Format(L"%d", gSystemMgr.UVImgFlag);
	gSystemMgr.m_cAAConfigIni.SaveConfigIni(L"AA", L"UVImgFlag", cstr);

	gSystemMgr.CalibrationLimit = CalibrationLimit;
	cstr.Format(L"%.3f", gSystemMgr.CalibrationLimit);
	gSystemMgr.m_cAAConfigIni.SaveConfigIni(L"AA", L"CalibrationLimit", cstr);
	gSystemMgr.m_dAngleLimitSpec = m_dAngleLimitSpec;
	cstr.Format(L"%.3f", gSystemMgr.m_dAngleLimitSpec);
	gSystemMgr.m_cAAConfigIni.SaveConfigIni(L"AA", L"m_dAngleLimitSpec", cstr);
	gSystemMgr.m_nUVTime = m_nUVTime;
	cstr.Format(L"%d", gSystemMgr.m_nUVTime);
	gSystemMgr.m_cAAConfigIni.SaveConfigIni(L"AA", L"m_nUVTime", cstr);
	gSystemMgr.m_nCaptureWaitTime = m_nCapWaitTime;
	cstr.Format(L"%d", gSystemMgr.m_nCaptureWaitTime);
	gSystemMgr.m_cAAConfigIni.SaveConfigIni(L"AA", L"m_nCaptureWaitTime", cstr);
	gSystemMgr.m_nPeakDiff = m_nPeakDiff;
	cstr.Format(L"%.3f", gSystemMgr.m_nPeakDiff);
	gSystemMgr.m_cAAConfigIni.SaveConfigIni(L"AA", L"m_nPeakDiff", cstr);
	gSystemMgr.m_nPeakMin = m_nPeakSpec;
	cstr.Format(L"%.3f", gSystemMgr.m_nPeakMin);
	gSystemMgr.m_cAAConfigIni.SaveConfigIni(L"AA", L"m_nPeakMin", cstr);
	gSystemMgr.m_dPixelSize = m_dPixelSize;
	cstr.Format(L"%.4f", gSystemMgr.m_dPixelSize);
	gSystemMgr.m_cAAConfigIni.SaveConfigIni(L"AA", L"m_dPixelSize", cstr);
	gSystemMgr.m_nReturnStepCnt = m_nReturnStep;
	cstr.Format(L"%d", gSystemMgr.m_nReturnStepCnt);
	gSystemMgr.m_cAAConfigIni.SaveConfigIni(L"AA", L"m_nReturnStepCnt", cstr);
	gSystemMgr.m_nSearchZStepMaxCnt = m_nSearchZCnt;
	cstr.Format(L"%d", gSystemMgr.m_nSearchZStepMaxCnt);
	gSystemMgr.m_cAAConfigIni.SaveConfigIni(L"AA", L"m_nSearchZStepMaxCnt", cstr);
	gSystemMgr.m_dSearchZStep_1 = m_dSearchZSiepDis_1;
	cstr.Format(L"%.4f", gSystemMgr.m_dSearchZStep_1);
	gSystemMgr.m_cAAConfigIni.SaveConfigIni(L"AA", L"m_dSearchZStep_1", cstr);
	gSystemMgr.m_dSearchZSpec_1 = m_dSearchZSpec_1;
	cstr.Format(L"%.4f", gSystemMgr.m_dSearchZSpec_1);
	gSystemMgr.m_cAAConfigIni.SaveConfigIni(L"AA", L"m_dSearchZSpec_1", cstr);
	gSystemMgr.m_dSearchZStep_2 = m_dSearchZSiepDis_2;
	cstr.Format(L"%.4f", gSystemMgr.m_dSearchZStep_2);
	gSystemMgr.m_cAAConfigIni.SaveConfigIni(L"AA", L"m_dSearchZStep_2", cstr);
	gSystemMgr.m_dSearchZSpec_2 = m_dSearchZSpec_2;
	cstr.Format(L"%.4f", gSystemMgr.m_dSearchZSpec_2);
	gSystemMgr.m_cAAConfigIni.SaveConfigIni(L"AA", L"m_dSearchZSpec_2", cstr);
	gSystemMgr.m_nAAStepMaxCnt = m_nAAStepCnt;
	cstr.Format(L"%d", gSystemMgr.m_nAAStepMaxCnt);
	gSystemMgr.m_cAAConfigIni.SaveConfigIni(L"AA", L"m_nAAStepMaxCnt", cstr);
	gSystemMgr.m_dAAStep = m_dAAStepDis;
	cstr.Format(L"%.4f", gSystemMgr.m_dAAStep);
	gSystemMgr.m_cAAConfigIni.SaveConfigIni(L"AA", L"m_dAAStep", cstr);
	gSystemMgr.m_dOffsetZ = m_dOffsetZ;
	cstr.Format(L"%.4f", gSystemMgr.m_dOffsetZ);
	gSystemMgr.m_cAAConfigIni.SaveConfigIni(L"AA", L"m_dOffsetZ", cstr);
	gSystemMgr.m_bOffsetFlag = m_bOpenOffset;
	cstr.Format(L"%d", gSystemMgr.m_bOffsetFlag);
	gSystemMgr.m_cAAConfigIni.SaveConfigIni(L"AA", L"m_bOffsetFlag", cstr);
	gSystemMgr.m_nPositionTableX[0] = m_nPosTableX0;
	cstr.Format(L"%d", gSystemMgr.m_nPositionTableX[0]);
	gSystemMgr.m_cAAConfigIni.SaveConfigIni(L"AA", L"m_nPositionTableX[0]", cstr);
	gSystemMgr.m_nPositionTableX[1] = m_nPosTableX1;
	cstr.Format(L"%d", gSystemMgr.m_nPositionTableX[1]);
	gSystemMgr.m_cAAConfigIni.SaveConfigIni(L"AA", L"m_nPositionTableX[1]", cstr);
	gSystemMgr.m_nPositionTableZ[0] = m_nPosTableZ0;
	cstr.Format(L"%d", gSystemMgr.m_nPositionTableZ[0]);
	gSystemMgr.m_cAAConfigIni.SaveConfigIni(L"AA", L"m_nPositionTableZ[0]", cstr);
	gSystemMgr.m_nPositionTableZ[1] = m_nPosTableZ1;
	cstr.Format(L"%d", gSystemMgr.m_nPositionTableZ[1]);
	gSystemMgr.m_cAAConfigIni.SaveConfigIni(L"AA", L"m_nPositionTableZ[1]", cstr);
	gSystemMgr.m_nPositionTableZ[2] = m_nPosTableZ2;
	cstr.Format(L"%d", gSystemMgr.m_nPositionTableZ[2]);
	gSystemMgr.m_cAAConfigIni.SaveConfigIni(L"AA", L"m_nPositionTableZ[2]", cstr);
	gSystemMgr.m_nPositionX[0] = m_nPosX0;
	cstr.Format(L"%d", gSystemMgr.m_nPositionX[0]);
	gSystemMgr.m_cAAConfigIni.SaveConfigIni(L"AA", L"m_nPositionX[0]", cstr);
	gSystemMgr.m_nPositionX[1] = m_nPosX1;
	cstr.Format(L"%d", gSystemMgr.m_nPositionX[1]);
	gSystemMgr.m_cAAConfigIni.SaveConfigIni(L"AA", L"m_nPositionX[1]", cstr);
	gSystemMgr.m_nPositionY[0] = m_nPosY0;
	cstr.Format(L"%d", gSystemMgr.m_nPositionY[0]);
	gSystemMgr.m_cAAConfigIni.SaveConfigIni(L"AA", L"m_nPositionY[0]", cstr);
	gSystemMgr.m_nPositionY[1] = m_nPosY1;
	cstr.Format(L"%d", gSystemMgr.m_nPositionY[1]);
	gSystemMgr.m_cAAConfigIni.SaveConfigIni(L"AA", L"m_nPositionY[1]", cstr);
	gSystemMgr.m_nPositionZ[0] = m_nPosZ0;
	cstr.Format(L"%d", gSystemMgr.m_nPositionZ[0]);
	gSystemMgr.m_cAAConfigIni.SaveConfigIni(L"AA", L"m_nPositionZ[0]", cstr);
	gSystemMgr.m_nPositionZ[1] = m_nPosZ1;
	cstr.Format(L"%d", gSystemMgr.m_nPositionZ[1]);
	gSystemMgr.m_cAAConfigIni.SaveConfigIni(L"AA", L"m_nPositionZ[1]", cstr);
	gSystemMgr.m_nPositionXt[0] = m_nPosXt0;
	cstr.Format(L"%d", gSystemMgr.m_nPositionXt[0]);
	gSystemMgr.m_cAAConfigIni.SaveConfigIni(L"AA", L"m_nPositionXt[0]", cstr);
	gSystemMgr.m_nPositionXt[1] = m_nPosXt1;
	cstr.Format(L"%d", gSystemMgr.m_nPositionXt[1]);
	gSystemMgr.m_cAAConfigIni.SaveConfigIni(L"AA", L"m_nPositionXt[1]", cstr);
	gSystemMgr.m_nPositionYt[0] = m_nPosYt0;
	cstr.Format(L"%d", gSystemMgr.m_nPositionYt[0]);
	gSystemMgr.m_cAAConfigIni.SaveConfigIni(L"AA", L"m_nPositionYt[0]", cstr);
	gSystemMgr.m_nPositionYt[1] = m_nPosYt1;
	cstr.Format(L"%d", gSystemMgr.m_nPositionYt[1]);
	gSystemMgr.m_cAAConfigIni.SaveConfigIni(L"AA", L"m_nPositionYt[1]", cstr);

	gSystemMgr.m_nStepWait = m_nStepWait;
	cstr.Format(L"%d", gSystemMgr.m_nStepWait);
	gSystemMgr.m_cAAConfigIni.SaveConfigIni(L"AA", L"m_nStepWait", cstr);

	gSystemMgr.m_dCenterPer = m_dCenterPer;
	cstr.Format(L"%.4f", gSystemMgr.m_dCenterPer);
	gSystemMgr.m_cAAConfigIni.SaveConfigIni(L"AA", L"m_dCenterPer", cstr);
	gSystemMgr.m_dFieldSfrDiffSpec = m_dFieldSfrDiffSpec;
	cstr.Format(L"%.4f", gSystemMgr.m_dFieldSfrDiffSpec);
	gSystemMgr.m_cAAConfigIni.SaveConfigIni(L"AA", L"m_dFieldSfrDiffSpec", cstr);

	gSystemMgr.m_dCurrentLimit = m_dCurrentLimit;
	cstr.Format(L"%.3f", gSystemMgr.m_dCurrentLimit);
	gSystemMgr.m_cAAConfigIni.SaveConfigIni(L"AA", L"m_dCurrentLimit", cstr);

	gSystemMgr.m_nDelay = m_nDelay;
	cstr.Format(L"%.3f", gSystemMgr.m_nDelay);
	gSystemMgr.m_cAAConfigIni.SaveConfigIni(L"AA", L"m_nDelay", cstr);

	gSystemMgr.m_bManualFlag = m_bManual;
	cstr.Format(L"%d", gSystemMgr.m_bManualFlag);
	gSystemMgr.m_cAAConfigIni.SaveConfigIni(L"AA", L"m_bManualFlag", cstr);

	gSystemMgr.OpenNGBaojing = OpenNGBaojing;
	cstr.Format(L"%d", gSystemMgr.OpenNGBaojing);
	gSystemMgr.m_cAAConfigIni.SaveConfigIni(L"AA", L"OpenNGBaojing", cstr);

	gSystemMgr.UseMirrorFlag = UseMirrorFlag;
	cstr.Format(L"%d", gSystemMgr.UseMirrorFlag);
	gSystemMgr.m_cAAConfigIni.SaveConfigIni(L"AA", L"UseMirrorFlag", cstr);

	OpenDongtaiFlag = gSystemMgr.OpenDongtaiFlag;
	cstr.Format(L"%d", gSystemMgr.OpenDongtaiFlag);
	gSystemMgr.m_cAAConfigIni.SaveConfigIni(L"AA", L"OpenDongtaiFlag", cstr);

	gSystemMgr.ChartOpenFlag = ChartFlag;
	cstr.Format(L"%d", gSystemMgr.ChartOpenFlag);
	gSystemMgr.m_cAAConfigIni.SaveConfigIni(L"AA", L"ChartOpenFlag", cstr);
	gSystemMgr.ChartPos = ChartPos;
	cstr.Format(L"%d", gSystemMgr.ChartPos);
	gSystemMgr.m_cAAConfigIni.SaveConfigIni(L"AA", L"ChartPos", cstr);

	gSystemMgr.m_bOpenOffsetXY = m_bOffsetXYFlag;
	cstr.Format(L"%d", m_bOffsetXYFlag);
	gSystemMgr.m_cAAConfigIni.SaveConfigIni(L"AA", L"m_bOpenOffsetXY", cstr);

	gSystemLog.DisplayLogAndSave(L"AA保存数据完成", LV_EVENT);
}

void CAAControlDlg::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类

	CDialogEx::OnCancel();
}


void CAAControlDlg::OnBnClickedButtonSave()
{
	SaveValueToConfig();
}


void CAAControlDlg::OnBnClickedButton1()
{
	UpdateData(true);
	CString cstr, cstrName;
	gSystemMgr.m_dOffsetX[OffsetID.GetCurSel()] = OffsetX;
	gSystemMgr.m_dOffsetY[OffsetID.GetCurSel()] = OffsetY;
	gSystemMgr.m_bOpenOffsetXY = m_bOffsetXYFlag;

	cstr.Format(L"%d", m_bOffsetXYFlag);
	gSystemMgr.m_cAAConfigIni.SaveConfigIni(L"AA", L"m_bOpenOffsetXY", cstr);

	cstrName.Format(L"m_dOffsetX[%d]", OffsetID.GetCurSel());
	cstr.Format(L"%.2f", OffsetX);
	gSystemMgr.m_cAAConfigIni.SaveConfigIni(L"AA", cstrName, cstr);

	cstrName.Format(L"m_dOffsetY[%d]", OffsetID.GetCurSel());
	cstr.Format(L"%.2f", OffsetY);
	gSystemMgr.m_cAAConfigIni.SaveConfigIni(L"AA", cstrName, cstr);
}


void CAAControlDlg::OnCbnSelchangeCombo2()
{
	OffsetX = gSystemMgr.m_dOffsetX[OffsetID.GetCurSel()];
	OffsetY = gSystemMgr.m_dOffsetY[OffsetID.GetCurSel()];
	UpdateData(FALSE);
}


void CAAControlDlg::OnBnClickedButton2()
{
	//设定夹取位置
	if (IDYES == AfxMessageBox(L"确定 设定当前位置为夹取镜头位置 吗？", MB_YESNO))
	{
		m_nPosTableZ0 = gSystemMgr.m_vCMotor[M_TABLE_Z].m_nCurPositon;
		m_nPosTableX0 = gSystemMgr.m_vCMotor[M_TABLE_X].m_nCurPositon;
		m_nPosX0 = gSystemMgr.m_vCMotor[MOTOR_X].m_nCurPositon;
		m_nPosY0 = gSystemMgr.m_vCMotor[MOTOR_Y].m_nCurPositon;
		m_nPosZ0 = gSystemMgr.m_vCMotor[MOTOR_Z].m_nCurPositon;
		m_nPosXt0 = gSystemMgr.m_vCMotor[MOTOR_Xt].m_nCurPositon;
		m_nPosYt0 = gSystemMgr.m_vCMotor[MOTOR_Yt].m_nCurPositon;

		UpdateData(FALSE);
	}
}


void CAAControlDlg::OnBnClickedButton3()
{
	//设定AA位置
	if (IDYES == AfxMessageBox(L"确定 设定当前位置为AA位置 吗？", MB_YESNO))
	{
		m_nPosTableZ1 = gSystemMgr.m_vCMotor[M_TABLE_Z].m_nCurPositon;
		m_nPosTableX1 = gSystemMgr.m_vCMotor[M_TABLE_X].m_nCurPositon;
		m_nPosX1 = gSystemMgr.m_vCMotor[MOTOR_X].m_nCurPositon;
		m_nPosY1 = gSystemMgr.m_vCMotor[MOTOR_Y].m_nCurPositon;
		m_nPosZ1 = gSystemMgr.m_vCMotor[MOTOR_Z].m_nCurPositon;
		m_nPosXt1 = gSystemMgr.m_vCMotor[MOTOR_Xt].m_nCurPositon;
		m_nPosYt1 = gSystemMgr.m_vCMotor[MOTOR_Yt].m_nCurPositon;

		UpdateData(FALSE);
	}
}
