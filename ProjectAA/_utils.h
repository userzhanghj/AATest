#pragma once
#include <atlcom.h>
#include <atlbase.h>
#include <string>
#include <algorithm>
#include <fstream>
#include <iterator>
#include <io.h>
#include <map>
#include <tuple>
#include <vector>
#include <iomanip>
#include <regex>
#include <boost\algorithm\string.hpp>
#include <boost\lexical_cast.hpp>
#include <TlHelp32.h>
#include <boost\circular_buffer.hpp>
#include "pch.h"


using namespace std;
using namespace boost;

class _utils
{
public:

	static wstring Utf8ToUnicode(const string& str)
	{
		wstring tmpStr(L"");
		int wcsLen = ::MultiByteToWideChar(CP_UTF8, NULL, str.c_str(), (int)strlen(str.c_str()), NULL, 0);
		if (wcsLen <= 0)
			return tmpStr;
		wstring retWstr(wcsLen, '\0');
		::MultiByteToWideChar(CP_UTF8, NULL, str.c_str(), (int)strlen(str.c_str()), &retWstr[0], wcsLen);

		return retWstr;
	}

	//static string Unicode2Utf8(const wstring& unicodeStr)
	//{
	//	std::string retStr("");
	//	int strLen = (int)::WideCharToMultiByte(CP_UTF8, NULL, unicodeStr.c_str(), (int)wcslen(unicodeStr.c_str()), NULL, 0, NULL, NULL);
	//	if (strLen == 0)
	//		return retStr;
	//	std::vector<char> strBuffer(strLen, '\0');
	//	::WideCharToMultiByte(CP_UTF8, NULL, unicodeStr.c_str(), (int)wcslen(unicodeStr.c_str()), &strBuffer[0], strLen, NULL, NULL);

	//	retStr.assign(strBuffer.begin(), strBuffer.end());
	//	return retStr;
	//}

	static wstring AnsiToUnicode(const string& str)
	{
		wstring tmpStr(L"");
		int wcsLen = ::MultiByteToWideChar(CP_ACP, NULL, str.c_str(), (int)strlen(str.c_str()), NULL, 0);
		if (wcsLen <= 0)
			return tmpStr;
		wstring retWstr(wcsLen, '\0');
		::MultiByteToWideChar(CP_ACP, NULL, str.c_str(), (int)strlen(str.c_str()), &retWstr[0], wcsLen);
		return retWstr;
	}

	static string Unicode2Ansi(const wstring& unicodeStr)
	{
		std::string retStr("");
		int strLen = (int)::WideCharToMultiByte(CP_ACP, NULL, unicodeStr.c_str(), (int)wcslen(unicodeStr.c_str()), NULL, 0, NULL, NULL);
		if (strLen == 0)
			return retStr;
		std::vector<char> strBuffer(strLen, '\0');
		::WideCharToMultiByte(CP_ACP, NULL, unicodeStr.c_str(), (int)wcslen(unicodeStr.c_str()), &strBuffer[0], strLen, NULL, NULL);

		retStr.assign(strBuffer.begin(), strBuffer.end());
		return retStr;
	}

	static string TChar2Utf8(const CString& tStr)
	{
		wstring wstr = CT2W(tStr);
		return Unicode2Ansi(wstr);
	}

	static CString Utf82TChar(const string&str)
	{
		CString cStr(str.c_str());
		return cStr;
	}

	static CString Unicode2TChar(const wstring&wstr)
	{
		string str = Unicode2Ansi(wstr);
		CString cStr= Utf82TChar(str);
		return cStr;
	}

	static void TrimString(std::vector<wstring>& vStr)
	{
		for (size_t t = 0; t < vStr.size(); ++t)
		{
			boost::trim(vStr[t]);
		}
	}

	static void TrimString(std::vector<string>& vStr)
	{
		for (size_t t = 0; t < vStr.size(); ++t)
		{
			boost::trim(vStr[t]);
		}
	}

	static bool IsNumericString(wstring strValue, bool bIntegerOnly = false)
	{
		if (strValue.empty())
			return false;
		std::wregex wrx;
		if (bIntegerOnly)
		{
			wrx = L"\\d+$";
		}
		else
		{
			wrx = L"^[+-]?[0-9]+(?:\\.[0-9]{1,6})?$";
		}
		bool ret = std::regex_match(strValue, wrx);
		return ret;
	}

