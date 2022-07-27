
// ProjectAA.h: PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// 主符号
#include "SystemManager.h"
#include "ConfigFileManager.h"


// CProjectAAApp:
// 有关此类的实现，请参阅 ProjectAA.cpp
//

class CProjectAAApp : public CWinApp
{
public:
	CProjectAAApp();

// 重写
public:
	virtual BOOL InitInstance();

// 实现

	DECLARE_MESSAGE_MAP()
};

extern CProjectAAApp theApp;
extern CSystemManager      gSystemMgr;
extern CSystemLog          gSystemLog;
extern CConfigFileManager  gConfigMgr;
