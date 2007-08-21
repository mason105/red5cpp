// XDLTheme.cpp: implementation of the CXDLTheme class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "XDigitalLifeServerApp.h"
#include "XDLTheme.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CXDLTheme::CXDLTheme()
{

}

CXDLTheme::~CXDLTheme()
{

}

void CXDLTheme::FillStatusBar(CDC* pDC, CXTPStatusBar* pBar)
{
	pDC->FillSolidRect(CXTPClientRect(pBar), XDLCOLOR_3DFACE);
}

void CXDLTheme::FillDockBar(CDC* pDC, CXTPDockBar* pBar)
{
	pDC->FillSolidRect(CXTPClientRect(pBar), XDLCOLOR_3DFACE);
}

void CXDLTheme::DrawStatusBarGripper(CDC* pDC, CRect rcClient)
{
	int i;

	CXTPPenDC penBorder(*pDC, XDLCOLOR_3DSHADOW);
	for (i = 0; i < 4; i++ ) Line(pDC, CPoint(rcClient.Width() - 4 - i * 4, rcClient.Height() - 2),
		CPoint(rcClient.Width() - 1, rcClient.Height() - 5 - i * 4));

	CXTPPenDC penBorderWhite(*pDC, XDLCOLOR_BTNHIGHLIGHT);
	for (i = 0; i < 4; i++ )
		Line(pDC, CPoint(rcClient.Width() - 5 -i * 4, rcClient.Height() - 2), CPoint(rcClient.Width() - 1 , rcClient.Height() - 4 - i * 4 - 2));
}

void CXDLTheme::DrawStatusBarPane(CDC* pDC, CRect& rc, DWORD dwStyle, CString str)
{
	if (!(dwStyle & SBPS_DISABLED))
	{
		rc.DeflateRect(2, 1);
		pDC->SetBkMode(TRANSPARENT);
		pDC->DrawText(str, rc, DT_SINGLELINE | DT_VCENTER) ;
	}
}

void CXDLTheme::FillCommandBarEntry(CDC* pDC, CXTPCommandBar* pBar)
{
	CRect rc;
	pBar->GetClientRect(&rc);
	pDC->FillSolidRect(rc, XDLCOLOR_3DFACE);

	if (pBar->GetPosition() == xtpBarFloating || pBar->GetPosition() == xtpBarPopup)
	{
		Draw3dRect(pDC, rc, XDLCOLOR_3DSHADOW, XDLCOLOR_3DSHADOW);
		rc.DeflateRect(1, 1);
		Draw3dRect(pDC, rc, XDLCOLOR_BTNHIGHLIGHT, RGB(206, 206, 206));
	}
	else
	{
		Draw3dRect(pDC, rc, RGB(245, 245, 245), RGB(196, 196, 196));
	}

}
#define max(a,b)    (((a) > (b)) ? (a) : (b))
#define min(a,b)    (((a) < (b)) ? (a) : (b))

CSize CXDLTheme::DrawCommandBarGripper(CDC* pDC, CXTPCommandBar* pBar, BOOL bDraw)
{
	CRect rc;
	pBar->GetClientRect(&rc);

	CXTPPenDC pen(*pDC, 0);

	if (pBar->GetPosition() == xtpBarFloating)
	{
		ASSERT(pDC);
		CXTPFontDC font(pDC, &m_fontSmCaption);
		CSize sz = pDC->GetTextExtent(_T(" "));

		rc.SetRect(3, 3, rc.right - 3, 3 + max(15, sz.cy));
		if (pDC && bDraw)
		{
			pDC->FillSolidRect(rc, RGB(68, 100, 172));
			pDC->SetTextColor(GetXtremeColor(COLOR_3DHIGHLIGHT));
			pDC->DrawText(pBar->GetTitle(), CRect(5, 3, rc.right - 2* rc.Size().cy, rc.bottom), DT_SINGLELINE | DT_VCENTER );
		}
		return rc.Size();

	}
	else if (pBar->GetPosition() == xtpBarRight || pBar->GetPosition() == xtpBarLeft)
	{
		if (pDC && bDraw)
		{
			for (int i = 4; i < rc.right - 4; i += 5)
			{
				//pen.Color(clrGripper[i % 2]); pDC->MoveTo(i, 3); pDC->LineTo(i, 8);

				pen.Color(XDLCOLOR_3DSHADOW); pDC->MoveTo(i, 7); pDC->LineTo(i + 4, 3);
				pen.Color(XDLCOLOR_BTNHIGHLIGHT); pDC->MoveTo(i, 8); pDC->LineTo(i + 4, 4);

			}
		}
		return CSize(0, 8);
	}
	else if (pBar->GetPosition() == xtpBarTop || pBar->GetPosition() == xtpBarBottom)
	{
		if (pDC && bDraw)
		{
			for (int i = 8; i < rc.bottom - 4; i += 5)
			{
				pen.Color(XDLCOLOR_BTNHIGHLIGHT); pDC->MoveTo(3, i); pDC->LineTo(7, i - 4);
				pen.Color(XDLCOLOR_3DSHADOW); pDC->MoveTo(3, i-1); pDC->LineTo(7, i - 5);
			}
		}
		return CSize(8, 0);
	}
	return 0;

}


