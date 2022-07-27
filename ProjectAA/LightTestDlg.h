#pragma once


// CLightTestDlg 对话框

class CLightTestDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CLightTestDlg)

public:
	CLightTestDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CLightTestDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_STD };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	void ReadConfigIni();
	void SaveValueToConfig();

	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	BOOL LightFlag;
	int LightX0;
	int LightX1;
	int LightX2;
	int LightX3;
	int LightX4;
	int LightY0;
	int LightY1;
	int LightY2;
	int LightY3;
	int LightY4;
	int LightSpec0;
	int LightSpec1;
	int LightSpec2;
	int LightSpec3;
	int LightSpec4;
	int LightW;
	int LightH;
	afx_msg void OnBnClickedButton1();
};
