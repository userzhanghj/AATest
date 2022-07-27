#include "pch.h"
#include "Test.h"
#include "SystemManager.h"
#include "ConfigFileManager.h"
#include "SystemLog.h"

extern CConfigFileManager gConfigMgr;
extern CSystemLog     gSystemLog;

//AA运动
bool CSystemManager::AAMoveStepZ(double dFocusPos) // foucusPos 单位mm
{
	if (m_bMotorErrorFlag || !m_bHomeFlag || m_bEmergencyStopFlag)
		return FALSE;
	short bMotionDoneZ = 0x000;
	int nTimeout = 500;
	bool bMove(false);
	CString cstr;
	//gSystemLog.DisplayLogAndSave(L"Start Move Step Z -------------------------------------------------------------------) ", LV_ERROR);
	m_vCMotor[MOTOR_Z].m_sAxisSetting.m_dTargetPos = dFocusPos * m_vCMotor[MOTOR_Z].PositionRatio;
	m_vCMotor[MOTOR_Z].MotorMoveStep();
	Sleep(30);
	while (1)
	{
		Sleep(10);
		if (bMotionDoneZ == MOTION_DONE)
		{
			bMove = true;
			break;
		}
		if (nTimeout-- < 0)
		{
			bMove = false;
			break;
		}
		bMotionDoneZ = dmc_check_done( m_nCard, MOTOR_Z);
	}
	return bMove;
}

int CSystemManager::MoveOffsetZ(double dFocusPos)
{
	if (m_bMotorErrorFlag || !m_bHomeFlag || m_bEmergencyStopFlag)
		return FALSE;
	short bMotionDoneZ = 0x000;
	int nTimeout = 5000;
	bool bMove(false);
	CString cstr;
	cstr.Format(L"AA Offset Z：%.3f", dFocusPos);
	gSystemLog.DisplayLogAndSave(cstr.GetBuffer(), LV_EVENT);
	//gSystemLog.DisplayLogAndSave(L"Start Move Step Z -------------------------------------------------------------------) ", LV_ERROR);
	m_vCMotor[MOTOR_Z].m_sAxisSetting.m_dTargetPos = dFocusPos * m_vCMotor[MOTOR_Z].PositionRatio;
	m_vCMotor[MOTOR_Z].MotorMoveStep();
	Sleep(50);
	while (1)
	{
		Sleep(10);
		if (bMotionDoneZ == MOTION_DONE)
		{
			bMove = true;
			break;
		}
		if (nTimeout-- < 0)
		{
			bMove = false;
			break;
		}
		bMotionDoneZ = dmc_check_done( m_nCard, MOTOR_Z);
	}
	return bMove;
}

int CSystemManager::MoveStepXY(double stepx, double stepy)
{
	if (m_bMotorErrorFlag || !m_bHomeFlag || m_bEmergencyStopFlag)
		return FALSE;
	short bMotionDoneX = 0x000;
	short bMotionDoneY = 0x000;
	int nTimeout = 5000;
	bool bMove(false);
	CString cstr;
	//gSystemLog.DisplayLogAndSave(L"Start Move Step XY -------------------------------------------------------------------) ", LV_ERROR);
	//m_vCMotor[MOTOR_X].m_sAxisSetting.m_dTargetPos = stepx * m_vCMotor[MOTOR_X].PositionRatio;
	//m_vCMotor[MOTOR_Y].m_sAxisSetting.m_dTargetPos = stepy * m_vCMotor[MOTOR_Y].PositionRatio;
	if (ChangeXY == 1) {
		m_vCMotor[MOTOR_X].m_sAxisSetting.m_dTargetPos = stepy * m_vCMotor[MOTOR_X].PositionRatio;
		m_vCMotor[MOTOR_Y].m_sAxisSetting.m_dTargetPos = stepx * m_vCMotor[MOTOR_Y].PositionRatio;
	}
	else {
		m_vCMotor[MOTOR_X].m_sAxisSetting.m_dTargetPos = stepx * m_vCMotor[MOTOR_X].PositionRatio;
		m_vCMotor[MOTOR_Y].m_sAxisSetting.m_dTargetPos = stepy * m_vCMotor[MOTOR_Y].PositionRatio;
	}
	m_vCMotor[MOTOR_X].MotorMoveStep();
	m_vCMotor[MOTOR_Y].MotorMoveStep();

	while (1)
	{
		Sleep(10);
		if (bMotionDoneX == MOTION_DONE && bMotionDoneY == MOTION_DONE)
		{
			bMove = true;
			break;
		}
		if (nTimeout-- < 0)
		{
			bMove = false;
			break;
		}
		bMotionDoneX = dmc_check_done( m_nCard, MOTOR_X);
		bMotionDoneY = dmc_check_done( m_nCard, MOTOR_Y);
	}
	return bMove;
}

int CSystemManager::MoveStepXtYt(double stepxt, double stepyt)
{
	if (m_bMotorErrorFlag || !m_bHomeFlag || m_bEmergencyStopFlag)
		return FALSE;
	short bMotionDoneXt = 0x000;
	short bMotionDoneYt = 0x000;
	int nTimeout = 5000;
	bool bMove(false);
	CString cstr;
	//gSystemLog.DisplayLogAndSave(L"Start Move Step Z -------------------------------------------------------------------) ", LV_ERROR);
	//m_vCMotor[MOTOR_Xt].m_sAxisSetting.m_dTargetPos = stepxt * m_vCMotor[MOTOR_Xt].PositionRatio;
	//m_vCMotor[MOTOR_Yt].m_sAxisSetting.m_dTargetPos = stepyt * m_vCMotor[MOTOR_Yt].PositionRatio;
	if (ChangeXY == 1) {
		m_vCMotor[MOTOR_Xt].m_sAxisSetting.m_dTargetPos = stepyt * m_vCMotor[MOTOR_Xt].PositionRatio;
		m_vCMotor[MOTOR_Yt].m_sAxisSetting.m_dTargetPos = stepxt * m_vCMotor[MOTOR_Yt].PositionRatio;
	}
	else {
		m_vCMotor[MOTOR_Xt].m_sAxisSetting.m_dTargetPos = stepxt * m_vCMotor[MOTOR_Xt].PositionRatio;
		m_vCMotor[MOTOR_Yt].m_sAxisSetting.m_dTargetPos = stepyt * m_vCMotor[MOTOR_Yt].PositionRatio;
	}
	m_vCMotor[MOTOR_Xt].MotorMoveStep();
	m_vCMotor[MOTOR_Yt].MotorMoveStep();

	while (1)
	{
		Sleep(10);
		if (bMotionDoneXt == MOTION_DONE && bMotionDoneYt == MOTION_DONE)
		{
			bMove = true;
			break;
		}
		if (nTimeout-- < 0)
		{
			bMove = false;
			break;
		}
		bMotionDoneXt = dmc_check_done( m_nCard, MOTOR_Xt);
		bMotionDoneYt = dmc_check_done( m_nCard, MOTOR_Yt);
	}
	return bMove;
}

int CSystemManager::MoveCenter(void)
{
	CString cstrLog;
	int NewData;
	int cnt;

	Sleep(30);
	gSystemLog.DisplayLogAndSave(L"Start Move Center", LV_EVENT);
	NewData = m_nNewDataFlag;
	cnt = 0;
	while (m_nNewDataFlag == NewData)
	{
		Sleep(1);
		cnt++;
		if (cnt > 1000)
			return FALSE;
	}

	double MoveXmm = m_dCenterXDif * m_dPixelSize;
	double MoveYmm = m_dCenterYDif * m_dPixelSize;

	cstrLog.Format(L"Move Center moveX=%.2f,moveY=%.2f,moveX(mm):%.2f,moveY(mm):%.2f", m_dCenterXDif, m_dCenterYDif, MoveXmm, MoveYmm);
	gSystemLog.DisplayLogAndSave(cstrLog.GetBuffer(), LV_EVENT);
	//n*AAA + m * ABC + DD = 14
	char buf[100] = { 0 };
	//Sleep(50);

	int errcode;
	if (fabs(m_dCenterXDif) < m_nSearchW[0] / 2/*MAX_XY_OFFSET*/ && fabs(m_dCenterYDif) < m_nSearchH[0] / 2/*MAX_XY_OFFSET*/)
	{
		//logdlg.log("move x :%f move y :%f", MoveXmm, MoveYmm);
		errcode = MoveStepXY(MoveXmm, -MoveYmm);
		//errcode = MoveStepXY(-MoveXmm, -MoveYmm);
		if (errcode != 1) return errcode;
	}
	else
	{
		cstrLog.Format(L"Center xy out of %.2fmm range.", (double)(m_nSearchW[0] / 2));
		gSystemLog.DisplayLogAndSave(cstrLog.GetBuffer(), LV_EVENT);
		return FALSE;
	}
	Sleep(20);
	NewData = m_nNewDataFlag;
	cnt = 0;
	while (m_nNewDataFlag == NewData)
	{
		Sleep(1);
		cnt++;
		if (cnt > 1000)
			return FALSE;
	}
	for (int i = 0; i < SLANTED_BW_NUM; i++)
	{
		if (FindTarget[i] == TRUE)
			continue;
		else
		{
			cstrLog.Format(L"Error----****----can't find target No.%d.", i);
			gSystemLog.DisplayLogAndSave(cstrLog.GetBuffer(), LV_ERROR);
			Sleep(300);
			if (FindTarget[i] == TRUE)
				continue;
			return FALSE;
		}
	}
	//logdlg.log("move x, y to center. Xpos:%d Ypos:%d", motordlg.CurrentPos[0], motordlg.CurrentPos[1]);
	gSystemLog.DisplayLogAndSave(L"End Move Center", LV_EVENT);
	return TRUE;
}

int CSystemManager::PickLens(void)
{
	if (m_bMotorErrorFlag || !m_bHomeFlag || m_bEmergencyStopFlag) {
		gSystemLog.DisplayLogAndSave(L"安全错误", LV_EVENT);
		return FALSE;
	}
	if (!S10)
	{
		m_cIo.SetOutputIo(9, OFF);
		m_cIo.SetOutputIo(10, ON);
		Sleep(200);
	}
	CString cstr;
	cstr.Format(L"PickLens Move Start");
	gSystemLog.DisplayLogAndSave(cstr.GetBuffer(), LV_EVENT);

	int nTimeout = 0;
	short bMotionDoneTZ = 0x00;
	short bMotionDoneX = 0x00;
	short bMotionDoneY = 0x00;
	short bMotionDoneZ = 0x00;
	short bMotionDoneXt = 0x00;
	short bMotionDoneYt = 0x00;
	short bMotionDoneTX = 0x00;

	//夹爪传感器张开未感应，先张开夹爪

	//if (m_vCMotor[M_TABLE_Z].m_nCurPositon != m_nPositionTableZ[2])
	//{//不在安全位置，先移动 TableZ 轴
	m_vCMotor[M_TABLE_Z].m_sAxisSetting.m_dTargetPos = m_nPositionTableZ[2];

	m_vCMotor[M_TABLE_Z].MotorMoveAbsEnc();
	Sleep(100);
	nTimeout = 400;
	while (1)
	{
		Sleep(50);
		if (bMotionDoneTZ == MOTION_DONE)
		{
			break;
		}
		if (nTimeout-- < 0)
		{
			cstr.Format(L"TableZ 移动至安全位超时");
			gSystemLog.DisplayLogAndSave(cstr.GetBuffer(), LV_ERROR);
			return FALSE;
		}
		bMotionDoneTZ = dmc_check_done(m_nCard, M_TABLE_Z);
	}
	//}

	//Sleep(50);
	m_vCMotor[MOTOR_X].m_sAxisSetting.m_dTargetPos = m_nPositionX[0];
	m_vCMotor[MOTOR_Y].m_sAxisSetting.m_dTargetPos = m_nPositionY[0];
	m_vCMotor[MOTOR_Z].m_sAxisSetting.m_dTargetPos = m_nPositionZ[0];
	m_vCMotor[MOTOR_Xt].m_sAxisSetting.m_dTargetPos = m_nPositionXt[0];
	m_vCMotor[MOTOR_Yt].m_sAxisSetting.m_dTargetPos = m_nPositionYt[0];
	m_vCMotor[M_TABLE_X].m_sAxisSetting.m_dTargetPos = m_nPositionTableX[0];

	m_vCMotor[MOTOR_X].MotorMoveAbsEnc();
	m_vCMotor[MOTOR_Y].MotorMoveAbsEnc();
	m_vCMotor[MOTOR_Z].MotorMoveAbsEnc();
	m_vCMotor[MOTOR_Xt].MotorMoveAbsEnc();
	m_vCMotor[MOTOR_Yt].MotorMoveAbsEnc();
	m_vCMotor[M_TABLE_X].MotorMoveAbsEnc();
	nTimeout = 1000;

	while (1)
	{
		Sleep(50);
		if ((bMotionDoneX == MOTION_DONE) && (bMotionDoneY == MOTION_DONE) && (bMotionDoneZ == MOTION_DONE) && (bMotionDoneXt == MOTION_DONE) && (bMotionDoneYt == MOTION_DONE) && (bMotionDoneTX == MOTION_DONE))
		{
			break;
		}
		if (nTimeout-- < 0)
		{
			cstr.Format(L"五轴 + TX 移动至夹取位超时");
			gSystemLog.DisplayLogAndSave(cstr.GetBuffer(), LV_ERROR);
			return FALSE;
		}
		bMotionDoneX = dmc_check_done( m_nCard, MOTOR_X);
		bMotionDoneY = dmc_check_done( m_nCard, MOTOR_Y);
		bMotionDoneZ = dmc_check_done( m_nCard, MOTOR_Z);
		bMotionDoneXt = dmc_check_done( m_nCard, MOTOR_Xt);
		bMotionDoneYt = dmc_check_done( m_nCard, MOTOR_Yt);
		bMotionDoneTX = dmc_check_done( m_nCard, M_TABLE_X);
	}

	Sleep(10);
	m_vCMotor[M_TABLE_Z].m_sAxisSetting.m_dTargetPos = m_nPositionTableZ[0];

	m_vCMotor[M_TABLE_Z].MotorMoveAbsEnc();
	bMotionDoneTZ = 0x00;
	Sleep(100);
	nTimeout = 400;

	while (1)
	{
		Sleep(50);
		if (bMotionDoneTZ == MOTION_DONE)
		{
			break;
		}
		if (nTimeout-- < 0)
		{
			cstr.Format(L"TZ 移动至夹取位超时");
			gSystemLog.DisplayLogAndSave(cstr.GetBuffer(), LV_ERROR);
			return FALSE;
		}
		bMotionDoneTZ = dmc_check_done( m_nCard, M_TABLE_Z);
	}

	cstr.Format(L"PickLens Move Done");
	gSystemLog.DisplayLogAndSave(cstr.GetBuffer(), LV_EVENT);

	return TRUE;
}

int CSystemManager::LoadLens(void)
{
	if (m_bMotorErrorFlag || !m_bHomeFlag || m_bEmergencyStopFlag) {
		gSystemLog.DisplayLogAndSave(L"安全错误", LV_EVENT);
		return FALSE;
	}
	CString cstr;
	cstr.Format(L"LoadLens Move Start");
	gSystemLog.DisplayLogAndSave(cstr.GetBuffer(), LV_EVENT);

	int nTimeout = 0;
	short bMotionDoneTZ = 0x00;
	short bMotionDoneX = 0x00;
	short bMotionDoneY = 0x00;
	short bMotionDoneZ = 0x00;
	short bMotionDoneXt = 0x00;
	short bMotionDoneYt = 0x00;
	short bMotionDoneTX = 0x00;

	//if (m_vCMotor[M_TABLE_Z].m_nCurPositon != m_nPositionTableZ[2])
	//{//不在安全位置，先移动 TableZ 轴
	m_vCMotor[M_TABLE_Z].m_sAxisSetting.m_dTargetPos = m_nPositionTableZ[2];

	m_vCMotor[M_TABLE_Z].MotorMoveAbsEnc();
	Sleep(100);
	nTimeout = 400;
	while (1)
	{
		Sleep(50);
		if (bMotionDoneTZ == MOTION_DONE)
		{
			break;
		}
		if (nTimeout-- < 0)
		{
			cstr.Format(L"TableZ 移动至安全位超时");
			gSystemLog.DisplayLogAndSave(cstr.GetBuffer(), LV_ERROR);
			return FALSE;
		}
		bMotionDoneTZ = dmc_check_done(m_nCard, M_TABLE_Z);
	}
	//}

	//Sleep(50);
	m_vCMotor[MOTOR_X].m_sAxisSetting.m_dTargetPos = m_nPositionX[1];
	m_vCMotor[MOTOR_Y].m_sAxisSetting.m_dTargetPos = m_nPositionY[1];
	m_vCMotor[MOTOR_Z].m_sAxisSetting.m_dTargetPos = m_nPositionZ[1];
	m_vCMotor[MOTOR_Xt].m_sAxisSetting.m_dTargetPos = m_nPositionXt[1];
	m_vCMotor[MOTOR_Yt].m_sAxisSetting.m_dTargetPos = m_nPositionYt[1];
	m_vCMotor[M_TABLE_X].m_sAxisSetting.m_dTargetPos = m_nPositionTableX[1];

	m_vCMotor[MOTOR_X].MotorMoveAbsEnc();
	m_vCMotor[MOTOR_Y].MotorMoveAbsEnc();
	m_vCMotor[MOTOR_Z].MotorMoveAbsEnc();
	m_vCMotor[MOTOR_Xt].MotorMoveAbsEnc();
	m_vCMotor[MOTOR_Yt].MotorMoveAbsEnc();
	m_vCMotor[M_TABLE_X].MotorMoveAbsEnc();
	nTimeout = 1000;

	while (1)
	{
		Sleep(50);
		if ((bMotionDoneX == MOTION_DONE) && (bMotionDoneY == MOTION_DONE) && (bMotionDoneZ == MOTION_DONE) && (bMotionDoneXt == MOTION_DONE) && (bMotionDoneYt == MOTION_DONE) && (bMotionDoneTX == MOTION_DONE))
		{
			break;
		}
		if (nTimeout-- < 0)
		{
			cstr.Format(L"五轴 + TX 移动至AA位超时");
			gSystemLog.DisplayLogAndSave(cstr.GetBuffer(), LV_ERROR);
			return FALSE;
		}
		bMotionDoneX = dmc_check_done( m_nCard, MOTOR_X);
		bMotionDoneY = dmc_check_done( m_nCard, MOTOR_Y);
		bMotionDoneZ = dmc_check_done( m_nCard, MOTOR_Z);
		bMotionDoneXt = dmc_check_done( m_nCard, MOTOR_Xt);
		bMotionDoneYt = dmc_check_done( m_nCard, MOTOR_Yt);
		bMotionDoneTX = dmc_check_done( m_nCard, M_TABLE_X);
	}

	Sleep(10);
	m_vCMotor[M_TABLE_Z].m_sAxisSetting.m_dTargetPos = m_nPositionTableZ[1];

	m_vCMotor[M_TABLE_Z].MotorMoveAbsEnc();
	bMotionDoneTZ = 0x00;
	Sleep(100);
	nTimeout = 400;

	while (1)
	{
		Sleep(50);
		if (bMotionDoneTZ == MOTION_DONE)
		{
			break;
		}
		if (nTimeout-- < 0)
		{
			cstr.Format(L"TZ 移动至AA位超时");
			gSystemLog.DisplayLogAndSave(cstr.GetBuffer(), LV_ERROR);
			return FALSE;
		}
		bMotionDoneTZ = dmc_check_done( m_nCard, M_TABLE_Z);
	}

	cstr.Format(L"LoadLens Move Done");
	gSystemLog.DisplayLogAndSave(cstr.GetBuffer(), LV_EVENT);

	return TRUE;
}

