#include "stdafx.h"
#include "ToE_Task.h"
#include "TabMain.h"
#include "afxdialogex.h"


// TabMain ��ȭ �����Դϴ�.

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
	DDX_Control(pDX, IDC_EDIT_INIT, m_init);
	DDX_Control(pDX, IDC_EDIT_PIN_TEST, m_pin);
	DDX_Control(pDX, IDC_EDIT_SELF_CHECK, m_slefcap);
	DDX_Control(pDX, IDC_EDIT_MUTUAL_CHECK, m_mutualcap);
	DDX_Control(pDX, IDC_EDIT_DATA_COLLECT, m_datacollect);
	DDX_Control(pDX, IDC_EDIT_ATUOTUNE, m_autotune);
}


BEGIN_MESSAGE_MAP(CTabMain, CDialogEx)
	ON_BN_CLICKED(IDC_BN_START, &CTabMain::OnBnClickedBnStart)
	ON_EN_CHANGE(IDC_EDIT_SELF_CHECK, &CTabMain::OnEnChangeEditSelfCheck)
	ON_EN_CHANGE(IDC_EDIT_INIT, &CTabMain::OnEnChangeEditInit)
END_MESSAGE_MAP()


// TabMain �޽��� ó�����Դϴ�.

BOOL CTabMain::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	//this ->SetWindowPos(NULL,0,0,1000,800,SWP_NOREPOSITION);   //window size ����

	//font setting ���
	CFont m_font;
	m_font.CreatePointFont(0,"����");
	//m_edit1.SetFont(&SFont, TRUE);
	GetDlgItem(IDC_BN_START)->SetFont(&m_font);

	//edit ���� ����
	GetDlgItem(IDC_EDIT_INIT)->SetWindowText("Init");
	GetDlgItem(IDC_EDIT_PIN_TEST)->SetWindowText("Pin Test");
	GetDlgItem(IDC_EDIT_SELF_CHECK)->SetWindowText("ITO Test");
	GetDlgItem(IDC_EDIT_MUTUAL_CHECK)->SetWindowText("Mutual Check");
	GetDlgItem(IDC_EDIT_DATA_COLLECT)->SetWindowText("Data Collect");
	GetDlgItem(IDC_EDIT_ATUOTUNE)->SetWindowText("Autotune");

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}



void CTabMain::OnBnClickedBnStart()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void CTabMain::OnEnChangeEdit1()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialogEx::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void CTabMain::OnEnChangeEditSelfCheck()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialogEx::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void CTabMain::OnEnChangeEditInit()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialogEx::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

}
