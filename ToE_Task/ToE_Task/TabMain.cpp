#include "stdafx.h"
#include "ToE_Task.h"
#include "ToE_TaskDlg.h"
#include "TabMain.h"
#include "TabLog.h"
#include "TabSettings.h"
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
	DDX_Control(pDX, IDC_BN_START, m_mainstart);
	DDX_Control(pDX, IDC_CUSTOM1, m_Grid4);
	DDX_GridControl(pDX, IDC_CUSTOM1, m_Grid4);   //grid 
}


BEGIN_MESSAGE_MAP(CTabMain, CDialogEx)
	ON_BN_CLICKED(IDC_BN_START, &CTabMain::OnBnClickedBnStart)
	ON_EN_CHANGE(IDC_EDIT_SELF_CHECK, &CTabMain::OnEnChangeEditSelfCheck)
	ON_EN_CHANGE(IDC_EDIT_INIT, &CTabMain::OnEnChangeEditInit)
	ON_EN_CHANGE(IDC_EDIT_ITO_TEST, &CTabMain::OnEnChangeEditItoTest) 
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
	GetDlgItem(IDC_EDIT_ITO_TEST)->SetWindowText("ITO Test");
	GetDlgItem(IDC_EDIT_ATUOTUNE)->SetWindowText("Autotune");
	GetDlgItem(IDC_EDIT_DATA_COLLECT)->SetWindowText("Data Collect");
	GetDlgItem(IDC_EDIT_MUTUAL_CHECK)->SetWindowText("Mutual Check");
	GetDlgItem(IDC_EDIT_SELF_CHECK)->SetWindowText("Self Check");

	InitGrid4();  //grid

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}


void CTabMain::InitGrid4()
{
	int nRows = 10;
	int nCols = 8;

	m_Grid4.SetEditable(TRUE);
	m_Grid4.SetAutoSizeStyle();
	m_Grid4.SetColumnResize(0);
	m_Grid4.SetRowResize(0);
	m_Grid4.SetSingleRowSelection(2);
	m_Grid4.SetTrackFocusCell(FALSE); 
	m_Grid4.SetFrameFocusCell(FALSE);
	m_Grid4.SetFont(this->GetFont());

	TRY{
		m_Grid4.SetRowCount(nRows);
		m_Grid4.SetColumnCount(nCols);
		m_Grid4.SetFixedColumnCount(0);
		
	}
	CATCH (CMemoryException, e)
	{
		e->ReportError();
		return;
	}
	END_CATCH

	CString str;
	GV_ITEM Item;

	CRect rtSize;
	m_Grid4.GetClientRect(&rtSize);
	for (int col = 0; col < m_Grid4.GetColumnCount(); col++)
	{			
		Item.mask = GVIF_TEXT | GVIF_FORMAT ;
		Item.row = 0;
		Item.col = col;

		Item.nFormat = DT_CENTER|DT_VCENTER|DT_SINGLELINE;
		Item.crBkClr = RGB(255,255,255);
		Item.mask |= GVIF_BKCLR;		

		switch (col)
		{
		case 0: str = _T("Repeat"); break;
		case 1: str = _T("Date"); break;
		case 2: str = _T("Time"); break;
		case 3: str = _T("Value"); break;
		case 4: str = _T("units"); break;
		case 5: str = _T("X"); break;
		case 6: str = _T("Y"); break;
		case 7: str = _T("Lv"); break;
		}
		Item.strText = str;		
		m_Grid4.SetColumnWidth(col, rtSize.Width()/m_Grid4.GetColumnCount());		//55
		m_Grid4.SetItem(&Item);

		Item.mask = GVIF_TEXT | GVIF_FORMAT ;
		Item.row = 1;
		Item.col = col;
		Item.nFormat = DT_RIGHT|DT_VCENTER|DT_SINGLELINE|DT_CENTER;
		Item.mask |= GVIF_BKCLR;
		

		Item.crBkClr = RGB(255,255,255);
		Item.strText = _T("");
	
		m_Grid4.SetItem(&Item);
	}
	for (int row = 0; row < m_Grid4.GetRowCount(); row++)
	{
		int mA;
		CString Str_mA;
		mA= row+1;
		Str_mA.Format(_T("%d"),mA);
		Item.mask = GVIF_TEXT | GVIF_FORMAT ;
		Item.col = 0;
		Item.row = row+1;
		Item.nFormat = DT_RIGHT|DT_VCENTER|DT_SINGLELINE|DT_CENTER;
		Item.mask |= GVIF_BKCLR;
		Item.crBkClr = RGB(255,255,255);
		Item.strText = Str_mA;
		m_Grid4.SetItem(&Item);
		m_Grid4.SetRowHeight(row,rtSize.Height()/m_Grid4.GetRowCount());
	}
	
}

void CTabMain::OnBnClickedBnStart()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	GetDlgItem(IDC_EDIT_INIT)->SetWindowText("Init_check");
	Wait(500);
	GetDlgItem(IDC_EDIT_PIN_TEST)->SetWindowText("Pin Test_check");
	Wait(500);
	GetDlgItem(IDC_EDIT_ITO_TEST)->SetWindowText("ITO Test_check");
	Wait(500);
	GetDlgItem(IDC_EDIT_ATUOTUNE)->SetWindowText("Autotune_check");
	Wait(500);
	GetDlgItem(IDC_EDIT_DATA_COLLECT)->SetWindowText("Data Collect_check");
	Wait(500);
	GetDlgItem(IDC_EDIT_MUTUAL_CHECK)->SetWindowText("Mutual Check_check");
	Wait(500);
	GetDlgItem(IDC_EDIT_SELF_CHECK)->SetWindowText("Self Check_check");
	Wait(500);

	GetDlgItem(IDC_EDIT_INIT)->SetWindowText("Init");
	GetDlgItem(IDC_EDIT_PIN_TEST)->SetWindowText("Pin Test");
	GetDlgItem(IDC_EDIT_ITO_TEST)->SetWindowText("ITO Test");
	GetDlgItem(IDC_EDIT_ATUOTUNE)->SetWindowText("Autotune");
	GetDlgItem(IDC_EDIT_DATA_COLLECT)->SetWindowText("Data Collect");
	GetDlgItem(IDC_EDIT_MUTUAL_CHECK)->SetWindowText("Mutual Check");
	GetDlgItem(IDC_EDIT_SELF_CHECK)->SetWindowText("Self Check");

	//log ���
	CToE_TaskDlg *pFrm = (CToE_TaskDlg *)AfxGetMainWnd();
	pFrm->pDlgLog->Log("start");
}

void CTabMain::Wait(DWORD dwMillisecond)
{
	MSG msg;
	DWORD dwStart;
	dwStart = GetTickCount();

	while(GetTickCount() - dwStart < dwMillisecond)
	{
		while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
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


void CTabMain::OnEnChangeEditItoTest()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialogEx::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


