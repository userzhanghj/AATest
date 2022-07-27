// MotorDlg.cpp: 实现文件
//

#include "pch.h"
#include "ProjectAA.h"
#include "MotorDlg.h"
#include "afxdialogex.h"


// CMotorDlg 对话框

IMPLEMENT_DYNAMIC(CMotorDlg, CDialogEx)

CMotorDlg::CMotorDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_MOTOR, pParent)
{

}

CMotorDlg::~CMotorDlg()
{
}

void CMotorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_MOTORID, m_comboAxisNum);
	DDX_Control(pDX, IDC_EDIT_POSITION, m_editCrtPos);
	DDX_Control(pDX, IDC_EDIT_MOVESPEED, m_editSpeedMove);
	DDX_Control(pDX, IDC_EDIT_HOME_SPEED, m_editSpeedHome);
	DDX_Control(pDX, IDC_EDIT_ACCSPEED, m_editSpeedAcc);
	DDX_Control(pDX, IDC_EDIT_STEP_DIS, m_editReDis);
	DDX_Control(pDX, IDC_COMBO_DIRECTION, m_comboDirection);
	DDX_Control(pDX, IDC_CHECK_SERVOON, m_btnServoOn);
	DDX_Control(pDX, IDC_CHECK_HOME, m_btnHome);
	DDX_Control(pDX, IDC_CHECK_LIMITP, m_btnLmtP);
	DDX_Control(pDX, IDC_CHECK_LIMITM, m_btnLmtN);
	DDX_Control(pDX, IDC_CHECK_ALARM, m_btnAlarm);
	DDX_Control(pDX, IDC_LIST_AXIS, m_listAxis);
	DDX_Control(pDX, IDC_BUTTON_SERVO_ON, m_bBtnServoOn);
	DDX_Control(pDX, IDC_EDIT_STARTSPEED, m_editStartSpeed);
	DDX_Control(pDX, IDC_CHECK_RDY, m_btnRDY);
	DDX_Control(pDX, IDC_CHECK_INP, m_btnINP);
}


BEGIN_MESSAGE_MAP(CMotorDlg, CDialogEx)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CMotorDlg::OnBnClickedButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_SERVO_ON, &CMotorDlg::OnBnClickedButtonServoOn)
	ON_BN_CLICKED(IDC_BUTTON_STOP, &CMotorDlg::OnBnClickedButtonStop)
	ON_BN_CLICKED(IDC_BUTTON_RESET_ALARM, &CMotorDlg::OnBnClickedButtonResetAlarm)
	ON_BN_CLICKED(IDC_BUTTON_MOVE, &CMotorDlg::OnBnClickedButtonMove)
	ON_BN_CLICKED(IDC_BUTTON_HOME, &CMotorDlg::OnBnClickedButtonHome)
	ON_BN_CLICKED(IDC_BUTTON_STEP_P, &CMotorDlg::OnBnClickedButtonStepP)
	ON_BN_CLICKED(IDC_BUTTON_STEP_M, &CMotorDlg::OnBnClickedButtonStepM)
	ON_CBN_SELCHANGE(IDC_COMBO_MOTORID, &CMotorDlg::OnCbnSelchangeComboMotor)
END_MESSAGE_MAP()


// CMotorDlg 消息处理程序

BOOL CMotorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SetTimer(TIMER_ID_AXIS_STATUS, 500, NULL);

	gSystemMgr.m_ptrMotorDlg = this;

	m_mapAxisSetting = *gConfigMgr.GetAxisSettingDict();

	CreateAxisList();
	ListAllAxis();
	ShowCrtAxisMsg();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CMotorDlg::OnCancel()
{
	KillTimer(TIMER_ID_AXIS_STATUS);
	SITEDLG_TO_MOTORDLG temp;
	gSystemMgr.m_sSiteDlgToMotorDlg = temp;

	CDialogEx::OnCancel();
}


void CMotorDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == TIMER_ID_AXIS_STATUS)
	{
		GetCrtAxisStatus();
	}
	CDialogEx::OnTimer(nIDEvent);
}

