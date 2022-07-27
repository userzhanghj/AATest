#pragma once

#include <vector>
#include <string>
#include <map>
#include <memory>
#include <mutex>
#include <atomic>
#include <thread>
#include <future>
#include <type_traits>
#include <boost/circular_buffer.hpp>
#include <iostream>
#include <unordered_map>
#include <stdlib.h>
#include <queue>
#include "TypeDef.h"
#include "Motor.h"
#include "resource.h"
#include "ConfigFileManager.h"
#include "ConfigIni.h"
#include"Capture.h"
#include"Image.h"
#include"IO.h"
#include"Rs232Com.h"

using namespace std;
#define POS_COUNT		7

class CSystemManager
{
public:
	CSystemManager();
	~CSystemManager();

	bool DMC3800Init();

	int DMCMotorInit();

	int m_nExitFlag = 0;//???

	//更新显示
	int m_nCrtScreenWidth = 0;
	int m_nCrtScreenHeight = 0;


	//读取配置文件
	CConfigIni               m_cGeneralSetting;
	GENERAL_SETTING m_sGeneralSetting;
	void GeneralSettingIniInit();
	void ReadGeneralSettingIni();//读取型号文件名配置

	//CSocketServer m_cSocketServer;
	float                        m_fScreenX = 0.0f;
	float                        m_fScreenY = 0.0f;

    CFont                     m_logFont;
	CFont					  m_editFont;//字体
	CWnd*                     m_ptrMainUI;
	CWnd*					  m_ptrMotorDlg;
	CConfigFileManager        m_cClientConfigIni;

	SITEDLG_TO_MOTORDLG   m_sSiteDlgToMotorDlg;//轴界面设定位置//用于传递设定AA点位？
	void SetMotorPosToSiteDlg(CString cstrPos);

	wstring m_wstrSavePath = L"";

	CString GetCurrentExePath();//获取当前文件地址

	//**********************************************************************
	//MN200模块数量
	vector<CMotor> m_vCMotor;//电机轴
	BYTE m_nMotorDevNum;//电机模块数量
	BYTE m_nIODevNum;//IO模块数量

	void MotorReadConfig();
	void TotalMotorStop();
	bool HomeAll();//--------------------------------------------------------------------------------------待完善
	bool AllMotorHome();//
	bool CheckMotorHome();
	bool ChartMotorHome();//

	void StartGetMotorIoThread();
	unsigned int __stdcall GetMotorIoThread();
	void StartGetMotorEncoderThread();
	unsigned int __stdcall GetMotorEncoderThread();

	//**********************************************************************
	//IO控制
	DWORD m_wDOVal[3];
	DWORD m_wDIVal[3];
	CIo   m_cIo;
	WORD m_nCanLink = false;

	int  S00 = OFF; int  S16 = OFF;
	int  S01 = OFF; int  S17 = OFF;
	int  S02 = OFF; int  S18 = OFF;
	int  S03 = OFF; int  S19 = OFF;
	int  S04 = OFF; int  S20 = OFF;
	int  S05 = OFF; int  S21 = OFF;
	int  S06 = OFF; int  S22 = OFF;
	int  S07 = OFF; int  S23 = OFF;
	int  S08 = OFF; int  S24 = OFF;
	int  S09 = OFF; int  S25 = OFF;
	int  S10 = OFF; int  S26 = OFF;
	int  S11 = OFF; int  S27 = OFF;
	int  S12 = OFF; int  S28 = OFF;
	int  S13 = OFF; int  S29 = OFF;
	int  S14 = OFF; int  S30 = OFF;
	int  S15 = OFF; int  S31 = OFF;

	int  Y00 = OFF; int  Y16 = OFF;
	int  Y01 = OFF; int  Y17 = OFF;
	int  Y02 = OFF; int  Y18 = OFF;
	int  Y03 = OFF; int  Y19 = OFF;
	int  Y04 = OFF; int  Y20 = OFF;
	int  Y05 = OFF; int  Y21 = OFF;
	int  Y06 = OFF; int  Y22 = OFF;
	int  Y07 = OFF; int  Y23 = OFF;
	int  Y08 = OFF; int  Y24 = OFF;
	int  Y09 = OFF; int  Y25 = OFF;
	int  Y10 = OFF; int  Y26 = OFF;
	int  Y11 = OFF; int  Y27 = OFF;
	int  Y12 = OFF; int  Y28 = OFF;
	int  Y13 = OFF; int  Y29 = OFF;
	int  Y14 = OFF; int  Y30 = OFF;
	int  Y15 = OFF; int  Y31 = OFF;

