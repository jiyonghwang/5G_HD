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
	
	BOOL m_bConnected;						// ����Ʈ�� ����Ǹ� 1�� ����
	DWORD m_nTimeout;						// Ÿ�Ӿƿ� ����

public:
	BYTE m_strData[READ_BUFFER_SIZE];		// ����Ʈ���� ������ ����Ÿ
	HWND m_hMsgWnd;							// �޼����� ������ ������ �÷���

	CRITICAL_SECTION m_crWrite;
	
// Construction & Destruction
public:
	CSerialComm();
	virtual ~CSerialComm();

// Attributes
	BOOL IsConnect() { return m_bConnected; }
	void SetHwnd(HWND hwnd);				// Msg�� ���� Window Handle�� �����Ѵ�
	//����Ʈ�� ������
	void SetComPort(int Port = 1, DWORD Baudrate = 9600, BYTE DataBits = 8, BYTE StopBits = ONESTOPBIT, BYTE Parity = NOPARITY);

// Operations
	BOOL OpenComPort();						// ����Ʈ�� ���� ������ �õ��Ѵ�.
	BOOL DestroyComm();						// ����Ʈ�� �����Ѵ�
	BOOL WriteCommBlock(LPCTSTR, DWORD);	// ����Ʈ�� ����Ÿ�� �ִ´�

	BOOL SetupConnection();					// ��Ʈ�� �����Ѵ�
	BOOL CloseConnection();					// ������ �����Ѵ�
	BOOL CreateCommInfo();					// com ��Ʈ�� �����
	int  ReadCommBlock(LPSTR, int);			// ����Ʈ���� ����Ÿ�� �޴´�	

	HANDLE GetWaitObject(void) { return m_hWait; }
	
	virtual void SetReadData(int nPort, LPSTR data, int nLength);	//���� ����Ÿ�� ���ۿ� �����Ѵ�.

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
