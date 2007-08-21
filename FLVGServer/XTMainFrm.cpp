// XTMainFrm.cpp : implementation file
//

#include "stdafx.h"
#include "XDigitalLifeServerApp.h"
#include "XTMainFrm.h"
#include "XDLTheme.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CXTMainFrm

IMPLEMENT_DYNCREATE(CXTMainFrm, CFrameWnd)

CXTMainFrm::CXTMainFrm()
{
	m_rcBorders.SetRect(4, 4, 4, 4);
	m_nButtonDown = 0;
}

CXTMainFrm::~CXTMainFrm()
{
}


BEGIN_MESSAGE_MAP(CXTMainFrm, CFrameWnd)
	//{{AFX_MSG_MAP(CXTMainFrm)
	ON_WM_CREATE()
	ON_WM_NCPAINT()
	ON_WM_NCCALCSIZE()
	ON_WM_NCHITTEST()
	ON_WM_NCLBUTTONDOWN()
	ON_WM_NCLBUTTONUP()
	ON_WM_SIZE()
	ON_WM_WINDOWPOSCHANGING()
	ON_WM_LBUTTONUP()
	ON_WM_CAPTURECHANGED()
	ON_WM_ERASEBKGND()
	ON_WM_COPYDATA()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CXTMainFrm message handlers


int CXTMainFrm::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	SetMenu(0);
	ModifyStyle(WS_BORDER, 0);

	VERIFY(m_bmpBottomLeft.LoadBitmap(IDB_XDL_BOTTOMLEFT));
	VERIFY(m_bmpBottomRight.LoadBitmap(IDB_XDL_BOTTOMRIGHT));
	VERIFY(m_bmpMenuNormal.LoadBitmap(IDB_XDL_MENU_NORMAL));
	VERIFY(m_bmpCaption.LoadBitmap(IDB_XDL_CAPTION));
	VERIFY(m_bmpCloseNormal.LoadBitmap(IDB_XDL_CLOSE_NORMAL));
	VERIFY(m_bmpMaximizeNormal.LoadBitmap(IDB_XDL_MAXIMIZE_NORMAL));
	VERIFY(m_bmpMinimizeNormal.LoadBitmap(IDB_XDL_MINIMIZE_NORMAL));

	VERIFY(m_bmpClosePushed.LoadBitmap(IDB_XDL_CLOSE_PUSHED));
	VERIFY(m_bmpMaximizePushed.LoadBitmap(IDB_XDL_MAXIMIZE_PUSHED));
	VERIFY(m_bmpMinimizePushed.LoadBitmap(IDB_XDL_MINIMIZE_PUSHED));

	MoveWindow(CXTPWindowRect(this));

	NONCLIENTMETRICS ncm;

	ZeroMemory(&ncm, sizeof(NONCLIENTMETRICS));
	ncm.cbSize = sizeof(NONCLIENTMETRICS);
	VERIFY(::SystemParametersInfo(SPI_GETNONCLIENTMETRICS, sizeof(NONCLIENTMETRICS), &ncm, 0));

	m_fntTitle.CreateFontIndirect(&ncm.lfCaptionFont);

	return 0;
}

/////////////////////////////////////////////////////////////////////////////
// CXTMainFrm message handlers

#define XDLCAPTION_HEIGHT 20

void CXTMainFrm::OnNcPaint()
{
	//yan
	CWindowDC dcWindow(this);
	CXTPWindowRect rc(this);
	CXTPClientRect rcClient(this);
	ClientToScreen(&rcClient);

	rcClient.OffsetRect(-rc.TopLeft());
	rc.OffsetRect(-rc.TopLeft());

	CRgn rgnClient;
	rgnClient.CreateRectRgnIndirect(rcClient);

	CRgn rgnWindow;
	rgnWindow.CreateRoundRectRgn(rc.left, rc.top, rc.right, rc.bottom, 11, 11);

	dcWindow.SelectClipRgn(&rgnWindow);
	dcWindow.SelectClipRgn(&rgnClient, RGN_XOR );
	{
		CXTPBufferDC dc(dcWindow, rc);

		CXTPPenDC pen(dc, 0);
		CXTPBrushDC brush(dc, XDLCOLOR_3DFACE);

		dc.FillSolidRect(0, 0, rc.Width(), rc.Height(), 0);
		dc.RoundRect(0, 0, rc.Width() - 1, rc.Height() - 1, 14, 14);

		dc.FillSolidRect(0, XDLCAPTION_HEIGHT - 1, rc.Width(), 1, RGB(11, 11, 12));
		dc.FillSolidRect(1, XDLCAPTION_HEIGHT, 1, rc.Height() - XDLCAPTION_HEIGHT - 6, RGB(0xFF, 0xFF, 0xFF));

		dc.FillSolidRect(5, XDLCAPTION_HEIGHT, 1, rc.Height() - XDLCAPTION_HEIGHT - 6, RGB(161, 161, 161));
		dc.FillSolidRect(rc.Width() - 3, XDLCAPTION_HEIGHT, 1, rc.Height() - XDLCAPTION_HEIGHT - 6, RGB(196, 196, 196));
		dc.FillSolidRect(rc.Width() - 6, XDLCAPTION_HEIGHT, 1, rc.Height() - XDLCAPTION_HEIGHT - 6, RGB(255, 255, 255));
		dc.FillSolidRect(rc.Width() - 7, XDLCAPTION_HEIGHT, 1, rc.Height() - XDLCAPTION_HEIGHT - 6, RGB(161, 161, 161));

		dc.FillSolidRect(5, rc.Height() - 3, rc.Width() - 11, 1, RGB(184, 184, 184));
		dc.FillSolidRect(5, rc.Height() - 6, rc.Width() - 11, 1, RGB(255, 255, 255));
		dc.FillSolidRect(5, rc.Height() - 7, rc.Width() - 11, 1, RGB(161, 161, 161));


		dc.FillSolidRect(10, 1, rc.Width() - 20, 1, RGB(149, 169, 214));

		for (int nCaption = 23; nCaption < rc.Width() - 33; nCaption += 30)
		{
			dc.DrawState(CPoint(nCaption, 2), CSize(30, 17), m_bmpCaption, DST_BITMAP|DSS_NORMAL);
		}

		dc.DrawState(CPoint(1, rc.Height() - 23), CSize(21, 21), m_bmpBottomLeft, DST_BITMAP|DSS_NORMAL);
		dc.DrawState(CPoint(rc.Width() - 23, rc.Height() - 23), CSize(21, 21), m_bmpBottomRight, DST_BITMAP|DSS_NORMAL);
		dc.DrawState(CPoint(1, 1), CSize(22, 19), m_bmpMenuNormal, DST_BITMAP|DSS_NORMAL);


		dc.DrawState(CPoint(rc.Width() - 23, 1), CSize(21, 19), m_nButtonDown == XDL_HTCLOSE? m_bmpClosePushed: m_bmpCloseNormal, DST_BITMAP|DSS_NORMAL);
		dc.DrawState(CPoint(rc.Width() - 23 - 21, 1), CSize(21, 19), m_nButtonDown == XDL_HTMAXIMIZE? m_bmpMaximizePushed: m_bmpMaximizeNormal, DST_BITMAP|DSS_NORMAL);
		dc.DrawState(CPoint(rc.Width() - 23 - 21*2, 1), CSize(21, 19), m_nButtonDown == XDL_HTMINIMIZE? m_bmpMinimizePushed: m_bmpMinimizeNormal, DST_BITMAP|DSS_NORMAL);

		CRect rcTitle(rc.left + 30, rc.top, rc.right - 70, rc.top + XDLCAPTION_HEIGHT);
		dc.SetBkMode(TRANSPARENT);
		dc.SetTextColor(RGB(255, 255, 255));

		CString strTitle;
		GetWindowTitle(strTitle);

		CXTPFontDC font(&dc, &m_fntTitle);
		dc.DrawText(strTitle, rcTitle, DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS|DT_NOCLIP);

	}


	dcWindow.SelectClipRgn(NULL);
}

