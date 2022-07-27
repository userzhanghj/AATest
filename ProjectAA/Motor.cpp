#include "pch.h"
#include "Motor.h"
#include "SystemManager.h"
#include "ConfigFileManager.h"

extern CSystemLog     gSystemLog;
extern CSystemManager    gSystemMgr;
extern CConfigFileManager gConfigMgr;

CMotor::CMotor()
{
	
}


CMotor::~CMotor()
{
}

bool CMotor::CardInit()
{
	gSystemLog.DisplayLogAndSave(L"开始初始化运动控制卡", LV_EVENT);
	WORD My_CardNum;      //定义卡数
	WORD My_CardList[8];   //定义卡号数组
	DWORD My_CardTypeList[8];   //定义各卡类型
	if (dmc_board_init() <= 0)      //控制卡的初始化操作
		AfxMessageBox(L"初始化控制卡失败");

	dmc_get_CardInfList(&My_CardNum, My_CardTypeList, My_CardList);    //获取正在使用的卡号列表

	TCHAR  moduleFileName[MAX_PATH];
	::GetModuleFileName(NULL, moduleFileName, MAX_PATH);
	(_tcsrchr(moduleFileName, _T('\\')))[1] = 0;
	CString cstrPath = moduleFileName;
	cstrPath.Append(_T("Recipe\\"));
	if (!_wmkdir(cstrPath))
	{

	}
	cstrPath.Append(_T("LTDMC_0.ini"));

	USES_CONVERSION;
	char* c_strPath = T2A(cstrPath);
	int nErrCode = dmc_download_configfile(0, c_strPath);

	if (nErrCode)
	{
		CString cstrLog;
		cstrLog.Format(L"Device DMC3800 initialization error ! ERROR_CODE2=%d\n", nErrCode);
		gSystemLog.DisplayLogAndSave(cstrLog.GetBuffer(), LV_ERROR);
		dmc_board_close();
		return false;
	}
	gSystemLog.DisplayLogAndSave(L"DMC Init OK", LV_EVENT);
	return true;
}

void CMotor::ServoOn()
{
	int nErrCode = dmc_write_sevon_pin(gSystemMgr.m_nCard, m_sAxisSetting.m_nAxisId, OFF);
	if (nErrCode)
	{
		CString cstrLog = _utils::Unicode2TChar(m_sAxisSetting.m_wstrAxisName);
		cstrLog.AppendFormat(L"Servo On Error,error code=%d\n", nErrCode);
		gSystemLog.DisplayLogAndSave(cstrLog.GetBuffer(), LV_ERROR);
		return;
	}
	CString cstrLog;
	cstrLog.Format(L"axis:%d,servo on!", m_sAxisSetting.m_nAxisId);
	gSystemLog.DisplayLogAndSave(cstrLog.GetBuffer(), LV_INVALID);
}

void CMotor::ServoOff()
{
	int nErrCode = dmc_write_sevon_pin(gSystemMgr.m_nCard, m_sAxisSetting.m_nAxisId, ON);
	if (nErrCode)
	{
		CString cstrLog = _utils::Unicode2TChar(m_sAxisSetting.m_wstrAxisName);
		cstrLog.AppendFormat(L"Servo On Error,error code=%d\n", nErrCode);
		gSystemLog.DisplayLogAndSave(cstrLog.GetBuffer(), LV_ERROR);
	}
	CString cstrLog;
	cstrLog.Format(L"axis:%d,servo off!", m_sAxisSetting.m_nAxisId);
	gSystemLog.DisplayLogAndSave(cstrLog.GetBuffer(), LV_INVALID);
}

void CMotor::ResetAlarm()
{
	int nErrCode = dmc_set_alm_mode(gSystemMgr.m_nCard, m_sAxisSetting.m_nAxisId, 0, 1, 0);
	if (nErrCode)
	{
		CString cstrLog = _utils::Unicode2TChar(m_sAxisSetting.m_wstrAxisName);
		cstrLog.AppendFormat(L"Alarm Reset Error,error code=%d\n", nErrCode);
		gSystemLog.DisplayLogAndSave(cstrLog.GetBuffer(), LV_ERROR);
	}
}


void CMotor::HomeSearch(int nDirection)
{
	m_nMotorDirection = nDirection;
	StartMotorHomeThread();
}