int CSystemManager::MoveChart(void)
{
	if (m_bMotorErrorFlag || !ChartHomeFlag || m_bEmergencyStopFlag) {
		gSystemLog.DisplayLogAndSave(L"图卡轴安全错误", LV_EVENT);
		return FALSE;
	}
	CString cstr;
	cstr.Format(L"Chart Move Start");
	gSystemLog.DisplayLogAndSave(cstr.GetBuffer(), LV_EVENT);

	int nTimeout = 0;
	short bMotionDoneZ = 0x00;

	m_vCMotor[M_CHART_Z].m_sAxisSetting.m_dTargetPos = ChartPos;
	m_vCMotor[M_CHART_Z].MotorMoveAbsEnc();
	Sleep(100);
	nTimeout = 400;
	while (1)
	{
		Sleep(50);
		if (bMotionDoneZ == MOTION_DONE)
		{
			break;
		}
		if (nTimeout-- < 0)
		{
			cstr.Format(L"ChartZ 移动超时");
			gSystemLog.DisplayLogAndSave(cstr.GetBuffer(), LV_ERROR);
			return FALSE;
		}
		bMotionDoneZ = dmc_check_done(m_nCard, M_CHART_Z);
	}
	cstr.Format(L"Chart Move Done");
	gSystemLog.DisplayLogAndSave(cstr.GetBuffer(), LV_EVENT);

	return TRUE;
}

//int CSystemManager::SearchZ(void)
//{
//	int NewData;//新数据
//	int timeout = 0;
//	double StepDis = m_dSearchZStep_1;
//	int cnt = 0;
//	int result = 0;
//	CString cstrLog;
//	int cycle_num = 0;
//
//	CString cstr;
//	cstr.Format(L"Search Z Move Start");
//	gSystemLog.DisplayLogAndSave(cstr.GetBuffer(), LV_EVENT);
//
//	for (int i = 0; i < 5; i++)
//	{
//		SfrAvgValue[i] = 0;
//		SfrValue[i][0] = 0;
//		SfrValue[i][1] = 0;
//		SfrValue[i][2] = 0;
//		SfrValue[i][3] = 0;
//	}
//
//	while (timeout < 6)
//	{
//		Sleep(10);
//		NewData = m_nNewDataFlag;
//		cnt = 0;
//		while (m_nNewDataFlag == NewData)
//		{
//			Sleep(1);
//			cnt++;
//			if (cnt > 1000)
//				return FALSE;
//		}
//
//		if (FindTarget[0] == FALSE || SfrAvgValue[0] < m_dSearchZSpec_2)
//		{
//			break;
//		}
//		timeout++;
//		result = AAMoveStepZ(StepDis);
//		if (!result)
//			return FALSE;
//	}
//
//	//gSystemLog.DisplayLogAndSave(L"Start Search Z", LV_EVENT);
//	double sfrvalue = 0;
//
//	while (1)
//	{
//		Sleep(10);
//		Sleep(m_nStepWait);
//		cnt = 0;
//		NewData = m_nNewCapImg;
//		cnt = 0;
//		while (m_nNewCapImg == NewData)
//		{
//			Sleep(5);
//			cnt++;
//			if (cnt > 200)
//				return FALSE;
//		}
//		cnt = 0;
//		NewData = m_nNewDataFlag;
//		while (m_nNewDataFlag == NewData)
//		{
//			Sleep(5);
//			cnt++;
//			if (cnt > 200)
//				return FALSE;
//		}
//
//		if (SfrAvgValue[0] < m_dSearchZSpec_1)StepDis = m_dSearchZStep_1;
//		else StepDis = m_dSearchZStep_2;
//
//		cstrLog.Format(L"Search Z cycle num:%d; FindTarget:%d; SFRValueAvg:%.4f", cycle_num, FindTarget[0], SfrAvgValue[0]);
//		gSystemLog.DisplayLogAndSave(cstrLog.GetBuffer(), LV_EVENT);
//
//		if (FindTarget[0] == TRUE) {
//			sfrvalue = SfrAvgValue[0];
//		}
//		else {
//			sfrvalue = 0;
//		}
//
//		if ((FindTarget[0] == FALSE || /*SfrAvgValue[0]*/sfrvalue < m_dSearchZSpec_2) && cycle_num < m_nSearchZStepMaxCnt)
//		{
//			result = AAMoveStepZ(-StepDis);
//
//			cycle_num++;
//			if (result != 1) return FALSE;
//		}
//		else
//		{
//			if (cycle_num >= m_nSearchZStepMaxCnt)
//			{
//				AAMoveStepZ(StepDis * 5);
//				gSystemLog.DisplayLogAndSave(L"Error----****---- Search Z out of range!", LV_ERROR);
//				return FALSE;
//				//
//			}
//			if (FindTarget[0] != TRUE)
//			{
//				AAMoveStepZ(StepDis * 5);
//				gSystemLog.DisplayLogAndSave(L"Error----****----Move center, center recognizing fail!", LV_ERROR);
//				return FALSE;
//			}
//			else
//			{
//				gSystemLog.DisplayLogAndSave(L"break cycle.search z.", LV_EVENT);
//				break;
//			}
//		}
//
//	}
//
//	result = AAMoveStepZ(m_dAAStep * 3);
//	return TRUE;
//}

int CSystemManager::SearchZ(void)
{
	int NewData;//新数据
	int timeout = 0;
	double StepDis = m_dSearchZStep_1;
	int cnt = 0;
	int result = 0;
	CString cstrLog;
	int cycle_num = 0;

	CString cstr;
	cstr.Format(L"Search Z Move Start");
	gSystemLog.DisplayLogAndSave(cstr.GetBuffer(), LV_EVENT);

	int BackFlag = 0;//是否反向SearchZ

	int UpCnt = 0;
	//中心识别不到，先向上寻找？
	if (FindTarget[0] == 0) {
		while (1) {
			cstr.Format(L"Up Search Z ");
			gSystemLog.DisplayLogAndSave(cstr.GetBuffer(), LV_EVENT);

			Sleep(10);
			//if (SfrAvgValue[0] < m_dSearchZSpec_1)StepDis = m_dSearchZStep_1;
			//else StepDis = m_dSearchZStep_2;
			StepDis = m_dSearchZStep_1;

			result = AAMoveStepZ(StepDis);

			Sleep(m_nStepWait);
			cnt = 0;
			//NewData = m_nNewCapImg;
			//cnt = 0;
			//while (m_nNewCapImg == NewData)
			//{
			//	Sleep(5);
			//	cnt++;
			//	if (cnt > 200)
			//		return FALSE;
			//}
			cnt = 0;
			NewData = m_nNewDataFlag;
			while (m_nNewDataFlag == NewData)
			{
				Sleep(5);
				cnt++;
				if (cnt > 200)
					return FALSE;
			}

			UpCnt++;

			cstrLog.Format(L"Up Search Z Cnt num:%d; FindTarget:%d", UpCnt, FindTarget[0]);
			gSystemLog.DisplayLogAndSave(cstrLog.GetBuffer(), LV_EVENT);

			if (FindTarget[0])
			{
				gSystemLog.DisplayLogAndSave(L"UP FindTarget[0] ,Back Move!", LV_ERROR);
				BackFlag = 1;
				break;
			}

			if (UpCnt > 2) {
				result = AAMoveStepZ(-StepDis * (UpCnt + 1));
				gSystemLog.DisplayLogAndSave(L"UP out range，跳出!", LV_ERROR);
				break;
			}

		}
	}

	//gSystemLog.DisplayLogAndSave(L"Start Search Z", LV_EVENT);
	double sfrvalue = 0;
	double sfrvalue_l = 0;//移动前中心sfr值

	double sfrvalue_start = 0;


	int DisCnt;//中心清晰度递减次数

	int ZoreCnt;//中心清晰度为0的次数

	sfrvalue_start = FindTarget[0] * SfrAvgValue[0];
	int startflag = 0;

	while (1)
	{
		if (BackFlag == 1)
			break;

		Sleep(10);
		sfrvalue_l = FindTarget[0] * SfrAvgValue[0];

		if (sfrvalue_l > 0 && startflag == 0) {
			startflag = 1;
			sfrvalue_start = sfrvalue_l;
		}

		if (SfrAvgValue[0] < m_dSearchZSpec_1)StepDis = m_dSearchZStep_1;
		else StepDis = m_dSearchZStep_2;

		result = AAMoveStepZ(-StepDis);

		Sleep(m_nStepWait);
		cnt = 0;
		//NewData = m_nNewCapImg;
		//cnt = 0;
		//while (m_nNewCapImg == NewData)
		//{
		//	Sleep(5);
		//	cnt++;
		//	if (cnt > 200)
		//		return FALSE;
		//}
		cnt = 0;
		NewData = m_nNewDataFlag;
		while (m_nNewDataFlag == NewData)
		{
			Sleep(5);
			cnt++;
			if (cnt > 200)
				return FALSE;
		}

		sfrvalue = FindTarget[0] * SfrAvgValue[0];
		cycle_num++;

		cstrLog.Format(L"Search Z cycle num:%d; FindTarget:%d; SFRValueAvg:%.4f", cycle_num, FindTarget[0], SfrAvgValue[0]);
		gSystemLog.DisplayLogAndSave(cstrLog.GetBuffer(), LV_EVENT);

		if ((sfrvalue_l - sfrvalue) > 1) {
			DisCnt++;
		}
		else {
			DisCnt = 0;
		}

		if (sfrvalue == 0 && sfrvalue_start > 0) {
			ZoreCnt++;
		}

		if (DisCnt > 1) {
			BackFlag = 1;
			gSystemLog.DisplayLogAndSave(L"递减，反向SearchZ", LV_ERROR);
			break;
		}
		if (ZoreCnt > 2) {
			BackFlag = 1;
			gSystemLog.DisplayLogAndSave(L"由非零到零，反向SearchZ", LV_ERROR);
			break;
		}

		if (cycle_num >= m_nSearchZStepMaxCnt)
		{
			AAMoveStepZ(StepDis * 5);
			gSystemLog.DisplayLogAndSave(L"Error----****---- Search Z out of range!", LV_ERROR);
			return FALSE;
			//
		}

		if (sfrvalue >= m_dSearchZSpec_2 && DisCnt == 0)
		{
			result = AAMoveStepZ(StepDis);
			gSystemLog.DisplayLogAndSave(L"Search Z done! Break", LV_ERROR);
			break;
		}

	}

	if (BackFlag == 1) {
		cycle_num = 0;

		while (1) {
			cstr.Format(L"开始 反向 Search Z ");
			gSystemLog.DisplayLogAndSave(cstr.GetBuffer(), LV_EVENT);

			Sleep(10);
			sfrvalue_l = FindTarget[0] * SfrAvgValue[0];

			//if (SfrAvgValue[0] < m_dSearchZSpec_1)StepDis = m_dSearchZStep_1;
			//else StepDis = m_dSearchZStep_2;
			StepDis = m_dSearchZStep_2;

			result = AAMoveStepZ(StepDis);

			Sleep(m_nStepWait);
			cnt = 0;
			//NewData = m_nNewCapImg;
			//cnt = 0;
			//while (m_nNewCapImg == NewData)
			//{
			//	Sleep(5);
			//	cnt++;
			//	if (cnt > 200)
			//		return FALSE;
			//}
			cnt = 0;
			NewData = m_nNewDataFlag;
			while (m_nNewDataFlag == NewData)
			{
				Sleep(5);
				cnt++;
				if (cnt > 200)
					return FALSE;
			}

			sfrvalue = FindTarget[0] * SfrAvgValue[0];
			cycle_num++;

			cstrLog.Format(L"Back Search Z cycle num:%d; FindTarget:%d; SFRValueAvg:%.4f", cycle_num, FindTarget[0], SfrAvgValue[0]);
			gSystemLog.DisplayLogAndSave(cstrLog.GetBuffer(), LV_EVENT);

			if ((sfrvalue_l - sfrvalue) > 1) {
				DisCnt++;
			}
			else {
				DisCnt = 0;
			}

			if (DisCnt > 1) {
				gSystemLog.DisplayLogAndSave(L"清晰度开始递减，跳出!", LV_ERROR);
				break;
			}

			if (cycle_num >= m_nSearchZStepMaxCnt)
			{
				gSystemLog.DisplayLogAndSave(L"Error----****---- Back Search Z out of range!", LV_ERROR);
				return FALSE;
				//
			}
		}
	}

	result = AAMoveStepZ(m_dAAStep * 3);
	return TRUE;
}

