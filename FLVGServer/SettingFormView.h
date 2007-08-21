#if !defined(AFX_SETTINGFORMVIEW_H__E0E8DD9D_3A8A_4379_AD43_74E89A5771FA__INCLUDED_)
#define AFX_SETTINGFORMVIEW_H__E0E8DD9D_3A8A_4379_AD43_74E89A5771FA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SettingFormView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSettingFormView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif
#include "SettingVODDlg.h"
#include "Settingp2pDlg.h"
inline COLORREF GetStaticFrameColor(BOOL bTopLeft)
{
	XTPPaintTheme theme = XTPPaintManager()->BaseTheme();
	const COLORREF clrFrame = theme == xtpThemeNativeWinXP? GetXtremeColor(XPCOLOR_STATICFRAME): theme == xtpThemeOffice2003?
		GetXtremeColor(XPCOLOR_FRAME): GetXtremeColor(bTopLeft?COLOR_3DSHADOW: COLOR_3DHIGHLIGHT);
	return clrFrame;
}
template<class BASE_CLASS>
class CStaticFrameWnd : public BASE_CLASS
{
public:
	
protected:
	
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
	{
		switch (message)
		{
		case WM_NCPAINT:
			{
				CWindowDC dc(this);
				CXTPWindowRect rc(this);
				
				dc.Draw3dRect(0, 0, rc.Width(), rc.Height(), GetStaticFrameColor(TRUE), GetStaticFrameColor(FALSE));
				return TRUE;
			}
			
		case WM_NCCALCSIZE:
			{
				NCCALCSIZE_PARAMS FAR* lpncsp = (NCCALCSIZE_PARAMS FAR*)lParam;
				
				// adjust non-client area for border space
				lpncsp->rgrc[0].left   += 1;
				lpncsp->rgrc[0].top    += 1;
				lpncsp->rgrc[0].right  -= 1;
				lpncsp->rgrc[0].bottom -= 1;
				
				return TRUE;
			}
		}
		
		return BASE_CLASS::WindowProc(message, wParam, lParam);
	}
};
class CSettingFormView : public CXTMainFormView
{
protected:
	CSettingFormView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CSettingFormView)

// Form Data
public:
	//{{AFX_DATA(CSettingFormView)
	enum { IDD = IDD_DIALOG_SETTING };
	CXTButton	m_btnApply;
	CXTButton	m_btnDefault;
	//}}AFX_DATA

// Attributes
public:
	XDLS_Setting *m_pSetting;
	CPicture	m_jpgBackGround;
	
	CStaticFrameWnd<CXTPTaskPanel>  m_wndSettingPanel;
	CSettingVODDlg	m_SettingVODDlg;
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
	//{{AFX_VIRTUAL(CSettingFormView)
	public:
	virtual void OnFinalRelease();
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CSettingFormView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CSettingFormView)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	afx_msg void OnButtonDefault();
	afx_msg void OnButtonApply();
	//}}AFX_MSG
	afx_msg LRESULT OnPanelNotify (WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETTINGFORMVIEW_H__E0E8DD9D_3A8A_4379_AD43_74E89A5771FA__INCLUDED_)
