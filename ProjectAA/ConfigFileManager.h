#pragma once

#include <stdlib.h>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <set>
#include <algorithm>
#include <atlconv.h>
#include <boost\lexical_cast.hpp>
#include <boost\algorithm\string.hpp>
#include "../tinxml/tinyxml.h"
#include "TypeDef.h"
#include "_utils.h"

using namespace std;
using namespace boost;


class CConfigFileManager
{
public:
	CConfigFileManager() :m_wstrConfigFilePath(CConfigFileManager::GetConfigFilePath())
	{
		m_bLoaded = false;
		ParseConfigFile();
	}

	bool ParseConfigFile()
	{
		if (m_bLoaded == true)
		{
			return true;
		}
		m_cstrIndex = AfxGetApp()->m_lpCmdLine;
		if (INVALID_FILE_ATTRIBUTES == (::GetFileAttributes(m_wstrConfigFilePath.c_str())))
		{
			AfxMessageBox(_T("CANNOT ProjectAA.exe.config"), MB_OK | MB_ICONERROR);
			return false;
		}
		string strPath = _utils::Unicode2Ansi(m_wstrConfigFilePath);
		TiXmlDocument config(strPath);
		if (!config.LoadFile())
		{
			return false;
		}
		TiXmlNode* ptrRootNode = config.FirstChild("configuration");
		if (ptrRootNode == nullptr)
		{
			return false;
		}
		//ParseBasicSetting(ptrRootNode);
		ParseIOSetting(ptrRootNode);
		ParseAxisSetting(ptrRootNode);
		//ParseClientSetting(ptrRootNode);
		m_bLoaded = true;
		return true;
	}

	wstring GetBasicSetting(wstring wstrName)
	{
		wstring wstrRet(L"");
		if (m_dictBasicSetting.empty())
		{
			ParseConfigFile();
			m_bLoaded = true;
		}
		if (m_dictBasicSetting.find(wstrName) != m_dictBasicSetting.end())
		{
			wstrRet = m_dictBasicSetting[wstrName];
		}
		return wstrRet;
	}

	std::vector<IO_MODULE> *GetIOInputSetting()
	{
		if (m_vIoInputSetting.empty())
		{
			return nullptr;
		}
		return &m_vIoInputSetting;
	}

	std::vector<IO_MODULE> *GetIOOutputSetting()
	{
		if (m_vIoOutputSetting.empty())
		{
			return nullptr;
		}
		return &m_vIoOutputSetting;
	}

	std::vector<CLIENT_SETTING> *GetClientSetting()
	{
		if (m_vClientSetting.empty())
		{
			return nullptr;
		}
		return &m_vClientSetting;
	}

	std::map<int, AXIS_SETTING>* GetAxisSettingDict()
	{
		if (m_dictAxisSetting.empty())
		{
			return nullptr;
		}
		return &m_dictAxisSetting;
	}

	void ResetInternalData()
	{
		m_bLoaded = false;
		m_dictBasicSetting.clear();
		m_dictAxisSetting.clear();
		m_vIoInputSetting.clear();
		m_vIoOutputSetting.clear();
	}

	void ReloadConfigFile()
	{
		ResetInternalData();
		ParseConfigFile();
	}

	bool UpdateBasicSetting(string strItem, CString cstrValue)
	{
		string strPath = _utils::Unicode2Ansi(m_wstrConfigFilePath);
		TiXmlDocument config(strPath);
		if (!config.LoadFile())
		{
			return  false;
		}
		TiXmlNode* ptrRootNode = config.FirstChild("configuration");
		if (nullptr == ptrRootNode)
		{
			return  false;
		}
		TiXmlNode* pCommonNode = ptrRootNode->FirstChild("CommonSetting");
		if (pCommonNode == nullptr)
			return false;

		string key;
		string strValue;
		TiXmlElement* pElementList = pCommonNode->ToElement();
		if (pElementList != nullptr)
		{
			for (TiXmlElement* pElement = pElementList->FirstChildElement(); pElement; pElement = pElement->NextSiblingElement())
			{
				pElement->QueryValueAttribute("key", &key);
				if (!key.empty() && key == strItem)
				{
					pElement->SetAttribute("value", _utils::Unicode2Ansi(cstrValue.GetBuffer()));
				}
			}
		}config.SaveFile();
		m_bLoaded = false;
		ParseConfigFile();
		return true;
	}

