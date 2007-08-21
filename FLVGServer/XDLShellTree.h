#if !defined(AFX_XDLSHELLTREE_H__9FB9E91A_20A7_4F22_81C5_6D9947224073__INCLUDED_)
#define AFX_XDLSHELLTREE_H__9FB9E91A_20A7_4F22_81C5_6D9947224073__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// XDLShellTree.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CXDLShellTree window

class CXDLShellTree : public CXTShellTreeCtrl
{
// Construction
public:
	CXDLShellTree();

// Attributes
public:
	CString m_strRootPath;
// Operations
public:
	CString SetRootPath(CString strRootPath);
	CString GetRootPath(){return m_strRootPath;}
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXDLShellTree)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CXDLShellTree();

	// Generated message map functions
protected:
	//{{AFX_MSG(CXDLShellTree)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XDLSHELLTREE_H__9FB9E91A_20A7_4F22_81C5_6D9947224073__INCLUDED_)