void CXTMainFrm::OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS FAR* lpncsp)
{
	lpncsp->rgrc[0].top += XDLCAPTION_HEIGHT - m_rcBorders.top;
	lpncsp->rgrc[0].left += 6 - m_rcBorders.left;
	lpncsp->rgrc[0].right -= 6 - m_rcBorders.right + 1;
	lpncsp->rgrc[0].bottom -= 6 - m_rcBorders.bottom + 1;

	CFrameWnd::OnNcCalcSize(bCalcValidRects, lpncsp);
}

UINT CXTMainFrm::OnNcHitTest(CPoint point)
{
	int nHit = CFrameWnd::OnNcHitTest(point);

	CRect rcWindow;
	GetWindowRect(&rcWindow);

	if (point.y < rcWindow.top + XDLCAPTION_HEIGHT && nHit == HTNOWHERE)
	{
		//if (point.x < rcWindow.right - 23 * 3)
		//  return HTCAPTION;
		return HTCAPTION;
	}

	return nHit;
}

void CXTMainFrm::OnSize(UINT nType, int cx, int cy)
{
	CFrameWnd::OnSize(nType, cx, cy);


}

void CXTMainFrm::OnWindowPosChanging(WINDOWPOS* lpwndpos)
{
	CFrameWnd::OnWindowPosChanging(lpwndpos);

	if ((lpwndpos->flags & SWP_NOSIZE) ==  0 )
	{
		CRgn rgnResult;
		rgnResult.CreateRoundRectRgn(0, 0, lpwndpos->cx, lpwndpos->cy, 11, 11);

		SetWindowRgn((HRGN)rgnResult.Detach(), TRUE);
	}
}

int CXTMainFrm::GetSysButtonsHitTest(CPoint point)
{
	CRect rcWindow;
	GetWindowRect(&rcWindow);

	if (point.y < rcWindow.top + XDLCAPTION_HEIGHT && (point.x > rcWindow.right - 23))
		return XDL_HTCLOSE;
	if (point.y < rcWindow.top + XDLCAPTION_HEIGHT && (point.x > rcWindow.right - 23 - 21))
		return XDL_HTMAXIMIZE;
	if (point.y < rcWindow.top + XDLCAPTION_HEIGHT && (point.x > rcWindow.right - 23 - 21 - 21))
		return XDL_HTMINIMIZE;
	return 0;
}

void CXTMainFrm::OnNcLButtonDown(UINT nHitTest, CPoint point)
{
	if (nHitTest == HTCAPTION)
	{
		int nHit = GetSysButtonsHitTest(point);

		if (nHit > 0)
		{
			SetCapture();
			m_nButtonDown = nHit;
			RedrawWindow(0, 0, RDW_FRAME|RDW_INVALIDATE );
		}
	}


	CFrameWnd::OnNcLButtonDown(nHitTest, point);
}

void CXTMainFrm::OnNcLButtonUp(UINT nHitTest, CPoint point)
{

	CFrameWnd::OnNcLButtonUp(nHitTest, point);
}

void CXTMainFrm::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (m_nButtonDown > 0)
	{
		int nButtonDown = m_nButtonDown;

		m_nButtonDown = 0;
		RedrawWindow(0, 0, RDW_FRAME|RDW_INVALIDATE );
		ReleaseCapture();

		ClientToScreen(&point);

		if (GetSysButtonsHitTest(point) == nButtonDown)
		{
			switch (nButtonDown)
			{
				case XDL_HTCLOSE: SendMessage(WM_SYSCOMMAND, SC_CLOSE); break;
				case XDL_HTMAXIMIZE:
					SendMessage(WM_SYSCOMMAND, (GetStyle() & WS_MAXIMIZE) != 0? SC_RESTORE: SC_MAXIMIZE ); break;
				case XDL_HTMINIMIZE: SendMessage(WM_SYSCOMMAND, SC_MINIMIZE); break;
			}
		}
		return;

	}

	CFrameWnd::OnLButtonUp(nFlags, point);
}

