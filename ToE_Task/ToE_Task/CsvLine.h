// CsvLine.h: interface for the CsvLine class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CSVLINE_H__09147A73_026A_44C9_85CF_68C1C5AC5339__INCLUDED_)
#define AFX_CSVLINE_H__09147A73_026A_44C9_85CF_68C1C5AC5339__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CCsvLine : public CStringArray
{
	
public:
	CCsvLine ();
	virtual ~CCsvLine ();

    const CCsvLine & operator =(const CCsvLine & item);

	
};

#endif // !defined(AFX_CSVLINE_H__09147A73_026A_44C9_85CF_68C1C5AC5339__INCLUDED_)
