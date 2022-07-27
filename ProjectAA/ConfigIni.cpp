#include "pch.h"
#include "ConfigIni.h"
#include "SystemLog.h"
#include "SystemManager.h"
#include <stdio.h>

extern CSystemLog        gSystemLog;
extern CSystemManager    gSystemMgr;

CConfigIni::CConfigIni()
{

}

CConfigIni::~CConfigIni()
{

}

void CConfigIni::ConfigIniInit(CString cstrPath)
{
	m_cstrPath = cstrPath;
	CFileFind    finder;
	BOOL bfFind = finder.FindFile(m_cstrPath);
	if (!bfFind)
	{
		gSystemLog.DisplayLogAndSave(L"该路径下没有对应的ini配置文件", LV_ERROR);
		gSystemLog.DisplayLogAndSave(m_cstrPath.GetBuffer(), LV_ERROR);
		return;
	}


}

void CConfigIni::ReadConfigIni(CString cstrItemFather, CString cstrItemSon, CString& cstrValue)
{
	CString str;
	GetPrivateProfileString(cstrItemFather, cstrItemSon, CString("NULL"), str.GetBuffer(MAX_PATH), MAX_PATH, m_cstrPath);
	cstrValue = str;
}

void CConfigIni::SaveConfigIni(CString cstrItemFather, CString cstrItemSon, CString cstrValue)
{
	WritePrivateProfileStringW(cstrItemFather, cstrItemSon, cstrValue, m_cstrPath);

}

void CConfigIni::GetCurrentDir(LPWSTR path)
{
	if (path == NULL) return;

	GetModuleFileName(NULL, path, MAX_PATH);

	(_tcsrchr(path, _T('\\')))[0] = 0;
}