	static bool IsNumericString(CString strValue, bool bIntegerOnly = false)
	{
		int len = strValue.GetLength();
		if (len <= 0)
		{
			return false;
		}
		wstring value = CT2W(strValue);

		std::wregex wrx;
		if (bIntegerOnly)
		{
			wrx = L"\\d+$";
		}
		else
		{
			wrx = L"^-?[0-9]+([.][0-9]+){0,1}$";
		}
		bool ret = std::regex_match(value, wrx);
		if (!ret)
			return false;

		if (value.find(L".") != wstring::npos)
		{
			std::vector<wstring> vItem;// = SplitString(value, L".");
			if (!vItem.empty())
			{
				wstring wstrInt = vItem[0];
				if (wstrInt.size() >= 2 && wstrInt[0] == '0')
				{
					return false;
				}
			}
		}
		else
		{
			if (value.size() >= 2 && value[0] == '0')
				return false;
		}
		return ret;
	}

	static float to_float(wstring strValue)
	{
		if (!IsNumericString(strValue))
		{
			return -9999999.9f;
		}
		try
		{
			return boost::lexical_cast<float>(strValue);
		}
		catch (...)
		{
			return -9999999.9f;
		}
		return-9999999.9f;
	}

	static long to_long(wstring wstrValue)
	{
		if (!IsNumericString(wstrValue))
		{
			return -9999999;
		}
		try
		{
			return boost::lexical_cast<long>(wstrValue);
		}
		catch (...)
		{
			return -9999999;
		}
		return-9999999;
	}

	static float ConvertStr2Value(wstring strValue)
	{
		if (strValue == L"N/A")
			return 0.0f;
		try
		{
			return boost::lexical_cast<float>(strValue);
		}
		catch (...)
		{
			return 0.0f;
		}
		return 0.0f;
	}

	static int ConvertStr2Value(CString strValue)
	{
		wstring wstrValue = CT2W(strValue);
		int nRet = wcstol(wstrValue.c_str(), nullptr, 10);
		return nRet;
	}

	static TCHAR* CStringToTChar(CString& cstr)
	{
		int len = (int)cstr.GetLength();
		TCHAR* tChar = cstr.GetBuffer(len);
		cstr.ReleaseBuffer();
		return tChar;
	}

	static bool CheckDirExist(const wstring& path)
	{
		if (INVALID_FILE_ATTRIBUTES == (::GetFileAttributes(path.c_str())))
		{
			return false;
		}
		return true;
	}

    static bool CheckDirExist(const string& path)
    {
        if (INVALID_FILE_ATTRIBUTES == (::GetFileAttributesA(path.c_str())))
        {
            return false;
        }
        return true;
    }

	static std::vector<wstring> SplitString(wstring strTarget, wstring strSeperator,
		algorithm::token_compress_mode_type type = token_compress_on, bool m_bTrim = true)
	{
		std::vector<wstring> vSplitRslt;
		boost::split(vSplitRslt, strTarget, boost::is_any_of(strSeperator), type);
		if (m_bTrim)
		{
			TrimString(vSplitRslt);
		}

		return vSplitRslt;
	}
	//static HObject Mat2HObject(const cv::Mat & matImg)
	//{
	//	HObject retImg = HObject();
	//	int height = matImg.rows;
	//	int width = matImg.cols;
	//	size_t sz = height * width;
	//	if (matImg.type() == CV_8UC3)
	//	{
	//		std::vector<cv::Mat> imgChannel;
	//		cv::split(matImg, imgChannel);
	//		cv::Mat imgB = imgChannel[0];
	//		cv::Mat imgG = imgChannel[1];
	//		cv::Mat imgR = imgChannel[2];

	//		std::vector<uchar> dataR(sz, 0);
	//		std::vector<uchar> dataG(sz, 0);
	//		std::vector<uchar> dataB(sz, 0);

	//		for (int i = 0; i < height; i++) // TODO: parallel_for
	//		{
	//			memcpy(&dataR[0] + width*i, imgR.data + imgR.step*i, width);
	//			memcpy(&dataG[0] + width*i, imgG.data + imgG.step*i, width);
	//			memcpy(&dataB[0] + width*i, imgB.data + imgB.step*i, width);
	//		}
	//		GenImage3(&retImg, "byte", width, height, (Hlong)&dataR[0], (Hlong)&dataG[0], (Hlong)&dataB[0]);
	//	}
	//	//CV_8UC1
	//	if (matImg.type() == CV_8UC1)
	//	{
	//		std::vector<uchar> data(sz, 0);
	//		for (int i = 0; i < height; i++)
	//		{
	//			memcpy(&data[0] + width*i, matImg.data + matImg.step*i, width);
	//		}
	//		GenImage1(&retImg, "byte", width, height, (Hlong)&data[0]);
	//	}
	//	//CV_32FC1
	//	if (matImg.type() == CV_32FC1)
	//	{
	//		std::vector<float> data(sz * 4, 0);
	//		for (int i = 0; i < height; i++)
	//		{
	//			memcpy(&data[0] + width*i, matImg.data + matImg.step*i, width * 4);
	//		}
	//		GenImage1(&retImg, "real", width, height, (Hlong)&data[0]);
	//	}
	//	return retImg;
	//}

