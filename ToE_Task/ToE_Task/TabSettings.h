#pragma once
#include "afxwin.h"


// CTabSettings 대화 상자입니다.

class CTabSettings : public CDialogEx
{
	DECLARE_DYNAMIC(CTabSettings)

public:
	CTabSettings(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CTabSettings();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_Settings };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();

	afx_msg void OnEnChangeEditPath();
	CString m_strFilePath;
	afx_msg void OnBnClickedBnPathOpen();
	CEdit m_pathfile;
	afx_msg void OnBnClickedBnPathRead();
	CEdit m_Loading;
	afx_msg void OnEnChangeEditLoading();
	afx_msg void OnBnClickedBnFileLoading();

};
