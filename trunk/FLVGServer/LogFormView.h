#if !defined(AFX_LOGFORMVIEW_H__5EE94155_F283_48C4_9C1F_36FCDA882A63__INCLUDED_)
#define AFX_LOGFORMVIEW_H__5EE94155_F283_48C4_9C1F_36FCDA882A63__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LogFormView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLogFormView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif
#include <afxrich.h>        // MFC rich edit classes

class CLogFormView : public CXTMainFormView

{
protected:
	CLogFormView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CLogFormView)

	
	
	virtual HRESULT STDMETHODCALLTYPE OnUpdateMsg(BSTR psz_module, int i_type, BSTR psz_msg);
	
// Form Data
public:
	//{{AFX_DATA(CLogFormView)
	enum { IDD = IDD_DIALOG_LOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

// Attributes
public:
	XDLS_Setting *m_pSetting;
	CRichEditView* m_pRichEditView;
	CXTButton m_btnClear;
	CPicture	m_jpgBackGround;
	BOOL		m_bActive;
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
	//{{AFX_VIRTUAL(CLogFormView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CLogFormView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CLogFormView)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	afx_msg void OnClearMsg();
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LOGFORMVIEW_H__5EE94155_F283_48C4_9C1F_36FCDA882A63__INCLUDED_)
