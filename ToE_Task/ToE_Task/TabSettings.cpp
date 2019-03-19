// TabSettings.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "ToE_Task.h"
#include "TabSettings.h"
#include "afxdialogex.h"
#include "list"

// CTabSettings ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CTabSettings, CDialogEx)

CTabSettings::CTabSettings(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTabSettings::IDD, pParent)
{

}

CTabSettings::~CTabSettings()
{
}

void CTabSettings::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_PATH, m_pathfile);
	DDX_Control(pDX, IDC_EDIT_LOADING, m_Loading);
}


BEGIN_MESSAGE_MAP(CTabSettings, CDialogEx)
	ON_EN_CHANGE(IDC_EDIT_PATH, &CTabSettings::OnEnChangeEditPath)
	ON_BN_CLICKED(IDC_BN_PATH_OPEN, &CTabSettings::OnBnClickedBnPathOpen)
	ON_BN_CLICKED(IDC_BN_PATH_READ, &CTabSettings::OnBnClickedBnPathRead)
	ON_EN_CHANGE(IDC_EDIT_LOADING, &CTabSettings::OnEnChangeEditLoading)
	ON_BN_CLICKED(IDC_BN_FILE_LOADING, &CTabSettings::OnBnClickedBnFileLoading)
END_MESSAGE_MAP()

// CTabSettings �޽��� ó�����Դϴ�.

BOOL CTabSettings::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	//m_strFilePath.SetWindowText(_T("D:\\HJY\\SW\\KTmeas\\KTmeas\\Time_meas_CA310.csv"));
	m_strFilePath = "D:\\HJY\\SW\\KTmeas\\KTmeas\\Time_meas_CA310.csv";
	SetDlgItemText(IDC_EDIT_PATH, m_strFilePath);
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

void CTabSettings::OnBnClickedBnPathRead()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	char szFilter[]="hello(*.csv)|*.xls|User Settings(*.cfg)|*.cfg|All Files(*.*)|*.*|";
	CFileDialog fDlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, szFilter);
	//(TRUE(�б�)/FALSE(����),�⺻Ȯ����,�⺻���ϸ�,������->MSDN����, ����â �Ʒ��ʿ� ������ ���͸�)

	int iRet = fDlg.DoModal();
	m_strFilePath = fDlg.GetPathName();
	
	if(iRet == IDOK)
	{
		SetDlgItemText(IDC_EDIT_PATH, m_strFilePath);  //edit �� ���ϰ�� Ȯ��
	}
}

void CTabSettings::OnBnClickedBnPathOpen()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	ShellExecute(NULL, "open", m_strFilePath, NULL, NULL, SW_SHOW); //edit�� �����ִ� ���� ����
}

void CTabSettings::OnBnClickedBnFileLoading()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	/*
	CFile file;  
	CString cList;  //���پ� �ӽ÷� ������ ����  
	int lineCount = 0; //line ���� ������ ���� ����
	int nLength = file.GetLength();
	file.Open(m_strFilePath, CFile::modeRead); //  fName �� ������ ���� 
	CArchive ar(&file, CArchive::load);
	ar.ReadString(cList); //���پ� ������ �о�ͼ� cList���� 
	AfxMessageBox(cList);
	//SetDlgItemText(IDC_EDIT_LOADING, cList);
	ar.Close();
	file.Close();
	*/
	
	CFile file;
	CString strFile; // ������ ������ ��´�.
	CString strtest; // ����� Ȯ���غ��� ���� �ӽ� ���� ����
	int nFileSize = 0; // ������ ũ��
	CStringArray strWordArray; // �ܾ ���� ��Ʈ�� �迭 // CString�� �迭 ���� CStirng�� ���� �� �ִ� �迭�� ���°� ȿ�����̴�.
	CString strWord; // �ϳ��� �ܾ ���� �ӽ� ����
	
	strWordArray.RemoveAll();
	
	if (file.Open(m_strFilePath, CFile::modeRead))
	{
		int nFileSize = file.GetLength(); 	// ������ ũ�⸦ ���Ѵ�.
		strtest.Format("%d",nFileSize); 
		//AfxMessageBox(strtest); //���� ũ�� ��� ����
		file.Read(strFile.GetBuffer(nFileSize), nFileSize); // ������ ũ�� ��ŭ �о� CString ������ ��´�.
		strFile.ReleaseBuffer(nFileSize);
		AfxMessageBox(strFile);  //�о�� ������ ������ ���
		while(strFile.Find(",") != -1)
		{		
			strWord = strFile.Left(strFile.Find(","));
			//AfxMessageBox(strWord);
			strWordArray.Add(strWord);
			strFile.Delete(0, strWord.GetLength()+1);
		}
		//strWordArray.Add(strFile);
		AfxMessageBox(strWordArray[47]);   //0~47 
		
		for(int i =0;i<strWordArray.GetSize(); i++)
		{
			SetDlgItemText(IDC_EDIT_LOADING, strWordArray[i]);
			Sleep(500);
		}
		//strtest.Format("%d",strWordArray.GetCount()); 
		//SetDlgItemText(IDC_EDIT_LOADING, strtest); //0~47 �̹Ƿ� 48�� ���� ����.
		file.Close();		
		
	}
}

void CTabSettings::OnEnChangeEditPath()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialogEx::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}

void CTabSettings::OnEnChangeEditLoading()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialogEx::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


