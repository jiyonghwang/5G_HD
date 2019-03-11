// TabSettings.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "ToE_Task.h"
#include "TabSettings.h"
#include "afxdialogex.h"


// CTabSettings 대화 상자입니다.

IMPLEMENT_DYNAMIC(CTabSettings, CDialogEx)

CTabSettings::CTabSettings(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTabSettings::IDD, pParent)
{

}

CTabSettings::~CTabSettings()
{
}

void CTabSettings::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CTabSettings, CDialogEx)
	ON_BN_CLICKED(IDC_BN_FILE_OPEN, &CTabSettings::OnBnClickedBnFileOpen)
	ON_EN_CHANGE(IDC_EDIT_PATH, &CTabSettings::OnEnChangeEditPath)
	ON_COMMAND(ID_FILE_LIST2, &CTabSettings::OnFileList2)
	ON_BN_CLICKED(IDC_BN_PATH_OPEN, &CTabSettings::OnBnClickedBnPathOpen)
END_MESSAGE_MAP()

// CTabSettings 메시지 처리기입니다.

BOOL CTabSettings::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CTabSettings::OnBnClickedBnFileOpen()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//file을 선택할 수 있는 Dlg
	char szFilter[]="hello(*.csv)|*.xls|User Settings(*.cfg)|*.cfg|All Files(*.*)|*.*|";
	CFileDialog fDlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, szFilter);
	//(TRUE(읽기)/FALSE(저장),기본확장자,기본파일명,열기모드->MSDN참고, 파일창 아래쪽에 나오는 필터링)

	int iRet = fDlg.DoModal();
	m_strFilePath = fDlg.GetPathName();

	if(iRet == IDOK)
	{
		SetDlgItemText(IDC_EDIT_PATH, m_strFilePath);  //edit 에 파일경로 확인


	}
}

void CTabSettings::OnBnClickedBnPathOpen()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	ShellExecute(NULL, "open", m_strFilePath, NULL, NULL, SW_SHOW);
}

void CTabSettings::OnEnChangeEdit1()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CTabSettings::OnEnChangeEditPath()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CTabSettings::OnFileList2()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}

