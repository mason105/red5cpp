// RelayPropertySheet.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "RelayPropertySheet.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRelayPropertySheet

IMPLEMENT_DYNAMIC(CRelayPropertySheet, CXTMainPropertySheet)

CRelayPropertySheet::CRelayPropertySheet(CWnd* pWndParent)
	 : CXTMainPropertySheet(IDS_PROPSHT_CAPTION, pWndParent)
{
	// Add all of the property pages here.  Note that
	// the order that they appear in here will be
	// the order they appear in on screen.  By default,
	// the first page of the set is the active one.
	// One way to make a different property page the 
	// active one is to call SetActivePage().

	AddPage(&m_Page1);
	AddPage(&m_Page2);
	AddPage(&m_Page3);

	SetWizardMode();
}

CRelayPropertySheet::~CRelayPropertySheet()
{
}


BEGIN_MESSAGE_MAP(CRelayPropertySheet, CXTMainPropertySheet)
	//{{AFX_MSG_MAP(CRelayPropertySheet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CRelayPropertySheet message handlers



BOOL CRelayPropertySheet::OnInitDialog() 
{
	CXTMainPropertySheet::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CRelayPropertySheet::OnCommand(WPARAM wParam, LPARAM lParam) 
{

	return CXTMainPropertySheet::OnCommand(wParam, lParam);
}
