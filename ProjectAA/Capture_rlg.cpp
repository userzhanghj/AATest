#include "pch.h"
#include "capture.h"
#include "HisFX3Platform.h"
#include "SystemLog.h"
#include "SystemManager.h"

extern CSystemManager    gSystemMgr;
extern CSystemLog     gSystemLog;

#define MAXSTRLEN 512 
#define MAXTEXTLEN 4096
#define HisReleaseNewB(x)  {if(x!=NULL) {delete[] x; x = NULL;}}
//#define _stscanf        sscanf


#pragma comment (lib,"HisFX3Platform32.lib")
_HisFX3_PreviewStruct stParamPreviewCH1;

int bSPIClkHigh;
int bSPICSLow;
int bIsSetPWDN;
int bIsSetMCLK;
float mclk = 0;
INIEdit RLGCamHWINI[] = {
	{NULL,		DLGTYPE_INPUT_INT,		&stParamPreviewCH1.bIsSetRST	,		"bIsSetRST"		},
	{NULL,		DLGTYPE_INPUT_INT,		&/*stParamPreviewCH1.*/bIsSetPWDN	,		"bIsSetPWDN"		},
	{NULL,		DLGTYPE_INPUT_INT,		&/*stParamPreviewCH1.*/bIsSetMCLK	,		"bIsSetMCLK"		},
	{NULL,		DLGTYPE_INPUT_INT,		&stParamPreviewCH1.onlyRightFrame	,		"onlyRightFrame"		},
	{NULL,		DLGTYPE_INPUT_INT,		&/*stParamPreviewCH1.*/bSPIClkHigh	,		"bSPIClkHigh"		},
	{NULL,		DLGTYPE_INPUT_INT,		&/*stParamPreviewCH1.*/bSPICSLow			,	"bSPICSLow"				},
	//volt
	{NULL,		DLGTYPE_INPUT_FLOAT,		&stParamPreviewCH1.volt_AVDD ,				"volt_AVDD"		},
	{NULL,		DLGTYPE_INPUT_FLOAT,		&stParamPreviewCH1.volt_DVDD ,				"volt_DVDD"		},
	{NULL,		DLGTYPE_INPUT_FLOAT,		&stParamPreviewCH1.volt_DOVDD,				"volt_DOVDD"		},
	{NULL,		DLGTYPE_INPUT_FLOAT,		&stParamPreviewCH1.volt_IODD ,				"volt_IODD"		},
	{NULL,		DLGTYPE_INPUT_FLOAT,		&stParamPreviewCH1.volt_POW	,				"volt_POW"		},
	{NULL,		DLGTYPE_INPUT_FLOAT,		&stParamPreviewCH1.volt_AF	,				"volt_AF"			},
	{NULL,		DLGTYPE_INPUT_FLOAT,		&stParamPreviewCH1.volt_OTP	,				"volt_OTP"		},
	{NULL,		DLGTYPE_INPUT_FLOAT,		&stParamPreviewCH1.volt_5V	,				"volt_5V"			},
	{NULL,		DLGTYPE_INPUT_FLOAT,		&stParamPreviewCH1.volt_12V	,				"volt_12V"			},
	//iic
	{NULL,		DLGTYPE_INPUT_INT,		&stParamPreviewCH1.ucCommProtocal	,		"ucCommProtocal"		},
	{NULL,		DLGTYPE_INPUT_INT,		&stParamPreviewCH1.usI2CSpeed		,		"usI2CSpeed"				},
	{NULL,		DLGTYPE_INPUT_INT,		&stParamPreviewCH1.usI2CIntervalTime ,		"usI2CIntervalTime"		},
	{NULL,		DLGTYPE_INPUT_INT,		&stParamPreviewCH1.bCheckDeviceAck	,		"bCheckDeviceAck"			},
	{NULL,		DLGTYPE_INPUT_INT,		&stParamPreviewCH1.bSPILittleEndian	,		"bSPILittleEndian"		},
	{NULL,		DLGTYPE_INPUT_INT,		&stParamPreviewCH1.bReset_ActiveLow	,		"bReset_ActiveLow"			},
	{NULL,		DLGTYPE_INPUT_INT,		&stParamPreviewCH1.bPWND_ActiveLow	,		"bPWND_ActiveLow"			},
	{NULL,		DLGTYPE_INPUT_FLOAT,		&/*stParamPreviewCH1.*/mclk				,		"mclk"			},
	{NULL,		DLGTYPE_INPUT_INT,		&stParamPreviewCH1.bDVP_VS_ActiveHigh,		"bDVP_VS_ActiveHigh"			},
	{NULL,		DLGTYPE_INPUT_INT,		&stParamPreviewCH1.bDVP_HS_ActiveHigh,		"bDVP_HS_ActiveHigh"			},
	//power clock
	{NULL,		DLGTYPE_INPUT_INT,			&stParamPreviewCH1.sensorFactory,			"sensorFactory"			},
	{NULL,		DLGTYPE_INPUT_STRING,		stParamPreviewCH1.strSensorName,			"strSensorName"			},
	//cphy clock
	{NULL,		DLGTYPE_INPUT_FLOAT,		&stParamPreviewCH1.cphyRate,				"cphyRate"					},
	{NULL,		DLGTYPE_INPUT_INT,			&stParamPreviewCH1.cphyMode,				"cphyMode"			},
	//image
	{NULL,		DLGTYPE_INPUT_INT,			&stParamPreviewCH1.iWidth,				"iWidth"			},
	{NULL,		DLGTYPE_INPUT_INT,			&stParamPreviewCH1.iHeight,				"iHeight"			},
	{NULL,		DLGTYPE_INPUT_INT,			&stParamPreviewCH1.cphyMode,				"cphyMode"			},

	{NULL,  NULL, NULL, NULL},
};
INIEdit RLGCamHWINI2[] = {
	//volt
	{NULL,		DLGTYPE_INPUT_FLOAT,		&stParamPreviewCH1.volt_AVDD ,				"HW_Voltage_AVDD"		},
	{NULL,		DLGTYPE_INPUT_FLOAT,		&stParamPreviewCH1.volt_DVDD ,				"HW_Voltage_DVDD"		},
	{NULL,		DLGTYPE_INPUT_FLOAT,		&stParamPreviewCH1.volt_DOVDD,				"HW_Voltage_DOVDD"		},
	{NULL,		DLGTYPE_INPUT_FLOAT,		&stParamPreviewCH1.volt_IODD ,				"HW_Voltage_IOVDD"		},
	{NULL,		DLGTYPE_INPUT_FLOAT,		&stParamPreviewCH1.volt_POW	,				"HW_Voltage_POW"		},
	{NULL,		DLGTYPE_INPUT_FLOAT,		&stParamPreviewCH1.volt_AF	,				"HW_Voltage_AF"			},
	{NULL,		DLGTYPE_INPUT_FLOAT,		&stParamPreviewCH1.volt_OTP	,				"HW_Voltage_VFuse"		},
	{NULL,		DLGTYPE_INPUT_FLOAT,		&stParamPreviewCH1.volt_5V	,				"HW_OutPut_5V"			},
	{NULL,		DLGTYPE_INPUT_FLOAT,		&stParamPreviewCH1.volt_12V	,				"HW_OutPut_12V"			},
	//iic
	{NULL,		DLGTYPE_INPUT_INT,		&stParamPreviewCH1.ucCommProtocal	,		"HW_I2C_CommProtocal"		},
	{NULL,		DLGTYPE_INPUT_INT,		&stParamPreviewCH1.usI2CSpeed		,		"HW_I2C_Speed"				},
	{NULL,		DLGTYPE_INPUT_INT,		&stParamPreviewCH1.usI2CIntervalTime ,		"HW_I2C_IntervalTime"		},
	{NULL,		DLGTYPE_INPUT_INT,		&stParamPreviewCH1.bCheckDeviceAck	,		"HW_CheckDeviceAck"			},
	{NULL,		DLGTYPE_INPUT_INT,		&stParamPreviewCH1.bSPICSLow			,	"HW_SPICSLow"				},
	{NULL,		DLGTYPE_INPUT_INT,		&stParamPreviewCH1.bSPILittleEndian	,		"HW_SPILittleEndian"		},
	{NULL,		DLGTYPE_INPUT_INT,		&stParamPreviewCH1.bReset_ActiveLow	,		"HW_RESET_Active"			},
	{NULL,		DLGTYPE_INPUT_INT,		&stParamPreviewCH1.bPWND_ActiveLow	,		"HW_PWDN_Active"			},
	{NULL,		DLGTYPE_INPUT_FLOAT,		&stParamPreviewCH1.mclk				,		"HW_Sensor_MCLK"			},
	{NULL,		DLGTYPE_INPUT_INT,		&stParamPreviewCH1.bDVP_VS_ActiveHigh,		"HW_DVP_VS_Active"			},
	{NULL,		DLGTYPE_INPUT_INT,		&stParamPreviewCH1.bDVP_HS_ActiveHigh,		"HW_DVP_HS_Active"			},
	//power clock
	{NULL,		DLGTYPE_INPUT_INT,			&stParamPreviewCH1.sensorFactory,			"HW_PowerupSequence"			},
	{NULL,		DLGTYPE_INPUT_STRING,		stParamPreviewCH1.strSensorName,			"HW_SensorName"			},
	//cphy clock
	{NULL,		DLGTYPE_INPUT_FLOAT,		&stParamPreviewCH1.cphyRate,				"HW_CPHY_Rate"					},
	{NULL,		DLGTYPE_INPUT_INT,			&stParamPreviewCH1.cphyMode,				"HW_CPHY_Mode"			},
	//image
	{NULL,		DLGTYPE_INPUT_INT,			&stParamPreviewCH1.iWidth,				"Image_Width"			},
	{NULL,		DLGTYPE_INPUT_INT,			&stParamPreviewCH1.iHeight,				"Image_Height"			},
	{NULL,		DLGTYPE_INPUT_INT,			&stParamPreviewCH1.cphyMode,				"HW_CPHY_Mode"			},

	{NULL,  NULL, NULL, NULL},
};

