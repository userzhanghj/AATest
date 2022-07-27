#pragma once
#include"Typedef.h"
#include <winsock2.h>
#include "bounded_buffer.h"
#include <stdio.h>
#pragma comment(lib,"ws2_32")
using namespace std;
const int MAX_RECV_DATA = 1024;
class CSocketServer
{
public:
	CSocketServer();
	~CSocketServer();
	bool OpenSocketServer(char* CSocketServerName, char* cIpAddRess, int nIpPort);
	bool CloseSocketServer();
	void          StartSendMsgThread();
	unsigned int __stdcall SendMsgThread();
	void          StartRecvMsgThread();
	unsigned int __stdcall RecvMsgThread();
	void Accept();
	
public:
	bounded_buffer<wstring>				    m_sendBuffer;
	bool	 m_bConnect = false;
	int      m_nPort;
	char*    m_cIPAddress;
	char*	 m_CSocketServerName;
	SOCKET   m_macSocket;
	std::vector < BOOL>     m_vBConnect;
	std::vector<SOCKET> m_vClient;
	sockaddr_in m_spcAddr;
	char     m_cRcvData[MAX_RECV_DATA];//获得的数据
	union UNION_SPECT_RECVDATA
	{
		unsigned(__stdcall*ThreadProc)(void*);
		unsigned(__stdcall CSocketServer::*MemProc)();
	} SendData, RecvData;
};

