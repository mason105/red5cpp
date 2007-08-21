// XDigitalLifeServerAppDoc.cpp : implementation of the CXDigitalLifeServerAppDoc class
//

#include "stdafx.h"
#include "XDigitalLifeServerApp.h"

#include "XDigitalLifeServerAppDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CXDigitalLifeServerAppDoc

IMPLEMENT_DYNCREATE(CXDigitalLifeServerAppDoc, CDocument)

BEGIN_MESSAGE_MAP(CXDigitalLifeServerAppDoc, CDocument)
	//{{AFX_MSG_MAP(CXDigitalLifeServerAppDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CXDigitalLifeServerAppDoc construction/destruction

CXDigitalLifeServerAppDoc::CXDigitalLifeServerAppDoc()
{
	// TODO: add one-time construction code here

}

CXDigitalLifeServerAppDoc::~CXDigitalLifeServerAppDoc()
{
}

BOOL CXDigitalLifeServerAppDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CXDigitalLifeServerAppDoc serialization

void CXDigitalLifeServerAppDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CXDigitalLifeServerAppDoc diagnostics

#ifdef _DEBUG
void CXDigitalLifeServerAppDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CXDigitalLifeServerAppDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CXDigitalLifeServerAppDoc commands

void CXDigitalLifeServerAppDoc::SetTitle(LPCTSTR lpszTitle) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CDocument::SetTitle(lpszTitle);
}
BOOL CXDigitalLifeServerAppDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	return TRUE;
}
