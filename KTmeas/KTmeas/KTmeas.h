
// KTmeas.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.

// CKTmeasApp:
// �� Ŭ������ ������ ���ؼ��� KTmeas.cpp�� �����Ͻʽÿ�.
//

class CKTmeasApp : public CWinApp
{
public:
	CKTmeasApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CKTmeasApp theApp;