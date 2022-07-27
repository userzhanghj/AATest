#include "pch.h"
#include "IO.h"
#include "ConfigFileManager.h"
#include "SystemManager.h"
#include "SystemLog.h"

extern CSystemLog        gSystemLog;
extern CSystemManager    gSystemMgr;
extern CConfigFileManager gConfigMgr;

CIo::CIo()
{
}

CIo::~CIo()
{
}

void CIo::ShotDown()
{
	m_nExitFlagIo = 1;

	auto sz = m_vIoThread.size();
	if (sz > 0)
	{
		::WaitForMultipleObjects((DWORD)sz, &m_vIoThread[0], TRUE, INFINITE);
	}
	m_vIoThread.clear();
}

int CIo::DMC3800_GetAllInputIo()
{
	int nErr = 0;
	gSystemMgr.m_wDIVal[0] = dmc_read_inport(gSystemMgr.m_nCard, 0);
	nmc_read_inport(gSystemMgr.m_nCard, 1, 0, &gSystemMgr.m_wDIVal[1]);
	return 0;
}

int CIo::DMC_SetAllOutputOff()
{
	CString cstrLog;
	int nErr = 0;
	gSystemMgr.m_wDOVal[0] = 0xffff;
	gSystemMgr.m_wDOVal[1] = 0xffff;
	gSystemLog.DisplayLogAndSave(L"DMC_SetAllOutputOff Success!", LV_EVENT);
	return 1;
}

void CIo::StartGetIoInputThread()
{
	ProcIoInput.MemProc = &CIo::GetIoInputThread;
	UINT nThreadId;
	HANDLE hThread = (HANDLE)_beginthreadex(NULL, 0, ProcIoInput.ThreadProc, (LPVOID)this, 0, &nThreadId);
	if (hThread == NULL)
	{
		return;
	}
	m_vIoThread.push_back(hThread);
}

