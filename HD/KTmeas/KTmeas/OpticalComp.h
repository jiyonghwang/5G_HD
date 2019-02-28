#pragma once
// CA-SDK
#ifdef __CA_SDK
//extern "C" __decspec(dllimport) int COpticalComp::CheckFrame(COpticalParam * pIT, int nOptiCountMax, int m_nOptiCount)
//#import "DLL_Compensation,dll"  no_namespace no_implementation 
#import "Libs\CA200Srvr.dll" no_namespace no_implementation 
//#import "C:\Program Files\KONICAMINOLTA\CA-SDK\SDK\CA200Srvr.dll" no_namespace no_implementation 
#if 0
#include "DLL_Compensation.h"

#else
#include "resource.h"		// 주 기호입니다.
#include "CLSM.h"
#endif //0


const int OC_FRAME_COUNT=256;
const int OC_GRAY_COUNT=256;
const int GRAY_COUNT=12;

// Const.h
// Constant definition

// Communication port type
#define PORT_USB 0
#define PORT_COM1 1
#define PORT_COM2 2
#define PORT_COM3 3
#define PORT_COM4 4
#define PORT_COM5 5
#define PORT_COMMAX 255

// CA Display mode
#define DSP_LXY 0
#define DSP_DUV 1
#define DSP_ANL 2
#define DSP_ANLG 3
#define DSP_ANLR 4
#define DSP_PUV 5
#define DSP_FMA 6
#define DSP_XYZC 7
#define DSP_JEITA 8
#define DSP_XYZ 9

// CA Sync. mode
#define SYNC_NTSC 0
#define SYNC_PAL 1
#define SYNC_EXT 2
#define SYNC_UNIV 3
#define SYNC_INT 4

// CA Display digits
#define DIGT_3 0
#define DIGT_4 1

// CA FAST/SLOW Setting
#define AVRG_SLOW 0 
#define AVRG_FAST 1
#define AVRG_AUTO 2

// CA Luminance unit
#define BUNIT_FL 0 
#define BUNIT_CD 1

// Minolta calibration standards
#define CAL_D65 1 
#define CAL_9300 2
#define CAL_CA100 3

// CA Type
#define CATYPE_210 0
#define CATYPE_210S 1
#define CATYPE_100PLUS 2 
#define CATYPE_200 3 

// Probe Type
#define PROBETYPE_CA100PLUS 1001
#define PROBETYPE_CA100PLUSH 1002
#define PROBETYPE_CA210 2100
#define PROBETYPE_CA210S 2101

// Remote Mode
#define REMOTE_OFF 0 
#define REMOTE_ON 1 
#define REMOTE_LOCK 2 

// Color Calibration
#define CAL_RED 0 
#define CAL_GREEN 1 
#define CAL_BLUE 2 
#define CAL_WHITE 3 

//Copyright (c) 2002-2010 KONICA MINOLTA SENSING, INC. 


struct BAR_CODE_INFO{
		int Length;

		char Year;
		char Month;
		char W1,W2;
		char Day;
		
		unsigned char YWWD;
		unsigned char R;
		unsigned char C;
		unsigned char S0;
		unsigned char S1;
		unsigned char S2;
		unsigned char S3;
		unsigned char S4;
		unsigned char Y;
		unsigned char G;
};


struct COpticInitial
{
	double r_lv,g_lv,b_lv;
	double r_ratio;
	double g_ratio;
	double b_ratio;
	double rgb_sum;
	double sum_ratio;
};

struct COpticalResult
{
	UINT16 m_nRed;
	UINT16 m_nGreen;
	UINT16 m_nBlue;
};

struct stOptiEvalResult
{
	float X;
	float Y;
	float Lv;
};
struct stXYLv
{
	float X;
	float Y;
	float Lv;
};
struct boolXYLv
{
	bool X;
	bool Y;
	bool Lv;
};

class COpticalComp
{

public:
	IConnectionPointPtr m_pIConnectionPointObj;
	DWORD m_dwCk;
	IDispatch* m_pIDispatch;
	
	IOutputProbesPtr m_pOutputProbesObj;
	IProbesPtr m_pProbesObj;
	ICasPtr m_pCasObj;
	IMemoryPtr m_pMemoryObj;
	IProbePtr m_pProbeObj;
	ICaPtr m_pCaObj;
	ICa200Ptr m_pCa200Obj;
	
	BOOL m_bInit;

	int m_nFrameCount;
	int m_nOCTabCount;
	int m_nOptiCount;
	int m_nStep;
	stXYLv m_stXYLv;
	stXYLv m_BeforeXYLv;
	boolXYLv m_boolXYLv;
	//int m_nOptiCountMax;

	BOOL m_bOptiEvalWhite;
	BOOL m_bOptiEvalRed;
	BOOL m_bOptiEvalGreen;
	BOOL m_bOptiEvalBlue;

	COpticInitial OC_initial;
	COpticalResult m_Result[OC_GRAY_COUNT];
	stOptiEvalResult m_stOptiEvalResult[OC_GRAY_COUNT];
	stOptiEvalResult m_stOptiEvalWhite[OC_GRAY_COUNT];
	stOptiEvalResult m_stOptiEvalRed[OC_GRAY_COUNT];
	stOptiEvalResult m_stOptiEvalGreen[OC_GRAY_COUNT];
	stOptiEvalResult m_stOptiEvalBlue[OC_GRAY_COUNT];
	COpticalResult m_Result2[GRAY_COUNT+1];

	CString m_stOptiEvalWhite_Curr[1024];
	CString m_stOptiEvalRed_Curr[1024];
	CString m_stOptiEvalGreen_Curr[1024];
	CString m_stOptiEvalBlue_Curr[1024];

	double m_dbOptiEvalWhite_Curr[1024];
	double m_dbOptiEvalRed_Curr[1024];
	double m_dbOptiEvalGreen_Curr[1024];
	double m_dbOptiEvalBlue_Curr[1024];
	double T0_R,T0_G,T0_B;
	stOptiEvalResult m_stOptiEvalWhite_Dac[1024];
	stOptiEvalResult m_stOptiEvalRed_Dac[1024];
	stOptiEvalResult m_stOptiEvalGreen_Dac[1024];
	stOptiEvalResult m_stOptiEvalBlue_Dac[1024];


	COpticalComp(void);
	int Init(void);
	int OpticalMeasure(void);

	int SetZero(void);
	void CA210_Measure();

	int Close(void);

	int GetFrameCount(void)
	{
		return m_nFrameCount;
	}

	Linear linear_RGB[3];

	//===================================//
	int Write(void);
	int Read(void);

	BOOL WriteCSV(void);
	BOOL SaveOpticParam();
	BOOL SaveOpticParam_T0();
	void Optic_Param_Init();
	void Optic_Param_update();
	void Optic_Param_T0(double R, double G, double B);
	COpticalResult Optic_ratio(double TargetLv,double R, double G, double B);
	COpticalResult* GetOCResult() { return m_Result; }

	public:
	BOOL UpdateData(BOOL bSaveAndValidate = TRUE);

	BOOL BcrInputDataCheck(CString text, BAR_CODE_INFO& m_BAR_CODE_INFO);
private:
};

#endif