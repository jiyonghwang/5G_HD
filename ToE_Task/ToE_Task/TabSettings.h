#pragma once
#include "afxwin.h"


// CTabSettings ��ȭ �����Դϴ�.

class CTabSettings : public CDialogEx
{
	DECLARE_DYNAMIC(CTabSettings)

public:
	CTabSettings(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CTabSettings();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_Settings };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

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
