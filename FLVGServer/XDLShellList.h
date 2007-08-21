#if !defined(AFX_XDLSHELLLIST_H__21E6D7B8_0125_43D0_8FB7_7733F184ECF2__INCLUDED_)
#define AFX_XDLSHELLLIST_H__21E6D7B8_0125_43D0_8FB7_7733F184ECF2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// XDLShellList.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CXDLShellList window

class CXDLShellList : public CXTShellListCtrl
{
// Construction
public:
	CXDLShellList();

// Attributes
public:

// Operations
public:
	void RefreshList();
	
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXDLShellList)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CXDLShellList();
	void OnShowContextMenu(int idCmd, CMINVOKECOMMANDINFO& cmi);
	
	// Generated message map functions
protected:
	//{{AFX_MSG(CXDLShellList)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XDLSHELLLIST_H__21E6D7B8_0125_43D0_8FB7_7733F184ECF2__INCLUDED_)
