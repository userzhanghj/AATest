#pragma once


// CAAControlDlg 对话框

class CAAControlDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAAControlDlg)

public:
	CAAControlDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CAAControlDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_AA };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	void ReadConfigIni();
	void SaveValueToConfig();

	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	afx_msg void OnBnClickedButtonSave();
	double m_dAngleLimitSpec;
	int m_nUVTime;
	int m_nCapWaitTime;
	double m_nPeakDiff;
	double m_nPeakSpec;
	double m_dPixelSize;
	int m_nReturnStep;
	int m_nSearchZCnt;
	double m_dSearchZSiepDis_1;
	double m_dSearchZSpec_1;
	double m_dSearchZSiepDis_2;
	double m_dSearchZSpec_2;
	int m_nAAStepCnt;
	double m_dAAStepDis;
	double m_dOffsetZ;
	BOOL m_bOpenOffset;
	int m_nPosTableX0;
	int m_nPosTableX1;
	int m_nPosTableZ0;
	int m_nPosTableZ1;
	int m_nPosTableZ2;
	int m_nPosX0;
	int m_nPosX1;
	int m_nPosY0;
	int m_nPosY1;
	int m_nPosZ0;
	int m_nPosZ1;
	int m_nPosXt0;
	int m_nPosXt1;
	int m_nPosYt0;
	int m_nPosYt1;
	int m_nStepWait;
	double m_dCenterPer;
	double m_dFieldSfrDiffSpec;
	double m_dCurrentLimit;
	double m_nDelay;
	BOOL m_bManual;
	BOOL OpenNGBaojing;
	afx_msg void OnBnClickedButton1();
	BOOL m_bOffsetXYFlag;
	CComboBox OffsetID;
	double OffsetX;
	double OffsetY;
	afx_msg void OnCbnSelchangeCombo2();
	BOOL UseMirrorFlag;
	BOOL OpenDongtaiFlag;
	BOOL ChartFlag;
	int ChartPos;
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	double CalibrationLimit;
	BOOL AAImgFlag;
	BOOL UVImgFlag;
	BOOL XFlag;
	BOOL YFlag;
};