void CMotor::HomeSearch2(int nDirection)
{
	m_nMotorDirection = nDirection;
	StartMotorHomeThread2();
}

void CMotor::StopMove()
{
	StopMotorMoveThread();
}

void CMotor::MotorMoveStep()
{
	StartMotorStepMoveThread();
}

void CMotor::MotorMoveAbsEnc()
{
	StartMotorAbsEncMoveThread();
}

void CMotor::MotorMoveContinue(int nDirection)
{
	m_nMotorDirection = nDirection;
	StartMotorContinueMoveThread();
}

void CMotor::StartMotorHomeThread()
{
	m_bHomed = false;
	ProcHome.MemProc = &CMotor::MotorHomeThread;
	UINT nThreadId;
	HANDLE hThread = (HANDLE)_beginthreadex(NULL, 0, ProcHome.ThreadProc, (LPVOID)this, 0, &nThreadId);
	if (hThread == NULL)
	{
		return;
	}
}

unsigned int __stdcall CMotor::MotorHomeThread()
{

	int nErrcode = 0;
	BYTE	 HomeMode, EZcount;
	HomeMode = 6;
	EZcount = 0;

	if (m_sAxisSetting.m_nAxisId < 3)
	{
		nErrcode = dmc_write_sevon_pin(gSystemMgr.m_nCard, m_sAxisSetting.m_nAxisId, OFF);
		Sleep(500);
	}
	dmc_set_profile_unit(gSystemMgr.m_nCard, m_sAxisSetting.m_nAxisId, m_sAxisSetting.m_nStartSpeed, m_sAxisSetting.m_nSpeedHome, m_sAxisSetting.m_nSpeedAcc, m_sAxisSetting.m_nSpeedAcc, 0);

	nErrcode = dmc_vmove(gSystemMgr.m_nCard, m_sAxisSetting.m_nAxisId, m_nMotorDirection);
	if (nErrcode != 0)
	{
		if (m_nMotorDirection == MOVE_DIRECTION_REVERSE && m_bNEL == 1) {

		}
		else if (m_nMotorDirection == MOVE_DIRECTION_FORWARD && m_bPEL == 1) {

		}
		else {
			CString cstrLog = _utils::Unicode2TChar(m_sAxisSetting.m_wstrAxisName);
			cstrLog.AppendFormat(L" dmc_vmove Move Error,error code=%d", nErrcode);
			gSystemLog.DisplayLogAndSave(cstrLog.GetBuffer(), LV_ERROR);
			return 0;
		}
	}
	DWORD status = dmc_check_done(gSystemMgr.m_nCard, m_sAxisSetting.m_nAxisId);           //判断当前轴状态
	int timeout = 1000;
	while (status != 1)
	{
		timeout--;
		Sleep(50);
		status = dmc_check_done(gSystemMgr.m_nCard, m_sAxisSetting.m_nAxisId);
		if (timeout < 0) {
			dmc_stop(gSystemMgr.m_nCard, m_sAxisSetting.m_nAxisId, 0);
			return -1;
		}
		if (m_bALM) {
			gSystemLog.DisplayLogAndSave(L"轴 - Alarm报错", LV_ERROR);
			return -1;
		}
	}
	gSystemLog.DisplayLogAndSave(L"运动到极限位置", LV_EVENT);
	Sleep(500);

	if (m_sAxisSetting.m_nAxisId == MOTOR_Y) {
		Sleep(1000);
		dmc_set_position(gSystemMgr.m_nCard, m_sAxisSetting.m_nAxisId, 0);        //设置零点
		dmc_set_encoder(gSystemMgr.m_nCard, m_sAxisSetting.m_nAxisId, 0);

		CString cstrLog = _utils::Unicode2TChar(m_sAxisSetting.m_wstrAxisName);
		cstrLog.AppendFormat(L"找原点完成", m_sAxisSetting.m_nAxisId);
		gSystemLog.DisplayLogAndSave(cstrLog.GetBuffer(), LV_EVENT);

		m_bHomed = true;
		return 0;
	}

	dmc_set_home_el_return(gSystemMgr.m_nCard, m_sAxisSetting.m_nAxisId, 1);
	dmc_set_home_pin_logic(gSystemMgr.m_nCard, m_sAxisSetting.m_nAxisId, 0, 0);//原点信号低电平有效
	dmc_set_homemode(gSystemMgr.m_nCard, m_sAxisSetting.m_nAxisId, m_nMotorDirection, 0, 0, 0);//设置回零模式

	nErrcode = dmc_home_move(gSystemMgr.m_nCard, m_sAxisSetting.m_nAxisId);//启动回零
	if (nErrcode != 0)
	{
		CString cstrLog = _utils::Unicode2TChar(m_sAxisSetting.m_wstrAxisName);
		cstrLog.AppendFormat(L" Home Move Error,error code=%d", nErrcode);
		gSystemLog.DisplayLogAndSave(cstrLog.GetBuffer(), LV_ERROR);
		return 0;
	}

	status = dmc_check_done(gSystemMgr.m_nCard, m_sAxisSetting.m_nAxisId);           //判断当前轴状态
	timeout = 2000;
	while (status != 1)
	{
		timeout--;
		Sleep(50);
		status = dmc_check_done(gSystemMgr.m_nCard, m_sAxisSetting.m_nAxisId);
		if (timeout < 0) {
			dmc_stop(gSystemMgr.m_nCard, m_sAxisSetting.m_nAxisId, 0);
			return -1;
		}
		if (m_bALM) {
			gSystemLog.DisplayLogAndSave(L"轴 - Alarm报错", LV_ERROR);
			return -1;
		}
	}
	Sleep(1000);
	dmc_set_position(gSystemMgr.m_nCard, m_sAxisSetting.m_nAxisId, 0);        //设置零点
	dmc_set_encoder(gSystemMgr.m_nCard, m_sAxisSetting.m_nAxisId, 0);

	CString cstrLog = _utils::Unicode2TChar(m_sAxisSetting.m_wstrAxisName);
	cstrLog.AppendFormat(L"找原点完成", m_sAxisSetting.m_nAxisId);
	gSystemLog.DisplayLogAndSave(cstrLog.GetBuffer(), LV_EVENT);

	m_bHomed = true;
	return 0;
}

