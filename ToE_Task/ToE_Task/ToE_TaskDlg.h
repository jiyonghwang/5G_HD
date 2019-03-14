
// ToE_TaskDlg.h : 헤더 파일
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"

class CTabLog;
class CTabMain;
class CTabSettings;

// CToE_TaskDlg 대화 상자
class CToE_TaskDlg : public CDialogEx
{
// 생성입니다.
public:
	CToE_TaskDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

	CTabLog *pDlgLog;
	CTabMain *pDlgMain;
	CTabSettings *pDlgSettings;


// 대화 상자 데이터입니다.
	enum { IDD = IDD_TOE_TASK_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
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
