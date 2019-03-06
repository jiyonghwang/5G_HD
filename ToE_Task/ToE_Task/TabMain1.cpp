// TabMain1.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "ToE_Task.h"
#include "TabMain1.h"
#include "afxdialogex.h"


// TabMain1 대화 상자입니다.

IMPLEMENT_DYNAMIC(TabMain1, CDialogEx)

TabMain1::TabMain1(CWnd* pParent /*=NULL*/)
	: CDialogEx(TabMain1::IDD, pParent)
{

}

TabMain1::~TabMain1()
{
}

void TabMain1::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(TabMain1, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &TabMain1::OnBnClickedButton1)
END_MESSAGE_MAP()


// TabMain1 메시지 처리기입니다.


void TabMain1::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
