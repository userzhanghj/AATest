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

	//������ʾ
	int m_nCrtScreenWidth = 0;
	int m_nCrtScreenHeight = 0;


	//��ȡ�����ļ�
	CConfigIni               m_cGeneralSetting;
	GENERAL_SETTING m_sGeneralSetting;
	void GeneralSettingIniInit();
	void ReadGeneralSettingIni();//��ȡ�ͺ��ļ�������

	//CSocketServer m_cSocketServer;
	float                        m_fScreenX = 0.0f;
	float                        m_fScreenY = 0.0f;

    CFont                     m_logFont;
	CFont					  m_editFont;//����
	CWnd*                     m_ptrMainUI;
	CWnd*					  m_ptrMotorDlg;
	CConfigFileManager        m_cClientConfigIni;

	SITEDLG_TO_MOTORDLG   m_sSiteDlgToMotorDlg;//������趨λ��//���ڴ����趨AA��λ��
	void SetMotorPosToSiteDlg(CString cstrPos);

	wstring m_wstrSavePath = L"";

	CString GetCurrentExePath();//��ȡ��ǰ�ļ���ַ

	//**********************************************************************
	//MN200ģ������
	vector<CMotor> m_vCMotor;//�����
	BYTE m_nMotorDevNum;//���ģ������
	BYTE m_nIODevNum;//IOģ������

	void MotorReadConfig();
	void TotalMotorStop();
	bool HomeAll();//--------------------------------------------------------------------------------------������
	bool AllMotorHome();//
	bool CheckMotorHome();
	bool ChartMotorHome();//

	void StartGetMotorIoThread();
	unsigned int __stdcall GetMotorIoThread();
	void StartGetMotorEncoderThread();
	unsigned int __stdcall GetMotorEncoderThread();

	//**********************************************************************
	//IO����
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
	//ͼ��ɼ�-����
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

	int ChangeXY;//��ͷ��ת90��
	int SYMBOL1;//Ťת�Ƕ����
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
	double m_dSpecSfrUV[2];//UV���MTF����
	int m_nRoiEnable[5][4];
	int m_nStartX[5];
	int m_nStartY[5];
	int m_nBin[5];
	int m_bDisplay;
	int m_nTargetX;//���Ĺ��
	int m_nTargetY;

	double m_dCenterPer;//����Ȩ��
	double m_dFieldSfrDiffSpec;//���������Ȳ���
	double m_dPeakDis;
	double m_dFieldSfrDiff;
	double m_dCurrentLimit;  //��������
	double m_nDelay;  //AAǰ�ȴ���

	SlantedBW_SM FS;
	RECT SearchRT[SLANTED_BW_NUM];
	int FindTarget[SLANTED_BW_NUM];
	int CenterX[SLANTED_BW_NUM];
	int CenterY[SLANTED_BW_NUM];
	RECT RoiRT[SLANTED_BW_NUM][4];
	int EdgeX[SLANTED_BW_NUM][4];
	int EdgeY[SLANTED_BW_NUM][4];
	double SfrValue[SLANTED_BW_NUM][4];
	double SfrAvgValue[SLANTED_BW_NUM];//�洢ÿһ��ʶ���ƽ��SFR��ֵ		//TCP���ݵ�����
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
	double m_dCenterXDif;//�洢X��������ƫ��		//TCP���ݵ�����
	double m_dCenterYDif;//�洢Y��������ƫ��		//TCP���ݵ�����
	double TiltX;
	double TiltY;
	int SfrResult[SLANTED_BW_NUM][4];
	int TestResult;//���ս��				//TCP���ݵ�����
	int CenterTestResult;//���Ľ��
	int TiltTestResult;//�ǶȽ��
	int FieldSfrDifResult;

	int m_bDrawLine;//���ƻ�������
	int m_nLightValue;

	Convert changeImg;
	Paint pt;//������������
	HWND HWND_SFR_CURVE;
	COLORREF mycolor[SLANTED_BW_NUM][4] = {
		{RGB(255, 0, 0),	RGB(255, 62, 62),	RGB(255, 125, 125), RGB(255, 181, 181)},
		{RGB(0, 255, 0),	RGB(62, 255, 62),	RGB(125, 255, 125), RGB(181, 255, 181)},
		{RGB(0, 0, 255),	RGB(62, 62, 255),	RGB(125, 125, 255), RGB(181, 181, 255)},
		{RGB(160, 61, 153), RGB(193, 91, 186),	RGB(210, 136, 205), RGB(226, 177, 223)},
		{RGB(206, 139, 15), RGB(240, 174, 51),	RGB(244, 193, 100), RGB(248, 213, 148)}
	};

	int m_nNewCapImg = 1;//���ڼ���Ƿ��õ���һ֡ͼ��
	int m_nNewDataFlag = 1;//���ڼ���Ƿ��õ���һ֡����

	CWnd*					 m_ptrSFRSettingDlg;//���SFR���棬������ʾʶ�������
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
	//ͳ����Ϣ
	CConfigIni          m_cStateConfigIni;
	void StateConfigIniInit();
	void ReadStateConfigIni();
	void SaveStateConfigIni();

	int m_nAAAll;
	int m_nAAOK;
	int m_nAANG1;//����ͼ
	int m_nAANG2;//AANG
	int m_nAANG3;//UVNG
	double m_dAAOKPer;
	CString AATime;//��һ�����ʱ��


	//**********************************************************************
	//AA�˶�
	CConfigIni          m_cAAConfigIni;
	void AAConfigIniInit();
	void ReadAAConfigIni();
	void LoginConfigIniInit();
	void ReadLoginConfigIni();

	//ͼ��λ�����
	int ChartHomeFlag;//ͼ�����ԭ��־
	int ChartOpenFlag;//ͼ���Ὺ���´������������λ��
	int ChartPos;//ͼ��λ��
	int MoveChart();

	int m_nUVTime;
	int m_nCaptureWaitTime;
	double m_nPeakDiff;
	double m_nPeakMin;
	double m_dPixelSize;//�����س� mm
	int m_nReturnStepCnt;
	int m_nSearchZStepMaxCnt;
	double m_dSearchZStep_1;
	double m_dSearchZSpec_1;
	double m_dSearchZStep_2;
	double m_dSearchZSpec_2;
	int m_nAAStepMaxCnt;
	double m_dAAStep; //AA����
	double m_dAngleLimitSpec;//AA�����Ƕ�����
	double CalibrationLimit;//��������
	double m_dOffsetZ;//Z�Ჹ��
	int m_bOffsetFlag;

	int m_nStepWait;//����ȴ��������ȼ�����

	//�Ƿ񱣴�ͼƬ��ѡ��
	int AAImgFlag;
	int UVImgFlag;

	//�Ƕȵ��������趨
	int XFlag;
	int YFlag;

	int m_nPositionTableX[2];//�������λ	//��ȡλ	//AAλ
	int m_nPositionTableZ[3];//				//��ȫλ	//��ȡλ	//AAλ
	int m_nPositionX[2];//					//��ȡλ	//AAλ
	int m_nPositionY[2];
	int m_nPositionZ[2];
	int m_nPositionXt[2];
	int m_nPositionYt[2];

	int m_nAAStepCnt;//���ڼ�¼AA���ڲ���

	int m_bManualFlag = 0;
	int m_bManualDone = 0;
	int RestartAA = 0;//�����Զ�AA

	int OpenNGBaojing = 0;

	int UseMirrorFlag = 0;//ʹ�É��ྵ�ı�־

	int m_bOpenOffsetXY;
	double m_dOffsetX[20];
	double m_dOffsetY[20];

	//��̬Ȩ��
	int OpenDongtaiFlag;
	double DongtaiPos[5][2];//5��������	0:���	1:�Ҳ�
	double BackLeft;
	double BackRight;


	//double m_dOC_x[100][5];
	//double m_dOC_y[100][5];//���ڴ洢ÿһ��ʶ������꣬���ڼ���AA�Ƕ�
	void GetRotation(float alfa, float beta, float &theta, float &fai);
	int CalculateTiltXY(double step_unit);
	int CalculateTiltXY_Plane();
	int CalibrateTiltAngle();
	int CalibrateTiltAngle2();
	void DrawFocusCurve(vector < vector<double>> vdSfrValue);
	void get_curve_fitting(int factor_num, float * input_data, int length, float * output_data);//��������õ�
	double get_curve_fitting_d(int factor_num, float * input_data, int length, float * output_data, int cnt);//������ߣ�����peak��

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
	//���ݱ���
	double m_dPower;//����ֵ
	char SN[50];
	DirPath		m_dirPath;
	int SaveTestResult();//8��λ����
	void SaveTestReport2(BYTE *bmp, int img_w, int img_h, int type);//��ǰ�ģ��ֿ��洢
	void SaveMes(int glue,int capture, int result);//��ǰ��
	BOOL save_drawing_image(HWND hdlg, char *img_path);//���ڴ�ؼ���ʾ��ͼƬ
	BOOL save_drawing_image_jpg(HWND hdlg, char *img_path);//���ڴ�ؼ���ʾ��ͼƬ

	void SaveTestReport3(BYTE *bmp, int img_w, int img_h);//AA �� UV�� �������Ƚ����һ��
	void SaveImg(BYTE *bmp, int img_w, int img_h, int type);//AA �� UV�� �������Ƚ����һ��

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


	WORD	m_nCard;//�������ƿ���

	//***************************
	//LOGIN
	LOGIN_INFO m_sLoginInfo;
	CConfigIni m_cLoginConfigIni;


	//**********************************************************************
	//RFID - RS232����
	//��ȡrfid��Ϣ
	char output[2000];
	char output2[2000];
	int outInt[2000] = { 0 };

	BYTE Read_Rfid[8] = { 0x02, 0x03, 0x00, 0x0A, 0x00, 0x05, 0xA5, 0xF8 };//

	BYTE Read_SN[8] = { 0x02, 0x03, 0x00, 0x10, 0x00, 0x19, 0x85, 0xF6 };//

	BYTE Next_10[8] = { 0x02, 0x06, 0x00, 0x0B, 0x00, 0x0A, 0x78, 0x3C };//Ŀ�� 10

	BYTE CameraIn_0[8] = { 0x02, 0x06, 0x00, 0x0C, 0x00, 0x00, 0x49, 0xFA };//�޲�Ʒ
	BYTE CameraIn_1[8] = { 0x02, 0x06, 0x00, 0x0C, 0x00, 0x01, 0x88, 0x3A };//�в�Ʒ

	BYTE Result_0[8] = { 0x02, 0x06, 0x00, 0x0D, 0x00, 0x00, 0x18, 0x3A };//NG
	BYTE Result_1[8] = { 0x02, 0x06, 0x00, 0x0D, 0x00, 0x01, 0xD9, 0xFA };//OK

	BYTE NG_00[8] = { 0x02, 0x06, 0x00, 0x0E, 0x00, 0x00, 0xE8, 0x3A };//NG 00	- �����������NGվ��
	BYTE NG_30[8] = { 0x02, 0x06, 0x00, 0x0E, 0x00, 0x1E, 0x68, 0x32 };//NG 30

	int m_nComNo2;
	int m_nComPort2;
	int m_bAutoFlag_RS232;
	int m_nPassRfidFlag;//����rfid

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

	//�̿ص�Դ
	RS232 m_cPower;
	int m_nPowerPort;
	int m_nPowerBaudrate;
	int m_nPowerLinked;
	int m_nPowerFlag;

	double current_limit[3];
	double voltage_val[3];
	double m_fPowerCurrentVal[3];//��¼3·����ֵ
	void StartPowerLinkThread();
	unsigned int __stdcall PowerLinkThread();

	double PowerDiff = 0;//���ڱ���δ��ͼʱ�ɼ�������

	//**********************************************************************
	//�Զ�����
	int m_bAutoAAFlag = 0;//40վ�Զ���־

	void StartAutoAAThread();
	unsigned int __stdcall AutoAAThread();
	unsigned int __stdcall AutoRightThread();

	//**********************************************************************
	//��ɫ��״̬
	int m_nLightMode = 0;//������ɫ��״̬
	void StartLightControlThread();
	unsigned int __stdcall LightControlThread();


	//**********************************************************************
	//һЩ��������߳�
	int m_bRfidLinkFlag = 0;

	void StartOtherControlThread();
	unsigned int __stdcall OtherControlThread();

	//��ͣ + ������
	BOOL   m_bEmergencyStopFlag = FALSE;//��ͣ������True
	int m_bMotorErrorFlag = 0;
	BOOL   m_bHomeFlag = 0;//�ȸ��˻�ԭλ��־
	int m_nAAErrorCode = 0;
	char*				m_cErrorMsg[100];
	void ReadErrorListIni();


	//**********************************************************
	//���Ȳ���
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

