#pragma once

#include <afxstr.h>
#include <string>
#include <map>
#include <unordered_map>
#include <io.h>
#include <set>
#include <vector>
#include <iostream>
#include <iomanip>
#include <tchar.h>
#include <atlcomcli.h>
#include <atlconv.h>
#include <atltypes.h>

#include<Windows.h>
#include<string.h>
#include<stdio.h>
#include<iostream>
#include<windowsx.h>
#include<CommCtrl.h>
#include<direct.h>
#include <assert.h>
#include<winsock.h>
#include<math.h>
#include<string.h>

#include "afxwin.h"
#include <boost\lexical_cast.hpp>
#include "_utils.h"
#include "pch.h"
#include"chart.h"
#include"s_sfr.h"
#include"SocketServer.h"
#include"SocketClient.h"
#include"cts.h"
#pragma comment(lib,"s_sfr.lib")
#define MAX_SFR_ROI_HEIGHT		5000
//#include "CSVparser.h"
using namespace std;
using namespace boost;

//三色灯
#define LIGHT_YELLOW				0
#define LIGHT_RED				1
#define LIGHT_GREEN				2
#define LIGHT_RED_TWINKEL				3

//AA
#define CHOOSE_XY				0
//#define SYMBOL1					0
//#define SYMBOL2					0
//拟合曲线用到
#define M 9			//max pivot count		
#define MULTI_FACTOR			4
#define N2 100		//max input data count
#define K 2*M

#define COLOR_ALICE_BLUE_00					RGB(240, 248, 255)
#define COLOR_ANTIQUE_WHITE_01				RGB(250, 235, 215)
#define COLORLIGHT_STEEL_BLUE_74			RGB(176, 196, 222)

#define COLOR_BLACK							RGB(0,     0,   0)
#define COLOR_WHITE							RGB(255, 255, 255)
#define COLOR_RED							RGB(255,   0,   0)
#define COLOR_GREEN							RGB(0,   255,   0)
#define COLOR_BLUE							RGB(0,     0, 255)
#define COLOR_DODGER_BLUE					RGB( 30, 144, 255)
#define COLOR_MEDIUM_STATE_BLUE				RGB(123, 104, 238)
#define COLOR_MAGENTA						RGB(255,   0, 255)
#define COLOR_YELLOW_GREEN					RGB(154, 205,  50)
#define COLOR_TOMATO						RGB(255,  99,  71)
#define COLOR_GHOST_WHITE					RGB(248, 248, 255)
#define COLOR_LIGHT_DARK					RGB(68,   68,  68)
#define COLOR_YELLOW						RGB(255, 255,   0)
#define COLOR_DARK_ORANGE					RGB(255, 140,   0)
#define COLOR_SADDLE_BROWN					RGB(139,  69,  19)

#define COLOR_LIME_GREEN					RGB( 50, 205,  50)
#define COLOR_DEEP_PINK						RGB(255,  20, 147)
#define COLOR_FIRE_BRICK					RGB(178,  34,  34)
#define COLOR_GOLD							RGB(255, 215,   0)
#define COLOR_PLUM							RGB(255, 215,   0)

const int UI_SCREEN_X = 1024;
const int UI_SCREEN_Y = 768;

#define WM_SEND_LOG_MSG_TO_MAIN_UI				WM_USER + 2
#define WM_SEND_SOCKET_SERVER_MSG_TO_MAIN_UI             WM_USER + 6

#define ON										0x01
#define OFF										0x00
#define MOTION_DONE					1
//#define MOTOR_CARD_LINE1				1 //io

#define MOVE_DIRECTION_REVERSE		0
#define MOVE_DIRECTION_FORWARD		1


const int TIMER_ID_AXIS_STATUS = 90001;//轴 Timer
const int TIMER_ID_IO_CONTROL_STATUS = 90002;//IO Timer
const int TIMER_CONTROL_AXIS_POS = 90003;//轴 Timer
const int TIMER_CONTROL_COUNT = 90004;//

//SFR Test
#define TF_MAX_CNT			100
#define SLANTED_BW_NUM			5

typedef struct _tagSlantedBW_SM
{
	//double pixel_size;
	//int	   fs_index;
	int	   fs_peak_index[SLANTED_BW_NUM];
	//int    select_roi[SLANTED_BW_NUM];
	int	   find_target_num;
	double tilt_angle[2];
	double sfr_val[SLANTED_BW_NUM][TF_MAX_CNT];
	double oc_x[TF_MAX_CNT][SLANTED_BW_NUM];
	double oc_y[TF_MAX_CNT][SLANTED_BW_NUM];
	//double fs_z_pos[TF_MAX_CNT];
	double	   fs_peak_index_d[SLANTED_BW_NUM];

}SlantedBW_SM;