unsigned int __stdcall CIo::GetIoInputThread()
{
	while (0 == m_nExitFlagIo)
	{
		Sleep(10);
		DMC3800_GetAllInputIo();

		gSystemMgr.S00 = (((gSystemMgr.m_wDIVal[0] & 0x0001) == 0x00) ? ON : OFF);
		gSystemMgr.S01 = (((gSystemMgr.m_wDIVal[0] & 0x0002) == 0x00) ? ON : OFF);
		gSystemMgr.S02 = (((gSystemMgr.m_wDIVal[0] & 0x0004) == 0x00) ? ON : OFF);
		gSystemMgr.S03 = (((gSystemMgr.m_wDIVal[0] & 0x0008) == 0x00) ? ON : OFF);
		gSystemMgr.S04 = (((gSystemMgr.m_wDIVal[0] & 0x0010) == 0x00) ? ON : OFF);
		gSystemMgr.S05 = (((gSystemMgr.m_wDIVal[0] & 0x0020) == 0x00) ? ON : OFF);
		gSystemMgr.S06 = (((gSystemMgr.m_wDIVal[0] & 0x0040) == 0x00) ? ON : OFF);
		gSystemMgr.S07 = (((gSystemMgr.m_wDIVal[0] & 0x0080) == 0x00) ? ON : OFF);
		gSystemMgr.S08 = (((gSystemMgr.m_wDIVal[0] & 0x0100) == 0x00) ? ON : OFF);
		gSystemMgr.S09 = (((gSystemMgr.m_wDIVal[0] & 0x0200) == 0x00) ? ON : OFF);
		gSystemMgr.S10 = (((gSystemMgr.m_wDIVal[0] & 0x0400) == 0x00) ? ON : OFF);
		gSystemMgr.S11 = (((gSystemMgr.m_wDIVal[0] & 0x0800) == 0x00) ? ON : OFF);
		gSystemMgr.S12 = (((gSystemMgr.m_wDIVal[0] & 0x1000) == 0x00) ? ON : OFF);
		gSystemMgr.S13 = (((gSystemMgr.m_wDIVal[0] & 0x2000) == 0x00) ? ON : OFF);
		gSystemMgr.S14 = (((gSystemMgr.m_wDIVal[0] & 0x4000) == 0x00) ? ON : OFF);
		gSystemMgr.S15 = (((gSystemMgr.m_wDIVal[0] & 0x8000) == 0x00) ? ON : OFF);

		gSystemMgr.S16 = (((gSystemMgr.m_wDIVal[1] & 0x0001) == 0x00) ? ON : OFF);
		gSystemMgr.S17 = (((gSystemMgr.m_wDIVal[1] & 0x0002) == 0x00) ? ON : OFF);
		gSystemMgr.S18 = (((gSystemMgr.m_wDIVal[1] & 0x0004) == 0x00) ? ON : OFF);
		gSystemMgr.S19 = (((gSystemMgr.m_wDIVal[1] & 0x0008) == 0x00) ? ON : OFF);
		gSystemMgr.S20 = (((gSystemMgr.m_wDIVal[1] & 0x0010) == 0x00) ? ON : OFF);
		gSystemMgr.S21 = (((gSystemMgr.m_wDIVal[1] & 0x0020) == 0x00) ? ON : OFF);
		gSystemMgr.S22 = (((gSystemMgr.m_wDIVal[1] & 0x0040) == 0x00) ? ON : OFF);
		gSystemMgr.S23 = (((gSystemMgr.m_wDIVal[1] & 0x0080) == 0x00) ? ON : OFF);
		gSystemMgr.S24 = (((gSystemMgr.m_wDIVal[1] & 0x0100) == 0x00) ? ON : OFF);
		gSystemMgr.S25 = (((gSystemMgr.m_wDIVal[1] & 0x0200) == 0x00) ? ON : OFF);
		gSystemMgr.S26 = (((gSystemMgr.m_wDIVal[1] & 0x0400) == 0x00) ? ON : OFF);
		gSystemMgr.S27 = (((gSystemMgr.m_wDIVal[1] & 0x0800) == 0x00) ? ON : OFF);
		gSystemMgr.S28 = (((gSystemMgr.m_wDIVal[1] & 0x1000) == 0x00) ? ON : OFF);
		gSystemMgr.S29 = (((gSystemMgr.m_wDIVal[1] & 0x2000) == 0x00) ? ON : OFF);
		gSystemMgr.S30 = (((gSystemMgr.m_wDIVal[1] & 0x4000) == 0x00) ? ON : OFF);
		gSystemMgr.S31 = (((gSystemMgr.m_wDIVal[1] & 0x8000) == 0x00) ? ON : OFF);	
	}
	return 0;
}


 void CIo::SetOutputIo(int nPort, long nValue)
 {
 	int nCard = nPort / 16;
 	if (nValue == OFF)
 	{
 		switch (nCard)
 		{
		case 0:	dmc_write_outbit(gSystemMgr.m_nCard, (nPort % 16), ON); break;

		case 1:	nmc_write_outbit(gSystemMgr.m_nCard, 1, (nPort % 16), ON); break;
 		}
 	}
 	else if (nValue == ON)
 	{
		switch (nCard)
		{
		case 0:	dmc_write_outbit(gSystemMgr.m_nCard, (nPort % 16), OFF); break;

		case 1:	nmc_write_outbit(gSystemMgr.m_nCard, 1, (nPort % 16), OFF); break;
		}
 	}
	gSystemMgr.m_wDOVal[0] = dmc_read_outport(gSystemMgr.m_nCard, 0);
	nmc_read_outport(gSystemMgr.m_nCard, 1, 0, &gSystemMgr.m_wDOVal[1]);
 	GetOutputIoToY();
 }

