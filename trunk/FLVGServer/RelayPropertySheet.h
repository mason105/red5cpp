// RelayPropertySheet.h : header file
//
// This class defines custom modal property sheet 
// CRelayPropertySheet.
 
#ifndef __RELAYPROPERTYSHEET_H__
#define __RELAYPROPERTYSHEET_H__

#include "RelayPropertyPage1.h"

/////////////////////////////////////////////////////////////////////////////
// CRelayPropertySheet

class CRelayPropertySheet : public CXTMainPropertySheet
{
	DECLARE_DYNAMIC(CRelayPropertySheet)

// Construction
public:
	CRelayPropertySheet(CWnd* pWndParent = NULL);

// Attributes
public:
	CRelayPropertyPage1 m_Page1;
	CRelayPropertyPage2 m_Page2;
	CRelayPropertyPage3 m_Page3;
	
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRelayPropertySheet)
	protected:
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL
// Implementation
public:
	virtual ~CRelayPropertySheet();

// Generated message map functions
protected:
	//{{AFX_MSG(CRelayPropertySheet)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

#endif	// __RELAYPROPERTYSHEET_H__
