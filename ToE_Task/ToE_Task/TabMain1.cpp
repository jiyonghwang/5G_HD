// TabMain1.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "ToE_Task.h"
#include "TabMain1.h"
#include "afxdialogex.h"


// TabMain1 ��ȭ �����Դϴ�.

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


// TabMain1 �޽��� ó�����Դϴ�.


void TabMain1::OnBnClickedButton1()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}
