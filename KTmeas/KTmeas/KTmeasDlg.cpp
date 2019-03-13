
// KTmeasDlg.cpp : ���� ����
//
//test1
//test2
//test3


#include "stdafx.h"
#include "KTmeas.h"
#include "KTmeasDlg.h"
#include "afxdialogex.h"
#define USER_TIMER 1000
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define _CRT_SECURE_NO_WARNINGS

// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CKTmeasDlg ��ȭ ����

CKTmeasDlg::CKTmeasDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CKTmeasDlg::IDD, pParent)
	, m_Repeat(5)
	, m_Time(1)
	, m_nX(_T(""))
	, m_nY(_T(""))
	, m_nLv(_T(""))
	, m_Mode(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CKTmeasDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_COM3, m_cboPort3);
	DDX_Control(pDX, IDC_CHECK_COM1, m_ButPort1);
	DDX_Control(pDX, IDC_BUTTON_COM3, m_ButPort3);
	DDX_Control(pDX, IDC_CHECK_COM3, m_ButPort3);
	DDX_Text(pDX, IDC_EDIT_REPEAT, m_Repeat);
	DDX_Text(pDX, IDC_EDIT_TIME, m_Time);
	DDX_Text(pDX, IDC_EDIT_MEASURE, m_Meas);
	DDX_Text(pDX, IDC_EDIT_MEASURE, m_Meas);
	DDX_GridControl(pDX, IDC_CUSTOM1, m_Grid4);   //grid 
	DDX_Text(pDX, IDC_EDIT_X, m_nX);
	DDX_Text(pDX, IDC_EDIT_Y, m_nY);
	DDX_Text(pDX, IDC_EDIT_Lv, m_nLv);
	//  DDX_Radio(pDX, IDC_RADIO_CA, m_Mode);
	//  DDX_Radio(pDX, IDC_RADIO_CA, m_Mode);
	DDX_Radio(pDX, IDC_RADIO_CA, m_Mode);
	DDX_Control(pDX, IDC_LISTCTRL, m_ListCtrl);
}

BEGIN_MESSAGE_MAP(CKTmeasDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_MESSAGE(WM_RECEIVEDATA, OnReceiveData)
	ON_BN_CLICKED(IDOK, &CKTmeasDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_CHECK_COM1, &CKTmeasDlg::OnBnClickedCheckCom1)
	ON_CBN_SELCHANGE(IDC_COMBO_COM3, &CKTmeasDlg::OnCbnSelchangeComboCom3)
	ON_BN_CLICKED(IDC_CHECK_COM3, &CKTmeasDlg::OnBnClickedCheckCom3)
	ON_EN_CHANGE(IDC_EDIT_REPEAT, &CKTmeasDlg::OnEnChangeEditRepeat)
	ON_BN_CLICKED(IDC_BUTTON_START, &CKTmeasDlg::OnBnClickedButtonStart)
	ON_BN_CLICKED(IDC_BUTTON_MEASURE, &CKTmeasDlg::OnBnClickedButtonMeasure)
	ON_EN_CHANGE(IDC_EDIT_MEASURE, &CKTmeasDlg::OnEnChangeEditMeasure)
	ON_BN_CLICKED(IDC_BUTTON_VOLT, &CKTmeasDlg::OnBnClickedButtonVolt)
	ON_BN_CLICKED(IDC_BUTTON_CURR, &CKTmeasDlg::OnBnClickedButtonCurr)
	ON_BN_CLICKED(IDC_RADIO_CA, &CKTmeasDlg::OnBnClickedRadioCa)
	ON_BN_CLICKED(IDC_CA310_Measure, &CKTmeasDlg::OnBnClickedCa310Measure)
	ON_BN_CLICKED(IDC_RADIO_KT, &CKTmeasDlg::OnBnClickedRadioKt)
	ON_BN_CLICKED(IDC_RADIO_CAKT, &CKTmeasDlg::OnBnClickedRadioCakt)
	ON_BN_CLICKED(IDC_BUTTON_CSV, &CKTmeasDlg::OnBnClickedButtonCsv)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LISTCTRL, &CKTmeasDlg::OnLvnItemchangedListctrl)
	//ON_BN_CLICKED(IDC_LISTCTRL_ADD, &CKTmeasDlg::OnBnClickedListctrlAdd)
	ON_BN_CLICKED(IDC_LISTCTRL_DEL, &CKTmeasDlg::OnBnClickedListctrlDel)
	ON_EN_CHANGE(IDC_LISTCTRL_EDIT, &CKTmeasDlg::OnEnChangeListctrlEdit)