int CSystemManager::FocusScan(void)
{
	TestResult = 0;
	gSystemLog.DisplayLogAndSave(L"Start Focus Scan", LV_EVENT);
	int    nTimeout = 0;
	//int    nTotalCount = 0;
	int    nErrcode = 0;
	bool bFindPeak[SLANTED_BW_NUM]{ false };
	float fSfrValue[SLANTED_BW_NUM][100] = { 0 };
	float fSfrCruve[SLANTED_BW_NUM][100] = { 0 };// 拟合曲线
	float fMaxValue[SLANTED_BW_NUM] = { 0 };
	int    nSfrPeakIndex[SLANTED_BW_NUM] = { 0 };//最大值得INdex
	bool bMove = false;

	int FsNum = 0;//控制扫描次数
	CString cstrLog;

	int NewData;
	int cnt;
	//int z = 0;
	int all_find_peak;

	while (FsNum < 5)
	{
		//最大扭转角度次数 : 5 - 1//Sleep(50);
		FsNum++;

		int PeakNum[SLANTED_BW_NUM] = { 0 };//找到peak点标记，连续两次判定为找到peak点
		vector < vector<double>> vdSfrValue;
		vector<double> vdSfrValue1;
		vector<double> vdSfrValue2;
		vector<double> vdSfrValue3;
		vector<double> vdSfrValue4;
		vector<double> vdSfrValue5;

		//*************************************************************************************
		cstrLog.Format(L"Start Focus Scan _ %d", FsNum);
		gSystemLog.DisplayLogAndSave(cstrLog.GetBuffer(), LV_EVENT);

		m_nAAStepCnt = 0;
		all_find_peak = 1;
		for (int i = 0; i < SLANTED_BW_NUM; i++)
		{
			bFindPeak[i] = false;
			fMaxValue[i] = 0;
			nSfrPeakIndex[i] = 0;
			PeakNum[i] = 0;
		}
		for (int z = 0; z < m_nAAStepMaxCnt; z++)//50
		{
			all_find_peak = TRUE;
			bMove = AAMoveStepZ(-m_dAAStep);//步长
			if (bMove == false)
			{
				gSystemLog.DisplayLogAndSave(L"move step z fail", LV_ERROR);
				return false;
			}
			//if (m_nStepWait <= 10)
			//	Sleep(10);
			Sleep(m_nStepWait / 2);
			NewData = m_nNewCapImg;
			cnt = 0;
			while (m_nNewCapImg == NewData)
			{
				Sleep(5);
				cnt++;
				if (cnt > 200)
					return FALSE;
			}
			NewData = m_nNewDataFlag;
			cnt = 0;
			while (m_nNewDataFlag == NewData)
			{
				Sleep(5);
				cnt++;
				if (cnt > 200)
					return FALSE;
			}
			m_nAAStepCnt++;
			//m_nAAStepCnt = z;
			for (int i = 0; i < SLANTED_BW_NUM; i++)
			{
				fSfrValue[i][z] = (float)SfrAvgValue[i];
				FS.oc_x[z][i] = OCx[i];
				FS.oc_y[z][i] = OCy[i];
			}
			for (int i = 0; i < SLANTED_BW_NUM; i++)
			{
				switch (i)
				{
				case 0:
					vdSfrValue1.push_back(fSfrValue[0][z]);
					break;
				case 1:
					vdSfrValue2.push_back(fSfrValue[1][z]);
					break;
				case 2:
					vdSfrValue3.push_back(fSfrValue[2][z]);
					break;
				case 3:
					vdSfrValue4.push_back(fSfrValue[3][z]);
					break;
				case 4:
					vdSfrValue5.push_back(fSfrValue[4][z]);
					break;
				}
				if (bFindPeak[i] == true)
				{
					continue;
				}
				if (fSfrValue[i][z] > fMaxValue[i])
				{
					fMaxValue[i] = fSfrValue[i][z];
					nSfrPeakIndex[i] = z;
				}
				if (fMaxValue[i] - fSfrValue[i][z] > m_nPeakDiff && fMaxValue[i] > m_nPeakMin)
				{
					if (PeakNum[i] == 1)
						bFindPeak[i] = true;
					/*	int index = nSfrPeakIndex;
						if (fSfrValue[index] == fSfrValue[index - 1])
						{
							nSfrPeakIndex -= 1;
						}*/
					PeakNum[i] = 1;
				}
				else
				{
					PeakNum[i] = 0;
				}
				if (bFindPeak[i] == FALSE)	all_find_peak = FALSE;
			}

			cstrLog.Format(L"step%d,sfr[%d]:%.2f,%.2f,%.2f,%.2f,%.2f", z, TestResult, fSfrValue[0][z], fSfrValue[1][z], fSfrValue[2][z], fSfrValue[3][z], fSfrValue[4][z]);
			gSystemLog.DisplayLogAndSave(cstrLog.GetBuffer(), LV_EVENT);
			//cstrLog.Format(L"[%d],[%d],[%d],[%d],[%d]", bFindPeak[0], bFindPeak[1], bFindPeak[2], bFindPeak[3], bFindPeak[4]);
			//gSystemLog.DisplayLogAndSave(cstrLog.GetBuffer(), LV_EVENT);

			//nTotalCount++;

			//vdSfrValue[0].push_back(fSfrValue[0][z]);//暂时画中心
			//DrawFocusCurve(vdSfrValue[0]);

			vdSfrValue.clear();
			vdSfrValue.push_back(vdSfrValue1);
			vdSfrValue.push_back(vdSfrValue2);
			vdSfrValue.push_back(vdSfrValue3);
			vdSfrValue.push_back(vdSfrValue4);
			vdSfrValue.push_back(vdSfrValue5);
			DrawFocusCurve(vdSfrValue);

			if (all_find_peak == TRUE) break;

		}

		vdSfrValue1.clear();
		vdSfrValue2.clear();
		vdSfrValue3.clear();
		vdSfrValue4.clear();
		vdSfrValue5.clear();
		for (int i = 0; i < SLANTED_BW_NUM; i++)
		{
			//get_curve_fitting(MULTI_FACTOR, fSfrValue[i], m_nAAStepCnt, fSfrCruve[i]);//拟合曲线
			FS.fs_peak_index_d[i] = get_curve_fitting_d(MULTI_FACTOR, fSfrValue[i], m_nAAStepCnt, fSfrCruve[i], i);
			float fitted_curve_peak = 0;
			for (int j = 0; j < m_nAAStepCnt; j++)
			{
				switch (i)
				{
				case 0:
					vdSfrValue1.push_back(fSfrCruve[0][j]);
					break;
				case 1:
					vdSfrValue2.push_back(fSfrCruve[1][j]);
					break;
				case 2:
					vdSfrValue3.push_back(fSfrCruve[2][j]);
					break;
				case 3:
					vdSfrValue4.push_back(fSfrCruve[3][j]);
					break;
				case 4:
					vdSfrValue5.push_back(fSfrCruve[4][j]);
					break;
				}

				if (fSfrCruve[i][j] >= fitted_curve_peak)
				{
					fitted_curve_peak = fSfrCruve[i][j];
					nSfrPeakIndex[i] = j;
					FS.fs_peak_index[i] = j;
				}
			}
		}

		//
		BackLeft = DongtaiPos[0][0];
		BackRight = DongtaiPos[0][1];
		for (int i = 0; i < SLANTED_BW_NUM; i++)
		{
			if (BackLeft < DongtaiPos[i][0])
				BackLeft = DongtaiPos[i][0];

			if (BackRight > DongtaiPos[i][1])
				BackRight = DongtaiPos[i][1];
		}


		vdSfrValue.clear();
		vdSfrValue.push_back(vdSfrValue1);
		vdSfrValue.push_back(vdSfrValue2);
		vdSfrValue.push_back(vdSfrValue3);
		vdSfrValue.push_back(vdSfrValue4);
		vdSfrValue.push_back(vdSfrValue5);
		DrawFocusCurve(vdSfrValue);

		for (int i = 0; i < SLANTED_BW_NUM; i++)
		{
			//logdlg.log("roi[%d] peak_index=%d, oc_x=%.2f, oc_y=%.2f", i, FS.fs_peak_index[i], FS.oc_x[FS.fs_peak_index[i]][i], FS.oc_y[FS.fs_peak_index[i]][i]);
			cstrLog.Format(L"roi[%d] peak_index=%.3f, oc_x=%.2f, oc_y=%.2f", i, FS.fs_peak_index_d[i], FS.oc_x[nSfrPeakIndex[i]][i], FS.oc_y[nSfrPeakIndex[i]][i]);
			gSystemLog.DisplayLogAndSave(cstrLog.GetBuffer(), LV_EVENT);
		}
		CalculateTiltXY(m_dAAStep);
		double center_cnt = m_nAAStepCnt - 1 - FS.fs_peak_index_d[0];

		Sleep(50);
		if (abs(FS.tilt_angle[0]) < m_dSpecAAAngle && abs(FS.tilt_angle[1]) < m_dSpecAAAngle)
		{

			//logdlg.log("Move Back %d;%d", center_cnt, center_cnt * 5000 * m_fStepUnit);
			if (m_dCenterPer < 0)m_dCenterPer = 0;
			if (m_dCenterPer > 1)m_dCenterPer = 1;
			double center_cnt2;
			if (OpenDongtaiFlag) {
				center_cnt2 = m_nAAStepCnt - 1 - (BackLeft + BackRight) / 2;
				cstrLog.Format(L"Back Dongtai Step:%.2f - %.2f ", BackLeft, BackRight);
				gSystemLog.DisplayLogAndSave(cstrLog.GetBuffer(), LV_EVENT);
			}
			else
				center_cnt2 = m_nAAStepCnt - 1 - double(FS.fs_peak_index_d[0] * m_dCenterPer) - double(1 - m_dCenterPer)*(FS.fs_peak_index_d[1] + FS.fs_peak_index_d[2] + FS.fs_peak_index_d[3] + FS.fs_peak_index_d[4]) / 4;

			bMove = AAMoveStepZ(center_cnt2 * m_dAAStep);//步长
			//errcode = MoveStepZ(-center_cnt * m_nDirection);
			//Sleep(100);
			cstrLog.Format(L"Back Step:%.2f ", center_cnt2);
			gSystemLog.DisplayLogAndSave(cstrLog.GetBuffer(), LV_EVENT);
			//logdlg.log("After Zpos:%d;%d", motordlg.CurrentPos[2], motordlg.ActualPos[2]);
			cstrLog.Format(L"Focus Scan Done  :%d ", m_vCMotor[MOTOR_Z].m_nCurPositon);
			gSystemLog.DisplayLogAndSave(cstrLog.GetBuffer(), LV_EVENT);

			m_dPeakDis = (nSfrPeakIndex[0] * 4 - nSfrPeakIndex[1] - nSfrPeakIndex[2] - nSfrPeakIndex[3] - nSfrPeakIndex[4])*m_dAAStep;

			return TRUE;

		}
		else
		{
			cstrLog.Format(L"start[%d]", m_vCMotor[MOTOR_Z].m_nCurPositon);
			gSystemLog.DisplayLogAndSave(cstrLog.GetBuffer(), LV_EVENT);
			//errcode = MoveStepZ((-center_cnt - m_nBackOffset) * m_nDirection);
			bMove = AAMoveStepZ((center_cnt + m_nReturnStepCnt) * m_dAAStep);//步长
			if (bMove != 1)
				return FALSE;

			//logdlg.log("back move :%d", center_cnt + m_nReturnStepCnt);
			cstrLog.Format(L"Focus Scan back move :%.3f[%d]", center_cnt + m_nReturnStepCnt, m_vCMotor[MOTOR_Z].m_nCurPositon);
			gSystemLog.DisplayLogAndSave(cstrLog.GetBuffer(), LV_EVENT);

			//bMove = CalibrateTiltAngle();
			bMove = CalibrateTiltAngle2();
			if (bMove != 1)
				return FALSE;
			//if (AA_FS_AUTO_CALIBRATION) {
			//	errcode = CalibrateTiltAngle();
			//	if (errcode != 0)
			//		return errcode;
			//}
			//else
			//	return 0;

			//Sleep(200);
			//bMove = MoveCenter();
			//if (bMove != 1)
				//return FALSE;
		}

	}

	cstrLog.Format(L"Focus Scan Over Circle", m_vCMotor[MOTOR_Z].m_nCurPositon);
	gSystemLog.DisplayLogAndSave(cstrLog.GetBuffer(), LV_ERROR);
	return FALSE;

}

int CSystemManager::FocusScan2(void)
{
	TestResult = 0;
	gSystemLog.DisplayLogAndSave(L"Start Focus Scan 只用中心一个图卡", LV_EVENT);
	int    nTimeout = 0;
	//int    nTotalCount = 0;
	int    nErrcode = 0;
	bool bFindPeak[SLANTED_BW_NUM]{ false };
	float fSfrValue[SLANTED_BW_NUM][100] = { 0 };
	float fSfrCruve[SLANTED_BW_NUM][100] = { 0 };// 拟合曲线
	float fMaxValue[SLANTED_BW_NUM] = { 0 };
	int    nSfrPeakIndex[SLANTED_BW_NUM] = { 0 };//最大值得INdex
	bool bMove = false;

	int FsNum = 0;//控制扫描次数
	CString cstrLog;

	int NewData;
	int cnt;
	//int z = 0;
	int all_find_peak;

	while (FsNum < 5)
	{
		//最大扭转角度次数 : 5 - 1//Sleep(50);
		FsNum++;

		int PeakNum[SLANTED_BW_NUM] = { 0 };//找到peak点标记，连续两次判定为找到peak点
		vector < vector<double>> vdSfrValue;
		vector<double> vdSfrValue1;
		vector<double> vdSfrValue2;
		vector<double> vdSfrValue3;
		vector<double> vdSfrValue4;
		vector<double> vdSfrValue5;

		//*************************************************************************************
		cstrLog.Format(L"Start Focus Scan _ %d", FsNum);
		gSystemLog.DisplayLogAndSave(cstrLog.GetBuffer(), LV_EVENT);

		m_nAAStepCnt = 0;
		all_find_peak = 1;
		for (int i = 0; i < SLANTED_BW_NUM; i++)
		{
			bFindPeak[i] = false;
			fMaxValue[i] = 0;
			nSfrPeakIndex[i] = 0;
			PeakNum[i] = 0;
		}
		for (int z = 0; z < m_nAAStepMaxCnt; z++)//50
		{
			all_find_peak = TRUE;
			bMove = AAMoveStepZ(-m_dAAStep);//步长
			if (bMove == false)
			{
				gSystemLog.DisplayLogAndSave(L"move step z fail", LV_ERROR);
				return false;
			}
			//if (m_nStepWait <= 10)
			//	Sleep(10);
			Sleep(m_nStepWait / 2);
			NewData = m_nNewCapImg;
			cnt = 0;
			while (m_nNewCapImg == NewData)
			{
				Sleep(5);
				cnt++;
				if (cnt > 200)
					return FALSE;
			}
			NewData = m_nNewDataFlag;
			cnt = 0;
			while (m_nNewDataFlag == NewData)
			{
				Sleep(5);
				cnt++;
				if (cnt > 200)
					return FALSE;
			}
			m_nAAStepCnt++;
			//m_nAAStepCnt = z;
			for (int i = 0; i < SLANTED_BW_NUM; i++)
			{
				if (i == 0) {
					fSfrValue[i][z] = (float)SfrAvgValue[i];
					FS.oc_x[z][i] = OCx[i];
					FS.oc_y[z][i] = OCy[i];
				}
				else {
					fSfrValue[i][z] = (float)SfrValue[0][i];
					FS.oc_x[z][i] = (RoiRT[0][i].left + RoiRT[0][i].right) / 2;
					FS.oc_y[z][i] = (RoiRT[0][i].bottom + RoiRT[0][i].top) / 2;
				}
			}
			for (int i = 0; i < SLANTED_BW_NUM; i++)
			{
				switch (i)
				{
				case 0:
					vdSfrValue1.push_back(fSfrValue[0][z]);
					break;
				case 1:
					vdSfrValue2.push_back(fSfrValue[1][z]);
					break;
				case 2:
					vdSfrValue3.push_back(fSfrValue[2][z]);
					break;
				case 3:
					vdSfrValue4.push_back(fSfrValue[3][z]);
					break;
				case 4:
					vdSfrValue5.push_back(fSfrValue[4][z]);
					break;
				}
				if (bFindPeak[i] == true)
				{
					continue;
				}
				if (fSfrValue[i][z] > fMaxValue[i])
				{
					fMaxValue[i] = fSfrValue[i][z];
					nSfrPeakIndex[i] = z;
				}
				if (fMaxValue[i] - fSfrValue[i][z] > m_nPeakDiff && fMaxValue[i] > m_nPeakMin)
				{
					if (PeakNum[i] == 1)
						bFindPeak[i] = true;
					/*	int index = nSfrPeakIndex;
						if (fSfrValue[index] == fSfrValue[index - 1])
						{
							nSfrPeakIndex -= 1;
						}*/
					PeakNum[i] = 1;
				}
				else
				{
					PeakNum[i] = 0;
				}
				if (bFindPeak[i] == FALSE)	all_find_peak = FALSE;
			}

			cstrLog.Format(L"step%d,sfr[%d]:%.2f,%.2f,%.2f,%.2f,%.2f", z, TestResult, fSfrValue[0][z], fSfrValue[1][z], fSfrValue[2][z], fSfrValue[3][z], fSfrValue[4][z]);
			gSystemLog.DisplayLogAndSave(cstrLog.GetBuffer(), LV_EVENT);
			//cstrLog.Format(L"[%d],[%d],[%d],[%d],[%d]", bFindPeak[0], bFindPeak[1], bFindPeak[2], bFindPeak[3], bFindPeak[4]);
			//gSystemLog.DisplayLogAndSave(cstrLog.GetBuffer(), LV_EVENT);

			//nTotalCount++;

			//vdSfrValue[0].push_back(fSfrValue[0][z]);//暂时画中心
			//DrawFocusCurve(vdSfrValue[0]);

			vdSfrValue.clear();
			vdSfrValue.push_back(vdSfrValue1);
			vdSfrValue.push_back(vdSfrValue2);
			vdSfrValue.push_back(vdSfrValue3);
			vdSfrValue.push_back(vdSfrValue4);
			vdSfrValue.push_back(vdSfrValue5);
			DrawFocusCurve(vdSfrValue);

			if (all_find_peak == TRUE) break;

		}

		vdSfrValue1.clear();
		vdSfrValue2.clear();
		vdSfrValue3.clear();
		vdSfrValue4.clear();
		vdSfrValue5.clear();
		for (int i = 0; i < SLANTED_BW_NUM; i++)
		{
			//get_curve_fitting(MULTI_FACTOR, fSfrValue[i], m_nAAStepCnt, fSfrCruve[i]);//拟合曲线
			FS.fs_peak_index_d[i] = get_curve_fitting_d(MULTI_FACTOR, fSfrValue[i], m_nAAStepCnt, fSfrCruve[i], i);
			float fitted_curve_peak = 0;
			for (int j = 0; j < m_nAAStepCnt; j++)
			{
				switch (i)
				{
				case 0:
					vdSfrValue1.push_back(fSfrCruve[0][j]);
					break;
				case 1:
					vdSfrValue2.push_back(fSfrCruve[1][j]);
					break;
				case 2:
					vdSfrValue3.push_back(fSfrCruve[2][j]);
					break;
				case 3:
					vdSfrValue4.push_back(fSfrCruve[3][j]);
					break;
				case 4:
					vdSfrValue5.push_back(fSfrCruve[4][j]);
					break;
				}

				if (fSfrCruve[i][j] >= fitted_curve_peak)
				{
					fitted_curve_peak = fSfrCruve[i][j];
					nSfrPeakIndex[i] = j;
					FS.fs_peak_index[i] = j;
				}
			}
		}

		//
		BackLeft = DongtaiPos[0][0];
		BackRight = DongtaiPos[0][1];
		for (int i = 0; i < SLANTED_BW_NUM; i++)
		{
			if (BackLeft < DongtaiPos[i][0])
				BackLeft = DongtaiPos[i][0];

			if (BackRight > DongtaiPos[i][1])
				BackRight = DongtaiPos[i][1];
		}


		vdSfrValue.clear();
		vdSfrValue.push_back(vdSfrValue1);
		vdSfrValue.push_back(vdSfrValue2);
		vdSfrValue.push_back(vdSfrValue3);
		vdSfrValue.push_back(vdSfrValue4);
		vdSfrValue.push_back(vdSfrValue5);
		DrawFocusCurve(vdSfrValue);

		for (int i = 0; i < SLANTED_BW_NUM; i++)
		{
			//logdlg.log("roi[%d] peak_index=%d, oc_x=%.2f, oc_y=%.2f", i, FS.fs_peak_index[i], FS.oc_x[FS.fs_peak_index[i]][i], FS.oc_y[FS.fs_peak_index[i]][i]);
			cstrLog.Format(L"roi[%d] peak_index=%.3f, oc_x=%.2f, oc_y=%.2f", i, FS.fs_peak_index_d[i], FS.oc_x[nSfrPeakIndex[i]][i], FS.oc_y[nSfrPeakIndex[i]][i]);
			gSystemLog.DisplayLogAndSave(cstrLog.GetBuffer(), LV_EVENT);
		}
		//CalculateTiltXY(m_dAAStep);
		CalculateTiltXY_Plane();
		double center_cnt = m_nAAStepCnt - 1 - FS.fs_peak_index_d[0];

		Sleep(50);
		if (abs(FS.tilt_angle[0]) < m_dSpecAAAngle && abs(FS.tilt_angle[1]) < m_dSpecAAAngle)
		{

			//logdlg.log("Move Back %d;%d", center_cnt, center_cnt * 5000 * m_fStepUnit);
			if (m_dCenterPer < 0)m_dCenterPer = 0;
			if (m_dCenterPer > 1)m_dCenterPer = 1;
			double center_cnt2;
			if (OpenDongtaiFlag) {
				center_cnt2 = m_nAAStepCnt - 1 - (BackLeft + BackRight) / 2;
				cstrLog.Format(L"Back Dongtai Step:%.2f - %.2f ", BackLeft, BackRight);
				gSystemLog.DisplayLogAndSave(cstrLog.GetBuffer(), LV_EVENT);
			}
			else
				center_cnt2 = m_nAAStepCnt - 1 - double(FS.fs_peak_index_d[0] * m_dCenterPer) - double(1 - m_dCenterPer)*(FS.fs_peak_index_d[1] + FS.fs_peak_index_d[2] + FS.fs_peak_index_d[3] + FS.fs_peak_index_d[4]) / 4;

			bMove = AAMoveStepZ(center_cnt2 * m_dAAStep);//步长
			//errcode = MoveStepZ(-center_cnt * m_nDirection);
			//Sleep(100);
			cstrLog.Format(L"Back Step:%.2f ", center_cnt2);
			gSystemLog.DisplayLogAndSave(cstrLog.GetBuffer(), LV_EVENT);
			//logdlg.log("After Zpos:%d;%d", motordlg.CurrentPos[2], motordlg.ActualPos[2]);
			cstrLog.Format(L"Focus Scan Done  :%d ", m_vCMotor[MOTOR_Z].m_nCurPositon);
			gSystemLog.DisplayLogAndSave(cstrLog.GetBuffer(), LV_EVENT);

			m_dPeakDis = (nSfrPeakIndex[0] * 4 - nSfrPeakIndex[1] - nSfrPeakIndex[2] - nSfrPeakIndex[3] - nSfrPeakIndex[4])*m_dAAStep;

			return TRUE;

		}
		else
		{
			cstrLog.Format(L"start[%d]", m_vCMotor[MOTOR_Z].m_nCurPositon);
			gSystemLog.DisplayLogAndSave(cstrLog.GetBuffer(), LV_EVENT);
			//errcode = MoveStepZ((-center_cnt - m_nBackOffset) * m_nDirection);
			bMove = AAMoveStepZ((center_cnt + m_nReturnStepCnt) * m_dAAStep);//步长
			if (bMove != 1)
				return FALSE;

			//logdlg.log("back move :%d", center_cnt + m_nReturnStepCnt);
			cstrLog.Format(L"Focus Scan back move :%.3f[%d]", center_cnt + m_nReturnStepCnt, m_vCMotor[MOTOR_Z].m_nCurPositon);
			gSystemLog.DisplayLogAndSave(cstrLog.GetBuffer(), LV_EVENT);

			//bMove = CalibrateTiltAngle();
			bMove = CalibrateTiltAngle2();
			if (bMove != 1)
				return FALSE;
			//if (AA_FS_AUTO_CALIBRATION) {
			//	errcode = CalibrateTiltAngle();
			//	if (errcode != 0)
			//		return errcode;
			//}
			//else
			//	return 0;

			//Sleep(200);
			//bMove = MoveCenter();
			//if (bMove != 1)
				//return FALSE;
		}

	}

	cstrLog.Format(L"Focus Scan Over Circle", m_vCMotor[MOTOR_Z].m_nCurPositon);
	gSystemLog.DisplayLogAndSave(cstrLog.GetBuffer(), LV_ERROR);
	return FALSE;

}

