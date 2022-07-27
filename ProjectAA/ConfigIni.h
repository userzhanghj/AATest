#pragma once

#include <string>
#include <vector>
#include <afxsock.h>
#include "TypeDef.h"


using namespace std;

class CConfigIni
{
public:
	CConfigIni();
	~CConfigIni();


	CString m_cstrPath = L"";

	void ConfigIniInit(CString cstrPath);
	void ReadConfigIni(CString cstrItemFather, CString cstrItemSon, CString &cstrValue);
	void SaveConfigIni(CString cstrItemFather, CString cstrItemSon, CString cstrValue);


	void GetCurrentDir(LPWSTR path);


};