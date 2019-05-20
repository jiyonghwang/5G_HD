
// KTmeasDlg.h : 헤더 파일
//

#pragma once
#include "afxwin.h"
#include "SerialComm.h"
#include <sys/timeb.h>
#include "afxcmn.h"
#include "Libs\GridCtrl\GridCtrl.h"
#include "D:\SW\5G_HD\KTmeas\KTmeas\Libs\GridCtrl\gridctrl.h"
#include "OpticalComp.h"


#define SAFE_DELETE(p) {if(p){delete p; p=NULL;}}


// CKTmeasDlg 대화 상자
class CKTmeasDlg : public CDialogEx
{
// 생성입니다.
public:
	CKTmeasDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

	UINT htimer;
// 대화 상자 데이터입니다.
	enum { IDD = IDD_KTMEAS_DIALOG };

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
	int ACK_Status;
	afx_msg void OnBnClickedOk();
	CComboBox m_cboPort3;
	afx_msg void OnBnClickedCheckCom1();
	CButton m_ButPort1;
	CButton m_ButPort3;
	BOOL m_bComConnect;
	BOOL m_bComConnect3;
	BOOL SetComPort(int nPort);
	BOOL SetComPort3(int nPort);
	CSerialComm m_Comm;
	CSerialComm m_Comm3;

	COpticalComp m_OptiComp;
	CString m_nX;
	CString m_nY;
	CString m_nLv;

	afx_msg void OnCbnSelchangeComboCom3();
	CComboBox m_cboPort2;
	afx_msg void OnBnClickedCheckCom3();
	void Kiethley_Connect();
	void Write_Comm_CString3(CString A_data);
	CString Keithley_Meas;
	LONG OnReceiveData(UINT wParam, LONG lParam);
	CString Keithley_Measure();
	void Wait(DWORD dwMillisecond);
	char* CString_To_Char(CString& str);
	BOOL m_RUN;

	int m_Repeat;
	int m_Repeat1;
	int m_Time;
	int m_Time1;
	SYSTEMTIME cur_time;

	afx_msg void OnEnChangeEditRepeat();
	afx_msg void OnBnClickedButtonStart();
	afx_msg void OnBnClickedButtonMeasure();
	CString m_Meas;
	CString m_MeasG;
	afx_msg void OnEnChangeEditMeasure();
	CGridCtrl m_Grid4;
	void InitGrid4();
	void ReGrid3();
	void AllGrid_Clear();
	void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);

	afx_msg void OnBnClickedButtonVolt();
	afx_msg void OnBnClickedButtonCurr();

	afx_msg void OnBnClickedRadioCa();
	afx_msg void OnBnClickedCa310Measure();
	afx_msg void OnBnClickedOptiInit1();

	int m_Mode;
	afx_msg void OnBnClickedRadioKt();
	afx_msg void OnBnClickedRadioCakt();

	afx_msg void OnBnClickedButtonCsv();

	CListCtrl m_ListCtrl;
	afx_msg void OnLvnItemchangedListctrl(NMHDR *pNMHDR, LRESULT *pResult);
	//afx_msg void OnBnClickedListctrlAdd();
	afx_msg void OnBnClickedListctrlDel();
	afx_msg void OnEnChangeListctrlEdit();
	void Log(CString strLog2);
};
