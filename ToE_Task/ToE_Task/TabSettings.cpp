// TabSettings.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "ToE_Task.h"
#include "TabSettings.h"
#include "afxdialogex.h"


// CTabSettings ��ȭ �����Դϴ�.

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
	ON_BN_CLICKED(IDC_BN_FILE_OPEN, &CTabSettings::OnBnClickedBnFileOpen)
	ON_EN_CHANGE(IDC_EDIT_PATH, &CTabSettings::OnEnChangeEditPath)
	ON_COMMAND(ID_FILE_LIST2, &CTabSettings::OnFileList2)
	ON_BN_CLICKED(IDC_BN_PATH_OPEN, &CTabSettings::OnBnClickedBnPathOpen)
END_MESSAGE_MAP()

// CTabSettings �޽��� ó�����Դϴ�.

BOOL CTabSettings::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}


void CTabSettings::OnBnClickedBnFileOpen()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	//file�� ������ �� �ִ� Dlg
	char szFilter[]="hello(*.csv)|*.xls|User Settings(*.cfg)|*.cfg|All Files(*.*)|*.*|";
	CFileDialog fDlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, szFilter);
	//(TRUE(�б�)/FALSE(����),�⺻Ȯ����,�⺻���ϸ�,������->MSDN����, ����â �Ʒ��ʿ� ������ ���͸�)

	int iRet = fDlg.DoModal();
	m_strFilePath = fDlg.GetPathName();

	if(iRet == IDOK)
	{
		SetDlgItemText(IDC_EDIT_PATH, m_strFilePath);  //edit �� ���ϰ�� Ȯ��


	}
}

void CTabSettings::OnBnClickedBnPathOpen()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	ShellExecute(NULL, "open", m_strFilePath, NULL, NULL, SW_SHOW);
}

void CTabSettings::OnEnChangeEdit1()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialogEx::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void CTabSettings::OnEnChangeEditPath()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialogEx::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void CTabSettings::OnFileList2()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
}

