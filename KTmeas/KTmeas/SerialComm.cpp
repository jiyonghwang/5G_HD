#include "stdafx.h"
#include "SerialComm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSerialComm

IMPLEMENT_DYNCREATE(CSerialComm, CObject)

CSerialComm::CSerialComm( )
{
	m_hComDev	 = NULL;
	m_bConnected = FALSE;

	m_nPort		 = 1;
	m_dwBaudrate = 9600;
	m_nDataBits	 = 8;
	m_nStopBits	 = ONESTOPBIT;
	m_nParity	 = NOPARITY;

	InitializeCriticalSection(&m_crWrite);
}

CSerialComm::~CSerialComm( )
{
	DestroyComm();

	DeleteCriticalSection(&m_crWrite);
}

void CSerialComm::SetReadData(int nPort, LPSTR data, int nLength)
{
	lstrcpy((LPSTR)m_strData, (LPSTR)data);
	SendMessage(m_hMsgWnd, WM_RECEIVEDATA, (WPARAM)data, MAKELPARAM(nPort, nLength));
}

//�޼����� ������ hwnd����
void CSerialComm::SetHwnd(HWND hwnd)
{
	m_hMsgWnd=hwnd;
}

//����Ʈ�� �����Ѵ�.
void CSerialComm::SetComPort(int Port, DWORD Baudrate, BYTE DataBits, BYTE StopBits, BYTE Parity)
{
	m_nPort		 = Port;
	m_dwBaudrate = Baudrate;
	m_nDataBits	 = DataBits;
	m_nStopBits	 = StopBits;
	m_nParity	 = Parity;
}

//����Ʈ ������ �����.
//�̰��� ���鶧 ������ ������
// SetComPort(); -> SetXonOff() ->SetDtrRts() �Ѵ��� �����Ѵ�.
BOOL CSerialComm::CreateCommInfo()
{
	memset(&m_osWrite, 0, sizeof(m_osWrite));
	memset(&m_osRead, 0, sizeof(m_osRead));
	
	//�̺�Ʈ â�� ����
	m_osRead.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL); 
	if (m_osRead.hEvent == NULL)
	{
		CloseHandle(m_osRead.hEvent);
		return FALSE;
	}
	m_osWrite.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	if (NULL == m_osWrite.hEvent)
	{
		CloseHandle(m_osWrite.hEvent);
		return FALSE;
	}
	
	return TRUE;
} 

