
#pragma once
#include "afxwin.h"


// TabMain 대화 상자입니다.

class CTabMain : public CDialogEx
{
	DECLARE_DYNAMIC(CTabMain)

public:
	CTabMain(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CTabMain();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_Main };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBnStart();
	afx_msg void OnEnChangeEdit1();
	CEdit m_init;
	CEdit m_pin;
	CEdit m_slefcap;
	CEdit m_mutualcap;
	CEdit m_datacollect;
	CEdit m_autotune;
	afx_msg void OnEnChangeEditSelfCheck();
	afx_msg void OnEnChangeEditInit();
};
