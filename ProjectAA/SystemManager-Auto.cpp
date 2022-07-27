#include "pch.h"
#include "SystemManager.h"
#include "ConfigFileManager.h"
#include "SystemLog.h"
#include "ProjectAADlg.h"

extern CConfigFileManager gConfigMgr;
extern CSystemLog     gSystemLog;


//AA
void CSystemManager::StartAutoAAThread()
{
	ProcAutoAA.MemProc = &CSystemManager::AutoAAThread;
	UINT nThreadId;
	HANDLE hThread = (HANDLE)_beginthreadex(NULL, 0, ProcAutoAA.ThreadProc, (LPVOID)this, 0, &nThreadId);

	ProcAutoRight.MemProc = &CSystemManager::AutoRightThread;
	UINT nThreadId2;
	HANDLE hThread2 = (HANDLE)_beginthreadex(NULL, 0, ProcAutoRight.ThreadProc, (LPVOID)this, 0, &nThreadId2);

	if (hThread == NULL)
	{
		return;
	}
	//m_vWorkerThread.push_back(hThread);
}

unsigned int __stdcall CSystemManager::AutoAAThread()
{
	int AAStep = 0;
	int timeout = 0;
	int result = 0;
	//GetLocalTime(&stAA[]);
	CString time;
	CString cstr;
	int Cnt_S22 = 0;
	int NGNum = 0;
	while (0 == m_nExitFlag)
	{
		Sleep(10);
		time.Format(L"%d", AAStep); SetDlgItemText(m_ptrMainUI->GetSafeHwnd(), IDC_STATIC_88, time.GetBuffer());

		if (S22 && m_nAAErrorCode > 0)
		{//��λ��ť�ź�
			m_bAutoAAFlag = 0;
			m_nAAErrorCode = 0;
			NGNum = 0;
			//AAStep = 0;
			continue;
		}
		if (S22 && m_bAutoAAFlag == 0)
		{//��λ��ť�ź�	//����һ�룬����Ӳ����λ
			if (Cnt_S22 < 100)
			{
				Cnt_S22++;
				continue;
			}
			NGNum = 0;
			Cnt_S22 = 0;
			m_bAutoAAFlag = 0;
			m_nAAErrorCode = 0;
			AAStep = 0;
			m_cIo.SetOutputIo(7, OFF);
			m_cIo.SetOutputIo(8, ON);
			Sleep(1000);
			m_cIo.SetOutputIo(5, OFF);
			m_cIo.SetOutputIo(6, ON);
			m_cIo.SetOutputIo(9, OFF);
			m_cIo.SetOutputIo(10, ON);

			m_cIo.SetOutputIo(3, OFF);
			m_cIo.SetOutputIo(4, OFF);
			if (m_bHomeFlag) {
				result = PickLens();
				if (!result)
				{
					gSystemLog.DisplayLogAndSave(L"AA��צ�ƶ�����-��ԭ!", LV_ERROR);
					m_nAAErrorCode = ERROR_PICK_ERROR;
					break;
				}
			}

			continue;
		}
		else
			Cnt_S22 = 0;

		if (m_nAAErrorCode != 0)
		{
			m_bAutoAAFlag = 0;
			continue;
		}

		if (S21) {
			m_nAAErrorCode = ERROR_EMERGENCY;
			continue;
		}
		if (S23) {
			m_nAAErrorCode = ERROR_EMERGENCY_2;
			continue;
		}

		if (!m_bAutoAAFlag)
		{
			continue;
		}

		if (!m_bHomeFlag)
		{
			m_bAutoAAFlag = 0;
			m_nAAErrorCode = ERROR_NOT_HOMED;
			continue;
		}

		if (UseMirrorFlag && !S26) {
			m_bAutoAAFlag = 0;
			m_nAAErrorCode = ERROR_NO_MIRROR;
			continue;
		}

		switch (AAStep) {
		case 0:
			SetDlgItemTextW(m_ptrMainUI->GetSafeHwnd(), IDC_STATIC_20, L"ǰ�赲�ȴ�����");
			if (S04) {
				m_nAAErrorCode = ERROR_CAMERA_IN;
				break;
			}
			if (S26/*S03*/) {
				Sleep(500);
				if(S26)
					AAStep = 1;
			}
			break;
		case 1:
			m_cIo.SetOutputIo(3, ON);
			Sleep(300);
			m_cIo.SetOutputIo(3, OFF);
			AAStep = 2;
			break;
		case 2:
			SetDlgItemTextW(m_ptrMainUI->GetSafeHwnd(), IDC_STATIC_20, L"�ȴ���������AAλ");
			timeout = 1000;
			while (true)
			{
				Sleep(10);
				if (S04 && m_nButtonDone == 1)
				{
					AAStep = 10;
					break;
				}
				timeout--;
				if (timeout < 0)
				{
					gSystemLog.DisplayLogAndSave(L"S04δ��λ!", LV_ERROR);
					m_nAAErrorCode = ERROR_S02_OFF;
					break;
				}
			}
			break;
		case 10:
			gSystemLog.DisplayLogAndSave(L"AAվ��ʼ����!", LV_EVENT);
			//SetDlgItemTextW(m_ptrMainUI->GetSafeHwnd(), IDC_STATIC_20, L"Testing");
			SetDlgItemTextW(m_ptrMainUI->GetSafeHwnd(), IDC_STATIC_20, L"AA:��ʼ��������");

			SetDlgItemTextW(m_ptrMainUI->GetSafeHwnd(), IDC_STATIC_22, L"Test");
			SetDlgItemTextW(m_ptrMainUI->GetSafeHwnd(), IDC_STATIC_25, L"...");
			SetDlgItemTextW(m_ptrMainUI->GetSafeHwnd(), IDC_STATIC_28, L"...");
			SetDlgItemTextW(m_ptrMainUI->GetSafeHwnd(), IDC_STATIC_31, L"...");
			SetDlgItemTextW(m_ptrMainUI->GetSafeHwnd(), IDC_STATIC_34, L"...");
			SetDlgItemTextW(m_ptrMainUI->GetSafeHwnd(), IDC_STATIC_37, L"...");
			SetDlgItemTextW(m_ptrMainUI->GetSafeHwnd(), IDC_STATIC_40, L"...");

			m_cIo.SetOutputIo(7, OFF);
			m_cIo.SetOutputIo(8, ON);
			Sleep(800);
			if(!S04)
			{
				AAStep = 2;
				break;
			}
			m_cIo.SetOutputIo(5, ON);
			m_cIo.SetOutputIo(6, OFF);
			//
			timeout = 200;
			while (true)
			{
				Sleep(10);
				if (S05)
				{
					//AAStep = 11;
					break;
				}
				timeout--;
				if (timeout < 0)
				{
					gSystemLog.DisplayLogAndSave(L"���̶���δ��λ!", LV_ERROR);
					m_nAAErrorCode = ERROR_S05_ERROR;
					//AAStep = 11;
					break;
				}
			}
			//Sleep(600);
			Sleep(200);
			m_cIo.SetOutputIo(7, ON);
			m_cIo.SetOutputIo(8, OFF);
			//Sleep(200);
			timeout = 100;
			while (true)
			{
				Sleep(10);
				if (S07 && S05)
				{
					AAStep = 11;
					break;
				}
				timeout--;
				if (timeout < 0)
				{
					gSystemLog.DisplayLogAndSave(L"�����ϵ�δ��λ!", LV_ERROR);
					//m_nAAErrorCode = ERROR_S02_OFF;
					AAStep = 11;
					break;
				}
			}
			break;
		case 11:
			PowerDiff = m_fPowerCurrentVal[0];
			gSystemLog.DisplayLogAndSave(L"AAվ��ʼ��ȡrfid", LV_EVENT);
			if (!m_nPassRfidFlag) {
				if (Com2ConnectFlag == 0)
				{
					gSystemLog.DisplayLogAndSave(L"40-1 rfid���Ӵ���", LV_ERROR);
					m_nAAErrorCode = ERROR_COM_2;
					break;
				}
				memset(output2, 0, sizeof(output2));
				m_cRfidComm2.send_data_feedback((BYTE*)Read_Rfid, sizeof(Read_Rfid), (BYTE*)output2, sizeof(output2));
				//Char2Num((BYTE*)output, outInt, sizeof(output));
				USES_CONVERSION;
				cstr.Format(L"30-[%d]%s", strlen(output2), A2T(output2));
				gSystemLog.DisplayLogAndSave(cstr.GetBuffer(), LV_EVENT);

				m_cRfidAA.m_nId = output2[4];
				cstr.Format(L"30-����ID[%d]", m_cRfidAA.m_nId);
				gSystemLog.DisplayLogAndSave(cstr.GetBuffer(), LV_EVENT);

				m_cRfidAA.m_nNextStation = output2[6];
				cstr.Format(L"30-Ŀ�깤λ[%d]", m_cRfidAA.m_nNextStation);
				gSystemLog.DisplayLogAndSave(cstr.GetBuffer(), LV_EVENT);

				m_cRfidAA.m_bCameraIn = output2[8];
				cstr.Format(L"30-��Ʒ����[%d]", m_cRfidAA.m_bCameraIn);
				gSystemLog.DisplayLogAndSave(cstr.GetBuffer(), LV_EVENT);

				m_cRfidAA.m_bCameraStatus = output2[10];
				cstr.Format(L"30-��Ʒ״̬[%d]", m_cRfidAA.m_bCameraStatus);
				gSystemLog.DisplayLogAndSave(cstr.GetBuffer(), LV_EVENT);

				m_cRfidAA.m_nNGStation = output2[12];
				cstr.Format(L"30-NG��λ[%d]", m_cRfidAA.m_nNGStation);
				gSystemLog.DisplayLogAndSave(cstr.GetBuffer(), LV_EVENT);

				memset(output2, 0, sizeof(output2));
				m_cRfidComm2.send_data_feedback((BYTE*)Read_SN, sizeof(Read_SN), (BYTE*)output2, sizeof(output2));
				for (int i = 0; i < 50; i++) {
					SN[i] = output2[i + 3];
				}
				cstr.Format(L"����[%s]", A2T(SN));
				gSystemLog.DisplayLogAndSave(cstr.GetBuffer(), LV_EVENT);

				if (m_cRfidAA.m_nNextStation != 30 || m_cRfidAA.m_bCameraIn != 1 || m_cRfidAA.m_bCameraStatus != 1) {
					AAStep = 70;
					SetDlgItemTextW(m_ptrMainUI->GetSafeHwnd(), IDC_STATIC_20, L"Fail");
					SetDlgItemTextW(m_ptrMainUI->GetSafeHwnd(), IDC_STATIC_22, L"NG");
					SaveMes(0, 0, 0);
					break;
				}

			}

			SetDlgItemTextW(m_ptrMainUI->GetSafeHwnd(), IDC_STATIC_22, L"OK");
			AAStep = 20;
			break;

		case 20:
			SetDlgItemTextW(m_ptrMainUI->GetSafeHwnd(), IDC_STATIC_20, L"AA:��ʼ��ͼ+�᾵ͷ");
			SetDlgItemTextW(m_ptrMainUI->GetSafeHwnd(), IDC_STATIC_25, L"Test");
			//��ʼ��ͼ
			//m_bStopCapture = 0;
			SendMessage(m_ptrMainUI->GetSafeHwnd(), WM_COMMAND, IDC_BUTTON_START, 0);
			TiltX = m_dSpecAAAngle + 1;
			TiltY = m_dSpecAAAngle + 1;
			//��ȡ��ͷ��AA��ʼ
			//Sleep(100);
			gSystemLog.DisplayLogAndSave(L"AAվ��ʼ�о�ͷ!", LV_EVENT);
			Sleep(100);
			//SetDlgItemTextW(m_ptrMainUI->GetSafeHwnd(), IDC_STATIC_25, L"Test");

			m_cIo.SetOutputIo(9, ON);
			m_cIo.SetOutputIo(10, OFF);
			Sleep(50);
			timeout = 60;
			while (true)
			{
				Sleep(10);
				if (S09)
				{
					AAStep = 21;
					Sleep(50);
					break;
				}
				timeout--;
				if (timeout < 0)
				{
					gSystemLog.DisplayLogAndSave(L"AA��צ���׹���λδ��λ!", LV_ERROR);
					//m_nAAErrorCode = ERROR_S16_ERROR;
					AAStep = 21;
					SetDlgItemTextW(m_ptrMainUI->GetSafeHwnd(), IDC_STATIC_20, L"Fail");
					SetDlgItemTextW(m_ptrMainUI->GetSafeHwnd(), IDC_STATIC_25, L"NG");
					break;
				}
			}
			break;
		case 21:
			Sleep(200);
			result = LoadLens();
			if (!result)
			{
				gSystemLog.DisplayLogAndSave(L"AA��צ�ƶ����� - 1!", LV_ERROR);
				m_nAAErrorCode = ERROR_LOAD_ERROR;
				SetDlgItemTextW(m_ptrMainUI->GetSafeHwnd(), IDC_STATIC_20, L"Fail");
				SetDlgItemTextW(m_ptrMainUI->GetSafeHwnd(), IDC_STATIC_25, L"NG");
				break;
			}
			AAStep = 22;
			SetDlgItemTextW(m_ptrMainUI->GetSafeHwnd(), IDC_STATIC_25, L"OK");
			break;
		case 22://�ȴ���ͼ���
			SetDlgItemTextW(m_ptrMainUI->GetSafeHwnd(), IDC_STATIC_28, L"Test");
			timeout = m_nCaptureWaitTime * 100;
			while (/*m_bStartCapture == 0 && */timeout >= 0) {
				if (m_bStartCapture == 1 && m_fPowerCurrentVal[0] >= m_dCurrentLimit)
					break;
				timeout--;
				Sleep(10);
			}
			if (timeout < 0) {
				gSystemLog.DisplayLogAndSave(L"AA��ͼ�ȴ���ʱ!", LV_ERROR);
				//m_nAAErrorCode = ERROR_CAPTURE_ERROR;
				AAStep = 23;
				break;
			}
			UVTestFlag = 0;
			AAStep = 30;
			break;
		case 23:
			//��ʼ��ͼ
			SendMessage(m_ptrMainUI->GetSafeHwnd(), WM_COMMAND, IDC_BUTTON_STOP, 0);
			m_cIo.SetOutputIo(8, ON);
			m_cIo.SetOutputIo(7, OFF);
			Sleep(400);
			m_cIo.SetOutputIo(7, ON);
			m_cIo.SetOutputIo(8, OFF);
			Sleep(700);
			SendMessage(m_ptrMainUI->GetSafeHwnd(), WM_COMMAND, IDC_BUTTON_START, 0);
			AAStep = 28;
			break;
		case 28://�ȴ���ͼ���
			timeout = m_nCaptureWaitTime * 100;
			while (/*m_bStartCapture == 0 && */timeout >= 0) {
				if (m_bStartCapture == 1 && m_fPowerCurrentVal[0] >= m_dCurrentLimit)
					break;
				timeout--;
				Sleep(10);
			}
			if (timeout < 0) {
				gSystemLog.DisplayLogAndSave(L"AA��ͼ�ȴ���ʱ!3", LV_ERROR);
				//m_nAAErrorCode = ERROR_CAPTURE_ERROR;
				AAStep = 50;
				SaveMes(1, 0, 0);
				m_nAANG1++;
				SetDlgItemTextW(m_ptrMainUI->GetSafeHwnd(), IDC_STATIC_20, L"Fail");
				SetDlgItemTextW(m_ptrMainUI->GetSafeHwnd(), IDC_STATIC_28, L"NG");
				SaveTestReport2(imgCap->bBmpTestBuf, imgCap->iBmpW, imgCap->iBmpH, 3);
				break;
			}
			UVTestFlag = 0;
			AAStep = 30;
			break;

			//******************************************AA
		case 30:
			//SetDlgItemTextW(m_ptrMainUI->GetSafeHwnd(), IDC_STATIC_28, L"Test");
			SetDlgItemTextW(m_ptrMainUI->GetSafeHwnd(), IDC_STATIC_20, L"Testing");
			gSystemLog.DisplayLogAndSave(L"AAվ��ʼAA����!", LV_EVENT);
			//AA������
			//NG���� ��֮����
			Sleep(int(m_nDelay * 1000));
			result = SearchZ();
			if (result)
			{
				result = MoveCenter();
				if (result)
				{
					result = FocusScan();
					if (result)
					{
						Sleep(400);
						result = MoveCenter();
					}
				}
			}
			if (!result || m_bStartCapture == 0)
			{

				gSystemLog.DisplayLogAndSave(L"AA���� - ����ʧ��", LV_ERROR);
				if (m_bManualFlag) {
					m_bManualDone = 0;
					RestartAA = 0;
					AAStep = 31;
				}
				else {
					AAStep = 50;
					SaveMes(1, 1, 0);
					m_nAANG2++;
					SaveTestReport2(imgCap->bBmpTestBuf, imgCap->iBmpW, imgCap->iBmpH, 1);
				}
				SetDlgItemTextW(m_ptrMainUI->GetSafeHwnd(), IDC_STATIC_20, L"Fail");
				SetDlgItemTextW(m_ptrMainUI->GetSafeHwnd(), IDC_STATIC_28, L"NG");
				//SaveMes();
			}
			else
			{
				if (TestResult)
				{
					if (m_bOffsetFlag)
					{
						UVTestFlag = 1;
						MoveOffsetZ(-m_dOffsetZ);
					}
					gSystemLog.DisplayLogAndSave(L"AA���� - �ɹ�", LV_ERROR);
					AAStep = 40;
					SetDlgItemTextW(m_ptrMainUI->GetSafeHwnd(), IDC_STATIC_28, L"OK");
					SaveTestReport2(imgCap->bBmpTestBuf, imgCap->iBmpW, imgCap->iBmpH, 1);
				}
				else
				{
					gSystemLog.DisplayLogAndSave(L"AA���� - ʧ�� - ���β���", LV_ERROR);
					Sleep(400);
					if (TestResult)
					{
						if (m_bOffsetFlag)
						{
							UVTestFlag = 1;
							MoveOffsetZ(-m_dOffsetZ);
						}
						gSystemLog.DisplayLogAndSave(L"AA���� - �ɹ�", LV_ERROR);
						AAStep = 40;
						SetDlgItemTextW(m_ptrMainUI->GetSafeHwnd(), IDC_STATIC_28, L"OK");
						SaveTestReport2(imgCap->bBmpTestBuf, imgCap->iBmpW, imgCap->iBmpH, 1);
					}
					else
					{
						Sleep(100);
						gSystemLog.DisplayLogAndSave(L"AA���� - ������ʧ��", LV_ERROR);
						if (m_bManualFlag) {
							m_bManualDone = 0;
							RestartAA = 0;
							AAStep = 31;
						}
						else {
							AAStep = 50;
							SaveMes(1, 1, 0);
							m_nAANG2++;
							SaveTestReport2(imgCap->bBmpTestBuf, imgCap->iBmpW, imgCap->iBmpH, 1);
						}
						SetDlgItemTextW(m_ptrMainUI->GetSafeHwnd(), IDC_STATIC_20, L"Fail");
						SetDlgItemTextW(m_ptrMainUI->GetSafeHwnd(), IDC_STATIC_28, L"NG");
						//SaveMes();
					}
				}
			}
			//SaveTestReport2(imgCap->bBmpTestBuf, imgCap->iBmpW, imgCap->iBmpH, 1);
			break;
		case 31:
			//�ȴ��ֶ�AA����
			SetDlgItemTextW(m_ptrMainUI->GetSafeHwnd(), IDC_STATIC_20, L"AA:ʧ�ܣ��ȴ��ֶ�");
			if (m_bManualFlag) {
				if (RestartAA == 1) {
					RestartAA = 0;
					gSystemLog.DisplayLogAndSave(L"�ٴ��Զ�AA", LV_ERROR);
					AAStep = 30;
					break;
				}
				if (m_bManualDone == 1) {
					m_bManualDone = 0;
					if (TestResult)
					{
						if (m_bOffsetFlag)
						{
							UVTestFlag = 1;
							MoveOffsetZ(-m_dOffsetZ);
						}
						gSystemLog.DisplayLogAndSave(L"�ֶ� AA���� - �ɹ�", LV_ERROR);
						AAStep = 40;
						SetDlgItemTextW(m_ptrMainUI->GetSafeHwnd(), IDC_STATIC_28, L"OK");
					}
					else
					{
						Sleep(100);
						gSystemLog.DisplayLogAndSave(L"�ֶ� AA���� - ����ʧ��", LV_ERROR);
						AAStep = 50;
						SaveMes(1, 1, 0);
						m_nAANG2++;
						SetDlgItemTextW(m_ptrMainUI->GetSafeHwnd(), IDC_STATIC_20, L"Fail");
						SetDlgItemTextW(m_ptrMainUI->GetSafeHwnd(), IDC_STATIC_28, L"NG");
					}
					SaveTestReport2(imgCap->bBmpTestBuf, imgCap->iBmpW, imgCap->iBmpH, 1);
				}
			}
			else {
				gSystemLog.DisplayLogAndSave(L"�ֶ� AA���� - ����", LV_ERROR);
				AAStep = 50;
				SaveMes(1, 1, 0);
			}
			break;
		case 40:
			SetDlgItemTextW(m_ptrMainUI->GetSafeHwnd(), IDC_STATIC_20, L"AA:UV");
			gSystemLog.DisplayLogAndSave(L"AAվ��ʼUV", LV_EVENT);
			SetDlgItemTextW(m_ptrMainUI->GetSafeHwnd(), IDC_STATIC_31, L"Test");
			//UV�̻�
			m_cIo.SetOutputIo(21, ON);
			Sleep(50);
			m_cIo.SetOutputIo(21, OFF);

			Sleep(m_nUVTime * 1000);

			m_cIo.SetOutputIo(22, ON);
			Sleep(50);
			m_cIo.SetOutputIo(22, OFF);

			SetDlgItemTextW(m_ptrMainUI->GetSafeHwnd(), IDC_STATIC_31, L"OK");
			AAStep = 41;
			break;
		case 41:
			gSystemLog.DisplayLogAndSave(L"AAվ��ʼUV����", LV_EVENT);
			SetDlgItemTextW(m_ptrMainUI->GetSafeHwnd(), IDC_STATIC_34, L"Test");
			m_cIo.SetOutputIo(10, ON);
			m_cIo.SetOutputIo(9, OFF);
			Sleep(50);
			timeout = 50;
			while (true)
			{
				Sleep(10);
				if (S10)
				{
					AAStep = 45;
					break;
				}
				timeout--;
				if (timeout < 0)
				{
					gSystemLog.DisplayLogAndSave(L"AA��צ����ԭλδ��λ!", LV_ERROR);
					//m_nAAErrorCode = ERROR_S17_ERROR;
					//SetDlgItemTextW(m_ptrMainUI->GetSafeHwnd(), IDC_STATIC_34, L"NG");
					AAStep = 45;
					break;
				}
			}
			break;
		case 45:
			//AAStep = 60;
			//SetDlgItemTextW(m_ptrMainUI->GetSafeHwnd(), IDC_STATIC_34, L"OK");
			//break;
			UVTestFlag = 1;
			//�̻������Ȳ���
			Sleep(50);
			if (1)
			{
				int NewData = m_nNewDataFlag;
				int cnt = 0;
				while (m_nNewDataFlag == NewData)
				{
					Sleep(1);
					cnt++;
					if (cnt > 1000)
						break;
				}
			}
			//NG���� ��֮����

			Sleep(200);
			if (TestResult)
			{
				gSystemLog.DisplayLogAndSave(L"UV����� - �ɹ�", LV_ERROR);
				AAStep = 60; 
				m_nAAOK++;
				SetDlgItemTextW(m_ptrMainUI->GetSafeHwnd(), IDC_STATIC_34, L"OK");
			}
			else
			{
				Sleep(400);
				if (TestResult)
				{
					gSystemLog.DisplayLogAndSave(L"UV����� - �ɹ�", LV_ERROR);
					AAStep = 60;
					m_nAAOK++;
					SetDlgItemTextW(m_ptrMainUI->GetSafeHwnd(), IDC_STATIC_34, L"OK");
				}
				else
				{
					gSystemLog.DisplayLogAndSave(L"UV����� - ������ʧ��", LV_ERROR);
					AAStep = 61;
					SaveMes(1, 1, 0);
					m_nAANG3++;
					SetDlgItemTextW(m_ptrMainUI->GetSafeHwnd(), IDC_STATIC_34, L"NG");
				}
			}
			SaveTestReport2(imgCap->bBmpTestBuf, imgCap->iBmpW, imgCap->iBmpH, 2);
			break;

		case 50://NG - �ɿ���צ
			m_cIo.SetOutputIo(10, ON);
			m_cIo.SetOutputIo(9, OFF);
			Sleep(50);
			timeout = 100;
			while (true)
			{
				Sleep(20);
				if (S10)
				{
					AAStep = 61;
					break;
				}
				timeout--;
				if (timeout < 0)
				{
					gSystemLog.DisplayLogAndSave(L"AA��צ����ԭλδ��λ!", LV_ERROR);
					//m_nAAErrorCode = ERROR_S17_ERROR;
					AAStep = 61;
					break;
				}
			}
			break;
		case 60://OK
			SaveMes(1, 1, 1);
			NGNum = 0;
			SetDlgItemTextW(m_ptrMainUI->GetSafeHwnd(), IDC_STATIC_20, L"Pass");
			gSystemLog.DisplayLogAndSave(L"AAվ��ʼдrfid - ok!", LV_EVENT);
			if (!m_nPassRfidFlag) {
				//дRfid - NG
				memset(output2, 0, sizeof(output2));
				m_cRfidComm2.send_data_feedback((BYTE*)Next_10, sizeof(Next_10), (BYTE*)output2, sizeof(output2));
			}
			
			//��������
			SetDlgItemTextW(m_ptrMainUI->GetSafeHwnd(), IDC_STATIC_37, L"OK");
			AAStep = 70;
			break;
		case 61://NG
			NGNum++;
			SetDlgItemTextW(m_ptrMainUI->GetSafeHwnd(), IDC_STATIC_20, L"Fail");
			gSystemLog.DisplayLogAndSave(L"AAվ��ʼдrfid - ng!", LV_EVENT);
			if (!m_nPassRfidFlag) {
				//дRfid - NG
				memset(output2, 0, sizeof(output2));
				m_cRfidComm2.send_data_feedback((BYTE*)Next_10, sizeof(Next_10), (BYTE*)output2, sizeof(output2));
				Sleep(100);
				m_cRfidComm2.send_data_feedback((BYTE*)Result_0, sizeof(Result_0), (BYTE*)output2, sizeof(output2));
				Sleep(100);
				m_cRfidComm2.send_data_feedback((BYTE*)NG_30, sizeof(NG_30), (BYTE*)output2, sizeof(output2));
				gSystemLog.DisplayLogAndSave(L"End Send Rfid ng", LV_EVENT);
			}

			//��������
			SetDlgItemTextW(m_ptrMainUI->GetSafeHwnd(), IDC_STATIC_37, L"OK");
			AAStep = 70;
			break;

		case 70:
			SetDlgItemTextW(m_ptrMainUI->GetSafeHwnd(), IDC_STATIC_20, L"��ʼ��λ����");
			SetDlgItemTextW(m_ptrMainUI->GetSafeHwnd(), IDC_STATIC_40, L"Wait");

			gSystemLog.DisplayLogAndSave(L"AAվ��ʼ��λ", LV_EVENT);
			//������ͼ
			//m_bStopCapture = 1;
			SendMessage(m_ptrMainUI->GetSafeHwnd(), WM_COMMAND, IDC_BUTTON_STOP, 0);
			imgCap->m_bInitFlag = FALSE;

			//������������ ���ԭλ
			m_cIo.SetOutputIo(7, OFF);
			m_cIo.SetOutputIo(8, ON);
			Sleep(50);
			//��⵽λ�ź�
			timeout = 300;
			while (true)
			{
				Sleep(10);
				if (S08)
				{
					break;
				}
				timeout--;
				if (timeout < 0)
				{
					UVTestFlag = 0;
					gSystemLog.DisplayLogAndSave(L"AA�ϵ�����ԭλδ��λ!", LV_ERROR);
					SetDlgItemTextW(m_ptrMainUI->GetSafeHwnd(), IDC_STATIC_40, L"NG");
					m_nAAErrorCode = ERROR_S08_ERROR;
					//m_nButtonValue = 20;
					break;
				}
			}

			m_cIo.SetOutputIo(5, OFF);
			m_cIo.SetOutputIo(6, ON);
			Sleep(50);
			//��⵽λ�ź�
			timeout = 300;
			while (true)
			{
				Sleep(10);
				if (S06)
				{
					UVTestFlag = 0;
					AAStep = 71;
					m_nButtonValue = 20;
					break;
				}
				timeout--;
				if (timeout < 0)
				{
					UVTestFlag = 0;
					gSystemLog.DisplayLogAndSave(L"AA�ϵ�����ԭλδ��λ!", LV_ERROR);
					gSystemLog.DisplayLogAndSave(L"AA��������ԭλδ��λ!", LV_ERROR);
					SetDlgItemTextW(m_ptrMainUI->GetSafeHwnd(), IDC_STATIC_40, L"NG");
					//m_nAAErrorCode = ERROR_S05_ERROR;
					m_nButtonValue = 20;
					break;
				}
			}
			break;
		case 71:
			if (S24) {
				Sleep(100);
				break;
			}
			m_cIo.SetOutputIo(4, ON);//�����赲���� ��ֹ�赲��ס����
			timeout = 500;
			//while (timeout > 0) {
			//	timeout--;
			//	Sleep(10);
			//	if (S24)
			//		break;
			//}
			Sleep(400);
			m_cIo.SetOutputIo(4, OFF);//
			//result = PickLens();
			//if (!result)
			//{
			//	gSystemLog.DisplayLogAndSave(L"AA��צ�ƶ����� - 2!", LV_ERROR);
			//	SetDlgItemTextW(m_ptrMainUI->GetSafeHwnd(), IDC_STATIC_40, L"NG");
			//	m_nAAErrorCode = ERROR_PICK_ERROR;
			//	break;
			//}
			SetDlgItemTextW(m_ptrMainUI->GetSafeHwnd(), IDC_STATIC_40, L"OK");
			AAStep = 0; 
			m_cRfidAA.m_nId = 0;
			if(NGNum > 3 && OpenNGBaojing)
				m_nAAErrorCode = ERROR_NGNUM_ERROR;
			break;

		}
	}
	return 0;
}

