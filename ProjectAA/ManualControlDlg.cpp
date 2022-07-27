// ManualControlDlg.cpp: 实现文件
//

#include "pch.h"
#include "ProjectAA.h"
#include "ManualControlDlg.h"
#include "afxdialogex.h"


// CManualControlDlg 对话框

IMPLEMENT_DYNAMIC(CManualControlDlg, CDialogEx)

CManualControlDlg::CManualControlDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_CONTROL, pParent)
{

}

CManualControlDlg::~CManualControlDlg()
{
}

void CManualControlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_STEPDIS, m_editStepDis);
	DDX_Control(pDX, IDC_COMBO_POSITION, m_comboPositionNum);
	DDX_Control(pDX, IDC_STATIC_POS1, m_staticTableZ);
	DDX_Control(pDX, IDC_STATIC_POS2, m_staticTableX);
	DDX_Control(pDX, IDC_STATIC_POS3, m_staticAAX);
	DDX_Control(pDX, IDC_STATIC_POS4, m_staticAAY);
	DDX_Control(pDX, IDC_STATIC_POS5, m_staticAAZ);
	DDX_Control(pDX, IDC_STATIC_POS6, m_staticAAXt);
	DDX_Control(pDX, IDC_STATIC_POS7, m_staticAAYt);
	DDX_Control(pDX, IDC_STATIC_POS8, m_staticChartZ);
}