CSize CXDLTheme::DrawCommandBarSeparator(CDC* pDC, CXTPCommandBar* pBar, CXTPControl* pControl, BOOL bDraw)
{
	if (!bDraw)
	{
		ASSERT(pBar->GetType() == xtpBarTypePopup);
		return CSize(0, 8);
	}


	CRect rc;
	pBar->GetClientRect(&rc);
	CRect rcControl = pControl->GetRect();
	CRect rcRaw = pControl->GetRawRect();

	if (pBar->GetType() == xtpBarTypePopup)
	{
		Draw3dRect(pDC, CRect(14, rcControl.top - 2 - 2 -1, rc.right - 14, rcControl.top - 0 - 2 -  1), RGB(206, 206, 206), XDLCOLOR_BTNHIGHLIGHT);
	}
	else if (pBar->GetPosition() != xtpBarPopup && IsVerticalPosition(pBar->GetPosition()))
	{
		if (!pControl->GetWrap())
			pDC->FillSolidRect(rcRaw.left + 4, rcControl.top - 4, rcRaw.Width() - 8, 1, RGB(161, 161, 161));
		else
			pDC->FillSolidRect(rcRaw.right + 2, rcRaw.top + 4, 1,  rcRaw.Height() - 8, RGB(161, 161, 161));
	} else
	{
		if (!pControl->GetWrap())
			pDC->FillSolidRect(rcControl.left - 4, rcRaw.top + 4, 1, rcRaw.Height() - 8, RGB(161, 161, 161));
		else
			pDC->FillSolidRect(rcRaw.left + 4, rcRaw.top - 4, rcRaw.Width() - 8, 1, RGB(161, 161, 161));
	}
	return 0;
}

void CXDLTheme::DrawRectangle(CDC* pDC, CRect rc, BOOL bSelected, BOOL bPressed, BOOL bEnabled, BOOL bChecked, BOOL bPopuped, BOOL /*bToolBar*/, XTPBarPosition /*barPosition = xtpBarPopup*/)
{
	if ((bSelected || bPressed || bPopuped) && bEnabled)
		pDC->FillSolidRect(rc, RGB(221, 221, 221));

	if (!bEnabled)
	{
		if ( bSelected == TRUE_KEYBOARD) Draw3dRect(pDC, rc, COLOR_3DSHADOW, COLOR_BTNHILIGHT);
	}
	else if (bChecked && !bSelected && !bPressed)
	{
		Draw3dRect(pDC, rc, XDLCOLOR_3DSHADOW, XDLCOLOR_BTNHIGHLIGHT);
	}
	else if (bChecked ||bPopuped || bPressed == TRUE_KEYBOARD || (bSelected && bPressed))
	{
		//Draw3dRect(pDC, rc, COLOR_3DSHADOW, COLOR_BTNHILIGHT);
		pDC->FillSolidRect(rc, RGB(204, 204, 204));
		pDC->Draw3dRect(rc, RGB(92, 92, 92), RGB(92, 92, 92));

		rc.DeflateRect(1, 1);
		pDC->Draw3dRect(rc, RGB(204, 204, 204), XDLCOLOR_BTNHIGHLIGHT);
	}
	else if (bSelected || bPressed)
	{
		pDC->FillSolidRect(rc, RGB(245, 245, 245));
		pDC->Draw3dRect(rc, RGB(92, 92, 92), RGB(92, 92, 92));
		rc.DeflateRect(1, 1);
		pDC->Draw3dRect(rc, XDLCOLOR_BTNHIGHLIGHT, RGB(206, 206, 206));
	}
}