END_MESSAGE_MAP()


// CKTmeasDlg �޽��� ó����

BOOL CKTmeasDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// �� ��ȭ ������ �������� �����մϴ�. ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.
	
	//---serial init catch----
	//	m_Comm = NULL;
	ACK_Status = 1;
	//SetComPort(10);

	for (int i = 1; i < 100; i++)
	{
		CString strText;
		strText.Format("\\\\.\\COM%d", i);

		BOOL bSuccess = FALSE;
		HANDLE hPort = ::CreateFile(strText, GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, 0, 0);
		if (hPort == INVALID_HANDLE_VALUE)
		{
			DWORD dwError = GetLastError();
			if (dwError == ERROR_ACCESS_DENIED) bSuccess = TRUE;
		}
		else
		{
			bSuccess = TRUE;

			CloseHandle(hPort);
		}
		
		if (bSuccess) 
		{
			strText.Format("COM%d", i);
			m_cboPort3.AddString(strText);
		}
	}
	if (m_cboPort3.GetCount()) m_cboPort3.SetCurSel(0);
	m_bComConnect=FALSE;
	m_bComConnect3=FALSE;
	//---Serial init catch---

	InitGrid4();  //grid

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	GetDlgItem(IDC_CA310_Measure)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_MEASURE)->EnableWindow(FALSE);

	CRect rt;
	m_ListCtrl.GetWindowRect(&rt);
	m_ListCtrl.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

	m_ListCtrl.InsertColumn(0,_T("�ð�"),LVCFMT_LEFT,rt.Width()*0.5);
	m_ListCtrl.InsertColumn(1,_T("����"),LVCFMT_CENTER,rt.Width()*0.5);

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

void CKTmeasDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�. ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CKTmeasDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ��� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CKTmeasDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CKTmeasDlg::OnBnClickedOk()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CDialogEx::OnOK();
}



void CKTmeasDlg::InitGrid4()
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


void CKTmeasDlg::ReGrid3()
{
	CString str;
	GV_ITEM Item;
	CRect rtSize;
	UpdateData(TRUE);
	m_Grid4.GetClientRect(&rtSize);
	m_Grid4.SetRowCount(m_Repeat+1);
	m_Grid4.SetColumnCount(8);
	m_Grid4.RedrawRow(m_Repeat);
	for (int row = 0; row < m_Grid4.GetRowCount(); row++)
	{
		int mA;
		CString Str_mA;
		mA= 1+row;
		Str_mA.Format(_T("%d"),mA);
		Item.mask = GVIF_TEXT | GVIF_FORMAT ;
		Item.row = row+1;
		Item.col = 0;
		Item.nFormat = DT_RIGHT|DT_VCENTER|DT_SINGLELINE|DT_CENTER;
		Item.mask |= GVIF_BKCLR;
		Item.crBkClr = RGB(255,255,255);
		Item.strText = Str_mA;
		m_Grid4.SetItem(&Item);
	}


	
}

