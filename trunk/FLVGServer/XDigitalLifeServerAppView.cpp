// XDigitalLifeServerAppView.cpp : implementation of the CXDigitalLifeServerAppView class
//

#include "stdafx.h"
#include "XDigitalLifeServerApp.h"

#include "XDigitalLifeServerAppDoc.h"
#include "XDigitalLifeServerAppView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CXDigitalLifeServerAppView

IMPLEMENT_DYNCREATE(CXDigitalLifeServerAppView, CView)

BEGIN_MESSAGE_MAP(CXDigitalLifeServerAppView, CView)
	//{{AFX_MSG_MAP(CXDigitalLifeServerAppView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CXDigitalLifeServerAppView construction/destruction

CXDigitalLifeServerAppView::CXDigitalLifeServerAppView()
{
	// TODO: add construction code here

}

CXDigitalLifeServerAppView::~CXDigitalLifeServerAppView()
{
}

BOOL CXDigitalLifeServerAppView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CXDigitalLifeServerAppView drawing

void CXDigitalLifeServerAppView::OnDraw(CDC* pDC)
{
	CXDigitalLifeServerAppDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CXDigitalLifeServerAppView printing

BOOL CXDigitalLifeServerAppView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CXDigitalLifeServerAppView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CXDigitalLifeServerAppView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CXDigitalLifeServerAppView diagnostics

#ifdef _DEBUG
void CXDigitalLifeServerAppView::AssertValid() const
{
	CView::AssertValid();
}

void CXDigitalLifeServerAppView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CXDigitalLifeServerAppDoc* CXDigitalLifeServerAppView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CXDigitalLifeServerAppDoc)));
	return (CXDigitalLifeServerAppDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CXDigitalLifeServerAppView message handlers
