#pragma once
#include <string>
#include "TypeDef.h"

//image source
#define IMG_DEV_FILE						0
#define IMG_DEV_CTS						1
#define IMG_RO_LONGO		2
#define IMG_CameraDS		3


//test item
#define SHOW_IMAGE			0
#define SFR_TEST			1

//display model
#define LOOP_MODEL			1
#define CHECK_MODEL			0

class ImgCap {
public:
	int iDevID;

	virtual BOOL init(void) { return true; }
	virtual int run(void) { return true; }
	virtual int cap(void) { return true; }
	virtual int stop(void) { release(); return true; }

	virtual void SetInitFlag(bool flag) { this->m_bInitFlag = flag; }
	virtual bool GetInitFlag() { return this->m_bInitFlag; }
	BYTE *bImgBuf = new BYTE[16000000];
	BYTE *bBmpBuf = new BYTE[16000000];
	BYTE *bBmpTestBuf = new BYTE[16000000];

	int iImgWidth;
	int iImgHeight;
	int iImgDepth = 3;
	int iBmpW = 1280;
	int iBmpH = 960;
	int iBmpD = 3;
	void release(void);
	bool m_bInitFlag = false;
	bool InitDoneFlag = false;
	int nDataFormat;

private:
};
//extern ImgCap *imgCap;

class ImgFile :public ImgCap {
public:
	BOOL OpenFile(HWND hdlg, char * path, int type);
	BOOL ReadBMPFile(const char * bmp_path, BYTE * bmp_source, int & bmp_w, int & bmp_h, int & bmp_channel);
	virtual BOOL init(void);
	virtual int run(void);
	virtual int cap(void);
	virtual int stop(void);

	virtual void SetInitFlag(bool flag) { this->m_bInitFlag = flag; }
	virtual bool GetInitFlag() { return this->m_bInitFlag; }
	bool m_bInitFlag = false;
private:
	char cImgPath[MAX_PATH] = { 0 };
	PALETTE pal[256];

};
//extern ImgFile imgFile;

class CTS :public ImgCap {
public:
	int iDevID;
	virtual BOOL init(void);
	virtual int run(void);
	virtual int cap(void);
	virtual int stop(void);
	virtual int destroy(void);
	BOOL WaitForFirstFrameArrived(DWORD devInst);
	int write_iic(void);
	bool m_bInitFlag = false;
	DirPath		dirPath;

	int initdone = 0;
	int write_iic_center(void);
	BYTE dataformat = 1; // 0:RAW8,1: YUV422, 2:MJPGorRGB24, 3:MIPIRAW10,4:DVPRAW10,5:MIPIRAW12				
	BYTE displayformat = 1; //0: RAW8, 1:RGB24
	BYTE BayerOrder = 1; // 0:RG_GB, 1:GR_BG, 2:GB_RG, 3:BG_GR
private:
	char sensorPath[MAX_PATH];
	char cDir[MAX_PATH];
	char sensor_name[100] = { 0 };

};
//extern CTS CTSCam;

class Rolongo :public ImgCap
{
public:
	virtual int init(void);
	virtual int run(void);
	virtual int cap(void);

	virtual int stop(void);
	virtual int destroy(void);
	DirPath		dirPath;

	int write_iic(void);
	double CurrentTest();
private:
	char sensorPath[MAX_PATH];
	char cDir[MAX_PATH];
	unsigned __int64 ui64FrameIndex, ui64SensorFrameIndex;
	int iresult;
	unsigned int nowIndex, recSize;
	bool errFrame;
	unsigned int uiFrameByteCount;
	int dev_id;
	char sensor_path[MAX_PATH];
};

class CameraDs :public ImgCap
{
public:
	virtual int init(void);
	virtual int run(void);
	virtual int cap(void);

	virtual int stop(void);
	virtual int destroy(void);
private:
	int iDevID;
};

