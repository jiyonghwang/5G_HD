#pragma once
#include "afxcmn.h"


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
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnLvnItemchangedListLog(NMHDR *pNMHDR, LRESULT *pResult);
	CListCtrl m_ListCtrl;
	void Log(CString strLog2);
};