	//**********************************************************************
	//图像采集-测试
	//bounded_buffer<Mat>				    m_bAngleAlgoMat;
	CConfigIni          m_cCaptureConfigIni;
	void CaptureConfigIniInit();
	void ReadCaptureConfigIni();
	int m_nImageSource = 0;
	int m_nTestMode = 0;
	int m_nCaptureMode = 0;
	int m_nImageChangeMode = 0;
	int m_bWriteIIC = 0;
	int m_bMirrorX = 0;
	int m_bMirrorY = 0; 
	int m_nCtsId;

	int ChangeXY;//镜头旋转90度
	int SYMBOL1;//扭转角度相关
	int SYMBOL2;

	int CameraDsH;
	int CameraDsW;

	int m_bGpioFlag;
	int m_nGpioNo;

	bool m_bStopCapture = 1;
	bool m_bStartCapture = 0;
	//bool m_bInitFlag = 0;
	ImgCap *imgCap; 
	ImgFile imgFile;
	int m_bCTSInitFlag = 0;
	CTS imgCTS;
	Rolongo imgRLG;
	CameraDs imgCDS;
	OutputImage ShowImg;
	//sfr-test
	int m_bUseMTF;
	int m_bOpenFieldA;
	int m_nMtfPer;
	double m_dFreq;
	int m_nRoiW[2];
	int m_nRoiH[2];
	int m_nSearchW[2];
	int m_nSearchH[2];
	int m_nPattern[2];
	int m_nDistance[2];
	int m_nSpecCenter;//OCLimit
	double m_dSpecAAAngle;//m_fTiltSpec
	double m_dSpecSfr[2];//m_nSfrSpec
	int UVTestFlag = 0;
	double m_dSpecSfrUV[2];//UV后的MTF测试
	int m_nRoiEnable[5][4];
	int m_nStartX[5];
	int m_nStartY[5];
	int m_nBin[5];
	int m_bDisplay;
	int m_nTargetX;//中心规格
	int m_nTargetY;

	double m_dCenterPer;//中心权重
	double m_dFieldSfrDiffSpec;//四周清晰度差异
	double m_dPeakDis;
	double m_dFieldSfrDiff;
	double m_dCurrentLimit;  //电流下限
	double m_nDelay;  //AA前等待秒

	SlantedBW_SM FS;
	RECT SearchRT[SLANTED_BW_NUM];
	int FindTarget[SLANTED_BW_NUM];
	int CenterX[SLANTED_BW_NUM];
	int CenterY[SLANTED_BW_NUM];
	RECT RoiRT[SLANTED_BW_NUM][4];
	int EdgeX[SLANTED_BW_NUM][4];
	int EdgeY[SLANTED_BW_NUM][4];
	double SfrValue[SLANTED_BW_NUM][4];
	double SfrAvgValue[SLANTED_BW_NUM];//存储每一个识别框平均SFR的值		//TCP传递的数据
	double OCSlope[SLANTED_BW_NUM][4];
	double OCOffset[SLANTED_BW_NUM][4];
	double Slope[SLANTED_BW_NUM][4];
	double Offset[SLANTED_BW_NUM][4];
	double ESF[SLANTED_BW_NUM][4][2000];
	double LSF[SLANTED_BW_NUM][4][2000];
	double Freq[SLANTED_BW_NUM][4][1000];
	double AMP[SLANTED_BW_NUM][4][1000];
	double EdgeVX[SLANTED_BW_NUM][4][200];
	double EdgeVY[SLANTED_BW_NUM][4][200];
	double EdgeHX[SLANTED_BW_NUM][4][200];
	double EdgeHY[SLANTED_BW_NUM][4][200];
	double OCx[SLANTED_BW_NUM];
	double OCy[SLANTED_BW_NUM];
	double m_dCenterXDif;//存储X方向像素偏差		//TCP传递的数据
	double m_dCenterYDif;//存储Y方向像素偏差		//TCP传递的数据
	double TiltX;
	double TiltY;
	int SfrResult[SLANTED_BW_NUM][4];
	int TestResult;//最终结果				//TCP传递的数据
	int CenterTestResult;//中心结果
	int TiltTestResult;//角度结果
	int FieldSfrDifResult;

