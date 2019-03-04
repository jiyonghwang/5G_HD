
#include "StdAfx.h"

#ifdef __CA_SDK

#include "OpticalComp.h"
#include <math.h>

// CA-SDK
#include "OpticalEvent.h"
#import "Libs\CA200Srvr.dll" no_namespace implementation_only  
//import "C:\Program Files\KONICAMINOLTA\CA-SDK\SDK\CA200Srvr.dll" no_namespace no_implementation 
#ifdef _DEBUG
#define new DEBUG_NEW
#undef  THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

COpticalComp::COpticalComp(void)
{
	m_bInit = FALSE;
	m_nOptiCount = 0;
	m_stXYLv.X = 0;
	m_stXYLv.Y = 0;
	m_stXYLv.Lv = 0;
}

int COpticalComp::Init(void)  // 초기
{
#ifdef USE_SENSING_SIMUL
	return 1;
#endif 
	
	long lcan = 1;
	_bstr_t strcnfig(_T("1"));
	long lprt = PORT_USB;
	long lbr = 38400;
	_bstr_t strprbid(_T("P1"));
	_variant_t vprbid(_T("P1"));

	try{
		m_pIConnectionPointObj=0;
		m_dwCk=0;
		m_pIDispatch=0;
		m_pOutputProbesObj=0;
		m_pProbesObj=0;
		m_pCasObj=0;
		m_pMemoryObj=0;
		m_pProbeObj=0;
		m_pCaObj=0;
		m_pCa200Obj=0;
		
		m_pCa200Obj = ICa200Ptr(__uuidof(Ca200));
		m_pCa200Obj->SetConfiguration(lcan, strcnfig, lprt, lbr);
		
	}
	catch(_com_error e){
		CString strerr;
		strerr.Format(_T("HR:0x%08x\nMSG:%s"), e.Error(), (LPCSTR)e.Description());
		AfxMessageBox((LPCSTR)strerr);
		return FALSE;
	}


	m_pCasObj = m_pCa200Obj->Cas;
	m_pCaObj = m_pCasObj->ItemOfNumber[lcan];
	m_pOutputProbesObj = m_pCaObj->OutputProbes;
	m_pOutputProbesObj->RemoveAll();
	m_pOutputProbesObj->Add(strprbid);
	m_pProbeObj = m_pOutputProbesObj->Item[vprbid];
	m_pMemoryObj = m_pCaObj->Memory;

	m_pCaObj->SyncMode = SYNC_NTSC;
	m_pCaObj->AveragingMode = AVRG_FAST;
	m_pCaObj->SetAnalogRange(2.5, 2.5);
	m_pCaObj->DisplayMode = DSP_LXY;
	m_pCaObj->DisplayDigits = DIGT_4;
	m_pCaObj->RemoteMode = TRUE;	
	m_dwCk = 0;

	COpticalEvent* pevntobj;

	if (NULL != (pevntobj = new COpticalEvent)){
		m_pIDispatch = pevntobj ->GetIDispatch(FALSE);

		IConnectionPointContainerPtr pcpcobj;
		DWORD dwck;

		pcpcobj = m_pCaObj;
		pcpcobj -> FindConnectionPoint(IID_IOptiEvent, &m_pIConnectionPointObj);
		m_pIConnectionPointObj ->Advise(m_pIDispatch, &dwck);
		m_dwCk = dwck;
	}

	m_bInit = TRUE;
	return TRUE;
}


int COpticalComp::SetZero(void)
{
	
	try{
		m_pCaObj->CalZero();
	}
	catch(_com_error e){
		CString strerr;
		strerr.Format(_T("HR:0x%08x\nMSG:%s"), e.Error(), (LPCSTR)e.Description());
		AfxMessageBox((LPCSTR)strerr);
		return FALSE;
	}

	return 0;
}


