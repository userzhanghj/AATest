// ImageCaptureDlg.cpp: 实现文件
//

#include "pch.h"
#include "ProjectAA.h"
#include "ImageCaptureDlg.h"
#include "afxdialogex.h"


// CImageCaptureDlg 对话框

IMPLEMENT_DYNAMIC(CImageCaptureDlg, CDialogEx)

CImageCaptureDlg::CImageCaptureDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_CAPTURE, pParent)
	, m_bWriteiic(FALSE)
	, m_bMirrorX(FALSE)
	, m_bMirrorY(FALSE)
	, m_nCTSId(0)
	, m_nGpioFlag(FALSE)
	, ChangeXY(FALSE)
	, CameraDsW(0)
	, CameraDsH(0)
{

}

CImageCaptureDlg::~CImageCaptureDlg()
{
}

void CImageCaptureDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_IMAGE_SOURCE, m_comboImageSource);
	DDX_Control(pDX, IDC_COMBO_TEST_MODE, m_comboTestMode);
	DDX_Control(pDX, IDC_COMBO_CAPTURE_MODE, m_comboCaptureMode);
	DDX_Control(pDX, IDC_COMBO_CHANGE_MODE, m_comboChangeMode);
	DDX_Check(pDX, IDC_CHECK_WRITE_IIC, m_bWriteiic);
	DDX_Check(pDX, IDC_CHECK_MIRROR_X, m_bMirrorX);
	DDX_Check(pDX, IDC_CHECK_MIRROR_Y, m_bMirrorY);
	DDX_Text(pDX, IDC_EDIT_CTS_ID, m_nCTSId);
	DDX_Check(pDX, IDC_CHECK_GPIO, m_nGpioFlag);
	DDX_Control(pDX, IDC_COMBO_GPIO, m_comboGpioNo);
	DDX_Check(pDX, IDC_CHECK_CHANGEXY, ChangeXY);
	DDX_Text(pDX, IDC_EDIT1, CameraDsW);
	DDX_Text(pDX, IDC_EDIT3, CameraDsH);
}


BEGIN_MESSAGE_MAP(CImageCaptureDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CImageCaptureDlg::OnBnClickedButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_WRITEIIC, &CImageCaptureDlg::OnBnClickedButtonWriteiic)
	ON_BN_CLICKED(IDC_BUTTON_RESETCTS, &CImageCaptureDlg::OnBnClickedButtonResetcts)
END_MESSAGE_MAP()


// CImageCaptureDlg 消息处理程序


BOOL CImageCaptureDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	ReadConfigIni();

	m_comboImageSource.ResetContent();
	m_comboImageSource.AddString(L"0: 本地文件");
	m_comboImageSource.AddString(L"1: CTS采集卡");
	m_comboImageSource.AddString(L"2: 软龙格采集卡");
	m_comboImageSource.AddString(L"3: CameraDS采集");
	m_comboImageSource.SetCurSel(gSystemMgr.m_nImageSource);

	m_comboTestMode.ResetContent();
	m_comboTestMode.AddString(L"0: 原图显示");
	m_comboTestMode.AddString(L"1: SFR测试");
	//m_comboTestMode.AddString(L"2: ");
	//m_comboTestMode.AddString(L"3: ");
	m_comboTestMode.SetCurSel(gSystemMgr.m_nTestMode);

	m_comboCaptureMode.ResetContent();
	m_comboCaptureMode.AddString(L"0: 单张");
	m_comboCaptureMode.AddString(L"1: 连续");
	m_comboCaptureMode.SetCurSel(gSystemMgr.m_nCaptureMode);

	m_comboChangeMode.ResetContent();
	m_comboChangeMode.AddString(L"0: RGB原图");
	m_comboChangeMode.AddString(L"1: UYVY");
	m_comboChangeMode.AddString(L"2: VYUY");
	m_comboChangeMode.AddString(L"3: YVYU");
	m_comboChangeMode.AddString(L"4: YUYV");
	m_comboChangeMode.AddString(L"5: BGGR");
	m_comboChangeMode.AddString(L"6: RGGB");
	m_comboChangeMode.AddString(L"7: GBRG");
	m_comboChangeMode.AddString(L"8: GRBG");
	m_comboChangeMode.SetCurSel(gSystemMgr.m_nImageChangeMode);

	m_comboGpioNo.ResetContent();
	m_comboGpioNo.AddString(L"0");
	m_comboGpioNo.AddString(L"1");
	m_comboGpioNo.AddString(L"2");
	m_comboGpioNo.AddString(L"3");
	m_comboGpioNo.SetCurSel(gSystemMgr.m_nGpioNo);

	return TRUE;  
}


