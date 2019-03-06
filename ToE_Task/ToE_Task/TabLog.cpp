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
}


BEGIN_MESSAGE_MAP(CTabLog, CDialogEx)
END_MESSAGE_MAP()


// CTabLog 메시지 처리기입니다.
