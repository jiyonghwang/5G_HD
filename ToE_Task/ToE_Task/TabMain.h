#pragma once


// CTabMain ��ȭ �����Դϴ�.

class CTabMain : public CDialogEx
{
	DECLARE_DYNAMIC(CTabMain)

public:
	CTabMain(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CTabMain();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_Log };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};
#pragma once


// TabMain ��ȭ �����Դϴ�.

class TabMain : public CDialogEx
{
	DECLARE_DYNAMIC(TabMain)

public:
	TabMain(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~TabMain();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_Main };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
};