void CXTMainFrm::OnCaptureChanged(CWnd *pWnd)
{
	if (m_nButtonDown > 0)
	{
		m_nButtonDown = 0;
		RedrawWindow(0, 0, RDW_FRAME|RDW_INVALIDATE );
	}

	CFrameWnd::OnCaptureChanged(pWnd);
}
BOOL CXTMainFrm::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	
	return CFrameWnd::OnEraseBkgnd(pDC);
}

//////////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNCREATE(CXTMainDlg, CXTResizeDialog)
CXTMainDlg::CXTMainDlg()
{	
	m_rcBorders.SetRect(4, 4, 4, 4);
	m_EraseBkgndBrush.CreateSolidBrush(RGB(221, 221, 221));
	m_nButtonDown = 0;
}
CXTMainDlg::CXTMainDlg(const UINT nID,CWnd* pParent,const UINT nFlags):
CXTResizeDialog(nID, pParent, nFlags)
{
	m_rcBorders.SetRect(4, 4, 4, 4);
	m_EraseBkgndBrush.CreateSolidBrush(RGB(221, 221, 221));
	m_nButtonDown = 0;
}

CXTMainDlg::~CXTMainDlg()
{
}


BEGIN_MESSAGE_MAP(CXTMainDlg, CXTResizeDialog)
	//{{AFX_MSG_MAP(CXTMainDlg)
	ON_WM_CREATE()
	ON_WM_NCPAINT()
	ON_WM_NCCALCSIZE()
	ON_WM_NCHITTEST()
	ON_WM_NCLBUTTONDOWN()
	ON_WM_NCLBUTTONUP()
	ON_WM_SIZE()
	ON_WM_WINDOWPOSCHANGING()
	ON_WM_LBUTTONUP()
	ON_WM_CAPTURECHANGED()
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CXTMainDlg message handlers


int CXTMainDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CXTResizeDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	SetMenu(0);
	ModifyStyle(WS_BORDER, 0);

	VERIFY(m_bmpBottomLeft.LoadBitmap(IDB_XDL_BOTTOMLEFT));
	VERIFY(m_bmpBottomRight.LoadBitmap(IDB_XDL_BOTTOMRIGHT));
	VERIFY(m_bmpMenuNormal.LoadBitmap(IDB_XDL_MENU_NORMAL));
	VERIFY(m_bmpCaption.LoadBitmap(IDB_XDL_CAPTION));
	VERIFY(m_bmpCloseNormal.LoadBitmap(IDB_XDL_CLOSE_NORMAL));
	VERIFY(m_bmpMaximizeNormal.LoadBitmap(IDB_XDL_MAXIMIZE_NORMAL));
	VERIFY(m_bmpMinimizeNormal.LoadBitmap(IDB_XDL_MINIMIZE_NORMAL));

	VERIFY(m_bmpClosePushed.LoadBitmap(IDB_XDL_CLOSE_PUSHED));
	VERIFY(m_bmpMaximizePushed.LoadBitmap(IDB_XDL_MAXIMIZE_PUSHED));
	VERIFY(m_bmpMinimizePushed.LoadBitmap(IDB_XDL_MINIMIZE_PUSHED));

	MoveWindow(CXTPWindowRect(this));

	NONCLIENTMETRICS ncm;

	ZeroMemory(&ncm, sizeof(NONCLIENTMETRICS));
	ncm.cbSize = sizeof(NONCLIENTMETRICS);
	VERIFY(::SystemParametersInfo(SPI_GETNONCLIENTMETRICS, sizeof(NONCLIENTMETRICS), &ncm, 0));

	m_fntTitle.CreateFontIndirect(&ncm.lfCaptionFont);

	XTThemeManager()->SetTheme(xtThemeOffice2003);
	if (XTThemeManager()->GetTheme() == xtThemeOfficeXP ||
		XTThemeManager()->GetTheme() == xtThemeOffice2003)
	{
		((CXTButtonThemeOfficeXP*)CXTButton::GetDefaultTheme())->UseWordTheme(TRUE);
	}

	return 0;
}

/////////////////////////////////////////////////////////////////////////////
// CXTMainDlg message handlers


