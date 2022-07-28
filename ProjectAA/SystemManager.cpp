#include "pch.h"
#include "SystemManager.h"
#include "ConfigFileManager.h"
#include "SystemLog.h"

extern CConfigFileManager gConfigMgr;
extern CSystemLog     gSystemLog;

//弹窗弹出一段时间后自动关闭
int DU_MessageBoxTimeout(HWND hWnd, const WCHAR* sText, const WCHAR* sCaption, UINT uType, DWORD dwMilliseconds)
{
	typedef int(_stdcall* MSGBOXWAPI)(IN HWND hWnd, IN LPCWSTR lpText, IN LPCWSTR lpCaption, IN UINT type, IN WORD wLanguageId, IN DWORD dwMilliseconds);
	int iResult;
	HMODULE hUser32 = LoadLibrary(L"user32.dll");
	if (hUser32) {
		auto MessageBoxTimeout = (MSGBOXWAPI)GetProcAddress(hUser32, "MessageBoxTimeoutW");
		iResult = MessageBoxTimeout(hWnd, sText, sCaption, uType, 0, dwMilliseconds);
		FreeLibrary(hUser32);
	}
}


CSystemManager::CSystemManager()
{
	CRect rcScreen;
	SystemParametersInfo(SPI_GETWORKAREA, 0, &rcScreen, 0);
	m_fScreenX = 1;//float(1.0f*rcScreen.Width() / UI_SCREEN_X);
	m_fScreenY = 1;//float(1.0f*rcScreen.Height() / UI_SCREEN_Y);

	m_logFont.CreateFont(int(16 * m_fScreenX), 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0,
		ANSI_CHARSET,
		OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_SWISS,
		_T("Arial"));



	m_vCMotor.resize(9);
	CString cstrMutex;
	for (size_t i = 0; i < 9; i++)
	{
		cstrMutex.Format(L"Motor%d", i);
		m_vCMotor[i].mutex = CreateMutex(NULL, FALSE, cstrMutex);
	}
}

CSystemManager::~CSystemManager()
{
}

bool CSystemManager::DMC3800Init()
{
	gSystemLog.DisplayLogAndSave(L"开始初始化运动控制卡", LV_EVENT);
	WORD My_CardNum;      //定义卡数
	WORD My_CardList[8];   //定义卡号数组
	DWORD My_CardTypeList[8];   //定义各卡类型
	if (dmc_board_init() <= 0)      //控制卡的初始化操作
	{
		AfxMessageBox(L"初始化控制卡失败");
		return false;
	}

	dmc_get_CardInfList(&My_CardNum, My_CardTypeList, My_CardList);    //获取正在使用的卡号列表

	m_nCard = My_CardList[0];

	int result;
	result = nmc_set_connect_state(m_nCard, 1, 1, 0);//链接
	CString cstr;
	cstr.Format(L"nmc_set_connect_state 1 result:%d", result);
	gSystemLog.DisplayLogAndSave(cstr.GetBuffer(), LV_EVENT);

	TCHAR  moduleFileName[MAX_PATH];
	::GetModuleFileName(NULL, moduleFileName, MAX_PATH);
	(_tcsrchr(moduleFileName, _T('\\')))[1] = 0;
	CString cstrPath = moduleFileName;
	cstrPath.Append(_T("recipe\\"));
	if (!_wmkdir(cstrPath))
	{

	}
	cstrPath.Append(_T("LTDMC_0.ini"));
	CString cstrLog;
	cstrLog.Format(L"read ini Path:%s", cstrPath);
	gSystemLog.DisplayLogAndSave(cstrLog.GetBuffer(), LV_INVALID);
	USES_CONVERSION;
	char* c_strPath = T2A(cstrPath);
	int nErrCode = dmc_download_configfile(m_nCard, c_strPath);
	//int nErrCode = DMCMotorInit();
	if (nErrCode)
	{
		CString cstrLog;
		cstrLog.Format(L"Device DMC5000 initialization error ! ERROR_CODE2=%d\n", nErrCode);
		gSystemLog.DisplayLogAndSave(cstrLog.GetBuffer(), LV_ERROR);
		dmc_board_close();
		return false;
	}
	gSystemLog.DisplayLogAndSave(L"DMC Init OK", LV_EVENT);
	return true;
}

int CSystemManager::DMCMotorInit()
{
	int nMotorCode;
	int nErrCode;

	
	for (nMotorCode = M_TABLE_Z;nMotorCode <=  MOTOR_Yt;nMotorCode++)
	{
		if (!(nErrCode = dmc_set_pulse_outmode(m_nCard, nMotorCode,0))) return nErrCode;

		if ( nMotorCode < MOTOR_X)
		{
			nErrCode = dmc_set_alm_mode(m_nCard, nMotorCode, 1, 0, 0);
		}
		else
		{
			nErrCode = dmc_set_alm_mode(m_nCard, nMotorCode, 1, 0, 0);
		}
		if (!nErrCode)
		{
			return nErrCode;
		}
	}
	/*motorz 与 motorYt 的传感器与其他轴不同*/
	if (!(nErrCode = dmc_set_el_mode(m_nCard, M_TABLE_Z, 1, 0, 0))) return nErrCode;
	if (!(nErrCode = dmc_set_el_mode(m_nCard, M_CHART_Z, 1, 0, 0))) return nErrCode;
	if (!(nErrCode = dmc_set_el_mode(m_nCard, M_TABLE_X, 1, 0, 0))) return nErrCode;
	if (!(nErrCode = dmc_set_el_mode(m_nCard, MOTOR_X, 1, 1, 0))) return nErrCode;
	if (!(nErrCode = dmc_set_el_mode(m_nCard, MOTOR_Y, 1, 1, 0))) return nErrCode;
	if (!(nErrCode = dmc_set_el_mode(m_nCard, MOTOR_Z, 1, 0, 0))) return nErrCode;
	if (!(nErrCode = dmc_set_el_mode(m_nCard, MOTOR_Xt, 1, 1, 0))) return nErrCode;
	if (!(nErrCode = dmc_set_el_mode(m_nCard, MOTOR_Yt, 1, 0, 0))) return nErrCode;
	
	return 0;
}

void CSystemManager::MotorReadConfig()
{
	std::map<int, AXIS_SETTING> mapAxisSetting = *gConfigMgr.GetAxisSettingDict();
	for (int i = 0; i < (int)m_vCMotor.size(); i++)
	{
		m_vCMotor[i].m_sAxisSetting = mapAxisSetting[i];

		//SPEED_PAR nSpeed;
		//nSpeed.Start_Speed = m_vCMotor[i].m_sAxisSetting.m_nSpeedHome;
		//nSpeed.Drive_Speed = m_vCMotor[i].m_sAxisSetting.m_nSpeedHome;
		//nSpeed.Acc = m_vCMotor[i].m_sAxisSetting.m_nSpeedHome * 10;
		//nSpeed.Dec = m_vCMotor[i].m_sAxisSetting.m_nSpeedHome * 10;
		//nSpeed.AccTime = 0.1;
		//nSpeed.DecTime = 0.1;
		//m_vCMotor[i].m_sMoveHome = nSpeed;

		//m_vCMotor[i].m_nMotorDirection = m_vCMotor[i].m_sAxisSetting.m_nDirection;

		//nSpeed.Start_Speed = m_vCMotor[i].m_sAxisSetting.m_nSpeedMove;
		//nSpeed.Drive_Speed = m_vCMotor[i].m_sAxisSetting.m_nSpeedMove;
		//nSpeed.Acc = m_vCMotor[i].m_sAxisSetting.m_nSpeedMove * 10;
		//nSpeed.Dec = m_vCMotor[i].m_sAxisSetting.m_nSpeedMove * 10;
		//nSpeed.AccTime = 0.1;
		//nSpeed.DecTime = 0.1;
		//m_vCMotor[i].m_sMoveStep = nSpeed;
	}
}

void CSystemManager::TotalMotorStop()
{
	for (int i = 0; i < (int)m_vCMotor.size(); i++)
	{
		m_vCMotor[i].StopMove();
	}
}

bool CSystemManager::HomeAll()
{
	CString cstrLog;
	cstrLog.AppendFormat(L"设备 开始回原点");
	gSystemLog.DisplayLogAndSave(cstrLog.GetBuffer(), LV_EVENT);

	m_cIo.SetOutputIo(6, ON);
	m_cIo.SetOutputIo(5, OFF);
	m_cIo.SetOutputIo(8, ON);
	m_cIo.SetOutputIo(7, OFF);
	m_cIo.SetOutputIo(10, ON);
	m_cIo.SetOutputIo(9, OFF);
	m_cIo.SetOutputIo(12, ON);
	m_cIo.SetOutputIo(11, OFF);

	m_cIo.SetOutputIo(3, OFF);
	m_cIo.SetOutputIo(4, OFF);

	AllMotorHome();
	if (m_bHomeFlag)
	{
		gSystemLog.DisplayLogAndSave(L"总复位:成功", LV_EVENT);
		return true;
	}
	else
	{
		gSystemLog.DisplayLogAndSave(L"总复位:失败", LV_ERROR);
		return false;
	}
	return false;

}

bool CSystemManager::AllMotorHome()
{
	if (m_bMotorErrorFlag) {
		gSystemLog.DisplayLogAndSave(L"轴报错:安全错误", LV_ERROR);
		return false;
	}
	CString cstrLog;
	cstrLog.AppendFormat(L"轴开始回原点");
	gSystemLog.DisplayLogAndSave(cstrLog.GetBuffer(), LV_EVENT);

	//待添加
	short bMotor0Done = 0x00;
	short bMotor5Done = 0x00;

	gSystemLog.DisplayLogAndSave(L"复位:各电机开始复位...", LV_EVENT);
	int nTimeout = 5000;//50s

	m_vCMotor[M_TABLE_Z].m_nMotorDirection = MOVE_DIRECTION_FORWARD;
	m_vCMotor[M_TABLE_Z].HomeSearch2(m_vCMotor[M_TABLE_Z].m_nMotorDirection);
	nTimeout = 9000;//50s
	Sleep(500);
	bMotor0Done = 0;
	while (1)
	{
		Sleep(10);
		if (bMotor0Done == MOTION_DONE)
		{
			break;
		}
		if (nTimeout-- < 0)
		{
			CString cstrLog;
			if (MOTION_DONE != bMotor0Done)
			{
				cstrLog.Format(L"TZ回极限超时");
				gSystemLog.DisplayLogAndSave(cstrLog.GetBuffer(), LV_ERROR);
			}
			return false;
		}
		bMotor0Done = dmc_check_done(m_nCard, M_TABLE_Z);
	}

	m_vCMotor[MOTOR_Z].m_bHomed = 0;
	m_vCMotor[MOTOR_Z].HomeSearch(MOVE_DIRECTION_FORWARD);
	nTimeout = 5000;//50s
	Sleep(500);
	while (1)
	{
		Sleep(10);
		if ((bMotor5Done == MOTION_DONE) && (m_vCMotor[MOTOR_Z].m_bHomed == 1))
		{
			break;
		}
		if (nTimeout-- < 0)
		{
			CString cstrLog;
			if (MOTION_DONE != bMotor5Done)
			{
				cstrLog.Format(L"调焦Z回原超时");
				gSystemLog.DisplayLogAndSave(cstrLog.GetBuffer(), LV_ERROR);
			}
			return false;
		}
		bMotor5Done = dmc_check_done(m_nCard, MOTOR_Z);
	}

	m_vCMotor[MOTOR_Y].m_bHomed = 0;
	m_vCMotor[MOTOR_Y].m_nMotorDirection = MOVE_DIRECTION_FORWARD;
	m_vCMotor[MOTOR_Y].HomeSearch(m_vCMotor[MOTOR_Y].m_nMotorDirection);
	nTimeout = 9000;//50s
	Sleep(500);
	bMotor0Done = 0;
	while (1)
	{
		Sleep(10);
		if (bMotor0Done == MOTION_DONE && m_vCMotor[MOTOR_Y].m_bHomed)
		{
			break;
		}
		if (nTimeout-- < 0)
		{
			CString cstrLog;
			if (MOTION_DONE != bMotor0Done)
			{
				cstrLog.Format(L"AAY回原超时");
				gSystemLog.DisplayLogAndSave(cstrLog.GetBuffer(), LV_ERROR);
			}
			return false;
		}
		bMotor0Done = dmc_check_done(m_nCard, MOTOR_Y);

	}

	m_vCMotor[M_TABLE_X].m_bHomed = 0;
	m_vCMotor[MOTOR_X].m_bHomed = 0;
	m_vCMotor[MOTOR_Xt].m_bHomed = 0;
	m_vCMotor[MOTOR_Yt].m_bHomed = 0;
	m_vCMotor[M_TABLE_X].m_nMotorDirection = MOVE_DIRECTION_FORWARD;
	m_vCMotor[MOTOR_X].m_nMotorDirection = MOVE_DIRECTION_REVERSE;
	m_vCMotor[MOTOR_Xt].m_nMotorDirection = MOVE_DIRECTION_FORWARD;
	m_vCMotor[MOTOR_Yt].m_nMotorDirection = MOVE_DIRECTION_FORWARD;

	m_vCMotor[M_TABLE_X].HomeSearch(m_vCMotor[M_TABLE_X].m_nMotorDirection);
	m_vCMotor[MOTOR_X].HomeSearch(m_vCMotor[MOTOR_X].m_nMotorDirection);
	m_vCMotor[MOTOR_Xt].HomeSearch(m_vCMotor[MOTOR_Xt].m_nMotorDirection);
	m_vCMotor[MOTOR_Yt].HomeSearch(m_vCMotor[MOTOR_Yt].m_nMotorDirection);
	nTimeout = 10000;//100s
	Sleep(500);
	while (1)
	{
		Sleep(10);
		if (nTimeout-- < 0)
		{
			CString cstrLog;
			cstrLog.Format(L"五轴回原超时");
			gSystemLog.DisplayLogAndSave(cstrLog.GetBuffer(), LV_ERROR);
			return false;
		}

		if (/*CheckMotorHome()*/m_vCMotor[MOTOR_X].m_bHomed && m_vCMotor[M_TABLE_X].m_bHomed && m_vCMotor[MOTOR_Xt].m_bHomed && m_vCMotor[MOTOR_Yt].m_bHomed)
		{
			//m_bHomeFlag = TRUE;

			break;
		}
	}

	bMotor0Done = 0;
	m_vCMotor[M_TABLE_Z].m_bHomed = 0;
	m_vCMotor[M_TABLE_Z].HomeSearch(MOVE_DIRECTION_FORWARD);
	nTimeout = 5000;//50s
	Sleep(500);
	while (1)
	{
		Sleep(10);
		if ((bMotor0Done == MOTION_DONE) && (m_vCMotor[M_TABLE_Z].m_bHomed == 1))
		{
			break;
		}
		if (nTimeout-- < 0)
		{
			CString cstrLog;
			if (MOTION_DONE != bMotor0Done)
			{
				cstrLog.Format(L"纵向Z回原超时");
				gSystemLog.DisplayLogAndSave(cstrLog.GetBuffer(), LV_ERROR);
			}
			return false;
		}
		bMotor0Done = dmc_check_done(m_nCard, M_TABLE_Z);
	}
	//m_vCMotor[MOTOR_Y].m_nMotorDirection = MOVE_DIRECTION_REVERSE;
	//m_vCMotor[MOTOR_Y].HomeSearch(m_vCMotor[MOTOR_Y].m_nMotorDirection);
	//nTimeout = 9000;//50s
	//Sleep(500);
	//bMotor0Done = 0;
	//while (1)
	//{
	//	Sleep(10);
	//	if (m_vCMotor[MOTOR_Y].m_bHomed == 1)
	//	{
	//		break;
	//	}
	//	if (nTimeout-- < 0)
	//	{
	//		CString cstrLog;
	//		cstrLog.Format(L"调焦Y回原超时");
	//		gSystemLog.DisplayLogAndSave(cstrLog.GetBuffer(), LV_ERROR);
	//		return false;
	//	}
	//}

	if (CheckMotorHome())
	{
		m_bHomeFlag = TRUE;
	}

	if (m_bHomeFlag)
	{
		gSystemLog.DisplayLogAndSave(L"复位:各电机复位结束 复位成功!", LV_EVENT);
		return true;
	}
	else
	{
		gSystemLog.DisplayLogAndSave(L"复位:各电机复位结束 复位失败!", LV_ERROR);
		return false;
	}

	return 0;
}

