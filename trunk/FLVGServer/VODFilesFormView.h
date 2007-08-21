#if !defined(AFX_VODFILESFORMVIEW_H__82772901_DB8C_4C59_8A30_8BADBDCD49B6__INCLUDED_)
#define AFX_VODFILESFORMVIEW_H__82772901_DB8C_4C59_8A30_8BADBDCD49B6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// VODFilesFormView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CVODFilesFormView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

#include "XDLShellTree.h"
#include "XDLShellList.h"

class CVODFilesFormView : public CXTMainFormView
{
protected:
	CVODFilesFormView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CVODFilesFormView)

// Form Data
public:
	//{{AFX_DATA(CVODFilesFormView)
	enum { IDD = IDD_DIALOG_VODFILES };
	CXTButton	m_btnPrevPath;
	CXTComboBoxEx	m_comboAddressBar;
	//}}AFX_DATA

	BOOL m_bInitialized;
	XDLS_Setting *m_pSetting;
	// Attributes
public:
	CXDLShellTree    m_shellTree;	
	inline CXDLShellTree& GetTreeCtrl() {
		return m_shellTree;
	}
	CXDLShellList  m_shellList;	
	inline CXDLShellList& GetListCtrl() {
		return m_shellList;
	}	
	
// Operations
public:
	void RecalcLayout();
	void InitSetting(XDLS_Setting *pSetting);	
	void Server_Run();
	void Server_Stop();
	void Wnd_Active(BOOL bActive);
	void OnTimerWork(UINT nID);
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVODFilesFormView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CVODFilesFormView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CVODFilesFormView)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnBtnPrevPathClicked();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VODFILESFORMVIEW_H__82772901_DB8C_4C59_8A30_8BADBDCD49B6__INCLUDED_)