void CKTmeasDlg::OnBnClickedCheckCom1()
{
#ifdef __CA_SDK
	if(!m_bComConnect)
	{
		if (m_OptiComp.Init())
		{
			m_bComConnect=TRUE;
			GetDlgItem(IDC_CA310_Measure)->EnableWindow(TRUE);      // CA310 ���� �ϸ� measuer ��ư Ȱ��ȭ
			m_ButPort1.SetWindowText("Connected");
			m_ButPort1.SetCheck(true);   //üũ ���� -> üũ
		}
	}
	else
	{
		if(m_OptiComp.m_dwCk != 0)
		{
			m_bComConnect = FALSE;
			m_OptiComp.m_pCaObj->RemoteMode = 0;
			m_ButPort1.SetWindowText("CA310");
			m_ButPort1.SetCheck(false);
		}
	}
	Log("CA connect");
}
#endif

BOOL CKTmeasDlg::SetComPort(int nPort)
{
	//��Ʈ�� ����Ʈ�� �����.
	m_Comm.SetComPort(nPort, 38400, 7, TWOSTOPBITS, EVENPARITY);

	//��Ʈ�� ����Ʈ�� ����
	if (m_Comm.OpenComPort() == FALSE)
	{
		AfxMessageBox("����� ������ �� �����ϴ�.");
		return FALSE;
	}

	m_Comm.SetHwnd(this->m_hWnd);

	return TRUE;
}

void CKTmeasDlg::OnBnClickedCheckCom3()
{
	CString cmd;
	if (!m_bComConnect3)
	{
		CString strText;
		m_cboPort3.GetLBText(m_cboPort3.GetCurSel(), strText);
		strText = strText.Mid(3);

		int nPort = atoi(strText);
		TRACE(_T("nPort = %d\n"), nPort);

		if (SetComPort3(nPort))
		{
			m_bComConnect3 = TRUE;
			m_ButPort3.SetWindowText("Connected");
			Kiethley_Connect();
			GetDlgItem(IDC_BUTTON_MEASURE)->EnableWindow(TRUE);
			m_ButPort3.SetCheck(true);   //üũ ���� -> üũ 
		}
		else
		{
			m_ButPort3.SetCheck(false);  //üũ -> üũ ����
		}
	}
	else
	{
		cmd.Format(_T(":OUTP OFF"));
		Write_Comm_CString3(cmd);
		Wait(10);
		cmd.Format(_T(":SYST:KEY 23"));  //local key
		Write_Comm_CString3(cmd);
		Wait(10);
		m_Comm3.DestroyComm();
		m_bComConnect3 = FALSE;
		m_ButPort3.SetWindowText("Keithley");
		m_ButPort3.SetCheck(false);
	}

	Log("KT connect");
}

BOOL CKTmeasDlg::SetComPort3(int nPort)
{
	//��Ʈ�� ����Ʈ�� �����.
	m_Comm3.SetComPort(nPort, 57600, 8, ONESTOPBIT, NOPARITY);

	//��Ʈ�� ����Ʈ�� ����
	if (m_Comm3.OpenComPort() == FALSE)
	{
		AfxMessageBox("����� ������ �� �����ϴ�.");
		return FALSE;
	}

	m_Comm3.SetHwnd(this->m_hWnd);

	return TRUE;
}

void CKTmeasDlg::Kiethley_Connect()
{
	CString cmd;
	cmd.Format(_T("*CLS"));
	Write_Comm_CString3(cmd);
	Wait(10);
	cmd.Format(_T(":OUTP ON"));
	Write_Comm_CString3(cmd);
	Wait(10);
}