void CXDLTheme::AdjustExcludeRect(CRect& /*rc*/, CXTPControl* /*pControl*/)
{
}
//////////////////////////////////////////////////////////////////////////
CXDLDockingTheme::CXDLDockingTheme()
{
}
CXDLDockingTheme::~CXDLDockingTheme()
{
}
void CXDLDockingTheme::DrawPane(CDC& dc, CXTPDockingPaneTabbedContainer* pPane, CRect rc)
{
	CXTPDockingPaneOffice2003Theme::DrawPane(dc, pPane, rc);
}
void CXDLDockingTheme::DrawCaption(CDC& dc, CXTPDockingPaneTabbedContainer* pPane, CRect rc)
{
	int nTitleHeight = m_nTitleHeight;
	CRect rcCaption(rc);
	rcCaption.DeflateRect(0, m_rcCaptionMargin.top, 0, rc.Height() - nTitleHeight - 1);
	dc.FillSolidRect(rc.left, rc.top, rc.Width(), rcCaption.bottom + 2, RGB(221, 221, 221));
	
	CString strTitle = pPane->GetSelected()? pPane->GetSelected()->GetTitle(): _T("");
	BOOL bActive = m_bHighlighActiveCaption && pPane->IsActive();
	DrawCaptionPart(dc, pPane, rcCaption, strTitle, bActive);
	
}
void CXDLDockingTheme::DrawCaptionPart(CDC& dc, CXTPDockingPaneBase* pPane, CRect rcCaption, CString strTitle, BOOL bActive)
{
	COLORREF clrButton = GetXtremeColor(bActive? COLOR_HIGHLIGHTTEXT: COLOR_BTNTEXT), clrText;
	{	
		if (bActive)
		{
			dc.FillSolidRect(rcCaption,  RGB(206, 206, 206));
		} 
		{
			CXTPPenDC pen(dc, GetXtremeColor(XPCOLOR_3DSHADOW));
			dc.MoveTo(rcCaption.left + 1, rcCaption.top); dc.LineTo(rcCaption.right - 1 , rcCaption.top);
			dc.MoveTo(rcCaption.left, rcCaption.top + 1); dc.LineTo(rcCaption.left, rcCaption.bottom - 1);
			dc.MoveTo(rcCaption.left + 1, rcCaption.bottom - 1); dc.LineTo(rcCaption.right - 1 ,rcCaption.bottom - 1);
			dc.MoveTo(rcCaption.right -1 , rcCaption.top + 1 ); dc.LineTo(rcCaption.right - 1, rcCaption.bottom - 1);
	
			{
				CRect rc(rcCaption);
				CXTPPenDC pen(dc, 0);
				for (int i = 8; i < rc.bottom - 2; i += 5)
				{
					pen.Color(XDLCOLOR_BTNHIGHLIGHT); dc.MoveTo(3, i); dc.LineTo(7, i - 4);
					pen.Color(XDLCOLOR_3DSHADOW); dc.MoveTo(3, i-1); dc.LineTo(7, i - 5);
				}	
			}
		}
		clrText = GetXtremeColor(bActive? COLOR_HIGHLIGHTTEXT: COLOR_BTNTEXT);		
	}
	
	rcCaption.right -= 2;
	DrawCaptionButtons(&dc, pPane->GetCaptionButtons(), rcCaption, clrButton, 14, 2);
	
	// Title text
	if (!strTitle.IsEmpty())
	{
		CRect rcText(rcCaption.left + 12, rcCaption.top + 1, rcCaption.right, rcCaption.bottom);
		
		dc.SetTextColor(clrText);
		CXTPFontDC font(&dc, &m_fntTitle);
		dc.DrawText(strTitle, rcText, DT_SINGLELINE|DT_END_ELLIPSIS|DT_VCENTER | DT_NOPREFIX);
	}


}
void CXDLDockingTheme::DrawSplitter(CDC& dc, CXTPDockingPaneSplitterWnd* pSplitter)
{
	CRect rc;
	if(pSplitter)
	{
		pSplitter->GetClientRect(rc);
		dc.FillSolidRect(rc,  RGB(128, 128, 128));	
	}
}
