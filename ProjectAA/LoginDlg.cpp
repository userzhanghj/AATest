// LoginDlg.cpp: 实现文件
//

#include "pch.h"
#include "ProjectAA.h"
#include "LoginDlg.h"
#include "afxdialogex.h"


// CLoginDlg 对话框

IMPLEMENT_DYNAMIC(CLoginDlg, CDialogEx)

CLoginDlg::CLoginDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_LOGIN, pParent)
	, m_cPassward(_T(""))
	, m_cNewPassword(_T(""))
	, NewID(_T(""))
	, NewPassword(_T(""))
{

}

CLoginDlg::~CLoginDlg()
{
}

void CLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_USERNAME, m_cUserName);
	DDX_Text(pDX, IDC_EDIT_PASSWORD, m_cPassward);
	DDX_Text(pDX, IDC_EDIT_USERNAME2, NewID);
	DDX_Text(pDX, IDC_EDIT_PASSWORD2, NewPassword);
}


BEGIN_MESSAGE_MAP(CLoginDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_LOGIN, &CLoginDlg::OnBnClickedButtonLogin)
	ON_CBN_SELCHANGE(IDC_COMBO_MODE_CHOOSE, &CLoginDlg::OnCbnSelchangeComboModeChoose)
	ON_BN_CLICKED(IDC_BUTTON_QUIT, &CLoginDlg::OnBnClickedButtonQuit)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON1, &CLoginDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CLoginDlg 消息处理程序

BOOL CLoginDlg::OnInitDialog()
{
	CComboBox* combo_box = nullptr;
	combo_box = (CComboBox*)GetDlgItem(IDC_COMBO_MODE_CHOOSE);

	combo_box->InsertString(0, L"员工");
	combo_box->InsertString(1, L"管理员");
	combo_box->SetCurSel(0);

	ReadLoginConfig();

	return TRUE;
}

void CLoginDlg::ReadLoginConfig()
{
	m_cPasswordCorrect = gSystemMgr.m_sLoginInfo.m_cPassword; 
	m_cUserNameCorrect = gSystemMgr.m_sLoginInfo.m_cUserName;
}

void CLoginDlg::OnBnClickedButtonLogin()
{
	UpdateData(TRUE);

	CComboBox* combo_box = (CComboBox*)(GetDlgItem(IDC_COMBO_MODE_CHOOSE));
	auto cboSelcect = combo_box->GetCurSel();

	//if(m_cPasswordCorrect == L"")
	//{
	//	m_cPasswordCorrect = L"1";
	//}

	if(cboSelcect == 0)
	{
		if(m_cUserName != L"")
		{
			int i = _ttoi(m_cUserName);
			CString cstr;
			cstr.Format(L"员工号:%d  员工登陆成功!", i);
			gSystemLog.DisplayLogAndSave(cstr.GetBuffer(), LV_EVENT);
			OnClose();
			EnableControl(TRUE);
		}
		else
		{
			gSystemLog.DisplayLogAndSave(L"请输入员工号!", LV_ERROR);
		}
		
	}
	if(cboSelcect == 1)
	{
		UpdateData(TRUE);

		if (m_cUserName == m_cUserNameCorrect /*!= L""*/ && m_cPassward == m_cPasswordCorrect)
		{
			ModeFlag = 1;
			int i = _ttoi(m_cUserName);
			CString cstr;
			cstr.Format(L"员工号:%d  管理员登陆成功!", i);
			gSystemLog.DisplayLogAndSave(cstr.GetBuffer(), LV_EVENT);
			OnClose();
			EnableControl(TRUE);
		}
		else
		{
			gSystemLog.DisplayLogAndSave(L"登陆失败!", LV_ERROR);
		}
		
	}

	m_cUserName = L"";
	m_cPassward = L"";
	UpdateData(FALSE);
}


