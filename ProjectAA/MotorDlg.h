#pragma once

#include "Motor.h"

// CMotorDlg 对话框

class CMotorDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMotorDlg)

public:
	CMotorDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CMotorDlg();

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_MOTOR };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	std::map<int, AXIS_SETTING> m_mapAxisSetting;
	void CreateAxisList();
	void ListAllAxis();
	void ShowCrtAxisMsg();
	void GetCrtAxisStatus();

	AXIS_SETTING    m_crtAxisSetting;

	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CComboBox m_comboAxisNum;
	CEdit m_editCrtPos;
	CEdit m_editSpeedMove;
	CEdit m_editSpeedHome;
	CEdit m_editSpeedAcc;
	CEdit m_editReDis;
	CComboBox m_comboDirection;
	CButton m_btnServoOn;
	CButton m_btnHome;
	CButton m_btnLmtP;
	CButton m_btnLmtN;
	CButton m_btnAlarm;
	CListCtrl m_listAxis;
	afx_msg void OnBnClickedButtonSave();
	afx_msg void OnBnClickedButtonServoOn();
	CButton m_bBtnServoOn;
	afx_msg void OnBnClickedButtonStop();
	afx_msg void OnBnClickedButtonResetAlarm();
	afx_msg void OnBnClickedButtonMove();
	afx_msg void OnBnClickedButtonHome();
	afx_msg void OnBnClickedButtonStepP();
	afx_msg void OnBnClickedButtonStepM();
	afx_msg void OnCbnSelchangeComboMotor();
	CEdit m_editStartSpeed;
	CButton m_btnRDY;
	CButton m_btnINP;
};
