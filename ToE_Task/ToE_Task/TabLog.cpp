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
}


BEGIN_MESSAGE_MAP(CTabLog, CDialogEx)
END_MESSAGE_MAP()


// CTabLog �޽��� ó�����Դϴ�.
