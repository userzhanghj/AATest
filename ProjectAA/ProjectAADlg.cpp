
// ProjectAADlg.cpp: 实现文件
//

#include "pch.h"
#include "Test.h"
#include "framework.h"
#include "ProjectAA.h"
#include "ProjectAADlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//ImgCap *imgCap;
//ImgFile imgFile; 
//CTS CTSCam;

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum
	{
		IDD = IDD_ABOUTBOX
	};
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CProjectAADlg 对话框



CProjectAADlg::CProjectAADlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PROJECTAA_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CProjectAADlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_START, m_butStart);
	DDX_Control(pDX, IDC_BUTTON_STOP, m_butStop);
	DDX_Control(pDX, IDC_BUTTON_SAVE, m_butSave);
	DDX_Control(pDX, IDC_STATIC_20, m_static_20);
	DDX_Control(pDX, IDC_STATIC_42, m_static_42);
	DDX_Control(pDX, IDC_STATIC_61, Static1);
	DDX_Control(pDX, IDC_BUTTON_HOME_40, Button1);
	DDX_Control(pDX, IDC_CHECK2, Button3);
	DDX_Control(pDX, IDC_EDIT1, m_editStep);
}

BEGIN_MESSAGE_MAP(CProjectAADlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_32771, &CProjectAADlg::OnOpenLogDlg)
	ON_COMMAND(ID_32773, &CProjectAADlg::OnOpenMotorDlg)
	ON_BN_CLICKED(IDC_BUTTON1, &CProjectAADlg::OnBnClickedButton1)
	ON_COMMAND(ID_32772, &CProjectAADlg::OnOpenProjectDlg)
	ON_BN_CLICKED(IDC_BUTTON_START, &CProjectAADlg::OnBnClickedButtonStart)
	ON_BN_CLICKED(IDC_BUTTON_STOP, &CProjectAADlg::OnBnClickedButtonStop)
	ON_COMMAND(ID_32776, &CProjectAADlg::OnOpenCaptureDlg)
	ON_COMMAND(ID_32777, &CProjectAADlg::OnOpenSFRDlg)
	ON_WM_SIZE()
	ON_MESSAGE(WM_SEND_SOCKET_SERVER_MSG_TO_MAIN_UI, &CProjectAADlg::OnReceiveServerMsg)
	ON_COMMAND(ID_32778, &CProjectAADlg::OnOpenIODlg)
	ON_BN_CLICKED(IDC_CHECK2, &CProjectAADlg::OnBnClickedCheck2)
	ON_WM_CTLCOLOR()
	ON_COMMAND(ID_32775, &CProjectAADlg::OnOpenAADlg)
	//	ON_WM_DRAWITEM()
	ON_BN_CLICKED(IDC_BUTTON_HOME_40, &CProjectAADlg::OnBnClickedButtonHome40)
	ON_COMMAND(ID_32782, &CProjectAADlg::OnOpenManualControl)
	ON_COMMAND(ID_32781, &CProjectAADlg::OnOpenComDlg)
	ON_COMMAND(ID_32780, &CProjectAADlg::OnOpenLogin)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CProjectAADlg::OnBnClickedButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_CLAER2, &CProjectAADlg::OnBnClickedButtonClaer2)
	ON_BN_CLICKED(IDC_BUTTON2, &CProjectAADlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON_HOME_41, &CProjectAADlg::OnBnClickedButtonHome41)
	ON_BN_CLICKED(IDC_BUTTON3, &CProjectAADlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CProjectAADlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON7, &CProjectAADlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON9, &CProjectAADlg::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON5, &CProjectAADlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CProjectAADlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON23, &CProjectAADlg::OnBnClickedButton23)
	ON_BN_CLICKED(IDC_BUTTON24, &CProjectAADlg::OnBnClickedButton24)
	ON_COMMAND(ID_32783, &CProjectAADlg::OnOpenLightTestDlg)
END_MESSAGE_MAP()


// CProjectAADlg 消息处理程序

