#pragma once


// CIOControlDlg 对话框

class CIOControlDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CIOControlDlg)

public:
	CIOControlDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CIOControlDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1_IO };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	void SetIoStatus();
	void ChangeIoTextIn();
	void ChangeIoTextOut();

	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	afx_msg void OnClose();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedOption(UINT nID);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