void CLoginDlg::EnableControl(const BOOL nflag)
{
	CComboBox* combo_box = (CComboBox*)(GetDlgItem(IDC_COMBO_MODE_CHOOSE));
	auto cboSelcect = combo_box->GetCurSel();

	CButton* btn = nullptr;
	btn = (CButton*)GetDlgItem(IDC_BUTTON_QUIT);
	btn->EnableWindow(nflag);

	CButton* btnLogin = nullptr;
	btnLogin = (CButton*)GetDlgItem(IDC_BUTTON_LOGIN);
	btnLogin->EnableWindow(!nflag);

	if (cboSelcect == 1)
	{
		CButton* btn2 = nullptr;
		btn2 = (CButton*)GetDlgItem(IDC_BUTTON1);
		btn2->EnableWindow(nflag);
	}

	CMenu* pMenu = GetMenu();
	pMenu = AfxGetMainWnd()->GetMenu();

	if (ModeFlag == 1)
	{
		//CStatic* staticAdmin = (CStatic*)GetDlgItem(IDC_STATIC_NEW_PASSWARD);
		//CEdit* editAdmin = (CEdit*)GetDlgItem(IDC_EDIT_NEW_PASSWORD);
		//CEdit* btnAdmin = (CEdit*)GetDlgItem(IDC_BUTTON_NEW_PASSWARD);

		//staticAdmin->ShowWindow(nflag);
		//editAdmin->ShowWindow(nflag);
		//btnAdmin->ShowWindow(nflag);


		if (nflag == 1)
		{
			pMenu->EnableMenuItem(ID_32781, MF_ENABLED);
			pMenu->EnableMenuItem(ID_32774, MF_ENABLED);
			pMenu->EnableMenuItem(ID_32783, MF_ENABLED);
			pMenu->EnableMenuItem(ID_32776, MF_ENABLED);
			pMenu->EnableMenuItem(ID_32777, MF_ENABLED);
			pMenu->EnableMenuItem(ID_32775, MF_ENABLED);
		}
		else
		{
			pMenu->EnableMenuItem(ID_32781, MF_DISABLED);
			pMenu->EnableMenuItem(ID_32774, MF_DISABLED);
			pMenu->EnableMenuItem(ID_32783, MF_DISABLED);
			pMenu->EnableMenuItem(ID_32776, MF_DISABLED);
			pMenu->EnableMenuItem(ID_32777, MF_DISABLED);
			pMenu->EnableMenuItem(ID_32775, MF_DISABLED);
		}
	}
}

void CLoginDlg::OnBnClickedButtonQuit()
{
	gSystemLog.DisplayLogAndSave(L"退出登录成功!", LV_EVENT);
	EnableControl(FALSE);
	ModeFlag = 0;
}



void CLoginDlg::OnCbnSelchangeComboModeChoose()
{
	CComboBox* combo_box = (CComboBox*)(GetDlgItem(IDC_COMBO_MODE_CHOOSE));
	auto i = combo_box->GetCurSel();
	if(i == 0)
	{
		CEdit* my_edit = (CEdit*)GetDlgItem(IDC_EDIT_PASSWORD);
		my_edit->SetReadOnly(TRUE);
	}
	else
	{
		CEdit* my_edit = (CEdit*)GetDlgItem(IDC_EDIT_PASSWORD);
		my_edit->SetReadOnly(FALSE);
	}
}


void CLoginDlg::OnClose()
{
	ShowWindow(SW_HIDE);
	CDialogEx::OnClose();
}


void CLoginDlg::OnBnClickedButton1()
{
	UpdateData(TRUE);
	if (IDYES == AfxMessageBox(L"确定 修改工程师账户密码 吗？", MB_YESNO))
	{
		gSystemMgr.m_sLoginInfo.m_cPassword = NewPassword;
		gSystemMgr.m_sLoginInfo.m_cUserName = NewID;
		gSystemMgr.m_cLoginConfigIni.SaveConfigIni(L"LoginConfig", L"m_cPassword", gSystemMgr.m_sLoginInfo.m_cPassword);
		gSystemMgr.m_cLoginConfigIni.SaveConfigIni(L"LoginConfig", L"m_cUserName", gSystemMgr.m_sLoginInfo.m_cUserName);
		ReadLoginConfig();
	}
}
