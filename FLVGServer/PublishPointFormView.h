#if !defined(AFX_PUBLISHPOINTFORMVIEW_H__FEF65338_0DF7_40DB_8191_1548A188A84B__INCLUDED_)
#define AFX_PUBLISHPOINTFORMVIEW_H__FEF65338_0DF7_40DB_8191_1548A188A84B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PublishPointFormView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPublishPointFormView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CPublishPointFormView : public CXTMainFormView
{
protected:
	CPublishPointFormView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CPublishPointFormView)

// Form Data
public:
	//{{AFX_DATA(CPublishPointFormView)
	enum { IDD = IDD_DIALOG_PUBLISHPOINT };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

// Attributes
public:
	XDLS_Setting *m_pSetting;
	
	CPicture	m_jpgBackGround;
	CFont		m_wideFont;
	CFont		m_thinFont;
	// Operations
public:
	void RecalcLayout();
	void InitSetting(XDLS_Setting *pSetting);	
	void Server_Run();
	void Server_Stop();
	void Wnd_Active(BOOL bActive);
	void OnTimerWork(UINT nID);
	
	void OnDrawInfo(CDC *pDC);
	
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPublishPointFormView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CPublishPointFormView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CPublishPointFormView)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PUBLISHPOINTFORMVIEW_H__FEF65338_0DF7_40DB_8191_1548A188A84B__INCLUDED_)