	//static cv::Mat HObject2Mat(HObject objImg)
	//{
	//	HTuple htCh;
	//	HString cType;
	//	cv::Mat retCvImg;
	//	ConvertImageType(objImg, &objImg, "byte");
	//	CountChannels(objImg, &htCh);
	//	Hlong width = 0;
	//	Hlong height = 0;
	//	if (htCh[0].I() == 1)
	//	{
	//		HImage hImg(objImg);
	//		void* ptr = hImg.GetImagePointer1(&cType, &width, &height);
	//		int w = (int)width;
	//		int h = (int)height;
	//		retCvImg.create(h, w, CV_8UC1);
	//		uchar* pData = static_cast<uchar*>(ptr);
	//		memcpy(retCvImg.data, pData, w*h);
	//	}
	//	if (htCh[0].I() == 3)
	//	{
	//		void* ptrR = nullptr;
	//		void* ptrG = nullptr;
	//		void* ptrB = nullptr;
	//		HImage hImg(objImg);
	//		hImg.GetImagePointer3(&ptrR, &ptrG, &ptrB, &cType, &width, &height);
	//		int w = (int)width;
	//		int h = (int)height;
	//		size_t sz = w*h;
	//		retCvImg.create(h, w, CV_8UC3);
	//		std::vector<cv::Mat> vecM(3);
	//		vecM[0].create(h, w, CV_8UC1);
	//		vecM[1].create(h, w, CV_8UC1);
	//		vecM[2].create(h, w, CV_8UC1);
	//		uchar* pR = (uchar*)ptrR;
	//		uchar* pG = (uchar*)ptrG;
	//		uchar* pB = (uchar*)ptrB;
	//		//TODO:
	//		memcpy(vecM[2].data, pR, sz);
	//		memcpy(vecM[1].data, pG, sz);
	//		memcpy(vecM[0].data, pB, sz);
	//		cv::merge(vecM, retCvImg);
	//	}
	//	return retCvImg;
	//}

	static void GetFiles(std::string strPath, std::vector<std::string>&strFiles,bool bIterator)//获取指定路径下所有文件的绝对路径
	{
		intptr_t hFile = 0;//文件句柄
		struct _finddata_t fileInfo;//存储文件信息的结构体
		std::string  strFilePath = strPath + "\\*";
		if ((hFile = _findfirst(strFilePath.c_str(), &fileInfo)) != -1)
		{
			do
			{
				if (fileInfo.attrib&_A_SUBDIR)//目录
				{
					if (strcmp(fileInfo.name, ".") != 0 && strcmp(fileInfo.name, "..") != 0)
					{
						if (bIterator)//迭代
						{
							std::string strNewPath = strPath + "\\" + fileInfo.name;
							GetFiles(strNewPath, strFiles, bIterator);
						}
						else//不迭代
						{
							strFiles.push_back(strPath + "\\" + fileInfo.name);
							continue;
						}
					}
				}
				else
				{
					strFiles.push_back(strPath + "\\" + fileInfo.name);
				}
			} while (_findnext(hFile, &fileInfo) == 0);
			_findclose(hFile);
		}
	}

	static void ReadFileToWstring(wstring wstrFilePath, wstring& wstrRet)
	{
		wifstream fs(wstrFilePath);
		wstring ret(istreambuf_iterator<wchar_t>(fs), (istreambuf_iterator<wchar_t>()));
		wstrRet = std::move(ret);
	}

	static void ReadFileToString(string strFilePath, string& strRet)
	{
		ifstream fs(strFilePath);
		string ret(istreambuf_iterator<char>(fs), (istreambuf_iterator<char>()));
		strRet = std::move(ret);
	}

	static void FloatToByteVector(float fInput, vector<BYTE> &vBOutput)
	{
		vBOutput.resize(4);
		float fTest = fInput;
		byte bAry[4];
		byte* lpAry = bAry;
		*(float*)lpAry = fTest;
		for (int i = 0; i < 4; i++)
		{
			vBOutput[i] = bAry[i];
		}
	}