void CXTMainDlg::OnNcPaint()
{
	CWindowDC dcWindow(this);
	CXTPWindowRect rc(this);
	CXTPClientRect rcClient(this);
	ClientToScreen(&rcClient);

	rcClient.OffsetRect(-rc.TopLeft());
	rc.OffsetRect(-rc.TopLeft());

	CRgn rgnClient;
	rgnClient.CreateRectRgnIndirect(rcClient);

	CRgn rgnWindow;
	rgnWindow.CreateRoundRectRgn(rc.left, rc.top, rc.right, rc.bottom, 11, 11);

	dcWindow.SelectClipRgn(&rgnWindow);
	dcWindow.SelectClipRgn(&rgnClient, RGN_XOR );
	{
		CXTPBufferDC dc(dcWindow, rc);

		CXTPPenDC pen(dc, 0);
		CXTPBrushDC brush(dc, XDLCOLOR_3DFACE);

		dc.FillSolidRect(0, 0, rc.Width(), rc.Height(), 0);
		dc.RoundRect(0, 0, rc.Width() - 1, rc.Height() - 1, 14, 14);

		dc.FillSolidRect(0, XDLCAPTION_HEIGHT - 1, rc.Width(), 1, RGB(11, 11, 12));
		dc.FillSolidRect(1, XDLCAPTION_HEIGHT, 1, rc.Height() - XDLCAPTION_HEIGHT - 6, RGB(0xFF, 0xFF, 0xFF));

		dc.FillSolidRect(5, XDLCAPTION_HEIGHT, 1, rc.Height() - XDLCAPTION_HEIGHT - 6, RGB(161, 161, 161));
		dc.FillSolidRect(rc.Width() - 3, XDLCAPTION_HEIGHT, 1, rc.Height() - XDLCAPTION_HEIGHT - 6, RGB(196, 196, 196));
		dc.FillSolidRect(rc.Width() - 6, XDLCAPTION_HEIGHT, 1, rc.Height() - XDLCAPTION_HEIGHT - 6, RGB(255, 255, 255));
		dc.FillSolidRect(rc.Width() - 7, XDLCAPTION_HEIGHT, 1, rc.Height() - XDLCAPTION_HEIGHT - 6, RGB(161, 161, 161));

		dc.FillSolidRect(5, rc.Height() - 3, rc.Width() - 11, 1, RGB(184, 184, 184));
		dc.FillSolidRect(5, rc.Height() - 6, rc.Width() - 11, 1, RGB(255, 255, 255));
		dc.FillSolidRect(5, rc.Height() - 7, rc.Width() - 11, 1, RGB(161, 161, 161));


		dc.FillSolidRect(10, 1, rc.Width() - 20, 1, RGB(149, 169, 214));

		for (int nCaption = 23; nCaption < rc.Width() - 33; nCaption += 30)
		{
			dc.DrawState(CPoint(nCaption, 2), CSize(30, 17), m_bmpCaption, DST_BITMAP|DSS_NORMAL);
		}

		dc.DrawState(CPoint(1, rc.Height() - 23), CSize(21, 21), m_bmpBottomLeft, DST_BITMAP|DSS_NORMAL);
		dc.DrawState(CPoint(rc.Width() - 23, rc.Height() - 23), CSize(21, 21), m_bmpBottomRight, DST_BITMAP|DSS_NORMAL);
		dc.DrawState(CPoint(1, 1), CSize(22, 19), m_bmpMenuNormal, DST_BITMAP|DSS_NORMAL);


		dc.DrawState(CPoint(rc.Width() - 23, 1), CSize(21, 19), m_nButtonDown == XDL_HTCLOSE? m_bmpClosePushed: m_bmpCloseNormal, DST_BITMAP|DSS_NORMAL);
		dc.DrawState(CPoint(rc.Width() - 23 - 21, 1), CSize(21, 19), m_nButtonDown == XDL_HTMAXIMIZE? m_bmpMaximizePushed: m_bmpMaximizeNormal, DST_BITMAP|DSS_NORMAL);
		dc.DrawState(CPoint(rc.Width() - 23 - 21*2, 1), CSize(21, 19), m_nButtonDown == XDL_HTMINIMIZE? m_bmpMinimizePushed: m_bmpMinimizeNormal, DST_BITMAP|DSS_NORMAL);

		CRect rcTitle(rc.left + 30, rc.top, rc.right - 70, rc.top + XDLCAPTION_HEIGHT);
		dc.SetBkMode(TRANSPARENT);
		dc.SetTextColor(RGB(255, 255, 255));

		CString strTitle;
		GetWindowText(strTitle);

		CXTPFontDC font(&dc, &m_fntTitle);
		dc.DrawText(strTitle, rcTitle, DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS|DT_NOCLIP);

	}


	dcWindow.SelectClipRgn(NULL);
}

void CXTMainDlg::OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS FAR* lpncsp)
{
	lpncsp->rgrc[0].top += XDLCAPTION_HEIGHT - m_rcBorders.top + 1;
	lpncsp->rgrc[0].left += 7 - m_rcBorders.left;
	lpncsp->rgrc[0].right -= 8 - m_rcBorders.right;
	lpncsp->rgrc[0].bottom -= 8 - m_rcBorders.bottom;

	CXTResizeDialog::OnNcCalcSize(bCalcValidRects, lpncsp);
}

UINT CXTMainDlg::OnNcHitTest(CPoint point)
{
	int nHit = CXTResizeDialog::OnNcHitTest(point);

	CRect rcWindow;
	GetWindowRect(&rcWindow);

	if (point.y < rcWindow.top + XDLCAPTION_HEIGHT && nHit == HTNOWHERE)
	{
		//if (point.x < rcWindow.right - 23 * 3)
		//  return HTCAPTION;
		return HTCAPTION;
	}

	return nHit;
}

void CXTMainDlg::OnSize(UINT nType, int cx, int cy)
{
	CXTResizeDialog::OnSize(nType, cx, cy);


}

void CXTMainDlg::OnWindowPosChanging(WINDOWPOS* lpwndpos)
{
	CXTResizeDialog::OnWindowPosChanging(lpwndpos);

	if ((lpwndpos->flags & SWP_NOSIZE) ==  0 )
	{
		CRgn rgnResult;
		rgnResult.CreateRoundRectRgn(0, 0, lpwndpos->cx, lpwndpos->cy, 11, 11);

		SetWindowRgn((HRGN)rgnResult.Detach(), TRUE);
	}
}

int CXTMainDlg::GetSysButtonsHitTest(CPoint point)
{
	CRect rcWindow;
	GetWindowRect(&rcWindow);

	if (point.y < rcWindow.top + XDLCAPTION_HEIGHT && (point.x > rcWindow.right - 23))
		return XDL_HTCLOSE;
	if (point.y < rcWindow.top + XDLCAPTION_HEIGHT && (point.x > rcWindow.right - 23 - 21))
		return XDL_HTMAXIMIZE;
	if (point.y < rcWindow.top + XDLCAPTION_HEIGHT && (point.x > rcWindow.right - 23 - 21 - 21))
		return XDL_HTMINIMIZE;
	return 0;
}

void CXTMainDlg::OnNcLButtonDown(UINT nHitTest, CPoint point)
{
	if (nHitTest == HTCAPTION)
	{
		int nHit = GetSysButtonsHitTest(point);

		if (nHit > 0)
		{
			SetCapture();
			m_nButtonDown = nHit;
			RedrawWindow(0, 0, RDW_FRAME|RDW_INVALIDATE );
		}
	}


	CXTResizeDialog::OnNcLButtonDown(nHitTest, point);
}