//MN200 的轴编号
enum eMotorID
{
	M_TABLE_Z = 0,
	M_CHART_Z,
	M_TABLE_X,
	MOTOR_X,
	MOTOR_Y,
	MOTOR_Z,
	MOTOR_Xt,
	MOTOR_Yt
};

enum eEVENT_LEVEL
{
	LV_INVALID = -1,
	LV_EVENT = 0,
	LV_WARNING,
	LV_ERROR
};

typedef struct tagPALETTE // 调色板
{
	BYTE b; // blue
	BYTE g; // green
	BYTE r; // red
	BYTE n; // not support
} PALETTE, *LPPALETTE;

struct RFID_MSG
{
	int m_nId;//托盘号
	int m_bCameraIn = 0;//产品有无
	int m_bCameraStatus = 0;//产品状态
	int m_nNextStation;//目标工位
	int m_nNGStation;//NG工位
	char m_cSN[30];
};

typedef struct _SPEED_PAR
{
	double		Start_Speed;			// Initial & Stop Speed (PPS)
	double		Drive_Speed;			// Operation Speed (PPS)
	//double		Correction_Speed;		// Correction Speed (PPS)
	double		Acc;					// Acceleration data (s/ PPS/S)
	double		Dec;					// Deceleration data (s/ PPS/S)
	double		AccTime;
	double		DecTime;
	//BYTE		AccDec_Mode;			// ADC_MODE_RATE / ADC_MODE_TIME
	//BYTE		SCurve_Enable;			// DISABLE / Enable
	//double	SCurveAcc_Sect;			// Acceleration S-curve range (PPS)
	//double	SCurveDec_Sect;			// Deceleration S-curve range (PPS)
	//double	Max_Speed;				// selecting MaxSpeed to set the speed magnification rate
}SPEED_PAR, *PSPEED_PAR;

struct AXIS_SETTING
{
	int			m_nAxisId;
	int			m_nDirection;
	wstring		m_wstrAxisName;
	double		m_dTargetPos;
	int			m_nSpeedHome;
	int			m_nSpeedMove;
	wstring		m_wstrProportion;
	double			m_nSpeedAcc;
	int			m_nStartSpeed;


	AXIS_SETTING() :m_nAxisId(0), m_wstrAxisName(L""), m_nDirection(0), m_dTargetPos(0.0f)
		, m_nSpeedHome(0), m_nSpeedMove(0),
		m_wstrProportion(L""), m_nSpeedAcc(0.0f), m_nStartSpeed(0)
	{

	}

	AXIS_SETTING(const AXIS_SETTING& other)
	{
		m_nAxisId = other.m_nAxisId;
		m_wstrAxisName = other.m_wstrAxisName;
		m_nDirection = other.m_nDirection;
		m_dTargetPos = other.m_dTargetPos;
		m_nSpeedHome = other.m_nSpeedHome;
		m_nSpeedMove = other.m_nSpeedMove;
		m_wstrProportion = other.m_wstrProportion;
		m_nSpeedAcc = other.m_nSpeedAcc;
		m_nStartSpeed = other.m_nStartSpeed;
	}

	AXIS_SETTING(AXIS_SETTING&& other)
	{
		m_nAxisId = other.m_nAxisId;
		m_wstrAxisName = other.m_wstrAxisName;
		m_nDirection = other.m_nDirection;
		m_dTargetPos = other.m_dTargetPos;
		m_nSpeedHome = other.m_nSpeedHome;
		m_nSpeedMove = other.m_nSpeedMove;
		m_wstrProportion = other.m_wstrProportion;
		m_nSpeedAcc = other.m_nSpeedAcc;
		m_nStartSpeed = other.m_nStartSpeed;
	}

	AXIS_SETTING& operator=(const AXIS_SETTING& other)
	{
		if (&other == this)
		{
			return *this;
		}
		m_nAxisId = other.m_nAxisId;
		m_wstrAxisName = other.m_wstrAxisName;
		m_nDirection = other.m_nDirection;
		m_dTargetPos = other.m_dTargetPos;
		m_nSpeedHome = other.m_nSpeedHome;
		m_nSpeedMove = other.m_nSpeedMove;
		m_wstrProportion = other.m_wstrProportion;
		m_nSpeedAcc = other.m_nSpeedAcc;
		m_nStartSpeed = other.m_nStartSpeed;
		return *this;
	}

