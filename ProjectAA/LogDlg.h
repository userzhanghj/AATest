#pragma once


// CLogDlg 对话框

class CLogDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CLogDlg)

public:
	CLogDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CLogDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_LOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	virtual void OnCancel();
public:
	virtual BOOL OnInitDialog();

	afx_msg LRESULT OnReceiveAndDisplaySystemLog(WPARAM wParam, LPARAM lParam);
	afx_msg void OnNMCustomdrawListLog(NMHDR *pNMHDR, LRESULT *pResult);
	circular_buffer<LOG_PACKAGE>   m_logBuffer;



	void SetUiHandle();
	afx_msg void OnLvnItemchangedListLog(NMHDR *pNMHDR, LRESULT *pResult);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CListCtrl m_listLog;
	afx_msg void OnNMDblclkListLog(NMHDR *pNMHDR, LRESULT *pResult);
};