void CIo::GetOutputIoToY()
{
	gSystemMgr.Y00 = (((gSystemMgr.m_wDOVal[0] & 0x0001) == 0x0001) ? OFF : ON);
	gSystemMgr.Y01 = (((gSystemMgr.m_wDOVal[0] & 0x0002) == 0x0002) ? OFF : ON);
	gSystemMgr.Y02 = (((gSystemMgr.m_wDOVal[0] & 0x0004) == 0x0004) ? OFF : ON);
	gSystemMgr.Y03 = (((gSystemMgr.m_wDOVal[0] & 0x0008) == 0x0008) ? OFF : ON);
	gSystemMgr.Y04 = (((gSystemMgr.m_wDOVal[0] & 0x0010) == 0x0010) ? OFF : ON);
	gSystemMgr.Y05 = (((gSystemMgr.m_wDOVal[0] & 0x0020) == 0x0020) ? OFF : ON);
	gSystemMgr.Y06 = (((gSystemMgr.m_wDOVal[0] & 0x0040) == 0x0040) ? OFF : ON);
	gSystemMgr.Y07 = (((gSystemMgr.m_wDOVal[0] & 0x0080) == 0x0080) ? OFF : ON);
	gSystemMgr.Y08 = (((gSystemMgr.m_wDOVal[0] & 0x0100) == 0x0100) ? OFF : ON);
	gSystemMgr.Y09 = (((gSystemMgr.m_wDOVal[0] & 0x0200) == 0x0200) ? OFF : ON);
	gSystemMgr.Y10 = (((gSystemMgr.m_wDOVal[0] & 0x0400) == 0x0400) ? OFF : ON);
	gSystemMgr.Y11 = (((gSystemMgr.m_wDOVal[0] & 0x0800) == 0x0800) ? OFF : ON);
	gSystemMgr.Y12 = (((gSystemMgr.m_wDOVal[0] & 0x1000) == 0x1000) ? OFF : ON);
	gSystemMgr.Y13 = (((gSystemMgr.m_wDOVal[0] & 0x2000) == 0x2000) ? OFF : ON);
	gSystemMgr.Y14 = (((gSystemMgr.m_wDOVal[0] & 0x4000) == 0x4000) ? OFF : ON);
	gSystemMgr.Y15 = (((gSystemMgr.m_wDOVal[0] & 0x8000) == 0x8000) ? OFF : ON);
																	   		 
	gSystemMgr.Y16 = (((gSystemMgr.m_wDOVal[1] & 0x0001) == 0x0001) ? OFF : ON);
	gSystemMgr.Y17 = (((gSystemMgr.m_wDOVal[1] & 0x0002) == 0x0002) ? OFF : ON);
	gSystemMgr.Y18 = (((gSystemMgr.m_wDOVal[1] & 0x0004) == 0x0004) ? OFF : ON);
	gSystemMgr.Y19 = (((gSystemMgr.m_wDOVal[1] & 0x0008) == 0x0008) ? OFF : ON);
	gSystemMgr.Y20 = (((gSystemMgr.m_wDOVal[1] & 0x0010) == 0x0010) ? OFF : ON);
	gSystemMgr.Y21 = (((gSystemMgr.m_wDOVal[1] & 0x0020) == 0x0020) ? OFF : ON);
	gSystemMgr.Y22 = (((gSystemMgr.m_wDOVal[1] & 0x0040) == 0x0040) ? OFF : ON);
	gSystemMgr.Y23 = (((gSystemMgr.m_wDOVal[1] & 0x0080) == 0x0080) ? OFF : ON);
	gSystemMgr.Y24 = (((gSystemMgr.m_wDOVal[1] & 0x0100) == 0x0100) ? OFF : ON);
	gSystemMgr.Y25 = (((gSystemMgr.m_wDOVal[1] & 0x0200) == 0x0200) ? OFF : ON);
	gSystemMgr.Y26 = (((gSystemMgr.m_wDOVal[1] & 0x0400) == 0x0400) ? OFF : ON);
	gSystemMgr.Y27 = (((gSystemMgr.m_wDOVal[1] & 0x0800) == 0x0800) ? OFF : ON);
	gSystemMgr.Y28 = (((gSystemMgr.m_wDOVal[1] & 0x1000) == 0x1000) ? OFF : ON);
	gSystemMgr.Y29 = (((gSystemMgr.m_wDOVal[1] & 0x2000) == 0x2000) ? OFF : ON);
	gSystemMgr.Y30 = (((gSystemMgr.m_wDOVal[1] & 0x4000) == 0x4000) ? OFF : ON);
	gSystemMgr.Y31 = (((gSystemMgr.m_wDOVal[1] & 0x8000) == 0x8000) ? OFF : ON);

	return;
}