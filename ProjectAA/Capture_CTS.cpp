#include "pch.h"
#include"Capture.h"
#include"cts.h"
#include "SystemLog.h"
#include "SystemManager.h"

extern CSystemManager    gSystemMgr;
extern CSystemLog     gSystemLog;

int CTS::init(void) {
	//log("recv CTS init.");
	BOOL bRes = 1;
	if (initdone == 0) {
		CString cstrLog;
		DEVINFO	stDevInfo[DEVNUM];
		DWORD nDevCount = 0;
		dirPath.GetCurrentDir(cDir);
		USES_CONVERSION;
		char* c_strPath = T2A(gSystemMgr.m_sGeneralSetting.m_cstrProjectName.GetBuffer());

		sprintf(sensorPath, "%s\\recipe\\%s\\%s_cts.ini", cDir, c_strPath, c_strPath);

		bRes = Cam_EnumAllDevInfo(stDevInfo, nDevCount, 0);
		cstrLog.Format(L"cam EnumAllDevInfo init result: %d,path:%s", bRes, A2T(sensorPath));
		gSystemLog.DisplayLogAndSave(cstrLog.GetBuffer(), LV_EVENT);
		Sleep(100);

		iDevID = stDevInfo[gSystemMgr.m_nCtsId].nDevID;//0304.gai		//0

		cstrLog.Format(L"id=%d,devCount=%d", iDevID, nDevCount);
		gSystemLog.DisplayLogAndSave(cstrLog.GetBuffer(), LV_EVENT);

		//if (capturedlg.ChangeGpio) {
		//	bRes = Cam_GPIODir(CTSCam.iDevID, 1, 0);//input model
		//	logdlg.log("Cam GPIO1 Dir 0: %d", bRes);
		//}
		if (gSystemMgr.m_bGpioFlag) {
			//Sleep(100);
			bRes = Cam_SetGPIOOutputValue(iDevID, gSystemMgr.m_nGpioNo, 0);
			bRes = Cam_GPIODir(iDevID, gSystemMgr.m_nGpioNo, 0);
		}

		bRes = Cam_SetConfigEx(iDevID, sensorPath); // 0: success

		iImgWidth = Cam_GetSensorOutputWidth(iDevID);
		iImgHeight = Cam_GetSensorOutputHeight(iDevID);

		cstrLog.Format(L"cam GetSensorOutputWidth result: %d,img w=%d, img h=%d", bRes, iImgWidth, iImgHeight);
		gSystemLog.DisplayLogAndSave(cstrLog.GetBuffer(), LV_EVENT);
		Sleep(100);


		//BYTE dataformat = 1; // 0:RAW8,1: YUV422, 2:MJPGorRGB24, 3:MIPIRAW10,4:DVPRAW10,5:MIPIRAW12			
		//BYTE displayformat = 1; //0: RAW8, 1:RGB24
		//BYTE BayerOrder = 1; // 0:RG_GB, 1:GR_BG, 2:GB_RG, 3:BG_GR

		dataformat = Cam_GetSensorDataFormat(iDevID);
		//if (!capturedlg.ChangeGpio) BayerOrder = Cam_GetSensorPixelOrder(iDevID);

		//logdlg.log("dataformat=%d,order=%d", dataformat, BayerOrder);
		//logdlg.log("dev id:%d, run result: %d", iDevID, bRes);
		Sleep(100);
		if (bRes == 0) {
			initdone = 1;
			return TRUE;
		}
		else {
			initdone = 0;
			return 0;
		}
	}
	bRes = Cam_BuildPreviewGraph(iDevID, NULL/*HWND_MAIN*/, iImgWidth, iImgHeight, dataformat, displayformat, BayerOrder);
	if (bRes == 0) {
		return TRUE;
	}
	else {
		initdone = 0;
		return 0;
	}
	return TRUE;
}

