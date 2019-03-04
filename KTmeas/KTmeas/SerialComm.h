// SerialComm.h : interface of the CSerialComm class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SERIALCOMM_H__169BBC89_CD3A_11D5_BB72_00504D0079F3__INCLUDED_)
#define AFX_SERIALCOMM_H__169BBC89_CD3A_11D5_BB72_00504D0079F3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define READ_BUFFER_SIZE	4096
#define WRITE_BUFFER_SIZE	4096

// Ascii Definitions
#define ASCII_BEL			0x07
#define ASCII_BS			0x08
#define ASCII_LF			0x0A
#define ASCII_CR			0x0D
#define ASCII_XON			0x11
#define ASCII_XOFF			0x13

#define WM_RECEIVEDATA		WM_USER + 1

/////////////////////////////////////////////////////////////////////////////
// CSerialComm class

class CSerialComm : public CObject
{
	DECLARE_DYNCREATE(CSerialComm)

public:
	HANDLE m_hComDev;						// handle of communication device
	HANDLE m_hThread;						// handle of the communication thread
	
	BOOL m_bConnected;						// 컴포트가 연결되면 1로 설정
	DWORD m_nTimeout;						// 타임아웃 측정

public:
	BYTE m_strData[READ_BUFFER_SIZE];		// 컴포트에서 들어오는 데이타
	HWND m_hMsgWnd;							// 메세지를 전달할 윈도우 플러그

	CRITICAL_SECTION m_crWrite;
	
// Construction & Destruction
public:
	CSerialComm();
	virtual ~CSerialComm();

// Attributes
	BOOL IsConnect() { return m_bConnected; }
	void SetHwnd(HWND hwnd);				// Msg를 보낼 Window Handle을 설정한다
	//컴포트를 설정함
	void SetComPort(int Port = 1, DWORD Baudrate = 9600, BYTE DataBits = 8, BYTE StopBits = ONESTOPBIT, BYTE Parity = NOPARITY);

// Operations
	BOOL OpenComPort();						// 컴포트를 열고 연결을 시도한다.
	BOOL DestroyComm();						// 컴포트를 해제한다
	BOOL WriteCommBlock(LPCTSTR, DWORD);	// 컴포트에 데이타를 넣는다

	BOOL SetupConnection();					// 포트를 연결한다
	BOOL CloseConnection();					// 연결을 해제한다
	BOOL CreateCommInfo();					// com 포트를 만든다
	int  ReadCommBlock(LPSTR, int);			// 컴포트에서 데이타를 받는다	

	HANDLE GetWaitObject(void) { return m_hWait; }
	
	virtual void SetReadData(int nPort, LPSTR data, int nLength);	//읽은 데이타를 버퍼에 저장한다.

public:
	int m_nPort;
	DWORD m_dwBaudrate;
	int m_nDataBits;
	int	m_nStopBits;
	int	m_nParity;

	HANDLE m_hWait;

	OVERLAPPED m_osWrite;
	OVERLAPPED m_osRead;
	friend DWORD WINAPI ComWatchThread(LPVOID lpData);
};


/////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SERIALCOMM_H__169BBC89_CD3A_11D5_BB72_00504D0079F3__INCLUDED_)