BOOL CProjectAADlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	unique_mutex = CreateMutex(NULL, FALSE, L"ProjectAA");
	DWORD errCode = GetLastError();
	if (errCode == ERROR_ALREADY_EXISTS) {
		Sleep(500);
		CloseHandle(unique_mutex);
		MessageBox(L"AA软件已经被打开!", L"Warning", 0);
		::TerminateProcess(::GetCurrentProcess(), NULL);//终止原先程序
	}

	// 设置字体参数
	gSystemMgr.m_editFont.CreateFont(40, 0, 4, 0, FW_NORMAL, FALSE, FALSE, 0,
		ANSI_CHARSET,
		OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_SWISS,
		_T("Arial"));
	m_static_20.SetFont(&gSystemMgr.m_editFont);
	m_static_20.SetWindowTextW(L"等待");
	m_static_42.SetFont(&gSystemMgr.m_editFont);
	m_static_42.SetWindowTextW(L"...");
	Static1.SetFont(&gSystemMgr.m_editFont);
	Button1.SetFont(&gSystemMgr.m_editFont);
	Button3.SetFont(&gSystemMgr.m_editFont);

	//轴的比率尺
	gSystemMgr.m_vCMotor[MOTOR_X].PositionRatio = 8000;//3		-1000 * 8 = 1r			1r = 1mm
	gSystemMgr.m_vCMotor[MOTOR_Y].PositionRatio = 8000;//3		-1000 * 8 = 1r			1r = 1mm
	gSystemMgr.m_vCMotor[MOTOR_Z].PositionRatio = 4000.0;//3		-1000 * 8 = 1r		1r = 2mm
	gSystemMgr.m_vCMotor[MOTOR_Xt].PositionRatio = 14035.1;//1r = 1mm  R = 100mm		//1000*8=1r	//16617.3	//14035.1
	gSystemMgr.m_vCMotor[MOTOR_Yt].PositionRatio = 4210.5;//1r = 1mm  R = 30mm			//1000*8=1r	//3864		//4210.5

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	gSystemMgr.GeneralSettingIniInit();//读取型号配置

	m_menu.LoadMenuW(IDR_MENU1);
	this->SetMenu(&m_menu);

	//SetUiHandle();

	gSystemMgr.CaptureConfigIniInit();//采图配置
	gSystemMgr.AAConfigIniInit();//AA运动配置
	gSystemMgr.RS232ConfigIniInit();//RS232通讯配置
	gSystemMgr.LoginConfigIniInit();//Login信息
	gSystemMgr.StateConfigIniInit();//统计信息
	gSystemMgr.ReadErrorListIni();//报错信息
	gSystemMgr.LightConfigIniInit();//亮度测试

	gSystemMgr.m_ptrMainUI = this;

	if (m_cLogDlg == nullptr)
	{
		m_cLogDlg = new CLogDlg;
		m_cLogDlg->Create(IDD_DIALOG_LOG, this);
	}
	m_cLogDlg->ShowWindow(SW_HIDE);

	bool bInit = gSystemMgr.DMC3800Init();//轴卡初始化
	if (bInit)
	{
		gSystemMgr.MotorReadConfig();

		Sleep(100);
		gSystemMgr.m_cIo.StartGetIoInputThread();

		gSystemMgr.StartGetMotorIoThread();//状态？
		gSystemMgr.StartGetMotorEncoderThread();//位置？
		gSystemMgr.m_cIo.SetOutputIo(18, ON);
		gSystemMgr.m_cIo.SetOutputIo(20, ON);
	}

	switch (gSystemMgr.m_nImageSource)
	{
	case IMG_DEV_FILE:
		gSystemMgr.imgCap = (ImgCap *)&gSystemMgr.imgFile;
		//SendMessage(HWND_STATUS, SB_SETTEXT, 2, (LPARAM)"Image Files");
		break;
	case IMG_DEV_CTS:
		Cam_Init();
		gSystemMgr.m_bCTSInitFlag = 1;
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
	gSystemMgr.StartCaptureThread();
	gSystemMgr.StartImageTestThread();

	GetClientRect(&m_rcUiRect);

	if (!gSystemMgr.changeImg.init_lib())
	{
		//logdlg.log("convert init error");
		gSystemLog.DisplayLogAndSave(L"convert init error", LV_ERROR);
	}

	gSystemMgr.StartAutoAAThread();
	gSystemMgr.StartLightControlThread(); 
	gSystemMgr.StartScanButtonValueThread();
	gSystemMgr.StartOtherControlThread();
	gSystemMgr.StartRS232LinkThread();
	gSystemMgr.StartPowerLinkThread();

	//画按钮
	CRect rect;
	m_butStart.GetWindowRect(rect);
	long width = rect.right - rect.left;
	long height = rect.bottom - rect.top;
	HICON hicon_btn = (HICON)LoadImage(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICON_START), IMAGE_ICON, width - 30, height - 10, LR_DEFAULTCOLOR | LR_CREATEDIBSECTION);
	m_butStart.SetIcon(hicon_btn);
	m_butStop.GetWindowRect(rect);
	width = rect.right - rect.left;
	height = rect.bottom - rect.top;
	hicon_btn = (HICON)LoadImage(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICON_STOP), IMAGE_ICON, width - 30, height - 10, LR_DEFAULTCOLOR | LR_CREATEDIBSECTION);
	m_butStop.SetIcon(hicon_btn);
	m_butSave.GetWindowRect(rect);
	width = rect.right - rect.left;
	height = rect.bottom - rect.top;
	hicon_btn = (HICON)LoadImage(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICON_SAVE), IMAGE_ICON, width - 30, height - 10, LR_DEFAULTCOLOR | LR_CREATEDIBSECTION);
	m_butSave.SetIcon(hicon_btn);

	CRect rcScreen;
	SystemParametersInfo(SPI_GETWORKAREA, 0, &rcScreen, 0);
	gSystemMgr.m_nCrtScreenWidth = rcScreen.Width() / 1;
	gSystemMgr.m_nCrtScreenHeight = rcScreen.Height() / 1;
	::SetWindowPos(m_hWnd, HWND_TOP, gSystemMgr.m_nCrtScreenWidth * 0, gSystemMgr.m_nCrtScreenHeight * 0, gSystemMgr.m_nCrtScreenWidth, gSystemMgr.m_nCrtScreenHeight, SWP_SHOWWINDOW);

	m_editStep.SetWindowTextW(L"0.01");

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CProjectAADlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CProjectAADlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CRect rect;
		CPaintDC dc(this);
		GetClientRect(rect);
		dc.FillSolidRect(rect, RGB(169, 179, 195));//设置为绿色背景  

		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CProjectAADlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CProjectAADlg::SetUiHandle()
{
	m_menu.EnableMenuItem(ID_32781, MF_DISABLED);
	m_menu.EnableMenuItem(ID_32774, MF_DISABLED);
	m_menu.EnableMenuItem(ID_32783, MF_DISABLED);
	m_menu.EnableMenuItem(ID_32776, MF_DISABLED);
	m_menu.EnableMenuItem(ID_32777, MF_DISABLED);
	m_menu.EnableMenuItem(ID_32775, MF_DISABLED);

}