void CImageCaptureDlg::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类

	CDialogEx::OnCancel();
}

void CImageCaptureDlg::ReadConfigIni()
{
	(gSystemMgr.m_bWriteIIC == 1) ? m_bWriteiic = true : m_bWriteiic = false;
	(gSystemMgr.m_bMirrorX == 1) ? m_bMirrorX = true : m_bMirrorX = false;
	(gSystemMgr.m_bMirrorY == 1) ? m_bMirrorY = true : m_bMirrorY = false;
	m_nCTSId = gSystemMgr.m_nCtsId;
	(gSystemMgr.m_bGpioFlag == 1) ? m_nGpioFlag = true : m_nGpioFlag = false;
	ChangeXY = gSystemMgr.ChangeXY;

	CameraDsW = gSystemMgr.CameraDsW;
	CameraDsH = gSystemMgr.CameraDsH;

	UpdateData(FALSE);
}

void CImageCaptureDlg::SaveValueToConfig()
{
	UpdateData(TRUE);

	(m_bWriteiic == TRUE) ? gSystemMgr.m_bWriteIIC = 1 : gSystemMgr.m_bWriteIIC = 0;
	(m_bMirrorX == TRUE) ? gSystemMgr.m_bMirrorX = 1 : gSystemMgr.m_bMirrorX = 0;
	(m_bMirrorY == TRUE) ? gSystemMgr.m_bMirrorY = 1 : gSystemMgr.m_bMirrorY = 0;
	gSystemMgr.m_nImageSource = m_comboImageSource.GetCurSel();
	gSystemMgr.m_nTestMode = m_comboTestMode.GetCurSel();
	gSystemMgr.m_nCaptureMode = m_comboCaptureMode.GetCurSel();
	gSystemMgr.m_nImageChangeMode = m_comboChangeMode.GetCurSel();
	gSystemMgr.m_nCtsId = m_nCTSId;
	(m_nGpioFlag == TRUE) ? gSystemMgr.m_bGpioFlag = 1 : gSystemMgr.m_bGpioFlag = 0;
	gSystemMgr.m_nGpioNo = m_comboGpioNo.GetCurSel();
	gSystemMgr.ChangeXY = ChangeXY;

	gSystemMgr.CameraDsW = CameraDsW;
	gSystemMgr.CameraDsH = CameraDsH;

	CString cstr;
	cstr.Format(L"%d", gSystemMgr.CameraDsW);
	gSystemMgr.m_cCaptureConfigIni.SaveConfigIni(L"CaptureConfig", L"CameraDsW", cstr);
	cstr.Format(L"%d", gSystemMgr.CameraDsH);
	gSystemMgr.m_cCaptureConfigIni.SaveConfigIni(L"CaptureConfig", L"CameraDsH", cstr);

	cstr.Format(L"%d", gSystemMgr.ChangeXY);
	gSystemMgr.m_cCaptureConfigIni.SaveConfigIni(L"CaptureConfig", L"ChangeXY", cstr);
	cstr.Format(L"%d", gSystemMgr.m_bWriteIIC);
	gSystemMgr.m_cCaptureConfigIni.SaveConfigIni(L"CaptureConfig", L"m_bWriteIIC", cstr);
	cstr.Format(L"%d", gSystemMgr.m_bMirrorX);
	gSystemMgr.m_cCaptureConfigIni.SaveConfigIni(L"CaptureConfig", L"m_bMirrorX", cstr);
	cstr.Format(L"%d", gSystemMgr.m_bMirrorY);
	gSystemMgr.m_cCaptureConfigIni.SaveConfigIni(L"CaptureConfig", L"m_bMirrorY", cstr);

	cstr.Format(L"%d", gSystemMgr.m_nImageSource);
	gSystemMgr.m_cCaptureConfigIni.SaveConfigIni(L"CaptureConfig", L"m_nImageSource", cstr);
	cstr.Format(L"%d", gSystemMgr.m_nTestMode);
	gSystemMgr.m_cCaptureConfigIni.SaveConfigIni(L"CaptureConfig", L"m_nTestMode", cstr);
	cstr.Format(L"%d", gSystemMgr.m_nCaptureMode);
	gSystemMgr.m_cCaptureConfigIni.SaveConfigIni(L"CaptureConfig", L"m_nCaptureMode", cstr);
	cstr.Format(L"%d", gSystemMgr.m_nImageChangeMode);
	gSystemMgr.m_cCaptureConfigIni.SaveConfigIni(L"CaptureConfig", L"m_nImageChangeMode", cstr);

	cstr.Format(L"%d", gSystemMgr.m_nCtsId);
	gSystemMgr.m_cCaptureConfigIni.SaveConfigIni(L"CaptureConfig", L"m_nCtsId", cstr);

	cstr.Format(L"%d", gSystemMgr.m_bGpioFlag);
	gSystemMgr.m_cCaptureConfigIni.SaveConfigIni(L"CaptureConfig", L"m_bGpioFlag", cstr);
	cstr.Format(L"%d", gSystemMgr.m_nGpioNo);
	gSystemMgr.m_cCaptureConfigIni.SaveConfigIni(L"CaptureConfig", L"m_nGpioNo", cstr);

	switch (gSystemMgr.m_nImageSource) {
	case IMG_DEV_FILE:
		gSystemMgr.imgCap = (ImgCap *)&gSystemMgr.imgFile;
		//SendMessage(HWND_STATUS, SB_SETTEXT, 2, (LPARAM)"Image Files");
		break;
	case IMG_DEV_CTS:
		if (gSystemMgr.m_bCTSInitFlag == 0) {
			Cam_Init();
			gSystemMgr.m_bCTSInitFlag = 1;
		}
		gSystemMgr.imgCap = (ImgCap *)&gSystemMgr.imgCTS;
		//SendMessage(HWND_STATUS, SB_SETTEXT, 2, (LPARAM)"CTS Cam");
		break;
	case IMG_RO_LONGO:
		gSystemMgr.imgCap = (ImgCap *)&gSystemMgr.imgRLG;
		//SendMessage(HWND_STATUS, SB_SETTEXT, 2, (LPARAM)"RLG Cam");
		break;
	case IMG_CameraDS:
		gSystemMgr.imgCap = (ImgCap *)&gSystemMgr.imgCDS;
		break;
	}

	gSystemLog.DisplayLogAndSave(L"Capture保存数据完成", LV_EVENT);
}

void CImageCaptureDlg::OnBnClickedButtonSave()
{
	SaveValueToConfig();
}



void CImageCaptureDlg::OnBnClickedButtonWriteiic()
{
	switch (gSystemMgr.m_nImageSource)
	{
	case IMG_DEV_CTS:
		gSystemMgr.imgCTS.write_iic();
		break;
	case IMG_RO_LONGO:
		gSystemMgr.imgRLG.write_iic();
		break;
	}
}


void CImageCaptureDlg::OnBnClickedButtonResetcts()
{
	Cam_Init();
	gSystemMgr.imgCTS.initdone = 0;
}
