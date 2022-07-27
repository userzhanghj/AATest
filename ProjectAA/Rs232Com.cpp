#include <afxwin.h>
#include "pch.h"
#include <math.h>
#include "Rs232Com.h"
#include "ConfigFileManager.h"
#include "SystemLog.h"
#include "TypeDef.h"
#include "SystemManager.h"

extern CSystemLog     gSystemLog;
extern CConfigFileManager gConfigMgr;
extern CSystemManager    gSystemMgr;
CComm::CComm()
	:m_bThreadAlive(false),
	m_nRxBuffSize(256),
	m_pOwnerWnd(nullptr),
	m_hCom(NULL),
	m_PortName(L"")
{
	m_RXBuff = std::vector<byte>(m_nRxBuffSize, 0x00);
	m_hRecvEvent = ::CreateEventW(NULL, TRUE, FALSE, L"RecvData");
}


bool CComm::OpenCom(LPCTSTR portName, DWORD baudRate, BYTE parity, BYTE dataBit, BYTE stopBit)
{

	BOOL _bFlag = 0;
	this->m_PortName = portName;
	//创建串口句柄
	this->m_hCom = ::CreateFile(portName, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
	if (m_hCom == INVALID_HANDLE_VALUE) {
		return false;
	}
	//DCB设置串口参数   
	DCB _dcb;
	//置空_dcb
	memset(&_dcb, 0, sizeof(_dcb));
	//设置参数
	_dcb.BaudRate = baudRate;
	_dcb.ByteSize = dataBit;
	switch (parity)
	{
	case 0:
		_dcb.Parity = NOPARITY;//无
		break;
	case 1:
		_dcb.Parity = ODDPARITY;//奇
		break;
	case 2:
		_dcb.Parity = EVENPARITY;//偶
		break;
	case 3:
		_dcb.Parity = MARKPARITY;//标记校验
		break;
	default:
		break;
	}
	switch (stopBit)
	{

	case 1:
		_dcb.StopBits = ONESTOPBIT; //1位停止位
		break;
	case 2:
		_dcb.StopBits = TWOSTOPBITS; //2位停止位
		break;
	case 3:
		_dcb.StopBits = ONE5STOPBITS; //1.5位停止位
		break;
	default:
		break;
	}
	_bFlag = SetCommState(m_hCom, &_dcb);
	if (0 == _bFlag)
	{
		return false;
	}
	//设置输入和输出缓冲区大小(字节数)
	_bFlag = SetupComm(m_hCom, 1024, 1024);
	if (0 == _bFlag)
	{
		return false;
	}
	//设置超时时间
	COMMTIMEOUTS _timeOut;
	//置空
	memset(&_timeOut, 0, sizeof(_timeOut));
	_timeOut.ReadIntervalTimeout = 100;//单位：ms
	_timeOut.ReadTotalTimeoutConstant = 2000;
	_timeOut.ReadTotalTimeoutMultiplier = 500;
	_timeOut.WriteTotalTimeoutConstant = 2000;
	_timeOut.WriteTotalTimeoutMultiplier = 500;
	//_timeOut.ReadIntervalTimeout = MAXDWORD;//单位：ms
	//_timeOut.ReadTotalTimeoutConstant = 0;
	//_timeOut.ReadTotalTimeoutMultiplier = 0; 
	//_timeOut.WriteTotalTimeoutConstant = 2000;
	//_timeOut.WriteTotalTimeoutMultiplier = 50;
	_bFlag = SetCommTimeouts(m_hCom, &_timeOut);
	if (0 == _bFlag)
	{
		return false;
	}
	//清空读、写缓冲区域
	_bFlag = PurgeComm(m_hCom, PURGE_TXCLEAR | PURGE_RXCLEAR);//清空串口缓冲区
	if (0 == _bFlag)
	{
		return false;
	}
	return true;
}

bool CComm::CloseCom()
{
	m_bThreadAlive = false;
	return CloseHandle(m_hCom) ? true : false;
}

void CComm::SetComIndex(int nIndex)
{
	m_nPortIndex = nIndex;
}

void CComm::SetOwnerWindowPtr(CWnd * pWnd)
{
	m_pOwnerWnd = pWnd;
}

bool CComm::StartReceiveThread()
{
	UINT nThreadID;
	SerialPortProc.MenProc = &CComm::SerialPortThreadFunc;
	HANDLE hThread = (HANDLE)_beginthreadex(NULL, 0, SerialPortProc.ThreadProc, this, 0, &nThreadID);
	if (hThread)
	{
		m_bThreadAlive = true;
		return true;
	}
	else
	{
		gSystemLog.DisplayLogAndSave(L"串口连接失败", LV_ERROR);
		return false;
	}

}

bool CComm::Change1LightValue(int nChannel, int nLightValue)
{
	vector<byte> vCommand =
	{
		0xab,
		0xba,
		0x03,
		0x31,
		boost::numeric_cast<byte>(nChannel),
		boost::numeric_cast<byte>(nLightValue)
	};
	WritePort(vCommand);
	return true;
}

bool CComm::Change4LightValue(int nLightValue1, int nLightValue2, int nLightValue3, int nLightValue4)
{
	vector<byte> vCommand =
	{
		0xab,
		0xba,
		0x05,
		0x33,
		boost::numeric_cast<byte>(nLightValue1),
		boost::numeric_cast<byte>(nLightValue2),
		boost::numeric_cast<byte>(nLightValue3),
		boost::numeric_cast<byte>(nLightValue4)
	};
	WritePort(vCommand);
	return true;
}

bool CComm::Change1LightMode(int nChannel, int nLightMode)
{
	vector<byte> vCommand =
	{
		0xab,
		0xba,
		0x03,
		0x32,
		boost::numeric_cast<byte>(nChannel),
		boost::numeric_cast<byte>(nLightMode)
	};
	WritePort(vCommand);
	return true;
}

bool CComm::Change4LightMode(int nLightMode11, int nLightMode12, int nLightMode13, int nLightMode14)
{
	vector<byte> vCommand =
	{
		0xab,
		0xba,
		0x05,
		0x34,
		boost::numeric_cast<byte>(nLightMode11),
		boost::numeric_cast<byte>(nLightMode12),
		boost::numeric_cast<byte>(nLightMode13),
		boost::numeric_cast<byte>(nLightMode14)
	};
	WritePort(vCommand);
	return true;
}

bool CComm::GetLightCtrlParam(std::vector<int>& vParam)
{
	vector<byte> vCommand =
	{
		0xab,
		0xba,
		0x02,
		0x02
	};
	WritePort(vCommand);
	WaitForSingleObject(m_hRecvEvent, INFINITE);
	ResetEvent(m_hRecvEvent);
	string s = m_strRecvData;
	return true;
}

void CComm::Receive()
{
	while (m_bThreadAlive)
	{
		Sleep(1);
		if (gSystemMgr.m_nExitFlag != 0)
		{
			break;
		}

		Sleep(10);
		m_RXBuff = std::vector<byte>(m_nRxBuffSize, 0x00);
		BOOL _bFlags = 0;
		DWORD dword;
		DWORD dwErrorFlags;
		COMSTAT comStat;
		ClearCommError(m_hCom, &dwErrorFlags, &comStat);
		if (0 != comStat.cbInQue)
		{
			_bFlags = ReadFile(m_hCom, &m_RXBuff[0], m_nRxBuffSize, &dword, NULL);
			PurgeComm(m_hCom, PURGE_TXCLEAR | PURGE_RXCLEAR);//清空串口缓冲区
			if (0 == _bFlags)
			{
				continue;
			}
			std::vector<char> vTemp;
			for (int i = 0; i < m_nRxBuffSize; i++)
			{
				Sleep(1);
				vTemp.push_back(m_RXBuff[i]);
			}
			m_strRecvData.insert(m_strRecvData.begin(), vTemp.begin(), vTemp.end());
			//m_strRecvData = ByteToHexString(m_RXBuff, dword);   

			gSystemLog.DisplayLogAndSave(_utils::AnsiToUnicode(m_strRecvData), LV_EVENT);


			std::vector<char> vTemp2;
			for (int i = 10; i < 17; i++)
			{
				vTemp2.push_back(m_RXBuff[i]);
			}

			string                 strHeight;
			strHeight.insert(strHeight.begin(), vTemp2.begin(), vTemp2.end());
			CString cstrLog;
			cstrLog.Format(L"R:%s", strHeight);
			gSystemLog.DisplayLogAndSave(cstrLog.GetBuffer(), LV_EVENT);
		}
		SetEvent(m_hRecvEvent);
	}
}


unsigned int CComm::SerialPortThreadFunc()
{
	Receive();
	return 0;
}

std::string CComm::ByteToHexString(vector<unsigned char> vByteArr, size_t len)
{
	std::string hexstr("");
	if (vByteArr.empty())
	{
		return hexstr;
	}
	for (size_t i = 0; i < len; i++)
	{
		char cHex1;
		char cHex2;
		int nValue = vByteArr[i];
		int nV1 = nValue / 16;
		int nV2 = nValue % 16;
		if (nV1 >= 0 && nV1 <= 9)
		{
			cHex1 = (char)(48 + nV1);
		}
		else
		{
			cHex1 = (char)(55 + nV1);
		}
		if (nV2 >= 0 && nV2 <= 9)
		{
			cHex2 = (char)(48 + nV2);
		}
		else
		{
			cHex2 = (char)(55 + nV2);
		}
		hexstr = hexstr + cHex1 + cHex2;
	}
	return hexstr;
}


int CComm::WritePort(const std::string& cmd)
{
	if (cmd.empty())
	{
		return -1;
	}
	BOOL _bFlags = 0;
	DWORD nNum;
	PurgeComm(m_hCom, PURGE_TXABORT | PURGE_RXABORT | PURGE_TXCLEAR | PURGE_RXCLEAR);
	_bFlags = WriteFile(m_hCom, cmd.c_str(), (DWORD)cmd.length(), &nNum, NULL);
	if (0 == _bFlags)
	{
		return -1;
	}
	return nNum;
}

int CComm::WritePort(const std::vector<byte>& cmd)
{
	if (cmd.empty())
	{
		return -1;
	}
	std::string str;
	str.assign(cmd.begin(), cmd.end());
	BOOL _bFlags = 0;
	DWORD nNum;
	PurgeComm(m_hCom, PURGE_TXABORT | PURGE_RXABORT | PURGE_TXCLEAR | PURGE_RXCLEAR);
	_bFlags = WriteFile(m_hCom, str.c_str(), (DWORD)str.length(), &nNum, NULL);

	if (0 == _bFlags)
	{
		return -1;
	}
	return nNum;
}


