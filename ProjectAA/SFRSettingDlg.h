#pragma once


// CSFRSettingDlg 对话框

class CSFRSettingDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSFRSettingDlg)

public:
	CSFRSettingDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CSFRSettingDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SFR };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	void ReadConfigIni();
	void SaveEditValueToConfig();

	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	int m_nMtfPer;
	double m_dFreq;
	BOOL m_bUseMtf;
	BOOL m_bOpenFieldA;
	int m_nRoiW0;
	int m_nRoiH0;
	int m_nSearchW0;
	int m_nSearchH0;
	int m_nPattern0;
	int m_nDistance0;
	int m_nRoiW1;
	int m_nRoiH1;
	int m_nSearchW1;
	int m_nSearchH1;
	int m_nPattern1;
	int m_nDistance1;
	int m_nCenterSpec;
	double m_dAngleSpec;
	double m_dCenterSfrSpec;
	double m_dFieldASfrSpec;
	BOOL m_bLeft0;
	BOOL m_bLeft1;
	BOOL m_bLeft2;
	BOOL m_bLeft3;
	BOOL m_bLeft4;
	BOOL m_bTop0;
	BOOL m_bTop1;
	BOOL m_bTop2;
	BOOL m_bTop3;
	BOOL m_bTop4;
	BOOL m_bRight0;
	BOOL m_bRight1;
	BOOL m_bRight2;
	BOOL m_bRight3;
	BOOL m_bRight4;
	BOOL m_bButton0;
	BOOL m_bButton1;
	BOOL m_bButton2;
	BOOL m_bButton3;
	BOOL m_bButton4;
	int m_nBin0;
	int m_nBin1;
	int m_nBin2;
	int m_nBin3;
	int m_nBin4;
	BOOL m_bDisplay;
	CComboBox m_comboCount;
	int m_nStartX0;
	int m_nStartX1;
	int m_nStartX2;
	int m_nStartX3;
	int m_nStartX4;
	int m_nStartY0;
	int m_nStartY1;
	int m_nStartY2;
	int m_nStartY3;
	int m_nStartY4;
	afx_msg void OnBnClickedButtonSave();
	CSpinButtonCtrl m_spinStartX0;
	CSpinButtonCtrl m_spinStartX1;
	CSpinButtonCtrl m_spinStartX2;
	CSpinButtonCtrl m_spinStartX3;
	CSpinButtonCtrl m_spinStartX4;
	CSpinButtonCtrl m_spinStartY0;
	CSpinButtonCtrl m_spinStartY1;
	CSpinButtonCtrl m_spinStartY2;
	CSpinButtonCtrl m_spinStartY3;
	CSpinButtonCtrl m_spinStartY4;
	afx_msg void OnEnChangeEditStartX0();
	afx_msg void OnEnChangeEditStartX1();
	afx_msg void OnEnChangeEditStartX2();
	afx_msg void OnEnChangeEditStartX3();
	afx_msg void OnEnChangeEditStartX4();
	afx_msg void OnEnChangeEditStartY0();
	afx_msg void OnEnChangeEditStartY1();
	afx_msg void OnEnChangeEditStartY2();
	afx_msg void OnEnChangeEditStartY3();
	afx_msg void OnEnChangeEditStartY4();
	afx_msg void OnCbnSelchangeComboCount();
	afx_msg void OnBnClickedCheckDisplay();
	int m_nInitFlag = 0;
	int m_nCenterX;
	int m_nCenterY;
	BOOL m_bDrawLine;
	double m_dCenterSfrSpec2;
	double m_dFieldASfrSpec2;
};
