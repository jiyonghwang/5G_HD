#pragma once


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
};
