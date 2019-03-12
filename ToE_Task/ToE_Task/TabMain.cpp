#include "stdafx.h"
#include "ToE_Task.h"
#include "TabMain.h"
#include "TabLog.h"
#include "TabSettings.h"
#include "afxdialogex.h"



// TabMain 대화 상자입니다.

IMPLEMENT_DYNAMIC(CTabMain, CDialogEx)

CTabMain::CTabMain(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTabMain::IDD, pParent)
{

}

CTabMain::~CTabMain()
{
}

void CTabMain::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_INIT, m_init);
	DDX_Control(pDX, IDC_EDIT_PIN_TEST, m_pin);
	DDX_Control(pDX, IDC_EDIT_SELF_CHECK, m_slefcap);
	DDX_Control(pDX, IDC_EDIT_MUTUAL_CHECK, m_mutualcap);
	DDX_Control(pDX, IDC_EDIT_DATA_COLLECT, m_datacollect);
	DDX_Control(pDX, IDC_EDIT_ATUOTUNE, m_autotune);
	DDX_Control(pDX, IDC_BN_START, m_mainstart);
	DDX_Control(pDX, IDC_LIST_LOG2, m_ListCtrl2);
}


BEGIN_MESSAGE_MAP(CTabMain, CDialogEx)
	ON_BN_CLICKED(IDC_BN_START, &CTabMain::OnBnClickedBnStart)
	ON_EN_CHANGE(IDC_EDIT_SELF_CHECK, &CTabMain::OnEnChangeEditSelfCheck)
	ON_EN_CHANGE(IDC_EDIT_INIT, &CTabMain::OnEnChangeEditInit)
	ON_EN_CHANGE(IDC_EDIT_ITO_TEST, &CTabMain::OnEnChangeEditItoTest) 
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_LOG2, &CTabMain::OnLvnItemchangedListLog2)
END_MESSAGE_MAP()


// TabMain 메시지 처리기입니다.

BOOL CTabMain::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	//this ->SetWindowPos(NULL,0,0,1000,800,SWP_NOREPOSITION);   //window size 조절

	//font setting 방법
	CFont m_font;
	m_font.CreatePointFont(0,"굴림");
	//m_edit1.SetFont(&SFont, TRUE);
	GetDlgItem(IDC_BN_START)->SetFont(&m_font);

	//edit 글자 띄우기
	GetDlgItem(IDC_EDIT_INIT)->SetWindowText("Init");
	GetDlgItem(IDC_EDIT_PIN_TEST)->SetWindowText("Pin Test");
	GetDlgItem(IDC_EDIT_ITO_TEST)->SetWindowText("ITO Test");
	GetDlgItem(IDC_EDIT_ATUOTUNE)->SetWindowText("Autotune");
	GetDlgItem(IDC_EDIT_DATA_COLLECT)->SetWindowText("Data Collect");
	GetDlgItem(IDC_EDIT_MUTUAL_CHECK)->SetWindowText("Mutual Check");
	GetDlgItem(IDC_EDIT_SELF_CHECK)->SetWindowText("Self Check");

	CRect rt;
	m_ListCtrl2.GetWindowRect(&rt);
	m_ListCtrl2.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

	m_ListCtrl2.InsertColumn(0,_T("TIMESTAMP"),LVCFMT_LEFT,rt.Width()*0.3);
	m_ListCtrl2.InsertColumn(1,_T("MESSAGE"),LVCFMT_CENTER,rt.Width()*0.5);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}



void CTabMain::OnBnClickedBnStart()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	GetDlgItem(IDC_EDIT_INIT)->SetWindowText("Init_check");
	Wait(500);
	GetDlgItem(IDC_EDIT_PIN_TEST)->SetWindowText("Pin Test_check");
	Wait(500);
	GetDlgItem(IDC_EDIT_ITO_TEST)->SetWindowText("ITO Test_check");
	Wait(500);
	GetDlgItem(IDC_EDIT_ATUOTUNE)->SetWindowText("Autotune_check");
	Wait(500);
	GetDlgItem(IDC_EDIT_DATA_COLLECT)->SetWindowText("Data Collect_check");
	Wait(500);
	GetDlgItem(IDC_EDIT_MUTUAL_CHECK)->SetWindowText("Mutual Check_check");
	Wait(500);
	GetDlgItem(IDC_EDIT_SELF_CHECK)->SetWindowText("Self Check_check");
	Wait(500);

	GetDlgItem(IDC_EDIT_INIT)->SetWindowText("Init");
	GetDlgItem(IDC_EDIT_PIN_TEST)->SetWindowText("Pin Test");
	GetDlgItem(IDC_EDIT_ITO_TEST)->SetWindowText("ITO Test");
	GetDlgItem(IDC_EDIT_ATUOTUNE)->SetWindowText("Autotune");
	GetDlgItem(IDC_EDIT_DATA_COLLECT)->SetWindowText("Data Collect");
	GetDlgItem(IDC_EDIT_MUTUAL_CHECK)->SetWindowText("Mutual Check");
	GetDlgItem(IDC_EDIT_SELF_CHECK)->SetWindowText("Self Check");

	CTabLog ptablog;
	ptablog.Log("start");
}

void CTabMain::Wait(DWORD dwMillisecond)
{
	MSG msg;
	DWORD dwStart;
	dwStart = GetTickCount();

	while(GetTickCount() - dwStart < dwMillisecond)
	{
		while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
}

void CTabMain::OnEnChangeEdit1()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CTabMain::OnEnChangeEditSelfCheck()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CTabMain::OnEnChangeEditInit()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.

}


void CTabMain::OnEnChangeEditItoTest()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}



void CTabMain::OnLvnItemchangedListLog2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
}

void CTabMain::Log(CString strLog2)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int num = m_ListCtrl2.GetItemCount();
	CString strDate;
	CString strTime;
	CTime gct = CTime::GetCurrentTime();
	strDate.Format(_T("%d/%d/%d-%d:%d"),gct.GetYear(),gct.GetMonth(),gct.GetDay(),gct.GetHour(),gct.GetMinute());

	m_ListCtrl2.InsertItem(num,strDate);

	m_ListCtrl2.SetItem(num,1,LVIF_TEXT,strLog2,NULL,NULL,NULL,NULL);
}
