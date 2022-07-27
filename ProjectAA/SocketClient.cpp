#include "pch.h"
#include "SocketClient.h"
#include "TypeDef.h"
#include "SystemLog.h"
#include "SystemManager.h"
#include <stdio.h>

extern CSystemLog        gSystemLog;
extern CSystemManager    gSystemMgr;

CSocketClient::CSocketClient()
	: 
	m_sendBuffer(30),
	m_recvBuffer(30)
{
	
}

CSocketClient::~CSocketClient()
{
	CloseClient();
}

bool  CSocketClient::ClientConnectionServer(char* cIpAddRess, int nIpPort)
{
	if (NULL != cIpAddRess)
	{
		m_cIPAddress = cIpAddRess;
	}
	if (nIpPort > 0 && nIpPort < 65535)
	{
		m_nPort = nIpPort;
	}
	WSADATA wsaData;
	if (0 == WSAStartup(MAKEWORD(2, 2), &wsaData))//使用WinSock2
	{
		closesocket(m_spcSocket);
		m_spcSocket = ::socket(AF_INET, SOCK_STREAM, 0);
		if (INVALID_SOCKET == m_spcSocket)
		{
			return false;
		}
		m_spcAddr.sin_family = AF_INET;
		m_spcAddr.sin_port = ::htons((UINT)(nIpPort));
		m_spcAddr.sin_addr.S_un.S_addr = inet_addr(cIpAddRess);
	}
	int nRet = ::connect(m_spcSocket, (sockaddr*)&m_spcAddr, sizeof(SOCKADDR));
	if (nRet != 0)
	{
		CString strMsg = L"客户端";
		strMsg.Append(_utils::Utf82TChar(cIpAddRess));
		strMsg.AppendFormat(L",Port:%d", m_nPort);
		strMsg.Append(_utils::Utf82TChar("连接服务器失败!"));
		//gSystemLog.DisplayLogAndSave(strMsg.GetBuffer(), LV_ERROR);
		return false;

	}
	else
	{
		CString strMsg = L"客户端";
		strMsg.Append(_utils::Utf82TChar(cIpAddRess));
		strMsg.AppendFormat(L",Port:%d", m_nPort);
		strMsg.Append(_utils::Utf82TChar("连接服务器成功!"));
		gSystemLog.DisplayLogAndSave(strMsg.GetBuffer(), LV_EVENT);

	}
	m_bConnect = TRUE;
	StartSendMsgThread();
	StartRecvMsgThread();

	return true;

}

bool  CSocketClient::CloseClient()
{
	if (!m_bConnect)
	{
		return true;
	}
	if (m_bConnect)
	{
		closesocket(m_spcSocket);
		m_bConnect = false;
	}
	return true;
}


void CSocketClient::StartSendMsgThread()
{
	ProcSend.MemProc = &CSocketClient::SendMsgThread;
	UINT nThreadID;
	HANDLE hHandle = (HANDLE)_beginthreadex(NULL, 0, ProcSend.ThreadProc, (LPVOID)this, 0, &nThreadID);
	if (NULL == hHandle)
	{
		return;
	}
}

unsigned int __stdcall CSocketClient::SendMsgThread()
{
	while (m_bConnect == TRUE)
	{
		Sleep(1);
		if (m_sendBuffer.is_empty())
		{
			Sleep(100);
			continue;
		}
		wstring wstrCode;
		m_sendBuffer.pop_back(&wstrCode);
		char data_buf[1024] = "";
		strcpy_s(data_buf, _utils::Unicode2Ansi(wstrCode).c_str());
		int nRet = send(m_spcSocket, data_buf, static_cast<int>(strlen(data_buf)), 0);
		if (nRet < 0)
		{
			closesocket(m_spcSocket);
			m_bConnect = false;
			CString strMsg = L"客户端";
			strMsg.Append(_utils::Utf82TChar(m_cIPAddress));
			strMsg.AppendFormat(L",Port:%d", m_nPort);
			strMsg.Append(_utils::Utf82TChar("与服务器连接中断!"));
			gSystemLog.DisplayLogAndSave(strMsg.GetBuffer(), LV_ERROR);
			return 0;
		}
	}
	return 0;
}

void CSocketClient::StartRecvMsgThread()
{
	ProcRecv.MemProc = &CSocketClient::RecvMsgThread;
	UINT nThreadID;
	HANDLE hHandle = (HANDLE)_beginthreadex(NULL, 0, ProcRecv.ThreadProc, (LPVOID)this, 0, &nThreadID);
	if (NULL == hHandle)
	{
		return;
	}
}


unsigned int __stdcall CSocketClient::RecvMsgThread()
{
	while (m_bConnect == true)
	{
		Sleep(100);
		char     m_cRcvData[MAX_RECV_DATA];//获得的数据
		memset(m_cRcvData, 0x00, sizeof(char)*MAX_RECV_DATA);
		int nRet = recv(m_spcSocket, m_cRcvData, MAX_RECV_DATA, 0);
		if (nRet == -1 || nRet == 0)//获取数据失败
		{
			m_bConnect = false;
			CString strMsg = L"客户端";
			strMsg.Append(_utils::Utf82TChar(m_cIPAddress));
			strMsg.AppendFormat(L",Port:%d", m_nPort);
			strMsg.Append(_utils::Utf82TChar("与服务器断开连接!"));
			gSystemLog.DisplayLogAndSave(strMsg.GetBuffer(), LV_ERROR);
			continue;
		}
		wstring  wstrRecv = _utils::AnsiToUnicode(m_cRcvData);
		gSystemLog.DisplayLogAndSave(wstrRecv, LV_EVENT);
		gSystemLog.DisplayLogAndSave(L"Tcpip接收到信息:", LV_EVENT);
		std::vector<wstring> vResultItem = _utils::SplitString(wstrRecv, L"_");
		if (vResultItem.size() != 2)
		{
			gSystemLog.DisplayLogAndSave(L"Server 返回的数据有误", LV_ERROR);
			continue;
		}

	}
	return 0;
}