void CXTMainDlg::OnNcLButtonUp(UINT nHitTest, CPoint point)
{

	CXTResizeDialog::OnNcLButtonUp(nHitTest, point);
}

void CXTMainDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (m_nButtonDown > 0)
	{
		int nButtonDown = m_nButtonDown;

		m_nButtonDown = 0;
		RedrawWindow(0, 0, RDW_FRAME|RDW_INVALIDATE );
		ReleaseCapture();

		ClientToScreen(&point);

		if (GetSysButtonsHitTest(point) == nButtonDown)
		{
			switch (nButtonDown)
			{
				case XDL_HTCLOSE: SendMessage(WM_SYSCOMMAND, SC_CLOSE); break;
				case XDL_HTMAXIMIZE:
					SendMessage(WM_SYSCOMMAND, (GetStyle() & WS_MAXIMIZE) != 0? SC_RESTORE: SC_MAXIMIZE ); break;
				case XDL_HTMINIMIZE: SendMessage(WM_SYSCOMMAND, SC_MINIMIZE); break;
			}
		}
		return;

	}

	CXTResizeDialog::OnLButtonUp(nFlags, point);
}

void CXTMainDlg::OnCaptureChanged(CWnd *pWnd)
{
	if (m_nButtonDown > 0)
	{
		m_nButtonDown = 0;
		RedrawWindow(0, 0, RDW_FRAME|RDW_INVALIDATE );
	}

	CXTResizeDialog::OnCaptureChanged(pWnd);
}

BOOL CXTMainDlg::OnEraseBkgnd(CDC* pDC) 
{
	CRect rc;
	GetClientRect(&rc);
	pDC->FillSolidRect(&rc, RGB(221, 221, 221));
	return TRUE;
}
HBRUSH CXTMainDlg::OnCtlColor(CDC *pDC, CWnd *pWnd, UINT nCtlColor)
{
	if(CTLCOLOR_STATIC == nCtlColor)
	{
		CRect rc;
		pWnd->GetClientRect(&rc);
		pDC->FillSolidRect(&rc, RGB(221, 221, 221));
		return (HBRUSH)m_EraseBkgndBrush.m_hObject;
	}
	return CXTResizeDialog::OnCtlColor(pDC, pWnd, nCtlColor);
}
////CXTMainPropertySheet//////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNCREATE(CXTMainPropertySheet, CPropertySheet)
CXTMainPropertySheet::CXTMainPropertySheet()
{	
	m_rcBorders.SetRect(4, 4, 4, 4);
	m_EraseBkgndBrush.CreateSolidBrush(RGB(221, 221, 221));
	m_nButtonDown = 0;
}
CXTMainPropertySheet::CXTMainPropertySheet(const UINT nID,CWnd* pParent,const UINT nFlags):
CPropertySheet(nID, pParent, nFlags)
{
	m_rcBorders.SetRect(4, 4, 4, 4);
	m_EraseBkgndBrush.CreateSolidBrush(RGB(221, 221, 221));
	m_nButtonDown = 0;
}

CXTMainPropertySheet::~CXTMainPropertySheet()
{
}


BEGIN_MESSAGE_MAP(CXTMainPropertySheet, CPropertySheet)
	//{{AFX_MSG_MAP(CXTMainPropertySheet)
	ON_WM_CREATE()
	ON_WM_NCPAINT()
	ON_WM_NCCALCSIZE()
	ON_WM_NCHITTEST()
	ON_WM_NCLBUTTONDOWN()
	ON_WM_NCLBUTTONUP()
	ON_WM_SIZE()
	ON_WM_WINDOWPOSCHANGING()
	ON_WM_LBUTTONUP()
	ON_WM_CAPTURECHANGED()
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CXTMainPropertySheet message handlers


int CXTMainPropertySheet::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CPropertySheet::OnCreate(lpCreateStruct) == -1)
		return -1;

	SetMenu(0);
	ModifyStyle(WS_BORDER, 0);

	VERIFY(m_bmpBottomLeft.LoadBitmap(IDB_XDL_BOTTOMLEFT));
	VERIFY(m_bmpBottomRight.LoadBitmap(IDB_XDL_BOTTOMRIGHT));
	VERIFY(m_bmpMenuNormal.LoadBitmap(IDB_XDL_MENU_NORMAL));
	VERIFY(m_bmpCaption.LoadBitmap(IDB_XDL_CAPTION));
	VERIFY(m_bmpCloseNormal.LoadBitmap(IDB_XDL_CLOSE_NORMAL));
	VERIFY(m_bmpMaximizeNormal.LoadBitmap(IDB_XDL_MAXIMIZE_NORMAL));
	VERIFY(m_bmpMinimizeNormal.LoadBitmap(IDB_XDL_MINIMIZE_NORMAL));

	VERIFY(m_bmpClosePushed.LoadBitmap(IDB_XDL_CLOSE_PUSHED));
	VERIFY(m_bmpMaximizePushed.LoadBitmap(IDB_XDL_MAXIMIZE_PUSHED));
	VERIFY(m_bmpMinimizePushed.LoadBitmap(IDB_XDL_MINIMIZE_PUSHED));

	MoveWindow(CXTPWindowRect(this));

	NONCLIENTMETRICS ncm;

	ZeroMemory(&ncm, sizeof(NONCLIENTMETRICS));
	ncm.cbSize = sizeof(NONCLIENTMETRICS);
	VERIFY(::SystemParametersInfo(SPI_GETNONCLIENTMETRICS, sizeof(NONCLIENTMETRICS), &ncm, 0));

	m_fntTitle.CreateFontIndirect(&ncm.lfCaptionFont);
	XTThemeManager()->SetTheme(xtThemeOffice2003);
	if (XTThemeManager()->GetTheme() == xtThemeOfficeXP ||
		XTThemeManager()->GetTheme() == xtThemeOffice2003)
	{
		((CXTButtonThemeOfficeXP*)CXTButton::GetDefaultTheme())->UseWordTheme(TRUE);
	}
	return 0;
}