void CProjectAADlg::OnOpenLogDlg()
{
	if (m_cLogDlg != nullptr)
	{
		m_cLogDlg->ShowWindow(SW_SHOW);
	}
	//else
	//{
	//	m_cLogDlg = new CLogDlg;
	//	m_cLogDlg->Create(IDD_DIALOG_LOG, this);
	//}
}


void CProjectAADlg::OnOpenMotorDlg()
{
	if (m_cMotorDlg != nullptr)
	{
		delete m_cMotorDlg;
		m_cMotorDlg = nullptr;
	}
	if (m_cMotorDlg == nullptr)
	{
		m_cMotorDlg = new CMotorDlg;
		m_cMotorDlg->Create(IDD_DIALOG_MOTOR, this);
	}
	m_cMotorDlg->ShowWindow(SW_SHOW);
}

double test[3][3] =
{
{1    ,1    ,1},
{0    ,1    ,0},
{0    ,1    ,1},

};

void CProjectAADlg::OnBnClickedButton1()
{
	gSystemLog.DisplayLogAndSave(L"Test", LV_ERROR);

	//CvMat* points_mat = cvCreateMat(3, 3, CV_32FC1);
	//for (int i = 0; i < 3; i++) {
	//	points_mat->data.fl[i * 3 + 0] = test[i][0];
	//	points_mat->data.fl[i * 3 + 1] = test[i][1];
	//	points_mat->data.fl[i * 3 + 2] = test[i][2];
	//}
	//float plane12[4] = { 0 };
	//cvFitPlane(points_mat, plane12);
	//CString cstr;
	//for (int i = 0; i < 4; i++)
	//{
	//	cstr.Format(L"plane%d = %lf\n", i, plane12[i]);
	//	gSystemLog.DisplayLogAndSave(cstr.GetBuffer(), LV_ERROR);
	//}

	gSystemMgr.CalculateTiltXY_Plane();
	gSystemMgr.CalculateTiltXY(gSystemMgr.m_dAAStep);

	//Point3D temp[3];
	//for (int i = 0; i < 3; i++)
	//{
	//	temp[i].x = test[i][0];
	//	temp[i].y = test[i][1];
	//	temp[i].z = test[i][2];
	//}
	//vector<Point3D>v_Point;
	//double M2[3];
	//for (int i = 0; i < 3; i++)
	//{
	//	v_Point.push_back(temp[i]);
	//}
	//Least_squares(v_Point, M2);
	//CString cstr;
	//for (int i = 0; i < 3; i++)
	//{
	//	cstr.Format(L"M%d = %lf\n", i, M2[i]);
	//	gSystemLog.DisplayLogAndSave(cstr.GetBuffer(), LV_ERROR);
	//}
}


void CProjectAADlg::OnOpenProjectDlg()
{
	if (m_cChangeProjectDlg != nullptr)
	{
		delete m_cChangeProjectDlg;
		m_cChangeProjectDlg = nullptr;
	}
	if (m_cChangeProjectDlg == nullptr)
	{
		m_cChangeProjectDlg = new CChangeProject;
		m_cChangeProjectDlg->Create(IDD_DIALOG_CHANGE_PROJECT, this);
	}
	m_cChangeProjectDlg->ShowWindow(SW_SHOW);
}


void CProjectAADlg::OnBnClickedButtonStart()
{
	gSystemMgr.m_bStopCapture = 0;
	CWnd* pBtn = nullptr;
	pBtn = (CWnd*)GetDlgItem(IDC_BUTTON_START);
	pBtn->EnableWindow(FALSE);
}


void CProjectAADlg::OnBnClickedButtonStop()
{
	gSystemMgr.m_bStopCapture = 1;
	gSystemMgr.imgCap->m_bInitFlag = FALSE;
	CWnd* pBtn = nullptr;
	pBtn = (CWnd*)GetDlgItem(IDC_BUTTON_START);
	pBtn->EnableWindow(TRUE);
}