void CSystemManager::GetRotation(float alfa, float beta, float &theta, float &fai)
{
	float a = -tan(alfa) / sqrt((tan(alfa))*(tan(alfa)) + (tan(beta))*(tan(beta)) + 1);
	float b = -tan(beta) / sqrt((tan(alfa))*(tan(alfa)) + (tan(beta))*(tan(beta)) + 1);
	float c = c = 1 / sqrt((tan(alfa))*(tan(alfa)) + (tan(beta))*(tan(beta)) + 1);
	float k;
	k = (float)sqrt(1.0 / 2.0);
	float a1, b1, c1;
	a1 = k * a + k * b;
	b1 = -k * a + k * b;
	c1 = c;
	theta = atan(a1 / c1);
	fai = atan(b1 / c1);
}

int CSystemManager::CalculateTiltXY(double step_unit)
{
	int result = TRUE;
	int CT = 0;
	int UL = 1;
	int UR = 2;
	int LL = 3;
	int LR = 4;
	int ct_index = FS.fs_peak_index[CT];
	int ul_index = FS.fs_peak_index[UL];
	int ur_index = FS.fs_peak_index[UR];
	int ll_index = FS.fs_peak_index[LL];
	int lr_index = FS.fs_peak_index[LR];

	double x[3] = { 0 };
	double y[3] = { 0 };
	double xx = 0;
	double yy = 0;
	double slope[3] = { 0 };
	double offset[3] = { 0 };
	double psize = m_dPixelSize;
	//if (!UseDefPix)
	//	psize2 = psize;
	double ul_ct = 0;
	double lr_ct = 0;
	double ll_ct = 0;
	double ur_ct = 0;

	xx = pow((FS.oc_x[lr_index][LR] - FS.oc_x[ct_index][CT]), (double)2);
	yy = pow((FS.oc_y[lr_index][LR] - FS.oc_y[ct_index][CT]), (double)2);
	ul_ct = sqrt(xx + yy);

	xx = pow((FS.oc_x[ul_index][UL] - FS.oc_x[ct_index][CT]), (double)2);
	yy = pow((FS.oc_y[ul_index][UL] - FS.oc_y[ct_index][CT]), (double)2);
	lr_ct = sqrt(xx + yy);

	xx = pow((FS.oc_x[ul_index][LL] - FS.oc_x[ct_index][CT]), (double)2);
	yy = pow((FS.oc_y[ul_index][LL] - FS.oc_y[ct_index][CT]), (double)2);
	ll_ct = sqrt(xx + yy);
	xx = pow((FS.oc_x[ul_index][UR] - FS.oc_x[ct_index][CT]), (double)2);
	yy = pow((FS.oc_y[ul_index][UR] - FS.oc_y[ct_index][CT]), (double)2);
	ur_ct = sqrt(xx + yy);

	x[1] = ul_ct * psize/**sqrt((double)2)*/;
	y[1] = (FS.fs_peak_index_d[CT] - FS.fs_peak_index_d[UL])*step_unit;
	x[2] = x[1] + lr_ct * psize/**sqrt((double)2)*/;
	y[2] = (FS.fs_peak_index_d[LR] - FS.fs_peak_index_d[UL])*step_unit;
	GetBestFitLine(x, y, 3, slope[0], offset[0]);

	x[1] = ll_ct * psize/**sqrt((double)2)*/;
	y[1] = (FS.fs_peak_index_d[CT] - FS.fs_peak_index_d[UR])*step_unit;
	x[2] = x[1] + ur_ct * psize/**sqrt((double)2)*/;
	y[2] = (FS.fs_peak_index_d[LL] - FS.fs_peak_index_d[UR])*step_unit;
	GetBestFitLine(x, y, 3, slope[1], offset[1]);

	float new_angle_x = 0;//45 trans
	float new_angle_y = 0;
	if (CHOOSE_XY)
		GetRotation((float)atan(slope[0]), (float)atan(slope[1]), new_angle_x, new_angle_y);
	else
		GetRotation((float)atan(slope[1]), (float)atan(slope[0]), new_angle_x, new_angle_y);

	FS.tilt_angle[0] = -new_angle_x * 180.0 / PI;
	FS.tilt_angle[1] = -new_angle_y * 180.0 / PI;
	//if (SYMBOL1) {
	//	if (SYMBOL2) {
	//		FS.tilt_angle[0] = new_angle_x * 180.0 / PI;
	//		FS.tilt_angle[1] = new_angle_y * 180.0 / PI;
	//	}
	//	else {
	//		FS.tilt_angle[0] = new_angle_x * 180.0 / PI;
	//		FS.tilt_angle[1] = -new_angle_y * 180.0 / PI;
	//	}
	//}
	//else {
	//	if (SYMBOL2) {
	//		FS.tilt_angle[0] = -new_angle_x * 180.0 / PI;
	//		FS.tilt_angle[1] = new_angle_y * 180.0 / PI;
	//	}
	//	else {
	//		FS.tilt_angle[0] = -new_angle_x * 180.0 / PI;
	//		FS.tilt_angle[1] = -new_angle_y * 180.0 / PI;
	//	}
	//}

	TiltX = FS.tilt_angle[0];
	TiltY = FS.tilt_angle[1];
	//logdlg.log("new x tilt:%.4f, y tilt:%.4f", FS.tilt_angle[0], FS.tilt_angle[1]);

	CString cstrLog;
	cstrLog.Format(L"new x tilt:%.4f, y tilt:%.4f", FS.tilt_angle[0], FS.tilt_angle[1]);
	gSystemLog.DisplayLogAndSave(cstrLog.GetBuffer(), LV_EVENT);

	//double change = 0;
	//if (capturedlg.ChangeXY) {
	//	change = FS.tilt_angle[0];
	//	FS.tilt_angle[0] = FS.tilt_angle[1];
	//	FS.tilt_angle[1] = change;
	//}

	return result;

}

int CSystemManager::CalculateTiltXY_Plane()
{
	int result = TRUE;
	double Pi = 180.0 / 3.1415926;

	CvMat* points_mat = cvCreateMat(4, 3, CV_32FC1);
	for (int i = 0; i < 4; i++) {
		points_mat->data.fl[i * 3 + 0] = FS.oc_x[FS.fs_peak_index[i + 1]][i + 1] * m_dPixelSize;
		points_mat->data.fl[i * 3 + 1] = FS.oc_y[FS.fs_peak_index[i + 1]][i + 1] * m_dPixelSize;
		points_mat->data.fl[i * 3 + 2] = FS.fs_peak_index_d[i + 1] * m_dAAStep;
	}

	float plane[4] = { 0 };
	cvFitPlane(points_mat, plane);
	CString cstr;
	for (int i = 0; i < 4; i++)
	{
		cstr.Format(L"plane%d = %f\n", i, plane[i]);
		gSystemLog.DisplayLogAndSave(cstr.GetBuffer(), LV_ERROR);
	}

	//plane[0]; plane[1]; plane[2];//xyz
	double d = 0;
	double xx = 0;
	double yy = 0;


	//tilt x
	//plane[1] plane[2];
	double tiltx = 0;
	tiltx = atan(plane[1] / plane[2]) * Pi;
	//y
	xx = pow((plane[1]), (double)2);
	yy = pow((plane[2]), (double)2);
	d = sqrt(xx + yy);
	if (plane[2] < 0)d = -d;
	double tilty_t = 0;
	tilty_t = atan(plane[0] / d) * Pi;

	CString cstrLog;

	//cstrLog.Format(L"d:%f", d);
	//gSystemLog.DisplayLogAndSave(cstrLog.GetBuffer(), LV_EVENT);

	//cstrLog.Format(L"tiltx:%f, tilty_t:%f", tiltx, tilty_t);
	//gSystemLog.DisplayLogAndSave(cstrLog.GetBuffer(), LV_EVENT);


	//tilt y
	//plane[0] plane[2]
	double tilty = 0;
	tilty = atan(plane[0] / plane[2]) * Pi;
	//y
	xx = pow((plane[0]), (double)2);
	yy = pow((plane[2]), (double)2);
	d = sqrt(xx + yy);
	if (plane[2] < 0)d = -d;
	double tiltx_t = 0;
	tiltx_t = atan(plane[1] / d) * Pi;

	//cstrLog.Format(L"d:%f", d);
	//gSystemLog.DisplayLogAndSave(cstrLog.GetBuffer(), LV_EVENT);

	//cstrLog.Format(L"tilty:%f, tiltx_t:%f", tilty, tiltx_t);
	//gSystemLog.DisplayLogAndSave(cstrLog.GetBuffer(), LV_EVENT);

	if (XFlag == 0) {
		if (YFlag == 0) {
			FS.tilt_angle[0] = tiltx;
			FS.tilt_angle[1] = tilty;
		}
		else {
			FS.tilt_angle[0] = tiltx;
			FS.tilt_angle[1] = -tilty;
		}
	}
	else {
		if (YFlag == 0) {
			FS.tilt_angle[0] = -tiltx;
			FS.tilt_angle[1] = tilty;
		}
		else {
			FS.tilt_angle[0] = -tiltx;
			FS.tilt_angle[1] = -tilty;
		}
	}
	TiltX = FS.tilt_angle[0];
	TiltY = FS.tilt_angle[1];
	//logdlg.log("new x tilt:%.4f, y tilt:%.4f", FS.tilt_angle[0], FS.tilt_angle[1]);

	cstrLog.Format(L"new x tilt:%.4f, y tilt:%.4f", FS.tilt_angle[0], FS.tilt_angle[1]);
	gSystemLog.DisplayLogAndSave(cstrLog.GetBuffer(), LV_EVENT);

	return result;

}

int CSystemManager::CalibrateTiltAngle()
{
	int result = TRUE;
	int cycletime = 0;
	int err = 0;
	//logdlg.log("start calibrate tilt angle.");
	gSystemLog.DisplayLogAndSave(L"start calibrate tilt angle.", LV_EVENT);

	if (abs(FS.tilt_angle[0]) > m_dAngleLimitSpec || abs(FS.tilt_angle[1]) > m_dAngleLimitSpec)
	{
		gSystemLog.DisplayLogAndSave(L"tilt angle over range.", LV_ERROR);
		//logdlg.log("tilt angle over range.");
		return FALSE;
	}

	err = MoveStepXtYt(-FS.tilt_angle[0], -FS.tilt_angle[1]);
	if (!err)
	{
		gSystemLog.DisplayLogAndSave(L"Move XtYt Error", LV_ERROR);
		return FALSE;
	}
	/*err = */MoveCenter();
	//logdlg.log("xt move angle:%f ; yt move angle:%f", FS.tilt_angle[0], FS.tilt_angle[1]);
	CString cstrLog;
	cstrLog.Format(L"xt move angle:%f ; yt move angle:%f", FS.tilt_angle[0], FS.tilt_angle[1]);
	gSystemLog.DisplayLogAndSave(cstrLog.GetBuffer(), LV_EVENT);
	return err;

}