void CMotor::StartMotorHomeThread2()
{
	ProcHome2.MemProc = &CMotor::MotorHomeThread2;
	UINT nThreadId;
	HANDLE hThread = (HANDLE)_beginthreadex(NULL, 0, ProcHome2.ThreadProc, (LPVOID)this, 0, &nThreadId);
	if (hThread == NULL)
	{
		return;
	}
}

unsigned int __stdcall CMotor::MotorHomeThread2()
{
	int nErrcode = 0;
	BYTE	 HomeMode, EZcount;
	HomeMode = 6;
	EZcount = 0;

	if (m_sAxisSetting.m_nAxisId < 3)
	{
		nErrcode = dmc_write_sevon_pin(gSystemMgr.m_nCard, m_sAxisSetting.m_nAxisId, OFF);
		Sleep(500);
	}

	dmc_set_profile_unit(gSystemMgr.m_nCard, m_sAxisSetting.m_nAxisId, m_sAxisSetting.m_nStartSpeed, m_sAxisSetting.m_nSpeedHome, m_sAxisSetting.m_nSpeedAcc, m_sAxisSetting.m_nSpeedAcc, 0);

	dmc_vmove(gSystemMgr.m_nCard, m_sAxisSetting.m_nAxisId, m_nMotorDirection);
	DWORD status = dmc_check_done(gSystemMgr.m_nCard, m_sAxisSetting.m_nAxisId);           //判断当前轴状态
	int timeout = 1000;
	while (status != 1)
	{
		timeout--;
		Sleep(50);
		status = dmc_check_done(gSystemMgr.m_nCard, m_sAxisSetting.m_nAxisId);
		if (timeout < 0) {
			dmc_stop(gSystemMgr.m_nCard, m_sAxisSetting.m_nAxisId, 0);
			return -1;
		}
	}

	gSystemLog.DisplayLogAndSave(L"运动到极限位置", LV_EVENT);
	Sleep(500);

	return 0;

}

void CMotor::StartMotorAbsEncMoveThread()
{
	ProcMove.MemProc = &CMotor::MotorAbsEncMoveThread;
	UINT nThreadId;
	//HANDLE hThread
	if (hThread_Abs != NULL)
	{
		CloseHandle(hThread_Abs);
	}
	hThread_Abs = (HANDLE)_beginthreadex(NULL, 0, ProcMove.ThreadProc, (LPVOID)this, 0, &nThreadId);
	if (hThread_Abs == NULL)
	{
		return;
	}
}

