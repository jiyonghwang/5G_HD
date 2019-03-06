#pragma once


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
};