void CKTmeasDlg::Wait(DWORD dwMillisecond)
{
	MSG msg;
	DWORD dwStart;
	dwStart = GetTickCount();

	while(GetTickCount() - dwStart < dwMillisecond)
	{
		while(PeekMessage(&msg, NULL, 0,0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			if(m_RUN == FALSE){return;}
		}

	}
}

void CKTmeasDlg::Write_Comm_CString3(CString A_data)
{
	int buf_length = A_data.GetLength();
	char* buf = new char[buf_length+1];
	memset(buf,0,buf_length);
	buf = CString_To_Char(A_data);
	m_Comm3.WriteCommBlock(buf,buf_length);
	char start5 =0x0D;	//+CS
	m_Comm3.WriteCommBlock(&start5,1); //+CS
	//start5 =0x0A;	//+CS
	//m_Comm3.WriteCommBlock(&start5,1); //+CS
	delete []buf;
}



char* CKTmeasDlg::CString_To_Char(CString& str)
{
	long len = str.GetLength();
	len = len + 2;
	char *szTemp = new char[len+1];
	memset(szTemp,0,len+1);
	USES_CONVERSION;
	strcpy(szTemp,T2CA(str));

	return szTemp;
}

CString CKTmeasDlg::Keithley_Measure()
{
	CString check;
	CString str_out;

	Write_Comm_CString3("READ?");

	while(true)
	{
		check = Keithley_Meas.Right(1);
		Wait(100);
		if(check == "\n")
		{
			double t_Curr;
			t_Curr = (double)atof (Keithley_Meas);
			Keithley_Meas.Format(_T("%6.4lf"), t_Curr);
			str_out=Keithley_Meas;
			Keithley_Meas.Format(_T(" "));
			//AfxMessageBox(Keithley_Meas);
			return str_out;

		}
	}
}

LONG CKTmeasDlg::OnReceiveData(UINT wParam, LONG lParam)
{
	int nPort = LOWORD(lParam);
	int nLength = HIWORD(lParam);
	
	if(nPort == m_Comm3.m_nPort)
	{
		CString str;
		LONG ch;
		for(int i=0; i <nLength; i++)
		{
			ch=(int)m_Comm3.m_strData[i];
			str.Format(_T("%C"),ch);
			Keithley_Meas += str;
		}	
	}
	SetEvent(m_Comm.GetWaitObject());
	return 0;
}

void CKTmeasDlg::OnBnClickedButtonMeasure()
{
	m_Meas=Keithley_Measure();
	Wait(10);
	UpdateData(FALSE);
	Log("KT measure");
}


void CKTmeasDlg::OnBnClickedButtonStart()
{
	GV_ITEM Item;
	UpdateData(TRUE);

	CString strDate;
	CString strTime;
	CString time;
	CString repeat;
	AllGrid_Clear();
	ReGrid3();

	while(true)
	{
		CTime gct = CTime::GetCurrentTime();

		strDate.Format(_T("%d-%d-%d"),gct.GetYear(),gct.GetMonth(),gct.GetMinute());

		m_Repeat1=m_Repeat;
		while (m_Repeat >0)
		{
			CTime gct1 = gct + m_Time;
			while(true)
			{
				gct = CTime::GetCurrentTime();

				if (m_Repeat == m_Repeat1) 
				{
					if(m_Mode == 0)
					{
						m_OptiComp.CA210_Measure();

						m_nX.Format("%.4f",m_OptiComp.m_stXYLv.X);
						m_nY.Format("%.4f",m_OptiComp.m_stXYLv.Y);
						m_nLv.Format("%.4f",m_OptiComp.m_stXYLv.Lv);

						m_MeasG = ("");
					}
					if(m_Mode == 1)
					{
						m_MeasG=Keithley_Measure();
					}
					if(m_Mode == 2)
					{
						m_OptiComp.CA210_Measure();

						m_nX.Format("%.4f",m_OptiComp.m_stXYLv.X);
						m_nY.Format("%.4f",m_OptiComp.m_stXYLv.Y);
						m_nLv.Format("%.4f",m_OptiComp.m_stXYLv.Lv);

						m_MeasG=Keithley_Measure();
					}
					break;
				}

				if (gct >= gct1)
				{
					if(m_Mode == 0)
					{
						m_OptiComp.CA210_Measure();

						m_nX.Format("%.4f",m_OptiComp.m_stXYLv.X);
						m_nY.Format("%.4f",m_OptiComp.m_stXYLv.Y);
						m_nLv.Format("%.4f",m_OptiComp.m_stXYLv.Lv);

						m_MeasG = ("");
					}
					if(m_Mode == 1)
					{
						m_MeasG=Keithley_Measure();
					}
					if(m_Mode == 2)
					{
						m_OptiComp.CA210_Measure();

						m_nX.Format("%.4f",m_OptiComp.m_stXYLv.X);
						m_nY.Format("%.4f",m_OptiComp.m_stXYLv.Y);
						m_nLv.Format("%.4f",m_OptiComp.m_stXYLv.Lv);

						m_MeasG=Keithley_Measure();
					}
					break;
				}
			}
			strTime = gct.Format(_T("%H:%M:%S"));
			repeat.Format("%d",m_Repeat);
			m_Grid4.SetItemText(m_Repeat,0,repeat);
			m_Grid4.SetItemText(m_Repeat,1,strDate);
			m_Grid4.SetItemText(m_Repeat,2,strTime);
			m_Grid4.SetItemText(m_Repeat,3,m_MeasG);
			m_Grid4.SetItemText(m_Repeat,5,m_nX);
			m_Grid4.SetItemText(m_Repeat,6,m_nY);
			m_Grid4.SetItemText(m_Repeat,7,m_nLv);
			m_Grid4.RedrawRow(m_Repeat);
			m_Repeat--;
		}
	break;
	}
	Log("Stability finish");
}


void CKTmeasDlg::AllGrid_Clear()
{

	for(int k=1; k<m_Grid4.GetRowCount(); k++)
	{
		for(int i=1; i<m_Grid4.GetColumnCount(); i++)
		{
			m_Grid4.SetItemText(k,i," ");
			m_Grid4.RedrawRow(k);
		}
	}
}

void CKTmeasDlg::OnCbnSelchangeComboCom3()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}