void CProjectAADlg::OnOpenCaptureDlg()
{
	if (m_cCaptureDlg != nullptr)
	{
		delete m_cCaptureDlg;
		m_cCaptureDlg = nullptr;
	}
	if (m_cCaptureDlg == nullptr)
	{
		m_cCaptureDlg = new CImageCaptureDlg;
		m_cCaptureDlg->Create(IDD_DIALOG_CAPTURE, this);
	}
	m_cCaptureDlg->ShowWindow(SW_SHOW);
}


void CProjectAADlg::OnOpenSFRDlg()
{
	if (m_cSfrSettingDlg != nullptr)
	{
		delete m_cSfrSettingDlg;
		m_cSfrSettingDlg = nullptr;
	}
	if (m_cSfrSettingDlg == nullptr)
	{
		m_cSfrSettingDlg = new CSFRSettingDlg;
		m_cSfrSettingDlg->Create(IDD_DIALOG_SFR, this);
	}
	m_cSfrSettingDlg->ShowWindow(SW_SHOW);
}

void CProjectAADlg::Repaint(CWnd * pWnd, int last_Width, int now_Width, int last_Height, int now_Height, int cnt)
{
	if (pWnd)
	{
		CRect rect;
		CRect rect2;
		pWnd->GetWindowRect(&rect2);
		rect = OriRect[cnt];
		int n = 62;
		int m = 8;
		//rect2.top = rect2.top - n;
		//rect2.bottom = rect2.bottom - n;
		ScreenToClient(&rect2);

		double proportion_x = now_Width / (double)last_Width;
		double proportion_y = now_Height / (double)last_Height;

		rect.left = (long)(rect.left*proportion_x + 0.5 - m * proportion_x);
		rect.right = (long)(rect.left + RectW[cnt] * proportion_x + 0.5);
		rect.top = (long)(rect.top *proportion_y + 0.5 - n * proportion_y);
		rect.bottom = (long)(rect.top + RectH[cnt] * proportion_y + 0.5);
		pWnd->MoveWindow(&rect);
	}

}

void CProjectAADlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	if (nType == SIZE_RESTORED || nType == SIZE_MAXIMIZED)//窗体大小发生变动。处理程序
	{
		float fsp[2];
		POINT Newp; //获取现在对话框的大小
		CRect recta;
		GetClientRect(&recta); //取客户区大小   
		Newp.x = recta.right - recta.left;
		Newp.y = recta.bottom - recta.top;
		fsp[0] = (float)Newp.x / Old.x;
		fsp[1] = (float)Newp.y / Old.y;
		CRect Rect;
		int woc;
		CPoint OldTLPoint, TLPoint; //左上角
		CPoint OldBRPoint, BRPoint; //右下角
		HWND hwndChild = ::GetWindow(m_hWnd, GW_CHILD); //列出所有控件   
		while (hwndChild)
		{
			woc = ::GetDlgCtrlID(hwndChild);//取得ID
			GetDlgItem(woc)->GetWindowRect(Rect);
			ScreenToClient(Rect);
			OldTLPoint = Rect.TopLeft();
			TLPoint.x = long(OldTLPoint.x*fsp[0]);
			TLPoint.y = long(OldTLPoint.y*fsp[1]);
			OldBRPoint = Rect.BottomRight();
			BRPoint.x = long(OldBRPoint.x *fsp[0]);
			BRPoint.y = long(OldBRPoint.y *fsp[1]); //高度不可读的控件（如:combBox),不要改变此值.
			Rect.SetRect(TLPoint, BRPoint);
			GetDlgItem(woc)->MoveWindow(Rect, TRUE);
			hwndChild = ::GetWindow(hwndChild, GW_HWNDNEXT);
		}
		Old = Newp;
	}
	Invalidate();//更新窗口

}


void CProjectAADlg::OnOpenIODlg()
{
	if (m_cIODlg != nullptr)
	{
		delete m_cIODlg;
		m_cIODlg = nullptr;
	}
	if (m_cIODlg == nullptr)
	{
		m_cIODlg = new CIOControlDlg;
		m_cIODlg->Create(IDD_DIALOG1_IO, this);
	}
	m_cIODlg->ShowWindow(SW_SHOW);
}

void CProjectAADlg::OnCancel()
{
	gSystemMgr.m_nExitFlag = 1;

	gSystemMgr.m_bStopCapture = 1;
	gSystemMgr.imgCap->m_bInitFlag = FALSE;
	Sleep(200);

	//还要加停止所有轴，锁紧刹车

	KillTimer(TIMER_ID_IO_CONTROL_STATUS);
	dmc_emg_stop(gSystemMgr.m_nCard);

	dmc_board_close();
	delete m_cAADlg;
	delete m_cMotorDlg;
	delete m_cLogDlg;
	delete m_cChangeProjectDlg;
	delete m_cCaptureDlg;
	delete m_cSfrSettingDlg;
	delete m_cIODlg;
	delete m_cManualDlg;
	delete m_cRS232Dlg;
	delete m_cLoginDlg;

	gSystemMgr.imgFile.release();
	gSystemMgr.imgCTS.release();
	gSystemMgr.imgRLG.release();
	gSystemMgr.imgCDS.release();

	//HANDLE hself = GetCurrentProcess();
	//TerminateProcess(hself, 0); 
	CDialogEx::OnCancel();
}

