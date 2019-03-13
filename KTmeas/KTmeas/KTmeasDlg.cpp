
// KTmeasDlg.cpp : 구현 파일
//
//test1


#include "stdafx.h"
#include "KTmeas.h"
#include "KTmeasDlg.h"
#include "afxdialogex.h"
#define USER_TIMER 1000
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define _CRT_SECURE_NO_WARNINGS

// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
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


// CKTmeasDlg 대화 상자

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


// CKTmeasDlg 메시지 처리기

BOOL CKTmeasDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
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

	// 이 대화 상자의 아이콘을 설정합니다. 응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.
	
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

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	GetDlgItem(IDC_CA310_Measure)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_MEASURE)->EnableWindow(FALSE);

	CRect rt;
	m_ListCtrl.GetWindowRect(&rt);
	m_ListCtrl.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

	m_ListCtrl.InsertColumn(0,_T("시간"),LVCFMT_LEFT,rt.Width()*0.5);
	m_ListCtrl.InsertColumn(1,_T("내용"),LVCFMT_CENTER,rt.Width()*0.5);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
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

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다. 문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CKTmeasDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CKTmeasDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CKTmeasDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
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
			GetDlgItem(IDC_CA310_Measure)->EnableWindow(TRUE);      // CA310 연결 하면 measuer 버튼 활성화
			m_ButPort1.SetWindowText("Connected");
			m_ButPort1.SetCheck(true);   //체크 해제 -> 체크
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
	//포트의 컴포트를 맞춘다.
	m_Comm.SetComPort(nPort, 38400, 7, TWOSTOPBITS, EVENPARITY);

	//포트의 컴포트를 연다
	if (m_Comm.OpenComPort() == FALSE)
	{
		AfxMessageBox("통신을 연결할 수 없습니다.");
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
			m_ButPort3.SetCheck(true);   //체크 해제 -> 체크 
		}
		else
		{
			m_ButPort3.SetCheck(false);  //체크 -> 체크 해제
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
	//포트의 컴포트를 맞춘다.
	m_Comm3.SetComPort(nPort, 57600, 8, ONESTOPBIT, NOPARITY);

	//포트의 컴포트를 연다
	if (m_Comm3.OpenComPort() == FALSE)
	{
		AfxMessageBox("통신을 연결할 수 없습니다.");
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
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CKTmeasDlg::OnEnChangeEditRepeat()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.


	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CKTmeasDlg::OnEnChangeEditMeasure()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.


	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CKTmeasDlg::OnBnClickedButtonVolt()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
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
	
	// 파일 쓰기 예제
	/*
    char* ps = new char[27];
    char* ps2 = ps;
    for(int i=0;i<26;i++)
        *ps2++ = 'a'+i;
    *ps2 = NULL;    // NULL 문자로 끝나게 한다.
    Wfile.Write(ps,27);
    Wfile.Close();
    delete ps;
	*/
	//파일 읽기 예제
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
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
}

/*
void CKTmeasDlg::OnBnClickedListctrlAdd()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
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
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
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
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	POSITION pos;
	pos = m_ListCtrl.GetFirstSelectedItemPosition();
	int idx = m_ListCtrl.GetNextSelectedItem(pos);
	m_ListCtrl.DeleteItem(idx);
}


void CKTmeasDlg::OnEnChangeListctrlEdit()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