bool CSystemManager::ChartMotorHome()
{
	if (m_bMotorErrorFlag) {
		gSystemLog.DisplayLogAndSave(L"轴报错:安全错误", LV_ERROR);
		return false;
	}
	CString cstrLog;
	cstrLog.AppendFormat(L"图卡轴开始回原点");
	gSystemLog.DisplayLogAndSave(cstrLog.GetBuffer(), LV_EVENT);

	//待添加
	short bMotor0Done = 0x00;
	int nTimeout = 5000;//50s

	m_vCMotor[M_CHART_Z].m_nMotorDirection = MOVE_DIRECTION_FORWARD;
	m_vCMotor[M_CHART_Z].HomeSearch(m_vCMotor[M_CHART_Z].m_nMotorDirection);
	nTimeout = 9000;//50s
	Sleep(500);
	while (1)
	{
		Sleep(10);
		if (m_vCMotor[M_CHART_Z].m_bHomed == 1)
		{
			break;
		}
		if (nTimeout-- < 0)
		{
			CString cstrLog;
			cstrLog.Format(L"图卡Z回原超时");
			gSystemLog.DisplayLogAndSave(cstrLog.GetBuffer(), LV_ERROR);
			return false;
		}
	}

	ChartHomeFlag = TRUE;
	

	if (ChartHomeFlag)
	{
		gSystemLog.DisplayLogAndSave(L"复位:图卡电机复位结束 复位成功!", LV_EVENT);
		return true;
	}
	else
	{
		gSystemLog.DisplayLogAndSave(L"复位:图卡电机复位结束 复位失败!", LV_ERROR);
		return false;
	}

	return 0;
}

bool CSystemManager::CheckMotorHome()
{

	if (m_vCMotor[MOTOR_X].m_bHomed == false)
	{
		return false;
	}
	if (m_vCMotor[MOTOR_Y].m_bHomed == false)
	{
		return false;
	}
	if (m_vCMotor[MOTOR_Z].m_bHomed == false)
	{
		return false;
	}
	if (m_vCMotor[MOTOR_Xt].m_bHomed == false)
	{
		return false;
	}
	if (m_vCMotor[MOTOR_Yt].m_bHomed == false)
	{
		return false;
	}
	if (m_vCMotor[M_TABLE_X].m_bHomed == false)
	{
		return false;
	}
	if (m_vCMotor[M_TABLE_Z].m_bHomed == false)
	{
		return false;
	}
	return true;
}


void CSystemManager::StartGetMotorIoThread()
{
	ProcGetMotorIo.MemProc = &CSystemManager::GetMotorIoThread;
	UINT nThreadId;
	HANDLE hThread = (HANDLE)_beginthreadex(NULL, 0, ProcGetMotorIo.ThreadProc, (LPVOID)this, 0, &nThreadId);
	if (hThread == NULL)
	{
		return;
	}
	m_vWorkerThread.push_back(hThread);
}

unsigned int __stdcall CSystemManager::GetMotorIoThread()
{
	while (0 == m_nExitFlag)
	{
		Sleep(5);
		DWORD nMotorIO;
		int nMotorCode;
		for (nMotorCode = M_TABLE_Z; nMotorCode <= MOTOR_Yt; nMotorCode++)
		{
			if (nMotorCode < MOTOR_X)
			{
				m_vCMotor[nMotorCode].m_bServoOn = dmc_read_sevon_pin(m_nCard, nMotorCode);
			}
			else
			{
				//步进电机无需上伺服
				m_vCMotor[nMotorCode].m_bServoOn = OFF;
			}

			nMotorIO = dmc_axis_io_status(m_nCard, nMotorCode);
			m_vCMotor[nMotorCode].m_bALM = (((nMotorIO & 0x01) == 0x00) ? OFF : ON);
			m_vCMotor[nMotorCode].m_bPEL = (((nMotorIO & 0x02) == 0x00) ? OFF : ON);
			m_vCMotor[nMotorCode].m_bNEL = (((nMotorIO & 0x04) == 0x00) ? OFF : ON);
			m_vCMotor[nMotorCode].m_bEMG = (((nMotorIO & 0x08) == 0x00) ? OFF : ON);
			m_vCMotor[nMotorCode].m_bORG = (((nMotorIO & 0x10) == 0x00) ? ON : OFF);
			//m_vCMotor[nMotorCode].m_bPSL = (((nMotorIO & 0x20) == 0x00) ? ON : OFF);
			//m_vCMotor[nMotorCode].m_bNSL = (((nMotorIO & 0x40) == 0x00) ? ON : OFF);
			m_vCMotor[nMotorCode].m_bINP = (((nMotorIO & 0x80) == 0x00) ? OFF : ON);
			//缺省ez
			m_vCMotor[nMotorCode].m_bRDY = (((nMotorIO & 0x200) == 0x00) ? OFF : ON);
		}
	}
	gSystemLog.DisplayLogAndSave(L"Exit thread 1", LV_EVENT);
	return 0;
}

void CSystemManager::StartGetMotorEncoderThread()
{
	ProcGetMotorEncoder.MemProc = &CSystemManager::GetMotorEncoderThread;
	UINT nThreadId;
	HANDLE hThread = (HANDLE)_beginthreadex(NULL, 0, ProcGetMotorEncoder.ThreadProc, (LPVOID)this, 0, &nThreadId);
	if (hThread == NULL)
	{
		return;
	}
	m_vWorkerThread.push_back(hThread);
}

unsigned int __stdcall CSystemManager::GetMotorEncoderThread()
{
	while (0 == m_nExitFlag)
	{
		Sleep(5);
		int nMotorCode;
		for (nMotorCode = M_TABLE_Z; nMotorCode <= MOTOR_Yt; nMotorCode++)
		{
			if (nMotorCode < MOTOR_X)
			{
				WaitForSingleObject(m_vCMotor[nMotorCode].mutex, INFINITE);
				m_vCMotor[nMotorCode].m_nCurPositon = dmc_get_encoder(m_nCard, nMotorCode);
				ReleaseMutex(m_vCMotor[nMotorCode].mutex);
			}
			else
			{
				WaitForSingleObject(m_vCMotor[nMotorCode].mutex, INFINITE);
				m_vCMotor[nMotorCode].m_nCurPositon = dmc_get_position(m_nCard, nMotorCode);
				ReleaseMutex(m_vCMotor[nMotorCode].mutex);
			}
		}
	}
	gSystemLog.DisplayLogAndSave(L"Exit thread 2", LV_EVENT);
	return 0;
}

void CSystemManager::SetMotorPosToSiteDlg(CString cstrPos)
{
	if (nullptr != m_sSiteDlgToMotorDlg.m_ptrDlgHandle)
	{
		SetDlgItemTextW(m_sSiteDlgToMotorDlg.m_ptrDlgHandle->GetSafeHwnd(),
			m_sSiteDlgToMotorDlg.m_nEditId, cstrPos);
	}
}

CString CSystemManager::GetCurrentExePath()
{
	char cDir[MAX_PATH];
	GetModuleFileName(NULL, (LPWSTR)cDir, MAX_PATH);
	(_tcsrchr((LPWSTR)cDir, _T('\\')))[0] = 0;

	CString cstrPath;
	cstrPath.Format(L"%s", cDir);
	return cstrPath;
}

void CSystemManager::GeneralSettingIniInit()
{
	char cDir[MAX_PATH];
	m_cGeneralSetting.GetCurrentDir((LPWSTR)cDir);
	CString cstr;
	cstr.Format(L"%s\\recipe\\GeneralSetting.ini", cDir);
	m_cGeneralSetting.ConfigIniInit(cstr);
	ReadGeneralSettingIni();
}

void CSystemManager::ReadGeneralSettingIni()
{
	CString cstr;
	m_cGeneralSetting.ReadConfigIni(L"GeneralSetting", L"m_cstrProductName", cstr);
	m_sGeneralSetting.m_cstrProjectName = cstr;

}

void CSystemManager::ReadErrorListIni()
{
	m_cErrorMsg[0] = "...";
	m_cErrorMsg[1] = " 托盘流进AA工位超时";
	m_cErrorMsg[2] = " AA站已存在托盘，需拿出";
	m_cErrorMsg[3] = " 检胶托盘下落超时";
	m_cErrorMsg[4] = " 检胶托盘顶起超时";
	m_cErrorMsg[5] = "5";
	m_cErrorMsg[6] = "6";
	m_cErrorMsg[7] = "7";
	m_cErrorMsg[8] = "8";
	m_cErrorMsg[9] = "9";
	m_cErrorMsg[10] = "10";
	m_cErrorMsg[11] = "AA夹爪气缸工作位未到位";
	m_cErrorMsg[12] = "AA夹爪移动错误 - Load";
	m_cErrorMsg[13] = "需放置増距镜";
	m_cErrorMsg[14] = "AA夹爪气缸原位未到位";
	m_cErrorMsg[15] = "AA顶升气缸原位未到位";
	m_cErrorMsg[16] = "16";
	m_cErrorMsg[17] = "AA夹爪移动错误 - Pick";
	m_cErrorMsg[18] = "升降机上升超时";
	m_cErrorMsg[19] = "升降机下降超时";
	m_cErrorMsg[20] = "升降机托盘流走超时";
	m_cErrorMsg[21] = "上电气缸原位错误";
	m_cErrorMsg[22] = "22";
	m_cErrorMsg[23] = "23";
	m_cErrorMsg[24] = "24";
	m_cErrorMsg[25] = "25";
	m_cErrorMsg[26] = "连续超过3个NG";
	m_cErrorMsg[27] = "27";
	m_cErrorMsg[28] = "28";
	m_cErrorMsg[29] = "29";
	m_cErrorMsg[30] = "30";
	m_cErrorMsg[31] = "31";
	m_cErrorMsg[32] = "32";
	m_cErrorMsg[33] = "33";
	m_cErrorMsg[34] = "34";
	m_cErrorMsg[35] = "35";
	m_cErrorMsg[36] = "36";
	m_cErrorMsg[37] = "37";
	m_cErrorMsg[38] = "38";
	m_cErrorMsg[39] = "39";
	m_cErrorMsg[40] = "40";
	m_cErrorMsg[41] = "41";
	m_cErrorMsg[42] = "42";
	m_cErrorMsg[43] = "胶水-RFID连接错误";
	m_cErrorMsg[44] = "AA-RFID连接错误";
	m_cErrorMsg[45] = "45";
	m_cErrorMsg[46] = "胶水TCP未连接-错误";
	m_cErrorMsg[47] = "47";
	m_cErrorMsg[48] = "Err:急停按下";
	m_cErrorMsg[49] = "40工站未回原位";
	m_cErrorMsg[50] = "安全继电器断开";

}

//图像采集
void CSystemManager::CaptureConfigIniInit()
{
	char cDir[MAX_PATH];
	m_cCaptureConfigIni.GetCurrentDir((LPWSTR)cDir);
	CString cstr;
	cstr.Format(L"%s\\recipe\\", cDir);
	cstr.Append(m_sGeneralSetting.m_cstrProjectName.GetBuffer());
	cstr.Append(L"\\");
	cstr.Append(L"Capture.ini");

	m_cCaptureConfigIni.ConfigIniInit(cstr);
	ReadCaptureConfigIni();
}

