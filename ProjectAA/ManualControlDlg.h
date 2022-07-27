#pragma once


// CManualControlDlg 对话框

class CManualControlDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CManualControlDlg)

public:
	CManualControlDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CManualControlDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_CONTROL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	afx_msg void OnBnClickedButtonLightOn();
	afx_msg void OnBnClickedButton23();
	afx_msg void OnBnClickedButton24();
	afx_msg void OnBnClickedButton25();
	afx_msg void OnBnClickedButton26();
	afx_msg void OnBnClickedButton27();
	afx_msg void OnBnClickedButton28();
	afx_msg void OnBnClickedButtonXu();
	CEdit m_editStepDis;
	afx_msg void OnBnClickedButtonXd();
	afx_msg void OnBnClickedButtonYu();
	afx_msg void OnBnClickedButtonYd();
	afx_msg void OnBnClickedButtonZu();
	afx_msg void OnBnClickedButtonZd();
	afx_msg void OnBnClickedButtonXtu();
	afx_msg void OnBnClickedButtonXtd();
	afx_msg void OnBnClickedButtonYtu();
	afx_msg void OnBnClickedButtonYtd();
	afx_msg void OnBnClickedButtonTzu();
	afx_msg void OnBnClickedButtonTzd();
	afx_msg void OnBnClickedButtonTxu();
	afx_msg void OnBnClickedButtonTxd();
	afx_msg void OnBnClickedButtonStop();
	CComboBox m_comboPositionNum;
	afx_msg void OnBnClickedButtonMove();
	afx_msg void OnBnClickedButton29();
	afx_msg void OnBnClickedButton30();
	afx_msg void OnBnClickedButton31();
	afx_msg void OnBnClickedButton32();
	afx_msg void OnBnClickedButton33();
	afx_msg void OnBnClickedButton34();
	afx_msg void OnBnClickedButton35();
	afx_msg void OnBnClickedButton37();
	afx_msg void OnBnClickedButton38();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CStatic m_staticTableZ;
	CStatic m_staticTableX;
	CStatic m_staticAAX;
	CStatic m_staticAAY;
	CStatic m_staticAAZ;
	CStatic m_staticAAXt;
	CStatic m_staticAAYt;
	afx_msg void OnBnClickedButton39();
	afx_msg void OnBnClickedButton9();
	afx_msg void OnBnClickedButton10();
	afx_msg void OnBnClickedButton41();
	afx_msg void OnBnClickedButton40();
	afx_msg void OnBnClickedButton42();
	afx_msg void OnBnClickedButtonChart0();
	afx_msg void OnBnClickedButtonChart1();
	afx_msg void OnBnClickedButton44();
	afx_msg void OnBnClickedButton43();
	CStatic m_staticChartZ;
	afx_msg void OnBnClickedButton45();
	afx_msg void OnBnClickedCheck1();
	afx_msg void OnBnClickedCheck5();
	afx_msg void OnBnClickedCheck6();
	afx_msg void OnBnClickedCheck7();
	afx_msg void OnBnClickedCheck8();
	afx_msg void OnBnClickedCheck11();
	afx_msg void OnBnClickedCheck9();
	afx_msg void OnBnClickedCheck10();
};