void CMotorDlg::GetCrtAxisStatus()
{
	m_btnServoOn.SetCheck(!gSystemMgr.m_vCMotor[m_crtAxisSetting.m_nAxisId].m_bServoOn);
	m_btnAlarm.SetCheck(gSystemMgr.m_vCMotor[m_crtAxisSetting.m_nAxisId].m_bALM);
	m_btnLmtP.SetCheck(gSystemMgr.m_vCMotor[m_crtAxisSetting.m_nAxisId].m_bPEL);
	m_btnLmtN.SetCheck(gSystemMgr.m_vCMotor[m_crtAxisSetting.m_nAxisId].m_bNEL);
	m_btnHome.SetCheck(gSystemMgr.m_vCMotor[m_crtAxisSetting.m_nAxisId].m_bORG);
	m_btnRDY.SetCheck(gSystemMgr.m_vCMotor[m_crtAxisSetting.m_nAxisId].m_bRDY);
	m_btnINP.SetCheck(gSystemMgr.m_vCMotor[m_crtAxisSetting.m_nAxisId].m_bINP);

	m_bBtnServoOn.SetWindowTextW(gSystemMgr.m_vCMotor[m_comboAxisNum.GetCurSel()].m_bServoOn? L"Servo_ON":L"Servo_OFF");
	long nDis = gSystemMgr.m_vCMotor[m_crtAxisSetting.m_nAxisId].m_nCurPositon;
	CString cstr;
	cstr.Format(L"%d", nDis);
	m_editCrtPos.SetWindowTextW(cstr);
}

void CMotorDlg::CreateAxisList()
{
	m_listAxis.InsertColumn(0, L"轴ID", LVCFMT_LEFT, int(80 * gSystemMgr.m_fScreenY));
	m_listAxis.InsertColumn(1, L"轴名称", LVCFMT_LEFT, int(120 * gSystemMgr.m_fScreenY));
	m_listAxis.InsertColumn(2, L"换算比例", LVCFMT_LEFT, int(200 * gSystemMgr.m_fScreenY));

	DWORD dwStyle = m_listAxis.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;
	dwStyle |= LVS_EX_GRIDLINES;
	dwStyle |= LVS_EX_SUBITEMIMAGES;
	dwStyle |= LVS_ICON;
	m_listAxis.SetExtendedStyle(dwStyle);
	m_listAxis.ModifyStyle(0, LVS_ALIGNTOP);
	m_listAxis.SetBkColor(RGB(255, 255, 255));
	m_listAxis.SetFont(&gSystemMgr.m_logFont);
	m_listAxis.EnableWindow(TRUE);
}

void CMotorDlg::ListAllAxis()
{
	m_comboDirection.ResetContent();
	m_comboDirection.AddString(L"反向");
	m_comboDirection.AddString(L"正向");
	m_comboDirection.SetCurSel(1);

	int nCrtDir = m_comboDirection.GetCurSel();

	m_comboAxisNum.ResetContent();
	for (auto it = m_mapAxisSetting.begin(); it != m_mapAxisSetting.end(); it++)
	{
		CString cstr;
		//cstr.Format(L"%d", it->first);
		switch (it->first) {
		case 0:
			cstr.Format(L"%d:Tzble Z", it->first);
			break;
		case 1:
			cstr.Format(L"%d:Chart Z", it->first);
			break;
		case 2:
			cstr.Format(L"%d:Tzble X", it->first);
			break;
		case 3:
			cstr.Format(L"%d:AA X", it->first);
			break;
		case 4:
			cstr.Format(L"%d:AA Y", it->first);
			break;
		case 5:
			cstr.Format(L"%d:AA Z", it->first);
			break;
		case 6:
			cstr.Format(L"%d:AA Xt", it->first);
			break;
		case 7:
			cstr.Format(L"%d:AA Yt", it->first);
			break;
		default:
			cstr.Format(L"%d", it->first);
			break;
		}
		m_comboAxisNum.AddString(cstr);

		//这部分是List
		//m_listAxis.DeleteItem(0);
		cstr.Format(L"%d", it->second.m_nAxisId);
		m_listAxis.InsertItem(0, cstr);

		cstr = ATL::CW2A(it->second.m_wstrAxisName.c_str());
		m_listAxis.SetItemText(0, 1, cstr);

		cstr = ATL::CW2A(it->second.m_wstrProportion.c_str());
		m_listAxis.SetItemText(0, 2, cstr);
	}
	m_comboAxisNum.SetCurSel(0);

	m_crtAxisSetting = m_mapAxisSetting[0];
}

void CMotorDlg::ShowCrtAxisMsg()
{
	CString cstr;
	cstr.Format(L"%d", m_crtAxisSetting.m_nSpeedHome);
	m_editSpeedHome.SetWindowTextW(cstr);

	cstr.Format(L"%d", m_crtAxisSetting.m_nSpeedMove);
	m_editSpeedMove.SetWindowTextW(cstr);

	cstr.Format(L"%.2f", m_crtAxisSetting.m_nSpeedAcc);
	m_editSpeedAcc.SetWindowTextW(cstr);

	cstr.Format(L"%d", m_crtAxisSetting.m_nStartSpeed);
	m_editStartSpeed.SetWindowTextW(cstr);

	m_editCrtPos.SetWindowTextW(L"0");
	m_editReDis.SetWindowTextW(L"0");
}


