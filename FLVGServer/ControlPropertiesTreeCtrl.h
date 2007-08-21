#if !defined(AFX_CONTROLPROPERTIESTREECTRL_H__EE08DE4D_BF6A_47B7_9DE6_A9561D7445E9__INCLUDED_)
#define AFX_CONTROLPROPERTIESTREECTRL_H__EE08DE4D_BF6A_47B7_9DE6_A9561D7445E9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ControlPropertiesTreeCtrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CControlPropertiesTreeCtrl window

class CControlPropertiesTreeCtrl : public CXTTreeCtrl
{
// Construction
public:
	CControlPropertiesTreeCtrl();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CControlPropertiesTreeCtrl)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CControlPropertiesTreeCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CControlPropertiesTreeCtrl)
		// NOTE - the ClassWizard will add and remove member functions here.
	afx_msg void OnSelchanged (NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONTROLPROPERTIESTREECTRL_H__EE08DE4D_BF6A_47B7_9DE6_A9561D7445E9__INCLUDED_)
