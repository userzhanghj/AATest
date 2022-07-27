#pragma once
#include <string>
#include <vector>
#include <afxwin.h>
#include "TypeDef.h"
using namespace std;
//#define WM_COMM_RECEIVE_MSG   WM_USER+1
class CComm
{
public:
	CComm();
	bool   OpenCom(LPCTSTR portName, DWORD baudRate, BYTE parity, BYTE dataBit, BYTE stopBit);
	bool   CloseCom();
	void   SetComIndex(int nIndex);
	int    WritePort(const std::string& cmd);
	int    WritePort(const std::vector<byte>& cmd);
	void   SetOwnerWindowPtr(CWnd* pWnd);
	bool   StartReceiveThread();
	bool   Change1LightValue(int nChannel, int nLightValue);
	bool   Change4LightValue(int nLightValue1, int nLightValue2, int nLightValue3, int nLightValue4);
	bool   Change1LightMode(int nChannel, int nLightMode);
	bool   Change4LightMode(int nLightMode11, int nLightMode12, int nLightMode13, int nLightMode14);
	bool   GetLightCtrlParam(std::vector<int>&vParam);
private:
	void Receive();
	unsigned int __stdcall SerialPortThreadFunc();
	std::string ByteToHexString(vector<unsigned char> byteArr, size_t len);
private:
	HANDLE                 m_hCom;
	HANDLE                 m_hRecvEvent = NULL;
	int                    m_nRxBuffSize;
	std::vector<byte>      m_RXBuff;
	CWnd*                  m_pOwnerWnd;
	bool                   m_bThreadAlive;
	wstring                m_PortName;
	string                 m_strRecvData;
	int m_nPortIndex = 0;
	union _SerialPortProc
	{
		unsigned(_stdcall * ThreadProc)(void*);
		unsigned(_stdcall CComm::*MenProc)();
	}SerialPortProc;
};

