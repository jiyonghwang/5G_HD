// TabLog.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "ToE_Task.h"
#include "TabLog.h"
#include "afxdialogex.h"


// CTabLog ��ȭ �����Դϴ�.

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

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	CRect rt;
	m_ListCtrl.GetWindowRect(&rt);
	m_ListCtrl.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

	m_ListCtrl.InsertColumn(0,_T("TIMESTAMP"),LVCFMT_LEFT,rt.Width()*0.3);
	m_ListCtrl.InsertColumn(1,_T("MESSAGE"),LVCFMT_CENTER,rt.Width()*0.5);

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

// CTabLog �޽��� ó�����Դϴ�.


void CTabLog::OnLvnItemchangedListLog(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	*pResult = 0;
}

void CTabLog::Log(CString strLog2)
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	POSITION pos;
	pos = m_ListCtrl.GetFirstSelectedItemPosition();
	int idx = m_ListCtrl.GetNextSelectedItem(pos);
	m_ListCtrl.DeleteItem(idx);
}
*/