unsigned int __stdcall CMotor::MotorAbsEncMoveThread()
{
	int nPulse = (int)m_sAxisSetting.m_dTargetPos;

	dmc_set_profile_unit(gSystemMgr.m_nCard, m_sAxisSetting.m_nAxisId, m_sAxisSetting.m_nStartSpeed, m_sAxisSetting.m_nSpeedMove, m_sAxisSetting.m_nSpeedAcc, m_sAxisSetting.m_nSpeedAcc, 0);

	int nErrcode;

	if (dmc_check_done(gSystemMgr.m_nCard, m_sAxisSetting.m_nAxisId) == 0) //已经在运动中
		return 1;
	
	nErrcode = dmc_pmove(gSystemMgr.m_nCard, m_sAxisSetting.m_nAxisId, nPulse, 1);
	if (nErrcode)
	{
		CString cstrLog = _utils::Unicode2TChar(m_sAxisSetting.m_wstrAxisName);
		cstrLog.AppendFormat(L"Enc Fix Move Error,error code=%d", nErrcode);
		gSystemLog.DisplayLogAndSave(cstrLog.GetBuffer(), LV_ERROR);
		return 0;
	}
	int nTimeout = 5000;//50s
	while (dmc_check_done(gSystemMgr.m_nCard, m_sAxisSetting.m_nAxisId) == 0)
	{
		nTimeout--;
		Sleep(10);
		if (nTimeout < 0) {
			dmc_stop(gSystemMgr.m_nCard, m_sAxisSetting.m_nAxisId, 0);
			CString cstrLog = _utils::Unicode2TChar(m_sAxisSetting.m_wstrAxisName);
			cstrLog.AppendFormat(L"运动超时", m_sAxisSetting.m_nAxisId);
			gSystemLog.DisplayLogAndSave(cstrLog.GetBuffer(), LV_EVENT);
			return -1;
		}
	}
	return 0;
}

void CMotor::StartMotorStepMoveThread()
{
	ProcMove.MemProc = &CMotor::MotorStepMoveThread;
	UINT nThreadId;
	//HANDLE hThread	
	if (hThread_Step != NULL)
	{
		CloseHandle(hThread_Step);
	}
	hThread_Step = (HANDLE)_beginthreadex(NULL, 0, ProcMove.ThreadProc, (LPVOID)this, 0, &nThreadId);
	if (hThread_Step == NULL)
	{
		return;
	}
}

unsigned int __stdcall CMotor::MotorStepMoveThread()
{
	//dmc_set_profile(gSystemMgr.m_nCard, m_sAxisSetting.m_nAxisId, m_sMoveStep.Start_Speed, m_sMoveStep.Drive_Speed, m_sMoveStep.AccTime, m_sMoveStep.DecTime, m_sMoveStep.Dec);
	//if (nErrcode)
	//{
	//	CString cstrLog = _utils::Unicode2TChar(m_sAxisSetting.m_wstrAxisName);
	//	cstrLog.AppendFormat(L"Rel Fix set profile  Error,error code=%d", nErrcode);
	//	gSystemLog.DisplayLogAndSave(cstrLog.GetBuffer(), LV_ERROR);
	//	return 0;
	//}
	if(m_sAxisSetting.m_nAxisId>2)
		dmc_set_profile(gSystemMgr.m_nCard, m_sAxisSetting.m_nAxisId, m_sAxisSetting.m_nStartSpeed, m_sAxisSetting.m_nSpeedMove, m_sAxisSetting.m_nSpeedAcc, m_sAxisSetting.m_nSpeedAcc, 0);
	else
		dmc_set_profile_unit(gSystemMgr.m_nCard, m_sAxisSetting.m_nAxisId, m_sAxisSetting.m_nStartSpeed, m_sAxisSetting.m_nSpeedMove, m_sAxisSetting.m_nSpeedAcc, m_sAxisSetting.m_nSpeedAcc, 0);
	int nPulse = (int)m_sAxisSetting.m_dTargetPos;
	int nErrcode = dmc_pmove(gSystemMgr.m_nCard, m_sAxisSetting.m_nAxisId, nPulse, 0);//0：相对坐标模式，1：绝对坐标模式s
	if (nErrcode)
	{
		CString cstrLog = _utils::Unicode2TChar(m_sAxisSetting.m_wstrAxisName);
		cstrLog.AppendFormat(L"Rel Fix Move Error,error code=%d", nErrcode);
		gSystemLog.DisplayLogAndSave(cstrLog.GetBuffer(), LV_ERROR);
		return 0;
	}
	int nTimeout = 5000;//50s
	while (dmc_check_done(gSystemMgr.m_nCard, m_sAxisSetting.m_nAxisId) == 0)
	{
		nTimeout--;
		Sleep(10);
		if (nTimeout < 0) {
			dmc_stop(gSystemMgr.m_nCard, m_sAxisSetting.m_nAxisId, 0);
			CString cstrLog = _utils::Unicode2TChar(m_sAxisSetting.m_wstrAxisName);
			cstrLog.AppendFormat(L"运动超时", m_sAxisSetting.m_nAxisId);
			gSystemLog.DisplayLogAndSave(cstrLog.GetBuffer(), LV_EVENT);
			return -1;
		}
	}
	return 0;
}