void CSystemManager::ReadCaptureConfigIni()
{
	CString cstr;
	m_cCaptureConfigIni.ReadConfigIni(L"CaptureConfig", L"m_nImageSource", cstr);
	m_nImageSource = _ttoi(cstr);

	m_cCaptureConfigIni.ReadConfigIni(L"CaptureConfig", L"m_nTestMode", cstr);
	m_nTestMode = _ttoi(cstr);

	m_cCaptureConfigIni.ReadConfigIni(L"CaptureConfig", L"m_nCaptureMode", cstr);
	m_nCaptureMode = _ttoi(cstr);

	m_cCaptureConfigIni.ReadConfigIni(L"CaptureConfig", L"m_nImageChangeMode", cstr);
	m_nImageChangeMode = _ttoi(cstr);

	m_cCaptureConfigIni.ReadConfigIni(L"CaptureConfig", L"m_bWriteIIC", cstr);
	m_bWriteIIC = _ttoi(cstr);

	m_cCaptureConfigIni.ReadConfigIni(L"CaptureConfig", L"m_bMirrorX", cstr);
	m_bMirrorX = _ttoi(cstr);

	m_cCaptureConfigIni.ReadConfigIni(L"CaptureConfig", L"m_bMirrorY", cstr);
	m_bMirrorY = _ttoi(cstr);

	m_cCaptureConfigIni.ReadConfigIni(L"CaptureConfig", L"m_nCtsId", cstr);
	m_nCtsId = _ttoi(cstr);

	m_cCaptureConfigIni.ReadConfigIni(L"CaptureConfig", L"m_bGpioFlag", cstr);
	m_bGpioFlag = _ttoi(cstr);
	m_cCaptureConfigIni.ReadConfigIni(L"CaptureConfig", L"m_nGpioNo", cstr);
	m_nGpioNo = _ttoi(cstr);

	m_cCaptureConfigIni.ReadConfigIni(L"CaptureConfig", L"ChangeXY", cstr);
	ChangeXY = _ttoi(cstr);

	m_cCaptureConfigIni.ReadConfigIni(L"CaptureConfig", L"CameraDsW", cstr);
	CameraDsW = _ttoi(cstr);
	m_cCaptureConfigIni.ReadConfigIni(L"CaptureConfig", L"CameraDsH", cstr);
	CameraDsH = _ttoi(cstr);

	//sfr测试设定参数
	m_cCaptureConfigIni.ReadConfigIni(L"SfrSetting", L"m_nMtfPer", cstr); m_nMtfPer = _ttoi(cstr);
	m_cCaptureConfigIni.ReadConfigIni(L"SfrSetting", L"m_dFreq", cstr); m_dFreq = _ttof(cstr);
	m_cCaptureConfigIni.ReadConfigIni(L"SfrSetting", L"m_bUseMTF", cstr); m_bUseMTF = _ttoi(cstr);
	m_cCaptureConfigIni.ReadConfigIni(L"SfrSetting", L"m_bOpenFieldA", cstr); m_bOpenFieldA = _ttoi(cstr);
	m_cCaptureConfigIni.ReadConfigIni(L"SfrSetting", L"m_nRoiW[0]", cstr); m_nRoiW[0] = _ttoi(cstr);
	m_cCaptureConfigIni.ReadConfigIni(L"SfrSetting", L"m_nRoiH[0]", cstr); m_nRoiH[0] = _ttoi(cstr);
	m_cCaptureConfigIni.ReadConfigIni(L"SfrSetting", L"m_nSearchW[0]", cstr); m_nSearchW[0] = _ttoi(cstr);
	m_cCaptureConfigIni.ReadConfigIni(L"SfrSetting", L"m_nSearchH[0]", cstr); m_nSearchH[0] = _ttoi(cstr);
	m_cCaptureConfigIni.ReadConfigIni(L"SfrSetting", L"m_nPattern[0]", cstr); m_nPattern[0] = _ttoi(cstr);
	m_cCaptureConfigIni.ReadConfigIni(L"SfrSetting", L"m_nDistance[0]", cstr); m_nDistance[0] = _ttoi(cstr);
	m_cCaptureConfigIni.ReadConfigIni(L"SfrSetting", L"m_nRoiW[1]", cstr); m_nRoiW[1] = _ttoi(cstr);
	m_cCaptureConfigIni.ReadConfigIni(L"SfrSetting", L"m_nRoiH[1]", cstr); m_nRoiH[1] = _ttoi(cstr);
	m_cCaptureConfigIni.ReadConfigIni(L"SfrSetting", L"m_nSearchW[1]", cstr); m_nSearchW[1] = _ttoi(cstr);
	m_cCaptureConfigIni.ReadConfigIni(L"SfrSetting", L"m_nSearchH[1]", cstr); m_nSearchH[1] = _ttoi(cstr);
	m_cCaptureConfigIni.ReadConfigIni(L"SfrSetting", L"m_nPattern[1]", cstr); m_nPattern[1] = _ttoi(cstr);
	m_cCaptureConfigIni.ReadConfigIni(L"SfrSetting", L"m_nDistance[1]", cstr); m_nDistance[1] = _ttoi(cstr);
	m_cCaptureConfigIni.ReadConfigIni(L"SfrSetting", L"m_nSpecCenter", cstr); m_nSpecCenter = _ttoi(cstr);
	m_cCaptureConfigIni.ReadConfigIni(L"SfrSetting", L"m_dSpecAAAngle", cstr); m_dSpecAAAngle = _ttof(cstr);
	m_cCaptureConfigIni.ReadConfigIni(L"SfrSetting", L"m_dSpecSfr[0]", cstr); m_dSpecSfr[0] = _ttof(cstr);
	m_cCaptureConfigIni.ReadConfigIni(L"SfrSetting", L"m_dSpecSfr[1]", cstr); m_dSpecSfr[1] = _ttof(cstr);
	m_cCaptureConfigIni.ReadConfigIni(L"SfrSetting", L"m_nRoiEnable[0][3]", cstr); m_nRoiEnable[0][3] = _ttoi(cstr);
	m_cCaptureConfigIni.ReadConfigIni(L"SfrSetting", L"m_nRoiEnable[1][3]", cstr); m_nRoiEnable[1][3] = _ttoi(cstr);
	m_cCaptureConfigIni.ReadConfigIni(L"SfrSetting", L"m_nRoiEnable[2][3]", cstr); m_nRoiEnable[2][3] = _ttoi(cstr);
	m_cCaptureConfigIni.ReadConfigIni(L"SfrSetting", L"m_nRoiEnable[3][3]", cstr); m_nRoiEnable[3][3] = _ttoi(cstr);
	m_cCaptureConfigIni.ReadConfigIni(L"SfrSetting", L"m_nRoiEnable[4][3]", cstr); m_nRoiEnable[4][3] = _ttoi(cstr);
	m_cCaptureConfigIni.ReadConfigIni(L"SfrSetting", L"m_nRoiEnable[0][2]", cstr); m_nRoiEnable[0][2] = _ttoi(cstr);
	m_cCaptureConfigIni.ReadConfigIni(L"SfrSetting", L"m_nRoiEnable[1][2]", cstr); m_nRoiEnable[1][2] = _ttoi(cstr);
	m_cCaptureConfigIni.ReadConfigIni(L"SfrSetting", L"m_nRoiEnable[2][2]", cstr); m_nRoiEnable[2][2] = _ttoi(cstr);
	m_cCaptureConfigIni.ReadConfigIni(L"SfrSetting", L"m_nRoiEnable[3][2]", cstr); m_nRoiEnable[3][2] = _ttoi(cstr);
	m_cCaptureConfigIni.ReadConfigIni(L"SfrSetting", L"m_nRoiEnable[4][2]", cstr); m_nRoiEnable[4][2] = _ttoi(cstr);
	m_cCaptureConfigIni.ReadConfigIni(L"SfrSetting", L"m_nRoiEnable[0][1]", cstr); m_nRoiEnable[0][1] = _ttoi(cstr);
	m_cCaptureConfigIni.ReadConfigIni(L"SfrSetting", L"m_nRoiEnable[1][1]", cstr); m_nRoiEnable[1][1] = _ttoi(cstr);
	m_cCaptureConfigIni.ReadConfigIni(L"SfrSetting", L"m_nRoiEnable[2][1]", cstr); m_nRoiEnable[2][1] = _ttoi(cstr);
	m_cCaptureConfigIni.ReadConfigIni(L"SfrSetting", L"m_nRoiEnable[3][1]", cstr); m_nRoiEnable[3][1] = _ttoi(cstr);
	m_cCaptureConfigIni.ReadConfigIni(L"SfrSetting", L"m_nRoiEnable[4][1]", cstr); m_nRoiEnable[4][1] = _ttoi(cstr);
	m_cCaptureConfigIni.ReadConfigIni(L"SfrSetting", L"m_nRoiEnable[0][0]", cstr); m_nRoiEnable[0][0] = _ttoi(cstr);
	m_cCaptureConfigIni.ReadConfigIni(L"SfrSetting", L"m_nRoiEnable[1][0]", cstr); m_nRoiEnable[1][0] = _ttoi(cstr);
	m_cCaptureConfigIni.ReadConfigIni(L"SfrSetting", L"m_nRoiEnable[2][0]", cstr); m_nRoiEnable[2][0] = _ttoi(cstr);
	m_cCaptureConfigIni.ReadConfigIni(L"SfrSetting", L"m_nRoiEnable[3][0]", cstr); m_nRoiEnable[3][0] = _ttoi(cstr);
	m_cCaptureConfigIni.ReadConfigIni(L"SfrSetting", L"m_nRoiEnable[4][0]", cstr); m_nRoiEnable[4][0] = _ttoi(cstr);
	m_cCaptureConfigIni.ReadConfigIni(L"SfrSetting", L"m_nBin[0]", cstr); m_nBin[0] = _ttoi(cstr);
	m_cCaptureConfigIni.ReadConfigIni(L"SfrSetting", L"m_nBin[1]", cstr); m_nBin[1] = _ttoi(cstr);
	m_cCaptureConfigIni.ReadConfigIni(L"SfrSetting", L"m_nBin[2]", cstr); m_nBin[2] = _ttoi(cstr);
	m_cCaptureConfigIni.ReadConfigIni(L"SfrSetting", L"m_nBin[3]", cstr); m_nBin[3] = _ttoi(cstr);
	m_cCaptureConfigIni.ReadConfigIni(L"SfrSetting", L"m_nBin[4]", cstr); m_nBin[4] = _ttoi(cstr);
	m_cCaptureConfigIni.ReadConfigIni(L"SfrSetting", L"m_nStartX[0]", cstr); m_nStartX[0] = _ttoi(cstr);
	m_cCaptureConfigIni.ReadConfigIni(L"SfrSetting", L"m_nStartX[1]", cstr); m_nStartX[1] = _ttoi(cstr);
	m_cCaptureConfigIni.ReadConfigIni(L"SfrSetting", L"m_nStartX[2]", cstr); m_nStartX[2] = _ttoi(cstr);
	m_cCaptureConfigIni.ReadConfigIni(L"SfrSetting", L"m_nStartX[3]", cstr); m_nStartX[3] = _ttoi(cstr);
	m_cCaptureConfigIni.ReadConfigIni(L"SfrSetting", L"m_nStartX[4]", cstr); m_nStartX[4] = _ttoi(cstr);
	m_cCaptureConfigIni.ReadConfigIni(L"SfrSetting", L"m_nStartY[0]", cstr); m_nStartY[0] = _ttoi(cstr);
	m_cCaptureConfigIni.ReadConfigIni(L"SfrSetting", L"m_nStartY[1]", cstr); m_nStartY[1] = _ttoi(cstr);
	m_cCaptureConfigIni.ReadConfigIni(L"SfrSetting", L"m_nStartY[2]", cstr); m_nStartY[2] = _ttoi(cstr);
	m_cCaptureConfigIni.ReadConfigIni(L"SfrSetting", L"m_nStartY[3]", cstr); m_nStartY[3] = _ttoi(cstr);
	m_cCaptureConfigIni.ReadConfigIni(L"SfrSetting", L"m_nStartY[4]", cstr); m_nStartY[4] = _ttoi(cstr);

	m_cCaptureConfigIni.ReadConfigIni(L"SfrSetting", L"m_nTargetX", cstr); m_nTargetX = _ttoi(cstr);
	m_cCaptureConfigIni.ReadConfigIni(L"SfrSetting", L"m_nTargetY", cstr); m_nTargetY = _ttoi(cstr);
	m_cCaptureConfigIni.ReadConfigIni(L"SfrSetting", L"m_bDrawLine", cstr); m_bDrawLine = _ttoi(cstr);

	m_cCaptureConfigIni.ReadConfigIni(L"SfrSetting", L"m_dSpecSfrUV[0]", cstr); m_dSpecSfrUV[0] = _ttof(cstr);
	m_cCaptureConfigIni.ReadConfigIni(L"SfrSetting", L"m_dSpecSfrUV[1]", cstr); m_dSpecSfrUV[1] = _ttof(cstr);
}

//统计信息
void CSystemManager::StateConfigIniInit()
{
	char cDir[MAX_PATH];
	m_cStateConfigIni.GetCurrentDir((LPWSTR)cDir);
	CString cstr;
	cstr.Format(L"%s\\recipe\\", cDir);
	cstr.Append(m_sGeneralSetting.m_cstrProjectName.GetBuffer());
	cstr.Append(L"\\");
	cstr.Append(L"State.ini");

	m_cStateConfigIni.ConfigIniInit(cstr);
	ReadStateConfigIni();
}

void CSystemManager::ReadStateConfigIni()
{
	CString cstr;
	//m_cStateConfigIni.ReadConfigIni(L"StateConfig", L"m_nWhiteAll", cstr); m_nWhiteAll = _ttoi(cstr);
	//m_cStateConfigIni.ReadConfigIni(L"StateConfig", L"m_nWhiteOK", cstr); m_nWhiteOK = _ttoi(cstr);
	//m_cStateConfigIni.ReadConfigIni(L"StateConfig", L"m_nWhiteNG", cstr); m_nWhiteNG = _ttoi(cstr);
	//m_cStateConfigIni.ReadConfigIni(L"StateConfig", L"m_nWhitePass", cstr); m_nWhitePass = _ttoi(cstr);

	//m_cStateConfigIni.ReadConfigIni(L"StateConfig", L"m_nAAAll", cstr); m_nAAAll = _ttoi(cstr);
	m_cStateConfigIni.ReadConfigIni(L"StateConfig", L"m_nAAOK", cstr); m_nAAOK = _ttoi(cstr);
	m_cStateConfigIni.ReadConfigIni(L"StateConfig", L"m_nAANG1", cstr); m_nAANG1 = _ttoi(cstr);
	m_cStateConfigIni.ReadConfigIni(L"StateConfig", L"m_nAANG2", cstr); m_nAANG2 = _ttoi(cstr);
	m_cStateConfigIni.ReadConfigIni(L"StateConfig", L"m_nAANG3", cstr); m_nAANG3 = _ttoi(cstr);
	m_cStateConfigIni.ReadConfigIni(L"StateConfig", L"AATime", AATime);
}

void CSystemManager::SaveStateConfigIni()
{
	CString cstr;
	//cstr.Format(L"%d", m_nWhiteAll); m_cStateConfigIni.SaveConfigIni(L"StateConfig", L"m_nWhiteAll", cstr);
	//cstr.Format(L"%d", m_nWhiteOK); m_cStateConfigIni.SaveConfigIni(L"StateConfig", L"m_nWhiteOK", cstr);
	//cstr.Format(L"%d", m_nWhiteNG); m_cStateConfigIni.SaveConfigIni(L"StateConfig", L"m_nWhiteNG", cstr);
	//cstr.Format(L"%d", m_nWhitePass); m_cStateConfigIni.SaveConfigIni(L"StateConfig", L"m_nWhitePass", cstr);

	//cstr.Format(L"%d", m_nAAAll); m_cStateConfigIni.SaveConfigIni(L"StateConfig", L"m_nAAAll", cstr);
	cstr.Format(L"%d", m_nAAOK); m_cStateConfigIni.SaveConfigIni(L"StateConfig", L"m_nAAOK", cstr);
	cstr.Format(L"%d", m_nAANG1); m_cStateConfigIni.SaveConfigIni(L"StateConfig", L"m_nAANG1", cstr);
	cstr.Format(L"%d", m_nAANG2); m_cStateConfigIni.SaveConfigIni(L"StateConfig", L"m_nAANG2", cstr);
	cstr.Format(L"%d", m_nAANG3); m_cStateConfigIni.SaveConfigIni(L"StateConfig", L"m_nAANG3", cstr);
	m_cStateConfigIni.SaveConfigIni(L"StateConfig", L"AATime", AATime);

}

//AA
void CSystemManager::AAConfigIniInit()
{
	char cDir[MAX_PATH];
	m_cAAConfigIni.GetCurrentDir((LPWSTR)cDir);
	CString cstr;
	cstr.Format(L"%s\\recipe\\", cDir);
	cstr.Append(m_sGeneralSetting.m_cstrProjectName.GetBuffer());
	cstr.Append(L"\\");
	cstr.Append(L"AAConfig.ini");

	m_cAAConfigIni.ConfigIniInit(cstr);
	ReadAAConfigIni();
}