void CKTmeasDlg::OnEnChangeEditRepeat()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialogEx::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.


	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}

void CKTmeasDlg::OnEnChangeEditMeasure()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialogEx::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.


	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}

void CKTmeasDlg::OnBnClickedButtonVolt()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	Write_Comm_CString3(":SYST:KEY 15");
	Log("Volt setting");
}

void CKTmeasDlg::OnBnClickedButtonCurr()
{
	Write_Comm_CString3(":SYST:KEY 22");
	Log("Curr setting");
}

void CKTmeasDlg::OnBnClickedCa310Measure()
{
	m_OptiComp.CA210_Measure();

	m_nX.Format("%.4f",m_OptiComp.m_stXYLv.X);
	m_nY.Format("%.4f",m_OptiComp.m_stXYLv.Y);
	m_nLv.Format("%.4f",m_OptiComp.m_stXYLv.Lv);
	UpdateData(FALSE);

	return ;
	Log("CA310 measure");
}



void CKTmeasDlg::OnBnClickedRadioCa()
{
	UpdateData(TRUE);
	m_Mode = 0;
	Log("CA310 check");

}
void CKTmeasDlg::OnBnClickedRadioKt()
{
	UpdateData(TRUE);
	m_Mode = 1;
	Log("keithly check");
}
void CKTmeasDlg::OnBnClickedRadioCakt()
{
	UpdateData(TRUE);
	m_Mode = 2;
	Log("CA_KT check");
}