INIEdit RLGCamIMGINI2[] = {
	//image
	{NULL,		DLGTYPE_INPUT_INT,			&stParamPreviewCH1.iWidth,				"Image_Width"			},
	{NULL,		DLGTYPE_INPUT_INT,			&stParamPreviewCH1.iHeight,				"Image_Height"			},
	{NULL,		DLGTYPE_INPUT_INT,			&stParamPreviewCH1.dataFormat,			"Image_DataFormat"			},
	{NULL,		DLGTYPE_INPUT_INT,			&stParamPreviewCH1.port,			"Image_Interface"			},
	{NULL,		DLGTYPE_INPUT_INT,			&stParamPreviewCH1.ucLaneNum,			"Image_LaneNumber"			},
	{NULL,		DLGTYPE_INPUT_INT,			&stParamPreviewCH1.ucDVP_LineFormat,			"DVP_LineFormat"			},
	{NULL,		DLGTYPE_INPUT_INT,			&stParamPreviewCH1.DVP_PhaseShift,			"DVP_PhaseShift"			},
	{NULL,		DLGTYPE_INPUT_INT,			&stParamPreviewCH1.bOutputXSVS,			"OutputXSVS"			},
	{NULL,		DLGTYPE_INPUT_INT,			&stParamPreviewCH1.uiDummyLeft,			"Image_DummyLeft"			},
	{NULL,		DLGTYPE_INPUT_INT,			&stParamPreviewCH1.uiDummyRight,			"Image_DummyRight"			},
	{NULL,		DLGTYPE_INPUT_INT,			&stParamPreviewCH1.uiDummyTop,			"Image_DummyTop"			},
	{NULL,		DLGTYPE_INPUT_INT,			&stParamPreviewCH1.uiDummyBottom,			"Image_DummyBottom"			},


	{NULL,  NULL, NULL, NULL},
};
INIEdit RLGCamIMGINI[] = {
	//image
	{NULL,		DLGTYPE_INPUT_INT,			&stParamPreviewCH1.iWidth,				"iWidth"			},
	{NULL,		DLGTYPE_INPUT_INT,			&stParamPreviewCH1.iHeight,				"iHeight"			},
	{NULL,		DLGTYPE_INPUT_INT,			&stParamPreviewCH1.dataFormat,			"dataFormat"			},
	{NULL,		DLGTYPE_INPUT_INT,			&stParamPreviewCH1.port,			"port"			},
	{NULL,		DLGTYPE_INPUT_INT,			&stParamPreviewCH1.ucLaneNum,			"ucLaneNum"			},
	{NULL,		DLGTYPE_INPUT_INT,			&stParamPreviewCH1.ucDVP_LineFormat,			"ucDVP_LineFormat"			},
	{NULL,		DLGTYPE_INPUT_INT,			&stParamPreviewCH1.DVP_PhaseShift,			"DVP_PhaseShift"			},
	{NULL,		DLGTYPE_INPUT_INT,			&stParamPreviewCH1.bOutputXSVS,			"bOutputXSVS"			},


	{NULL,  NULL, NULL, NULL},
};

