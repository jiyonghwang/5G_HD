// TabMain.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "ToE_Task.h"
#include "TabMain.h"
#include "afxdialogex.h"


// CTabMain ��ȭ �����Դϴ�.

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


// CTabMain �޽��� ó�����Դϴ�.
// TabMain.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "ToE_Task.h"
#include "TabMain.h"
#include "afxdialogex.h"


// TabMain ��ȭ �����Դϴ�.

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


// TabMain �޽��� ó�����Դϴ�.


void TabMain::OnBnClickedButton1()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}
