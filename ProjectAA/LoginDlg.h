#pragma once


// CLoginDlg 对话框

class CLoginDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CLoginDlg)

public:
	CLoginDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CLoginDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_LOGIN };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_cUserName = nullptr;
	CString m_cPassward;
	CString m_cNewPassword;
	CString m_cUserNameCorrect;
	CString m_cPasswordCorrect;
	BOOL OnInitDialog();
	BOOL ModeFlag = 0;

	void EnableControl(BOOL nflag);
	void ReadLoginConfig();

	afx_msg void OnBnClickedButtonLogin();
	afx_msg void OnCbnSelchangeComboModeChoose();
	afx_msg void OnBnClickedButtonQuit();
	afx_msg void OnBnClickedButtonNewPassward();
	afx_msg void OnClose();
	afx_msg void OnBnClickedButton1();
	CString NewID;
	CString NewPassword;
};