void CSystemManager::ReadAAConfigIni()
{
	CString cstr;
	m_cAAConfigIni.ReadConfigIni(L"AA", L"m_nUVTime", cstr);
	m_nUVTime = _ttoi(cstr);

	m_cAAConfigIni.ReadConfigIni(L"AA", L"m_nCaptureWaitTime", cstr);
	m_nCaptureWaitTime = _ttoi(cstr);

	m_cAAConfigIni.ReadConfigIni(L"AA", L"m_nPeakDiff", cstr);
	m_nPeakDiff = _ttof(cstr);

	m_cAAConfigIni.ReadConfigIni(L"AA", L"m_nPeakMin", cstr);
	m_nPeakMin = _ttof(cstr);

	m_cAAConfigIni.ReadConfigIni(L"AA", L"m_dPixelSize", cstr);
	m_dPixelSize = _ttof(cstr);

	m_cAAConfigIni.ReadConfigIni(L"AA", L"m_nReturnStepCnt", cstr);
	m_nReturnStepCnt = _ttoi(cstr);

	m_cAAConfigIni.ReadConfigIni(L"AA", L"m_nSearchZStepMaxCnt", cstr);
	m_nSearchZStepMaxCnt = _ttoi(cstr);

	m_cAAConfigIni.ReadConfigIni(L"AA", L"m_dSearchZStep_1", cstr);
	m_dSearchZStep_1 = _ttof(cstr);
	m_cAAConfigIni.ReadConfigIni(L"AA", L"m_dSearchZSpec_1", cstr);
	m_dSearchZSpec_1 = _ttof(cstr);
	m_cAAConfigIni.ReadConfigIni(L"AA", L"m_dSearchZStep_2", cstr);
	m_dSearchZStep_2 = _ttof(cstr);
	m_cAAConfigIni.ReadConfigIni(L"AA", L"m_dSearchZSpec_2", cstr);
	m_dSearchZSpec_2 = _ttof(cstr);

	m_cAAConfigIni.ReadConfigIni(L"AA", L"m_nAAStepMaxCnt", cstr);
	m_nAAStepMaxCnt = _ttoi(cstr);

	m_cAAConfigIni.ReadConfigIni(L"AA", L"m_dAAStep", cstr);
	m_dAAStep = _ttof(cstr);

	m_cAAConfigIni.ReadConfigIni(L"AA", L"m_dAngleLimitSpec", cstr);
	m_dAngleLimitSpec = _ttof(cstr); 

	m_cAAConfigIni.ReadConfigIni(L"AA", L"CalibrationLimit", cstr);
	CalibrationLimit = _ttof(cstr);

	m_cAAConfigIni.ReadConfigIni(L"AA", L"m_dOffsetZ", cstr);
	m_dOffsetZ = _ttof(cstr);

	m_cAAConfigIni.ReadConfigIni(L"AA", L"m_bOffsetFlag", cstr);
	m_bOffsetFlag = _ttoi(cstr);

	m_cAAConfigIni.ReadConfigIni(L"AA", L"AAImgFlag", cstr);
	AAImgFlag = _ttoi(cstr);

	m_cAAConfigIni.ReadConfigIni(L"AA", L"UVImgFlag", cstr);
	UVImgFlag = _ttoi(cstr);

	m_cAAConfigIni.ReadConfigIni(L"AA", L"XFlag", cstr);
	XFlag = _ttoi(cstr);

	m_cAAConfigIni.ReadConfigIni(L"AA", L"YFlag", cstr);
	YFlag = _ttoi(cstr);

	m_cAAConfigIni.ReadConfigIni(L"AA", L"m_nPositionTableX[0]", cstr);
	m_nPositionTableX[0] = _ttoi(cstr);
	m_cAAConfigIni.ReadConfigIni(L"AA", L"m_nPositionTableX[1]", cstr);
	m_nPositionTableX[1] = _ttoi(cstr);
	m_cAAConfigIni.ReadConfigIni(L"AA", L"m_nPositionTableZ[0]", cstr);
	m_nPositionTableZ[0] = _ttoi(cstr);
	m_cAAConfigIni.ReadConfigIni(L"AA", L"m_nPositionTableZ[1]", cstr);
	m_nPositionTableZ[1] = _ttoi(cstr);
	m_cAAConfigIni.ReadConfigIni(L"AA", L"m_nPositionTableZ[2]", cstr);
	m_nPositionTableZ[2] = _ttoi(cstr);
	m_cAAConfigIni.ReadConfigIni(L"AA", L"m_nPositionX[0]", cstr);
	m_nPositionX[0] = _ttoi(cstr);
	m_cAAConfigIni.ReadConfigIni(L"AA", L"m_nPositionX[1]", cstr);
	m_nPositionX[1] = _ttoi(cstr);
	m_cAAConfigIni.ReadConfigIni(L"AA", L"m_nPositionY[0]", cstr);
	m_nPositionY[0] = _ttoi(cstr);
	m_cAAConfigIni.ReadConfigIni(L"AA", L"m_nPositionY[1]", cstr);
	m_nPositionY[1] = _ttoi(cstr);
	m_cAAConfigIni.ReadConfigIni(L"AA", L"m_nPositionZ[0]", cstr);
	m_nPositionZ[0] = _ttoi(cstr);
	m_cAAConfigIni.ReadConfigIni(L"AA", L"m_nPositionZ[1]", cstr);
	m_nPositionZ[1] = _ttoi(cstr);
	m_cAAConfigIni.ReadConfigIni(L"AA", L"m_nPositionXt[0]", cstr);
	m_nPositionXt[0] = _ttoi(cstr);
	m_cAAConfigIni.ReadConfigIni(L"AA", L"m_nPositionXt[1]", cstr);
	m_nPositionXt[1] = _ttoi(cstr);
	m_cAAConfigIni.ReadConfigIni(L"AA", L"m_nPositionYt[0]", cstr);
	m_nPositionYt[0] = _ttoi(cstr);
	m_cAAConfigIni.ReadConfigIni(L"AA", L"m_nPositionYt[1]", cstr);
	m_nPositionYt[1] = _ttoi(cstr);

	m_cAAConfigIni.ReadConfigIni(L"AA", L"m_nStepWait", cstr);
	m_nStepWait = _ttoi(cstr);

	m_cAAConfigIni.ReadConfigIni(L"AA", L"m_dCenterPer", cstr);
	m_dCenterPer = _ttof(cstr);
	m_cAAConfigIni.ReadConfigIni(L"AA", L"m_dFieldSfrDiffSpec", cstr);
	m_dFieldSfrDiffSpec = _ttof(cstr);
	m_cAAConfigIni.ReadConfigIni(L"AA", L"m_dCurrentLimit", cstr);
	m_dCurrentLimit = _ttof(cstr);
	m_cAAConfigIni.ReadConfigIni(L"AA", L"m_nDelay", cstr);
	m_nDelay = _ttof(cstr);

	m_cAAConfigIni.ReadConfigIni(L"AA", L"m_bManualFlag", cstr);
	m_bManualFlag = _ttoi(cstr);

	m_cAAConfigIni.ReadConfigIni(L"AA", L"OpenNGBaojing", cstr);
	OpenNGBaojing = _ttoi(cstr);

	m_cAAConfigIni.ReadConfigIni(L"AA", L"UseMirrorFlag", cstr);
	UseMirrorFlag = _ttoi(cstr);

	m_cAAConfigIni.ReadConfigIni(L"AA", L"OpenDongtaiFlag", cstr);
	OpenDongtaiFlag = _ttoi(cstr);

	m_cAAConfigIni.ReadConfigIni(L"AA", L"ChartOpenFlag", cstr);
	ChartOpenFlag = _ttoi(cstr);
	m_cAAConfigIni.ReadConfigIni(L"AA", L"ChartPos", cstr);
	ChartPos = _ttoi(cstr);

	m_cAAConfigIni.ReadConfigIni(L"AA", L"m_bOpenOffsetXY", cstr); m_bOpenOffsetXY = _ttoi(cstr);

	m_cAAConfigIni.ReadConfigIni(L"AA", L"m_dOffsetX[0]", cstr); m_dOffsetX[0] = _ttof(cstr);
	m_cAAConfigIni.ReadConfigIni(L"AA", L"m_dOffsetX[1]", cstr); m_dOffsetX[1] = _ttof(cstr);
	m_cAAConfigIni.ReadConfigIni(L"AA", L"m_dOffsetX[2]", cstr); m_dOffsetX[2] = _ttof(cstr);
	m_cAAConfigIni.ReadConfigIni(L"AA", L"m_dOffsetX[3]", cstr); m_dOffsetX[3] = _ttof(cstr);
	m_cAAConfigIni.ReadConfigIni(L"AA", L"m_dOffsetX[4]", cstr); m_dOffsetX[4] = _ttof(cstr);
	m_cAAConfigIni.ReadConfigIni(L"AA", L"m_dOffsetX[5]", cstr); m_dOffsetX[5] = _ttof(cstr);
	m_cAAConfigIni.ReadConfigIni(L"AA", L"m_dOffsetX[6]", cstr); m_dOffsetX[6] = _ttof(cstr);
	m_cAAConfigIni.ReadConfigIni(L"AA", L"m_dOffsetX[7]", cstr); m_dOffsetX[7] = _ttof(cstr);
	m_cAAConfigIni.ReadConfigIni(L"AA", L"m_dOffsetX[8]", cstr); m_dOffsetX[8] = _ttof(cstr);
	m_cAAConfigIni.ReadConfigIni(L"AA", L"m_dOffsetX[9]", cstr); m_dOffsetX[9] = _ttof(cstr);

	m_cAAConfigIni.ReadConfigIni(L"AA", L"m_dOffsetY[0]", cstr); m_dOffsetY[0] = _ttof(cstr);
	m_cAAConfigIni.ReadConfigIni(L"AA", L"m_dOffsetY[1]", cstr); m_dOffsetY[1] = _ttof(cstr);
	m_cAAConfigIni.ReadConfigIni(L"AA", L"m_dOffsetY[2]", cstr); m_dOffsetY[2] = _ttof(cstr);
	m_cAAConfigIni.ReadConfigIni(L"AA", L"m_dOffsetY[3]", cstr); m_dOffsetY[3] = _ttof(cstr);
	m_cAAConfigIni.ReadConfigIni(L"AA", L"m_dOffsetY[4]", cstr); m_dOffsetY[4] = _ttof(cstr);
	m_cAAConfigIni.ReadConfigIni(L"AA", L"m_dOffsetY[5]", cstr); m_dOffsetY[5] = _ttof(cstr);
	m_cAAConfigIni.ReadConfigIni(L"AA", L"m_dOffsetY[6]", cstr); m_dOffsetY[6] = _ttof(cstr);
	m_cAAConfigIni.ReadConfigIni(L"AA", L"m_dOffsetY[7]", cstr); m_dOffsetY[7] = _ttof(cstr);
	m_cAAConfigIni.ReadConfigIni(L"AA", L"m_dOffsetY[8]", cstr); m_dOffsetY[8] = _ttof(cstr);
	m_cAAConfigIni.ReadConfigIni(L"AA", L"m_dOffsetY[9]", cstr); m_dOffsetY[9] = _ttof(cstr);

}

//登录
void CSystemManager::LoginConfigIniInit()
{
	char cDir[MAX_PATH];
	m_cLoginConfigIni.GetCurrentDir((LPWSTR)cDir);
	CString cstr;
	cstr.Format(L"%s\\recipe\\", cDir);
	cstr.Append(m_sGeneralSetting.m_cstrProjectName.GetBuffer());
	cstr.Append(L"\\");
	cstr.Append(L"Login.ini");

	m_cLoginConfigIni.ConfigIniInit(cstr);
	ReadLoginConfigIni();
}

void CSystemManager::ReadLoginConfigIni()
{
	CString cstr;
	m_cLoginConfigIni.ReadConfigIni(L"LoginConfig", L"m_cPassword", cstr);
	m_sLoginInfo.m_cPassword = cstr;
	m_cLoginConfigIni.ReadConfigIni(L"LoginConfig", L"m_cUserName", cstr);
	m_sLoginInfo.m_cUserName = cstr;
}

void CSystemManager::StartCaptureThread()
{
	ProcCapture.MemProc = &CSystemManager::CaptureThread;
	UINT nThreadId;
	HANDLE hThread = (HANDLE)_beginthreadex(NULL, 0, ProcCapture.ThreadProc, (LPVOID)this, 0, &nThreadId);
	if (hThread == NULL)
	{
		return;
	}
	m_vWorkerThread.push_back(hThread);
}

unsigned int __stdcall CSystemManager::CaptureThread()
{
	int count = 0;
	CString cstrLog;
	int result = 0;
	int Cnt = 0;
	int StopFlag = 0;

	double powerRlg = 0;
	int powerFlag = 0;
	while (0 == m_nExitFlag)
	{
		Sleep(10);
		if (m_bStopCapture)
		{
			StopFlag = 0;
			m_bStartCapture = 0;
			Cnt = 0;
			Sleep(10);
			count = 0;
			if (m_nImageSource == IMG_RO_LONGO)
				SetDlgItemTextW(m_ptrMainUI->GetSafeHwnd(), IDC_STATIC_103, L"0.0");
			continue;
		}

		cstrLog.Format(L"Cap init Flag--%d", imgCap->m_bInitFlag);
		gSystemLog.DisplayLogAndSave(cstrLog.GetBuffer(), LV_EVENT);

		if (m_nImageSource == IMG_RO_LONGO)
			SetDlgItemTextW(m_ptrMainUI->GetSafeHwnd(), IDC_STATIC_103, L"0.0");

		if (imgCap->m_bInitFlag == FALSE)
		{
			gSystemLog.DisplayLogAndSave(L"Start init img device.", LV_EVENT);

			result = imgCap->init();

			cstrLog.Format(L"Cap init done.result = %d", result);
			gSystemLog.DisplayLogAndSave(cstrLog.GetBuffer(), LV_EVENT);

			if (result == TRUE)
			{
				result = imgCap->run();
				cstrLog.Format(L"Cap run done.result = %d", result);
				gSystemLog.DisplayLogAndSave(cstrLog.GetBuffer(), LV_EVENT);
			}

			if (result == TRUE)
			{
				if (m_nImageSource == IMG_DEV_CTS)
				{
					result = imgCTS.WaitForFirstFrameArrived(imgCTS.iDevID);
					if (!result)
					{
						if (Cnt > 0)
						{
							//m_bStopCapture = 1;
							SendMessage(m_ptrMainUI->GetSafeHwnd(), WM_COMMAND, IDC_BUTTON_STOP, 0);
							gSystemLog.DisplayLogAndSave(L"CTS wait first frame Error! Cap stop cap img!", LV_ERROR);
						}
						else
						{
							Cnt++;
						}
						//imgCap->stop();
						continue;
					}
					else
					{
						gSystemLog.DisplayLogAndSave(L"Cap init success!", LV_EVENT);
						imgCap->m_bInitFlag = TRUE;
					}
				}
				else
				{
					gSystemLog.DisplayLogAndSave(L"Cap init success!", LV_EVENT);
					imgCap->m_bInitFlag = TRUE;
				}
			}
			else
			{
				if (Cnt > 0)
				{
					//m_bStopCapture = 1;
					SendMessage(m_ptrMainUI->GetSafeHwnd(), WM_COMMAND, IDC_BUTTON_STOP, 0);
					gSystemLog.DisplayLogAndSave(L"Cap stop cap img!", LV_ERROR);
				}
				else
				{
					Cnt++;
				}
				//imgCap->stop();
				continue;
			}
		}
		else
		{
			int cnt = 3;
			gSystemLog.DisplayLogAndSave(L"Cap start cap img!", LV_EVENT);
			if (m_bWriteIIC){
				switch (m_nImageSource)
				{
				case IMG_DEV_CTS:
					result = imgCTS.write_iic();
					break;
				case IMG_RO_LONGO:
					result = imgRLG.write_iic();
					while (result == 0 && cnt > 0) {
						Sleep(100);
						cnt--;
						result = imgRLG.write_iic();
					}
					//result = imgRLG.write_iic();
					break;
				}
				if(result == 0)
				{
					cstrLog.Format(L"write iic error stop capture");
					gSystemLog.DisplayLogAndSave(cstrLog.GetBuffer(), LV_EVENT);
					imgCap->m_bInitFlag = FALSE;
					imgCap->stop();
					if (StopFlag > 1) {
						m_bStopCapture = 1;
						m_bStartCapture = 0;
					}
					else {
						Sleep(500);
						StopFlag++;
					}
					continue;
				}
			}
			//result = imgCTS.write_iic();
			m_bStartCapture = 1;
			count = 0;
			powerFlag = 0;
			while (m_bStopCapture/*GetStopFlag()*/ == FALSE)
			{
				result = imgCap->cap();
				if (m_bWriteIIC && count == 0) {
					count = 1;
					switch (m_nImageSource)
					{
					case IMG_DEV_CTS:
						result = imgCTS.write_iic();
						break;
					case IMG_RO_LONGO:
						result = imgRLG.write_iic();
						break;
					}
				}
				if (powerFlag == 0 && m_nImageSource == IMG_RO_LONGO) {
					powerFlag = 1;
					powerRlg = imgRLG.CurrentTest();
				}
				m_nNewCapImg = m_nNewCapImg * -1;
				Sleep(1);
				if (result != 1)
				{
					cstrLog.Format(L"error stop capture[%d]", result);
					gSystemLog.DisplayLogAndSave(cstrLog.GetBuffer(), LV_EVENT);
					m_bStopCapture = 1;
					imgCap->m_bInitFlag = FALSE;
					break;
				}
				if (m_nImageSource == IMG_RO_LONGO ) {
					cstrLog.Format(L"%.3f", powerRlg/*imgRLG.CurrentTest()*/);
					SetDlgItemTextW(m_ptrMainUI->GetSafeHwnd(), IDC_STATIC_103, cstrLog.GetBuffer());
				}
			}
			Sleep(10);
			gSystemLog.DisplayLogAndSave(L"Cap stop cap img!", LV_ERROR);
			m_bStartCapture = 0;
			imgCap->stop();
		}
	}
	return 0;
}

int CSystemManager::FindRoiHEdge(const BYTE *roi, int start_x, int start_y, int w, int h, double *edge_x, double &slope, double &offset, int &left_black)
{
	left_black = GetRoiWbLeftRightOrder(roi, w, h);
	if (left_black == -1)
	{
		return FALSE;
	}

	int index_y = 0;
	double temp_edge_x[MAX_SFR_ROI_HEIGHT] = { 0.0 };
	double temp_edge_y[MAX_SFR_ROI_HEIGHT] = { 0.0 };
	for (int y = 0; y < h; y++)
	{
		index_y = y * w;
		temp_edge_x[y] = GetBinaryImageEdgeLine(&roi[index_y], w, left_black);
		temp_edge_y[y] = (double)y;
		temp_edge_x[y] += start_x;
		temp_edge_y[y] = start_y + h - 1 - temp_edge_y[y];
	}
	int result = GetBestFitLine(temp_edge_x, temp_edge_y, h, slope, offset);

	if (edge_x != NULL)
	{
		if (result == TRUE)
		{
			for (int y = 0; y < h; y++) edge_x[y] = (double)temp_edge_y[y] / slope - (offset / slope);
		}
		else
		{
			for (int y = 0; y < h; y++) edge_x[y] = temp_edge_x[y];
		}
	}
	return result;
}

