#pragma once
#include "afxcmn.h"


// CTabLog 대화 상자입니다.

class CTabLog : public CDialogEx
{
	DECLARE_DYNAMIC(CTabLog)

public:
	CTabLog(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CTabLog();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_Log };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnLvnItemchangedListLog(NMHDR *pNMHDR, LRESULT *pResult);
	CListCtrl m_ListCtrl;
	void Log(CString strLog2);
};