	int m_bDrawLine;//控制画辅助线
	int m_nLightValue;

	Convert changeImg;
	Paint pt;//画主界面曲线
	HWND HWND_SFR_CURVE;
	COLORREF mycolor[SLANTED_BW_NUM][4] = {
		{RGB(255, 0, 0),	RGB(255, 62, 62),	RGB(255, 125, 125), RGB(255, 181, 181)},
		{RGB(0, 255, 0),	RGB(62, 255, 62),	RGB(125, 255, 125), RGB(181, 255, 181)},
		{RGB(0, 0, 255),	RGB(62, 62, 255),	RGB(125, 125, 255), RGB(181, 181, 255)},
		{RGB(160, 61, 153), RGB(193, 91, 186),	RGB(210, 136, 205), RGB(226, 177, 223)},
		{RGB(206, 139, 15), RGB(240, 174, 51),	RGB(244, 193, 100), RGB(248, 213, 148)}
	};

	int m_nNewCapImg = 1;//用于监控是否拿到新一帧图像
	int m_nNewDataFlag = 1;//用于监控是否拿到新一帧数据

	CWnd*					 m_ptrSFRSettingDlg;//存放SFR界面，用于显示识别框内容
	Output SfrShowImg;
	int m_bDisplayFlag;
	int m_nDisplayCnt;

	void SfrTest(BYTE *img, BYTE *bmp, int w, int h);
	int FindRoiHEdge(const BYTE *roi, int start_x, int start_y, int w, int h, double *edge_y, double &slope, double &offset, int &bottom_black);
	int FindRoiVEdge(const BYTE *roi, int start_x, int start_y, int w, int h, double *edge_y, double &slope, double &offset, int &bottom_black);
	int GetRoiWbLeftRightOrder(const BYTE *roi, int w, int h);
	int GetRoiWbBottomTopOrder(const BYTE *roi, int w, int h);
	double GetBinaryImageEdgeLine(const BYTE *line, int num, int start_black);
	int GetBestFitLine(const double *x, const double *y, int n, double &slope, double &offset);
	void DrawSFRCurve(int x_cnt);
	void DrawTestResultChart(HDC memdc);

	void StartCaptureThread();
	unsigned int __stdcall CaptureThread();
	void StartImageTestThread();
	unsigned int __stdcall ImageTestThread();

	//**********************************************************************
	//统计信息
	CConfigIni          m_cStateConfigIni;
	void StateConfigIniInit();
	void ReadStateConfigIni();
	void SaveStateConfigIni();

	int m_nAAAll;
	int m_nAAOK;
	int m_nAANG1;//不出图
	int m_nAANG2;//AANG
	int m_nAANG3;//UVNG
	double m_dAAOKPer;
	CString AATime;//上一次清空时间


	//**********************************************************************
	//AA运动
	CConfigIni          m_cAAConfigIni;
	void AAConfigIniInit();
	void ReadAAConfigIni();
	void LoginConfigIniInit();
	void ReadLoginConfigIni();

	//图卡位置相关
	int ChartHomeFlag;//图卡轴回原标志
	int ChartOpenFlag;//图卡轴开启新打开软件会重新找位置
	int ChartPos;//图卡位置
	int MoveChart();

	int m_nUVTime;
	int m_nCaptureWaitTime;
	double m_nPeakDiff;
	double m_nPeakMin;
	double m_dPixelSize;//单像素长 mm
	int m_nReturnStepCnt;
	int m_nSearchZStepMaxCnt;
	double m_dSearchZStep_1;
	double m_dSearchZSpec_1;
	double m_dSearchZStep_2;
	double m_dSearchZSpec_2;
	int m_nAAStepMaxCnt;
	double m_dAAStep; //AA步长
	double m_dAngleLimitSpec;//AA调整角度上限
	double CalibrationLimit;//单次上限
	double m_dOffsetZ;//Z轴补偿
	int m_bOffsetFlag;

	int m_nStepWait;//步间等待，还是先加上了

	//是否保存图片的选项
	int AAImgFlag;
	int UVImgFlag;

