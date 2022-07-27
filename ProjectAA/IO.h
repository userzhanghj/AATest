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
IO输入端，就一直开线程扫描，拿到一个结果后，就把S01修改值，其他地方都拿这个值
IO输出端，点击了check box之后，就直接将对应的IO输出，然后将对应的值赋值给Y01，其他地方都读取IO状态的时候，都Y01
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

