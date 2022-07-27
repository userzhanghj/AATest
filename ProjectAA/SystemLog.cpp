#include "pch.h"
#include "SystemLog.h"
#include "_utils.h"

CSystemLog::CSystemLog() : m_hUiHandle(NULL)
{
	TCHAR  moduleFileName[MAX_PATH];
	::GetModuleFileName(NULL, moduleFileName, MAX_PATH);
	(_tcsrchr(moduleFileName, _T('\\')))[1] = 0;
	CString strPath = moduleFileName;
	strPath.Append(_T("\\data\\"));
	if (!_wmkdir(strPath))
	{
		//TODO
	}
	strPath.Append(_T("\\log\\"));
	m_wstrPath = strPath.GetString();
	if (!_wmkdir(m_wstrPath.c_str()))
	{
		//TODO
	}
	m_wstrLastLog = L"";
	::InitializeCriticalSection(&m_csLogger);
}

CSystemLog::CSystemLog(wstring wstrFolderName) : m_hUiHandle(NULL)
{
	TCHAR  moduleFileName[MAX_PATH];
	::GetModuleFileName(NULL, moduleFileName, MAX_PATH);
	(_tcsrchr(moduleFileName, _T('\\')))[1] = 0;
	CString strPath = moduleFileName;
	strPath.Append(_T("\\data\\"));
	if (!_wmkdir(strPath))
	{
		//TODO
	}
	strPath.Append(_T("\\log\\"));
	m_wstrPath = strPath.GetString();
	if (!_wmkdir(m_wstrPath.c_str()))
	{
		//TODO
	}
	m_wstrPath.append(wstrFolderName);
	if (!_wmkdir(m_wstrPath.c_str()))
	{
		//TODO
	}
	m_wstrLastLog = L"";
	::InitializeCriticalSection(&m_csLogger);
}


CSystemLog::~CSystemLog()
{
	::DeleteCriticalSection(&m_csLogger);
}

void CSystemLog::DisplayLog(wstring strMsg, bool bHighResolution)
{
	::EnterCriticalSection(&m_csLogger);
	SYSTEMTIME dt;
	::GetLocalTime(&dt);
	CString sTimestamp;
	if (!bHighResolution)
		sTimestamp.Format(_T("%02d:%02d:%02d"), dt.wHour, dt.wMinute, dt.wSecond);
	else
		sTimestamp.Format(_T("%02d:%02d:%02d:%03d"), dt.wHour, dt.wMinute, dt.wSecond, dt.wMilliseconds);
	wstring strTimestamp = sTimestamp.GetString();
	wstring strLog = strTimestamp + strMsg;
	m_dictLogMsg.insert(pair<wstring, wstring>(strTimestamp, strLog));
	m_wstrLastLog = strLog;
	::LeaveCriticalSection(&m_csLogger);
}


void CSystemLog::DisplayLogAndSave(wstring wstrMsg, eEVENT_LEVEL nLevel)
{
	::EnterCriticalSection(&m_csLogger);
	SYSTEMTIME dt;
	::GetLocalTime(&dt);
	CString sTimestamp;
	sTimestamp.Format(_T("%02d:%02d:%02d:%03d"), dt.wHour, dt.wMinute, dt.wSecond, dt.wMilliseconds);
	wstring strTimestamp = sTimestamp.GetString();
	m_wstrLastLog = strTimestamp + L"#" + wstrMsg;

	m_dictLogMsg.insert(pair<wstring, wstring>(strTimestamp, m_wstrLastLog));
	::LeaveCriticalSection(&m_csLogger);

	CString sLog = m_wstrLastLog.c_str();
	BSTR bstr = sLog.AllocSysString();
	::PostMessage(m_hUiHandle, WM_SEND_LOG_MSG_TO_MAIN_UI, (WPARAM)bstr, LPARAM(nLevel));
	FlushLogCache();
}


CMutex cMutlog(false, NULL);

void CSystemLog::FlushLogCache()
{
	std::multimap<wstring, wstring> tmpMsgArray;
	::EnterCriticalSection(&m_csLogger);
	tmpMsgArray = m_dictLogMsg;
	m_dictLogMsg.clear();
	::LeaveCriticalSection(&m_csLogger);

	if (tmpMsgArray.empty())
	{
		return;
	}
	SYSTEMTIME dt;
	::GetLocalTime(&dt);
	CString strNewDate;
	strNewDate.Format(_T("%d-%02d-%02d"), dt.wYear, dt.wMonth, dt.wDay);
	wstring wstrLogFile = m_wstrPath + L"\\" + strNewDate.GetString() + L".log";
	string strFile = _utils::Unicode2Ansi(wstrLogFile);
	cMutlog.Lock();
	FILE* fp1 = nullptr;
	fopen_s(&fp1, strFile.c_str(), "a");
	for (auto it = tmpMsgArray.begin(); it != tmpMsgArray.end(); it++)
	{
		string strLog = _utils::Unicode2Ansi(it->second);
		fputs(strLog.c_str(), fp1);
		fputs("\r\n", fp1);
	}
	fclose(fp1);
	cMutlog.Unlock();
}

