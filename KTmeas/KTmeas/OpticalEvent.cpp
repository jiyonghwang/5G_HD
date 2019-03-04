
#include "stdafx.h"
//#include "CaTest.h"
#include "OpticalEvent.h"

// CA-SDK
//#include "CaTestDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCaEvent

IMPLEMENT_DYNCREATE(COpticalEvent, CCmdTarget)

COpticalEvent::COpticalEvent()
{
	EnableAutomation();
}

COpticalEvent::~COpticalEvent()
{
}


void COpticalEvent::OnFinalRelease()
{

	CCmdTarget::OnFinalRelease();
}


BEGIN_MESSAGE_MAP(COpticalEvent, CCmdTarget)
	//{{AFX_MSG_MAP(CCaEvent)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(COpticalEvent, CCmdTarget)
	//{{AFX_DISPATCH_MAP(CCaEvent)
	DISP_FUNCTION(COpticalEvent, "ExeCalZero", ExeCalZero, VT_EMPTY, VTS_NONE)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()


// CA-SDK
// {D497071B-3F9F-41C2-9E04-1E573571BF0D}
// static const IID IID_ICaEvent =
// { 0xd497071b, 0x3f9f, 0x41c2, { 0x9e, 0x4, 0x1e, 0x57, 0x35, 0x71, 0xbf, 0xd } };
// {f7663750-5900-45eb-905f-78c5d5378481}
const IID IID_IOptiEvent =
{0xf7663750,0x5900,0x45eb,{0x90,0x5f,0x78,0xc5,0xd5,0x37,0x84,0x81}};

BEGIN_INTERFACE_MAP(COpticalEvent, CCmdTarget)
	INTERFACE_PART(COpticalEvent, IID_IOptiEvent, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCaEvent Message handler

void COpticalEvent::ExeCalZero() 
{
	// CA-SDK
	/*CWinApp* papp = AfxGetApp();
	CCa200SampleDlg* pdlg = reinterpret_cast<CCa200SampleDlg *>(papp -> m_pMainWnd);

	CButton* pb;

	pb = (CButton *)(pdlg ->GetDlgItem(IDC_BUTTON_MSR));
	pb->EnableWindow(FALSE);
	*/
}

//Copyright (c) 2002-2010 KONICA MINOLTA SENSING, INC. 