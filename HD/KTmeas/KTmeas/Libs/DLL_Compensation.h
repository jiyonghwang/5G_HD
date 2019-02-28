// DLL_Compensation.h : DLL_Compensation DLL의 기본 헤더 파일입니다.
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
	#error "PCH에 대해 이 파일을 포함하기 전에 'stdafx.h'를 포함합니다."
#endif

#include "resource.h"		// 주 기호입니다.


// CDLL_CompensationApp
// 이 클래스의 구현을 보려면 DLL_Compensation.cpp를 참조하십시오.
//

class CDLL_CompensationApp : public CWinApp
{
public:
	CDLL_CompensationApp();

// 재정의입니다.
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
