#if !defined(AFX_XTMAINFRM_H__F3A5899E_6F22_468C_B5C9_97F415A8B28C__INCLUDED_)
#define AFX_XTMAINFRM_H__F3A5899E_6F22_468C_B5C9_97F415A8B28C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// XTMainFrm.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CXTMainFrm frame
#define XDL_HTMINIMIZE 1
#define XDL_HTMAXIMIZE 2
#define XDL_HTCLOSE 3


class CXTMainFrm : public CXTPFrameWnd
{
	DECLARE_DYNCREATE(CXTMainFrm)
protected:
	CXTMainFrm();           // protected constructor used by dynamic creation

// Attributes
public:
	CRect m_rcBorders;
	CBitmap m_bmpBottomLeft;
	CBitmap m_bmpBottomRight;
	
	CBitmap m_bmpMenuNormal;
	CBitmap m_bmpCaption;
	
	CBitmap m_bmpCloseNormal;
	CBitmap m_bmpMaximizeNormal;
	CBitmap m_bmpMinimizeNormal;
	
	CBitmap m_bmpClosePushed;
	CBitmap m_bmpMaximizePushed;
	CBitmap m_bmpMinimizePushed;
	
	CFont m_fntTitle;
	
	int m_nButtonDown;
// Operations
public:
	int GetSysButtonsHitTest(CPoint point);
	virtual void GetWindowTitle (CString& rString){GetWindowText(rString);};
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXTMainFrm)
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CXTMainFrm();

	// Generated message map functions
	//{{AFX_MSG(CXTMainFrm)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnNcPaint();
	afx_msg void OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS FAR* lpncsp);
	afx_msg UINT OnNcHitTest(CPoint point);
	afx_msg void OnNcLButtonDown(UINT nHitTest, CPoint point);
	afx_msg void OnNcLButtonUp(UINT nHitTest, CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnWindowPosChanging(WINDOWPOS* lpwndpos);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnCaptureChanged(CWnd *pWnd);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg BOOL OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//////////////////////////////////////////////////////////////////////////

class CXTMainDlg : public CXTResizeDialog
{
	DECLARE_DYNCREATE(CXTMainDlg)
protected:
	CXTMainDlg(const UINT nID,CWnd* pParent = 0,const UINT nFlags = 0);           // protected constructor used by dynamic creation
	CXTMainDlg();
// Attributes
public:
	CRect m_rcBorders;
	CBitmap m_bmpBottomLeft;
	CBitmap m_bmpBottomRight;
	
	CBitmap m_bmpMenuNormal;
	CBitmap m_bmpCaption;
	
	CBitmap m_bmpCloseNormal;
	CBitmap m_bmpMaximizeNormal;
	CBitmap m_bmpMinimizeNormal;
	
	CBitmap m_bmpClosePushed;
	CBitmap m_bmpMaximizePushed;
	CBitmap m_bmpMinimizePushed;
	
	CFont m_fntTitle;
	
	int m_nButtonDown;

	CBrush	m_EraseBkgndBrush;
// Operations
public:
	int GetSysButtonsHitTest(CPoint point);
	
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXTMainDlg)
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CXTMainDlg();

	// Generated message map functions
	//{{AFX_MSG(CXTMainDlg)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnNcPaint();
	afx_msg void OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS FAR* lpncsp);
	afx_msg UINT OnNcHitTest(CPoint point);
	afx_msg void OnNcLButtonDown(UINT nHitTest, CPoint point);
	afx_msg void OnNcLButtonUp(UINT nHitTest, CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnWindowPosChanging(WINDOWPOS* lpwndpos);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnCaptureChanged(CWnd *pWnd);
	afx_msg BOOL OnEraseBkgnd(CDC *pDC);
	afx_msg HBRUSH OnCtlColor(CDC *pDC, CWnd *pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//////////////////////////////////////////////////////////////////////////
class CXTMainPropertySheet : public CPropertySheet
{
	DECLARE_DYNCREATE(CXTMainPropertySheet)
protected:
	CXTMainPropertySheet(const UINT nID,CWnd* pParent = 0,const UINT nFlags = 0);           // protected constructor used by dynamic creation
	CXTMainPropertySheet();
	// Attributes
public:
	CRect m_rcBorders;
	CBitmap m_bmpBottomLeft;
	CBitmap m_bmpBottomRight;
	
	CBitmap m_bmpMenuNormal;
	CBitmap m_bmpCaption;
	
	CBitmap m_bmpCloseNormal;
	CBitmap m_bmpMaximizeNormal;
	CBitmap m_bmpMinimizeNormal;
	
	CBitmap m_bmpClosePushed;
	CBitmap m_bmpMaximizePushed;
	CBitmap m_bmpMinimizePushed;
	
	CFont m_fntTitle;
	
	int m_nButtonDown;
	
	CBrush	m_EraseBkgndBrush;
	// Operations
public:
	int GetSysButtonsHitTest(CPoint point);
	
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXTMainPropertySheet)
	//}}AFX_VIRTUAL
	
	// Implementation
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnNcPaint();
protected:
	virtual ~CXTMainPropertySheet();
	
	// Generated message map functions
	//{{AFX_MSG(CXTMainPropertySheet)
	afx_msg void OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS FAR* lpncsp);
	afx_msg UINT OnNcHitTest(CPoint point);
	afx_msg void OnNcLButtonDown(UINT nHitTest, CPoint point);
	afx_msg void OnNcLButtonUp(UINT nHitTest, CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnWindowPosChanging(WINDOWPOS* lpwndpos);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnCaptureChanged(CWnd *pWnd);
	afx_msg BOOL OnEraseBkgnd(CDC *pDC);
	afx_msg HBRUSH OnCtlColor(CDC *pDC, CWnd *pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
class CXTMainPropertyPage :public CPropertyPage, public CXTResize
{
	DECLARE_DYNCREATE(CXTMainPropertyPage)
public:
	CXTMainPropertyPage();
	CXTMainPropertyPage(UINT nIDTemplate, UINT nIDCaption = 0);
	
protected:
	CBrush	m_EraseBkgndBrush;

	virtual BOOL OnInitDialog();
	// Generated message map functions
	//{{AFX_MSG(CXTMainPropertySheet)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO *lpMMI);
	afx_msg void OnDestroy();
	afx_msg BOOL OnEraseBkgnd(CDC *pDC);
	afx_msg HBRUSH OnCtlColor(CDC *pDC, CWnd *pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
		
};
//////////////////////////////////////////////////////////////////////////
class CXTMainFormView :public CFormView, public CXTResize
{
	DECLARE_DYNCREATE(CXTMainFormView)
public:
	CXTMainFormView();
	CXTMainFormView(UINT nIDTemplate);
	
	virtual void OnInitialUpdate();
protected:
	CBrush	m_EraseBkgndBrush;
	BOOL	m_bInitialized;
	// Generated message map functions
	//{{AFX_MSG(CXTMainPropertySheet)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO *lpMMI);
	afx_msg void OnDestroy();
	afx_msg BOOL OnEraseBkgnd(CDC *pDC);
	afx_msg HBRUSH OnCtlColor(CDC *pDC, CWnd *pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
		
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XTMAINFRM_H__F3A5899E_6F22_468C_B5C9_97F415A8B28C__INCLUDED_)
