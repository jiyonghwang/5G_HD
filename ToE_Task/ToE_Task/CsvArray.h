// CsvArray.h: interface for the CCsvArray class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CSVARRAY_H__79BE0F5F_1B97_4DAF_B929_7931053F7E92__INCLUDED_)
#define AFX_CSVARRAY_H__79BE0F5F_1B97_4DAF_B929_7931053F7E92__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <afxtempl.h>
#include "CsvLine.h"

class CCsvArray :public CArray<CCsvLine, CCsvLine &> // 구조체와 같은 역할. CArray에서 상속받음
{
	int Parse(const char sLine[],CCsvLine &ary);
//	static CString GetSaveFormat(CString str);

	int m_nRowCount;
public:
	int SetCsvSize(int nRow,int nCol);
 	int Add(CCsvLine &line);
 	void ShowList(CListCtrl &list);
	void InputList(CListCtrl &list);
	int GetRowCount();
	BOOL Save(CArchive &ar);
	void Load(CArchive& ar);

	int GetColumnCount(int nRow=0);

	

	BOOL Load(CString strFileName);
	BOOL Save(CString strFileName);

	CCsvArray();
	virtual ~CCsvArray();

	int Show(void);
};

#endif // !defined(AFX_CSVARRAY_H__79BE0F5F_1B97_4DAF_B929_7931053F7E92__INCLUDED_)
