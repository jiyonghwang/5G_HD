#pragma once


// TabMain1 대화 상자입니다.

class TabMain1 : public CDialogEx
{
	DECLARE_DYNAMIC(TabMain1)

public:
	TabMain1(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~TabMain1();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_Main };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
};
