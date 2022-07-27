#pragma once


// CChangeProject 对话框

class CChangeProject : public CDialogEx
{
	DECLARE_DYNAMIC(CChangeProject)

public:
	CChangeProject(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CChangeProject();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_CHANGE_PROJECT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	CEdit m_editCrtProject;
	CListBox m_editListProject;
	vector<CString> GetFileFolderInPath(CString cstrPath);

	afx_msg void OnLbnDblclkListProject();
};
