#pragma once
#include <string>
#include <vector>
#include <afxsock.h>
#include "TypeDef.h"
#include "bounded_buffer.h"
using namespace std;

class CSocketClient
{
public:
	CSocketClient();
	~CSocketClient();
	bool ClientConnectionServer(char* cIpAddRess, int nIpPort);
	bool CloseClient();
	void StartRecvMsgThread();
	unsigned int __stdcall RecvMsgThread();
	void StartSendMsgThread();
	unsigned int __stdcall SendMsgThread();
public:

	bool     m_bConnect = false;
	SOCKET   m_spcSocket;
	sockaddr_in m_spcAddr;
	char*    m_cIPAddress;
	int m_nPort = 0;
	bounded_buffer<wstring>				    m_sendBuffer;
	bounded_buffer<wstring>				    m_recvBuffer;


	union UNION__RESULT_DATA
	{
		unsigned(__stdcall*ThreadProc)(void*);
		unsigned(__stdcall CSocketClient::*MemProc)();
	} ProcRecv,ProcSend;
};