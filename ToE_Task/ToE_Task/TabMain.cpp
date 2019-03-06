// TabMain.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "ToE_Task.h"
#include "TabMain.h"
#include "afxdialogex.h"


// CTabMain 대화 상자입니다.

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
}


BEGIN_MESSAGE_MAP(CTabMain, CDialogEx)
END_MESSAGE_MAP()


// CTabMain 메시지 처리기입니다.
// TabMain.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "ToE_Task.h"
#include "TabMain.h"
#include "afxdialogex.h"


// TabMain 대화 상자입니다.

IMPLEMENT_DYNAMIC(TabMain, CDialogEx)

TabMain::TabMain(CWnd* pParent /*=NULL*/)
	: CDialogEx(TabMain::IDD, pParent)
{

}

TabMain::~TabMain()
{
}

void TabMain::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(TabMain, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &TabMain::OnBnClickedButton1)
END_MESSAGE_MAP()


// TabMain 메시지 처리기입니다.


void TabMain::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