	//角度调整方向设定
	int XFlag;
	int YFlag;

	int m_nPositionTableX[2];//各个轴点位	//夹取位	//AA位
	int m_nPositionTableZ[3];//				//安全位	//夹取位	//AA位
	int m_nPositionX[2];//					//夹取位	//AA位
	int m_nPositionY[2];
	int m_nPositionZ[2];
	int m_nPositionXt[2];
	int m_nPositionYt[2];

	int m_nAAStepCnt;//用于记录AA调节步数

	int m_bManualFlag = 0;
	int m_bManualDone = 0;
	int RestartAA = 0;//重新自动AA

	int OpenNGBaojing = 0;

	int UseMirrorFlag = 0;//使用増距镜的标志

	int m_bOpenOffsetXY;
	double m_dOffsetX[20];
	double m_dOffsetY[20];

	//动态权重
	int OpenDongtaiFlag;
	double DongtaiPos[5][2];//5个搜索框	0:左侧	1:右侧
	double BackLeft;
	double BackRight;


	//double m_dOC_x[100][5];
	//double m_dOC_y[100][5];//用于存储每一步识别的坐标，用于计算AA角度
	void GetRotation(float alfa, float beta, float &theta, float &fai);
	int CalculateTiltXY(double step_unit);
	int CalculateTiltXY_Plane();
	int CalibrateTiltAngle();
	int CalibrateTiltAngle2();
	void DrawFocusCurve(vector < vector<double>> vdSfrValue);
	void get_curve_fitting(int factor_num, float * input_data, int length, float * output_data);//拟合曲线用到
	double get_curve_fitting_d(int factor_num, float * input_data, int length, float * output_data, int cnt);//拟合曲线，返回peak点

	bool AAMoveStepZ(double dFocusPos);

	int MoveOffsetZ(double dFocusPos);
	int MoveStepXY(double stepx, double stepy);
	int MoveStepXtYt(double stepxt, double stepyt);
	int PickLens();
	int LoadLens();
	int SearchZ(void);
	int MoveCenter(void);
	int FocusScan(void);
	int FocusScan2(void);

	//**********************************************************************
	//数据保存
	double m_dPower;//电流值
	char SN[50];
	DirPath		m_dirPath;
	int SaveTestResult();//8工位程序
	void SaveTestReport2(BYTE *bmp, int img_w, int img_h, int type);//以前的，分开存储
	void SaveMes(int glue,int capture, int result);//以前的
	BOOL save_drawing_image(HWND hdlg, char *img_path);//用于存控件显示的图片
	BOOL save_drawing_image_jpg(HWND hdlg, char *img_path);//用于存控件显示的图片

	void SaveTestReport3(BYTE *bmp, int img_w, int img_h);//AA 和 UV后 的清晰度结果存一起
	void SaveImg(BYTE *bmp, int img_w, int img_h, int type);//AA 和 UV后 的清晰度结果存一起

	void Uppercase(char *str);
	BOOL SearchDirectory(const char *path, const char *name);
	void GetCurrentDirectory2(char *path);
	int CreateReportFile(const char *test_item_str, char *target_report_folder_path, char *target_folder_name);
	int CreateMesFile(const char *test_item_str, char *target_report_folder_path, char *target_folder_name);
	HANDLE CreateDefinePathCsv(const char *path);
	BOOL WriteCsv(HANDLE hfile, const char *format, ...);


	//button-value
	int m_nButtonValue = 0;
	int m_nButtonDone = 0;
	void StartScanButtonValueThread();
	unsigned int __stdcall ScanButtonValueThread();


	WORD	m_nCard;//雷赛控制卡号

	//***************************
	//LOGIN
	LOGIN_INFO m_sLoginInfo;
	CConfigIni m_cLoginConfigIni;


	//**********************************************************************
	//RFID - RS232串口
	//读取rfid信息
	char output[2000];
	char output2[2000];
	int outInt[2000] = { 0 };

	BYTE Read_Rfid[8] = { 0x02, 0x03, 0x00, 0x0A, 0x00, 0x05, 0xA5, 0xF8 };//

	BYTE Read_SN[8] = { 0x02, 0x03, 0x00, 0x10, 0x00, 0x19, 0x85, 0xF6 };//

