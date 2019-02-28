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

//메세지를 전달할 hwnd설정
void CSerialComm::SetHwnd(HWND hwnd)
{
	m_hMsgWnd=hwnd;
}

//컴포트를 설정한다.
void CSerialComm::SetComPort(int Port, DWORD Baudrate, BYTE DataBits, BYTE StopBits, BYTE Parity)
{
	m_nPort		 = Port;
	m_dwBaudrate = Baudrate;
	m_nDataBits	 = DataBits;
	m_nStopBits	 = StopBits;
	m_nParity	 = Parity;
}

//컴포트 정보를 만든다.
//이것을 만들때 이전에 할일이
// SetComPort(); -> SetXonOff() ->SetDtrRts() 한다음 설정한다.
BOOL CSerialComm::CreateCommInfo()
{
	memset(&m_osWrite, 0, sizeof(m_osWrite));
	memset(&m_osRead, 0, sizeof(m_osRead));
	
	//이벤트 창구 설정
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

// com 포트를 열고 연결을 시도한다.
// OpenComport()
BOOL CSerialComm::OpenComPort()
{            
	char szPort[15];
	BOOL bRet;
	COMMTIMEOUTS  CommTimeOuts;

	if (CreateCommInfo() == FALSE) return FALSE;

	if (m_nPort < 10) wsprintf(szPort, "COM%d", m_nPort);
	else			  wsprintf(szPort, "\\\\.\\COM%d", m_nPort);
	
	// COMM device를 화일형식으로 연결한다.
	m_hComDev = CreateFile(szPort,
						   GENERIC_READ | GENERIC_WRITE,
						   0,                    // exclusive access
						   NULL,                 // no security attrs
						   OPEN_EXISTING,
						   FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, // overlapped I/O
						   NULL);

	if (m_hComDev == (HANDLE) INVALID_HANDLE_VALUE)
		return ( FALSE );

	//컴포트에서 데이타를 교환하는 방법을 char단위를 기본으로 설정하자
	SetCommMask(m_hComDev, EV_RXCHAR);
	SetupComm(m_hComDev, READ_BUFFER_SIZE, WRITE_BUFFER_SIZE);
	//디바이스에 쓰레기가 있을지 모르니까 깨끗이 청소를 하자!
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
	if (bRet)//연결이 되었다면 bRet TRUE이므로
	{
		m_bConnected = TRUE;//연결되었다고 말해줌
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

//화일로 설정된 컴포트와 실질 포트와 연결을 시킨다.
//SetupConnection 이전에 CreateComPort를 해주어야 한다.
BOOL CSerialComm::SetupConnection()
{
	BOOL bRet;
	DCB dcb;

	GetCommState(m_hComDev, &dcb);			//dcb의 기본값을 받는다.

	dcb.DCBlength = sizeof(DCB);

	//이부분을 수정해야 합니다.
	dcb.BaudRate = m_dwBaudrate;			//전송속도
	dcb.ByteSize = m_nDataBits;				//데이타비트
	dcb.Parity	= m_nParity;				//패리티 체크
	dcb.StopBits = m_nStopBits;				//스톱비트

	dcb.fOutxDsrFlow = 0;					//Dsr Flow
	dcb.fDtrControl = DTR_CONTROL_ENABLE;	//Dtr Control
	dcb.fOutxCtsFlow = 0;					//Cts Flow
	dcb.fRtsControl = RTS_CONTROL_ENABLE;	//Ctr Control
	dcb.fInX = dcb.fOutX = 0;				//XON/XOFF 관한것
	dcb.XonChar = ASCII_XON;
	dcb.XoffChar = ASCII_XOFF;
	dcb.XonLim = 100;
	dcb.XoffLim = 100;
	dcb.fBinary = TRUE;
	dcb.fParity = TRUE;

	
	//	dcb.EvtChar = '\n';

	bRet = SetCommState(m_hComDev, &dcb);	//변경된 Dcb 설정

	return bRet;
} 

//컴포트로 부터 데이타를 읽는다.
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
			//이곳에 에라를 넣는것이다.
			//즉 ReadFile 했을때 데이타가 제대로 안나오면 fReadState에 여러
			//에라 코드를 리턴한다. 이때 복구할수있으면 좋지만 실질적인
			//복구가 불가능하다 따라서 재송출을 해달라는 메세지를 해주는것이
			//좋다.
			TRACE("ReadCommBlock> Error while Readfile\r\n");
		}
		ResetEvent(m_osRead.hEvent);
	}
	
	return dwLength;
} 

//컴포트를 완전히 해제한다.
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

//연결을 닫는다.
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
		//컴포트에 데이타를 제대로 써넣지 못했을경우이다.
		//이때는 어떻게 할까 그것은 사용자 마음이겠다.
		//다시 보내고 싶으면 제귀송출을 하면 된다.
		//그러나 주의점 무한 루프를 돌수 있다는 점을 생각하라.
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
// 통신을 하는 프로세저 즉 데이타가 들어왔을대 감시하는
// 루틴 본루틴은 OpenComPort 함수 실행시 프로시저로 연결됨
// OpenComPort 함수 참조
DWORD WINAPI ComWatchThread(LPVOID lpData)
{
	DWORD dwEvtMask;
	OVERLAPPED os;
	CSerialComm* npComm = (CSerialComm*)lpData;
	char InData[READ_BUFFER_SIZE];
	int	 nLength;

	// idCommDev 라는 핸들에 아무런 com 포트가 안붙어 있으면 error return
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
