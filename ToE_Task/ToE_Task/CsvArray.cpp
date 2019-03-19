// CsvArray.cpp: implementation of the CCsvArray class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"


#include "CsvArray.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCsvArray::CCsvArray()
{
	m_nRowCount =0;
}

CCsvArray::~CCsvArray()
{
	RemoveAll();
}

void CCsvArray::Load(CArchive &ar)
{
	CString strBuf;

	m_nRowCount =0;
	for(int i=0;ar.ReadString(strBuf);i++)
	{
		m_nRowCount ++;
	
		if(m_nRowCount>GetSize())
		{
			m_nRowCount--;
			return;
		};
	
		Parse(strBuf,ElementAt(i));
	}

}

int CCsvArray::GetColumnCount(int nRow)		//행(세로줄)
{
	return ElementAt(nRow).GetCount();
}
  
BOOL CCsvArray::Save(CArchive &ar)
{
	
	for (int row = 0; row < GetSize(); row++)
	{
		for (int col = 0; col < GetColumnCount(row); col++)
		{
			ar.WriteString(ElementAt(row).ElementAt(col));			
			
			if (col < GetColumnCount(row)-1)
				ar.WriteString(",");
		}
		ar.WriteString("\n");
	}
	
	
	return TRUE;
}

int CCsvArray::Parse(const char sLine[],CCsvLine &ary)
{
	int flag = FALSE;
	int count = 0;
	int j = 0;
	
	static char buf[BUFSIZ];
	
	for (unsigned i = 0; i <= strlen(sLine); i++) 	// strlen() : 문자열의 길이를 계산, 반환값: 문자열의 길이를 반환
	{						// 단위는 바이트 수
		if (sLine[i]== '\"') flag = !flag;
		
		if(!flag)
		{
			buf[j++] = sLine[i];

			if ((sLine[i] == ',' )	|| 
				(sLine[i] == NULL)	|| 
				(sLine[i] == '\n')	||
				(sLine[i] == '\"') )
			{	
				buf[j - 1] = NULL; //0
				ary.SetAt(count,buf);	
				count++;
				j = 0;
			}
		}else
		{
			if (sLine[i]!= '\"'){
				buf[j++] = sLine[i];
				flag = !flag;
			}
		}
	}
	
	return count;
};


int CCsvArray::GetRowCount()		//열(옆으로 늘어서 있는)
{
	return m_nRowCount;
}

void CCsvArray::ShowList(CListCtrl &list)
{
	list.DeleteAllItems();

	int nCount=list.GetHeaderCtrl()->GetItemCount();
	for (int i = 0; i < nCount ; i++)
	{
		list.DeleteColumn(0);
	}

	if(GetRowCount())
	{
		// Calc Column Width
		CArray <int,int> aryColLength;
		int r,c;

		for(r=0;r<GetRowCount();r++)
		{
			for(c=0;c<GetColumnCount(r);c++)
			{
				if(aryColLength[c]<((*this)[r][c]).GetLength())
					aryColLength[c]=((*this)[r][c]).GetLength();
			}
		}
		
		CDC *pDC=list.GetDC();
		CSize sz=pDC->GetTextExtent("M");
		list.ReleaseDC(pDC);
		
		// Set Data
		for(c=0;c<GetColumnCount();c++)
		{
			CString strName;
			list.InsertColumn(c, strName,LVCFMT_LEFT);
			list.SetColumnWidth(c, aryColLength[c]*sz.cx);
			strName.Format("%c",'A'+c);
		}
	
		for(r=0;r<GetRowCount();r++)
		{
			list.InsertItem(r,(*this)[r][0],0);
			for(c=1;c<GetColumnCount(r);c++)
			{
				list.SetItemText(r,c,(*this)[r][c]);	
			}
		}
	}	

}



void CCsvArray::InputList(CListCtrl &list)
{
	int nColCount=list.GetHeaderCtrl()->GetItemCount();
	
	RemoveAll();
	
	for(int r = 0; r< list.GetItemCount();r++)
	{
		Add(CCsvLine());
		for (int c = 0; c < GetColumnCount(0); c++)
		{
			ElementAt(r).Add(list.GetItemText(r,c));			
		}
	}
}


 

int CCsvArray::Add(CCsvLine &line)
{
	return CArray<CCsvLine, CCsvLine &> ::Add(line);
}

BOOL CCsvArray::Load(CString strFileName)
{
	CFile file;

	if(file.Open(strFileName,CFile::modeRead | CFile::shareDenyNone))
	{
		CArchive ar(&file,CArchive::load);
		Load(ar);
		return TRUE;
	}else
	{
		CString strMessage;
		strMessage.Format("File open error :%s",strFileName);
		AfxMessageBox(strMessage);
		return FALSE;
	}
}


BOOL CCsvArray::Save(CString strFileName)
{
	CFile file;

	if(file.Open(strFileName,CFile::modeWrite|CFile::modeCreate))
	{
		CArchive ar(&file,CArchive::store);
		Save(ar);
		ar.Flush();

		file.Close();
		return TRUE;
	}else
	{
		CString strMessage;
		strMessage.Format("File open error :%s",strFileName);
		AfxMessageBox(strMessage);
		return FALSE;
	}
}

int CCsvArray::SetCsvSize(int nRow, int nCol)
{
	SetSize(nRow);

	for(int nR=0;nR<nRow;nR++)
		ElementAt(nR).SetSize(nCol);

	return TRUE;
}


int CCsvArray::Show(void)
{
	
	for(int nRow=0;nRow<GetRowCount();nRow++)
	{
		for(int nCol=0;nCol<GetColumnCount();nCol++)
		{
			printf("[%s]",(*this)[nRow][nCol]);
		}
		printf("\n");
	}

	return 0;
}
