// CsvLinecpp: implementation of the CCsvLine class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CsvLine.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCsvLine::CCsvLine()
{

}

CCsvLine::~CCsvLine()
{

}

const CCsvLine& CCsvLine::operator =(const CCsvLine& item) 
{
		RemoveAll();
		SetSize(item.GetSize());
		for(int i=0;i<item.GetSize();i++)
			Add(item[i]);

        return *this;
}
