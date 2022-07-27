#ifndef HISFX3CCMALG_H
#define HISFX3CCMALG_H

#include <string>


#ifdef HISFX3CCMALG_LIB
# define HISFX3CCMALG_EXPORT __declspec(dllexport)
#else
# define HISFX3CCMALG_EXPORT __declspec(dllimport)
#endif

#define _His_MAX_BLOCK_COUNT					25
#define _His_MAX_DATABASE_PROJECT		9




class HISFX3CCMALG_EXPORT CHisFX3CCMAlg
{
public:
	CHisFX3CCMAlg(void);
	~CHisFX3CCMAlg(void);

	const wchar_t* GetLastError(void);
	void ClearError(void);

	void raw10toraw8(unsigned short* pusRaw10, unsigned char* pucRaw8, int iwidth, int iheight);
	void raw8toraw10( unsigned char* pucRaw8, unsigned short* pusRaw10, int iwidth, int iheight);
	void raw12toraw8(unsigned short* pusRaw12, unsigned char* pucRaw8, int iwidth, int iheight);
	void raw8toraw12( unsigned char* pucRaw8, unsigned short* pusRaw12, int iwidth, int iheight);
	void raw12toraw10(unsigned short* pusRaw12, unsigned short* pusRaw10, int iwidth, int iheight);
	void raw10toraw12(unsigned short* pusRaw10, unsigned short* pusRaw12, int iwidth, int iheight);
	int HisCCMYUV2RGB24(unsigned char* pucYUV, unsigned char* pucRGB24, unsigned int uiWidth, unsigned int uiHeight, unsigned char ucFormat, unsigned int uiFlag=0x0);
	int HisCCMBarlor2RGB24(unsigned char* pucRaw, unsigned char* pucRGB24, int iWidth, int iHeight, unsigned char ucBaylor, unsigned char ucAlg = 0);
	

private:


private:
	int isfrbin;
	double* pdflsfrwindow;
	double* pdflsfrdftcos;
	double* pdflsfrdftsin;
	void* classMiddle;
	//_HisAlg_LSCHA_Template stLSCHATemplateC1;
	//_HisAlg_LSCHA_Template stLSCHATemplateC2;
	std::wstring wstrLastError;

	bool bHisFX3PlatformConstruct;
};

#endif // HISFX3CCMALG_H