	BYTE Next_10[8] = { 0x02, 0x06, 0x00, 0x0B, 0x00, 0x0A, 0x78, 0x3C };//目标 10

	BYTE CameraIn_0[8] = { 0x02, 0x06, 0x00, 0x0C, 0x00, 0x00, 0x49, 0xFA };//无产品
	BYTE CameraIn_1[8] = { 0x02, 0x06, 0x00, 0x0C, 0x00, 0x01, 0x88, 0x3A };//有产品

	BYTE Result_0[8] = { 0x02, 0x06, 0x00, 0x0D, 0x00, 0x00, 0x18, 0x3A };//NG
	BYTE Result_1[8] = { 0x02, 0x06, 0x00, 0x0D, 0x00, 0x01, 0xD9, 0xFA };//OK

	BYTE NG_00[8] = { 0x02, 0x06, 0x00, 0x0E, 0x00, 0x00, 0xE8, 0x3A };//NG 00	- 用于清空拖盘NG站号
	BYTE NG_30[8] = { 0x02, 0x06, 0x00, 0x0E, 0x00, 0x1E, 0x68, 0x32 };//NG 30

	int m_nComNo2;
	int m_nComPort2;
	int m_bAutoFlag_RS232;
	int m_nPassRfidFlag;//跳过rfid

	RS232 m_cRfidComm2;//:AA
	int Com2ConnectFlag = 0;

	CConfigIni          m_cRS232ConfigIni;
	void RS232ConfigIniInit();
	void ReadRS232ConfigIni();

	int Char2Num(unsigned char* c, int* num, int size);
	int Char2Char(unsigned char* c, char* num, int size);

	RFID_MSG m_cRfidAA;

	void StartRS232LinkThread();
	unsigned int __stdcall RS232LinkThread();

	//程控电源
	RS232 m_cPower;
	int m_nPowerPort;
	int m_nPowerBaudrate;
	int m_nPowerLinked;
	int m_nPowerFlag;

	double current_limit[3];
	double voltage_val[3];
	double m_fPowerCurrentVal[3];//记录3路电流值
	void StartPowerLinkThread();
	unsigned int __stdcall PowerLinkThread();

	double PowerDiff = 0;//用于保留未出图时采集卡电流

	//**********************************************************************
	//自动流程
	int m_bAutoAAFlag = 0;//40站自动标志

	void StartAutoAAThread();
	unsigned int __stdcall AutoAAThread();
	unsigned int __stdcall AutoRightThread();

	//**********************************************************************
	//三色灯状态
	int m_nLightMode = 0;//控制三色灯状态
	void StartLightControlThread();
	unsigned int __stdcall LightControlThread();


	//**********************************************************************
	//一些杂项控制线程
	int m_bRfidLinkFlag = 0;

	void StartOtherControlThread();
	unsigned int __stdcall OtherControlThread();

	//急停 + 报错监控
	BOOL   m_bEmergencyStopFlag = FALSE;//急停按下是True
	int m_bMotorErrorFlag = 0;
	BOOL   m_bHomeFlag = 0;//先改了回原位标志
	int m_nAAErrorCode = 0;
	char*				m_cErrorMsg[100];
	void ReadErrorListIni();


	//**********************************************************
	//亮度测试
	CConfigIni          m_cLightConfigIni;
	void LightConfigIniInit();
	void ReadLightConfigIni();
	int LightnessFlag;
	int LightX[5];
	int LightY[5];
	int LightRoiW;
	int LightRoiH;
	int LightSpec[5];

	int LightTestResult;
	float LightValue[5];
	int LightValueResult[5];
	int LightTest(BYTE *bmp, int imgW, int imgH);



private:

	std::vector<HANDLE> m_vWorkerThread;
	union UI_Proc
	{
		unsigned(_stdcall * ThreadProc)(void*);
		unsigned(_stdcall CSystemManager::*MemProc)();
	} ProcMotor3, ProcGetMotorIo, ProcGetMotorEncoder, ProcCapture, ProcImageTest, ProcSocket,
		ProcAutoWhite, ProcAutoAA, ProcAutoRight, ProcLight, ProcScanBtn, ProcOther, ProcRS232Link, ProcAutoAATest,
		ProcAutoAA2, ProcRS232Receive, ProcPowerLink,CanLInk;

};