void setConfigIni(char* strPath)
{

	//dirPath.LoadKey(strPath, "User", hdlg, UserDlgINI, sizeof(UserDlgINI) / sizeof(UserDlgINI[0]));
	//I2C
	//07.09 gai dong
	//stParamPreviewCH1.uiVoltSetFlag = ai_win::read_integer_key(strPath, "HW_Sensor", "HW_uiVoltSetFlag");
	stParamPreviewCH1.uiVoltSetFlag = 0x77;	
	//stParamPreviewCH1.bIsSetMCLK = ai_win::read_integer_key(strPath, "HW_Sensor", "HW_bIsSetMCLK");
	stParamPreviewCH1.ddr = 1;
	stParamPreviewCH1.mclk = mclk;
	stParamPreviewCH1.bIsSetMCLK = bIsSetMCLK;
	stParamPreviewCH1.bIsSetPWDN = bIsSetPWDN;
	stParamPreviewCH1.bSPIClkHigh = bSPIClkHigh;
	stParamPreviewCH1.bSPICSLow = bSPICSLow;

	//power clock
	//stParamPreviewCH1.sensorFactory = (_HisFX3_ImageSenor_Factory)ai_win::read_integer_key(strPath, "HW_Sensor", "HW_PowerupSequence");
	//ai_win::read_string_key(strPath, "HW_Sensor", "HW_SensorName", stParamPreviewCH1.strSensorName, 64);
	//bool HW_ENGINEER_Mode = ai_win::read_integer_key(strPath, "HW_Sensor", "HW_ENGINEER_Mode");
	//if (HW_ENGINEER_Mode)
	//	stParamPreviewCH1.onlyRightFrame = 0x0;  //工程人员模式，在分析没有图输出的时候，可以开启，检查是否有帧输出；
	//else
	//	stParamPreviewCH1.onlyRightFrame = 0x3;  //产线生产模式，底层丢掉错误帧，不上传；
	stParamPreviewCH1.onlyRightFrame = 0x0;
	//////////////////////////////////////////////////////////////////////////
	//image
	//stParamPreviewCH1.dataFormat = (_HisFX3_BaylorMode)ai_win::read_integer_key(strPath, "Image_Sensor", "Image_DataFormat");
	//log("dataformat:%d", stParamPreviewCH1.dataFormat);
	//stParamPreviewCH1.port = (_HisFX3_MIPILane_Stream)ai_win::read_integer_key(strPath, "Image_Sensor", "Image_Interface");

	stParamPreviewCH1.uiDummyBottom = stParamPreviewCH1.uiDummyLeft = stParamPreviewCH1.uiDummyRight = stParamPreviewCH1.uiDummyTop = 0;

	//if (stParamPreviewCH1.port == 0x10)
	//{
	//	stParamPreviewCH1.LVDS_XHS = (unsigned int)ai_win::read_integer_key(strPath, "Image_Sensor", "Image_LVDS_XHS");
	//	stParamPreviewCH1.LVDS_XVS = (unsigned int)ai_win::read_integer_key(strPath, "Image_Sensor", "Image_LVDS_XVS");
	//	stParamPreviewCH1.LVDSAlign = (unsigned short)ai_win::read_integer_key(strPath, "Image_Sensor", "Image_LVDSAlign");
	//}
	//////////////////////////////////////////////////////////////////////////
	//I2C cmd
	int iresult = 0;
	FILE			*fp;
	unsigned int	wRegAddr = 0;
	unsigned int	wRegData = 0;
	unsigned char  usSlave = 0;
	unsigned short  usI2Type = 0;
	int				tmp_idata = 0;
	BOOL			Register_end = FALSE;
	int				data = 0;
	int               I2CIndex = 0;
	std::string   sdata;
	int idata = 0;
	char _temp[128] = { 0 };
	char	tmp_cmd[MAXSTRLEN] = { 0 };
	char	tmp_data[MAXSTRLEN] = { 0 };
	char	linebufIn[MAXSTRLEN * 2];
	bool	bwrite_start = false;
	CString cstrLog;

	HisReleaseNewB(stParamPreviewCH1.pucSlave);
	HisReleaseNewB(stParamPreviewCH1.puiReg);
	HisReleaseNewB(stParamPreviewCH1.puiData);
	HisReleaseNewB(stParamPreviewCH1.pusType);
	stParamPreviewCH1.usI2CCount = 2048;   //预设值；如果I2C 指令条数超过2048行，设置加大
	stParamPreviewCH1.pucSlave = new unsigned char[stParamPreviewCH1.usI2CCount];
	stParamPreviewCH1.puiReg = new unsigned int[stParamPreviewCH1.usI2CCount];
	stParamPreviewCH1.puiData = new unsigned int[stParamPreviewCH1.usI2CCount];
	stParamPreviewCH1.pusType = new unsigned short[stParamPreviewCH1.usI2CCount];

	if (fopen_s(&fp, strPath, "r") != 0)
	{
		//Fail
		iresult = HisFX3Error_OpenFile;
		//cstrLog.Format(L"cam EnumAllDevInfo init result: %d,path:%s", bRes, sensorPath);
		gSystemLog.DisplayLogAndSave(L"cannot find config file", LV_ERROR);
	}

	memset(linebufIn, 0, sizeof(char)*MAXSTRLEN * 2);

	while (fgets(linebufIn, MAXSTRLEN * 2, fp))
	{
		memset(tmp_cmd, 0, sizeof(char)*MAXSTRLEN);
		sscanf_s(linebufIn, "%s", tmp_cmd, _countof(tmp_cmd));
		if ((0 == strcmp("[Register_Sensor]", tmp_cmd)))
		{

			if (bwrite_start == false)
			{
				bwrite_start = true;
			}
		}
		else if ((0 == strcmp("[END]", tmp_cmd)) && bwrite_start == true)
		{
			bwrite_start = false;
			break;
		}
		//-------------------------------------------------
		if (true == bwrite_start)
		{
			for (int i = 0; i < 4; i++)	//
			{
				linebufIn[i] = (char)towupper(linebufIn[i]);
			}

			if (linebufIn[0] == '0' && linebufIn[1] == 'X')
			{
				sdata = linebufIn;
				int index = sdata.find(",", 0);
				strncpy_s(_temp, linebufIn, index);
				sscanf(_temp, "%x", &idata);
				usSlave = unsigned char(idata);

				sdata.clear();
				sdata = linebufIn + (index + 1);
				index = sdata.find(",", 0);
				strncpy_s(_temp, sdata.c_str(), index);
				sscanf(_temp, "%x", &idata);
				wRegAddr = unsigned int(idata);

				strcpy_s(linebufIn, 1024, sdata.c_str());
				sdata.clear();
				sdata = linebufIn + (index + 1);
				index = sdata.find(",", 0);
				strncpy_s(_temp, sdata.c_str(), index);
				sscanf(_temp, "%x", &idata);
				wRegData = unsigned int(idata);

				strcpy_s(linebufIn, 1024, sdata.c_str());
				sdata.clear();
				sdata = linebufIn + (index + 1);
				sscanf(sdata.c_str(), "%x", &idata);
				usI2Type = unsigned short(idata);

				stParamPreviewCH1.pucSlave[I2CIndex] = usSlave;
				stParamPreviewCH1.puiReg[I2CIndex] = wRegAddr;
				stParamPreviewCH1.puiData[I2CIndex] = wRegData;
				stParamPreviewCH1.pusType[I2CIndex] = usI2Type;
				//cstrLog.Format(L"write reg:0x%x,0x%x,0x%x,0x%x", usSlave, wRegAddr, wRegData, usI2Type);
				//gSystemLog.DisplayLogAndSave(cstrLog.GetBuffer(), LV_EVENT);
				I2CIndex++;
			}
			memset(linebufIn, 0, sizeof(char)*MAXSTRLEN * 2);
		}//end bWrite
	}
	stParamPreviewCH1.usI2CCount = I2CIndex;

	cstrLog.Format(L"uI2CCount:%d", stParamPreviewCH1.usI2CCount);
	gSystemLog.DisplayLogAndSave(cstrLog.GetBuffer(), LV_EVENT);
	fclose(fp);
}

