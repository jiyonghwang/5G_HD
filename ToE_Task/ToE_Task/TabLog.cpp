// TabLog.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "ToE_Task.h"
#include "TabLog.h"
#include "afxdialogex.h"


// CTabLog 대화 상자입니다.

IMPLEMENT_DYNAMIC(CTabLog, CDialogEx)

CTabLog::CTabLog(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTabLog::IDD, pParent)
{
	
}

CTabLog::~CTabLog()
{
}

void CTabLog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_LIST_LOG, m_ListCtrl);
}


BEGIN_MESSAGE_MAP(CTabLog, CDialogEx)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_LOG, &CTabLog::OnLvnItemchangedListLog)
END_MESSAGE_MAP()



BOOL CTabLog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	CRect rt;
	m_ListCtrl.GetWindowRect(&rt);
	m_ListCtrl.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

	m_ListCtrl.InsertColumn(0,_T("TIMESTAMP"),LVCFMT_LEFT,rt.Width()*0.3);
	m_ListCtrl.InsertColumn(1,_T("MESSAGE"),LVCFMT_CENTER,rt.Width()*0.5);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

// CTabLog 메시지 처리기입니다.


void CTabLog::OnLvnItemchangedListLog(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
}

void CTabLog::Log(CString strLog2)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int num = m_ListCtrl.GetItemCount();
	CString strDate;
	CString strTime;
	CTime gct = CTime::GetCurrentTime();
	strDate.Format(_T("%d/%d/%d-%d:%d"),gct.GetYear(),gct.GetMonth(),gct.GetDay(),gct.GetHour(),gct.GetMinute());

	m_ListCtrl.InsertItem(num,strDate);

	m_ListCtrl.SetItem(num,1,LVIF_TEXT,strLog2,NULL,NULL,NULL,NULL);
}

/*
void CKTmeasDlg::OnBnClickedListctrlDel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	POSITION pos;
	pos = m_ListCtrl.GetFirstSelectedItemPosition();
	int idx = m_ListCtrl.GetNextSelectedItem(pos);
	m_ListCtrl.DeleteItem(idx);
}
*/