BEGIN_MESSAGE_MAP(CManualControlDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_LIGHT_ON, &CManualControlDlg::OnBnClickedButtonLightOn)
	ON_BN_CLICKED(IDC_BUTTON23, &CManualControlDlg::OnBnClickedButton23)
	ON_BN_CLICKED(IDC_BUTTON24, &CManualControlDlg::OnBnClickedButton24)
	ON_BN_CLICKED(IDC_BUTTON25, &CManualControlDlg::OnBnClickedButton25)
	ON_BN_CLICKED(IDC_BUTTON26, &CManualControlDlg::OnBnClickedButton26)
	ON_BN_CLICKED(IDC_BUTTON27, &CManualControlDlg::OnBnClickedButton27)
	ON_BN_CLICKED(IDC_BUTTON28, &CManualControlDlg::OnBnClickedButton28)
	ON_BN_CLICKED(IDC_BUTTON_XU, &CManualControlDlg::OnBnClickedButtonXu)
	ON_BN_CLICKED(IDC_BUTTON_XD, &CManualControlDlg::OnBnClickedButtonXd)
	ON_BN_CLICKED(IDC_BUTTON_YU, &CManualControlDlg::OnBnClickedButtonYu)
	ON_BN_CLICKED(IDC_BUTTON_YD, &CManualControlDlg::OnBnClickedButtonYd)
	ON_BN_CLICKED(IDC_BUTTON_ZU, &CManualControlDlg::OnBnClickedButtonZu)
	ON_BN_CLICKED(IDC_BUTTON_ZD, &CManualControlDlg::OnBnClickedButtonZd)
	ON_BN_CLICKED(IDC_BUTTON_XTU, &CManualControlDlg::OnBnClickedButtonXtu)
	ON_BN_CLICKED(IDC_BUTTON_XTD, &CManualControlDlg::OnBnClickedButtonXtd)
	ON_BN_CLICKED(IDC_BUTTON_YTU, &CManualControlDlg::OnBnClickedButtonYtu)
	ON_BN_CLICKED(IDC_BUTTON_YTD, &CManualControlDlg::OnBnClickedButtonYtd)
	ON_BN_CLICKED(IDC_BUTTON_TZU, &CManualControlDlg::OnBnClickedButtonTzu)
	ON_BN_CLICKED(IDC_BUTTON_TZD, &CManualControlDlg::OnBnClickedButtonTzd)
	ON_BN_CLICKED(IDC_BUTTON_TXU, &CManualControlDlg::OnBnClickedButtonTxu)
	ON_BN_CLICKED(IDC_BUTTON_TXD, &CManualControlDlg::OnBnClickedButtonTxd)
	ON_BN_CLICKED(IDC_BUTTON_STOP, &CManualControlDlg::OnBnClickedButtonStop)
	ON_BN_CLICKED(IDC_BUTTON_MOVE, &CManualControlDlg::OnBnClickedButtonMove)
	ON_BN_CLICKED(IDC_BUTTON29, &CManualControlDlg::OnBnClickedButton29)
	ON_BN_CLICKED(IDC_BUTTON30, &CManualControlDlg::OnBnClickedButton30)
	ON_BN_CLICKED(IDC_BUTTON31, &CManualControlDlg::OnBnClickedButton31)
	ON_BN_CLICKED(IDC_BUTTON32, &CManualControlDlg::OnBnClickedButton32)
	ON_BN_CLICKED(IDC_BUTTON33, &CManualControlDlg::OnBnClickedButton33)
	ON_BN_CLICKED(IDC_BUTTON34, &CManualControlDlg::OnBnClickedButton34)
	ON_BN_CLICKED(IDC_BUTTON35, &CManualControlDlg::OnBnClickedButton35)
	ON_BN_CLICKED(IDC_BUTTON37, &CManualControlDlg::OnBnClickedButton37)
	ON_BN_CLICKED(IDC_BUTTON38, &CManualControlDlg::OnBnClickedButton38)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON39, &CManualControlDlg::OnBnClickedButton39)
	ON_BN_CLICKED(IDC_BUTTON9, &CManualControlDlg::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON10, &CManualControlDlg::OnBnClickedButton10)
	ON_BN_CLICKED(IDC_BUTTON41, &CManualControlDlg::OnBnClickedButton41)
	ON_BN_CLICKED(IDC_BUTTON40, &CManualControlDlg::OnBnClickedButton40)
	ON_BN_CLICKED(IDC_BUTTON42, &CManualControlDlg::OnBnClickedButton42)
	ON_BN_CLICKED(IDC_BUTTON_CHART0, &CManualControlDlg::OnBnClickedButtonChart0)
	ON_BN_CLICKED(IDC_BUTTON_CHART1, &CManualControlDlg::OnBnClickedButtonChart1)
	ON_BN_CLICKED(IDC_BUTTON44, &CManualControlDlg::OnBnClickedButton44)
	ON_BN_CLICKED(IDC_BUTTON43, &CManualControlDlg::OnBnClickedButton43)
	ON_BN_CLICKED(IDC_BUTTON45, &CManualControlDlg::OnBnClickedButton45)
	ON_BN_CLICKED(IDC_CHECK1, &CManualControlDlg::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_CHECK5, &CManualControlDlg::OnBnClickedCheck5)
	ON_BN_CLICKED(IDC_CHECK6, &CManualControlDlg::OnBnClickedCheck6)
	ON_BN_CLICKED(IDC_CHECK7, &CManualControlDlg::OnBnClickedCheck7)
	ON_BN_CLICKED(IDC_CHECK8, &CManualControlDlg::OnBnClickedCheck8)
	ON_BN_CLICKED(IDC_CHECK11, &CManualControlDlg::OnBnClickedCheck11)
	ON_BN_CLICKED(IDC_CHECK9, &CManualControlDlg::OnBnClickedCheck9)
	ON_BN_CLICKED(IDC_CHECK10, &CManualControlDlg::OnBnClickedCheck10)
END_MESSAGE_MAP()


// CManualControlDlg 消息处理程序


BOOL CManualControlDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SetTimer(TIMER_CONTROL_AXIS_POS, 500, NULL);

	CString cstr;
	cstr.Format(L"0");
	m_editStepDis.SetWindowTextW(cstr);

	m_comboPositionNum.ResetContent();
	m_comboPositionNum.AddString(L"0:镜头夹取 上方");
	m_comboPositionNum.AddString(L"1:镜头夹取位");
	m_comboPositionNum.AddString(L"2:AA位置 上方");
	m_comboPositionNum.AddString(L"3:AA位置");
	m_comboPositionNum.SetCurSel(0);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CManualControlDlg::OnCancel()
{
	KillTimer(TIMER_CONTROL_AXIS_POS);

	CDialogEx::OnCancel();
}


void CManualControlDlg::OnBnClickedButtonLightOn()
{
	if(gSystemMgr.Y19 == FALSE)
		gSystemMgr.m_cIo.SetOutputIo(19, ON);
	else
		gSystemMgr.m_cIo.SetOutputIo(19, OFF);
}


void CManualControlDlg::OnBnClickedButton23()
{
	gSystemMgr.m_cIo.SetOutputIo(5, ON);
	gSystemMgr.m_cIo.SetOutputIo(6, OFF);
}