void CMotor::StartMotorContinueMoveThread()
{
	ProcMoveContinue.MemProc = &CMotor::MotorContinueMoveThread;
	UINT nThreadId;
	HANDLE hThread = (HANDLE)_beginthreadex(NULL, 0, ProcMoveContinue.ThreadProc, (LPVOID)this, 0, &nThreadId);
	if (hThread == NULL)
	{
		return;
	}
}

unsigned int __stdcall CMotor::MotorContinueMoveThread()
{
	//int nErrcode = dmc_set_profile(gSystemMgr.m_nCard, m_sAxisSetting.m_nAxisId, m_sMoveStep.Start_Speed, m_sMoveStep.Drive_Speed, m_sMoveStep.AccTime, m_sMoveStep.DecTime, m_sMoveStep.Dec);
	//if (nErrcode)
	//{
	//	CString cstrLog = _utils::Unicode2TChar(m_sAxisSetting.m_wstrAxisName);
	//	cstrLog.AppendFormat(L"dmc_set_profile Error,error code=%d\n", nErrcode);
	//	gSystemLog.DisplayLogAndSave(cstrLog.GetBuffer(), LV_ERROR);
	//	return 0;
	//}
	int nErrcode = dmc_vmove(gSystemMgr.m_nCard, m_sAxisSetting.m_nAxisId, m_nMotorDirection);
	if (nErrcode)
	{
		CString cstrLog = _utils::Unicode2TChar(m_sAxisSetting.m_wstrAxisName);
		cstrLog.AppendFormat(L"dmc_vmove Error,error code=%d\n", nErrcode);
		gSystemLog.DisplayLogAndSave(cstrLog.GetBuffer(), LV_ERROR);
		return 0;
	}
	return 0;
}

void CMotor::StopMotorMoveThread()
{
	ProcStop.MemProc = &CMotor::StopMotorThread;
	UINT nThreadId;
	HANDLE hThread = (HANDLE)_beginthreadex(NULL, 0, ProcStop.ThreadProc, (LPVOID)this, 0, &nThreadId);
	if (hThread == NULL)
	{
		return;
	}
}

unsigned int __stdcall CMotor::StopMotorThread()
{
	int nErrCode = dmc_stop(gSystemMgr.m_nCard, m_sAxisSetting.m_nAxisId, 0); //0：减速停止，1：立即停止
	if (nErrCode)
	{
		CString cstrLog = _utils::Unicode2TChar(m_sAxisSetting.m_wstrAxisName);
		cstrLog.AppendFormat(L"mn_velocity_move Error,error code=%d\n", nErrCode);
		gSystemLog.DisplayLogAndSave(cstrLog.GetBuffer(), LV_ERROR);
		return 0;
	}
	CString cstrLog = _utils::Unicode2TChar(m_sAxisSetting.m_wstrAxisName);
	cstrLog.AppendFormat(L"Stop Move");
	gSystemLog.DisplayLogAndSave(cstrLog.GetBuffer(), LV_EVENT);
	return 0;
}