int CSystemManager::FindRoiVEdge(const BYTE *roi, int start_x, int start_y, int w, int h, double *edge_y, double &slope, double &offset, int &bottom_black)
{
	bottom_black = GetRoiWbBottomTopOrder(roi, w, h);
	if (bottom_black == -1) return FALSE;

	int index_y = 0;
	double temp_edge_x[MAX_SFR_ROI_HEIGHT] = { 0.0 };
	double temp_edge_y[MAX_SFR_ROI_HEIGHT] = { 0.0 };
	BYTE *y_line = new BYTE[h];

	for (int x = 0; x < w; x++)
	{
		for (int y = 0; y < h; y++)
		{
			y_line[y] = roi[y*w + x];
		}
		temp_edge_y[x] = GetBinaryImageEdgeLine(y_line, h, bottom_black);
		temp_edge_x[x] = (double)x;
		temp_edge_x[x] += start_x;
		temp_edge_y[x] = start_y + h - 1 - temp_edge_y[x];
	}
	int result = GetBestFitLine(temp_edge_x, temp_edge_y, w, slope, offset);
	if (edge_y != NULL && result == TRUE)
	{
		for (int x = 0; x < w; x++)
		{
			edge_y[x] = temp_edge_x[x] * (slope)+offset;
		}
	}
	delete[] y_line;
	return result;
}

int CSystemManager::GetRoiWbLeftRightOrder(const BYTE *roi, int w, int h)
{
	long	sum_left = 0, sum_right = 0;
	int		offset;
	for (int y = 0; y < h; y++)
	{
		offset = y * w;
		for (int x = 0; x < w / 4; x++)	 sum_left += roi[offset + x];
		for (int x = (w * 3) / 4; x < w; x++) sum_right += roi[y*w + x];
	}

	int devide_factor = (h*(w / 4));
	if (devide_factor <= 0) devide_factor = 1;

	int	avg_left = sum_left / devide_factor;
	int avg_right = sum_right / devide_factor;

	return (sum_left > sum_right) ? 0 : 1;
}

int CSystemManager::GetRoiWbBottomTopOrder(const BYTE *roi, int w, int h)
{
	int sum_up = 0;
	int sum_down = 0;

	for (int y = 0; y < h / 4; y++)
	{
		for (int x = 0; x < w; x++)
		{
			sum_down += roi[y*w + x];
			sum_up += roi[(h - 1 - y)*w + x];
		}
	}
	int devide_factor = (h*(w / 4));
	if (devide_factor <= 0) devide_factor = 1;

	int avg_up = sum_up / devide_factor;
	int avg_down = sum_down / devide_factor;

	return (sum_down > sum_up) ? 0 : 1;
}

double CSystemManager::GetBinaryImageEdgeLine(const BYTE *line, int num, int start_black)
{
	int white_count = 0, black_count = 0;

	long white_sum, black_sum;
	double white_mean, black_mean;

	long sum = 0;
	for (int i = 0; i < num; i++) sum += line[i];
	if (num == 0) return 0;

	double mean = (double)sum / (double)num;

	for (int j = 0; j < 2; j++)
	{
		white_sum = 0, white_count = 0;
		black_sum = 0, black_count = 0;
		for (int i = 0; i < num; i++)
		{
			if ((double)line[i] < mean)
			{
				black_sum += line[i];
				black_count++;
			}
			else
			{
				white_sum += line[i];
				white_count++;
			}
		}
		if (black_count == 0)	black_mean = 0;
		else 			    black_mean = (double)black_sum / (double)black_count;

		if (white_count == 0)	white_mean = 0;
		else  				white_mean = (double)white_sum / (double)white_count;

		mean = (black_mean + white_mean) / 2.0f;
	}

	return (double)(start_black ? black_count : white_count);
}

int CSystemManager::GetBestFitLine(const double *x, const double *y, int n, double &slope, double &offset)
{
	int result = TRUE;
	double x_mean = 0, y_mean = 0, numerator = 0, denominator = 0;

	for (int i = 0; i < n; i++)  x_mean += x[i], y_mean += y[i];

	x_mean /= (double)n;
	y_mean /= (double)n;

	for (int i = 0; i < n; i++)
	{
		numerator += y[i] * (x[i] - x_mean);
		denominator += x[i] * (x[i] - x_mean);
	}

	if (denominator == 0)
	{
		slope = 0;
		offset = 0;
		result = FALSE;
	}
	else
	{
		slope = numerator / denominator;
		offset = y_mean - x_mean * slope;
		result = TRUE;
	}
	return result;
}

void CSystemManager::DrawSFRCurve(int x_cnt)//SFR curve
{
	HWND_SFR_CURVE = GetDlgItem(m_ptrMainUI->GetSafeHwnd(), IDC_SFR_CURVE);
	int x_ratio = (int)(2560.0 / (x_cnt * 10) + 1);
	int w = x_cnt * 10 * x_ratio, h = 210;
	int begin_x = 600, end_x = 600;
	int begin_y = 25, end_y = 50;

	float factor_x = x_cnt * x_ratio*1.0f, interval_x = 1.0f;
	float factor_y = 2.0f, interval_y = 20.0f;

	int full_w = w + begin_x + end_x;
	int full_h = h + begin_y + end_y;

	int font_size = 14;
	int axis_x_offset[4] = { -200,5,-100,-20 };
	//                     横坐标平移，负向朝左；横坐标单位平移；横坐标上下，负向朝上；横坐标单位上下
	int axis_y_offset[4] = { -500,-8,-500,-15 };
	//纵坐标

	HDC memdc = pt.create(HWND_SFR_CURVE, w, h, 600, 600, 25, 50, RGB(156, 170, 193));//网格背景色,
	SetTextColor(memdc, COLOR_WHITE);
	pt.set_axis(font_size, axis_x_offset, axis_y_offset);
	pt.draw_axis_x_float(memdc, factor_x, interval_x, "cy/px", 0.0f, 0.1f);
	pt.draw_axis_y_float(memdc, factor_y, interval_y, "SFR");

	HFONT font = CreateFont(15, 0, 0, 0, FW_BLACK, 0, 0, 0, ANSI_CHARSET, 0, 0, 0, 0, L"黑体");
	HFONT old_font = (HFONT)SelectObject(memdc, font);
	TextOut(memdc, 2560, 5, L"MTF曲线", 7);//表头位置设定，左右，上下，内容，长度
	DeleteObject(font);
	font = CreateFont(font_size, 0, 0, 0, FW_BLACK, 0, 0, 0, ANSI_CHARSET, 0, 0, 0, 0, L"黑体");
	old_font = (HFONT)SelectObject(memdc, font);
	HPEN pen, old_pen;
	pen = CreatePen(PS_SOLID, 1, COLOR_BLUE);
	old_pen = (HPEN)SelectObject(memdc, pen);

	int select_num = 0;
	for (int j = 0; j < SLANTED_BW_NUM; j++)
	{
		select_num = (int)((j - 1) / 4.0 + 1);
		if (select_num == 1 && !m_bOpenFieldA) continue;

		for (int i = 0; i < 4; i++)
		{
			if (m_nRoiEnable[j][i] == FALSE) continue;
			DeleteObject(pen);
			pen = CreatePen(PS_SOLID, 1, mycolor[j][i]);
			SelectObject(memdc, pen);
			MoveToEx(memdc, begin_x, full_h - (begin_y + (int)(AMP[j][i][0] * factor_y)), NULL);

			for (int m = 1; m < x_cnt / 2; m++)
			{
				LineTo(memdc, begin_x + (int)((Freq[j][i][m] * x_cnt) * 10 * x_ratio), full_h - (begin_y + (int)(AMP[j][i][m] * factor_y)));
			}
		}
	}

	DeleteObject(pen);
	DeleteObject(font);
	pt.release(NULL, memdc);
}

void CSystemManager::SfrTest(BYTE *img, BYTE *bmp, int w, int h)
{
	//gSystemLog.DisplayLogAndSave(L"start sfr", LV_ERROR);
	int roiW;
	int roiH;
	int searchW;
	int searchH;
	int roiDistance;
	int patternSize;
	int centerX;
	int centerY;
	int centerX2;
	int centerY2;
	int edgeX[4];
	int edgeY[4];
	BYTE *bmpSfrTest = NULL;
	BYTE *bmpBin = NULL;
	BYTE *bmpP = NULL;
	int selectNum = 0;
	int findEdgeResult = TRUE;
	int oneEdgeResult = TRUE;
	double myEdge[4][500];
	int bwOrder[4] = { 0 };
	int err;
	double mtfVal = 0;
	double mtfFreq = 0;
	double crossX[2] = { 0 };
	double crossY[2] = { 0 };
	int BinaryThrehoid;
	Recognition Recog;
	int LightTotal = 0;
	int LightCnt = 0;
	int nSfrErrCode = 0;

	for (int i = 0; i < SLANTED_BW_NUM; i++)
	{
		SearchRT[i].left = m_nStartX[i];
		SearchRT[i].top = m_nStartY[i];
		SearchRT[i].right = SearchRT[i].left + m_nSearchW[(int)((i - 1) / 4.0 + 1)];
		SearchRT[i].bottom = SearchRT[i].top + m_nSearchH[(int)((i - 1) / 4.0 + 1)];

		//for (int j = 0; j < 4; j++) {
		//	if (m_nRoiEnable[i][j]) {
		//		FS.select_roi[i] = j;
		//		break;
		//	}
		//}
	}

	for (int index = 0; index < SLANTED_BW_NUM; index++)
	{
		selectNum = (int)((index - 1) / 4.0 + 1);
		if (selectNum == 1 && !m_bOpenFieldA)
		{
			continue;
		}
		BinaryThrehoid = m_nBin[index];

		roiW = m_nRoiW[selectNum];
		roiH = m_nRoiH[selectNum];
		searchW = m_nSearchW[selectNum];
		searchH = m_nSearchH[selectNum];
		roiDistance = m_nDistance[selectNum];
		patternSize = m_nPattern[selectNum];
		bmpSfrTest = new BYTE[searchW*searchH];
		bmpBin = new BYTE[searchW*searchH];

		changeImg.bmp24_to_y8(bmp, w, h, &SearchRT[index], bmpSfrTest);

		if (index == 0)
		{
			LightTotal = 0;
			LightCnt = 0;
		}
		for (int i = 0; i < searchW*searchH; i++)
		{
			bmpBin[i] = ((bmpSfrTest[i] > BinaryThrehoid) ? ABS_WHITE : ABS_BLACK);
			if (index == 0 && bmpSfrTest[i] > BinaryThrehoid)
			{
				LightTotal = LightTotal + (int)bmpSfrTest[i];
				LightCnt = LightCnt + 1;
			}
		}
		if (index == 0)
		{
			if (LightCnt == 0)
				m_nLightValue = 0;
			else
				m_nLightValue = LightTotal / LightCnt;
		}


		if (m_bDisplayFlag && m_nDisplayCnt == index)
		{
			SfrShowImg.ClearStream();
			SfrShowImg.Display(GetDlgItem(m_ptrSFRSettingDlg->GetSafeHwnd(), IDC_STATIC_DISPLAY), bmpBin, searchW, searchH, 1);
		}

		FindTarget[index] = Recog.get_target_center(bmpBin, searchW, searchH, patternSize, patternSize / 4, centerX, centerY, edgeX, edgeY);
		CenterX[index] = SearchRT[index].left + centerX;
		CenterY[index] = SearchRT[index].top + searchH - 1 - centerY;
		bmpP = NULL;
		if (centerX<0 || centerX>searchW)
		{
			FindTarget[index] = FALSE;
		}
		if (centerY<0 || centerY>searchH)
		{
			FindTarget[index] = FALSE;
		}
		if (centerX - 1 - roiDistance<0 || centerX - 1 + roiDistance>searchW)
		{
			FindTarget[index] = FALSE;
		}
		if (centerY - 1 - roiDistance<0 || centerY - 1 + roiDistance>searchH)
		{
			FindTarget[index] = FALSE;
		}
		if (FindTarget[index])
		{
			bmpP = bmpBin + (centerY - 1 - roiDistance)*searchW + centerX - roiDistance;
			Recog.get_pattern_center(bmpP, searchW, searchH, roiDistance * 2, centerX2, centerY2, edgeX, edgeY);
			if (centerX2<roiDistance / 2 || centerX2>roiDistance * 3 / 2)
			{
				FindTarget[index] = FALSE;
			}
			if (centerY2<roiDistance / 2 || centerY2>roiDistance * 3 / 2)
			{
				FindTarget[index] = FALSE;
			}
			if (FindTarget[index])
			{
				BYTE *bmpRoi = new BYTE[roiW*roiH];
				for (int i = 0; i < 4; i++)
				{
					EdgeX[index][i] = SearchRT[index].left + (centerX - roiDistance) + edgeX[i];
					EdgeY[index][i] = SearchRT[index].top + searchH - 1 - (centerY - 1 - roiDistance + edgeY[i]);
					RoiRT[index][i].left = EdgeX[index][i] - roiW / 2;
					RoiRT[index][i].top = EdgeY[index][i] - roiH / 2;
					RoiRT[index][i].right = EdgeX[index][i] + roiW / 2;
					RoiRT[index][i].bottom = EdgeY[index][i] + roiH / 2;

					if (RoiRT[index][i].left<0 || RoiRT[index][i].top<0 || RoiRT[index][i].right<0 || RoiRT[index][i].bottom<0 ||
						RoiRT[index][i].left >w || RoiRT[index][i].top >h || RoiRT[index][i].right >w || RoiRT[index][i].bottom >h)
					{
						FindTarget[index] = FALSE;
						SfrValue[index][i] = 0.0;
						continue;
					}

					changeImg.bmp24_to_y8(bmp, w, h, &RoiRT[index][i], bmpRoi);

					if (i == 1 || i == 3)
					{
						oneEdgeResult = FindRoiVEdge(bmpRoi, RoiRT[index][i].left, RoiRT[index][i].top,
							m_nRoiW[selectNum], m_nRoiH[selectNum], myEdge[i], OCSlope[index][i], OCOffset[index][i], bwOrder[i]);
						for (int searchX = 0; searchX < roiW; searchX++)
						{
							EdgeVX[index][i][searchX] = RoiRT[index][i].left + searchX;
							EdgeVY[index][i][searchX] = myEdge[i][searchX];
						}
						if (oneEdgeResult == FALSE)
							findEdgeResult = FALSE;
					}
					else
					{
						oneEdgeResult = FindRoiHEdge(bmpRoi, RoiRT[index][i].left, RoiRT[index][i].top,
							m_nRoiW[selectNum], m_nRoiH[selectNum], myEdge[i], OCSlope[index][i], OCOffset[index][i], bwOrder[i]);

						for (int searchY = 0; searchY < roiH; searchY++)
						{
							EdgeHX[index][i][searchY] = myEdge[i][searchY];
							EdgeHY[index][i][searchY] = RoiRT[index][i].top + roiH - 1 - searchY;
						}
						if (oneEdgeResult == FALSE)
							findEdgeResult = FALSE;
					}

					if (m_nRoiEnable[i] == FALSE)
						continue;
					if (i == 1 || i == 3)
					{
						roi_column_to_row(bmpRoi, roiW, roiH);
						int change = roiW;
						roiW = roiH;
						roiH = change;
					}

					err = sfr_proc(bmpRoi, roiW, roiH, 1, &m_dFreq, &SfrValue[index][i], Slope[index][i], Offset[index][i],
						ESF[index][i], LSF[index][i], Freq[index][i], AMP[index][i]);
					//SfrValue[index][i] = SfrValue[index][i] * 0.01;
#define SFR_METHOD_EX					
					if (err == FALSE && m_bUseMTF)
					{
						mtfp(Freq[index][i], AMP[index][i], m_nMtfPer, mtfVal, mtfFreq, roiW * 2);
						SfrValue[index][i] = 100.0*mtfFreq;
					}
				}
				SfrAvgValue[index] = (SfrValue[index][0] * m_nRoiEnable[index][0] + SfrValue[index][1] * m_nRoiEnable[index][1] + SfrValue[index][2] * m_nRoiEnable[index][2] + SfrValue[index][3] * m_nRoiEnable[index][3]) / (m_nRoiEnable[index][0] + m_nRoiEnable[index][1] + m_nRoiEnable[index][2] + m_nRoiEnable[index][3]);//会改变OCSlope[0][0]的值

				delete[] bmpRoi;

				if (findEdgeResult)
				{
					Recog.get_cross_xy(OCSlope[index][0], OCOffset[index][0], OCSlope[index][1], OCOffset[index][1], crossX[0], crossY[0]);
					Recog.get_cross_xy(OCSlope[index][2], OCOffset[index][2], OCSlope[index][3], OCOffset[index][3], crossX[1], crossY[1]);
					OCx[index] = (crossX[0] + crossX[1]) / 2;
					OCy[index] = (crossY[0] + crossY[1]) / 2;
				}
				else
				{
					OCx[index] = CenterX[index];
					OCy[index] = CenterY[index];
				}
				findEdgeResult = TRUE;
			}
		}
		if (index == 0)
		{
			if (m_cRfidAA.m_nId < 0 || m_cRfidAA.m_nId>18)
				m_cRfidAA.m_nId = 0;
			m_dCenterXDif = m_nTargetX + m_dOffsetX[m_cRfidAA.m_nId] - OCx[index];
			m_dCenterYDif = m_nTargetY + m_dOffsetY[m_cRfidAA.m_nId] - OCy[index];
			if (FindTarget[index] == FALSE)
			{
				m_dCenterXDif = 0;
				m_dCenterYDif = 0;//现在设定为0
			}
		}
		if (FindTarget[index] == FALSE)
		{
			//SfrAvgValue[index] = 0;//未识别到target，设定值为0
			OCx[index] = SearchRT[index].left + searchW / 2;
			OCy[index] = SearchRT[index].top + searchH / 2;
		}
		delete[] bmpBin;
		delete[] bmpSfrTest;
		//sfrtestdlg.SfrAvgValue[index] = sfrtestdlg.SfrValue[index][0] + sfrtestdlg.SfrValue[index][2];//会改变OCSlope[0][0]的值
	}
	Recog.Release();


	//get_eSfrDiff,get_eCoorDiff,draw_sfr_curve,draw_fs_curve
	DrawSFRCurve(FFT_NUM / 2);
	//sfr result
	//DrawFsCurve(aamotiondlg.m_nMaxCnt);

	int testresult = TRUE;
	//int ErrorCode[4];
	//ErrorCode[0] = 1;
	//ErrorCode[1] = 1;
	//ErrorCode[2] = 1;
	//ErrorCode[3] = 1;
	for (int index = 0; index < SLANTED_BW_NUM; index++)
	{
		selectNum = (int)((index - 1) / 4.0 + 1);
		if (index > 0 && !m_bOpenFieldA)
			break;
		if (FindTarget[index] == FALSE)
		{
			testresult = FALSE;
			//ErrorCode[0] = 0;
		}

		for (int i = 0; i < 4; i++)
		{
			if (m_nRoiEnable[index][i] == FALSE)continue;

			if (UVTestFlag == 1) {
				if (SfrValue[index][i] < m_dSpecSfrUV[selectNum])
				{
					SfrResult[index][i] = FALSE;
					testresult = FALSE;
					//ErrorCode[1] = 0;
				}
				else
				{
					SfrResult[index][i] = TRUE;
				}
			}
			else {
				if (SfrValue[index][i] < m_dSpecSfr[selectNum])
				{
					SfrResult[index][i] = FALSE;
					testresult = FALSE;
					//ErrorCode[1] = 0;
				}
				else
				{
					SfrResult[index][i] = TRUE;
				}
			}
		}
	}
	if (abs(m_dCenterXDif) > m_nSpecCenter || abs(m_dCenterYDif) > m_nSpecCenter)
	{
		testresult = FALSE;
		//ErrorCode[2] = 0;
		CenterTestResult = FALSE;
	}
	else
	{
		CenterTestResult = TRUE;
	}
	if (abs(TiltX) > m_dSpecAAAngle || abs(TiltY) > m_dSpecAAAngle)
	{
		testresult = FALSE;
		TiltTestResult = FALSE;
		//ErrorCode[3] = 0;
	}
	else
	{
		TiltTestResult = TRUE;
	}
	double Sfr_Min = SfrAvgValue[1];
	double Sfr_Max = SfrAvgValue[1];
	for (int i = 1; i < SLANTED_BW_NUM; i++)
	{
		int select = (int)((i - 1) / 4.0 + 1);
		if (select == 1 && !m_bOpenFieldA)
		{
			continue;
		}
		if (SfrAvgValue[i] > Sfr_Max)
		{
			Sfr_Max = SfrAvgValue[i];
		}
		if (SfrAvgValue[i] < Sfr_Min)
		{
			Sfr_Min = SfrAvgValue[i];
		}
	}
	m_dFieldSfrDiff = Sfr_Max - Sfr_Min;
	if (m_dFieldSfrDiff > m_dFieldSfrDiffSpec)
	{
		FieldSfrDifResult = false;
	}
	else
	{
		FieldSfrDifResult = true;
	}

	TestResult = testresult;
	//ResultCode[0] = ErrorCode[0];
	//ResultCode[1] = ErrorCode[1];
	//ResultCode[2] = ErrorCode[2];
	//ResultCode[3] = ErrorCode[3];

	//gSystemLog.DisplayLogAndSave(L"end sfr", LV_ERROR);
}