LRESULT CProjectAADlg::OnReceiveServerMsg(WPARAM wParam, LPARAM lParam)
{
	CString cstrp = (BSTR)wParam;
	SysFreeString((BSTR)wParam);

	gSystemLog.DisplayLogAndSave(cstrp.GetBuffer(), LV_EVENT);

	std::vector<wstring> vResultItem = _utils::SplitString(cstrp.GetBuffer(), L";");

	//gSystemLog.DisplayLogAndSave(cstrp.GetBuffer(), LV_EVENT);

	//在此处添加对接收数据的分析

	return LRESULT();
}


void CProjectAADlg::OnBnClickedCheck2()
{
	CString cstr;
	CButton* pCheckBox = (CButton*)GetDlgItem(IDC_CHECK2);
	int nFlag = pCheckBox->GetCheck();
	if (nFlag == BST_CHECKED)
	{
		gSystemMgr.m_bAutoAAFlag = 1;
		cstr.Append(L"开启AA自动");
		gSystemLog.DisplayLogAndSave(cstr.GetBuffer(), LV_EVENT);
		GetDlgItem(IDC_CHECK2)->SetWindowTextW(L"AA自动开启");
	}
	if (nFlag == BST_UNCHECKED)
	{
		gSystemMgr.m_bAutoAAFlag = 0;
		cstr.Append(L"关闭AA自动");
		gSystemLog.DisplayLogAndSave(cstr.GetBuffer(), LV_EVENT);
		GetDlgItem(IDC_CHECK2)->SetWindowTextW(L"AA自动关闭");
	}
}


