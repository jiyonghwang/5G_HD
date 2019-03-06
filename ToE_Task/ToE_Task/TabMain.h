#pragma once


// CTabMain 대화 상자입니다.

class CTabMain : public CDialogEx
{
	DECLARE_DYNAMIC(CTabMain)

public:
	CTabMain(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CTabMain();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_Log };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};
#pragma once


// TabMain 대화 상자입니다.

class TabMain : public CDialogEx
{
	DECLARE_DYNAMIC(TabMain)

public:
	TabMain(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~TabMain();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_Main };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
};