void CSystemManager::StartImageTestThread()
{
	ProcImageTest.MemProc = &CSystemManager::ImageTestThread;
	UINT nThreadId;
	HANDLE hThread = (HANDLE)_beginthreadex(NULL, 0, ProcImageTest.ThreadProc, (LPVOID)this, 0, &nThreadId);
	if (hThread == NULL)
	{
		return;
	}
	m_vWorkerThread.push_back(hThread);
}

unsigned int __stdcall CSystemManager::ImageTestThread()
{
	int count = 0;
	CString cstrLog;
	int result = 0;
	int NewImgFlag = m_nNewCapImg;
	while (0 == m_nExitFlag)
	{
		Sleep(1);
		while (m_bStopCapture || !imgCap->m_bInitFlag)
		{
			Sleep(10);

		}

		gSystemLog.DisplayLogAndSave(L"开始测试", LV_EVENT);

		if (m_nCaptureMode == LOOP_MODEL)
		{
			while (m_bStopCapture == FALSE)
			{
				if (NewImgFlag == m_nNewCapImg)
				{//没有新的图像传入，不进行计算；
					Sleep(5);
					continue;
				}
				switch (m_nImageSource)
				{
				case IMG_DEV_FILE:
					imgCap->iBmpW = imgCap->iImgWidth;
					imgCap->iBmpH = imgCap->iImgHeight;
					break;
				case IMG_DEV_CTS:
					if (m_nImageChangeMode == 0)
						memcpy(imgCap->bBmpBuf, imgCap->bImgBuf, imgCap->iImgWidth * imgCap->iImgHeight * 3);
					else if (m_nImageChangeMode == 1)
						changeImg.yuv422_to_bmp24(0, imgCap->bImgBuf, imgCap->bBmpBuf, imgCap->iImgWidth, imgCap->iImgHeight);
					else if (m_nImageChangeMode == 2)
						changeImg.yuv422_to_bmp24(1, imgCap->bImgBuf, imgCap->bBmpBuf, imgCap->iImgWidth, imgCap->iImgHeight);
					else if (m_nImageChangeMode == 3)
						changeImg.yuv422_to_bmp24(2, imgCap->bImgBuf, imgCap->bBmpBuf, imgCap->iImgWidth, imgCap->iImgHeight);
					else if (m_nImageChangeMode == 4)
						changeImg.yuv422_to_bmp24(3, imgCap->bImgBuf, imgCap->bBmpBuf, imgCap->iImgWidth, imgCap->iImgHeight);
					else if (m_nImageChangeMode == 5)
						changeImg.raw8_to_bmp24_y(0, imgCap->bImgBuf, imgCap->bBmpBuf, imgCap->iImgWidth, imgCap->iImgHeight);
					else if (m_nImageChangeMode == 6)
						changeImg.raw8_to_bmp24_y(1, imgCap->bImgBuf, imgCap->bBmpBuf, imgCap->iImgWidth, imgCap->iImgHeight);
					else if (m_nImageChangeMode == 7)
						changeImg.raw8_to_bmp24_y(2, imgCap->bImgBuf, imgCap->bBmpBuf, imgCap->iImgWidth, imgCap->iImgHeight);
					else if (m_nImageChangeMode == 8)
						changeImg.raw8_to_bmp24_y(3, imgCap->bImgBuf, imgCap->bBmpBuf, imgCap->iImgWidth, imgCap->iImgHeight);
					//changeImg.ConverttoBGRBMP(imgCap->nDataFormat, imgCap->bImgBuf, imgCap->bBmpBuf, imgCap->iImgWidth, imgCap->iImgHeight);
					imgCap->iBmpW = imgCap->iImgWidth;
					imgCap->iBmpH = imgCap->iImgHeight;
					break;
				case IMG_RO_LONGO:
					changeImg.ConverttoBGRBMP(imgCap->nDataFormat, imgCap->bImgBuf, imgCap->bBmpBuf, imgCap->iImgWidth, imgCap->iImgHeight);
					imgCap->iBmpW = imgCap->iImgWidth;
					imgCap->iBmpH = imgCap->iImgHeight;
					break;
				case IMG_CameraDS:
					memcpy(imgCap->bBmpBuf, imgCap->bImgBuf, imgCap->iImgWidth * imgCap->iImgHeight * 3);
					imgCap->iBmpW = imgCap->iImgWidth;
					imgCap->iBmpH = imgCap->iImgHeight;
					break;
				default:
					memcpy(imgCap->bBmpBuf, imgCap->bImgBuf, imgCap->iImgWidth * imgCap->iImgHeight * 3);
					break;
				}
				if (m_bMirrorX)
					{
						if (m_bMirrorY)
						{
							for (int y = 0; y < imgCap->iBmpH; y++)
							{
								for (int x = 0; x < imgCap->iBmpW; x++)
								{
									imgCap->bBmpTestBuf[y * 3 * imgCap->iBmpW + x * 3 + 0] = imgCap->bBmpBuf[y * 3 * imgCap->iBmpW + x * 3];
									imgCap->bBmpTestBuf[y * 3 * imgCap->iBmpW + x * 3 + 1] = imgCap->bBmpBuf[y * 3 * imgCap->iBmpW + x * 3 + 1];
									imgCap->bBmpTestBuf[y * 3 * imgCap->iBmpW + x * 3 + 2] = imgCap->bBmpBuf[y * 3 * imgCap->iBmpW + x * 3 + 2];
								}
							}
						}
						else
						{
							for (int y = 0; y < imgCap->iBmpH; y++)
							{
								for (int x = 0; x < imgCap->iBmpW; x++)
								{
									imgCap->bBmpTestBuf[y * 3 * imgCap->iBmpW + x * 3 + 0] = imgCap->bBmpBuf[(imgCap->iBmpH - 1 - y) * 3 * imgCap->iBmpW + x * 3];
									imgCap->bBmpTestBuf[y * 3 * imgCap->iBmpW + x * 3 + 1] = imgCap->bBmpBuf[(imgCap->iBmpH - 1 - y) * 3 * imgCap->iBmpW + x * 3 + 1];
									imgCap->bBmpTestBuf[y * 3 * imgCap->iBmpW + x * 3 + 2] = imgCap->bBmpBuf[(imgCap->iBmpH - 1 - y) * 3 * imgCap->iBmpW + x * 3 + 2];
								}
							}
						}
					}
				else
					{
						if (m_bMirrorY)
						{
							for (int y = 0; y < imgCap->iBmpH; y++)
							{
								for (int x = 0; x < imgCap->iBmpW; x++)
								{
									imgCap->bBmpTestBuf[y * 3 * imgCap->iBmpW + x * 3 + 0] = imgCap->bBmpBuf[y * 3 * imgCap->iBmpW + (imgCap->iBmpW - 1 - x) * 3];
									imgCap->bBmpTestBuf[y * 3 * imgCap->iBmpW + x * 3 + 1] = imgCap->bBmpBuf[y * 3 * imgCap->iBmpW + (imgCap->iBmpW - 1 - x) * 3 + 1];
									imgCap->bBmpTestBuf[y * 3 * imgCap->iBmpW + x * 3 + 2] = imgCap->bBmpBuf[y * 3 * imgCap->iBmpW + (imgCap->iBmpW - 1 - x) * 3 + 2];
								}
							}
						}
						else
						{
							for (int y = 0; y < imgCap->iBmpH; y++)
							{
								for (int x = 0; x < imgCap->iBmpW; x++)
								{
									imgCap->bBmpTestBuf[y * 3 * imgCap->iBmpW + x * 3 + 0] = imgCap->bBmpBuf[(imgCap->iBmpH - 1 - y) * 3 * imgCap->iBmpW + (imgCap->iBmpW - 1 - x) * 3];
									imgCap->bBmpTestBuf[y * 3 * imgCap->iBmpW + x * 3 + 1] = imgCap->bBmpBuf[(imgCap->iBmpH - 1 - y) * 3 * imgCap->iBmpW + (imgCap->iBmpW - 1 - x) * 3 + 1];
									imgCap->bBmpTestBuf[y * 3 * imgCap->iBmpW + x * 3 + 2] = imgCap->bBmpBuf[(imgCap->iBmpH - 1 - y) * 3 * imgCap->iBmpW + (imgCap->iBmpW - 1 - x) * 3 + 2];
								}
							}
						}
					}
				
				switch (m_nTestMode)
				{
				case SHOW_IMAGE:
					break;
				case SFR_TEST:
					if (LightnessFlag) LightTest(imgCap->bBmpTestBuf, imgCap->iBmpW, imgCap->iBmpH);
					SfrTest(NULL, imgCap->bBmpTestBuf, imgCap->iBmpW, imgCap->iBmpH);

					cstrLog.Format(L"%.1f", OCx[0]);
					SetDlgItemTextW(m_ptrMainUI->GetSafeHwnd(), IDC_STATIC_78, cstrLog.GetBuffer());
					cstrLog.Format(L"%.1f", OCy[0]);
					SetDlgItemTextW(m_ptrMainUI->GetSafeHwnd(), IDC_STATIC_80, cstrLog.GetBuffer());
					cstrLog.Format(L"%.3f", TiltX);
					SetDlgItemTextW(m_ptrMainUI->GetSafeHwnd(), IDC_STATIC_82, cstrLog.GetBuffer());
					cstrLog.Format(L"%.3f", TiltY);
					SetDlgItemTextW(m_ptrMainUI->GetSafeHwnd(), IDC_STATIC_63, cstrLog.GetBuffer());

					cstrLog.Format(L"%.1f", SfrAvgValue[0]);
					SetDlgItemTextW(m_ptrMainUI->GetSafeHwnd(), IDC_STATIC_84, cstrLog.GetBuffer());
					cstrLog.Format(L"%.1f", SfrAvgValue[1]);
					SetDlgItemTextW(m_ptrMainUI->GetSafeHwnd(), IDC_STATIC_86, cstrLog.GetBuffer());
					cstrLog.Format(L"%.1f", SfrAvgValue[2]);
					SetDlgItemTextW(m_ptrMainUI->GetSafeHwnd(), IDC_STATIC_96, cstrLog.GetBuffer());
					cstrLog.Format(L"%.1f", SfrAvgValue[3]);
					SetDlgItemTextW(m_ptrMainUI->GetSafeHwnd(), IDC_STATIC_99, cstrLog.GetBuffer());
					cstrLog.Format(L"%.1f", SfrAvgValue[4]);
					SetDlgItemTextW(m_ptrMainUI->GetSafeHwnd(), IDC_STATIC_101, cstrLog.GetBuffer());

					break;
				}
				NewImgFlag = m_nNewCapImg;
				m_nNewDataFlag = m_nNewDataFlag * -1;

				ShowImg.ClearStream();
				ShowImg.Display(GetDlgItem(m_ptrMainUI->GetSafeHwnd(), IDC_DISPLAY),
					imgCap->bBmpTestBuf,
					imgCap->iBmpW, imgCap->iBmpH, imgCap->iImgDepth);

				Sleep(1);
			}
		}
		else
		{
			Sleep(100);
			switch (m_nImageSource)
			{
			case IMG_DEV_FILE:
				imgCap->iBmpW = imgCap->iImgWidth;
				imgCap->iBmpH = imgCap->iImgHeight;
				break;
			case IMG_DEV_CTS:
				if (m_nImageChangeMode == 0)
					memcpy(imgCap->bBmpBuf, imgCap->bImgBuf, imgCap->iImgWidth * imgCap->iImgHeight * 3);
				else if (m_nImageChangeMode == 1)
					changeImg.yuv422_to_bmp24(0, imgCap->bImgBuf, imgCap->bBmpBuf, imgCap->iImgWidth, imgCap->iImgHeight);
				else if (m_nImageChangeMode == 2)
					changeImg.yuv422_to_bmp24(1, imgCap->bImgBuf, imgCap->bBmpBuf, imgCap->iImgWidth, imgCap->iImgHeight);
				else if (m_nImageChangeMode == 3)
					changeImg.yuv422_to_bmp24(2, imgCap->bImgBuf, imgCap->bBmpBuf, imgCap->iImgWidth, imgCap->iImgHeight);
				else if (m_nImageChangeMode == 4)
					changeImg.yuv422_to_bmp24(3, imgCap->bImgBuf, imgCap->bBmpBuf, imgCap->iImgWidth, imgCap->iImgHeight);
				else if (m_nImageChangeMode == 5)
					changeImg.raw8_to_bmp24_y(0, imgCap->bImgBuf, imgCap->bBmpBuf, imgCap->iImgWidth, imgCap->iImgHeight);
				else if (m_nImageChangeMode == 6)
					changeImg.raw8_to_bmp24_y(1, imgCap->bImgBuf, imgCap->bBmpBuf, imgCap->iImgWidth, imgCap->iImgHeight);
				else if (m_nImageChangeMode == 7)
					changeImg.raw8_to_bmp24_y(2, imgCap->bImgBuf, imgCap->bBmpBuf, imgCap->iImgWidth, imgCap->iImgHeight);
				else if (m_nImageChangeMode == 8)
					changeImg.raw8_to_bmp24_y(3, imgCap->bImgBuf, imgCap->bBmpBuf, imgCap->iImgWidth, imgCap->iImgHeight);

				imgCap->iBmpW = imgCap->iImgWidth;
				imgCap->iBmpH = imgCap->iImgHeight;
				break;
			case IMG_RO_LONGO:
				changeImg.ConverttoBGRBMP(imgCap->nDataFormat, imgCap->bImgBuf, imgCap->bBmpBuf, imgCap->iImgWidth, imgCap->iImgHeight);
				imgCap->iBmpW = imgCap->iImgWidth;
				imgCap->iBmpH = imgCap->iImgHeight;
				break;
			case IMG_CameraDS:
				memcpy(imgCap->bBmpBuf, imgCap->bImgBuf, imgCap->iImgWidth * imgCap->iImgHeight * 3);
				imgCap->iBmpW = imgCap->iImgWidth;
				imgCap->iBmpH = imgCap->iImgHeight;
				break;
			default:
				memcpy(imgCap->bBmpBuf, imgCap->bImgBuf, imgCap->iImgWidth * imgCap->iImgHeight * 3);
				break;
			}
			if (m_bMirrorX)
			{
				if (m_bMirrorY)
				{
					for (int y = 0; y < imgCap->iImgHeight; y++)
					{
						for (int x = 0; x < imgCap->iImgWidth; x++)
						{
							imgCap->bBmpTestBuf[y * 3 * imgCap->iImgWidth + x * 3] = imgCap->bBmpBuf[y * 3 * imgCap->iImgWidth + x * 3];
							imgCap->bBmpTestBuf[y * 3 * imgCap->iImgWidth + x * 3 + 1] = imgCap->bBmpBuf[y * 3 * imgCap->iImgWidth + x * 3 + 1];
							imgCap->bBmpTestBuf[y * 3 * imgCap->iImgWidth + x * 3 + 2] = imgCap->bBmpBuf[y * 3 * imgCap->iImgWidth + x * 3 + 2];
						}
					}
				}
				else
				{
					for (int y = 0; y < imgCap->iImgHeight; y++)
					{
						for (int x = 0; x < imgCap->iImgWidth; x++)
						{
							imgCap->bBmpTestBuf[y * 3 * imgCap->iImgWidth + x * 3] = imgCap->bBmpBuf[(imgCap->iImgHeight - 1 - y) * 3 * imgCap->iImgWidth + x * 3];
							imgCap->bBmpTestBuf[y * 3 * imgCap->iImgWidth + x * 3 + 1] = imgCap->bBmpBuf[(imgCap->iImgHeight - 1 - y) * 3 * imgCap->iImgWidth + x * 3 + 1];
							imgCap->bBmpTestBuf[y * 3 * imgCap->iImgWidth + x * 3 + 2] = imgCap->bBmpBuf[(imgCap->iImgHeight - 1 - y) * 3 * imgCap->iImgWidth + x * 3 + 2];
						}
					}
				}
			}
			else
			{
				if (m_bMirrorY)
				{
					for (int y = 0; y < imgCap->iImgHeight; y++)
					{
						for (int x = 0; x < imgCap->iImgWidth; x++)
						{
							imgCap->bBmpTestBuf[y * 3 * imgCap->iImgWidth + x * 3] = imgCap->bBmpBuf[y * 3 * imgCap->iImgWidth + (imgCap->iImgWidth - 1 - x) * 3];
							imgCap->bBmpTestBuf[y * 3 * imgCap->iImgWidth + x * 3 + 1] = imgCap->bBmpBuf[y * 3 * imgCap->iImgWidth + (imgCap->iImgWidth - 1 - x) * 3 + 1];
							imgCap->bBmpTestBuf[y * 3 * imgCap->iImgWidth + x * 3 + 2] = imgCap->bBmpBuf[y * 3 * imgCap->iImgWidth + (imgCap->iImgWidth - 1 - x) * 3 + 2];
						}
					}
				}
				else
				{
					for (int y = 0; y < imgCap->iImgHeight; y++)
					{
						for (int x = 0; x < imgCap->iImgWidth; x++)
						{
							imgCap->bBmpTestBuf[y * 3 * imgCap->iImgWidth + x * 3] = imgCap->bBmpBuf[(imgCap->iImgHeight - 1 - y) * 3 * imgCap->iImgWidth + (imgCap->iImgWidth - 1 - x) * 3];
							imgCap->bBmpTestBuf[y * 3 * imgCap->iImgWidth + x * 3 + 1] = imgCap->bBmpBuf[(imgCap->iImgHeight - 1 - y) * 3 * imgCap->iImgWidth + (imgCap->iImgWidth - 1 - x) * 3 + 1];
							imgCap->bBmpTestBuf[y * 3 * imgCap->iImgWidth + x * 3 + 2] = imgCap->bBmpBuf[(imgCap->iImgHeight - 1 - y) * 3 * imgCap->iImgWidth + (imgCap->iImgWidth - 1 - x) * 3 + 2];
						}
					}
				}
			}
			switch (m_nTestMode)
			{
			case SHOW_IMAGE:
				break;
			case SFR_TEST:
				if (LightnessFlag) LightTest(imgCap->bBmpTestBuf, imgCap->iBmpW, imgCap->iBmpH);
				SfrTest(NULL, imgCap->bBmpTestBuf, imgCap->iImgWidth, imgCap->iImgHeight);
				break;
			}
			NewImgFlag = m_nNewCapImg;
			m_nNewDataFlag = m_nNewDataFlag * -1;
			ShowImg.ClearStream();
			ShowImg.Display(GetDlgItem(m_ptrMainUI->GetSafeHwnd(), IDC_DISPLAY),
				imgCap->bBmpTestBuf,
				imgCap->iImgWidth, imgCap->iImgHeight, imgCap->iImgDepth);

			//m_bStopCapture = 1;
			SendMessage(m_ptrMainUI->GetSafeHwnd(), WM_COMMAND, IDC_BUTTON_STOP, 0);
			imgCap->m_bInitFlag = FALSE;

		}
		Sleep(10);
	}
	gSystemLog.DisplayLogAndSave(L"Exit thread 4", LV_EVENT);
	return 0;
}