HBRUSH CProjectAADlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr1 = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	DeleteObject(hbr);

	UINT id = pWnd->GetDlgCtrlID();
	CString Cstr;
	if (id == IDC_CHECK2)
	{
		if (gSystemMgr.m_bAutoAAFlag)
		{
			hbr = CreateSolidBrush(RGB(0, 255, 0));
			pDC->SetTextColor(RGB(0, 255, 0));
		}
		else
		{
			hbr = CreateSolidBrush(RGB(255, 0, 0));
			pDC->SetTextColor(RGB(255, 0, 0));
		}
		pDC->SetBkMode(TRANSPARENT);
	}
	else if (id == IDC_STATIC_1 || id == IDC_STATIC_2 || id == IDC_STATIC_50 || id == IDC_STATIC_60 || id == IDC_STATIC_69 || id == IDC_STATIC_72
		|| id == IDC_STATIC_74 || id == IDC_STATIC_76 || id == IDC_STATIC_92 || id == IDC_STATIC_93)
	{
		hbr = CreateSolidBrush(RGB(169, 179, 195));
		pDC->SetBkMode(TRANSPARENT);
	}
	else if (id == IDC_STATIC_20)
	{
		GetDlgItem(id)->GetWindowTextW(Cstr);
		if (Cstr == L"Testing")
		{
			hbr = CreateSolidBrush(RGB(222, 233, 20));
		}
		else if (Cstr == L"Pass")
		{
			hbr = CreateSolidBrush(RGB(0, 255, 0));
		}
		else if (Cstr == L"Fail")
		{
			hbr = CreateSolidBrush(RGB(255, 0, 0));
		}
		else
		{
			hbr = CreateSolidBrush(RGB(70, 111, 166));
		}
		pDC->SetBkMode(TRANSPARENT);
	}
	else if (id == IDC_STATIC_42)
	{
		GetDlgItem(id)->GetWindowTextW(Cstr);
		if (Cstr == L"...")
		{
			hbr = CreateSolidBrush(RGB(157, 187, 210));
		}
		else
		{
			hbr = CreateSolidBrush(RGB(255, 0, 0));
		}
		pDC->SetBkMode(TRANSPARENT);
	}
	else if (id == IDC_STATIC_22 || id == IDC_STATIC_25 || id == IDC_STATIC_28 || id == IDC_STATIC_31 || id == IDC_STATIC_34
		|| id == IDC_STATIC_37 || id == IDC_STATIC_40)
	{
		GetDlgItem(id)->GetWindowTextW(Cstr);
		if (Cstr == L"OK")
		{
			hbr = CreateSolidBrush(RGB(0, 255, 0));
		}
		else if (Cstr == L"NG")
		{
			hbr = CreateSolidBrush(RGB(255, 0, 0));
		}
		else
		{
			hbr = CreateSolidBrush(RGB(222, 233, 20));
		}
		pDC->SetBkMode(TRANSPARENT);
	}
	else if (id == IDC_STATIC_45)
	{
		if (gSystemMgr.m_nPassRfidFlag)
		{
			hbr = CreateSolidBrush(RGB(255, 0, 0));
		}
		else
		{
			hbr = CreateSolidBrush(RGB(0, 255, 0));
		}
		pDC->SetBkMode(TRANSPARENT);
	}
	else if (id == IDC_STATIC_44)
	{
		if (gSystemMgr.Com2ConnectFlag)
		{
			hbr = CreateSolidBrush(RGB(0, 255, 0));
		}
		else
		{
			hbr = CreateSolidBrush(RGB(255, 0, 0));
		}
		pDC->SetBkMode(TRANSPARENT);
	}
	else if (id == IDC_STATIC_47)
	{
		if (gSystemMgr.m_bHomeFlag)
		{
			hbr = CreateSolidBrush(RGB(0, 255, 0));
		}
		else
		{
			hbr = CreateSolidBrush(RGB(255, 0, 0));
		}
		pDC->SetBkMode(TRANSPARENT);
	}
	else if (id == IDC_STATIC_48)
	{
		if (!gSystemMgr.m_bMotorErrorFlag)
		{
			hbr = CreateSolidBrush(RGB(0, 255, 0));
		}
		else
		{
			hbr = CreateSolidBrush(RGB(255, 0, 0));
		}
		pDC->SetBkMode(TRANSPARENT);
	}
	else if (id == IDC_STATIC_49)
	{
		if (!gSystemMgr.m_bEmergencyStopFlag)
		{
			hbr = CreateSolidBrush(RGB(0, 255, 0));
		}
		else
		{
			hbr = CreateSolidBrush(RGB(255, 0, 0));
		}
		pDC->SetBkMode(TRANSPARENT);
	}
	else if (id == IDC_STATIC_94)
	{
		if (gSystemMgr.m_nPowerLinked == TRUE)
		{
			hbr = CreateSolidBrush(RGB(0, 255, 0));
		}
		else
		{
			hbr = CreateSolidBrush(RGB(255, 0, 0));
		}
		pDC->SetBkMode(TRANSPARENT);
	}
	else if (id == IDC_STATIC_84)
		{
		if (gSystemMgr.SfrAvgValue[0] > gSystemMgr.m_dSpecSfr[0]/*gSystemMgr.SfrResult[0][0] == TRUE*/)
		{
			hbr = CreateSolidBrush(RGB(0, 255, 0));
		}
		else
		{
			hbr = CreateSolidBrush(RGB(255, 0, 0));
		}
		pDC->SetBkMode(TRANSPARENT);
	}
	else if (id == IDC_STATIC_86)
		{
		if (gSystemMgr.SfrAvgValue[1] > gSystemMgr.m_dSpecSfr[1]/*gSystemMgr.SfrResult[1][0] == TRUE*/)
		{
			hbr = CreateSolidBrush(RGB(0, 255, 0));
		}
		else
		{
			hbr = CreateSolidBrush(RGB(255, 0, 0));
		}
		pDC->SetBkMode(TRANSPARENT);
	}
	else if (id == IDC_STATIC_96)
		{
		if (gSystemMgr.SfrAvgValue[2] > gSystemMgr.m_dSpecSfr[1]/*gSystemMgr.SfrResult[2][0] == TRUE*/)
		{
			hbr = CreateSolidBrush(RGB(0, 255, 0));
		}
		else
		{
			hbr = CreateSolidBrush(RGB(255, 0, 0));
		}
		pDC->SetBkMode(TRANSPARENT);
	}
	else if (id == IDC_STATIC_99)
		{
		if (gSystemMgr.SfrAvgValue[3] > gSystemMgr.m_dSpecSfr[1]/*gSystemMgr.SfrResult[3][0] == TRUE*/)
		{
			hbr = CreateSolidBrush(RGB(0, 255, 0));
		}
		else
		{
			hbr = CreateSolidBrush(RGB(255, 0, 0));
		}
		pDC->SetBkMode(TRANSPARENT);
	}
	else if (id == IDC_STATIC_101)
		{
		if (gSystemMgr.SfrAvgValue[4] > gSystemMgr.m_dSpecSfr[1]/*gSystemMgr.SfrResult[4][0] == TRUE*/)
		{
			hbr = CreateSolidBrush(RGB(0, 255, 0));
		}
		else
		{
			hbr = CreateSolidBrush(RGB(255, 0, 0));
		}
		pDC->SetBkMode(TRANSPARENT);
	}
	else if (id == IDC_STATIC_78 || id == IDC_STATIC_80)
		{
		if (gSystemMgr.CenterTestResult == TRUE)
		{
			hbr = CreateSolidBrush(RGB(0, 255, 0));
		}
		else
		{
			hbr = CreateSolidBrush(RGB(255, 0, 0));
		}
		pDC->SetBkMode(TRANSPARENT);
	}
	else if (id == IDC_STATIC_82 || id == IDC_STATIC_63)
		{
		if (gSystemMgr.TiltTestResult == TRUE)
		{
			hbr = CreateSolidBrush(RGB(0, 255, 0));
		}
		else
		{
			hbr = CreateSolidBrush(RGB(255, 0, 0));
		}
		pDC->SetBkMode(TRANSPARENT);
	}
	else
	{
		hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	}
	hbr1 = hbr;
	return hbr1;
}