BOOL COpticalComp::BcrInputDataCheck(CString text, BAR_CODE_INFO& m_BAR_CODE_INFO)
{
	int BCR_LENGTH;
	int Year, Month=1, Day=1, Week, WDay;
	//char bar_code[PID_MAX];

	WCHAR bar_code[100];
	CString str, errStr;


	if(text.Right(1) == '\n') text = text.Left(text.GetLength()-1);
	memset(bar_code, 0, sizeof(bar_code));

	BCR_LENGTH = text.GetLength();

	if(BCR_LENGTH > 100)
	{
		return FALSE;
	}
	if(BCR_LENGTH > 31)
	{
		//if(BCR_LENGTH != 88) //추후 적용
		//	return FALSE;

		str = text.Left(31);	

		wcscpy(bar_code, (const WCHAR *)str.GetBuffer(0));
		//wcscpy(bar_code, str);
		//strcpy(bar_code, str);	
		BCR_LENGTH = 31;
	}
	else
	{
		//NG_Display(ch,_T("QR Code NG : 31자릿수 미만"));
		return FALSE;
	}

	m_BAR_CODE_INFO.Length = BCR_LENGTH;

	str = bar_code[11];
	str += bar_code[12];
	str += bar_code[13];
	str += bar_code[14];

	if(bar_code[0] != 'D')
		return FALSE;
	if(bar_code[1] != 'L')
		return FALSE;
	if(bar_code[2] != 'R')
		return FALSE;
	if(bar_code[15] != 'L')
		return FALSE;
	if(bar_code[16] != '-')
		return FALSE;

	if(bar_code[17] == 'P')
	{
		if((bar_code[18] == '0'|| bar_code[18] == '1' || bar_code[18] == '2'|| bar_code[18] == '3'|| bar_code[18] == '4'|| bar_code[18] == '5'|| bar_code[18] == '6'|| bar_code[18] == '7'|| bar_code[18] == '8'|| bar_code[18] == '9') && BCR_LENGTH == 31)
			;
		else
		{
			errStr.Format(_T("QR Code[19]NG%c"),bar_code[18]);
			//NG_Display(ch,errStr);

			return FALSE;
		}
	}
	else if(bar_code[17] == 'E')
	{
		if((bar_code[18] == '0'|| bar_code[18] == '1' || bar_code[18] == '2'|| bar_code[18] == '3'|| bar_code[18] == '4'|| bar_code[18] == '5'|| bar_code[18] == '6'|| bar_code[18] == '7'|| bar_code[18] == '8'|| bar_code[18] == '9') && BCR_LENGTH == 31)
			;
		else
		{
			errStr.Format(_T("QR Code[19]NG%c"),bar_code[18]);
			//NG_Display(ch,errStr);

			return FALSE;
		}
	}
	else if(bar_code[17] == 'D')
	{
		if((bar_code[18] == '0'|| bar_code[18] == '1' || bar_code[18] == '2'|| bar_code[18] == '3'|| bar_code[18] == '4'|| bar_code[18] == '5'|| bar_code[18] == '6'|| bar_code[18] == '7'|| bar_code[18] == '8'|| bar_code[18] == '9') && BCR_LENGTH == 31)
			;
		else
		{
			errStr.Format(_T("QR Code[19]NG%c"),bar_code[18]);
			//NG_Display(ch,errStr);

			return FALSE;
		}
	}
	else if(bar_code[17] == 'M')
	{
		if((bar_code[18] == '0'|| bar_code[18] == '1' || bar_code[18] == '2'|| bar_code[18] == '3'|| bar_code[18] == '4'|| bar_code[18] == '5'|| bar_code[18] == '6'|| bar_code[18] == '7'|| bar_code[18] == '8'|| bar_code[18] == '9') && BCR_LENGTH == 31)
			;
		else
		{
			errStr.Format(_T("QR Code[19]NG%c"),bar_code[18]);
			//NG_Display(ch,errStr);

			return FALSE;
		}
	}
	else if(bar_code[17] == 'A')
	{
		if((bar_code[18] == '0'|| bar_code[18] == '1' || bar_code[18] == '2'|| bar_code[18] == '3'|| bar_code[18] == '4'|| bar_code[18] == '5'|| bar_code[18] == '6'|| bar_code[18] == '7'|| bar_code[18] == '8'|| bar_code[18] == '9')&& BCR_LENGTH == 31)
			;
		else
		{
			errStr.Format(_T("QR Code[19]NG%c"),bar_code[18]);
			//NG_Display(ch,errStr);

			return FALSE;
		}
	}
	else
	{
		errStr.Format(_T("QR Code[18]NG%c"),bar_code[17]);
			//NG_Display(ch,errStr);

		return FALSE;
	}

	////////////// 27번째 자리, anything OK ////////////////
	//if(BCR_LENGTH == 31)
	//{
	//	if(bar_code[26] != 'N' && bar_code[26] != 'P')
	//	{
	//		errStr.Format(_T("QR Code[27]NG%c"),bar_code[26]);
	//		//NG_Display(ch,errStr);
	//		switch(ch)
	//		{
	//			case 1: QR_NG = errStr;
	//				break;
	//			case 2: QR_NG2 = errStr;
	//				break;
	//			case 3: QR_NG3 = errStr;
	//				break;
	//			case 4: QR_NG4 = errStr;
	//				break;
	//		}
	//		return FALSE;
	//	}
	//}

	if(bar_code[3] >= '3' && bar_code[3] <= '9')
	{
		Year=2010+bar_code[3]-'0';
	}
	else
	{
		Year=2010+bar_code[3]-'0';
		errStr.Format(_T("QR Code[4] Year NG%d"),Year);
			//NG_Display(ch,errStr);

		return FALSE;
	}
	
	Week = (bar_code[4]-'0')*10+(bar_code[5]-'0');
	if(Week < 1 || Week > 53)
	{
		errStr.Format(_T("QR Code[5 6] Week NG%d"),Week);
			//NG_Display(ch,errStr);

		return FALSE;
	}
	
	if(bar_code[6] >= '1' && bar_code[6] <= '7')
	{
		WDay = bar_code[6]-'0';
	}
	else
	{
		WDay = bar_code[6]-'0';
		errStr.Format(_T("QR Code[7] Day NG%d"),WDay);
			//NG_Display(ch,errStr);
		return FALSE;
	}
	
	m_BAR_CODE_INFO.YWWD = Month*0x10+(Year-2010);

	if(bar_code[19]>='A' && bar_code[19]<='M' && bar_code[19] != 'I')
	{
		m_BAR_CODE_INFO.R    = bar_code[19];
	}
	else
	{
		errStr.Format(_T("QR Code[20]NG%c"),bar_code[19]);
			//NG_Display(ch,errStr);

		return FALSE;
	}

	if(bar_code[20]>='1' && bar_code[20]<='T' && bar_code[20] != 'I' && bar_code[20] != 'O')
	{
		m_BAR_CODE_INFO.C    = bar_code[20];
	}
	else
	{
		errStr.Format(_T("QR Code[20]NG%c"),bar_code[21]);
					//NG_Display(ch,errStr);

		return FALSE;
	}

	if(bar_code[21]>='0' && bar_code[21]<='Z' && bar_code[21]!='I' && bar_code[21]!='O')
	{
		m_BAR_CODE_INFO.S4    = bar_code[21];
	}
	else
	{
		errStr.Format(_T("QR Code[22]NG%c"),bar_code[21]);
				//	NG_Display(ch,errStr);

		return FALSE;
	}


	if(bar_code[22]>='0' && bar_code[22]<='Z' && bar_code[22]!='I' && bar_code[22]!='O')
	{
		m_BAR_CODE_INFO.S3    = bar_code[22];
	}
	else
	{
		errStr.Format(_T("QR Code[23]NG%c"),bar_code[22]);
			//NG_Display(ch,errStr);

		return FALSE;
	}

	if(bar_code[23]>='0' && bar_code[23]<='Z' && bar_code[23]!='I' && bar_code[23]!='O')
	{
		m_BAR_CODE_INFO.S2    = bar_code[23];
	}
	else
	{
		errStr.Format(_T("QR Code[24]NG%c"),bar_code[23]);
				//	NG_Display(ch,errStr);

		return FALSE;
	}

	if(bar_code[24]>='1' && bar_code[24]<='9')
	{
		m_BAR_CODE_INFO.S1    = bar_code[24]-'0';
	}
	else if(bar_code[24]>='A' && bar_code[24]<='Q' && bar_code[24]!='I' && bar_code[24]!='O')
	{
		m_BAR_CODE_INFO.S1    = bar_code[24]-'A'+0x0A;
		//if(bar_code[24]>'I')                    m_BAR_CODE_INFO[ch].S1--;
		//if(bar_code[24]>'O')                    m_BAR_CODE_INFO[ch].S1--;
	}
	else
	{
		errStr.Format(_T("QR Code[24]NG%c"),bar_code[22]);
				//	NG_Display(ch,errStr);

		return FALSE;
	}
	
	if(bar_code[25] == 'A' || bar_code[25] == 'B')
	{
		m_BAR_CODE_INFO.S0    = bar_code[25]-'@';
	}
	else
	{
		errStr.Format(_T("QR Code[26]NG%c"),bar_code[25]);
			//NG_Display(ch,errStr);

		return FALSE;
	}
	
	if(BCR_LENGTH == 31)
	{
		if(bar_code[27]>='3' && bar_code[27]<='9')
		{
			m_BAR_CODE_INFO.Y    = bar_code[27]-'0';			
		}
		else
		{
			errStr.Format(_T("QR Code[28]NG%c"),bar_code[27]);
			//NG_Display(ch,errStr);

			return FALSE;
		}
		
		if(bar_code[28]>='1' && bar_code[28]<='9')
		{
			m_BAR_CODE_INFO.G    = bar_code[28]-'0';			
		}
		else if(bar_code[28]>='A' && bar_code[28]<='C')
		{
			m_BAR_CODE_INFO.G    = bar_code[28]-'A'+0x0A;			
		}
		else
		{
			errStr.Format(_T("QR Code[29]NG%c"),bar_code[28]);
			//NG_Display(ch,errStr);

			return FALSE;
		}
	}

	//if(cbxList=="D154_C1_2_Main")
//	{
		if(bar_code[11] == 'G' && bar_code[12] == 'K' && bar_code[13] == '0' && bar_code[14] == '1' )
			;
		else
		{
			errStr.Format(_T("QR Code[12 13 14 15]NG%c%c%c%c",bar_code[11],bar_code[12],bar_code[13],bar_code[14]));
			//errStr.Format(L"QR Code[12 13 14 15]NG%c%c%c%c",bar_code[11],bar_code[12],bar_code[13],bar_code[14]);
		//	NG_Display(ch,errStr);

			return FALSE;
		}
//	}
	// Large:"FYKN" ,Small:"FFV0" 가 없으면 NG 
	//if(m_MODULE_INFORMATION.pg_h_active > 272)//Large
	//{
	//	if(bar_code[29] == 'D' && bar_code[30] == '1')
	//	{
	//		;
	//	}
	//	else if(bar_code[29] == 'D' && bar_code[30] == 'B')
	//	{
	//		;
	//	}
	//	else
	//	{
	//		m_EETestStep1Dialog[m_BCR_CH]->EventMsg("Change Small model code", MSG_ERROR);
	//		return FALSE;
	//	}
		//if(bar_code[11] == 'F' && bar_code[12] == 'Y' && bar_code[13] == 'K' && bar_code[14] == 'N' )
		//	;
		//else if(bar_code[11] == 'G' && bar_code[12] == '8' && bar_code[13] == 'M' && bar_code[14] == 'L' )
		//	;
		//else if(bar_code[11] == 'G' && bar_code[12] == '5' && bar_code[13] == '8' && bar_code[14] == 'Q' )
		//	;
		//else
		//{
		//	errStr.Format(L"QR Code[12,13,14,15] NG : %c%c%c%c",bar_code[11],bar_code[12],bar_code[13],bar_code[14]);
		//	NG_Display(ch,errStr);
		//	switch(ch)
		//	{
		//		case 1: NG_Code = errStr;
		//			break;
		//		case 2: NG_Code2 = errStr;
		//			break;
		//		case 3: NG_Code3 = errStr;
		//			break;
		//		case 4: NG_Code4 = errStr;
		//			break;
		//	}
		//	return FALSE;
		//}
	////}
	//else
	//{
	//	if(bar_code[29] == 'C' && bar_code[30] == '1')
	//	{
	//		;
	//	}
	//	else if(bar_code[29] == 'C' && bar_code[30] == 'B')
	//	{
	//		;
	//	}
	//	else
	//	{
	//		m_EETestStep1Dialog[m_BCR_CH]->EventMsg("Change Large model code", MSG_ERROR);
	//		return FALSE;
	//	}

		//if(bar_code[11] == 'F' && bar_code[12] == 'F' && bar_code[13] == 'V' && bar_code[14] == '0' )
		//	;
		//else if(bar_code[11] == 'G' && bar_code[12] == '8' && bar_code[13] == 'M' && bar_code[14] == 'K' )
		//	;
		//else if(bar_code[11] == 'G' && bar_code[12] == '5' && bar_code[13] == '8' && bar_code[14] == 'R' )
		//	;
		//else
		//{
		//	errStr.Format(L"QR Code[12,13,14,15] NG : %c%c%c%c",bar_code[11],bar_code[12],bar_code[13],bar_code[14]);
		//	NG_Display(ch,errStr);
		//	switch(ch)
		//	{
		//		case 1: NG_Code = errStr;
		//			break;
		//		case 2: NG_Code2 = errStr;
		//			break;
		//		case 3: NG_Code3 = errStr;
		//			break;
		//		case 4: NG_Code4 = errStr;
		//			break;
		//	}
		//	return FALSE;
		//}

	//}
	return TRUE;
}


void COpticalComp::CA210_Measure()  //측정 4
{
	m_pCaObj->Measure(0);
	//CIE1931 (x, y)
	m_stXYLv.X = m_pProbeObj->sx;
	m_stXYLv.Y = m_pProbeObj->sy;
	m_stXYLv.Lv = m_pProbeObj->Lv;

}

int COpticalComp::Close(void)
{

	if (m_dwCk != 0){
		m_pIConnectionPointObj ->Unadvise(m_dwCk);
	}
	m_pIDispatch ->Release();
	m_pCaObj ->RemoteMode = 0;
	return 0;
}

#endif