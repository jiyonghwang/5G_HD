// DLL_Compensation.h : DLL_Compensation DLL�� �⺻ ��� �����Դϴ�.
//
extern "C" __declspec(dllexport) extern struct COpticalParam
{
	int m_nIntialGray;
	int m_nIntialRed;
	int m_nIntialGreen;
	int m_nIntialBlue;
	int m_nCalcRed;
	int m_nCalcGreen;
	int m_nCalcBlue;
	float m_fMeasureX;
	float m_fMeasureY;
	float m_fMeasureLv;
	float m_fTargetX;
	float m_fTargetY;
	float m_fTargetLv;
	float m_fAEX;
	float m_fAEY;
	float m_fAELv;
	int m_nGray4;
};

extern "C" __declspec(dllexport) int CheckFrame(COpticalParam * pIT, int nOptiCountMax, int &m_nOptiCount);
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CDLL_CompensationApp
// �� Ŭ������ ������ ������ DLL_Compensation.cpp�� �����Ͻʽÿ�.
//

class CDLL_CompensationApp : public CWinApp
{
public:
	CDLL_CompensationApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