	bool UpdateAxisSetting(wstring wstrAxisId, AXIS_SETTING axisSetting)
	{
		string strPath = _utils::Unicode2Ansi(m_wstrConfigFilePath);
		TiXmlDocument config(strPath);
		if (!config.LoadFile())
		{
			return  false;
		}
		TiXmlNode* ptrRootNode = config.FirstChild("configuration");
		if (nullptr == ptrRootNode)
		{
			return  false;
		}
		TiXmlNode* pBasicSettingNode = ptrRootNode->FirstChild("AxisSetting");
		if (pBasicSettingNode == nullptr)
		{
			return false;
		}
		auto ptrNodeElement = pBasicSettingNode->ToElement();
		if (nullptr == ptrNodeElement)
		{
			return false;
		}
		for (auto pElement = ptrNodeElement->FirstChildElement(); pElement; pElement = pElement->NextSiblingElement())
		{
			TiXmlElement* pElementSpect = pElement->ToElement();
			if (pElementSpect != nullptr)
			{
				string strId;
				pElementSpect->QueryStringAttribute("nId", &strId);

				wstring wstrId = _utils::AnsiToUnicode(strId);
				if (wstrId == wstrAxisId)
				{
					CString cstr;
					cstr.Format(L"%d", axisSetting.m_nSpeedHome);
					pElementSpect->SetAttribute("SpeedHome", _utils::Unicode2Ansi(cstr.GetBuffer()));
					cstr.Format(L"%d", axisSetting.m_nSpeedMove);
					pElementSpect->SetAttribute("SpeedMove", _utils::Unicode2Ansi(cstr.GetBuffer()));
					cstr.Format(L"%d", axisSetting.m_nDirection);
					pElementSpect->SetAttribute("Direction", _utils::Unicode2Ansi(cstr.GetBuffer()));
					cstr.Format(L"%.2f", axisSetting.m_nSpeedAcc);
					pElementSpect->SetAttribute("SpeedTime", _utils::Unicode2Ansi(cstr.GetBuffer()));
					cstr.Format(L"%d", axisSetting.m_nStartSpeed);
					pElementSpect->SetAttribute("StartSpeed", _utils::Unicode2Ansi(cstr.GetBuffer()));
				}
			}
		}
		config.SaveFile();
		m_bLoaded = false;
		ParseConfigFile();
		return true;
	}

	void ConfigIniInit(CString cstrPath)
	{
		m_cstrPath = cstrPath;
		CFileFind    finder;
		BOOL bfFind = finder.FindFile(m_cstrPath);
		if (!bfFind)
		{
			return;
		}
	}

	void ReadConfigIni(CString cstrItemFather, CString cstrItemSon, CString &cstrValue)
	{
		CString str;
		GetPrivateProfileString(cstrItemFather, cstrItemSon, CString("NULL"), str.GetBuffer(MAX_PATH), MAX_PATH, m_cstrPath);
		cstrValue = str;
	}

	void SaveConfigIni(CString cstrItemFather, CString cstrItemSon, CString cstrValue)
	{
		WritePrivateProfileStringW(cstrItemFather, cstrItemSon, cstrValue, m_cstrPath);
	}

	void GetCurrentDir(LPWSTR path)
	{
		if (path == NULL) return;

		GetModuleFileName(NULL, path, MAX_PATH);

		(_tcsrchr(path, _T('\\')))[0] = 0;
	}
private:
	static std::wstring GetConfigFilePath()
	{
		TCHAR  moduleFileName[MAX_PATH];
		::GetModuleFileName(NULL, moduleFileName, MAX_PATH);
		wstring filePath(moduleFileName);
		filePath.append(L".config");
		return filePath;
	}


	void ParseBasicSetting(TiXmlNode* ptrRootNode)
	{
		TiXmlNode* ptrBasicNode = ptrRootNode->FirstChild("CommonSetting");
		if (ptrBasicNode == nullptr)
		{
			return;
		}
		string strKey(""), strValue("");
		TiXmlElement* ptrElementArray = ptrBasicNode->ToElement();
		if (ptrElementArray == nullptr)
		{
			return;
		}
		for (auto pElement = ptrElementArray->FirstChildElement(); pElement; pElement = pElement->NextSiblingElement())
		{
			pElement->QueryValueAttribute("key", &strKey);
			pElement->QueryValueAttribute("value", &strValue);
			if (strKey != "" && strValue != "")
			{
				wstring wstrKey = _utils::AnsiToUnicode(strKey);
				wstring wstrValue = _utils::AnsiToUnicode(strValue);
				m_dictBasicSetting[wstrKey] = wstrValue;
			}
		}
	}