// com ��Ʈ�� ���� ������ �õ��Ѵ�.
// OpenComport()
BOOL CSerialComm::OpenComPort()
{            
	char szPort[15];
	BOOL bRet;
	COMMTIMEOUTS  CommTimeOuts;

	if (CreateCommInfo() == FALSE) return FALSE;

	if (m_nPort < 10) wsprintf(szPort, "COM%d", m_nPort);
	else			  wsprintf(szPort, "\\\\.\\COM%d", m_nPort);
	
	// COMM device�� ȭ���������� �����Ѵ�.
	m_hComDev = CreateFile(szPort,
						   GENERIC_READ | GENERIC_WRITE,
						   0,                    // exclusive access
						   NULL,                 // no security attrs
						   OPEN_EXISTING,
						   FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, // overlapped I/O
						   NULL);

	if (m_hComDev == (HANDLE) INVALID_HANDLE_VALUE)
		return ( FALSE );

	//����Ʈ���� ����Ÿ�� ��ȯ�ϴ� ����� char������ �⺻���� ��������
	SetCommMask(m_hComDev, EV_RXCHAR);
	SetupComm(m_hComDev, READ_BUFFER_SIZE, WRITE_BUFFER_SIZE);
	//����̽��� �����Ⱑ ������ �𸣴ϱ� ������ û�Ҹ� ����!
	PurgeComm(m_hComDev, PURGE_TXABORT | PURGE_RXABORT | PURGE_TXCLEAR | PURGE_RXCLEAR);
	
	//CommTimeOuts.ReadIntervalTimeout = 0xFFFFFFFF ;
	//CommTimeOuts.ReadTotalTimeoutMultiplier = 0;
	//CommTimeOuts.ReadTotalTimeoutConstant = 1000;	// ORG
	//CommTimeOuts.WriteTotalTimeoutMultiplier = 0;
	//CommTimeOuts.WriteTotalTimeoutConstant = 1000;

	CommTimeOuts.ReadIntervalTimeout = 0xFFFFFFFF;
	CommTimeOuts.ReadTotalTimeoutMultiplier = 0;
	CommTimeOuts.ReadTotalTimeoutConstant = 0;
	CommTimeOuts.WriteTotalTimeoutMultiplier = 0;
	CommTimeOuts.WriteTotalTimeoutConstant = 1000;


	SetCommTimeouts(m_hComDev, &CommTimeOuts);

	m_hWait = CreateEvent(NULL, FALSE, FALSE, NULL);

	bRet = SetupConnection();
	if (bRet)//������ �Ǿ��ٸ� bRet TRUE�̹Ƿ�
	{
		m_bConnected = TRUE;//����Ǿ��ٰ� ������
		DWORD nThreadID = 0;

		m_hThread = ::CreateThread(NULL,
								   0,
								   ComWatchThread,
								   this,
								   0,
								   &nThreadID );
		if (m_hThread == NULL)
		{
			MessageBox(NULL, "Cannot Create a Transmittion Thread.", "ERROR", MB_OK);
		}
	}
	else
	{
		m_bConnected = FALSE;
		CloseHandle(m_hComDev);
	}
	
	return bRet;
} 

//ȭ�Ϸ� ������ ����Ʈ�� ���� ��Ʈ�� ������ ��Ų��.
//SetupConnection ������ CreateComPort�� ���־�� �Ѵ�.
BOOL CSerialComm::SetupConnection()
{
	BOOL bRet;
	DCB dcb;

	GetCommState(m_hComDev, &dcb);			//dcb�� �⺻���� �޴´�.

	dcb.DCBlength = sizeof(DCB);

	//�̺κ��� �����ؾ� �մϴ�.
	dcb.BaudRate = m_dwBaudrate;			//���ۼӵ�
	dcb.ByteSize = m_nDataBits;				//����Ÿ��Ʈ
	dcb.Parity	= m_nParity;				//�и�Ƽ üũ
	dcb.StopBits = m_nStopBits;				//�����Ʈ

	dcb.fOutxDsrFlow = 0;					//Dsr Flow
	dcb.fDtrControl = DTR_CONTROL_ENABLE;	//Dtr Control
	dcb.fOutxCtsFlow = 0;					//Cts Flow
	dcb.fRtsControl = RTS_CONTROL_ENABLE;	//Ctr Control
	dcb.fInX = dcb.fOutX = 0;				//XON/XOFF ���Ѱ�
	dcb.XonChar = ASCII_XON;
	dcb.XoffChar = ASCII_XOFF;
	dcb.XonLim = 100;
	dcb.XoffLim = 100;
	dcb.fBinary = TRUE;
	dcb.fParity = TRUE;

	
	//	dcb.EvtChar = '\n';

	bRet = SetCommState(m_hComDev, &dcb);	//����� Dcb ����

	return bRet;
} 

