#pragma once


// CRS232SetDlg 对话框

class CRS232SetDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CRS232SetDlg)

public:
	CRS232SetDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CRS232SetDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_COM };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	void ReadConfigIni();
	void SaveValueToConfig();

	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	int m_nComNo2;
	int m_nPort2;
	char input[2] = { 'U', 'U' };
	char output[150];
	afx_msg void OnBnClickedButtonSave();
	afx_msg void OnBnClickedButtonConnect2();
	afx_msg void OnBnClickedButton3();
	BOOL m_BRs232Auto;
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton7();
	BOOL m_nLinkFlag;
	int m_nPowerCom;
	int m_nPowerPort;
	double m_fValSet0;
	double m_fCurrentSet0;
	double m_fValSet1;
	double m_fCurrentSet1;
	BOOL m_bPassRfid;
};
