// ChangeProject.cpp: 实现文件
//

#include "pch.h"
#include "ProjectAA.h"
#include "ChangeProject.h"
#include "afxdialogex.h"


// CChangeProject 对话框

IMPLEMENT_DYNAMIC(CChangeProject, CDialogEx)

CChangeProject::CChangeProject(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_CHANGE_PROJECT, pParent)
{

}

CChangeProject::~CChangeProject()
{
}

void CChangeProject::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_CRT_PROJECT, m_editCrtProject);
	DDX_Control(pDX, IDC_LIST_PROJECT, m_editListProject);
}


BEGIN_MESSAGE_MAP(CChangeProject, CDialogEx)
	ON_LBN_DBLCLK(IDC_LIST_PROJECT, &CChangeProject::OnLbnDblclkListProject)
END_MESSAGE_MAP()


// CChangeProject 消息处理程序

BOOL CChangeProject::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_editCrtProject.SetWindowTextW(gSystemMgr.m_sGeneralSetting.m_cstrProjectName);

	CString cstrPath = gSystemMgr.GetCurrentExePath();
	cstrPath.Append(L"\\recipe");
	vector<CString> vPath = GetFileFolderInPath(cstrPath);


	m_editListProject.ResetContent();
	for (int i = 0; i < (int)vPath.size(); i++)
	{
		Sleep(1);
		if (vPath[i] != L"log")
		{
			m_editListProject.AddString(vPath[i]);
		}
	}

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CChangeProject::OnCancel()
{

	CDialogEx::OnCancel();
}

vector<CString> CChangeProject::GetFileFolderInPath(CString cstrPath)
{
	vector<CString> vCstrPath;

	if (cstrPath == L"")
	{
		return vector<CString>();
	}

	if (cstrPath.Right(1) != _T("\\"))
	{
		cstrPath += L"\\";
		cstrPath = cstrPath + _T("*.*");
	}

	CFileFind cFinder;
	CString cstrPathChild;
	BOOL bWorking = cFinder.FindFile(cstrPath);
	while (bWorking)
	{
		Sleep(1);
		bWorking = cFinder.FindNextFile();
		cstrPathChild = cFinder.GetFilePath();
		//文件夹
		if (cFinder.IsDirectory() && !cFinder.IsDots())
		{
			CString cstrFolderName = cstrPathChild.Right(cstrPathChild.GetLength() - cstrPath.GetLength() + 3);
			vCstrPath.push_back(cstrFolderName);
		}
		//文件
		else if (!cFinder.IsDirectory() && !cFinder.IsDots())
		{
			CString cstrFolderName = cstrPathChild.Right(cstrPathChild.GetLength() - cstrPath.GetLength() + 3);
		}
	}
	return vCstrPath;
}


void CChangeProject::OnLbnDblclkListProject()
{
	int nSel = m_editListProject.GetCurSel();
	if (nSel < 0)
	{
		return;
	}
	else
	{
		CString cstr;
		m_editListProject.GetText(nSel, cstr);
		if (IDYES == AfxMessageBox(L"确定切换型号吗？", MB_YESNO))
		{
			gSystemMgr.m_cGeneralSetting.SaveConfigIni(L"GeneralSetting", L"m_cstrProductName", cstr);

			/*CString cstrPath = gSystemMgr.GetCurrentExePath();
			cstrPath.Append(L"\\EightStationsAA.exe");

			STARTUPINFO sinf;
			PROCESS_INFORMATION pif;
			memset(&sinf, 0, sizeof(STARTUPINFO));
			sinf.cb = sizeof(STARTUPINFO);
			sinf.wShowWindow = SW_SHOW;
			sinf.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;
			bool bwork= ::CreateProcess((LPCTSTR)cstrPath,NULL,NULL,NULL,FALSE,
				0,NULL,NULL,&sinf,&pif);*/

			::TerminateProcess(::GetCurrentProcess(), NULL);//终止原先程序
		//	ExitProcess(0);
		}
	}
}