int Rolongo::init(void)
{
	gSystemLog.DisplayLogAndSave(L"recv RLG init.", LV_EVENT);
	CString cstrLog;
	int nReslut;
	int devCount = 0;
	char **dev[MAX_PATH];
	char dir[MAX_PATH] = { 0 };
	char sensor_path[MAX_PATH] = { 0 };
	int ret = RBOXAPI::HisFX3EnumDev(dev, &devCount);
	cstrLog.Format(L"Enum rt:%d", ret);
	gSystemLog.DisplayLogAndSave(cstrLog.GetBuffer(), LV_EVENT);
	cstrLog.Format(L"devCount:%d", devCount);
	gSystemLog.DisplayLogAndSave(cstrLog.GetBuffer(), LV_EVENT);
	USES_CONVERSION;
	if (devCount == 0)
		return 0;
	for (int i = 0; i < devCount; i++) {
		cstrLog.Format(L"dev[%d]:%s", i, A2T(dev[0][i]));
		gSystemLog.DisplayLogAndSave(cstrLog.GetBuffer(), LV_EVENT);
	}
	//RBOXAPI::HisFX3IsOpen();
	//RBOXAPI::HisFX3OpenDevice(0, dev[0][0]);
	nReslut = RBOXAPI::HisFX3IsOpen();
	if (!nReslut)
	{
		nReslut = RBOXAPI::HisFX3OpenDevice(0, dev[0][0]);
		cstrLog.Format(L"HisFX3OpenDevice:%d", nReslut);
		gSystemLog.DisplayLogAndSave(cstrLog.GetBuffer(), LV_EVENT);
		if (nReslut != 0)
		{
			return 0;
		}
	}
	else
	{
		int rt = RBOXAPI::HisFX3StopPreview(NULL, 0);
		RBOXAPI::HisFX3CloseDevice();
		gSystemLog.DisplayLogAndSave(L"HisFX3IsOpen faild", LV_EVENT);
		return 0;
	}
	dirPath.GetCurrentDir(cDir);

	char* c_strPath = T2A(gSystemMgr.m_sGeneralSetting.m_cstrProjectName.GetBuffer());
	sprintf(sensor_path, "%s\\recipe\\%s\\rlg.ini", cDir, c_strPath/*, recipedlg.RecipeName*/);
	dirPath.LoadKey(sensor_path, "HW_Sensor", NULL, RLGCamHWINI, sizeof(RLGCamHWINI) / sizeof(RLGCamHWINI[0]));
	dirPath.LoadKey(sensor_path, "HW_Sensor", NULL, RLGCamIMGINI, sizeof(RLGCamIMGINI) / sizeof(RLGCamIMGINI[0]));

	cstrLog.Format(L"sensor_path:%s", A2T(sensor_path));
	gSystemLog.DisplayLogAndSave(cstrLog.GetBuffer(), LV_EVENT);
	setConfigIni(sensor_path);
	ret = RBOXAPI::HisFX3StartPreview(&stParamPreviewCH1, 0);
	cstrLog.Format(L"StartPreview:%d", ret);//0:succeed
	gSystemLog.DisplayLogAndSave(cstrLog.GetBuffer(), LV_EVENT);
	if (ret != 0)
	{
		return 0;
	}
	return 1;
}