unsigned int __stdcall CSystemManager::AutoRightThread()
{
	int nStep = 0;
	int timeout = 0;
	int result = 0;
	CString cstr;
	int Cnt_S22 = 0;
	while (0 == m_nExitFlag)
	{
		Sleep(10);

		if (S22 && m_bAutoAAFlag == 0)
		{//��λ��ť�ź�	//����һ�룬����Ӳ����λ
			if (Cnt_S22 < 100)
			{
				Cnt_S22++;
				continue;
			}
			Cnt_S22 = 0;
			nStep = 0;

			m_cIo.SetOutputIo(12, ON);
			m_cIo.SetOutputIo(11, OFF);
			m_cIo.SetOutputIo(30, OFF);

			continue;
		}
		else
			Cnt_S22 = 0;

		if (m_nAAErrorCode != 0)
		{
			m_bAutoAAFlag = 0;
			continue;
		}

		if (!m_bAutoAAFlag)
		{
			continue;
		}

		switch (nStep) {
		case 0:
			if (S24 && !S13 && S12) {
				Sleep(400);
				if (!S24)
					break;
				nStep = 1;
				m_cIo.SetOutputIo(30, ON);
				Sleep(200);
				m_cIo.SetOutputIo(30, OFF);
			}
			if (S13) {
				Sleep(2000);
				if (!S13)
					break;
				nStep = 2;
			}
			break;
		case 1:
			if (S13) {
				Sleep(2000);
				if (!S13)
					break;
				nStep = 2;
			}
			break;
		case 2:
			m_cIo.SetOutputIo(11, ON);
			m_cIo.SetOutputIo(12, OFF);
			timeout = 500;
			while (true)
			{
				Sleep(10);
				if (S11)
				{
					nStep = 10;
					break;
				}
				timeout--;
				if (timeout < 0)
				{
					gSystemLog.DisplayLogAndSave(L"����������δ��λ!", LV_ERROR);
					m_nAAErrorCode = ERROR_S12_ERROR;
					break;
				}
			}
			break;
		case 10:
			timeout = 500;
			while (true)
			{
				Sleep(10);
				if (S14)
				{
					nStep = 20;
					break;
				}
				timeout--;
				if (timeout < 0)
				{
					gSystemLog.DisplayLogAndSave(L"�������������߳�ʱ!", LV_ERROR);
					//m_nAAErrorCode = ERROR_S14_ERROR;
					nStep = 20;
					break;
				}
			}
			break;
		case 20:
			Sleep(5000);
			m_cIo.SetOutputIo(12, ON);
			m_cIo.SetOutputIo(11, OFF);
			timeout = 500;
			while (true)
			{
				Sleep(10);
				if (S12)
				{
					nStep = 0;
					break;
				}
				timeout--;
				if (timeout < 0)
				{
					gSystemLog.DisplayLogAndSave(L"����������δ��λ!", LV_ERROR);
					m_nAAErrorCode = ERROR_S11_ERROR;
					break;
				}
			}
			break;

		}
	}
	return 0;
}

