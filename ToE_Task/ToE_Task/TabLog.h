#pragma once


// CTabLog ��ȭ �����Դϴ�.

class CTabLog : public CDialogEx
{
	DECLARE_DYNAMIC(CTabLog)

public:
	CTabLog(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CTabLog();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_Log };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};