void CProjectAADlg::OnOpenAADlg()
{
	if (m_cAADlg != nullptr)
	{
		delete m_cAADlg;
		m_cAADlg = nullptr;
	}
	if (m_cAADlg == nullptr)
	{
		m_cAADlg = new CAAControlDlg;
		m_cAADlg->Create(IDD_DIALOG_AA, this);
	}
	m_cAADlg->ShowWindow(SW_SHOW);
}

void CProjectAADlg::OnBnClickedButtonHome40()
{
	gSystemMgr.m_nButtonValue = 10;
}


void CProjectAADlg::OnOpenManualControl()
{
	if (m_cManualDlg != nullptr)
	{
		delete m_cManualDlg;
		m_cManualDlg = nullptr;
	}
	if (m_cManualDlg == nullptr)
	{
		m_cManualDlg = new CManualControlDlg;
		m_cManualDlg->Create(IDD_DIALOG_CONTROL, this);
	}
	m_cManualDlg->ShowWindow(SW_SHOW);
}


void CProjectAADlg::OnOpenComDlg()
{
	if (m_cRS232Dlg != nullptr)
	{
		delete m_cRS232Dlg;
		m_cRS232Dlg = nullptr;
	}
	if (m_cRS232Dlg == nullptr)
	{
		m_cRS232Dlg = new CRS232SetDlg;
		m_cRS232Dlg->Create(IDD_DIALOG_COM, this);
	}
	m_cRS232Dlg->ShowWindow(SW_SHOW);
}


void CProjectAADlg::OnOpenLogin()
{
	if (m_cLoginDlg != nullptr)
	{
		m_cLoginDlg->ShowWindow(SW_SHOW);
	}
	if (m_cLoginDlg == nullptr)
	{
		m_cLoginDlg = new CLoginDlg;
		m_cLoginDlg->Create(IDD_DIALOG_LOGIN, this);
	}
	m_cLoginDlg->ShowWindow(SW_SHOW);
}


void CProjectAADlg::OnBnClickedButtonSave()
{
	gSystemMgr.SaveTestReport2(gSystemMgr.imgCap->bBmpTestBuf, gSystemMgr.imgCap->iBmpW, gSystemMgr.imgCap->iBmpH, 0);
}



void CProjectAADlg::OnBnClickedButtonClaer2()
{
	if (m_cCountDlg != nullptr)
	{
		delete m_cCountDlg;
		m_cCountDlg = nullptr;
	}
	if (m_cCountDlg == nullptr)
	{
		m_cCountDlg = new CCountDlg;
		m_cCountDlg->Create(IDD_DIALOG_COUNT, this);
	}
	m_cCountDlg->ShowWindow(SW_SHOW);
	//if (IDYES == AfxMessageBox(L"确定清空 AA 站统计数据吗？", MB_YESNO))
	//{
	//	CString cstr;
	//	cstr.Format(L"AA旧数据[%s]: %d,%d,%d,%d,%d", gSystemMgr.AATime, gSystemMgr.m_nAAAll, gSystemMgr.m_nAAOK, gSystemMgr.m_nAANG1, gSystemMgr.m_nAANG2, gSystemMgr.m_nAANG3);
	//	gSystemMgr.m_nAAAll = 0;
	//	gSystemMgr.m_nAAOK = 0;
	//	gSystemMgr.m_nAANG1 = 0;
	//	gSystemMgr.m_nAANG2 = 0;
	//	gSystemMgr.m_nAANG3 = 0;
	//	gSystemLog.DisplayLogAndSave(L"AA 站统计数据清除成功。", LV_ERROR);
	//}
}



void CProjectAADlg::OnBnClickedButton2()
{
	gSystemMgr.RestartAA = 1;
}


void CProjectAADlg::OnBnClickedButtonHome41()
{
	gSystemMgr.imgCTS.write_iic_center();
	gSystemLog.DisplayLogAndSave(L"写入 iic 完成", LV_EVENT);
}


BOOL CProjectAADlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_SPACE) return TRUE; //如果是空格消息，返回；
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE) return TRUE; //如果是Esc消息，返回；
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN) return TRUE;
	if (pMsg->message == WM_KEYDOWN) return TRUE;//屏蔽所有键盘按键消息

	return CDialogEx::PreTranslateMessage(pMsg);
}


void CProjectAADlg::OnBnClickedButton3()
{
	gSystemMgr.m_nButtonValue = 27;
}


void CProjectAADlg::OnBnClickedButton4()
{
	if (gSystemMgr.m_nPassRfidFlag) {
		if (IDYES == AfxMessageBox(L"确定 开启RFID 吗？", MB_YESNO | MB_ICONWARNING))
		{
			gSystemMgr.m_nPassRfidFlag = 0;
		}
	}
	else {
		if (IDYES == AfxMessageBox(L"确定 屏蔽RFID 吗？", MB_YESNO | MB_ICONWARNING))
		{
			gSystemMgr.m_nPassRfidFlag = 1;
		}
	}
}