void CManualControlDlg::OnBnClickedButton24()
{
	gSystemMgr.m_cIo.SetOutputIo(6, ON);
	gSystemMgr.m_cIo.SetOutputIo(5, OFF);
}


void CManualControlDlg::OnBnClickedButton25()
{
	gSystemMgr.m_cIo.SetOutputIo(7, ON);
	gSystemMgr.m_cIo.SetOutputIo(8, OFF);
}


void CManualControlDlg::OnBnClickedButton26()
{
	gSystemMgr.m_cIo.SetOutputIo(8, ON);
	gSystemMgr.m_cIo.SetOutputIo(7, OFF);
}


void CManualControlDlg::OnBnClickedButton27()
{
	gSystemMgr.m_cIo.SetOutputIo(9, ON);
	gSystemMgr.m_cIo.SetOutputIo(10, OFF);
}


void CManualControlDlg::OnBnClickedButton28()
{
	gSystemMgr.m_cIo.SetOutputIo(10, ON);
	gSystemMgr.m_cIo.SetOutputIo(9, OFF);
}


void CManualControlDlg::OnBnClickedButtonXu()
{
	CString cstr;
	m_editStepDis.GetWindowTextW(cstr);
	gSystemMgr.m_vCMotor[MOTOR_X].m_sAxisSetting.m_dTargetPos = _ttof(cstr);
	gSystemMgr.m_vCMotor[MOTOR_X].MotorMoveStep();
}

void CManualControlDlg::OnBnClickedButtonXd()
{
	CString cstr;
	m_editStepDis.GetWindowTextW(cstr);
	gSystemMgr.m_vCMotor[MOTOR_X].m_sAxisSetting.m_dTargetPos = -_ttof(cstr);
	gSystemMgr.m_vCMotor[MOTOR_X].MotorMoveStep();
}

void CManualControlDlg::OnBnClickedButtonYu()
{
	CString cstr;
	m_editStepDis.GetWindowTextW(cstr);
	gSystemMgr.m_vCMotor[MOTOR_Y].m_sAxisSetting.m_dTargetPos = _ttof(cstr);
	gSystemMgr.m_vCMotor[MOTOR_Y].MotorMoveStep();
}


void CManualControlDlg::OnBnClickedButtonYd()
{
	CString cstr;
	m_editStepDis.GetWindowTextW(cstr);
	gSystemMgr.m_vCMotor[MOTOR_Y].m_sAxisSetting.m_dTargetPos = -_ttof(cstr);
	gSystemMgr.m_vCMotor[MOTOR_Y].MotorMoveStep();
}


void CManualControlDlg::OnBnClickedButtonZu()
{
	CString cstr;
	m_editStepDis.GetWindowTextW(cstr);
	gSystemMgr.m_vCMotor[MOTOR_Z].m_sAxisSetting.m_dTargetPos = _ttof(cstr);
	gSystemMgr.m_vCMotor[MOTOR_Z].MotorMoveStep();
}


void CManualControlDlg::OnBnClickedButtonZd()
{
	CString cstr;
	m_editStepDis.GetWindowTextW(cstr);
	gSystemMgr.m_vCMotor[MOTOR_Z].m_sAxisSetting.m_dTargetPos = -_ttof(cstr);
	gSystemMgr.m_vCMotor[MOTOR_Z].MotorMoveStep();
}


void CManualControlDlg::OnBnClickedButtonXtu()
{
	CString cstr;
	m_editStepDis.GetWindowTextW(cstr);
	gSystemMgr.m_vCMotor[MOTOR_Xt].m_sAxisSetting.m_dTargetPos = _ttof(cstr);
	gSystemMgr.m_vCMotor[MOTOR_Xt].MotorMoveStep();
}


void CManualControlDlg::OnBnClickedButtonXtd()
{
	CString cstr;
	m_editStepDis.GetWindowTextW(cstr);
	gSystemMgr.m_vCMotor[MOTOR_Xt].m_sAxisSetting.m_dTargetPos = -_ttof(cstr);
	gSystemMgr.m_vCMotor[MOTOR_Xt].MotorMoveStep();
}


void CManualControlDlg::OnBnClickedButtonYtu()
{
	CString cstr;
	m_editStepDis.GetWindowTextW(cstr);
	gSystemMgr.m_vCMotor[MOTOR_Yt].m_sAxisSetting.m_dTargetPos = _ttof(cstr);
	gSystemMgr.m_vCMotor[MOTOR_Yt].MotorMoveStep();
}


