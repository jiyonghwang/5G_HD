#if !defined(AFX_CAEVENT_H__78F17399_F575_4268_A5D5_C3B7EA42B7A8__INCLUDED_)
#define AFX_CAEVENT_H__78F17399_F575_4268_A5D5_C3B7EA42B7A8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
//

// CA-SDK
extern const IID IID_IOptiEvent;

/////////////////////////////////////////////////////////////////////////////
// CCaEvent Command Target

class COpticalEvent : public CCmdTarget
{
	DECLARE_DYNCREATE(COpticalEvent)

	// CA-SDK

// Attribute
public:

// Operation
public:
	// CA-SDK
	COpticalEvent();

// Override
	//{{AFX_VIRTUAL(DOptiEvent)
	public:
	virtual void OnFinalRelease();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~COpticalEvent();

	//{{AFX_MSG(CCaEvent)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	//{{AFX_DISPATCH(CCaEvent)
	afx_msg void ExeCalZero();
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}

#endif // !defined(AFX_CAEVENT_H__78F17399_F575_4268_A5D5_C3B7EA42B7A8__INCLUDED_)

//Copyright (c) 2002-2010 KONICA MINOLTA SENSING, INC. 