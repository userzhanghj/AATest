#pragma once
#include "TypeDef.h"
#include "LTDMC.h"
#include "SystemLog.h"
#pragma comment(lib, "LTDMC.lib")

class CMotor
{
public:
	CMotor();
	~CMotor();
	bool CardInit();
public:
	//MOTION_IO m_sMotionIO;
	HANDLE hThread_Abs;
	HANDLE hThread_Step;

	int		m_speedmode;
	int		m_homemode;
	long m_nCurPositon=0;
	bool m_bServoOn = false;
	bool m_bHomed = false;
	
	bool m_bNEL = false;
	bool m_bPEL = false;
	bool m_bORG = false;
	bool m_bALM = false;
	bool m_bRDY = false;
	bool m_bINP = false;
	bool m_bEMG = false;
	bool m_bPSL = false;
	bool m_bNSL = false;

	SPEED_PAR m_sMoveStep;
	SPEED_PAR m_sMoveHome;
	double dHomeOffset;
	double dStepDistance;

	double PositionRatio = 1;
	double SpeedRatio;
	long position[10];
	long setpos[3];//点胶求圆
	HANDLE mutex;

	AXIS_SETTING m_sAxisSetting;
	int m_nMotorDirection = 0;//0是逆时针，1是顺时针。0是往上，1是往下。0是正向，1是负向

private:

	//输出输入都4张


public:
	void ServoOn();
	void ServoOff();
	void ResetAlarm();

   void HomeSearch2(int nDirection);
   void StopMove();
   void HomeSearch(int nDirection);
   void MotorMoveContinue(int nDirection);
   void MotorMoveAbsEnc();
   void MotorMoveStep();
   unsigned int __stdcall MotorStepMoveThread();
   unsigned int __stdcall MotorAbsEncMoveThread();
   void StopMotorMoveThread();
   unsigned int __stdcall StopMotorThread();
   void StartMotorContinueMoveThread();
private:
   void StartMotorHomeThread();
   unsigned int __stdcall MotorHomeThread();
   void StartMotorStepMoveThread();
   void StartMotorAbsEncMoveThread();
   unsigned int __stdcall MotorContinueMoveThread();

   void StartMotorHomeThread2();
   unsigned int __stdcall MotorHomeThread2();

   union UI_Proc
   {
	   unsigned(_stdcall * ThreadProc)(void*);
	   unsigned(_stdcall CMotor::*MemProc)();
   } ProcHome, ProcHome2, ProcMove,ProcMoveContinue, ProcStop;
};