//����Ʈ�� ���� ����Ÿ�� �д´�.
int CSerialComm::ReadCommBlock(LPSTR lpszBlock, int nMaxLength)
{
	BOOL fReadStat;
	COMSTAT ComStat;
	DWORD dwErrorFlags;
	DWORD dwLength;
	
	// only try to read number of bytes in queue 
	ClearCommError(m_hComDev, &dwErrorFlags, &ComStat);
	if (dwErrorFlags > 0)
	{
		switch(dwErrorFlags)
		{
		case CE_BREAK:	  TRACE("CSerialComm::ReadCommBlock> CE_BREAK Error.\n");	 break;
		case CE_DNS:	  TRACE("CSerialComm::ReadCommBlock> CE_DNS Error.\n");	     break;
		case CE_FRAME:	  TRACE("CSerialComm::ReadCommBlock> CE_FRAME Error.\n");	 break;
		case CE_IOE:	  TRACE("CSerialComm::ReadCommBlock> CE_IOE Error.\n");	     break;
		case CE_MODE:	  TRACE("CSerialComm::ReadCommBlock> CE_MODE Error.\n");	 break;
		case CE_OOP:	  TRACE("CSerialComm::ReadCommBlock> CE_OOP Error.\n");	     break;
		case CE_OVERRUN:  TRACE("CSerialComm::ReadCommBlock> CE_OVERRUN Error.\n");  break;
		case CE_PTO:	  TRACE("CSerialComm::ReadCommBlock> CE_PTO Error.\n");      break;
		case CE_RXOVER:	  TRACE("CSerialComm::ReadCommBlock> CE_RXOVER Error.\n");   break;
		case CE_RXPARITY: TRACE("CSerialComm::ReadCommBlock> CE_RXPARITY Error.\n"); break;
		case CE_TXFULL:	  TRACE("CSerialComm::ReadCommBlock> CE_TXFULL Error.\n");   break;
		}
	}
	dwLength = min((DWORD)nMaxLength, ComStat.cbInQue);

	if (dwLength > 0)
	{
		fReadStat = ReadFile(m_hComDev, lpszBlock, dwLength, &dwLength, &m_osRead);
		if (!fReadStat)
		{
			//�̰��� ���� �ִ°��̴�.
			//�� ReadFile ������ ����Ÿ�� ����� �ȳ����� fReadState�� ����
			//���� �ڵ带 �����Ѵ�. �̶� �����Ҽ������� ������ ��������
			//������ �Ұ����ϴ� ���� ������� �ش޶�� �޼����� ���ִ°���
			//����.
			TRACE("ReadCommBlock> Error while Readfile\r\n");
		}
		ResetEvent(m_osRead.hEvent);
	}
	
	return dwLength;
} 

//����Ʈ�� ������ �����Ѵ�.
BOOL CSerialComm::DestroyComm()
{
   if (m_bConnected)
   {
	   CloseConnection();
	   CloseHandle(m_osRead.hEvent);
	   CloseHandle(m_osWrite.hEvent);
   	   CloseHandle(m_hWait) ;
	}

   return TRUE;
} 

//������ �ݴ´�.
BOOL CSerialComm::CloseConnection()
{
	// set connected flag to FALSE
	m_bConnected = FALSE;
	
	SetCommMask(m_hComDev, 0);
	
	EscapeCommFunction(m_hComDev, CLRDTR);
	
	PurgeComm(m_hComDev, PURGE_TXABORT | PURGE_RXABORT | PURGE_TXCLEAR | PURGE_RXCLEAR);
	CloseHandle(m_hComDev);

	// added by amugeona
	// terminate the communication thread
	DWORD dwExitCode;

	if (GetExitCodeThread(m_hThread, &dwExitCode) && (dwExitCode == STILL_ACTIVE))
	{
		TerminateThread(m_hThread, 101);
		Sleep(500);
	}

	return TRUE;
} 