/////////////////////////////////////////////////////////////////////////////
// CXTMainPropertySheet message handlers


void CXTMainPropertySheet::OnNcPaint()
{
	CWindowDC dcWindow(this);
	CXTPWindowRect rc(this);
	CXTPClientRect rcClient(this);
	ClientToScreen(&rcClient);

	rcClient.OffsetRect(-rc.TopLeft());
	rc.OffsetRect(-rc.TopLeft());

	CRgn rgnClient;
	rgnClient.CreateRectRgnIndirect(rcClient);

	CRgn rgnWindow;
	rgnWindow.CreateRoundRectRgn(rc.left, rc.top, rc.right, rc.bottom, 11, 11);

	dcWindow.SelectClipRgn(&rgnWindow);
	dcWindow.SelectClipRgn(&rgnClient, RGN_XOR );
	{
		CXTPBufferDC dc(dcWindow, rc);

		CXTPPenDC pen(dc, 0);
		CXTPBrushDC brush(dc, XDLCOLOR_3DFACE);

		dc.FillSolidRect(0, 0, rc.Width(), rc.Height(), 0);
		dc.RoundRect(0, 0, rc.Width() - 1, rc.Height() - 1, 14, 14);

		dc.FillSolidRect(0, XDLCAPTION_HEIGHT - 1, rc.Width(), 1, RGB(11, 11, 12));
		dc.FillSolidRect(1, XDLCAPTION_HEIGHT, 1, rc.Height() - XDLCAPTION_HEIGHT - 6, RGB(0xFF, 0xFF, 0xFF));

		dc.FillSolidRect(5, XDLCAPTION_HEIGHT, 1, rc.Height() - XDLCAPTION_HEIGHT - 6, RGB(161, 161, 161));
		dc.FillSolidRect(rc.Width() - 3, XDLCAPTION_HEIGHT, 1, rc.Height() - XDLCAPTION_HEIGHT - 6, RGB(196, 196, 196));
		dc.FillSolidRect(rc.Width() - 6, XDLCAPTION_HEIGHT, 1, rc.Height() - XDLCAPTION_HEIGHT - 6, RGB(255, 255, 255));
		dc.FillSolidRect(rc.Width() - 7, XDLCAPTION_HEIGHT, 1, rc.Height() - XDLCAPTION_HEIGHT - 6, RGB(161, 161, 161));

		dc.FillSolidRect(5, rc.Height() - 3, rc.Width() - 11, 1, RGB(184, 184, 184));
		dc.FillSolidRect(5, rc.Height() - 6, rc.Width() - 11, 1, RGB(255, 255, 255));
		dc.FillSolidRect(5, rc.Height() - 7, rc.Width() - 11, 1, RGB(161, 161, 161));


		dc.FillSolidRect(10, 1, rc.Width() - 20, 1, RGB(149, 169, 214));

		for (int nCaption = 23; nCaption < rc.Width() - 33; nCaption += 30)
		{
			dc.DrawState(CPoint(nCaption, 2), CSize(30, 17), m_bmpCaption, DST_BITMAP|DSS_NORMAL);
		}

		dc.DrawState(CPoint(1, rc.Height() - 23), CSize(21, 21), m_bmpBottomLeft, DST_BITMAP|DSS_NORMAL);
		dc.DrawState(CPoint(rc.Width() - 23, rc.Height() - 23), CSize(21, 21), m_bmpBottomRight, DST_BITMAP|DSS_NORMAL);
		dc.DrawState(CPoint(1, 1), CSize(22, 19), m_bmpMenuNormal, DST_BITMAP|DSS_NORMAL);


		dc.DrawState(CPoint(rc.Width() - 23, 1), CSize(21, 19), m_nButtonDown == XDL_HTCLOSE? m_bmpClosePushed: m_bmpCloseNormal, DST_BITMAP|DSS_NORMAL);
		dc.DrawState(CPoint(rc.Width() - 23 - 21, 1), CSize(21, 19), m_nButtonDown == XDL_HTMAXIMIZE? m_bmpMaximizePushed: m_bmpMaximizeNormal, DST_BITMAP|DSS_NORMAL);
		dc.DrawState(CPoint(rc.Width() - 23 - 21*2, 1), CSize(21, 19), m_nButtonDown == XDL_HTMINIMIZE? m_bmpMinimizePushed: m_bmpMinimizeNormal, DST_BITMAP|DSS_NORMAL);

		CRect rcTitle(rc.left + 30, rc.top, rc.right - 70, rc.top + XDLCAPTION_HEIGHT);
		dc.SetBkMode(TRANSPARENT);
		dc.SetTextColor(RGB(255, 255, 255));

		CString strTitle;
		GetWindowText(strTitle);

		CXTPFontDC font(&dc, &m_fntTitle);
		dc.DrawText(strTitle, rcTitle, DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS|DT_NOCLIP);

	}


	dcWindow.SelectClipRgn(NULL);
}

void CXTMainPropertySheet::OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS FAR* lpncsp)
{
	lpncsp->rgrc[0].top += XDLCAPTION_HEIGHT - m_rcBorders.top + 1;
	lpncsp->rgrc[0].left += 7 - m_rcBorders.left;
	lpncsp->rgrc[0].right -= 8 - m_rcBorders.right;
	lpncsp->rgrc[0].bottom -= 8 - m_rcBorders.bottom;

	CPropertySheet::OnNcCalcSize(bCalcValidRects, lpncsp);
}

UINT CXTMainPropertySheet::OnNcHitTest(CPoint point)
{
	int nHit = CPropertySheet::OnNcHitTest(point);

	CRect rcWindow;
	GetWindowRect(&rcWindow);

	if (point.y < rcWindow.top + XDLCAPTION_HEIGHT && nHit == HTNOWHERE)
	{
		//if (point.x < rcWindow.right - 23 * 3)
		//  return HTCAPTION;
		return HTCAPTION;
	}

	return nHit;
}

