
// ToE_TaskDlg.h : ��� ����
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"

class CTabLog;
class CTabMain;
class CTabSettings;

// CToE_TaskDlg ��ȭ ����
class CToE_TaskDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CToE_TaskDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

	CTabLog *pDlgLog;
	CTabMain *pDlgMain;
	CTabSettings *pDlgSettings;


// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_TOE_TASK_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CTabCtrl m_Tab;
	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnFileListMain();
	afx_msg void OnFileListSettings();
	afx_msg void OnFileListLog();

};