int CTS::run()
{
	BOOL bRes = TRUE;
	gSystemLog.DisplayLogAndSave(L"Start Run", LV_EVENT);

	bRes = Cam_MediaControlEx(iDevID, 0); //run
	CString cstrLog;
	cstrLog.Format(L"run --- dev id:%d, run result: %d", iDevID, bRes);
	gSystemLog.DisplayLogAndSave(cstrLog.GetBuffer(), LV_EVENT);
	if (bRes != 1)
		return bRes;
	if (gSystemMgr.m_bGpioFlag) {
		bRes = Cam_GPIODir(iDevID, gSystemMgr.m_nGpioNo, 1);
		if (bRes != 1)
			return bRes;
		bRes = Cam_SetGPIOOutputValue(iDevID, gSystemMgr.m_nGpioNo, 1);
		if (bRes != 1)
			return bRes;
		Sleep(500);
		bRes = Cam_SetGPIOOutputValue(iDevID, gSystemMgr.m_nGpioNo,0);
		if (bRes != 1)
			return bRes;
		bRes = Cam_GPIODir(iDevID, gSystemMgr.m_nGpioNo, 0);
	}
	//bRes = Cam_GPIOPull(iDevID,3,0);//no pull
	//logdlg.log("result0: %d",bRes);
	//bRes = Cam_GPIODir(iDevID,3,1);//output model
	//logdlg.log("result1: %d",bRes);
//	Sleep(500);
	//bRes = Cam_SetGPIOOutputValue(iDevID,3,0);
	//logdlg.log("result2: %d",bRes);
	//Sleep(500);
	//bRes = Cam_SetGPIOOutputValue(iDevID,3,1);
	//if (capturedlg.ChangeGpio) {
	//	bRes = Cam_GPIODir(iDevID, 1, 1);//output model
	//	logdlg.log("Cam GPIO1 Dir 1: %d", bRes);
	//	//Sleep(500);
	//	//bRes = Cam_SetGPIOOutputValue(iDevID, 1, 0);
	//	//logdlg.log("result2: %d", bRes);
	//	//Sleep(500);
	//	//bRes = Cam_SetGPIOOutputValue(iDevID, 1, 1);
	//}
	for (int i = 0; i < iImgWidth*iImgHeight * 3; i++) {
		gSystemMgr.imgCap->bImgBuf[i] = 0;
	}
	Sleep(100);
	return bRes;
}

int CTS::cap(void)
{
	//log("cap dev.");
	BOOL bRes;

	long buf_size = iImgWidth * iImgHeight * 3;
	bRes = Cam_GrabFrameEx(iDevID, gSystemMgr.imgCap->bImgBuf, &buf_size, 0);

	//Sleep(20);
	return bRes;
}

int CTS::stop()
{
	BOOL bRes = Cam_MediaControlEx(iDevID, 1);
	CString cstrLog;
	cstrLog.Format(L"CTS stop result:%d", bRes);
	gSystemLog.DisplayLogAndSave(cstrLog.GetBuffer(), LV_EVENT);
	//if (capturedlg.ChangeGpio) {
	//	bRes = Cam_GPIODir(CTSCam.iDevID, 1, 0);//output model
	//	logdlg.log("Cam GPIO1 Dir 0: %d", bRes);
	//}
	return TRUE;
}

int CTS::destroy()
{
	return TRUE;

}

BOOL CTS::WaitForFirstFrameArrived(DWORD devInst)
{
	gSystemLog.DisplayLogAndSave(L"start search first cam", LV_EVENT);
	int count = 400;
	int err = 0;
	err = Cam_IsFirstFrameArrived(devInst);
	while (!err && count > 0)
	{
		//Cam_MediaControl(iDevID, 1);
		count--;
		Sleep(5);
		err = Cam_IsFirstFrameArrived(devInst);
	}
	CString cstr;
	cstr.Format(L"err:%d, count:%d", err, count);
	gSystemLog.DisplayLogAndSave(cstr.GetBuffer(), LV_EVENT);

	if (count > 0)
	{
		gSystemLog.DisplayLogAndSave(L"end search first cam! Success", LV_EVENT);
		return TRUE;
	}
	else
	{
		gSystemLog.DisplayLogAndSave(L"end search first cam! Fail", LV_EVENT);
		return FALSE;
	}
}