//��ɫ��
void CSystemManager::StartLightControlThread()
{
	ProcLight.MemProc = &CSystemManager::LightControlThread;
	UINT nThreadId;
	HANDLE hThread = (HANDLE)_beginthreadex(NULL, 0, ProcLight.ThreadProc, (LPVOID)this, 0, &nThreadId);
	if (hThread == NULL)
	{
		return;
	}
	//m_vWorkerThread.push_back(hThread);
}

unsigned int __stdcall CSystemManager::LightControlThread()
{
	while (0 == m_nExitFlag)
	{
		Sleep(500);
		//m_nLightMode
		switch (m_nLightMode)
		{
		case LIGHT_RED:
			m_cIo.SetOutputIo(13, TRUE);//��
			m_cIo.SetOutputIo(14, FALSE);//��
			m_cIo.SetOutputIo(15, FALSE);//��
			m_cIo.SetOutputIo(16, FALSE);
			break;
		case LIGHT_YELLOW:
			m_cIo.SetOutputIo(13, FALSE);
			m_cIo.SetOutputIo(14, TRUE);
			m_cIo.SetOutputIo(15, FALSE);
			m_cIo.SetOutputIo(16, FALSE);
			break;
		case LIGHT_GREEN:
			m_cIo.SetOutputIo(13, FALSE);
			m_cIo.SetOutputIo(14, FALSE);
			m_cIo.SetOutputIo(15, TRUE);
			m_cIo.SetOutputIo(16, FALSE);
			break;
		case LIGHT_RED_TWINKEL:
			m_cIo.SetOutputIo(13, TRUE);
			m_cIo.SetOutputIo(14, FALSE);
			m_cIo.SetOutputIo(15, FALSE);
			m_cIo.SetOutputIo(16, TRUE);
			Sleep(700);
			m_cIo.SetOutputIo(13, FALSE);
			m_cIo.SetOutputIo(14, FALSE);
			m_cIo.SetOutputIo(15, FALSE);
			m_cIo.SetOutputIo(16, FALSE);
			Sleep(200);
			break;
		}

		if (!m_bAutoAAFlag)
			SendMessage(GetDlgItem(m_ptrMainUI->GetSafeHwnd(), IDC_CHECK2), BM_SETCHECK, BST_UNCHECKED, 0);
	}
	gSystemLog.DisplayLogAndSave(L"Exit thread 14", LV_EVENT);
	return 0;
}