int Rolongo::run()
{
	ui64FrameIndex = 0, ui64SensorFrameIndex = 0;
	iresult = 0;
	uiFrameByteCount = 0;
	uiFrameByteCount = stParamPreviewCH1.iWidth *stParamPreviewCH1.iHeight * 2;
	iImgWidth = stParamPreviewCH1.iWidth;
	iImgHeight = stParamPreviewCH1.iHeight;
	nDataFormat = stParamPreviewCH1.dataFormat;
	return 1;
}

int Rolongo::cap(void)
{
	iresult = 0;

	DWORD dGrabStartTime = GetTickCount64();
	iresult = RBOXAPI::HisFX3GrabFrame(gSystemMgr.imgCap->bImgBuf, uiFrameByteCount, &nowIndex, &errFrame, &recSize, 0, 2000, 0);

	////iresult = HisFX3GrabFrame(pucRawBuffer, uiFrameByteCount, &nowIndex, &errFrame, &recSize, 0, 2000, 0);
	//Sleep(1);
	//logdlg.log("run result:%d,%d,%d,%d,%d", iresult, uiFrameByteCount, nowIndex, errFrame, recSize);
	return 1;
}

int Rolongo::stop()
{
	int rt = RBOXAPI::HisFX3StopPreview(NULL, 0);
	RBOXAPI::HisFX3CloseDevice();
	return 1;
}