int CTS::write_iic(void) {
	char line[500] = { 0 };
	int slave = 0;
	int addr = 0;
	char fpga[20];
	int index = 0;
	int err = 0;
	int data[4] = { 0,0,0,0 };
	uint8_t subdata[2] = { 0 };

	char sensor_name[100] = { 0 };
	char path[MAX_PATH] = { 0 };
	char ini_path[MAX_PATH] = { 0 };
	char dir[2 * MAX_PATH] = { 0 };
	dirPath.GetCurrentDir(dir);
	//sprintf(path, "%s\\recipe\\config.ini", dir);
	//read_string_key(path, "system", "default_recipe_setting", sensor_name, sizeof(sensor_name));
	USES_CONVERSION;
	char* c_strPath = T2A(gSystemMgr.m_sGeneralSetting.m_cstrProjectName.GetBuffer());
	sprintf(ini_path, "%s\\recipe\\%s\\register_setting.ini", dir, c_strPath);
	
	CString cstrLog;
	cstrLog.Format(L"write ini path: %s", A2T(ini_path));
	gSystemLog.DisplayLogAndSave(cstrLog.GetBuffer(), LV_EVENT);

	FILE *file = fopen(ini_path, "r");
	if (file == NULL) {
		gSystemLog.DisplayLogAndSave(L"open iic ini file fail", LV_ERROR);
		return FALSE;
	}

	while (fgets(line, sizeof(line), file) && index < 1000) {
		if (line[0] == 'f' && (line[1] == 'p' || line[1] == 'g')) {
			sscanf(line, "%s %x %x %x ", &fpga, &data[0], &data[1], &data[2]);

			if (strstr(fpga, "fpga0")) {
				//logdlg.log("%s 0x%02x, 0x%02x, 0x%02x", fpga, data[0], data[1], data[2]);

				slave = data[0];
				addr = data[1];
				subdata[0] = (data[2] & 0xff);
				err = Cam_WriteNormalI2CEx(iDevID, slave, addr, 1, subdata, 0);
				if (err != 1) {
					cstrLog.Format(L"write ini err line: %d", index);
					gSystemLog.DisplayLogAndSave(cstrLog.GetBuffer(), LV_EVENT);
				}
				Sleep(10);
			}
			else if (strstr(fpga, "fpga1")) { //16:8
				//logdlg.log("%s 0x%02x, 0x%04x, 0x%02x", fpga, data[0], data[1], data[2]);

				slave = data[0];
				addr = data[1];
				subdata[0] = data[2];
				err = Cam_WriteNormalI2CEx(iDevID, slave, addr, 1, subdata, 2);
				if (err != 1) {
					cstrLog.Format(L"write ini err line: %d", index);
					gSystemLog.DisplayLogAndSave(cstrLog.GetBuffer(), LV_EVENT);
				}
				Sleep(10);
			}
			else if (strstr(fpga, "fpga2")) { //8:16
				//logdlg.log("%s 0x%02x, 0x%02x, 0x%04x", fpga, data[0], data[1], data[2]);

				slave = data[0];
				addr = data[1];
				subdata[0] = ((data[2] >> 8) & 0xff);
				subdata[1] = (data[2] & 0xff);
				err = Cam_WriteNormalI2CEx(iDevID, slave, addr, 2, subdata, 1);
				if (err != 1) {
					cstrLog.Format(L"write ini err line: %d", index);
					gSystemLog.DisplayLogAndSave(cstrLog.GetBuffer(), LV_EVENT);
				}
				Sleep(10);
			}
			else if (strstr(fpga, "fpga3")) { //16:16
				//logdlg.log("%s 0x%02x, 0x%04x, 0x%04x", fpga, data[0], data[1], data[2]);
				slave = data[0];
				addr = data[1];
				subdata[0] = ((data[2] >> 8) & 0xff);
				subdata[1] = (data[2] & 0xff);
				err = Cam_WriteNormalI2CEx(iDevID, slave, addr, 2, subdata, 3);
				if (err != 1) {
					cstrLog.Format(L"write ini err line: %d", index);
					gSystemLog.DisplayLogAndSave(cstrLog.GetBuffer(), LV_EVENT);
				}
				Sleep(10);
			}

			Sleep(1);
		}
		else if (line[0] == 's' && line[1] == 'l' || line[1] == 'p') { //sleep
			sscanf(line, "%s %d", &fpga, &data[0]);
			cstrLog.Format(L"sleep %d", data[0]);
			gSystemLog.DisplayLogAndSave(cstrLog.GetBuffer(), LV_EVENT);
			Sleep(data[0]);
		}
		//if (index == 36 || index == 37 || index == 71 || index == 99)
		//	logdlg.log("-------------%s 0x%02x, 0x%04x, 0x%04x", fpga, data[0], data[1], data[2]);
		index++;
		Sleep(1);
	}

	fclose(file);
	return TRUE;
}

