
// ProjectAADlg.h: 头文件
//

#pragma once
#include"MotorDlg.h"
#include"LogDlg.h"
#include "ChangeProject.h"
#include "ImageCaptureDlg.h"
#include "SFRSettingDlg.h"
#include "IOControlDlg.h"
#include "AAControlDlg.h"
#include "ManualControlDlg.h"
#include "RS232SetDlg.h"
#include "LoginDlg.h"
#include "LightTestDlg.h"
#include "CountDlg.h"

// CProjectAADlg 对话框
class CProjectAADlg : public CDialogEx
{
// 构造
public:
	CProjectAADlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PROJECTAA_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;
	CMenu m_menu;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	HANDLE unique_mutex;
public:
	POINT Old;

	CMotorDlg*   m_cMotorDlg = nullptr;
	CLogDlg*   m_cLogDlg = nullptr;
	CChangeProject*  m_cChangeProjectDlg = nullptr;
	CImageCaptureDlg*  m_cCaptureDlg = nullptr;
	CSFRSettingDlg*  m_cSfrSettingDlg = nullptr;
	CIOControlDlg* m_cIODlg = nullptr;
	CAAControlDlg* m_cAADlg = nullptr;
	CManualControlDlg* m_cManualDlg = nullptr;
	CRS232SetDlg* m_cRS232Dlg = nullptr;
	CLoginDlg*   m_cLoginDlg = nullptr;
	CLightTestDlg*   m_cLightTestDlg = nullptr;
	CCountDlg*   m_cCountDlg = nullptr;

	CBitmap Bitmap;
	HBITMAP hBitmap; 
	HBRUSH hbr;//画笔相关

	LRESULT OnReceiveServerMsg(WPARAM wParam, LPARAM lParam);
	CRect m_rcUiRect;
	CRect OriRect[200];
	int RectW[200] = { 0 };
	int RectH[200] = { 0 };
	void Repaint(CWnd * pWnd, int last_Width, int now_Width, int last_Height, int now_Height, int cnt);
	void SetUiHandle();

	afx_msg void OnOpenLogDlg();
	afx_msg void OnOpenMotorDlg();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnOpenProjectDlg();
	afx_msg void OnBnClickedButtonStart();
	afx_msg void OnBnClickedButtonStop();
	afx_msg void OnOpenCaptureDlg();
	afx_msg void OnOpenSFRDlg();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual void OnCancel();
	afx_msg void OnOpenIODlg();
	afx_msg void OnBnClickedCheck2();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
//	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
//	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnOpenAADlg();
	CBitmapButton m_butStart;
	CBitmapButton m_butStop;
//	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	CButton m_butSave;
	CStatic m_static_3;
	CStatic m_static_19;
	CStatic m_static_20;
	CStatic m_static_42;
	afx_msg void OnBnClickedButtonHome40();
	afx_msg void OnOpenManualControl();
	afx_msg void OnOpenComDlg();
	afx_msg void OnOpenLogin();
	afx_msg void OnBnClickedButtonSave();
	afx_msg void OnBnClickedButtonClaer2();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButtonHome41();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	CStatic Static1;
	CButton Button1;
	CButton Button2;
	CButton Button3;
	CEdit m_editStep;
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton9();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton23();
	afx_msg void OnBnClickedButton24();
	afx_msg void OnOpenLightTestDlg();
};
