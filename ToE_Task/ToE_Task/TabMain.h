
#pragma once
#include "afxwin.h"


// TabMain ��ȭ �����Դϴ�.

class CTabMain : public CDialogEx
{
	DECLARE_DYNAMIC(CTabMain)

public:
	CTabMain(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CTabMain();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_Main };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

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
