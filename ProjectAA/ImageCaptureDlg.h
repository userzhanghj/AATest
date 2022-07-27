#pragma once


// CImageCaptureDlg 对话框

class CImageCaptureDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CImageCaptureDlg)

public:
	CImageCaptureDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CImageCaptureDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_CAPTURE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	void ReadConfigIni();
	void SaveValueToConfig();
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	CComboBox m_comboImageSource;
	CComboBox m_comboTestMode;
	CComboBox m_comboCaptureMode;
	CComboBox m_comboChangeMode;
	BOOL m_bWriteiic;
	BOOL m_bMirrorX;
	BOOL m_bMirrorY;
	afx_msg void OnBnClickedButtonSave();
	int m_nCTSId;
	BOOL m_nGpioFlag;
	CComboBox m_comboGpioNo;
	afx_msg void OnBnClickedButtonWriteiic();
	afx_msg void OnBnClickedButtonResetcts();
	BOOL ChangeXY;
	int CameraDsW;
	int CameraDsH;
};