int CSystemManager::CalibrateTiltAngle2()
{
	int result = TRUE;
	int cycletime = 0;
	int err = 0;
	gSystemLog.DisplayLogAndSave(L"start calibrate tilt angle.", LV_EVENT);
	if (CalibrationLimit < 0)
		CalibrationLimit = -CalibrationLimit;
	cycletime = 5;
	if (abs(FS.tilt_angle[0]) > m_dAngleLimitSpec || abs(FS.tilt_angle[1]) > m_dAngleLimitSpec) {
		gSystemLog.DisplayLogAndSave(L"tilt angle over range.", LV_ERROR);
		return FALSE;
	}
	while (cycletime > 0) {
		cycletime--;
		if (FS.tilt_angle[0] > CalibrationLimit) {
			if (FS.tilt_angle[1] > CalibrationLimit) {
				err = MoveStepXtYt(-CalibrationLimit, -CalibrationLimit);
				err += MoveCenter();
				FS.tilt_angle[0] = FS.tilt_angle[0] - CalibrationLimit;
				FS.tilt_angle[1] = FS.tilt_angle[1] - CalibrationLimit;
			}
			else if (FS.tilt_angle[1] < -CalibrationLimit) {
				err = MoveStepXtYt(-CalibrationLimit, CalibrationLimit);
				err += MoveCenter();
				FS.tilt_angle[0] = FS.tilt_angle[0] - CalibrationLimit;
				FS.tilt_angle[1] = FS.tilt_angle[1] + CalibrationLimit;
			}
			else {
				err = MoveStepXtYt(-CalibrationLimit, -FS.tilt_angle[1]);
				err += MoveCenter();
				FS.tilt_angle[0] = FS.tilt_angle[0] - CalibrationLimit;
				FS.tilt_angle[1] = 0;
			}
		}
		else if (FS.tilt_angle[0] < -CalibrationLimit) {
			if (FS.tilt_angle[1] > CalibrationLimit) {
				err = MoveStepXtYt(CalibrationLimit, -CalibrationLimit);
				err += MoveCenter();
				FS.tilt_angle[0] = FS.tilt_angle[0] + CalibrationLimit;
				FS.tilt_angle[1] = FS.tilt_angle[1] - CalibrationLimit;
			}
			else if (FS.tilt_angle[1] < -CalibrationLimit) {
				err = MoveStepXtYt(CalibrationLimit, CalibrationLimit);
				err += MoveCenter();
				FS.tilt_angle[0] = FS.tilt_angle[0] + CalibrationLimit;
				FS.tilt_angle[1] = FS.tilt_angle[1] + CalibrationLimit;
			}
			else {
				err = MoveStepXtYt(CalibrationLimit, -FS.tilt_angle[1]);
				err += MoveCenter();
				FS.tilt_angle[0] = FS.tilt_angle[0] + CalibrationLimit;
				FS.tilt_angle[1] = 0;
			}
		}
		else {
			if (FS.tilt_angle[1] > CalibrationLimit) {
				err = MoveStepXtYt(-FS.tilt_angle[0], -CalibrationLimit);
				err += MoveCenter();
				FS.tilt_angle[0] = 0;
				FS.tilt_angle[1] = FS.tilt_angle[1] - CalibrationLimit;
			}
			else if (FS.tilt_angle[1] < -CalibrationLimit) {
				err = MoveStepXtYt(-FS.tilt_angle[0], CalibrationLimit);
				err += MoveCenter();
				FS.tilt_angle[0] = 0;
				FS.tilt_angle[1] = FS.tilt_angle[1] + CalibrationLimit;
			}
			else {
				err = MoveStepXtYt(-FS.tilt_angle[0], -FS.tilt_angle[1]);
				err += MoveCenter();
				FS.tilt_angle[0] = 0;
				FS.tilt_angle[1] = 0;
			}
		}
		if (err != 2) {
			gSystemLog.DisplayLogAndSave(L"错误1", LV_EVENT);
			return FALSE;
		}
		if (FS.tilt_angle[0] == 0 && FS.tilt_angle[1] == 0)
			break;
	}
	CString cstrLog;
	cstrLog.Format(L"xt move angle:%f ; yt move angle:%f", FS.tilt_angle[0], FS.tilt_angle[1]);
	gSystemLog.DisplayLogAndSave(cstrLog.GetBuffer(), LV_EVENT);
	return TRUE;
	
}

void CSystemManager::DrawFocusCurve(vector < vector<double>> vdSfrValue)
{
	int nChartXCount = m_nAAStepCnt;// m_sControlByHand.m_nFocusStepCount;

	int nChartWidth = 2560;//控件的宽度
	int nChartHeight = 200;//控件的高度

	int nBeginX = nChartWidth / 9;
	int nEndX = nChartWidth / 9;
	int nBeginY = nChartHeight / 9;
	int nEndY = nChartHeight / 20;

	int Cnt = 6;//Y坐标高度 = Cnt*20
	CDrawCurve drawCurve;
	HWND hPaint = GetDlgItem(m_ptrMainUI->GetSafeHwnd(), IDC_AA_CURVE);
	HDC hMemdc = drawCurve.CreateChart(hPaint, nChartWidth, nChartHeight, nBeginX, nEndX, nBeginY, nEndY);
	SetTextColor(hMemdc, RGB(255, 255, 255));

	drawCurve.DrawAxisXInt(hMemdc, nChartXCount, L"Steps");
	drawCurve.DrawAxisYFloat(hMemdc, (Cnt + 1), L"Value");

	HFONT font = CreateFont(15, 0, 0, 0, FW_BLACK, 0, 0, 0, ANSI_CHARSET, 0, 0, 0, 0, L"黑体");
	HFONT old_font = (HFONT)SelectObject(hMemdc, font);
	TextOut(hMemdc, nBeginX + nChartWidth / 10, 5, L"MTF SCAN", 9);
	DeleteObject(font);
	font = CreateFont(10, 0, 0, 0, FW_BLACK, 0, 0, 0, ANSI_CHARSET, 0, 0, 0, 0, L"黑体");
	old_font = (HFONT)SelectObject(hMemdc, font);

	HPEN pen, old_pen;
	pen = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));

	int nRatioX = (nChartWidth - nBeginX - nEndX) / nChartXCount;//横坐标的比例
	int nAxisYStep = (nChartHeight - nBeginY - nEndY) / Cnt;//Y轴的数值20代表的高度
	CString cstr;
	cstr.Format(L"sfr lenth:%d", vdSfrValue.size());
	//gSystemLog.DisplayLogAndSave(cstr.GetBuffer(), LV_EVENT);

	for (int i = 0; i < (int)vdSfrValue.size(); i++)
	{
		old_pen = (HPEN)SelectObject(hMemdc, pen);
		DeleteObject(pen);
		if (i == 0)
		{
			pen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
			SelectObject(hMemdc, pen);
		}
		else if (i == 1)
		{
			pen = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
			SelectObject(hMemdc, pen);
		}
		else if (i == 2)
		{
			pen = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
			SelectObject(hMemdc, pen);
		}
		else if (i == 3)
		{
			pen = CreatePen(PS_SOLID, 1, RGB(160, 61, 153));
			SelectObject(hMemdc, pen);
		}
		else if (i == 4)
		{
			pen = CreatePen(PS_SOLID, 1, RGB(206, 139, 15));
			SelectObject(hMemdc, pen);
		}

		if (vdSfrValue[i].size() > 1)
		{
			int nSize = vdSfrValue[i].size() - 1;
			for (int j = 0; j < nSize; j++)
			{
				int nY1Pos = (int)((nChartHeight - nBeginY - nEndY) - vdSfrValue[i][j] /** 5*/ / 20 * nAxisYStep + nBeginY);
				int nY2Pos = (int)((nChartHeight - nBeginY - nEndY) - vdSfrValue[i][j + 1] /** 5*/ / 20 * nAxisYStep + nBeginY);

				//cstr.Format(L"1:%d,%.2f,%d,%d", nChartHeight - nBeginY - nEndY, vdSfrValue[i][j], nAxisYStep, nBeginY);
				//gSystemLog.DisplayLogAndSave(cstr.GetBuffer(), LV_EVENT);
				//int nYPos = (int)(m_nChartHeight - m_nBeginY - m_nEndY) - i * nAxisYStep + m_nBeginY;
				////图标上面点的纵坐标Y，靠上的部分
				////图标上面点的纵坐标Y，靠下的部分

				//MoveToEx(hMemdc, m_nBeginX, nYPos, NULL);
				//LineTo(hMemdc, m_nChartWidth - m_nEndX, nYPos);

				MoveToEx(hMemdc, j* nRatioX + nBeginX, nY1Pos, NULL);
				LineTo(hMemdc, (j + 1) * nRatioX + nBeginX, nY2Pos);
			}
		}

	}




	DeleteObject(pen);
	DeleteObject(font);
	//DeleteObject(old_pen);
	//DeleteObject(old_font);

	drawCurve.CloseChart(hPaint, hMemdc);
}

void pivot(unsigned char k, unsigned char n, float a[M + 1][M + 2])
{
	int  t, i, j;
	float x, y;
	x = fabs(a[k][k]);
	t = k;
	for (i = k + 1; i <= n; i++)
	{
		if (fabs(a[i][k]) > x)
		{
			x = fabs(a[i][k]);
			t = i;
		}
	}

	for (j = k; j <= n + 1; j++)
	{
		y = a[k][j];
		a[k][j] = a[t][j];
		a[t][j] = y;
	}
}
void xiaoyuan(unsigned char n, float a[M + 1][M + 2])
{
	int i, j, k;
	for (i = 0; i < n; i++)
	{
		pivot(i, n, a);
		for (j = i + 1; j <= n; j++)
		{
			for (k = i + 1; k <= n + 1; k++)
			{
				a[j][k] = a[j][k] - a[j][i] * a[i][k] / a[i][i];
			}
		}
	}
}
void back_substitution(unsigned char n, float a[M + 1][M + 2], float x[M + 1])
{
	int i, j;
	x[n] = a[n][n + 1] / a[n][n];
	for (i = n - 1; i >= 0; i--)
	{
		x[i] = a[i][n + 1];
		for (j = i + 1; j <= n; j++)
		{
			x[i] = x[i] - a[i][j] * x[j];
		}
		x[i] = x[i] / a[i][i];
	}
}

void CSystemManager::get_curve_fitting(int factor_num, float * input_data, int length, float * output_data)
{
	float a[M + 1][M + 2], A[N2][K + 1], B[100][M + 1], AA[K + 1], BB[M + 1];
	int f_n = length;
	int f_k = factor_num * 2;
	int f_m = factor_num;
	float *index_data = new float[length];
	for (int x = 0; x < length; x++)
	{
		index_data[x] = (float)(x + 1);
	}

	float m[10] = { 0 };

	unsigned char i, j, n;
	for (i = 0; i < f_n; i++)
	{
		A[i][0] = 1;
		for (j = 1; j <= f_k; j++)
		{
			A[i][j] = A[i][j - 1] * index_data[i];
		}
		for (j = 0; j <= f_m; j++)
		{
			B[i][j] = A[i][j] * input_data[i];
		}
	}
	for (j = 0; j <= f_k; j++)
	{
		for (AA[j] = 0, i = 0; i < f_n; i++)
		{
			AA[j] += A[i][j];
		}
	}
	for (j = 0; j <= f_m; j++)
	{
		for (BB[j] = 0, i = 0; i < f_n; i++)
		{
			BB[j] += B[i][j];
		}
	}
	for (i = 0; i < f_m + 1; i++)
	{
		a[i][f_m + 1] = BB[i];
		for (j = 0; j <= f_m; j++)
		{
			a[i][j] = AA[i + j];
		}
	}
	n = f_m;
	xiaoyuan(n, a);
	back_substitution(n, a, m);

	for (i = 0; i < length; i++)
	{
		switch (factor_num)
		{
		case 1:
			output_data[i] = m[0] + m[1] * (i + 1);
			break;

		case 2:
			output_data[i] = m[0] + m[1] * (i + 1) + m[2] * (i + 1)*(i + 1);
			break;

		case 3:
			output_data[i] = m[0] + m[1] * (i + 1) + m[2] * (i + 1)*(i + 1) + m[3] * (i + 1)*(i + 1)*(i + 1);
			break;

		case 4:
			output_data[i] = m[0] + m[1] * (i + 1) + m[2] * (i + 1)*(i + 1) + m[3] * (i + 1)*(i + 1)*(i + 1) + m[4] * (i + 1)*(i + 1)*(i + 1)*(i + 1);
			break;

		case 5:
			output_data[i] = m[0] + m[1] * (i + 1) + m[2] * (i + 1)*(i + 1) + m[3] * (i + 1)*(i + 1)*(i + 1) + m[4] * (i + 1)*(i + 1)*(i + 1)*(i + 1) +
				m[5] * (i + 1)*(i + 1)*(i + 1)*(i + 1)*(i + 1);
			break;

		case 6:
			output_data[i] = m[0] + m[1] * (i + 1) + m[2] * (i + 1)*(i + 1) + m[3] * (i + 1)*(i + 1)*(i + 1) + m[4] * (i + 1)*(i + 1)*(i + 1)*(i + 1) +
				m[5] * (i + 1)*(i + 1)*(i + 1)*(i + 1)*(i + 1) + m[6] * (i + 1)*(i + 1)*(i + 1)*(i + 1)*(i + 1)*(i + 1);
			break;

		case 7:
			output_data[i] = m[0] + m[1] * (i + 1) + m[2] * (i + 1)*(i + 1) + m[3] * (i + 1)*(i + 1)*(i + 1) + m[4] * (i + 1)*(i + 1)*(i + 1)*(i + 1) +
				m[5] * (i + 1)*(i + 1)*(i + 1)*(i + 1)*(i + 1) + m[6] * (i + 1)*(i + 1)*(i + 1)*(i + 1)*(i + 1)*(i + 1) +
				m[7] * (i + 1)*(i + 1)*(i + 1)*(i + 1)*(i + 1)*(i + 1)*(i + 1);
			break;

		case 8:
			output_data[i] = m[0] + m[1] * (i + 1) + m[2] * (i + 1)*(i + 1) + m[3] * (i + 1)*(i + 1)*(i + 1) + m[4] * (i + 1)*(i + 1)*(i + 1)*(i + 1) +
				m[5] * (i + 1)*(i + 1)*(i + 1)*(i + 1)*(i + 1) + m[6] * (i + 1)*(i + 1)*(i + 1)*(i + 1)*(i + 1)*(i + 1) +
				m[7] * (i + 1)*(i + 1)*(i + 1)*(i + 1)*(i + 1)*(i + 1)*(i + 1) + m[8] * (i + 1)*(i + 1)*(i + 1)*(i + 1)*(i + 1)*(i + 1)*(i + 1)*(i + 1);
			break;

		case 9:
			output_data[i] = m[0] + m[1] * (i + 1) + m[2] * (i + 1)*(i + 1) + m[3] * (i + 1)*(i + 1)*(i + 1) + m[4] * (i + 1)*(i + 1)*(i + 1)*(i + 1) +
				m[5] * (i + 1)*(i + 1)*(i + 1)*(i + 1)*(i + 1) + m[6] * (i + 1)*(i + 1)*(i + 1)*(i + 1)*(i + 1)*(i + 1) +
				m[7] * (i + 1)*(i + 1)*(i + 1)*(i + 1)*(i + 1)*(i + 1)*(i + 1) + m[8] * (i + 1)*(i + 1)*(i + 1)*(i + 1)*(i + 1)*(i + 1)*(i + 1)*(i + 1) +
				m[9] * (i + 1)*(i + 1)*(i + 1)*(i + 1)*(i + 1)*(i + 1)*(i + 1)*(i + 1)*(i + 1);
			break;
		}
	}
	delete[] index_data;
}

double CSystemManager::get_curve_fitting_d(int factor_num, float * input_data, int length, float * output_data, int cnt)
{
	float a[M + 1][M + 2], A[N2][K + 1], B[100][M + 1], AA[K + 1], BB[M + 1];
	int f_n = length;
	int f_k = factor_num * 2;
	int f_m = factor_num;
	float *index_data = new float[length];
	for (int x = 0; x < length; x++)
	{
		index_data[x] = (float)(x + 1);
	}

	float m[10] = { 0 };

	unsigned char i, j, n;
	for (i = 0; i < f_n; i++)
	{
		A[i][0] = 1;
		for (j = 1; j <= f_k; j++)
		{
			A[i][j] = A[i][j - 1] * index_data[i];
		}
		for (j = 0; j <= f_m; j++)
		{
			B[i][j] = A[i][j] * input_data[i];
		}
	}
	for (j = 0; j <= f_k; j++)
	{
		for (AA[j] = 0, i = 0; i < f_n; i++)
		{
			AA[j] += A[i][j];
		}
	}
	for (j = 0; j <= f_m; j++)
	{
		for (BB[j] = 0, i = 0; i < f_n; i++)
		{
			BB[j] += B[i][j];
		}
	}
	for (i = 0; i < f_m + 1; i++)
	{
		a[i][f_m + 1] = BB[i];
		for (j = 0; j <= f_m; j++)
		{
			a[i][j] = AA[i + j];
		}
	}
	n = f_m;
	xiaoyuan(n, a);
	back_substitution(n, a, m);

	for (i = 0; i < length; i++)
	{
		output_data[i] = m[0] + m[1] * (i + 1) + m[2] * (i + 1)*(i + 1) + m[3] * (i + 1)*(i + 1)*(i + 1) + m[4] * (i + 1)*(i + 1)*(i + 1)*(i + 1);
	}
	delete[] index_data;

	double step = 0;
	double Max_m = 0;
	double MaxStep = 0;
	double stepadd = 0;
	stepadd = fabs(double(0.001 / m_dAAStep));
	if (stepadd < 0.1) {
		stepadd = 0.1;
	}

	//动态权重
	//DongtaiPos[cnt][0];
	//DongtaiPos[cnt][1];
	int no;
	if (cnt == 0) {
		no = 0;
	}
	else {
		no = 1;
	}
	int flag = 0;

	while (step < length) {
		double j = step;
		double number = m[0] + m[1] * (j + 1) + m[2] * (j + 1)*(j + 1) + m[3] * (j + 1)*(j + 1)*(j + 1) + m[4] * (j + 1)*(j + 1)*(j + 1)*(j + 1);
		step = step + stepadd;
		if (number > Max_m) {
			Max_m = number;
			MaxStep = step;
		}

		if (number > m_dSpecSfr[no]) {
			DongtaiPos[cnt][1] = step;
		}
		if (flag == 0 && number > m_dSpecSfr[no]) {
			flag = 1;
			DongtaiPos[cnt][0] = step;
		}
	}
	return MaxStep;
}

