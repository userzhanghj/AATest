#pragma once

#include <string>
#include <vector>
#include <map>
#include <boost\lexical_cast.hpp>
#include "TypeDef.h"

using namespace std;
using namespace boost;

class CSystemLog
{
public:
	CSystemLog();
	CSystemLog(wstring wstrFolderName);
	~CSystemLog();
	HWND m_hUiHandle;
	void DisplayLog(wstring strMsg, bool bHighResolution = true);
	void FlushLogCache();
	void DisplayLogAndSave(wstring strMsg, eEVENT_LEVEL m_uacLevel);

private:
	wstring          m_wstrPath;
	wstring          m_wstrLastLog;
	CString          m_sLastLogMsg;
	CRITICAL_SECTION m_csLogger;
	std::multimap<wstring, wstring> m_dictLogMsg;
};