void CManualControlDlg::OnBnClickedButtonYtd()
{
	CString cstr;
	m_editStepDis.GetWindowTextW(cstr);
	gSystemMgr.m_vCMotor[MOTOR_Yt].m_sAxisSetting.m_dTargetPos = -_ttof(cstr);
	gSystemMgr.m_vCMotor[MOTOR_Yt].MotorMoveStep();
}


void CManualControlDlg::OnBnClickedButtonTzu()
{
	CString cstr;
	m_editStepDis.GetWindowTextW(cstr);
	gSystemMgr.m_vCMotor[M_TABLE_Z].m_sAxisSetting.m_dTargetPos = _ttof(cstr);
	gSystemMgr.m_vCMotor[M_TABLE_Z].MotorMoveStep();
}


void CManualControlDlg::OnBnClickedButtonTzd()
{
	CString cstr;
	m_editStepDis.GetWindowTextW(cstr);
	gSystemMgr.m_vCMotor[M_TABLE_Z].m_sAxisSetting.m_dTargetPos = -_ttof(cstr);
	gSystemMgr.m_vCMotor[M_TABLE_Z].MotorMoveStep();
}


void CManualControlDlg::OnBnClickedButtonTxu()
{
	CString cstr;
	m_editStepDis.GetWindowTextW(cstr);
	gSystemMgr.m_vCMotor[M_TABLE_X].m_sAxisSetting.m_dTargetPos = _ttof(cstr);
	gSystemMgr.m_vCMotor[M_TABLE_X].MotorMoveStep();
}


void CManualControlDlg::OnBnClickedButtonTxd()
{
	CString cstr;
	m_editStepDis.GetWindowTextW(cstr);
	gSystemMgr.m_vCMotor[M_TABLE_X].m_sAxisSetting.m_dTargetPos = -_ttof(cstr);
	gSystemMgr.m_vCMotor[M_TABLE_X].MotorMoveStep();
}


void CManualControlDlg::OnBnClickedButtonStop()
{
	gSystemMgr.m_vCMotor[M_TABLE_Z].StopMove();
	gSystemMgr.m_vCMotor[M_TABLE_X].StopMove();
	gSystemMgr.m_vCMotor[MOTOR_X].StopMove();
	gSystemMgr.m_vCMotor[MOTOR_Y].StopMove();
	gSystemMgr.m_vCMotor[MOTOR_Z].StopMove();
	gSystemMgr.m_vCMotor[MOTOR_Xt].StopMove();
	gSystemMgr.m_vCMotor[MOTOR_Yt].StopMove();
}


void CManualControlDlg::OnBnClickedButtonMove()
{
	if (gSystemMgr.m_bMotorErrorFlag || !gSystemMgr.m_bHomeFlag || gSystemMgr.m_bEmergencyStopFlag)
		return;
	int n;
	n = m_comboPositionNum.GetCurSel();
	gSystemMgr.m_nButtonValue = 100 + n;
}


void CManualControlDlg::OnBnClickedButton29()
{
	gSystemMgr.m_nButtonValue = 20;
}


void CManualControlDlg::OnBnClickedButton30()
{
	gSystemMgr.m_nButtonValue = 21;
}


void CManualControlDlg::OnBnClickedButton31()
{
	gSystemMgr.m_nButtonValue = 22;
}


void CManualControlDlg::OnBnClickedButton32()
{
	gSystemMgr.m_nButtonValue = 23;
}


void CManualControlDlg::OnBnClickedButton33()
{
	gSystemMgr.m_nButtonValue = 24;
}


void CManualControlDlg::OnBnClickedButton34()
{
	gSystemMgr.m_nButtonValue = 25;
}


void CManualControlDlg::OnBnClickedButton35()
{
	gSystemMgr.m_nButtonValue = 11;
}


void CManualControlDlg::OnBnClickedButton37()
{
	gSystemMgr.m_cIo.SetOutputIo(21, ON);
	Sleep(100);
	gSystemMgr.m_cIo.SetOutputIo(21, OFF);
}


void CManualControlDlg::OnBnClickedButton38()
{
	gSystemMgr.m_cIo.SetOutputIo(22, ON);
	Sleep(100);
	gSystemMgr.m_cIo.SetOutputIo(22, OFF);
}


void CManualControlDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == TIMER_CONTROL_AXIS_POS)
	{
		CString cstr;
		cstr.Format(L"%d", gSystemMgr.m_vCMotor[M_TABLE_Z].m_nCurPositon);
		m_staticTableZ.SetWindowTextW(cstr);
		cstr.Format(L"%d", gSystemMgr.m_vCMotor[M_TABLE_X].m_nCurPositon);
		m_staticTableX.SetWindowTextW(cstr);
		cstr.Format(L"%d", gSystemMgr.m_vCMotor[MOTOR_X].m_nCurPositon);
		m_staticAAX.SetWindowTextW(cstr);
		cstr.Format(L"%d", gSystemMgr.m_vCMotor[MOTOR_Y].m_nCurPositon);
		m_staticAAY.SetWindowTextW(cstr);
		cstr.Format(L"%d", gSystemMgr.m_vCMotor[MOTOR_Z].m_nCurPositon);
		m_staticAAZ.SetWindowTextW(cstr);
		cstr.Format(L"%d", gSystemMgr.m_vCMotor[MOTOR_Xt].m_nCurPositon);
		m_staticAAXt.SetWindowTextW(cstr);
		cstr.Format(L"%d", gSystemMgr.m_vCMotor[MOTOR_Yt].m_nCurPositon);
		m_staticAAYt.SetWindowTextW(cstr);

		cstr.Format(L"%d", gSystemMgr.m_vCMotor[M_CHART_Z].m_nCurPositon);
		m_staticChartZ.SetWindowTextW(cstr);
	}

	CDialogEx::OnTimer(nIDEvent);
}


void CManualControlDlg::OnBnClickedButton39()
{
	gSystemMgr.MoveOffsetZ(-gSystemMgr.m_dOffsetZ);
}


void CManualControlDlg::OnBnClickedButton9()
{
	if (gSystemMgr.Y03 == FALSE)
		gSystemMgr.m_cIo.SetOutputIo(3, ON);
	else
		gSystemMgr.m_cIo.SetOutputIo(3, OFF);
}


void CManualControlDlg::OnBnClickedButton10()
{
	if (gSystemMgr.Y30 == FALSE)
		gSystemMgr.m_cIo.SetOutputIo(30, ON);
	else
		gSystemMgr.m_cIo.SetOutputIo(30, OFF);
}





void CManualControlDlg::OnBnClickedButton41()
{
	gSystemMgr.m_bManualDone = 1;
}


void CManualControlDlg::OnBnClickedButton40()
{
	gSystemMgr.m_cIo.SetOutputIo(12, ON);
	gSystemMgr.m_cIo.SetOutputIo(11, OFF);
}


void CManualControlDlg::OnBnClickedButton42()
{
	gSystemMgr.m_cIo.SetOutputIo(11, ON);
	gSystemMgr.m_cIo.SetOutputIo(12, OFF);
}


void CManualControlDlg::OnBnClickedButtonChart0()
{
	CString cstr;
	m_editStepDis.GetWindowTextW(cstr);
	gSystemMgr.m_vCMotor[M_CHART_Z].m_sAxisSetting.m_dTargetPos = _ttof(cstr);
	gSystemMgr.m_vCMotor[M_CHART_Z].MotorMoveStep();
}


void CManualControlDlg::OnBnClickedButtonChart1()
{
	CString cstr;
	m_editStepDis.GetWindowTextW(cstr);
	gSystemMgr.m_vCMotor[M_CHART_Z].m_sAxisSetting.m_dTargetPos = -_ttof(cstr);
	gSystemMgr.m_vCMotor[M_CHART_Z].MotorMoveStep();
}


void CManualControlDlg::OnBnClickedButton44()
{
	gSystemMgr.m_nButtonValue = 110;
}


void CManualControlDlg::OnBnClickedButton43()
{
	gSystemMgr.m_nButtonValue = 12;
}


void CManualControlDlg::OnBnClickedButton45()
{
	if (gSystemMgr.Y04 == FALSE)
		gSystemMgr.m_cIo.SetOutputIo(4, ON);
	else
		gSystemMgr.m_cIo.SetOutputIo(4, OFF);
}