void CSystemManager::StartScanButtonValueThread()
{
	ProcScanBtn.MemProc = &CSystemManager::ScanButtonValueThread;
	UINT nThreadId;
	HANDLE hThread = (HANDLE)_beginthreadex(NULL, 0, ProcScanBtn.ThreadProc, (LPVOID)this, 0, &nThreadId);
	if (hThread == NULL)
	{
		return;
	}
	m_vWorkerThread.push_back(hThread);
}

unsigned int __stdcall CSystemManager::ScanButtonValueThread()
{
	int result = 0;
	CString cstrlog;
	while (0 == m_nExitFlag)
	{
		Sleep(50);
		int nBtnValue = m_nButtonValue;
		if (nBtnValue == 0)continue;
		cstrlog.Format(L"Start Button Value:%d", nBtnValue);
		m_nButtonDone = 0;
		gSystemLog.DisplayLogAndSave(cstrlog.GetBuffer(), LV_ERROR);
		switch (nBtnValue)
		{
		case 0:
			break;
		case 10://回零线程
			if (IDYES == AfxMessageBox(L"确定归位吗？", MB_YESNO))
			{
				if (S23)
				{
					AfxMessageBox(L"请先启动控制开按钮！", MB_OK);
					break;
				}
				bool bHome = HomeAll();
				//bool bHome = AllMotorHome();
				if (bHome)
				{
					//EnableWindow(GetDlgItem(m_ptrMainUI->GetSafeHwnd(), IDC_BUTTON_START), TRUE);
					gSystemLog.DisplayLogAndSave(L"40站复位成功", LV_ERROR);
					m_bHomeFlag = 1;
					result = PickLens();
					if (!result)
					{
						gSystemLog.DisplayLogAndSave(L"AA夹爪移动错误 - 2!", LV_ERROR);
					}
				}
				else
					gSystemLog.DisplayLogAndSave(L"40站复位失败", LV_ERROR);

				if (abs(m_vCMotor[M_CHART_Z].m_nCurPositon - ChartPos) > 100 && ChartOpenFlag == 1) {
					bHome = ChartMotorHome();
					if (bHome)
					{
						gSystemLog.DisplayLogAndSave(L"图卡轴复位成功", LV_ERROR);
						result = MoveChart();
						if (!result)
						{
							gSystemLog.DisplayLogAndSave(L"图卡移动到位错误!", LV_ERROR);
						}
					}
					else
						gSystemLog.DisplayLogAndSave(L"图卡轴复位失败", LV_ERROR);
				}
			}
			//EnableWindow(GetDlgItem(m_ptrMainUI->GetSafeHwnd(), IDC_BUTTON_HOME), TRUE);
			break;
		case 11://轴 - 回零线程
			if (IDYES == AfxMessageBox(L"确定归位 - 轴 吗？", MB_YESNO))
			{
				bool bHome = AllMotorHome();
				if (bHome)
				{
					//EnableWindow(GetDlgItem(m_ptrMainUI->GetSafeHwnd(), IDC_BUTTON_START), TRUE);
					gSystemLog.DisplayLogAndSave(L"轴复位成功", LV_ERROR);
					m_bHomeFlag = 1;
					result = PickLens();
					if (!result)
					{
						gSystemLog.DisplayLogAndSave(L"AA夹爪移动错误 - 2!", LV_ERROR);
					}
				}
				else
					gSystemLog.DisplayLogAndSave(L"轴复位失败", LV_ERROR);
			}
			//EnableWindow(GetDlgItem(m_ptrMainUI->GetSafeHwnd(), IDC_BUTTON_HOME), TRUE);
			break;
		case 12://图卡轴 - 回零线程
			if (IDYES == AfxMessageBox(L"确定归位 - 图卡Z轴 吗？", MB_YESNO))
			{
				bool bHome = ChartMotorHome();
				if (bHome)
				{
					gSystemLog.DisplayLogAndSave(L"图卡轴复位成功", LV_ERROR);
					result = MoveChart();
					if (!result)
					{
						gSystemLog.DisplayLogAndSave(L"图卡移动到位错误!", LV_ERROR);
					}
				}
				else
					gSystemLog.DisplayLogAndSave(L"图卡轴复位失败", LV_ERROR);
			}
			//EnableWindow(GetDlgItem(m_ptrMainUI->GetSafeHwnd(), IDC_BUTTON_HOME), TRUE);
			break;



		case 20://回夹取位置
			result = PickLens();
			break;
		case 21://夹镜头去AA位置
			result = LoadLens();
			break;
		case 22://Search Z
			result = SearchZ();
			break;
		case 23://Move Center
			result = MoveCenter();
			break;
		case 24://AA
			result = FocusScan();
			break;
		case 25://Full AA
			result = SearchZ();
			if (result)
			{
				result = MoveCenter();
				if (result)
				{
					result = FocusScan();
					if (result)
					{
						result = MoveCenter();
					}
				}
			}
			Sleep(1000);
			if (!result)
			{
				gSystemLog.DisplayLogAndSave(L"AA调焦 - 失败", LV_ERROR);
			}
			else
			{
				gSystemLog.DisplayLogAndSave(L"AA调焦 - 成功", LV_ERROR);
				//SaveTestReport2(imgCap->bBmpTestBuf, imgCap->iBmpW, imgCap->iBmpH, 4);
			}
			break;
		case 26://Full AA
			if (IDYES == AfxMessageBox(L"确定 进行AA动作 吗？", MB_YESNO))
			{
				result = SearchZ();
				if (result)
				{
					result = MoveCenter();
					if (result)
					{
						result = FocusScan();
						if (result)
						{
							result = MoveCenter();
						}
					}
				}
				Sleep(1000);
				if (!result)
				{
					gSystemLog.DisplayLogAndSave(L"AA调焦 - 失败", LV_ERROR);
				}
				else
				{
					gSystemLog.DisplayLogAndSave(L"AA调焦 - 成功", LV_ERROR);
					//SaveTestReport2(imgCap->bBmpTestBuf, imgCap->iBmpW, imgCap->iBmpH, 4);
				}
			}
			break;

		case 27:
			if (IDYES == AfxMessageBox(L"确定 手动AA结束 吗？", MB_YESNO))
			{
				m_bManualDone = 1;
			}
			break;
		case 28:
			//if (IDYES == AfxMessageBox(L"确定 手动AA结束 吗？", MB_YESNO))
			//{
			//	RestartAA = 1;
			//}
			break;


			//串口通讯
		case 33:
		{
			RFID_MSG m_cRfid;
			CString cstr;
			gSystemLog.DisplayLogAndSave(L"Start Send Com_2 Rfid", LV_EVENT);
			memset(output, 0, sizeof(output));
			m_cRfidComm2.send_data_feedback((BYTE*)Read_Rfid, sizeof(Read_Rfid), (BYTE*)output, sizeof(output));
			USES_CONVERSION;
			cstr.Format(L"30-AA[%d]%s", strlen(output), A2T(output));
			gSystemLog.DisplayLogAndSave(cstr.GetBuffer(), LV_EVENT);
			m_cRfid.m_nId = output[4];
			cstr.Format(L"托盘ID[%d]", m_cRfid.m_nId);
			gSystemLog.DisplayLogAndSave(cstr.GetBuffer(), LV_EVENT);
			m_cRfid.m_nNextStation = output[6];
			cstr.Format(L"目标工位[%d]", m_cRfid.m_nNextStation);
			gSystemLog.DisplayLogAndSave(cstr.GetBuffer(), LV_EVENT);
			m_cRfid.m_bCameraIn = output[8];
			cstr.Format(L"产品有无[%d]", m_cRfid.m_bCameraIn);
			gSystemLog.DisplayLogAndSave(cstr.GetBuffer(), LV_EVENT);
			m_cRfid.m_bCameraStatus = output[10];
			cstr.Format(L"产品状态[%d]", m_cRfid.m_bCameraStatus);
			gSystemLog.DisplayLogAndSave(cstr.GetBuffer(), LV_EVENT);
			m_cRfid.m_nNGStation = output[12];
			cstr.Format(L"NG工位[%d]", m_cRfid.m_nNGStation);
			gSystemLog.DisplayLogAndSave(cstr.GetBuffer(), LV_EVENT);

			memset(output2, 0, sizeof(output2));
			m_cRfidComm2.send_data_feedback((BYTE*)Read_SN, sizeof(Read_SN), (BYTE*)output2, sizeof(output2));
			for (int i = 0; i < 50; i++) {
				SN[i] = output2[i + 3];
			}
			cstr.Format(L"条码[%s]", A2T(SN));
			gSystemLog.DisplayLogAndSave(cstr.GetBuffer(), LV_EVENT);

			gSystemLog.DisplayLogAndSave(L"End Send Com_2 Rfid", LV_EVENT);
		}
			break;
		case 34:
			gSystemLog.DisplayLogAndSave(L"Write OK Send Com_2 Rfid", LV_EVENT);
			memset(output, 0, sizeof(output));
			m_cRfidComm2.send_data_feedback((BYTE*)Next_10, sizeof(Next_10), (BYTE*)output, sizeof(output));
			Sleep(100);
			m_cRfidComm2.send_data_feedback((BYTE*)CameraIn_1, sizeof(CameraIn_1), (BYTE*)output, sizeof(output));
			Sleep(100);
			m_cRfidComm2.send_data_feedback((BYTE*)Result_1, sizeof(Result_1), (BYTE*)output, sizeof(output));
			Sleep(100);
			m_cRfidComm2.send_data_feedback((BYTE*)NG_00, sizeof(NG_00), (BYTE*)output, sizeof(output));
			gSystemLog.DisplayLogAndSave(L"End Send Rfid", LV_EVENT);
			break;
		case 35:
			gSystemLog.DisplayLogAndSave(L"Write NG Send Com_2 Rfid", LV_EVENT);
			memset(output, 0, sizeof(output));
			m_cRfidComm2.send_data_feedback((BYTE*)Next_10, sizeof(Next_10), (BYTE*)output, sizeof(output));
			Sleep(100);
			m_cRfidComm2.send_data_feedback((BYTE*)CameraIn_1, sizeof(CameraIn_1), (BYTE*)output, sizeof(output));
			Sleep(100);
			m_cRfidComm2.send_data_feedback((BYTE*)Result_0, sizeof(Result_0), (BYTE*)output, sizeof(output));
			Sleep(100);
			m_cRfidComm2.send_data_feedback((BYTE*)NG_30, sizeof(NG_30), (BYTE*)output, sizeof(output));
			gSystemLog.DisplayLogAndSave(L"End Send Rfid", LV_EVENT);
			break;

		case 40:
			break;

		case 100://夹取位 上方
		{
			if (m_bMotorErrorFlag || !m_bHomeFlag || m_bEmergencyStopFlag)
			{
				gSystemLog.DisplayLogAndSave(L"安全错误", LV_EVENT);
				break;
			}
			if (!S10)
			{
				m_cIo.SetOutputIo(9, OFF);
				m_cIo.SetOutputIo(10, ON);
				Sleep(200);
			}
			CString cstr;
			cstr.Format(L"夹镜头上方 Move Start");
			gSystemLog.DisplayLogAndSave(cstr.GetBuffer(), LV_EVENT);
			int nTimeout = 0;
			short bMotionDoneTZ = 0x00;
			short bMotionDoneX = 0x00;
			short bMotionDoneY = 0x00;
			short bMotionDoneZ = 0x00;
			short bMotionDoneXt = 0x00;
			short bMotionDoneYt = 0x00;
			short bMotionDoneTX = 0x00;
			m_vCMotor[M_TABLE_Z].m_sAxisSetting.m_dTargetPos = m_nPositionTableZ[2];
			m_vCMotor[M_TABLE_Z].MotorMoveAbsEnc();
			Sleep(100);
			nTimeout = 400;
			while (1)
			{
				Sleep(50);
				if (bMotionDoneTZ == MOTION_DONE)
				{
					break;
				}
				if (nTimeout-- < 0)
				{
					cstr.Format(L"TableZ 移动至安全位超时");
					gSystemLog.DisplayLogAndSave(cstr.GetBuffer(), LV_ERROR);
					break;
				}
				bMotionDoneTZ = dmc_check_done(m_nCard, M_TABLE_Z);
			}
			if (nTimeout-- < 0)
			{
				break;
			}
			m_vCMotor[MOTOR_X].m_sAxisSetting.m_dTargetPos = m_nPositionX[0];
			m_vCMotor[MOTOR_Y].m_sAxisSetting.m_dTargetPos = m_nPositionY[0];
			m_vCMotor[MOTOR_Z].m_sAxisSetting.m_dTargetPos = m_nPositionZ[0];
			m_vCMotor[MOTOR_Xt].m_sAxisSetting.m_dTargetPos = m_nPositionXt[0];
			m_vCMotor[MOTOR_Yt].m_sAxisSetting.m_dTargetPos = m_nPositionYt[0];
			m_vCMotor[M_TABLE_X].m_sAxisSetting.m_dTargetPos = m_nPositionTableX[0];
			m_vCMotor[MOTOR_X].MotorMoveAbsEnc();
			m_vCMotor[MOTOR_Y].MotorMoveAbsEnc();
			m_vCMotor[MOTOR_Z].MotorMoveAbsEnc();
			m_vCMotor[MOTOR_Xt].MotorMoveAbsEnc();
			m_vCMotor[MOTOR_Yt].MotorMoveAbsEnc();
			m_vCMotor[M_TABLE_X].MotorMoveAbsEnc();
			nTimeout = 1000;
			while (1)
			{
				Sleep(50);
				if ((bMotionDoneX == MOTION_DONE) && (bMotionDoneY == MOTION_DONE) && (bMotionDoneZ == MOTION_DONE) && (bMotionDoneXt == MOTION_DONE) && (bMotionDoneYt == MOTION_DONE) && (bMotionDoneTX == MOTION_DONE))
				{
					break;
				}
				if (nTimeout-- < 0)
				{
					cstr.Format(L"五轴 + TX 移动至夹取位超时");
					gSystemLog.DisplayLogAndSave(cstr.GetBuffer(), LV_ERROR);
					break;
				}
				bMotionDoneX = dmc_check_done(m_nCard, MOTOR_X);
				bMotionDoneY = dmc_check_done(m_nCard, MOTOR_Y);
				bMotionDoneZ = dmc_check_done(m_nCard, MOTOR_Z);
				bMotionDoneXt = dmc_check_done(m_nCard, MOTOR_Xt);
				bMotionDoneYt = dmc_check_done(m_nCard, MOTOR_Yt);
				bMotionDoneTX = dmc_check_done(m_nCard, M_TABLE_X);
			}
			cstr.Format(L"Move Done");
			gSystemLog.DisplayLogAndSave(cstr.GetBuffer(), LV_EVENT);

		}
			break;
		case 101://夹取位
			result = PickLens();
			break;
		case 102://AA位 上方
		{
			if (m_bMotorErrorFlag || !m_bHomeFlag || m_bEmergencyStopFlag)
			{
				gSystemLog.DisplayLogAndSave(L"安全错误", LV_EVENT);
				break;
			}
			CString cstr;
			cstr.Format(L"AA位置上方 Move Start");
			gSystemLog.DisplayLogAndSave(cstr.GetBuffer(), LV_EVENT);

			int nTimeout = 0;
			short bMotionDoneTZ = 0x00;
			short bMotionDoneX = 0x00;
			short bMotionDoneY = 0x00;
			short bMotionDoneZ = 0x00;
			short bMotionDoneXt = 0x00;
			short bMotionDoneYt = 0x00;
			short bMotionDoneTX = 0x00;

			m_vCMotor[M_TABLE_Z].m_sAxisSetting.m_dTargetPos = m_nPositionTableZ[2];
			m_vCMotor[M_TABLE_Z].MotorMoveAbsEnc();
			Sleep(100);
			nTimeout = 400;
			while (1)
			{
				Sleep(50);
				if (bMotionDoneTZ == MOTION_DONE)
				{
					break;
				}
				if (nTimeout-- < 0)
				{
					cstr.Format(L"TableZ 移动至安全位超时");
					gSystemLog.DisplayLogAndSave(cstr.GetBuffer(), LV_ERROR);
					break;
				}
				bMotionDoneTZ = dmc_check_done(m_nCard, M_TABLE_Z);
			}
			if (nTimeout-- < 0)
			{
				break;
			}
			m_vCMotor[MOTOR_X].m_sAxisSetting.m_dTargetPos = m_nPositionX[1];
			m_vCMotor[MOTOR_Y].m_sAxisSetting.m_dTargetPos = m_nPositionY[1];
			m_vCMotor[MOTOR_Z].m_sAxisSetting.m_dTargetPos = m_nPositionZ[1];
			m_vCMotor[MOTOR_Xt].m_sAxisSetting.m_dTargetPos = m_nPositionXt[1];
			m_vCMotor[MOTOR_Yt].m_sAxisSetting.m_dTargetPos = m_nPositionYt[1];
			m_vCMotor[M_TABLE_X].m_sAxisSetting.m_dTargetPos = m_nPositionTableX[1];
			m_vCMotor[MOTOR_X].MotorMoveAbsEnc();
			m_vCMotor[MOTOR_Y].MotorMoveAbsEnc();
			m_vCMotor[MOTOR_Z].MotorMoveAbsEnc();
			m_vCMotor[MOTOR_Xt].MotorMoveAbsEnc();
			m_vCMotor[MOTOR_Yt].MotorMoveAbsEnc();
			m_vCMotor[M_TABLE_X].MotorMoveAbsEnc();
			nTimeout = 1000;
			while (1)
			{
				Sleep(50);
				if ((bMotionDoneX == MOTION_DONE) && (bMotionDoneY == MOTION_DONE) && (bMotionDoneZ == MOTION_DONE) && (bMotionDoneXt == MOTION_DONE) && (bMotionDoneYt == MOTION_DONE) && (bMotionDoneTX == MOTION_DONE))
				{
					break;
				}
				if (nTimeout-- < 0)
				{
					cstr.Format(L"五轴 + TX 移动至AA位超时");
					gSystemLog.DisplayLogAndSave(cstr.GetBuffer(), LV_ERROR);
					break;
				}
				bMotionDoneX = dmc_check_done(m_nCard, MOTOR_X);
				bMotionDoneY = dmc_check_done(m_nCard, MOTOR_Y);
				bMotionDoneZ = dmc_check_done(m_nCard, MOTOR_Z);
				bMotionDoneXt = dmc_check_done(m_nCard, MOTOR_Xt);
				bMotionDoneYt = dmc_check_done(m_nCard, MOTOR_Yt);
				bMotionDoneTX = dmc_check_done(m_nCard, M_TABLE_X);
			}
			cstr.Format(L"Move Done");
			gSystemLog.DisplayLogAndSave(cstr.GetBuffer(), LV_EVENT);
		}
			break;
		case 103://AA位
			result = LoadLens();
			break;

		case 110://AA位
			result = MoveChart();
			break;
		default:
			break;
		}
		m_nButtonDone = 1;
		m_nButtonValue = 0;
	}
	gSystemLog.DisplayLogAndSave(L"Exit thread 6", LV_EVENT);
	return 0;
}