//����
void CSystemManager::StartOtherControlThread()
{
	ProcOther.MemProc = &CSystemManager::OtherControlThread;
	UINT nThreadId;
	HANDLE hThread = (HANDLE)_beginthreadex(NULL, 0, ProcOther.ThreadProc, (LPVOID)this, 0, &nThreadId);
	if (hThread == NULL)
	{
		return;
	}
	//m_vWorkerThread.push_back(hThread);
}

unsigned int __stdcall CSystemManager::OtherControlThread()
{
	m_nLightMode = LIGHT_YELLOW;
	int cnt = 0;
	CString cstr;
	while (0 == m_nExitFlag)
	{
		Sleep(50);

		cstr.Format(L"%s", m_sGeneralSetting.m_cstrProjectName);
		SetDlgItemTextW(m_ptrMainUI->GetSafeHwnd(), IDC_STATIC_61, cstr.GetBuffer());

		SetDlgItemTextW(m_ptrMainUI->GetSafeHwnd(), IDC_STATIC_47, L"Home");
		SetDlgItemTextW(m_ptrMainUI->GetSafeHwnd(), IDC_STATIC_48, L"Alarm");
		SetDlgItemTextW(m_ptrMainUI->GetSafeHwnd(), IDC_STATIC_49, L"Emergency");

		if (m_nPassRfidFlag) {
			SetDlgItemTextA(m_ptrMainUI->GetSafeHwnd(), IDC_STATIC_45, "����RFID");
		}
		else {
			SetDlgItemTextA(m_ptrMainUI->GetSafeHwnd(), IDC_STATIC_45, "����RFID");
		}

		m_bEmergencyStopFlag = FALSE;

		if (m_vCMotor[0].m_bALM || m_vCMotor[1].m_bALM || m_vCMotor[2].m_bALM)
		{
			m_bMotorErrorFlag = 1;
		}
		else
			m_bMotorErrorFlag = 0;

		if (m_bAutoAAFlag)
		{
			m_nLightMode = LIGHT_GREEN;
		}
		else if (m_nAAErrorCode > 0)
		{
			m_nLightMode = LIGHT_RED_TWINKEL;
		}
		else if (!m_bHomeFlag)
		{
			m_nLightMode = LIGHT_RED;
		}
		else
		{
			m_nLightMode = LIGHT_YELLOW;
		}

		//if (Show > 15) {
		//	Show = 0;
		//	if (m_nImageSource == IMG_RO_LONGO) {
		//		CString cstr;
		//		cstr.Format(L"%.3f", imgRLG.CurrentTest());
		//		SetDlgItemTextW(m_ptrMainUI->GetSafeHwnd(), IDC_STATIC_103, cstr.GetBuffer());
		//	}
		//}
		cnt++;
		if (cnt > 10)
		{
			//if (m_nImageSource == IMG_RO_LONGO && m_bStartCapture) {
			//	cstr.Format(L"%.3f", imgRLG.CurrentTest());
			//	SetDlgItemTextW(m_ptrMainUI->GetSafeHwnd(), IDC_STATIC_103, cstr.GetBuffer());
			//}
			if (m_nAAErrorCode > 0)
			{
				SetDlgItemTextA(m_ptrMainUI->GetSafeHwnd(), IDC_STATIC_42, m_cErrorMsg[m_nAAErrorCode]);
			}
			else
			{
				SetDlgItemTextA(m_ptrMainUI->GetSafeHwnd(), IDC_STATIC_42, "...");
			}

			cnt = 0;

			m_nAAAll = m_nAAOK + m_nAANG1 + m_nAANG2 + m_nAANG3;
			if (m_nAAAll != 0)
				m_dAAOKPer = double(m_nAAOK*100.0) / m_nAAAll;
			else
				m_dAAOKPer = 0;
			cstr.Format(L"%d", m_nAAOK); SetDlgItemText(m_ptrMainUI->GetSafeHwnd(), IDC_STATIC_70, cstr.GetBuffer());
			cstr.Format(L"%d", m_nAANG1); SetDlgItemText(m_ptrMainUI->GetSafeHwnd(), IDC_STATIC_73, cstr.GetBuffer());
			cstr.Format(L"%d", m_nAANG2); SetDlgItemText(m_ptrMainUI->GetSafeHwnd(), IDC_STATIC_75, cstr.GetBuffer());
			cstr.Format(L"%d", m_nAANG3); SetDlgItemText(m_ptrMainUI->GetSafeHwnd(), IDC_STATIC_59, cstr.GetBuffer());
			cstr.Format(L"%.1f", m_dAAOKPer); SetDlgItemText(m_ptrMainUI->GetSafeHwnd(), IDC_STATIC_77, cstr.GetBuffer());

			SaveStateConfigIni();
		}

	}
	return 0;
}