	static void AutoFitWindowSize(int& nWindowWidth, int& nWindowHeight, 
		int& nImgWidth, int& nImgHeight,
		double& dPartRow_LeftUp, double& dPartCol_LeftUp,
		double& dPartRow_RightDown, double& dPartCol_RightDown)
	{
		double dRateImg = nImgWidth*1.0 / nImgHeight;
		double dRateWnd = (double)(nWindowWidth*1.0) / nWindowHeight;
		double dRow0 = 0.0, dCol0 = 0.0, dRow1 = nImgHeight*1.0, dCol1 = nImgWidth*1.0;
		if (dRateWnd > dRateImg)
		{
			double dNewWidth = dRateWnd*nImgHeight;
			dRow0 = 0;
			dCol0 = (nImgWidth - dNewWidth) / 2;
			dRow1 = nImgHeight;
			dCol1 = nImgWidth + (dNewWidth - nImgWidth) / 2;
		}
		else
		{
			double dNewHeight = nImgWidth / dRateWnd;
			dRow0 = (nImgHeight - dNewHeight) / 2;
			dCol0 = 0;
			dRow1 = nImgHeight + (dNewHeight - nImgHeight) / 2;
			dCol1 = nImgWidth;
		}
		dPartRow_LeftUp = dRow0;
		dPartCol_LeftUp = dCol0;
		dPartRow_RightDown = dRow1;
		dPartCol_RightDown = dCol1;
	}

	static bool CheckResult(HRESULT hr)
	{
		if (hr == S_FALSE)
			return false;
		if (SUCCEEDED(hr))
		{
			return true;
		}
		return false;
	}

	static VARENUM GetType(wstring strType)
	{
		VARENUM ret;
		ret = VT_EMPTY;
		if (strType == L"B")
			return VT_UI1;
		if (strType == L"LP")
			return VT_I4;
		if (strType == L"L")
			return VT_I4;
		if (strType == L"F" || strType == L"FP")
			return VT_R4;
		if (strType.find(L"SP") != wstring::npos)
			return VT_BSTR;

		return ret;
	}

	static DISPID GetInterfaceDispID(IDispatch * pDisp, wstring strFuncName)
	{
		DISPID dispID = -1;
		if (pDisp == nullptr)
			return dispID;

		CComBSTR tmp(strFuncName.c_str());
		pDisp->GetIDsOfNames(IID_NULL, &tmp, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
		return dispID;
	}

	static HRESULT GetInterfaceMetadata(IDispatch * pDisp, wstring funcName, wstring& retStr)
	{
		if (pDisp == nullptr)
			return S_FALSE;
		wstring helpFuncName = funcName + L"Metadata";
		DISPID dispID;
		CComBSTR tmp(helpFuncName.c_str());
		HRESULT hr = pDisp->GetIDsOfNames(IID_NULL, &tmp, 1, LOCALE_SYSTEM_DEFAULT, &dispID);
		if (SUCCEEDED(hr))
		{
			DISPPARAMS dispParams = { NULL, NULL, 0, 0 };
			CComVariant strHelp;
			hr = pDisp->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_METHOD, &dispParams, &strHelp, NULL, NULL);
			if (SUCCEEDED(hr))
			{
				retStr = COLE2T(strHelp.bstrVal);
				return S_OK;
			}
		}
		return S_FALSE;
	}
};

class chronograph
{
public:
	chronograph()
	{
		QueryPerformanceFrequency(&m_freq);
		QueryPerformanceCounter(&m_bgn);
	}
	void start()
	{
		QueryPerformanceCounter(&m_bgn);
	}

	double duration()
	{
		QueryPerformanceCounter(&m_end);
		//return (m_end.QuadPart - m_bgn.QuadPart) * 1000.0 / m_freq.QuadPart;
		return (m_end.QuadPart - m_bgn.QuadPart) * 1.0 / m_freq.QuadPart;

	}

	string duration_str()
	{
		string strDur = to_string(duration());
		return strDur;
	}

	wstring duration_wstr()
	{
		wstring wstrDur = to_wstring(duration());
		return wstrDur;
	}

	LARGE_INTEGER now()
	{
		LARGE_INTEGER now;
		QueryPerformanceCounter(&now);
		return now;
	}
	double DoubleNow()
	{
		LARGE_INTEGER now;
		QueryPerformanceCounter(&now);
		return now.QuadPart*1000.0 / m_freq.QuadPart;
	}
private:
	LARGE_INTEGER m_freq;
	LARGE_INTEGER m_bgn;
	LARGE_INTEGER m_end;
};