void CMotorDlg::OnBnClickedButtonSave()
{
	CString cstrId;
	//m_comboAxisNum.GetWindowTextW(cstrId);
	int nCrtIndex = m_comboAxisNum.GetCurSel();
	CString cstr;

	m_editSpeedHome.GetWindowTextW(cstr);
	m_crtAxisSetting.m_nSpeedHome = _ttoi(cstr);
	m_editSpeedMove.GetWindowTextW(cstr);
	m_crtAxisSetting.m_nSpeedMove = _ttoi(cstr);
	m_editSpeedAcc.GetWindowTextW(cstr);
	m_crtAxisSetting.m_nSpeedAcc = _ttof(cstr);
	m_editStartSpeed.GetWindowTextW(cstr);
	m_crtAxisSetting.m_nStartSpeed = _ttoi(cstr);
	cstrId.Format(L"%d", nCrtIndex);
	gConfigMgr.UpdateAxisSetting(cstrId.GetBuffer(), m_crtAxisSetting);

	m_mapAxisSetting = *gConfigMgr.GetAxisSettingDict();
	gSystemMgr.MotorReadConfig();
	AfxMessageBox(L"参数保存成功");
}


void CMotorDlg::OnBnClickedButtonServoOn()
{
	if (m_crtAxisSetting.m_nAxisId > M_TABLE_X)
	{
		//步进驱动器不要上伺服
		return;
	}
	if (!gSystemMgr.m_vCMotor[m_crtAxisSetting.m_nAxisId].m_bServoOn)
	{
		
		gSystemMgr.m_vCMotor[m_crtAxisSetting.m_nAxisId].ServoOff();
	}
	else
	{
		
		gSystemMgr.m_vCMotor[m_crtAxisSetting.m_nAxisId].ServoOn();
	}
}


void CMotorDlg::OnBnClickedButtonStop()
{
	gSystemMgr.m_vCMotor[m_crtAxisSetting.m_nAxisId].StopMove();
}


void CMotorDlg::OnBnClickedButtonResetAlarm()
{
	gSystemMgr.m_vCMotor[m_crtAxisSetting.m_nAxisId].ResetAlarm();
}


void CMotorDlg::OnBnClickedButtonMove()
{
	int nCrtDir = m_comboDirection.GetCurSel();
	gSystemMgr.m_vCMotor[m_crtAxisSetting.m_nAxisId].MotorMoveContinue(nCrtDir);
}


void CMotorDlg::OnBnClickedButtonHome()
{
	int nCrtDir = m_comboDirection.GetCurSel();
	gSystemMgr.m_vCMotor[m_crtAxisSetting.m_nAxisId].HomeSearch(nCrtDir);
}


void CMotorDlg::OnBnClickedButtonStepP()
{
	CString cstr;
	m_editReDis.GetWindowTextW(cstr);
	gSystemMgr.m_vCMotor[m_crtAxisSetting.m_nAxisId].m_sAxisSetting.m_dTargetPos = _ttof(cstr);
	gSystemMgr.m_vCMotor[m_crtAxisSetting.m_nAxisId].MotorMoveStep();
}


void CMotorDlg::OnBnClickedButtonStepM()
{
	CString cstr;
	m_editReDis.GetWindowTextW(cstr);
	gSystemMgr.m_vCMotor[m_crtAxisSetting.m_nAxisId].m_sAxisSetting.m_dTargetPos = -_ttof(cstr);
	gSystemMgr.m_vCMotor[m_crtAxisSetting.m_nAxisId].MotorMoveStep();
}

void CMotorDlg::OnCbnSelchangeComboMotor()
{
	int nCrtIndex = m_comboAxisNum.GetCurSel();
	m_crtAxisSetting = m_mapAxisSetting[nCrtIndex];

	CString cstr;
	cstr.Format(L"%d", m_crtAxisSetting.m_nSpeedHome);
	m_editSpeedHome.SetWindowTextW(cstr);
	cstr.Format(L"%d", m_crtAxisSetting.m_nSpeedMove);
	m_editSpeedMove.SetWindowTextW(cstr);
	cstr.Format(L"%.2f", m_crtAxisSetting.m_nSpeedAcc);
	m_editSpeedAcc.SetWindowTextW(cstr);
	cstr.Format(L"%d", m_crtAxisSetting.m_nStartSpeed);
	m_editStartSpeed.SetWindowTextW(cstr);

	ShowCrtAxisMsg();
}