void CSystemManager::DrawTestResultChart(HDC memdc)
{
	char buffer[100] = { 0 };
	HPEN pen = CreatePen(PS_SOLID, 2, COLOR_GHOST_WHITE);
	HPEN old_pen = (HPEN)SelectObject(memdc, pen);

	HFONT hfont = CreateFont(24, 0, 0, 0, 20, 0, 0, 0, ANSI_CHARSET, 3, 2, 1, VARIABLE_PITCH | FF_ROMAN, L"黑体");
	HFONT old_font = (HFONT)SelectObject(memdc, hfont);
	SetTextColor(memdc, COLOR_BLUE);
	int select_num = 0;
	for (int i = 0; i < SLANTED_BW_NUM; i++)
	{
		select_num = (int)((i - 1) / 4.0 + 1);
		if (select_num == 1 && !m_bOpenFieldA) continue;
		Output::DrawCrossline(memdc, SearchRT[i].left + m_nSearchW[select_num] / 2,
			SearchRT[i].top + m_nSearchH[select_num] / 2, m_nSearchW[select_num],
			m_nSearchH[select_num]);
		Rectangle(memdc, SearchRT[i].left, SearchRT[i].top, SearchRT[i].right, SearchRT[i].bottom);

		sprintf(buffer, "#%d[%.1f]", i, SfrAvgValue[i]);
		TextOutA(memdc, SearchRT[i].left, SearchRT[i].top, buffer, strlen(buffer));
	}

	DeleteObject(pen);
	pen = CreatePen(PS_SOLID, 2, COLOR_YELLOW);
	old_pen = (HPEN)SelectObject(memdc, pen);
	for (int i = 0; i < SLANTED_BW_NUM; i++)
	{
		select_num = (int)((i - 1) / 4.0 + 1);
		if (select_num == 1 && !m_bOpenFieldA) continue;

		Output::DrawCrossline(memdc, (int)OCx[i], (int)OCy[i], 20, 20);
	}

	DeleteObject(pen);
	pen = CreatePen(PS_SOLID, 2, COLOR_RED);
	old_pen = (HPEN)SelectObject(memdc, pen);
	for (int i = 0; i < SLANTED_BW_NUM; i++)
	{
		select_num = (int)((i - 1) / 4.0 + 1);
		if (select_num == 1 && !m_bOpenFieldA) continue;
		Output::DrawCrossline(memdc, (int)CenterX[i], (int)CenterY[i], 20, 20);

	}

	DeleteObject(pen);
	pen = CreatePen(PS_SOLID, 2, COLOR_YELLOW);
	old_pen = (HPEN)SelectObject(memdc, pen);
	if (m_bDrawLine)
	{
		Output::DrawCrossline(memdc, (int)(imgCap->iImgWidth / 2), (int)(imgCap->iImgHeight / 2), imgCap->iImgWidth, imgCap->iImgHeight);
	}

	DeleteObject(pen);
	RECT myrt;
	pen = CreatePen(PS_SOLID, 2, COLOR_YELLOW);
	old_pen = (HPEN)SelectObject(memdc, pen);

	for (int j = 0; j < SLANTED_BW_NUM; j++)
	{
		select_num = (int)((j - 1) / 4.0 + 1);
		if (select_num == 1 && !m_bOpenFieldA) continue;
		else if (FindTarget[j] == FALSE)	continue;

		for (int i = 0; i < 4; i++)
		{
			if (m_nRoiEnable[j][i] == FALSE) continue;
			DeleteObject(pen);
			pen = CreatePen(PS_SOLID, 1, ((SfrResult[j][i] == TRUE) ? COLOR_DODGER_BLUE : COLOR_RED));
			SelectObject(memdc, pen);

			Rectangle(memdc, RoiRT[j][i].left, RoiRT[j][i].top, RoiRT[j][i].right, RoiRT[j][i].bottom);
			SetTextColor(memdc, ((SfrResult[j][i] == TRUE) ? COLOR_DODGER_BLUE : COLOR_RED));

			sprintf(buffer, "%.1f", SfrValue[j][i]);
			if (i == 0)
			{
				TextOutA(memdc, RoiRT[j][i].left, RoiRT[j][i].bottom + 10, buffer, strlen(buffer));
			}
			else if (i == 1)
			{
				TextOutA(memdc, RoiRT[j][i].right - 10, RoiRT[j][i].bottom, buffer, strlen(buffer));
			}
			else if (i == 2)
			{
				TextOutA(memdc, RoiRT[j][i].right + 2, RoiRT[j][i].top, buffer, strlen(buffer));
			}
			else if (i == 3)
			{
				TextOutA(memdc, RoiRT[j][i].left - 20, RoiRT[j][i].bottom, buffer, strlen(buffer));
			}
			HBRUSH mybrush = CreateSolidBrush(mycolor[j][i]);
			HBRUSH old_brush = (HBRUSH)SelectObject(memdc, (HBRUSH)mybrush);

			myrt.left = RoiRT[j][i].left;
			myrt.top = RoiRT[j][i].top;
			myrt.right = myrt.left + m_nRoiW[0] / 5;
			myrt.bottom = myrt.top + m_nRoiH[0] / 5;
			FillRect(memdc, &myrt, mybrush);
			DeleteObject(mybrush);
			SelectObject(memdc, old_brush);
		}
		sprintf(buffer, "(%.1f, %.1f)[%.1f]", OCx[j], OCy[j], (atan(OCSlope[j][0])*180.0 / PI));
		TextOutA(memdc, SearchRT[j].left, SearchRT[j].top - 20, buffer, strlen(buffer));
	}

	if (LightnessFlag) {
		for (int i = 0; i < 5; i++) {
			if (LightValueResult[i] == TRUE) {
				SelectObject(memdc, (HPEN)old_pen);
				DeleteObject(pen);
				pen = CreatePen(PS_SOLID, 1, COLOR_GREEN);
				old_pen = (HPEN)SelectObject(memdc, pen);
				SetTextColor(memdc, COLOR_BLUE);
			}
			else {
				SelectObject(memdc, (HPEN)old_pen);
				DeleteObject(pen);
				pen = CreatePen(PS_SOLID, 1, COLOR_RED);
				old_pen = (HPEN)SelectObject(memdc, pen);
				SetTextColor(memdc, COLOR_RED);
			}
			sprintf(buffer, "#%d[%.1f]", i, LightValue[i]);
			TextOutA(memdc, LightX[i] + LightRoiW, LightY[i], buffer, strlen(buffer));
			Rectangle(memdc, LightX[i], LightY[i], LightX[i] + LightRoiW, LightY[i] + LightRoiH);
		}
	}


	DeleteObject(hfont);
	//char buffer[50];
	hfont = CreateFont(20, 0, 0, 0, 20, 0, 0, 0, ANSI_CHARSET, 3, 2, 1, VARIABLE_PITCH | FF_ROMAN, L"黑体");
	old_font = (HFONT)SelectObject(memdc, hfont);
	if (TestResult)
	{
		SetTextColor(memdc, COLOR_GREEN);
		sprintf(buffer, "测试总结果: %s", "Pass");
		TextOutA(memdc, 20, 30, buffer, strlen(buffer));
	}
	else
	{
		SetTextColor(memdc, COLOR_RED);
		sprintf(buffer, "测试总结果: %s", "Fail");
		TextOutA(memdc, 20, 30, buffer, strlen(buffer));
	}

	SetTextColor(memdc, COLOR_GREEN);
	sprintf(buffer, "[%d]", m_nLightValue);
	TextOutA(memdc, 20, 5, buffer, strlen(buffer));

	if (CenterTestResult && FindTarget[0])
	{
		SetTextColor(memdc, COLOR_GREEN);
		sprintf(buffer, "中心测试: %.1f,%.1f", OCx[0], OCy[0]);
		TextOutA(memdc, 20, 55, buffer, strlen(buffer));
	}
	else
	{
		SetTextColor(memdc, COLOR_RED);
		sprintf(buffer, "中心测试: %.1f,%.1f", OCx[0], OCy[0]);
		TextOutA(memdc, 20, 55, buffer, strlen(buffer));
	}
	if (TiltTestResult)
	{
		SetTextColor(memdc, COLOR_GREEN);
		sprintf(buffer, "角度调整测试: %.3f, %.3f;", TiltX, TiltY);
		TextOutA(memdc, 20, 80, buffer, strlen(buffer));
	}
	else
	{
		SetTextColor(memdc, COLOR_RED);
		sprintf(buffer, "角度调整测试: %.3f, %.3f", TiltX, TiltY);
		TextOutA(memdc, 20, 80, buffer, strlen(buffer));
	}
	//if (FieldSfrDifResult)
	//{
	//	SetTextColor(memdc, COLOR_GREEN);
	//	sprintf(buffer, "四周清晰度差异: %.3f", m_dFieldSfrDiff);
	//	TextOutA(memdc, 20, 105, buffer, strlen(buffer));
	//}
	//else
	//{
	//	SetTextColor(memdc, COLOR_RED);
	//	sprintf(buffer, "四周清晰度差异: %.3f", m_dFieldSfrDiff);
	//	TextOutA(memdc, 20, 105, buffer, strlen(buffer));
	//}
	DeleteObject(hfont);
	DeleteObject(pen);
}

