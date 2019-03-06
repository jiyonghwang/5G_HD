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
END_MESSAGE_MAP()


// CTabSettings 메시지 처리기입니다.
