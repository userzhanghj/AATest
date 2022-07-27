#pragma once


// CCountDlg 对话框

class CCountDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCountDlg)

public:
	CCountDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CCountDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_COUNT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	virtual void OnCancel();
};