	void ParseIOSetting(TiXmlNode* pRootNode)
	{
		TiXmlNode* pIONode = pRootNode->FirstChild("IOSetting");
		if (pIONode == nullptr)
		{
			return;
		}
		TiXmlElement* pElementList = pIONode->ToElement();
		if (pElementList != nullptr)
		{
			for (TiXmlElement* pElement = pElementList->FirstChildElement(); pElement; pElement = pElement->NextSiblingElement())
			{
				IO_MODULE tempIo;
				pElement->QueryIntAttribute("port", &tempIo.m_nPort);
				pElement->QueryIntAttribute("type", &tempIo.m_nType);
				string sDes = "";
				pElement->QueryStringAttribute("description", &sDes);
				wstring wsDes = _utils::Utf8ToUnicode(sDes);
				tempIo.m_cstrDescription = wsDes.c_str();
				if (tempIo.m_nType == 0)
				{
					m_vIoInputSetting.push_back(tempIo);
				}
				else if (tempIo.m_nType == 1)
				{
					m_vIoOutputSetting.push_back(tempIo);
				}
			}
		}
	}

	void ParseAxisSetting(TiXmlNode* pRootNode)
	{
		TiXmlNode* pdimListSettingSetting = pRootNode->FirstChild("AxisSetting");
		if (pdimListSettingSetting == nullptr)
		{
			return;
		}
		TiXmlElement* pdimListSetting = pdimListSettingSetting->ToElement();
		for (auto pElement = pdimListSetting->FirstChildElement(); pElement; pElement = pElement->NextSiblingElement())
		{
			AXIS_SETTING axis_Setting;
			pElement->QueryIntAttribute("nId", &axis_Setting.m_nAxisId);
			pElement->QueryIntAttribute("SpeedHome", &axis_Setting.m_nSpeedHome);
			pElement->QueryIntAttribute("SpeedMove", &axis_Setting.m_nSpeedMove);
			pElement->QueryIntAttribute("Direction", &axis_Setting.m_nDirection);
			pElement->QueryDoubleAttribute("SpeedTime", &axis_Setting.m_nSpeedAcc);
			pElement->QueryIntAttribute("StartSpeed", &axis_Setting.m_nStartSpeed);

			string strName;
			pElement->QueryStringAttribute("name", &strName);
			axis_Setting.m_wstrAxisName = _utils::Utf8ToUnicode(strName);

			string strProportion;
			pElement->QueryStringAttribute("proportion", &strProportion);
			axis_Setting.m_wstrProportion = _utils::Utf8ToUnicode(strProportion);
			m_dictAxisSetting[axis_Setting.m_nAxisId] = axis_Setting;
		}
	}

	void ParseClientSetting(TiXmlNode* pRootNode)
	{
		TiXmlNode* pdimListSettingSetting = pRootNode->FirstChild("ClientSetting");
		if (pdimListSettingSetting == nullptr)
		{
			return;
		}
		TiXmlElement* pdimListSetting = pdimListSettingSetting->ToElement();
		for (auto pElement = pdimListSetting->FirstChildElement(); pElement; pElement = pElement->NextSiblingElement())
		{
			CLIENT_SETTING client_Setting;
			pElement->QueryIntAttribute("nIndex", &client_Setting.m_nIndex);

			string strIp;
			pElement->QueryStringAttribute("Ip", &strIp);
			client_Setting.m_wstrIp = _utils::Utf8ToUnicode(strIp);

			pElement->QueryIntAttribute("Port", &client_Setting.m_nPort);


			m_vClientSetting.push_back(client_Setting);
		}
	}



public:
	wstring                             m_wstrCrtTaskName;
	std::map<wstring, wstring>  m_dictBasicSetting;
	CString      m_cstrIndex = L"100";
	CString      m_cstrPath = L"";
private:
	bool                                  m_bLoaded;
	wstring                             m_wstrConfigFilePath;

	std::vector<IO_MODULE>  m_vIoInputSetting;
	std::vector<IO_MODULE>  m_vIoOutputSetting;
	std::map<int, AXIS_SETTING>                m_dictAxisSetting;
	std::vector<CLIENT_SETTING>         m_vClientSetting;


	CConfigFileManager(CConfigFileManager&&) = delete;
	CConfigFileManager(const CConfigFileManager& other) = delete;
	CConfigFileManager& operator=(CConfigFileManager&&) = delete;
	CConfigFileManager& operator=(const CConfigFileManager& other) = delete;
};