int CSystemManager::SaveTestResult()
{
	//保存所有的东西
	//CreateImageFolder();

	gSystemLog.DisplayLogAndSave(L"开始保存产品数据", LV_ERROR);
	//创建一个产品的文件夹

	TCHAR  moduleFileName[MAX_PATH];
	::GetModuleFileName(NULL, moduleFileName, MAX_PATH);
	(_tcsrchr(moduleFileName, _T('\\')))[1] = 0;
	CString cstrPathData = moduleFileName;
	cstrPathData.Append(L"\\CenterData");

	wstring wstrImgFolder = cstrPathData.GetBuffer();
	if (!_utils::CheckDirExist(wstrImgFolder))
	{
		_wmkdir(wstrImgFolder.c_str());
	}
	wstrImgFolder += L"\\";

	gSystemLog.DisplayLogAndSave(L"开始保存产品数据", LV_ERROR);
	//创建一个产品的文件夹
	SYSTEMTIME dt;
	::GetLocalTime(&dt);
	CString strNewDate;
	strNewDate.Format(_T("%d-%02d-%02d.csv"), dt.wYear, dt.wMonth, dt.wDay);
	wstrImgFolder.append(strNewDate);
	CString cstrPath = wstrImgFolder.c_str();

	//读取区域设定
	char* old_locale = _strdup(setlocale(LC_CTYPE, NULL));
	//设定“简体中文”区域
	setlocale(LC_CTYPE, "chs");
	//创建文件并以文本方式打开
	//写入简体中文数据
	//恢复区域设定


	CStdioFile file;
	if (!_utils::CheckDirExist(cstrPath.GetBuffer()))
	{
		file.Open(cstrPath, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite | CFile::shareDenyWrite);
		file.SeekToBegin();
		CString strIndexTitle;
		CString str;// = L"Result,";
		//strIndexTitle = L"二维码,Site0Result,dSite0I,Site1Result,Site1Height,Site1Angle,dSite2Score,Site3Result,dSite3Height,dSite3Angle,Site6Result,dSite6Score";
		strIndexTitle = L"时间,条码,夹具号,总结果,电流测试,工位一相机中心(X/Y),角度,黑场测试,黑场测高高度,MTF-0,MTF-1,MTF-2,MTF-3,MTF-4,";
		str.Append(strIndexTitle);
		str.Append(L"\n");
		file.WriteString(str);
		file.SeekToEnd();

		CString strData;// = L"Data,";
		//strData.Append(product_Info.m_cstrCode);
		//strData.Append(L",");

		CString strIndexValue;
		strIndexValue.Format(L"%02d.%02d.%02d,", dt.wHour, dt.wMinute, dt.wSecond);
		strData.Append(strIndexValue);
		strData.Append(L"\n");
		file.WriteString(strData);
		file.Close();
	}
	else
	{
		BOOL bOpen = file.Open(cstrPath, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite | CFile::shareDenyWrite);
		if (!bOpen)
		{
			gSystemLog.DisplayLogAndSave(L"Result.csv文件被打开", LV_ERROR);
		}
		else
		{
			file.SeekToEnd();

			CString strData;
			CString strIndexValue;
			strIndexValue.Format(L"%02d.%02d.%02d,", dt.wHour, dt.wMinute, dt.wSecond);
			strData.Append(strIndexValue);
			strData.Append(L"\n");
			file.WriteString(strData);
			file.Close();
		}
	}

	setlocale(LC_CTYPE, old_locale);
	free(old_locale);

	return 0;
}

void CSystemManager::Uppercase(char *str)
{
	int n = strlen(str);
	for (int i = 0; i < n; i++)
	{
		str[i] = (char)toupper((int)str[i]);
	}
}
BOOL CSystemManager::SearchDirectory(const char *path, const char *name)
{
	WIN32_FIND_DATAA wfd;

	char search_path[MAX_PATH] = { 0 };
	sprintf(search_path, "%s\\*.*", path);
	HANDLE search = FindFirstFileA(search_path, &wfd);

	char search_name[MAX_PATH] = { 0 };
	strcpy(search_name, name);

	BOOL finding = TRUE;
	while (finding)
	{
		if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			Uppercase(wfd.cFileName);
			Uppercase(search_name);
			if (!strcmp(wfd.cFileName, search_name))
			{
				FindClose(search);
				return TRUE;
			}
		}
		finding = FindNextFileA(search, &wfd);
	}

	FindClose(search);
	return FALSE;
}
void CSystemManager::GetCurrentDirectory2(char *path)
{
	if (path == NULL) return;
	GetModuleFileNameA(NULL, path, MAX_PATH);
	char *p = strrchr(path, '\\');
	*p = '\0';
}
int CSystemManager::CreateReportFile(const char *test_item_str, char *target_report_folder_path, char *target_folder_name)
{
	SYSTEMTIME st;
	GetLocalTime(&st);
	char dir[MAX_PATH] = { 0 };
	GetCurrentDirectory2(dir);

	char new_path[MAX_PATH] = { 0 };
	char new_folder[MAX_PATH] = { 0 };
	char new_folder_path[MAX_PATH] = { 0 };

	sprintf(new_folder_path, "%s\\report", dir);

	if (!SearchDirectory(new_path, new_folder))
	{
		_mkdir(new_folder_path);
	}

	USES_CONVERSION;
	char* c_strPath = T2A(m_sGeneralSetting.m_cstrProjectName.GetBuffer());
	sprintf(new_path, "%s", new_folder_path);
	sprintf(new_folder_path, "%s\\%s", new_path, c_strPath);
	if (!SearchDirectory(new_path, new_folder))
	{
		_mkdir(new_folder_path);
	}

	sprintf(new_folder, test_item_str);
	sprintf(new_path, "%s", new_folder_path);
	sprintf(new_folder_path, "%s\\%s", new_path, new_folder);

	if (!SearchDirectory(new_path, new_folder))
	{
		_mkdir(new_folder_path);
	}


	sprintf(new_folder, "%04d%02d%02d", st.wYear, st.wMonth, st.wDay);
	sprintf(new_path, "%s", new_folder_path);
	sprintf(new_folder_path, "%s\\%s", new_path, new_folder);

	if (!SearchDirectory(new_path, new_folder))
	{
		_mkdir(new_folder_path);
	}

	char report_path[MAX_PATH] = { 0 };
	char report_name[MAX_PATH] = { 0 };
	sprintf(report_name, "%s_report_%s.csv", test_item_str, new_folder);
	sprintf(report_path, "%s\\%s", new_folder_path, report_name);

	strcpy(target_report_folder_path, new_folder_path);
	strcpy(target_folder_name, new_folder);
	if (!m_dirPath.SearchFile(new_folder_path, report_name))
	{
		return 0;
	}
	else
	{
		return 1;
	}
}
int CSystemManager::CreateMesFile(const char *test_item_str, char *target_report_folder_path, char *target_folder_name)
{
	SYSTEMTIME st;
	GetLocalTime(&st);

	char new_path[MAX_PATH] = { 0 };
	char new_folder[MAX_PATH] = { 0 };
	char new_folder_path[MAX_PATH] = { 0 };

	sprintf(new_folder_path, "D:\\data");

	if (!SearchDirectory(new_path, new_folder))
	{
		_mkdir(new_folder_path);
	}

	USES_CONVERSION;

	sprintf(new_folder, "%04d%02d%02d", st.wYear, st.wMonth, st.wDay);

	char report_path[MAX_PATH] = { 0 };
	char report_name[MAX_PATH] = { 0 };
	sprintf(report_name, "AA-%s.csv", new_folder);
	sprintf(report_path, "%s\\%s", new_folder_path, report_name);

	strcpy(target_report_folder_path, new_folder_path);
	strcpy(target_folder_name, new_folder);
	if (!m_dirPath.SearchFile(new_folder_path, report_name))
	{
		return 0;
	}
	else
	{
		return 1;
	}
}
HANDLE CSystemManager::CreateDefinePathCsv(const char *path)
{
	char new_path[MAX_PATH] = { 0 };
	if (strcmp((path + strlen(path) - 4), ".csv"))
	{
		sprintf(new_path, "%s.csv", path);
	}
	else
	{
		strcpy(new_path, path);
	}
	HANDLE hfile = CreateFileA(new_path, GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	return hfile;
}
BOOL CSystemManager::WriteCsv(HANDLE hfile, const char *format, ...)
{
	DWORD dw = 0;
	char buffer[10000] = { 0 };
	va_list args;
	va_start(args, format);
	vsprintf(buffer, format, args);
	BOOL is_write_successed = WriteFile(hfile, buffer, strlen(buffer), &dw, NULL);
	va_end(args);

	return is_write_successed;
}

void CSystemManager::SaveTestReport2(BYTE *bmp, int img_w, int img_h, int type)
{
	SYSTEMTIME st;
	GetLocalTime(&st);
	char date_string[MAX_PATH] = { 0 };
	sprintf(date_string, "%04d%02d%02d%02d%02d%02d", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);
	char report_folder_path[MAX_PATH] = { 0 };
	char report_folder_name[MAX_PATH] = { 0 };
	char report_path[MAX_PATH] = { 0 };
	int is_report_exist;

	switch (type)
	{
	case 0:
		is_report_exist = CreateReportFile("手动保存", report_folder_path, report_folder_name);
		sprintf(report_path, "%s\\手动保存_report_%s.csv", report_folder_path, report_folder_name);
		break;
	case 1:
		is_report_exist = CreateReportFile("AA", report_folder_path, report_folder_name);
		sprintf(report_path, "%s\\AA_report_%s.csv", report_folder_path, report_folder_name);
		break;
	case 2:
		is_report_exist = CreateReportFile("AfterUV", report_folder_path, report_folder_name);
		sprintf(report_path, "%s\\AfterUV_report_%s.csv", report_folder_path, report_folder_name);
		break;
	case 3:
		is_report_exist = CreateReportFile("AA", report_folder_path, report_folder_name);
		sprintf(report_path, "%s\\AA_report_%s.csv", report_folder_path, report_folder_name);
		break;
	case 4:
		is_report_exist = CreateReportFile("手动AA", report_folder_path, report_folder_name);
		sprintf(report_path, "%s\\AA_report_%s.csv", report_folder_path, report_folder_name);
		break;
	}

	HANDLE report_handle = CreateDefinePathCsv(report_path);
	char str[500] = { 0 };

	if (is_report_exist == FALSE)
	{
		SetFilePointer(report_handle, 0, NULL, FILE_BEGIN);
		sprintf(str, "MTF规格1, 规格2, MTF(UV后)规格1, 规格2, ,");
		WriteCsv(report_handle, str);
		sprintf(str, "TargetX, TargetY,OC Limit, ,Tilt Limit\r\n");
		WriteCsv(report_handle, str);
		sprintf(str, "%d, %d, %d, %d, ,", m_dSpecSfr[0], m_dSpecSfr[1], m_dSpecSfrUV[0], m_dSpecSfrUV[1]);
		WriteCsv(report_handle, str);
		sprintf(str, "%d, %d, %d, , %.2f\r\n", m_nTargetX, m_nTargetY, m_nSpecCenter, m_dSpecAAAngle);
		WriteCsv(report_handle, str);
		sprintf(str, "#sn, 日期, 总结果, FindTarget, MTF, 中心, 镜头角度, ");
		WriteCsv(report_handle, str);
		sprintf(str, "CenterX, CenterY, Tilt_X, Tilt_Y, 托盘号,");
		WriteCsv(report_handle, str);
		sprintf(str, "Sfr_C_b, Sfr_C_r, Sfr_C_t, Sfr_C_l, Sfr_C_avg,");
		WriteCsv(report_handle, str);
		sprintf(str, "Sfr_LT_b, Sfr_LT_r, Sfr_LT_t, Sfr_LT_l, Sfr_LT_avg,");
		WriteCsv(report_handle, str);
		sprintf(str, "Sfr_RT_b, Sfr_RT_r, Sfr_RT_t, Sfr_RT_l, Sfr_RT_avg,");
		WriteCsv(report_handle, str);
		sprintf(str, "Sfr_LB_b, Sfr_LB_r, Sfr_LB_t, Sfr_LB_l, Sfr_LB_avg,");
		WriteCsv(report_handle, str);
		sprintf(str, "Sfr_RB_b, Sfr_RB_r, Sfr_RB_t, Sfr_RB_l, Sfr_RB_avg,");
		WriteCsv(report_handle, str);
		sprintf(str, "电流值,");
		WriteCsv(report_handle, str);
		sprintf(str, "\r\n");
		WriteCsv(report_handle, str);
	}
	else SetFilePointer(report_handle, 0, NULL, FILE_END);

	SetFilePointer(report_handle, 0, NULL, FILE_END);

	if (type == 3) {
		sprintf(str, "%4d/%02d/%02d/%02d:%02d:%02d,%s,%d,未出图", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, SN, m_cRfidAA.m_nId);
		WriteCsv(report_handle, str);
		sprintf(str, " \r\n");
		WriteCsv(report_handle, str);


		CloseHandle(report_handle);
		return;
	}

	if (TestResult) {
		sprintf(str, "%s, %04d/%02d/%02d-%02d:%02d:%02d, Pass, 1, 1, 1, 1,", SN, st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);
		WriteCsv(report_handle, str);
	}
	else {
		sprintf(str, "%s, %04d/%02d/%02d-%02d:%02d:%02d, Fail, %d, %d, %d, %d,", SN, st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, TestResult, TestResult, CenterTestResult, TiltTestResult);
		WriteCsv(report_handle, str);
	}
	sprintf(str, "%.2f, %.2f, %.2f, %.2f, %d,", OCx[0], OCy[0], TiltX, TiltY, m_cRfidAA.m_nId);
	WriteCsv(report_handle, str);

	double val;
	int n;
	for (int i = 0; i < 5; i++) {
		val = 0;
		n = 0;
		for (int j = 0; j < 4; j++) {
			switch (j) {
			case 0:
				if (m_nRoiEnable[i][0]) {
					sprintf(str, "%.2f, ", SfrValue[i][j]);
				}
				else
					sprintf(str, "N/A, ");
				WriteCsv(report_handle, str);
				break;
			case 1:
				if (m_nRoiEnable[i][1]) {
					sprintf(str, "%.2f, ", SfrValue[i][j]);
				}
				else
					sprintf(str, "N/A, ");
				WriteCsv(report_handle, str);
				break;
			case 2:
				if (m_nRoiEnable[i][2]) {
					sprintf(str, "%.2f, ", SfrValue[i][j]);
				}
				else
					sprintf(str, "N/A, ");
				WriteCsv(report_handle, str);
				break;
			case 3:
				if (m_nRoiEnable[i][3]) {
					sprintf(str, "%.2f, ", SfrValue[i][j]);
				}
				else
					sprintf(str, "N/A, ");
				WriteCsv(report_handle, str);
				break;
			}
		}
		sprintf(str, " %.2f, ", SfrAvgValue[i]);
		WriteCsv(report_handle, str);
	}
	sprintf(str, " %.3f, ", m_fPowerCurrentVal[0]);
	WriteCsv(report_handle, str);

	sprintf(str, " \r\n");
	WriteCsv(report_handle, str);

	CloseHandle(report_handle);

	char file_name[MAX_PATH] = { 0 };
	switch (type)
	{
	case 0:
		sprintf(file_name, "%s\\[%s]sfr-org%02d%02d%02d", report_folder_path, SN, st.wHour, st.wMinute, st.wSecond);
		changeImg.save_bmp24_image(file_name, bmp, img_w, img_h);
		sprintf(file_name, "%s\\[%s]sfr-result%02d%02d%02d.jpg", report_folder_path, SN, st.wHour, st.wMinute, st.wSecond);
		save_drawing_image_jpg(GetDlgItem(m_ptrMainUI->GetSafeHwnd(), IDC_DISPLAY), file_name);
		break;
	case 1:
		if (!AAImgFlag) {
			sprintf(file_name, "%s\\[%s]sfr-org%02d%02d%02d", report_folder_path, SN, st.wHour, st.wMinute, st.wSecond);
			changeImg.save_bmp24_image(file_name, bmp, img_w, img_h);
			sprintf(file_name, "%s\\[%s]sfr-result%02d%02d%02d.jpg", report_folder_path, SN, st.wHour, st.wMinute, st.wSecond);
			save_drawing_image_jpg(GetDlgItem(m_ptrMainUI->GetSafeHwnd(), IDC_DISPLAY), file_name);
		}
		break;
	case 2:
		if (!UVImgFlag) {
			sprintf(file_name, "%s\\[%s]sfr-org%02d%02d%02d", report_folder_path, SN, st.wHour, st.wMinute, st.wSecond);
			changeImg.save_bmp24_image(file_name, bmp, img_w, img_h);
			sprintf(file_name, "%s\\[%s]sfr-result%02d%02d%02d.jpg", report_folder_path, SN, st.wHour, st.wMinute, st.wSecond);
			save_drawing_image_jpg(GetDlgItem(m_ptrMainUI->GetSafeHwnd(), IDC_DISPLAY), file_name);
		}
		break;
	case 3:
		if (!AAImgFlag) {
			sprintf(file_name, "%s\\[%s]sfr-org%02d%02d%02d", report_folder_path, SN, st.wHour, st.wMinute, st.wSecond);
			changeImg.save_bmp24_image(file_name, bmp, img_w, img_h);
			sprintf(file_name, "%s\\[%s]sfr-result%02d%02d%02d.jpg", report_folder_path, SN, st.wHour, st.wMinute, st.wSecond);
			save_drawing_image_jpg(GetDlgItem(m_ptrMainUI->GetSafeHwnd(), IDC_DISPLAY), file_name);
		}
		break;
	default:
		sprintf(file_name, "%s\\[%s]sfr-org%02d%02d%02d", report_folder_path, SN, st.wHour, st.wMinute, st.wSecond);
		changeImg.save_bmp24_image(file_name, bmp, img_w, img_h);
		sprintf(file_name, "%s\\[%s]sfr-result%02d%02d%02d.jpg", report_folder_path, SN, st.wHour, st.wMinute, st.wSecond);
		save_drawing_image_jpg(GetDlgItem(m_ptrMainUI->GetSafeHwnd(), IDC_DISPLAY), file_name);
		break;
	}
	//sprintf(file_name, "%s\\[%s]sfr-org%02d%02d%02d", report_folder_path, SN, st.wHour, st.wMinute, st.wSecond);
	//changeImg.save_bmp24_image(file_name, bmp, img_w, img_h);

	////sprintf(file_name, "%s\\[%s]sfr-result.bmp", report_folder_path, date_string);
	////ShowImg.SaveLayers(file_name, img_w, img_h);
	////换成窗口截图
	////sprintf(file_name, "%s\\[%s]sfr-result", report_folder_path, SN);
	////save_drawing_image(GetDlgItem(m_ptrMainUI->GetSafeHwnd(), IDC_DISPLAY), file_name);
	//sprintf(file_name, "%s\\[%s]sfr-result%02d%02d%02d.jpg", report_folder_path, SN, st.wHour, st.wMinute, st.wSecond);
	//save_drawing_image_jpg(GetDlgItem(m_ptrMainUI->GetSafeHwnd(), IDC_DISPLAY), file_name);

}

void CSystemManager::SaveTestReport3(BYTE *bmp, int img_w, int img_h)
{
	SYSTEMTIME st;
	GetLocalTime(&st);
	char date_string[MAX_PATH] = { 0 };
	sprintf(date_string, "%04d%02d%02d%02d%02d%02d", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);
	char report_folder_path[MAX_PATH] = { 0 };
	char report_folder_name[MAX_PATH] = { 0 };
	char report_path[MAX_PATH] = { 0 };
	int is_report_exist;

	is_report_exist = CreateReportFile("AA", report_folder_path, report_folder_name);
	sprintf(report_path, "%s\\AA_report_%s.csv", report_folder_path, report_folder_name);

	HANDLE report_handle = CreateDefinePathCsv(report_path);
	char str[500] = { 0 };

	if (is_report_exist == FALSE)
	{
		SetFilePointer(report_handle, 0, NULL, FILE_BEGIN);
		sprintf(str, "#时间,条码,托盘号,总结果,中心-X, 中心-Y, ");
		WriteCsv(report_handle, str);
		sprintf(str, "[AA]Sfr-C,[AA]Sfr-LU,[AA]Sfr-RU,[AA]Sfr-LD,[AA]Sfr-RD,");
		WriteCsv(report_handle, str);
		sprintf(str, "[UV]Sfr-C,[UV]Sfr-LU,[UV]Sfr-RU,[UV]Sfr-LD,[UV]Sfr-RD,");
		WriteCsv(report_handle, str);
		sprintf(str, "电流值, 角度-X, 角度-Y, Z轴坐标, UV时间(s)");
		WriteCsv(report_handle, str);
		sprintf(str, "\r\n");
		WriteCsv(report_handle, str);
	}
	else SetFilePointer(report_handle, 0, NULL, FILE_END);

	SetFilePointer(report_handle, 0, NULL, FILE_END);

	sprintf(str, "%4d/%02d/%02d/%02d:%02d:%02d,%s,%d,%d,", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, SN, m_cRfidAA.m_nId, TestResult);
	WriteCsv(report_handle, str);
	sprintf(str, "%.2f,%.2f,", OCx[0], OCy[0]);
	WriteCsv(report_handle, str);
	for (int i = 0; i < 5; i++) {
		sprintf(str, "%.4f,", SfrAvgValue[i]);
		WriteCsv(report_handle, str);
	}

	sprintf(str, "%.3f,%.2f,%.2f,%d,%d", m_fPowerCurrentVal[0] - PowerDiff, TiltX, TiltY, m_vCMotor[MOTOR_Z].m_nCurPositon, m_nUVTime);
	WriteCsv(report_handle, str);

	sprintf(str, " \r\n");
	WriteCsv(report_handle, str);


	CloseHandle(report_handle);

	char file_name[MAX_PATH] = { 0 };
	sprintf(file_name, "%s\\[%s]sfr-org%02d%02d%02d", report_folder_path, SN, st.wHour, st.wMinute, st.wSecond);
	changeImg.save_bmp24_image(file_name, bmp, img_w, img_h);

	sprintf(file_name, "%s\\[%s]sfr-result%02d%02d%02d.jpg", report_folder_path, SN, st.wHour, st.wMinute, st.wSecond);
	save_drawing_image_jpg(GetDlgItem(m_ptrMainUI->GetSafeHwnd(), IDC_DISPLAY), file_name);

}

void CSystemManager::SaveMes(int glue,int capture,int result)
{
	SYSTEMTIME st;
	GetLocalTime(&st);
	char date_string[MAX_PATH] = { 0 };
	sprintf(date_string, "%04d%02d%02d%02d%02d%02d", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);
	char report_folder_path[MAX_PATH] = { 0 };
	char report_folder_name[MAX_PATH] = { 0 };
	char report_path[MAX_PATH] = { 0 };
	//int is_report_exist;

	//SN_YYYYMMDD.csv
	//is_report_exist = CreateMesFile("AfterUV", report_folder_path, report_folder_name);
	sprintf(report_path, "D:\\MES\\%s_%s.csv", SN, date_string);

	HANDLE report_handle = CreateDefinePathCsv(report_path);
	char str[500] = { 0 };

	if (1) {
		SetFilePointer(report_handle, 0, NULL, FILE_BEGIN);
		sprintf(str, "SN, 日期, 总结果, 胶水结果, 采图结果, FindTarget, MTFResult, 中心结果, 角度结果, ");
		WriteCsv(report_handle, str);
		sprintf(str, "CenterX, CenterY, Tilt_X, Tilt_Y, 托盘号,");
		WriteCsv(report_handle, str);
		sprintf(str, "Sfr_C_b, Sfr_C_r, Sfr_C_t, Sfr_C_l, Sfr_C_avg,");
		WriteCsv(report_handle, str);
		sprintf(str, "Sfr_LT_b, Sfr_LT_r, Sfr_LT_t, Sfr_LT_l, Sfr_LT_avg,");
		WriteCsv(report_handle, str);
		sprintf(str, "Sfr_RT_b, Sfr_RT_r, Sfr_RT_t, Sfr_RT_l, Sfr_RT_avg,");
		WriteCsv(report_handle, str);
		sprintf(str, "Sfr_LB_b, Sfr_LB_r, Sfr_LB_t, Sfr_LB_l, Sfr_LB_avg,");
		WriteCsv(report_handle, str);
		sprintf(str, "Sfr_RB_b, Sfr_RB_r, Sfr_RB_t, Sfr_RB_l, Sfr_RB_avg,");
		WriteCsv(report_handle, str);
		sprintf(str, "电流值");
		WriteCsv(report_handle, str);
		sprintf(str, "\r\n");
		WriteCsv(report_handle, str);
	}

	SetFilePointer(report_handle, 0, NULL, FILE_END);

	if (result == 1/* && glue == 1 && capture == 1*/) {
		sprintf(str, "%s, %04d/%02d/%02d-%02d:%02d:%02d, Pass, 1, 1, 1, 1, 1, 1,", SN, st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);
		WriteCsv(report_handle, str);
	}
	else {
		sprintf(str, "%s, %04d/%02d/%02d-%02d:%02d:%02d, Fail, %d, %d, %d, %d, %d, %d,", SN, st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, glue, capture, TestResult, TestResult, CenterTestResult, TiltTestResult);
		WriteCsv(report_handle, str);
	}
	sprintf(str, "%.2f, %.2f, %.2f, %.2f, %d,", OCx[0], OCy[0], TiltX, TiltY, m_cRfidAA.m_nId);
	WriteCsv(report_handle, str);

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 4; j++) {
			switch (j) {
			case 0:
				if (m_nRoiEnable[i][0]) {
					sprintf(str, "%.2f, ", SfrValue[i][j]);
				}
				else
					sprintf(str, "N/A, ");
				WriteCsv(report_handle, str);
				break;
			case 1:
				if (m_nRoiEnable[i][1]) {
					sprintf(str, "%.2f, ", SfrValue[i][j]);
				}
				else
					sprintf(str, "N/A, ");
				WriteCsv(report_handle, str);
				break;
			case 2:
				if (m_nRoiEnable[i][2]) {
					sprintf(str, "%.2f, ", SfrValue[i][j]);
				}
				else
					sprintf(str, "N/A, ");
				WriteCsv(report_handle, str);
				break;
			case 3:
				if (m_nRoiEnable[i][3]) {
					sprintf(str, "%.2f, ", SfrValue[i][j]);
				}
				else
					sprintf(str, "N/A, ");
				WriteCsv(report_handle, str);
				break;
			}
		}
		sprintf(str, " %.2f, ", SfrAvgValue[i]);
		WriteCsv(report_handle, str);
	}
	sprintf(str, " %.3f", m_fPowerCurrentVal[0]);
	WriteCsv(report_handle, str);

	CloseHandle(report_handle);
}