	AXIS_SETTING& operator=(AXIS_SETTING&& other)
	{
		if (&other == this)
		{
			return *this;
		}
		m_nAxisId = other.m_nAxisId;
		m_wstrAxisName = other.m_wstrAxisName;
		m_nDirection = other.m_nDirection;
		m_dTargetPos = other.m_dTargetPos;
		m_nSpeedHome = other.m_nSpeedHome;
		m_nSpeedMove = other.m_nSpeedMove;
		m_wstrProportion = other.m_wstrProportion;
		m_nSpeedAcc = other.m_nSpeedAcc;
		m_nStartSpeed = other.m_nStartSpeed;
		return *this;
	}
};

struct CLIENT_SETTING
{
	int  m_nIndex;
	wstring m_wstrIp;
	int  m_nPort;


	CLIENT_SETTING() :m_nIndex(0), m_wstrIp(L""), m_nPort(0)
	{
	}

	CLIENT_SETTING(const CLIENT_SETTING& other)
	{
		m_nIndex = other.m_nIndex;
		m_wstrIp = other.m_wstrIp;
		m_nPort = other.m_nPort;
	}

	CLIENT_SETTING& operator=(const CLIENT_SETTING& other)
	{
		if (&other == this)
		{
			return *this;
		}
		m_nIndex = other.m_nIndex;
		m_wstrIp = other.m_wstrIp;
		m_nPort = other.m_nPort;
		return *this;
	}

	CLIENT_SETTING(CLIENT_SETTING&& other)
	{
		m_nIndex = other.m_nIndex;
		m_wstrIp = other.m_wstrIp;
		m_nPort = other.m_nPort;
	}

	CLIENT_SETTING& operator=(CLIENT_SETTING&& other)
	{
		if (&other == this)
		{
			return *this;
		}
		m_nIndex = other.m_nIndex;
		m_wstrIp = other.m_wstrIp;
		m_nPort = other.m_nPort;
		return *this;
	}
};

struct GENERAL_SETTING
{
	CString m_cstrProjectName;

	GENERAL_SETTING() :m_cstrProjectName(L"")
	{
	}

	GENERAL_SETTING(const GENERAL_SETTING& other)
	{
		m_cstrProjectName = other.m_cstrProjectName;
	}

	GENERAL_SETTING& operator=(const GENERAL_SETTING& other)
	{
		if (&other == this)
		{
			return *this;
		}
		m_cstrProjectName = other.m_cstrProjectName;

		return *this;
	}

	GENERAL_SETTING(GENERAL_SETTING&& other)
	{
		m_cstrProjectName = other.m_cstrProjectName;

	}

	GENERAL_SETTING& operator=(GENERAL_SETTING&& other)
	{
		if (&other == this)
		{
			return *this;
		}
		m_cstrProjectName = other.m_cstrProjectName;

		return *this;
	}
};

struct SITEDLG_TO_MOTORDLG
{
	CWnd*  m_ptrDlgHandle;
	int m_nEditId;
	int m_nMotorIndex;

	SITEDLG_TO_MOTORDLG() :m_ptrDlgHandle(nullptr), m_nEditId(0), m_nMotorIndex(0)
	{
	}

	SITEDLG_TO_MOTORDLG(const SITEDLG_TO_MOTORDLG& other)
	{
		m_ptrDlgHandle = other.m_ptrDlgHandle;
		m_nEditId = other.m_nEditId;
		m_nMotorIndex = other.m_nMotorIndex;
	}

	SITEDLG_TO_MOTORDLG& operator=(const SITEDLG_TO_MOTORDLG& other)
	{
		if (&other == this)
		{
			return *this;
		}
		m_ptrDlgHandle = other.m_ptrDlgHandle;
		m_nEditId = other.m_nEditId;
		m_nMotorIndex = other.m_nMotorIndex;
		return *this;
	}

	SITEDLG_TO_MOTORDLG(SITEDLG_TO_MOTORDLG&& other)
	{
		m_ptrDlgHandle = other.m_ptrDlgHandle;
		m_nEditId = other.m_nEditId;
		m_nMotorIndex = other.m_nMotorIndex;
	}

	SITEDLG_TO_MOTORDLG& operator=(SITEDLG_TO_MOTORDLG&& other)
	{
		if (&other == this)
		{
			return *this;
		}
		m_ptrDlgHandle = other.m_ptrDlgHandle;
		m_nEditId = other.m_nEditId;
		m_nMotorIndex = other.m_nMotorIndex;
		return *this;
	}
};

struct LOG_PACKAGE
{
	eEVENT_LEVEL  m_level;
	wstring       m_wstrTime;
	wstring       m_wstrMsg;

