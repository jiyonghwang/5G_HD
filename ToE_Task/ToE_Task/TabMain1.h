#pragma once


// TabMain1 ��ȭ �����Դϴ�.

class TabMain1 : public CDialogEx
{
	DECLARE_DYNAMIC(TabMain1)

public:
	TabMain1(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~TabMain1();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_Main };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
};