void CProjectAADlg::OnBnClickedButton7()
{
	CString cstr;
	m_editStep.GetWindowTextW(cstr);
	if(_ttof(cstr) < 0)
		m_editStep.SetWindowTextW(L"0.0");
	if (_ttof(cstr) > 0.05)
		m_editStep.SetWindowTextW(L"0.05");
	m_editStep.GetWindowTextW(cstr);
	gSystemMgr.m_vCMotor[MOTOR_X].m_sAxisSetting.m_dTargetPos = _ttof(cstr) * gSystemMgr.m_vCMotor[MOTOR_X].PositionRatio;
	gSystemMgr.m_vCMotor[MOTOR_X].MotorMoveStep();
}


void CProjectAADlg::OnBnClickedButton9()
{
	CString cstr;
	m_editStep.GetWindowTextW(cstr);
	if (_ttof(cstr) < 0)
		m_editStep.SetWindowTextW(L"0.0");
	if (_ttof(cstr) > 0.05)
		m_editStep.SetWindowTextW(L"0.05");
	m_editStep.GetWindowTextW(cstr);
	gSystemMgr.m_vCMotor[MOTOR_X].m_sAxisSetting.m_dTargetPos = -_ttof(cstr) * gSystemMgr.m_vCMotor[MOTOR_X].PositionRatio;
	gSystemMgr.m_vCMotor[MOTOR_X].MotorMoveStep();
}


void CProjectAADlg::OnBnClickedButton5()
{
	CString cstr;
	m_editStep.GetWindowTextW(cstr);
	if (_ttof(cstr) < 0)
		m_editStep.SetWindowTextW(L"0.0");
	if (_ttof(cstr) > 0.05)
		m_editStep.SetWindowTextW(L"0.05");
	m_editStep.GetWindowTextW(cstr);
	gSystemMgr.m_vCMotor[MOTOR_Y].m_sAxisSetting.m_dTargetPos = _ttof(cstr) * gSystemMgr.m_vCMotor[MOTOR_Y].PositionRatio;
	gSystemMgr.m_vCMotor[MOTOR_Y].MotorMoveStep();
}


void CProjectAADlg::OnBnClickedButton6()
{
	CString cstr;
	m_editStep.GetWindowTextW(cstr);
	if (_ttof(cstr) < 0)
		m_editStep.SetWindowTextW(L"0.0");
	if (_ttof(cstr) > 0.05)
		m_editStep.SetWindowTextW(L"0.05");
	m_editStep.GetWindowTextW(cstr);
	gSystemMgr.m_vCMotor[MOTOR_Y].m_sAxisSetting.m_dTargetPos = -_ttof(cstr) * gSystemMgr.m_vCMotor[MOTOR_Y].PositionRatio;
	gSystemMgr.m_vCMotor[MOTOR_Y].MotorMoveStep();
}


void CProjectAADlg::OnBnClickedButton23()
{
	CString cstr;
	m_editStep.GetWindowTextW(cstr);
	if (_ttof(cstr) < 0)
		m_editStep.SetWindowTextW(L"0.0");
	if (_ttof(cstr) > 0.05)
		m_editStep.SetWindowTextW(L"0.05");
	m_editStep.GetWindowTextW(cstr);
	gSystemMgr.m_vCMotor[MOTOR_Z].m_sAxisSetting.m_dTargetPos = _ttof(cstr) * gSystemMgr.m_vCMotor[MOTOR_Z].PositionRatio;
	gSystemMgr.m_vCMotor[MOTOR_Z].MotorMoveStep();
}


void CProjectAADlg::OnBnClickedButton24()
{
	CString cstr;
	m_editStep.GetWindowTextW(cstr);
	if (_ttof(cstr) < 0)
		m_editStep.SetWindowTextW(L"0.0");
	if (_ttof(cstr) > 0.05)
		m_editStep.SetWindowTextW(L"0.05");
	m_editStep.GetWindowTextW(cstr);
	gSystemMgr.m_vCMotor[MOTOR_Z].m_sAxisSetting.m_dTargetPos = -_ttof(cstr) * gSystemMgr.m_vCMotor[MOTOR_Z].PositionRatio;
	gSystemMgr.m_vCMotor[MOTOR_Z].MotorMoveStep();
}


void CProjectAADlg::OnOpenLightTestDlg()
{
	if (m_cLightTestDlg != nullptr)
	{
		delete m_cLightTestDlg;
		m_cLightTestDlg = nullptr;
	}
	if (m_cLightTestDlg == nullptr)
	{
		m_cLightTestDlg = new CLightTestDlg;
		m_cLightTestDlg->Create(IDD_DIALOG_STD, this);
	}
	m_cLightTestDlg->ShowWindow(SW_SHOW);
}