	LOG_PACKAGE()
		:
		m_level(LV_INVALID),
		m_wstrTime(L""),
		m_wstrMsg(L"")
	{

	}
	LOG_PACKAGE(const LOG_PACKAGE& other)
	{
		m_level = other.m_level;
		m_wstrTime = other.m_wstrTime;
		m_wstrMsg = other.m_wstrMsg;
	}
	LOG_PACKAGE(LOG_PACKAGE&& other)
	{
		m_level = other.m_level;
		m_wstrTime = other.m_wstrTime;
		m_wstrMsg = other.m_wstrMsg;
	}
	LOG_PACKAGE& operator=(const LOG_PACKAGE& other)
	{
		if (&other == this)
		{
			return *this;
		}
		m_level = other.m_level;
		m_wstrTime = other.m_wstrTime;
		m_wstrMsg = other.m_wstrMsg;
		return *this;
	}

	LOG_PACKAGE& operator=(LOG_PACKAGE&& other)
	{
		if (&other == this)
		{
			return *this;
		}
		m_level = other.m_level;
		m_wstrTime = other.m_wstrTime;
		m_wstrMsg = other.m_wstrMsg;
		return *this;
	}
};

struct IO_MODULE
{
	int m_nModule;
	int m_nPort;
	int m_nType;
	CString m_cstrDescription;

	IO_MODULE() :m_nModule(0), m_nPort(0), m_nType(0), m_cstrDescription(L"")
	{

	}

	IO_MODULE(const IO_MODULE& other)
	{
		m_nModule = other.m_nModule;
		m_nPort = other.m_nPort;
		m_nType = other.m_nType;
		m_cstrDescription = other.m_cstrDescription;
	}

	IO_MODULE& operator=(const IO_MODULE& other)
	{
		if (&other == this)
		{
			return *this;
		}
		m_nModule = other.m_nModule;
		m_nPort = other.m_nPort;
		m_nType = other.m_nType;
		m_cstrDescription = other.m_cstrDescription; return *this;
	}

	IO_MODULE(IO_MODULE&& other)
	{
		m_nModule = other.m_nModule;
		m_nPort = other.m_nPort;
		m_nType = other.m_nType;
		m_cstrDescription = other.m_cstrDescription;
	}

	IO_MODULE& operator=(IO_MODULE&& other)
	{
		if (&other == this)
		{
			return *this;
		}
		m_nModule = other.m_nModule;
		m_nPort = other.m_nPort;
		m_nType = other.m_nType;
		m_cstrDescription = other.m_cstrDescription;
		return *this;
	}
};

struct LOGIN_INFO
{
	CString m_cUserName;
	CString m_cPassword;

	LOGIN_INFO() :m_cUserName(L""), m_cPassword(L"")
	{

	}

	LOGIN_INFO(const LOGIN_INFO& other)
	{
		m_cUserName = other.m_cUserName;
		m_cPassword = other.m_cPassword;
	}

	LOGIN_INFO& operator=(const LOGIN_INFO& other)
	{
		if (&other == this)
		{
			return *this;
		}
		m_cUserName = other.m_cUserName;
		m_cPassword = other.m_cPassword;
		return *this;
	}

	LOGIN_INFO(LOGIN_INFO&& other)
	{
		m_cUserName = other.m_cUserName;
		m_cPassword = other.m_cPassword;
	}

	LOGIN_INFO& operator=(LOGIN_INFO&& other)
	{
		if (&other == this)
		{
			return *this;
		}
		m_cUserName = other.m_cUserName;
		m_cPassword = other.m_cPassword;
		return *this;
	}
};

//报错信息
#define ERROR_S02_OFF			1
#define ERROR_CAMERA_IN			2
#define ERROR_S04_OFF			3
#define ERROR_S03_OFF			4





#define ERROR_S16_ERROR           11
#define ERROR_LOAD_ERROR           12

#define ERROR_NO_MIRROR				13

#define ERROR_S17_ERROR           14
#define ERROR_S05_ERROR			15

#define ERROR_PICK_ERROR           17

#define ERROR_S11_ERROR			18
#define ERROR_S12_ERROR			19
#define ERROR_S14_ERROR			20
#define ERROR_S08_ERROR			21

#define ERROR_NGNUM_ERROR		26




#define ERROR_COM_1           43
#define ERROR_COM_2           44

#define ERROR_TCP_2           46

#define ERROR_EMERGENCY		48
#define ERROR_NOT_HOMED       49
#define ERROR_EMERGENCY_2		50