void CSystemManager::RS232ConfigIniInit()
{
	char cDir[MAX_PATH];
	m_cRS232ConfigIni.GetCurrentDir((LPWSTR)cDir);
	CString cstr;
	cstr.Format(L"%s\\recipe\\", cDir);
	cstr.Append(m_sGeneralSetting.m_cstrProjectName.GetBuffer());
	cstr.Append(L"\\");
	cstr.Append(L"RS232.ini");

	m_cRS232ConfigIni.ConfigIniInit(cstr);
	ReadRS232ConfigIni();
}

void CSystemManager::ReadRS232ConfigIni()
{
	CString cstr;
	m_cRS232ConfigIni.ReadConfigIni(L"RS232", L"m_nComNo2", cstr);
	m_nComNo2 = _ttoi(cstr);

	m_cRS232ConfigIni.ReadConfigIni(L"RS232", L"m_nComPort2", cstr);
	m_nComPort2 = _ttoi(cstr);

	m_cRS232ConfigIni.ReadConfigIni(L"RS232", L"m_bAutoFlag_RS232", cstr);
	m_bAutoFlag_RS232 = _ttoi(cstr);

	m_cRS232ConfigIni.ReadConfigIni(L"RS232", L"m_nPassRfidFlag", cstr);
	m_nPassRfidFlag = _ttoi(cstr);

	m_cRS232ConfigIni.ReadConfigIni(L"Power", L"m_nPowerPort", cstr);
	m_nPowerPort = _ttoi(cstr);

	m_cRS232ConfigIni.ReadConfigIni(L"Power", L"m_nPowerBaudrate", cstr);
	m_nPowerBaudrate = _ttoi(cstr);

	m_cRS232ConfigIni.ReadConfigIni(L"Power", L"m_nPowerFlag", cstr);
	m_nPowerFlag = _ttoi(cstr);

	m_cRS232ConfigIni.ReadConfigIni(L"Power", L"current_limit[0]", cstr);
	current_limit[0] = _ttof(cstr);

	m_cRS232ConfigIni.ReadConfigIni(L"Power", L"current_limit[1]", cstr);
	current_limit[1] = _ttof(cstr);

	//m_cRS232ConfigIni.ReadConfigIni(L"Power", L"current_limit[2]", cstr);
	//current_limit[2] = _ttof(cstr);

	m_cRS232ConfigIni.ReadConfigIni(L"Power", L"voltage_val[0]", cstr);
	voltage_val[0] = _ttof(cstr);

	m_cRS232ConfigIni.ReadConfigIni(L"Power", L"voltage_val[1]", cstr);
	voltage_val[1] = _ttof(cstr);

	//m_cRS232ConfigIni.ReadConfigIni(L"Power", L"voltage_val[2]", cstr);
	//voltage_val[2] = _ttof(cstr);

}

void CSystemManager::StartRS232LinkThread()
{
	ProcRS232Link.MemProc = &CSystemManager::RS232LinkThread;
	UINT nThreadId;
	HANDLE hTemp = (HANDLE)_beginthreadex(NULL, 0, ProcRS232Link.ThreadProc, (LPVOID)this, 0, &nThreadId);
	if (hTemp == NULL)
	{
		return;
	}
}

unsigned int __stdcall CSystemManager::RS232LinkThread()
{
	int err = 0;
	while (0 == m_nExitFlag)
	{
		Sleep(500);
		if (!m_bAutoFlag_RS232)
			continue;

		if (m_cRfidComm2.get_com_port() == NULL)
		{
			err = m_cRfidComm2.com_open(m_nComNo2, m_nComPort2, EVENPARITY);
			if (err != 1)
				Com2ConnectFlag = 0;
			else
				Com2ConnectFlag = 1;
		}
		SetDlgItemTextW(m_ptrMainUI->GetSafeHwnd(), IDC_STATIC_44, L"RFID");

		if (m_cRfidComm2.get_com_port() == NULL)
		{
			m_bRfidLinkFlag = 0;
		}
		else
		{
			m_bRfidLinkFlag = 1;
		}

	}
	gSystemLog.DisplayLogAndSave(L"Exit thread 8", LV_EVENT);
	return 0;
}

void CSystemManager::StartPowerLinkThread()
{
	ProcPowerLink.MemProc = &CSystemManager::PowerLinkThread;
	UINT nThreadId;
	HANDLE hTemp = (HANDLE)_beginthreadex(NULL, 0, ProcPowerLink.ThreadProc, (LPVOID)this, 0, &nThreadId);
	if (hTemp == NULL)
	{
		return;
	}
}

unsigned int __stdcall CSystemManager::PowerLinkThread()
{
	char cmd[20] = { 0 };
	float current = 0.0f;
	CString cstr;
	while (0 == m_nExitFlag)
	{
		Sleep(200);
		if (m_nPowerLinked != TRUE && m_nPowerFlag == TRUE)
		{
			m_cPower.com_close();
			m_nPowerLinked = m_cPower.com_open(m_nPowerPort, m_nPowerBaudrate);

			if (m_nPowerLinked == TRUE)
			{
				m_cPower.send_data((BYTE *)"SYST:REM\n", 9); //Get control of ps

				m_cPower.send_data((BYTE *)"INST CH1\n", 9); //select ch1
				sprintf(cmd, "VOLT %.2f\n", voltage_val[0]);
				m_cPower.send_data((BYTE *)cmd, strlen(cmd));
				sprintf(cmd, "CURR %.3f\n", current_limit[0]);
				m_cPower.send_data((BYTE *)cmd, strlen(cmd));
				m_cPower.send_data((BYTE *)"CHAN:OUTP 1\n", 12);

				m_cPower.send_data((BYTE *)"INST CH2\n", 9); //select ch2
				sprintf(cmd, "VOLT %.2f\n", voltage_val[1]);
				m_cPower.send_data((BYTE *)cmd, strlen(cmd));
				sprintf(cmd, "CURR %.3f\n", current_limit[1]);
				m_cPower.send_data((BYTE *)cmd, strlen(cmd));
				m_cPower.send_data((BYTE *)"CHAN:OUTP 1\n", 12);

				//m_cPower.send_data((BYTE *)"INST CH3\n", 9); //select ch3
				//sprintf(cmd, "VOLT %.2f\n", voltage_val[2]);
				//m_cPower.send_data((BYTE *)cmd, strlen(cmd));
				//sprintf(cmd, "CURR %.3f\n", current_limit[2]);
				//m_cPower.send_data((BYTE *)cmd, strlen(cmd));
				//m_cPower.send_data((BYTE *)"CHAN:OUTP 1\n", 12);
			}
			else
			{
				break;
			}
		}
		else if (m_nPowerLinked == TRUE)
		{
			char feedback1[100] = { 0 };
			char feedback2[100] = { 0 };
			m_cPower.send_data((BYTE *)"INST CH1\n", 9); //select ch1
			m_cPower.send_data_feedback((BYTE *)"MEAS:CURR?\n", 11, (BYTE *)feedback1, sizeof(feedback1));
			m_fPowerCurrentVal[0] = atof(feedback1);

			m_cPower.send_data((BYTE *)"INST CH2\n", 9); //select ch2
			m_cPower.send_data_feedback((BYTE *)"MEAS:CURR?\n", 11, (BYTE *)feedback2, sizeof(feedback2));
			m_fPowerCurrentVal[1] = atof(feedback2);
		}
		SetDlgItemTextW(m_ptrMainUI->GetSafeHwnd(), IDC_STATIC_94, L"电流");//程控电源
		cstr.Format(L"%.3f", m_fPowerCurrentVal[0]);
		SetDlgItemTextW(m_ptrMainUI->GetSafeHwnd(), IDC_STATIC_90, cstr.GetBuffer());
		if(m_nImageSource != IMG_RO_LONGO)
			SetDlgItemTextW(m_ptrMainUI->GetSafeHwnd(), IDC_STATIC_103, cstr.GetBuffer());
		cstr.Format(L"%.3f", m_fPowerCurrentVal[1]);
		SetDlgItemTextW(m_ptrMainUI->GetSafeHwnd(), IDC_STATIC_91, cstr.GetBuffer());
	}
	return 0;
}


void CSystemManager::LightConfigIniInit()
{
	char cDir[MAX_PATH];
	m_cLightConfigIni.GetCurrentDir((LPWSTR)cDir);
	CString cstr;
	cstr.Format(L"%s\\recipe\\", cDir);
	cstr.Append(m_sGeneralSetting.m_cstrProjectName.GetBuffer());
	cstr.Append(L"\\");
	cstr.Append(L"Light.ini");

	m_cLightConfigIni.ConfigIniInit(cstr);
	ReadLightConfigIni();
}

void CSystemManager::ReadLightConfigIni()
{
	CString cstr;
	m_cLightConfigIni.ReadConfigIni(L"Light", L"LightnessFlag", cstr); LightnessFlag = _ttoi(cstr);
	m_cLightConfigIni.ReadConfigIni(L"Light", L"LightX[0]", cstr); LightX[0] = _ttoi(cstr);
	m_cLightConfigIni.ReadConfigIni(L"Light", L"LightX[1]", cstr); LightX[1] = _ttoi(cstr);
	m_cLightConfigIni.ReadConfigIni(L"Light", L"LightX[2]", cstr); LightX[2] = _ttoi(cstr);
	m_cLightConfigIni.ReadConfigIni(L"Light", L"LightX[3]", cstr); LightX[3] = _ttoi(cstr);
	m_cLightConfigIni.ReadConfigIni(L"Light", L"LightX[4]", cstr); LightX[4] = _ttoi(cstr);
	m_cLightConfigIni.ReadConfigIni(L"Light", L"LightY[0]", cstr); LightY[0] = _ttoi(cstr);
	m_cLightConfigIni.ReadConfigIni(L"Light", L"LightY[1]", cstr); LightY[1] = _ttoi(cstr);
	m_cLightConfigIni.ReadConfigIni(L"Light", L"LightY[2]", cstr); LightY[2] = _ttoi(cstr);
	m_cLightConfigIni.ReadConfigIni(L"Light", L"LightY[3]", cstr); LightY[3] = _ttoi(cstr);
	m_cLightConfigIni.ReadConfigIni(L"Light", L"LightY[4]", cstr); LightY[4] = _ttoi(cstr);
	m_cLightConfigIni.ReadConfigIni(L"Light", L"LightSpec[0]", cstr); LightSpec[0] = _ttoi(cstr);
	m_cLightConfigIni.ReadConfigIni(L"Light", L"LightSpec[1]", cstr); LightSpec[1] = _ttoi(cstr);
	m_cLightConfigIni.ReadConfigIni(L"Light", L"LightSpec[2]", cstr); LightSpec[2] = _ttoi(cstr);
	m_cLightConfigIni.ReadConfigIni(L"Light", L"LightSpec[3]", cstr); LightSpec[3] = _ttoi(cstr);
	m_cLightConfigIni.ReadConfigIni(L"Light", L"LightSpec[4]", cstr); LightSpec[4] = _ttoi(cstr);
	m_cLightConfigIni.ReadConfigIni(L"Light", L"LightRoiW", cstr); LightRoiW = _ttoi(cstr);
	m_cLightConfigIni.ReadConfigIni(L"Light", L"LightRoiH", cstr); LightRoiH = _ttoi(cstr);

}

void get_avg_rgb(BYTE *roi_bmp, int roi_w, int roi_h, float *avg_r, float *avg_g, float *avg_b)
{
	float sum_r = 0, sum_g = 0, sum_b = 0;
	float r = 0.0f, g = 0.0f, b = 0.0f;
	for (int j = 0; j < roi_h; j++) {
		for (int i = 0; i < roi_w; i++) {

			b = roi_bmp[j*roi_w * 3 + i * 3];
			g = roi_bmp[j*roi_w * 3 + i * 3 + 1];
			r = roi_bmp[j*roi_w * 3 + i * 3 + 2];

			sum_b += b;
			sum_g += g;
			sum_r += r;


		}
	}

	r = (float)sum_r / (roi_w*roi_h);
	b = (float)sum_b / (roi_w*roi_h);
	g = (float)sum_g / (roi_w*roi_h);

	*avg_r = r;
	*avg_g = g;
	*avg_b = b;

}
void get_color_hsl(BYTE *roi_bmp, int roi_w, int roi_h, float* H, float* S, float* L) {
	float r, b, g;
	get_avg_rgb(roi_bmp, roi_w, roi_h, &r, &g, &b);
	float h, s, l;

	float min = r;
	if (g < min)
		min = g;
	if (b < min)
		min = b;
	float max = r;
	float f1 = 0.0;
	float f2 = g - b;
	if (g > max) {
		max = g;
		f1 = 120.0;
		f2 = b - r;
	}
	if (b > max) {
		max = b;
		f1 = 240.0;
		f2 = r - g;
	}
	float dif = max - min;
	float sum = max + min;
	l = 120 * (sum / 255);//计算亮度，定义为 0~240 
	if (dif == 0) {
		h = 0.0;
		s = 0.0;
	}
	else if (l < 120) {
		s = 255.0 * dif / sum;
	}
	else {
		s = 255.0 * dif / (510.0 - sum);
	}

	h = (f1 + 60.0 * f2 / dif);
	if (h < 0.0) {
		h += 360.0;
	}
	if (h >= 360.0) {
		h -= 360.0;
	}

	*H = h;
	*S = s;
	*L = l;

}

int CSystemManager::LightTest(BYTE *bmp, int imgW, int imgH) {
	RECT rt;
	int TestResult = TRUE;
	int roi_size = LightRoiW * LightRoiH * 3;
	BYTE *bmpRoi = new BYTE[roi_size];
	float ColorH[5], ColorS[5];
	int index = 0;
	for (int i = 0; i < 5; i++) {
		for (int y = 0; y < LightRoiH; y++) {
			index = (imgH - LightY[i] - LightRoiH + y)*imgW * 3 + LightX[i] * 3;
			memcpy(bmpRoi + y * LightRoiW * 3, bmp + index, LightRoiW * 3);
		}

		get_color_hsl(bmpRoi, LightRoiW, LightRoiH, &ColorH[i], &ColorS[i], &LightValue[i]);

		if (LightValue[i] < LightSpec[i]) {
			TestResult = FALSE;
			LightValueResult[i] = FALSE;
		}
		else {
			LightValueResult[i] = TRUE;
		}
	}
	LightTestResult = TestResult;
	delete[] bmpRoi;
	return TestResult;
}