int CTS::write_iic_center(void) {
	char line[500] = { 0 };
	int slave = 0;
	int addr = 0;
	char fpga[20];
	int index = 0;
	int err = 0;
	int data[4] = { 0,0,0,0 };
	uint8_t subdata[2] = { 0 };

	char sensor_name[100] = { 0 };
	char path[MAX_PATH] = { 0 };
	char ini_path[MAX_PATH] = { 0 };
	char dir[2 * MAX_PATH] = { 0 };
	dirPath.GetCurrentDir(dir);
	//sprintf(path, "%s\\recipe\\config.ini", dir);
	//read_string_key(path, "system", "default_recipe_setting", sensor_name, sizeof(sensor_name));
	USES_CONVERSION;
	char* c_strPath = T2A(gSystemMgr.m_sGeneralSetting.m_cstrProjectName.GetBuffer());
	sprintf(ini_path, "%s\\recipe\\%s\\center_iic.ini", dir, c_strPath);

	CString cstrLog;
	cstrLog.Format(L"write ini path: %s", A2T(ini_path));
	gSystemLog.DisplayLogAndSave(cstrLog.GetBuffer(), LV_EVENT);

	FILE *file = fopen(ini_path, "r");
	if (file == NULL) {
		gSystemLog.DisplayLogAndSave(L"open iic ini file fail", LV_ERROR);
		return FALSE;
	}

	int MoveX = 0;
	int MoveY = 0;
	int difX;
	int difY;
	difX = gSystemMgr.m_dCenterXDif;
	difY = gSystemMgr.m_dCenterYDif;
	MoveX = difX - (difX % 2);
	MoveY = difY - (difY % 2);

	while (fgets(line, sizeof(line), file) && index < 1000) {
		if (line[0] == 'f' && (line[1] == 'p' || line[1] == 'g')) {
			sscanf(line, "%s %x %x %x ", &fpga, &data[0], &data[1], &data[2]);

			if (strstr(fpga, "fpga0")) {
				//logdlg.log("%s 0x%02x, 0x%02x, 0x%02x", fpga, data[0], data[1], data[2]);

				slave = data[0];
				addr = data[1];
				subdata[0] = (data[2] & 0xff);
				err = Cam_WriteNormalI2CEx(iDevID, slave, addr, 1, subdata, 0);
				if (err != 1) {
					cstrLog.Format(L"write ini err line: %d", index);
					gSystemLog.DisplayLogAndSave(cstrLog.GetBuffer(), LV_EVENT);
				}
				Sleep(10);
			}
			else if (strstr(fpga, "fpga1")) { //16:8
				//logdlg.log("%s 0x%02x, 0x%04x, 0x%02x", fpga, data[0], data[1], data[2]);

				slave = data[0];
				addr = data[1];
				if (addr == 0xe40c) {
					subdata[0] = data[2] + MoveX;
				}
				else if (addr == 0xe412) {
					subdata[0] = data[2] + MoveY;
				}
				else if (addr == 0xe418) {
					subdata[0] = data[2] + MoveY;
				}
				else {
					subdata[0] = data[2];
				}

				cstrLog.Format(L"0x%02x, 0x%04x, 0x%02x", slave, addr, subdata[0]);
				gSystemLog.DisplayLogAndSave(cstrLog.GetBuffer(), LV_EVENT);

				err = Cam_WriteNormalI2CEx(iDevID, slave, addr, 1, subdata, 2);
				if (err != 1) {
					cstrLog.Format(L"write ini err line: %d", index);
					gSystemLog.DisplayLogAndSave(cstrLog.GetBuffer(), LV_EVENT);
				}
				Sleep(10);
			}
			else if (strstr(fpga, "fpga2")) { //8:16
				//logdlg.log("%s 0x%02x, 0x%02x, 0x%04x", fpga, data[0], data[1], data[2]);

				slave = data[0];
				addr = data[1];
				subdata[0] = ((data[2] >> 8) & 0xff);
				subdata[1] = (data[2] & 0xff);
				err = Cam_WriteNormalI2CEx(iDevID, slave, addr, 2, subdata, 1);
				if (err != 1) {
					cstrLog.Format(L"write ini err line: %d", index);
					gSystemLog.DisplayLogAndSave(cstrLog.GetBuffer(), LV_EVENT);
				}
				Sleep(10);
			}
			else if (strstr(fpga, "fpga3")) { //16:16
				//logdlg.log("%s 0x%02x, 0x%04x, 0x%04x", fpga, data[0], data[1], data[2]);
				slave = data[0];
				addr = data[1];
				subdata[0] = ((data[2] >> 8) & 0xff);
				subdata[1] = (data[2] & 0xff);
				err = Cam_WriteNormalI2CEx(iDevID, slave, addr, 2, subdata, 3);
				if (err != 1) {
					cstrLog.Format(L"write ini err line: %d", index);
					gSystemLog.DisplayLogAndSave(cstrLog.GetBuffer(), LV_EVENT);
				}
				Sleep(10);
			}

			Sleep(1);
		}
		else if (line[0] == 's' && line[1] == 'l' || line[1] == 'p') { //sleep
			sscanf(line, "%s %d", &fpga, &data[0]);
			cstrLog.Format(L"sleep %d", data[0]);
			gSystemLog.DisplayLogAndSave(cstrLog.GetBuffer(), LV_EVENT);
			Sleep(data[0]);
		}
		//if (index == 36 || index == 37 || index == 71 || index == 99)
		//	logdlg.log("-------------%s 0x%02x, 0x%04x, 0x%04x", fpga, data[0], data[1], data[2]);
		index++;
		Sleep(1);
	}

	fclose(file);
	return TRUE;
}