BOOL CSerialComm::WriteCommBlock( LPCTSTR lpByte , DWORD dwBytesToWrite)
{
	BOOL fWriteStat;
	DWORD dwBytesWritten ;

	EnterCriticalSection(&m_crWrite);

	fWriteStat = WriteFile(m_hComDev, lpByte, dwBytesToWrite, &dwBytesWritten, &m_osWrite);
//	TRACE("WriteCommBlock> %d byte send.\r\n", dwBytesToWrite);

	if (!fWriteStat)
	{
		//����Ʈ�� ����Ÿ�� ����� ����� ����������̴�.
		//�̶��� ��� �ұ� �װ��� ����� �����̰ڴ�.
		//�ٽ� ������ ������ ���ͼ����� �ϸ� �ȴ�.
		//�׷��� ������ ���� ������ ���� �ִٴ� ���� �����϶�.
		if (GetLastError() == ERROR_IO_PENDING)
		{
			DWORD dwBytesWritten = 0;
			while (!GetOverlappedResult(m_hComDev, &m_osWrite, &dwBytesWritten, FALSE))
			{
				DWORD dwError = GetLastError();
				if(dwError == ERROR_IO_INCOMPLETE)
				{	// normal result if not finished
					continue;
				}
				else
				{	// an error occurred, try to recover
					TRACE("CSerialComm::WriteCommBlock> on IO_PENDING, Error Code = %8x\n", dwError);

					DWORD dwErrorFlags = 0;
					COMSTAT ComStat;

					ClearCommError(m_hComDev, &dwErrorFlags, &ComStat);
					if (dwErrorFlags > 0)
						TRACE("CSerialComm::WriteCommBlock> Error Flags = %08x\n", dwErrorFlags);
					break;
				}
			}
		}
		else
		{	// some other error.
			DWORD dwErrorFlags = 0; 
			COMSTAT ComStat;

//			TRACE("CSerialComm::WriteCommBlock> GetLastError() returns %u\n", GetLastError());

			ClearCommError(m_hComDev, &dwErrorFlags, &ComStat);
			if (dwErrorFlags > 0)
			{
				TRACE("CSerialComm::WriteCommBlock> on non-IO_PANDING, Error Flags = %08x\n", 
					  dwErrorFlags);
			}
		}
	}

	LeaveCriticalSection(&m_crWrite);
//	TRACE("WriteCommBlock> Transferred successfully.\r\n");

 	return TRUE;
} 


/////////////////////////////////////////////////////////////////////////////
// ComWatchProc()
// ����� �ϴ� ���μ��� �� ����Ÿ�� �������� �����ϴ�
// ��ƾ ����ƾ�� OpenComPort �Լ� ����� ���ν����� �����
// OpenComPort �Լ� ����
DWORD WINAPI ComWatchThread(LPVOID lpData)
{
	DWORD dwEvtMask;
	OVERLAPPED os;
	CSerialComm* npComm = (CSerialComm*)lpData;
	char InData[READ_BUFFER_SIZE];
	int	 nLength;

	// idCommDev ��� �ڵ鿡 �ƹ��� com ��Ʈ�� �Ⱥپ� ������ error return
	if (npComm == NULL || !npComm->IsKindOf(RUNTIME_CLASS(CSerialComm)))
		return (DWORD)(-1);

	memset(&os, 0, sizeof(OVERLAPPED));	
	
	os.hEvent = CreateEvent(NULL,		// no security
                            TRUE,		// explicit reset req
                            FALSE,		// initial event reset
                            NULL );		// no name

	if (os.hEvent == NULL)
	{
		MessageBox(NULL, "Failed to create event for thread!", "comm Error!", MB_ICONEXCLAMATION | MB_OK);
		return FALSE;
	}

	if (!SetCommMask(npComm->m_hComDev, EV_RXCHAR))	return FALSE;

	while (npComm->m_bConnected)
	{
		dwEvtMask = 0;
		
		WaitCommEvent(npComm->m_hComDev, &dwEvtMask, NULL);
		Sleep(1);
		if ((dwEvtMask & EV_RXCHAR) == EV_RXCHAR)
		{
			do
			{
				memset(InData,0,READ_BUFFER_SIZE);
				if (nLength = npComm->ReadCommBlock((LPSTR)InData, READ_BUFFER_SIZE))
				{
					if (npComm) npComm->SetReadData(npComm->m_nPort, InData, nLength);
				}
			}
			while (nLength > 0 && npComm->m_bConnected);
		}
	}

	SetEvent(npComm->m_hThread);

	CloseHandle(os.hEvent);

	return 100;
} 
