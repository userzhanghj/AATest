#pragma once
#include "afxwin.h"
#include "TypeDef.h"
#include "afxcmn.h"
#include <string>
#include <vector>
#include <afxwin.h>
#include <atomic>

using namespace std;
//////////////////////////////////////////////////////////////////////////
/*
IO����ˣ���һֱ���߳�ɨ�裬�õ�һ������󣬾Ͱ�S01�޸�ֵ�������ط��������ֵ
IO����ˣ������check box֮�󣬾�ֱ�ӽ���Ӧ��IO�����Ȼ�󽫶�Ӧ��ֵ��ֵ��Y01�������ط�����ȡIO״̬��ʱ�򣬶�Y01
*/
//////////////////////////////////////////////////////////////////////////

class CIo
{
public:
	CIo();
	~CIo();

	std::atomic_int        m_nExitFlagIo = 0;

	void ShotDown();
	int DMC3800_GetAllInputIo();
	int DMC_SetAllOutputOff();
	void SetOutputIo(int nPort, long nValue);
	void GetOutputIoToY();

	void StartGetIoInputThread();
	unsigned int __stdcall GetIoInputThread();

	std::vector<HANDLE> m_vIoThread;

	union UI_Proc
	{
		unsigned(_stdcall * ThreadProc)(void*);
		unsigned(_stdcall CIo::*MemProc)();
	} ProcIoInput;
};

