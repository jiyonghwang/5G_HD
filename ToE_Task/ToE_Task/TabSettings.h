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
	afx_msg void OnBnClickedBnFileOpen();
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnEnChangeEditPath();
	CString m_strFilePath;
	afx_msg void OnFileList2();
	afx_msg void OnBnClickedBnPathOpen();
	CEdit m_pathfile;
};