void CManualControlDlg::OnBnClickedCheck1()
{
	CString cstr;
	CButton* pCheckBox = (CButton*)GetDlgItem(IDC_CHECK1);
	int nFlag = pCheckBox->GetCheck();
	if (nFlag == BST_CHECKED)
	{
		gSystemMgr.m_cIo.SetOutputIo(3, ON);
	}
	else
	{
		gSystemMgr.m_cIo.SetOutputIo(3, OFF);
	}
}


void CManualControlDlg::OnBnClickedCheck5()
{
	CString cstr;
	CButton* pCheckBox = (CButton*)GetDlgItem(IDC_CHECK5);
	int nFlag = pCheckBox->GetCheck();
	if (nFlag == BST_CHECKED)
	{
		gSystemMgr.m_cIo.SetOutputIo(4, ON);
	}
	else
	{
		gSystemMgr.m_cIo.SetOutputIo(4, OFF);
	}
}


void CManualControlDlg::OnBnClickedCheck6()
{
	CString cstr;
	CButton* pCheckBox = (CButton*)GetDlgItem(IDC_CHECK6);
	int nFlag = pCheckBox->GetCheck();
	if (nFlag == BST_CHECKED)
	{
		gSystemMgr.m_cIo.SetOutputIo(5, ON);
		gSystemMgr.m_cIo.SetOutputIo(6, OFF);
	}
	else
	{
		gSystemMgr.m_cIo.SetOutputIo(6, ON);
		gSystemMgr.m_cIo.SetOutputIo(5, OFF);
	}
}


void CManualControlDlg::OnBnClickedCheck7()
{
	CString cstr;
	CButton* pCheckBox = (CButton*)GetDlgItem(IDC_CHECK7);
	int nFlag = pCheckBox->GetCheck();
	if (nFlag == BST_CHECKED)
	{
		gSystemMgr.m_cIo.SetOutputIo(7, ON);
		gSystemMgr.m_cIo.SetOutputIo(8, OFF);
	}
	else
	{
		gSystemMgr.m_cIo.SetOutputIo(8, ON);
		gSystemMgr.m_cIo.SetOutputIo(7, OFF);
	}
}


void CManualControlDlg::OnBnClickedCheck8()
{
	CString cstr;
	CButton* pCheckBox = (CButton*)GetDlgItem(IDC_CHECK8);
	int nFlag = pCheckBox->GetCheck();
	if (nFlag == BST_CHECKED)
	{
		gSystemMgr.m_cIo.SetOutputIo(9, ON);
		gSystemMgr.m_cIo.SetOutputIo(10, OFF);
	}
	else
	{
		gSystemMgr.m_cIo.SetOutputIo(10, ON);
		gSystemMgr.m_cIo.SetOutputIo(9, OFF);
	}
}


void CManualControlDlg::OnBnClickedCheck11()
{
	CString cstr;
	CButton* pCheckBox = (CButton*)GetDlgItem(IDC_CHECK11);
	int nFlag = pCheckBox->GetCheck();
	if (nFlag == BST_CHECKED)
	{
		gSystemMgr.m_cIo.SetOutputIo(21, ON);
		Sleep(100);
		gSystemMgr.m_cIo.SetOutputIo(21, OFF);
	}
	else
	{
		gSystemMgr.m_cIo.SetOutputIo(22, ON);
		Sleep(100);
		gSystemMgr.m_cIo.SetOutputIo(22, OFF);
	}
}


void CManualControlDlg::OnBnClickedCheck9()
{
	CString cstr;
	CButton* pCheckBox = (CButton*)GetDlgItem(IDC_CHECK9);
	int nFlag = pCheckBox->GetCheck();
	if (nFlag == BST_CHECKED)
	{
		gSystemMgr.m_cIo.SetOutputIo(30, ON);
	}
	else
	{
		gSystemMgr.m_cIo.SetOutputIo(30, OFF);
	}
}


void CManualControlDlg::OnBnClickedCheck10()
{
	CString cstr;
	CButton* pCheckBox = (CButton*)GetDlgItem(IDC_CHECK10);
	int nFlag = pCheckBox->GetCheck();
	if (nFlag == BST_CHECKED)
	{
		gSystemMgr.m_cIo.SetOutputIo(12, ON);
		gSystemMgr.m_cIo.SetOutputIo(11, OFF);
	}
	else
	{
		gSystemMgr.m_cIo.SetOutputIo(11, ON);
		gSystemMgr.m_cIo.SetOutputIo(12, OFF);
	}
}