void CKTmeasDlg::OnBnClickedButtonCsv()
{
	
	CFile Wfile;
	CString strFile_Name;
	CString strTemp;
	CString strFile_Write;


	UpdateData(TRUE);

    if(!Wfile.Open("Time_meas.csv", CFile::modeCreate | CFile::modeWrite))
    {
        MessageBox("Can't Create testfile.txt !", "Warning", MB_OK | MB_ICONHAND);
        return;
    }
	else
	{
		strFile_Write = _T("Repeat,Date,Time,Value,Unit,X,Y,Lv,\r\n");
		for(int i = 1; i< m_Repeat+1; i++){
			strTemp.Format(_T("%d,%s,%s,%f,%s,%f,%f,%f,\r\n"),atoi(m_Grid4.GetItemText(i,0)),m_Grid4.GetItemText(i,1),m_Grid4.GetItemText(i,2),atof(m_Grid4.GetItemText(i,3)),m_Grid4.GetItemText(i,4),atof(m_Grid4.GetItemText(i,5)),atof(m_Grid4.GetItemText(i,6)),atof(m_Grid4.GetItemText(i,7)));
			strFile_Write += strTemp;
		}
		char *cFile_Write = new char[strFile_Write.GetLength()+1];
		sprintf(cFile_Write, "%s", strFile_Write.GetBuffer());
		Wfile.Write(cFile_Write,strFile_Write.GetLength()+1);
		Wfile.Close();	
	}

	Log("CSV save");
	
	// ���� ���� ����
	/*
    char* ps = new char[27];
    char* ps2 = ps;
    for(int i=0;i<26;i++)
        *ps2++ = 'a'+i;
    *ps2 = NULL;    // NULL ���ڷ� ������ �Ѵ�.
    Wfile.Write(ps,27);
    Wfile.Close();
    delete ps;
	*/
	//���� �б� ����
	/*
	CFile Rfile;
    if(!Wfile.Open("TestFile.txt", CFile::modeRead))
    {
        MessageBox("Can't Open testfile.txt !", "Warning",
                        MB_OK | MB_ICONHAND);
        return;
    }
    UINT FileLength = (UINT)Rfile.GetLength();
    char* ps = new char[FileLength];
    Rfile.Read(ps,FileLength);
    Rfile.Close();
 
    CClientDC dc(this);
    dc.TextOut(0,0,ps,lstrlen(ps));
    delete ps;
	*/
}


void CKTmeasDlg::OnLvnItemchangedListctrl(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	*pResult = 0;
}

/*
void CKTmeasDlg::OnBnClickedListctrlAdd()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	int num = m_ListCtrl.GetItemCount();
	CString strDate;
	CString strTime;
	CTime gct = CTime::GetCurrentTime();
	strDate.Format(_T("%d/%d/%d-%d:%d"),gct.GetYear(),gct.GetMonth(),gct.GetDay(),gct.GetHour(),gct.GetMinute());

	CString str;
	str.Format(_T("%d"),num);

	m_ListCtrl.InsertItem(num,strDate);
	//m_ListCtrl.SetItem(num,1,LVIF_TEXT,_T("test"),NULL,NULL,NULL,NULL);

	CString str2;
	GetDlgItemText(IDC_LISTCTRL_EDIT,str2);

	m_ListCtrl.SetItem(num,2,LVIF_TEXT,str2,NULL,NULL,NULL,NULL);
}
*/
void CKTmeasDlg::Log(CString strLog2)
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	int num = m_ListCtrl.GetItemCount();
	CString strDate;
	CString strTime;
	CTime gct = CTime::GetCurrentTime();
	strDate.Format(_T("%d/%d/%d-%d:%d"),gct.GetYear(),gct.GetMonth(),gct.GetDay(),gct.GetHour(),gct.GetMinute());

	m_ListCtrl.InsertItem(num,strDate);

	m_ListCtrl.SetItem(num,1,LVIF_TEXT,strLog2,NULL,NULL,NULL,NULL);
}

void CKTmeasDlg::OnBnClickedListctrlDel()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	POSITION pos;
	pos = m_ListCtrl.GetFirstSelectedItemPosition();
	int idx = m_ListCtrl.GetNextSelectedItem(pos);
	m_ListCtrl.DeleteItem(idx);
}


void CKTmeasDlg::OnEnChangeListctrlEdit()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialogEx::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}
