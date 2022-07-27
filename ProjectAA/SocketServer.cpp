#include "pch.h"
#include "TypeDef.h"
#include "SocketServer.h"
#include "SystemLog.h"
#include "SystemManager.h"
#include <stdio.h>

extern CSystemLog        gSystemLog;
extern CSystemManager    gSystemMgr;

CSocketServer::CSocketServer()
	: m_sendBuffer(10)
{
}

CSocketServer::~CSocketServer()
{
	CloseSocketServer();
}

bool CSocketServer::OpenSocketServer(char* CSocketServerName, char* cIpAddRess,int nIpPort)
{
	if (NULL != cIpAddRess)
	{
		m_cIPAddress = cIpAddRess;
	}
	if (NULL != CSocketServerName)
	{
		m_CSocketServerName = CSocketServerName;
	}
	if (nIpPort > 0 && nIpPort < 65535)
	{
		m_nPort = nIpPort;
	}

	WSADATA wsaData;
	if (0 == WSAStartup(MAKEWORD(2, 2), &wsaData))//使用WinSock2
	{
		m_macSocket = ::socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

		memset(&m_spcAddr, 0, sizeof(m_spcAddr));
		m_spcAddr.sin_family = AF_INET;
		m_spcAddr.sin_port = ::htons((unsigned short)(m_nPort));
		m_spcAddr.sin_addr.S_un.S_addr = inet_addr(m_cIPAddress);
	}
	
	int nRet = ::bind(m_macSocket, (sockaddr*)&m_spcAddr, sizeof(SOCKADDR));
	if (nRet < 0)
	{
		CString strMsg = L"";
		strMsg.Append(_utils::Utf82TChar(m_CSocketServerName));
		strMsg.Append(_utils::Utf82TChar(m_cIPAddress));
		strMsg.AppendFormat(L",Port:%d",m_nPort);
		strMsg.Append(_utils::Utf82TChar("创建失败!"));
		gSystemLog.DisplayLogAndSave(strMsg.GetBuffer(), LV_ERROR);

	}
	else
	{
		CString strMsg = L"";
		strMsg.Append(_utils::Utf82TChar(m_CSocketServerName));
		strMsg.Append(_utils::Utf82TChar(m_cIPAddress));
		strMsg.AppendFormat(L",Port:%d", m_nPort);
		strMsg.Append(_utils::Utf82TChar("创建成功!"));
		gSystemLog.DisplayLogAndSave(strMsg.GetBuffer(), LV_EVENT);

	}

	return true;
}

bool  CSocketServer::CloseSocketServer()
{
	for (int i=0;i<(int)m_vBConnect.size();i++)
	{
		if (m_vBConnect[i])
		{
			closesocket(m_macSocket);

			m_vBConnect[i] = false;
		}
	}
	return true;
}

void CSocketServer::StartSendMsgThread()
{
	SendData.MemProc = &CSocketServer::SendMsgThread;
	UINT nThreadID;
	HANDLE hHandle = (HANDLE)_beginthreadex(NULL, 0, SendData.ThreadProc, (LPVOID)this, 0, &nThreadID);
	if (NULL == hHandle)
	{
		return;
	}
}

unsigned int CSocketServer::SendMsgThread()
{
	size_t nNum = m_vClient.size();
	while (m_vBConnect[nNum - 1] == TRUE)
	{
		if (m_sendBuffer.is_empty())
		{
			Sleep(100);
			continue;
		}
		wstring wstrMsg;
		m_sendBuffer.pop_back(&wstrMsg);
		char data_buf[MAX_RECV_DATA] = "";
		strcpy_s(data_buf, _utils::Unicode2Ansi(wstrMsg).c_str());

		int nRet = send(m_vClient[nNum - 1], data_buf, static_cast<int>(strlen(data_buf)), 0);
		if (nRet < 0)
		{
			closesocket(m_vClient[nNum - 1]);
			m_vBConnect[nNum - 1] = false;
			CString strMsg = L"PC与";
			strMsg.Append(_utils::Utf82TChar(m_CSocketServerName));
			strMsg.Append(_utils::Utf82TChar("断开连接!"));
			gSystemLog.DisplayLogAndSave(strMsg.GetBuffer(), LV_ERROR);
			return false;
		}
		
	}
	return 0;
}

void CSocketServer::StartRecvMsgThread()
{
	RecvData.MemProc = &CSocketServer::RecvMsgThread;
	UINT nThreadID;
	HANDLE hHandle = (HANDLE)_beginthreadex(NULL, 0, RecvData.ThreadProc, (LPVOID)this, 0, &nThreadID);
	if (NULL == hHandle)
	{
		return;
	}
}

unsigned int CSocketServer::RecvMsgThread()
{
	size_t nNum = m_vClient.size();
	SOCKET tempSocket = NULL;
	if (0 != nNum)
	{
		tempSocket = m_vClient[nNum - 1];
	}
	
	while (m_vBConnect[nNum - 1] == TRUE)
	{
		Sleep(100);
		memset(m_cRcvData, 0x00, sizeof(char)*MAX_RECV_DATA);
		int nRet = recv(tempSocket, m_cRcvData, MAX_RECV_DATA, 0);
		if (nRet == -1 || nRet == 0)//获取数据失败
		{
			m_vBConnect[nNum - 1] = false;
			gSystemLog.DisplayLogAndSave(L"断开连接", LV_ERROR);
			m_bConnect = 0;
			continue;
		}
		wstring  wstrRecv = _utils::AnsiToUnicode(m_cRcvData);
		CString sLog = _utils::Unicode2TChar(wstrRecv);
		if (L""!= sLog)
		{
			
			BSTR bstr = sLog.AllocSysString();
			::PostMessage(gSystemMgr.m_ptrMainUI->m_hWnd, WM_SEND_SOCKET_SERVER_MSG_TO_MAIN_UI, (WPARAM)bstr, NULL);
		}
	}
	return 0;
}

void CSocketServer::Accept()
{
	int nRet = listen(m_macSocket, MAX_RECV_DATA);
	if (nRet < 0)
	{
		//gSystemLog.DisplayLogAndSave(L"Error in listen", LV_ERROR);
		return;
	}

	int nSize = sizeof(m_spcAddr);
	SOCKADDR clientAddr;
	SOCKET client;
	client = accept(m_macSocket, (sockaddr*)&clientAddr, &nSize);
	if (client == SOCKET_ERROR)
	{
		gSystemLog.DisplayLogAndSave(L"连接失败", LV_ERROR);
	}
	else
	{
		m_vClient.push_back(client);
		m_vBConnect.push_back(TRUE);

		//当前的client是否还存在
		StartSendMsgThread();
		StartRecvMsgThread();

		gSystemLog.DisplayLogAndSave(L"连接到服务器成功", LV_EVENT);
		m_bConnect = 1;
	}
}
