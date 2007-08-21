// XDLTheme.h: interface for the CXDLTheme class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_XDLTHEME_H__8B039169_50B4_43B7_81F7_DA6D3AACD60E__INCLUDED_)
#define AFX_XDLTHEME_H__8B039169_50B4_43B7_81F7_DA6D3AACD60E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define XDLCOLOR_3DFACE RGB(230, 230, 230)
#define XDLCOLOR_3DSHADOW RGB(153, 153, 153)
#define XDLCOLOR_BTNHIGHLIGHT RGB(255, 255, 255)

class CXDLTheme : public CXTPDefaultTheme  
{
public:
	CXDLTheme();
	virtual ~CXDLTheme();

	virtual void FillStatusBar(CDC* pDC, CXTPStatusBar* pBar);
	virtual void FillDockBar(CDC* pDC, CXTPDockBar* pBar);
	virtual void DrawStatusBarGripper(CDC* pDC, CRect rcClient);
	virtual void DrawStatusBarPane(CDC* pDC, CRect& rc, DWORD dwStyle, CString str);
	
	virtual void FillCommandBarEntry(CDC* pDC, CXTPCommandBar* pBar);
	CSize DrawCommandBarGripper(CDC* pDC, CXTPCommandBar* pBar, BOOL bDraw);
	
	CSize DrawCommandBarSeparator(CDC* pDC, CXTPCommandBar* pBar, CXTPControl* pControl, BOOL bDraw);
	void DrawRectangle(CDC* pDC, CRect rc, BOOL bSelected, BOOL bPressed, BOOL bEnabled, BOOL bChecked, BOOL bPopuped, BOOL bToolBar, XTPBarPosition barPosition = xtpBarPopup);
	
	void AdjustExcludeRect(CRect& rc, CXTPControl* pControl);
	
};

class CXDLDockingTheme:  public CXTPDockingPaneOffice2003Theme
{
public :
	CXDLDockingTheme();
	virtual ~CXDLDockingTheme();
	
	virtual void DrawPane(CDC& dc, CXTPDockingPaneTabbedContainer* pPane, CRect rc);
	virtual void DrawCaption(CDC& dc, CXTPDockingPaneTabbedContainer* pPane, CRect rc);
protected:
	virtual void DrawCaptionPart(CDC& dc, CXTPDockingPaneBase* pPane, CRect rcCaption, CString strTitle, BOOL bActive);
	virtual void DrawSplitter(CDC& dc, CXTPDockingPaneSplitterWnd* pSplitter);
};
#endif // !defined(AFX_XDLTHEME_H__8B039169_50B4_43B7_81F7_DA6D3AACD60E__INCLUDED_)