void CXTMainPropertySheet::OnSize(UINT nType, int cx, int cy)
{
	CPropertySheet::OnSize(nType, cx, cy);


}

void CXTMainPropertySheet::OnWindowPosChanging(WINDOWPOS* lpwndpos)
{
	CPropertySheet::OnWindowPosChanging(lpwndpos);

	if ((lpwndpos->flags & SWP_NOSIZE) ==  0 )
	{
		CRgn rgnResult;
		rgnResult.CreateRoundRectRgn(0, 0, lpwndpos->cx, lpwndpos->cy, 11, 11);

		SetWindowRgn((HRGN)rgnResult.Detach(), TRUE);
	}
}

int CXTMainPropertySheet::GetSysButtonsHitTest(CPoint point)
{
	CRect rcWindow;
	GetWindowRect(&rcWindow);

	if (point.y < rcWindow.top + XDLCAPTION_HEIGHT && (point.x > rcWindow.right - 23))
		return XDL_HTCLOSE;
	if (point.y < rcWindow.top + XDLCAPTION_HEIGHT && (point.x > rcWindow.right - 23 - 21))
		return XDL_HTMAXIMIZE;
	if (point.y < rcWindow.top + XDLCAPTION_HEIGHT && (point.x > rcWindow.right - 23 - 21 - 21))
		return XDL_HTMINIMIZE;
	return 0;
}

void CXTMainPropertySheet::OnNcLButtonDown(UINT nHitTest, CPoint point)
{
	if (nHitTest == HTCAPTION)
	{
		int nHit = GetSysButtonsHitTest(point);

		if (nHit > 0)
		{
			SetCapture();
			m_nButtonDown = nHit;
			RedrawWindow(0, 0, RDW_FRAME|RDW_INVALIDATE );
		}
	}


	CPropertySheet::OnNcLButtonDown(nHitTest, point);
}

void CXTMainPropertySheet::OnNcLButtonUp(UINT nHitTest, CPoint point)
{

	CPropertySheet::OnNcLButtonUp(nHitTest, point);
}

void CXTMainPropertySheet::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (m_nButtonDown > 0)
	{
		int nButtonDown = m_nButtonDown;

		m_nButtonDown = 0;
		RedrawWindow(0, 0, RDW_FRAME|RDW_INVALIDATE );
		ReleaseCapture();

		ClientToScreen(&point);

		if (GetSysButtonsHitTest(point) == nButtonDown)
		{
			switch (nButtonDown)
			{
				case XDL_HTCLOSE: SendMessage(WM_SYSCOMMAND, SC_CLOSE); break;
				case XDL_HTMAXIMIZE:
					SendMessage(WM_SYSCOMMAND, (GetStyle() & WS_MAXIMIZE) != 0? SC_RESTORE: SC_MAXIMIZE ); break;
				case XDL_HTMINIMIZE: SendMessage(WM_SYSCOMMAND, SC_MINIMIZE); break;
			}
		}
		return;

	}

	CPropertySheet::OnLButtonUp(nFlags, point);
}

void CXTMainPropertySheet::OnCaptureChanged(CWnd *pWnd)
{
	if (m_nButtonDown > 0)
	{
		m_nButtonDown = 0;
		RedrawWindow(0, 0, RDW_FRAME|RDW_INVALIDATE );
	}

	CPropertySheet::OnCaptureChanged(pWnd);
}

BOOL CXTMainPropertySheet::OnEraseBkgnd(CDC* pDC) 
{
	CRect rc;
	GetClientRect(&rc);
	pDC->FillSolidRect(&rc, RGB(221, 221, 221));
	return TRUE;
}
HBRUSH CXTMainPropertySheet::OnCtlColor(CDC *pDC, CWnd *pWnd, UINT nCtlColor)
{
	if(CTLCOLOR_STATIC == nCtlColor)
	{
		CRect rc;
		pWnd->GetClientRect(&rc);
		pDC->FillSolidRect(&rc, RGB(221, 221, 221));
		return (HBRUSH)m_EraseBkgndBrush.m_hObject;
	}
	return CPropertySheet::OnCtlColor(pDC, pWnd, nCtlColor);
}
//////////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNCREATE(CXTMainPropertyPage, CPropertyPage)
CXTMainPropertyPage::CXTMainPropertyPage():CXTResize(this, 0)
{
	m_EraseBkgndBrush.CreateSolidBrush(RGB(221, 221, 221));	
}
CXTMainPropertyPage::CXTMainPropertyPage(UINT nIDTemplate, UINT nIDCaption /* = 0 */):
CPropertyPage(nIDTemplate, nIDCaption),
CXTResize(this, 0)
{
	m_EraseBkgndBrush.CreateSolidBrush(RGB(221, 221, 221));
	
}
BEGIN_MESSAGE_MAP(CXTMainPropertyPage, CPropertyPage)
	//{{AFX_MSG_MAP(CXTMainDlg)
	ON_WM_SIZE()
	ON_WM_GETMINMAXINFO()
	ON_WM_DESTROY()
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CXTMainPropertyPage::OnEraseBkgnd(CDC* pDC) 
{
	CRect rc;
	GetClientRect(&rc);
	pDC->FillSolidRect(&rc, RGB(221, 221, 221));
	return TRUE;
}
HBRUSH CXTMainPropertyPage::OnCtlColor(CDC *pDC, CWnd *pWnd, UINT nCtlColor)
{
	if(CTLCOLOR_STATIC == nCtlColor)
	{
		CRect rc;
		pWnd->GetClientRect(&rc);
		pDC->FillSolidRect(&rc, RGB(221, 221, 221));
		return (HBRUSH)m_EraseBkgndBrush.m_hObject;
	}
	return  CPropertyPage::OnCtlColor(pDC, pWnd, nCtlColor);
}
BOOL CXTMainPropertyPage::OnInitDialog()
{
	// Only show the resize grip if the frame is a resizing frame
	DWORD dwStyle = ::GetWindowLong(m_hWnd, GWL_STYLE);
	if ((dwStyle & WS_THICKFRAME) == 0) {
		SetFlag(xtResizeNoSizeIcon);
	}
	
	CPropertyPage::OnInitDialog();
	CXTResize::Init();

	XTThemeManager()->SetTheme(xtThemeOffice2003);
	if (XTThemeManager()->GetTheme() == xtThemeOfficeXP ||
		XTThemeManager()->GetTheme() == xtThemeOffice2003)
	{
		((CXTButtonThemeOfficeXP*)CXTButton::GetDefaultTheme())->UseWordTheme(TRUE);
	}	
	return TRUE;
}
void CXTMainPropertyPage::OnGetMinMaxInfo(MINMAXINFO* pMMI)
{
	CXTResize::GetMinMaxInfo(pMMI);
}