int Rolongo::destroy()
{
	//RBOXAPI::HisFX3StopPreview();
	return 1;
}

int Rolongo::write_iic(void) {
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
				//err = Cam_WriteNormalI2CEx(iDevID, slave, addr, 1, subdata, 0);
				err = RBOXAPI::HisFX3WriteIIC(slave, addr, data[2], 0x0808);
				if (err != 0) {
					cstrLog.Format(L"write ini err line[%d]: %d", index, err);
					gSystemLog.DisplayLogAndSave(cstrLog.GetBuffer(), LV_EVENT);
					return FALSE;
				}
				Sleep(10);
			}
			else if (strstr(fpga, "fpga1")) { //16:8
				//logdlg.log("%s 0x%02x, 0x%04x, 0x%02x", fpga, data[0], data[1], data[2]);

				slave = data[0];
				addr = data[1];
				subdata[0] = data[2];
				//err = Cam_WriteNormalI2CEx(iDevID, slave, addr, 1, subdata, 2);
				err = RBOXAPI::HisFX3WriteIIC(slave, addr, data[2], 0x1608);
				if (err != 0) {
					cstrLog.Format(L"write ini err line[%d]: %d", index, err);
					gSystemLog.DisplayLogAndSave(cstrLog.GetBuffer(), LV_EVENT);
					return FALSE;
				}
				Sleep(10);
			}
			else if (strstr(fpga, "fpga2")) { //8:16
				//logdlg.log("%s 0x%02x, 0x%02x, 0x%04x", fpga, data[0], data[1], data[2]);

				slave = data[0];
				addr = data[1];
				subdata[0] = ((data[2] >> 8) & 0xff);
				subdata[1] = (data[2] & 0xff);
				//err = Cam_WriteNormalI2CEx(iDevID, slave, addr, 2, subdata, 1);
				err = RBOXAPI::HisFX3WriteIIC(slave, addr, data[2], 0x0816);
				if (err != 1) {
					cstrLog.Format(L"write ini err line[%d]: %d", index, err);
					gSystemLog.DisplayLogAndSave(cstrLog.GetBuffer(), LV_EVENT);
					return FALSE;
				}
				Sleep(10);
			}
			else if (strstr(fpga, "fpga3")) { //16:16
				//logdlg.log("%s 0x%02x, 0x%04x, 0x%04x", fpga, data[0], data[1], data[2]);
				slave = data[0];
				addr = data[1];
				subdata[0] = ((data[2] >> 8) & 0xff);
				subdata[1] = (data[2] & 0xff);
				//err = Cam_WriteNormalI2CEx(iDevID, slave, addr, 2, subdata, 3);
				err = RBOXAPI::HisFX3WriteIIC(slave, addr, data[2], 0x1616);
				if (err != 1) {
					cstrLog.Format(L"write ini err line[%d]: %d", index, err);
					gSystemLog.DisplayLogAndSave(cstrLog.GetBuffer(), LV_EVENT);
					return FALSE;
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

double Rolongo::CurrentTest()
{
	CString cstrLog;
	double current[10] = { 0 };
	int result = 0;
	//result = RBOXAPI::HisFX3MeasureBoxTotalCurrent(current);
	//cstrLog.Format(L"HisFX3MeasureBoxTotalCurrent:%.1f[%d]", current[0], result);
	//gSystemLog.DisplayLogAndSave(cstrLog.GetBuffer(), LV_EVENT);

	result = RBOXAPI::HisFX3MeasureCurrent(current, 0x01FF, 0);
	//cstrLog.Format(L"HisFX3MeasureCurrent[0]:%.1f[%d]", current[0], result);
	//gSystemLog.DisplayLogAndSave(cstrLog.GetBuffer(), LV_EVENT);
	//cstrLog.Format(L"HisFX3MeasureCurrent[1]:%.1f[%d]", current[1], result);
	//gSystemLog.DisplayLogAndSave(cstrLog.GetBuffer(), LV_EVENT);
	//cstrLog.Format(L"HisFX3MeasureCurrent[2]:%.1f[%d]", current[2], result);
	//gSystemLog.DisplayLogAndSave(cstrLog.GetBuffer(), LV_EVENT);
	//cstrLog.Format(L"HisFX3MeasureCurrent[3]:%.1f[%d]", current[3], result);
	//gSystemLog.DisplayLogAndSave(cstrLog.GetBuffer(), LV_EVENT);
	//cstrLog.Format(L"HisFX3MeasureCurrent[4]:%f[%d]", current[4], result);
	//gSystemLog.DisplayLogAndSave(cstrLog.GetBuffer(), LV_EVENT);
	//cstrLog.Format(L"HisFX3MeasureCurrent[5]:%.1f[%d]", current[5], result);
	//gSystemLog.DisplayLogAndSave(cstrLog.GetBuffer(), LV_EVENT);
	//cstrLog.Format(L"HisFX3MeasureCurrent[6]:%.1f[%d]", current[6], result);
	//gSystemLog.DisplayLogAndSave(cstrLog.GetBuffer(), LV_EVENT);
	//cstrLog.Format(L"HisFX3MeasureCurrent[7]:%.1f[%d]", current[7], result);
	//gSystemLog.DisplayLogAndSave(cstrLog.GetBuffer(), LV_EVENT);
	//cstrLog.Format(L"HisFX3MeasureCurrent[8]:%.1f[%d]", current[8], result);
	//gSystemLog.DisplayLogAndSave(cstrLog.GetBuffer(), LV_EVENT);
	//cstrLog.Format(L"HisFX3MeasureCurrent[9]:%.1f[%d]", current[9], result);
	//gSystemLog.DisplayLogAndSave(cstrLog.GetBuffer(), LV_EVENT);
	//RBOXAPI::HisFX3StopPreview();
	return current[4] * 0.001;
}