BOOL CSystemManager::save_drawing_image(HWND hdlg, char *img_path)
{
	RECT rect;
	GetClientRect(hdlg, &rect);
	int cx = rect.right;
	int cy = rect.bottom;

	HDC hdc = GetDC(hdlg);

	BITMAP bm_histogram;
	HBITMAP hbitmap = CreateCompatibleBitmap(hdc, cx, cy);
	HDC mdc = CreateCompatibleDC(hdc);
	HBITMAP old_bitmap = (HBITMAP)SelectObject(mdc, hbitmap);

	GetObject(hbitmap, sizeof(BITMAP), &bm_histogram);

	BitBlt(mdc, 0, 0, cx, cy, hdc, 0, 0, SRCCOPY);

	BITMAPINFOHEADER ih;
	ih.biSize = sizeof(BITMAPINFOHEADER);
	ih.biWidth = bm_histogram.bmWidth = cx;
	ih.biHeight = bm_histogram.bmHeight = cy;
	ih.biPlanes = 1;
	ih.biBitCount = bm_histogram.bmPlanes*bm_histogram.bmBitsPixel;

	if (ih.biBitCount > 8) ih.biBitCount = 24;

	ih.biCompression = BI_RGB;
	ih.biSizeImage = 0;
	ih.biXPelsPerMeter = 0;
	ih.biYPelsPerMeter = 0;
	ih.biClrUsed = 0;
	ih.biClrImportant = 0;

	int palette_size = (ih.biBitCount == 24 ? 0 : 1 << ih.biBitCount) * sizeof(RGBQUAD);

	BITMAPINFO *bitmap_info = (BITMAPINFO *)malloc(ih.biSize + palette_size);
	bitmap_info->bmiHeader = ih;

	GetDIBits(mdc, hbitmap, 0, bm_histogram.bmHeight, NULL, bitmap_info, DIB_RGB_COLORS);
	ih = bitmap_info->bmiHeader;

	if (ih.biSizeImage == 0)
	{
		ih.biSizeImage = ((((ih.biWidth*ih.biBitCount) + 31) & ~31) >> 3) * ih.biHeight;
	}

	DWORD new_size = ih.biSize + palette_size + ih.biSizeImage;
	bitmap_info = (BITMAPINFO *)realloc(bitmap_info, new_size);

	GetDIBits(mdc, hbitmap, 0, bm_histogram.bmHeight, (PBYTE)bitmap_info + ih.biSize + palette_size, bitmap_info, DIB_RGB_COLORS);

	BITMAPFILEHEADER fh;
	fh.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + palette_size;
	fh.bfReserved1 = 0;
	fh.bfReserved2 = 0;
	fh.bfSize = new_size + sizeof(BITMAPFILEHEADER);
	fh.bfType = 0x4d42;

	char path[MAX_PATH] = { 0 };
	strcpy(path, img_path);
	strcat(path, ".bmp");
	DWORD writen;
	HANDLE file = CreateFileA(path, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	WriteFile(file, &fh, sizeof(fh), &writen, NULL);
	WriteFile(file, bitmap_info, new_size, &writen, NULL);

	CloseHandle(file);

	SelectObject(mdc, old_bitmap);
	DeleteObject(mdc);

	ReleaseDC(hdlg, hdc);
	free(bitmap_info);

	return TRUE;
}

//#include<atlimage.h>
BOOL CSystemManager::save_drawing_image_jpg(HWND hdlg, char *img_path)
{
	RECT rect;
	GetClientRect(hdlg, &rect);
	int cx = rect.right;
	int cy = rect.bottom;

	HDC hdc = GetDC(hdlg);

	BITMAP bm_histogram;
	HBITMAP hbitmap = CreateCompatibleBitmap(hdc, cx, cy);

	HDC mdc = CreateCompatibleDC(hdc);
	HBITMAP old_bitmap = (HBITMAP)SelectObject(mdc, hbitmap);

	GetObject(hbitmap, sizeof(BITMAP), &bm_histogram);

	BitBlt(mdc, 0, 0, cx, cy, hdc, 0, 0, SRCCOPY);

	CImage image;
	image.Attach(hbitmap);

	//LPCTSTR str;
	CString cstr;
	USES_CONVERSION;
	cstr.Format(L"%s", A2T(img_path));
	image.Save(cstr);

	SelectObject(mdc, old_bitmap);
	DeleteObject(mdc);

	ReleaseDC(hdlg, hdc);

	return TRUE;
}

int CSystemManager::Char2Num(unsigned char* c, int* num, int size)
{
	int count;
	int no = 0;
	int high, low;
	count = size;
	for (int i = 0; i < count; i++)
	{
		if (c[i] == '0'&&c[i + 1] == 'x')
		{
			if (c[i + 3] == ' ')
			{
				low = c[i + 2] - '0';
				if (low > 10)num[no] = low - 39;
				else num[no] = low;
				no++;
			}
			else
			{
				high = c[i + 2] - '0';
				if (high > 10)high = high - 39;

				low = c[i + 3] - '0';
				if (low > 10)low = low - 39;

				num[no] = high * 16 + low;
				no++;
			}
		}
	}
	return true;
}
int CSystemManager::Char2Char(unsigned char* c, char* num, int size)
{
	int count;
	int no = 0;
	int high, low;
	count = size;
	for (int i = 0; i < count; i++)
	{
		if (c[i] == '0'&&c[i + 1] == 'x')
		{
			if (c[i + 3] == ' ')
			{
				low = c[i + 2] - '0';
				if (low > 10)num[no] = low - 39;
				else num[no] = low;
				no++;
			}
			else
			{
				high = c[i + 2] - '0';
				if (high > 10)high = high - 39;

				low = c[i + 3] - '0';
				if (low > 10)low = low - 39;

				num[no] = high * 16 + low;
				no++;
			}
		}
	}
	return true;
}