void CXTMainPropertyPage::OnSize(UINT nType, int cx, int cy)
{
	CPropertyPage::OnSize(nType, cx, cy);
	CXTResize::Size();
}

void CXTMainPropertyPage::OnDestroy()
{
	// Save window placement if AutoLoadPlacement was used.
	if (!m_strSection.IsEmpty()) {
		SavePlacement(m_strSection);
	}
	
	CPropertyPage::OnDestroy();
}
//////////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNCREATE(CXTMainFormView, CFormView)
CXTMainFormView::CXTMainFormView():
CFormView((UINT)0),
CXTResize(this, 0)
{
	m_bInitialized = FALSE;
	m_EraseBkgndBrush.CreateSolidBrush(RGB(221, 221, 221));
	
}
CXTMainFormView::CXTMainFormView(UINT nIDTemplate):
CFormView(nIDTemplate),
CXTResize(this, 0)
{
	m_EraseBkgndBrush.CreateSolidBrush(RGB(221, 221, 221));
	
}
BEGIN_MESSAGE_MAP(CXTMainFormView, CFormView)
//{{AFX_MSG_MAP(CXTMainDlg)
ON_WM_SIZE()
ON_WM_GETMINMAXINFO()
ON_WM_DESTROY()
ON_WM_ERASEBKGND()
ON_WM_CTLCOLOR()
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CXTMainFormView::OnEraseBkgnd(CDC* pDC) 
{
	CRect rc;
	GetClientRect(&rc);
	pDC->FillSolidRect(&rc, RGB(221, 221, 221));
	return TRUE;
	return CFormView::OnEraseBkgnd(pDC);
}
HBRUSH CXTMainFormView::OnCtlColor(CDC *pDC, CWnd *pWnd, UINT nCtlColor)
{
	if(CTLCOLOR_STATIC == nCtlColor)
	{
		static char szWndClass[128] = "";	
		::GetClassName(pWnd->GetSafeHwnd(), szWndClass, 127);

		CString strClassName(szWndClass);
		if(strClassName != "msctls_trackbar32")
		{
			CRect rc;
			pWnd->GetClientRect(&rc);
			pDC->FillSolidRect(&rc, RGB(221, 221, 221));

			if(strClassName ==  "Button" )
			{
				DWORD dwStyle = GetWindowLong(pWnd->GetSafeHwnd(), GWL_STYLE);
				int nType = (dwStyle & 0x0f); 
				
				switch (nType)
				{
				case BS_PUSHBUTTON:       
				case BS_DEFPUSHBUTTON: 
					break;
					
				case BS_CHECKBOX:         
				case BS_AUTOCHECKBOX:     
				case BS_3STATE:           
				case BS_AUTO3STATE:       
					{
						CString strText;
						pWnd->GetWindowText(strText);
						CFont *pFont = this->GetFont();
						CFont *pOldFont = pDC->SelectObject(pFont);
						CRect rcBtn(rc);
						rcBtn.left += 18;
						rcBtn.top  += 1;
						pDC->DrawText(strText, &rcBtn, DT_LEFT);
						pDC->SelectObject(pOldFont);
					}
					break;
				case BS_RADIOBUTTON:      
				case BS_AUTORADIOBUTTON:  
					break;
					
				case BS_GROUPBOX:     
					break;
					
				case BS_OWNERDRAW:        
				case BS_USERBUTTON: 
					break;
					
				default:
					break;
				}
				
			}
		}
		return (HBRUSH)m_EraseBkgndBrush.m_hObject;
	}
	return  CFormView::OnCtlColor(pDC, pWnd, nCtlColor);
}
void CXTMainFormView::OnInitialUpdate()
{
	// Only show the resize grip if the frame is a resizing frame
	DWORD dwStyle = ::GetWindowLong(m_hWnd, GWL_STYLE);
	if ((dwStyle & WS_THICKFRAME) == 0) {
		SetFlag(xtResizeNoSizeIcon);
	}
	
	CFormView::OnInitialUpdate();
	CXTResize::Init();
	
	ModifyStyle(WS_BORDER, 0);
	
	XTThemeManager()->SetTheme(xtThemeOffice2003);
	if (XTThemeManager()->GetTheme() == xtThemeOfficeXP ||
		XTThemeManager()->GetTheme() == xtThemeOffice2003)
	{
		((CXTButtonThemeOfficeXP*)CXTButton::GetDefaultTheme())->UseWordTheme(TRUE);
	}
	m_bInitialized = TRUE;
}
void CXTMainFormView::OnGetMinMaxInfo(MINMAXINFO* pMMI)
{
	CXTResize::GetMinMaxInfo(pMMI);
}

void CXTMainFormView::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);
	CXTResize::Size();
}

void CXTMainFormView::OnDestroy()
{
	// Save window placement if AutoLoadPlacement was used.
	if (!m_strSection.IsEmpty()) {
		SavePlacement(m_strSection);
	}
	
	CFormView::OnDestroy();
}

BOOL CXTMainFrm::OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct) 
{
	// TODO: Add your message handler code here and/or call default
	
	return CFrameWnd::OnCopyData(pWnd, pCopyDataStruct);
}
