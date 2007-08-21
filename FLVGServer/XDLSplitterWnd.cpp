// XDLSplitterWnd.cpp: implementation of the CXDLSplitterWnd class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "XDigitalLifeServerApp.h"
#include "XDLSplitterWnd.h"
#include "c:\Program Files\Microsoft Visual Studio .NET 2003\Vc7\atlmfc\src\mfc\afximpl.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
AFX_STATIC void AFXAPI _HxyLayoutRowCol(CSplitterWnd::CRowColInfo* pInfoArray,
										int nMax, int nSize, int nSizeSplitter)
{
	ASSERT(pInfoArray != NULL);
	ASSERT(nMax > 0);
	ASSERT(nSizeSplitter > 0);
	
	CSplitterWnd::CRowColInfo* pInfo;
	int i;
	
	if (nSize < 0)
		nSize = 0;  // if really too small, layout as zero size
	
	// start with ideal sizes
	for (i = 0, pInfo = pInfoArray; i < nMax-1; i++, pInfo++)
	{
		if (pInfo->nIdealSize < pInfo->nMinSize)
			pInfo->nIdealSize = 0;      // too small to see
		pInfo->nCurSize = pInfo->nIdealSize;
	}
	pInfo->nCurSize = INT_MAX;  // last row/column takes the rest
	
	for (i = 0, pInfo = pInfoArray; i < nMax; i++, pInfo++)
	{
		ASSERT(nSize >= 0);
		if (nSize == 0)
		{
			// no more room (set pane to be invisible)
			pInfo->nCurSize = 0;
			continue;       // don't worry about splitters
		}
		else if (nSize < pInfo->nMinSize && i != 0)
		{
			// additional panes below the recommended minimum size
			//   aren't shown and the size goes to the previous pane
			pInfo->nCurSize = 0;
			
			// previous pane already has room for splitter + border
			//   add remaining size and remove the extra border
			ASSERT(afxData.cxBorder2 == afxData.cyBorder2);
			(pInfo-1)->nCurSize += nSize + afxData.cxBorder2;
			nSize = 0;
		}
		else
		{
			// otherwise we can add the second pane
			ASSERT(nSize > 0);
			if (pInfo->nCurSize == 0)
			{
				// too small to see
				if (i != 0)
					pInfo->nCurSize = 0;
			}
			else if (nSize < pInfo->nCurSize)
			{
				// this row/col won't fit completely - make as small as possible
				pInfo->nCurSize = nSize;
				nSize = 0;
			}
			else
			{
				// can fit everything
				nSize -= pInfo->nCurSize;
			}
		}
		
		// see if we should add a splitter
		ASSERT(nSize >= 0);
		if (i != nMax - 1)
		{
			// should have a splitter
			if (nSize > nSizeSplitter)
			{
				nSize -= nSizeSplitter; // leave room for splitter + border
				ASSERT(nSize > 0);
			}
			else
			{
				// not enough room - add left over less splitter size
				ASSERT(afxData.cxBorder2 == afxData.cyBorder2);
				pInfo->nCurSize += nSize;
				if (pInfo->nCurSize > (nSizeSplitter - afxData.cxBorder2))
					pInfo->nCurSize -= (nSizeSplitter - afxData.cyBorder2);
				nSize = 0;
			}
		}
	}
	ASSERT(nSize == 0); // all space should be allocated
}
AFX_STATIC void AFXAPI _HxyDeferClientPos(AFX_SIZEPARENTPARAMS* lpLayout,
										  CWnd* pWnd, int x, int y, int cx, int cy, BOOL bScrollBar)
{
	ASSERT(pWnd != NULL);
	ASSERT(pWnd->m_hWnd != NULL);
	
	if (bScrollBar)
	{
		// if there is enough room, draw scroll bar without border
		// if there is not enough room, set the WS_BORDER bit so that
		//   we will at least get a proper border drawn
		BOOL bNeedBorder = (cx <= CX_BORDER || cy <= CY_BORDER);
		pWnd->ModifyStyle(bNeedBorder ? 0 : WS_BORDER,
			bNeedBorder ? WS_BORDER : 0);
	}
	CRect rect(x, y, x+cx, y+cy);
	
	// adjust for border size (even if zero client size)
	if (!afxData.bWin95)
	{
		if (bScrollBar)
			rect.InflateRect(CX_BORDER, CY_BORDER);
		else
			pWnd->CalcWindowRect(&rect);
	}
	
	// adjust for 3d border (splitter windows have implied border)
	if ((pWnd->GetExStyle() & WS_EX_CLIENTEDGE) ||
		pWnd->IsKindOf(RUNTIME_CLASS(CSplitterWnd)))
		rect.InflateRect(afxData.cxBorder2, afxData.cyBorder2);
	
	// first check if the new rectangle is the same as the current
	CRect rectOld;
	pWnd->GetWindowRect(rectOld);
	pWnd->GetParent()->ScreenToClient(&rectOld);
	if (rect != rectOld)
		AfxRepositionWindow(lpLayout, pWnd->m_hWnd, rect);
}
CXDLSplitterWnd::CXDLSplitterWnd()
{
	m_cyBorder = m_cxBorder = 0;
	m_cxSplitter = m_cySplitter = 4;
	m_cySplitterGap = m_cxSplitterGap = 4;
	
}

CXDLSplitterWnd::~CXDLSplitterWnd()
{

}

void CXDLSplitterWnd::StartTracking(int ht)
{
	CXTSplitterWnd::StartTracking(ht);
}
void CXDLSplitterWnd::RecalcLayout()
{

	ASSERT_VALID(this);
	ASSERT(m_nRows > 0 && m_nCols > 0); // must have at least one pane

	CRect rectClient;
	GetClientRect(rectClient);
	rectClient.InflateRect(-m_cxBorder, -m_cyBorder);

	CRect rectInside;
	GetInsideRect(rectInside);

	// layout columns (restrict to possible sizes)
	_HxyLayoutRowCol(m_pColInfo, m_nCols, rectInside.Width(), m_cxSplitterGap);
	_HxyLayoutRowCol(m_pRowInfo, m_nRows, rectInside.Height(), m_cySplitterGap);

	// adjust the panes (and optionally scroll bars)

	// give the hint for the maximum number of HWNDs
	AFX_SIZEPARENTPARAMS layout;
	layout.hDWP = ::BeginDeferWindowPos((m_nCols + 1) * (m_nRows + 1) + 1);

	// size of scrollbars
	int cx = (rectClient.right - rectInside.right) - afxData.bWin95;
	int cy = (rectClient.bottom - rectInside.bottom) - afxData.bWin95;

	// reposition size box
	if (m_bHasHScroll && m_bHasVScroll)
	{
		CWnd* pScrollBar = GetDlgItem(AFX_IDW_SIZE_BOX);
		ASSERT(pScrollBar != NULL);

		// fix style if necessary
		BOOL bSizingParent = (GetSizingParent() != NULL);
		// modifyStyle returns TRUE if style changes
		if (pScrollBar->ModifyStyle(SBS_SIZEGRIP|SBS_SIZEBOX,
				bSizingParent ? SBS_SIZEGRIP : SBS_SIZEBOX))
			pScrollBar->Invalidate();
		pScrollBar->EnableWindow(bSizingParent);

		// reposition the size box
		_HxyDeferClientPos(&layout, pScrollBar,
			rectInside.right + afxData.bWin95,
			rectInside.bottom + afxData.bWin95, cx, cy, TRUE);
	}

	// reposition scroll bars
	if (m_bHasHScroll)
	{
		int cxSplitterBox = m_cxSplitter + afxData.bWin95;// split box bigger
		int x = rectClient.left;
		int y = rectInside.bottom + afxData.bWin95;
		for (int col = 0; col < m_nCols; col++)
		{
			CWnd* pScrollBar = GetDlgItem(AFX_IDW_HSCROLL_FIRST + col);
			ASSERT(pScrollBar != NULL);
			int cx = m_pColInfo[col].nCurSize;
			if (col == 0 && m_nCols < m_nMaxCols)
				x += cxSplitterBox, cx -= cxSplitterBox;
			_HxyDeferClientPos(&layout, pScrollBar, x, y, cx, cy, TRUE);
			x += cx + m_cxSplitterGap;
		}
	}

	if (m_bHasVScroll)
	{
		int cySplitterBox = m_cySplitter + afxData.bWin95;// split box bigger
		int x = rectInside.right + afxData.bWin95;
		int y = rectClient.top;
		for (int row = 0; row < m_nRows; row++)
		{
			CWnd* pScrollBar = GetDlgItem(AFX_IDW_VSCROLL_FIRST + row);
			ASSERT(pScrollBar != NULL);
			int cy = m_pRowInfo[row].nCurSize;
			if (row == 0 && m_nRows < m_nMaxRows)
				y += cySplitterBox, cy -= cySplitterBox;
			_HxyDeferClientPos(&layout, pScrollBar, x, y, cx, cy, TRUE);
			y += cy + m_cySplitterGap;
		}
	}

	//BLOCK: Reposition all the panes
	{
		int x = rectClient.left;
		for (int col = 0; col < m_nCols; col++)
		{
			int cx = m_pColInfo[col].nCurSize;
			int y = rectClient.top;
			for (int row = 0; row < m_nRows; row++)
			{
				int cy = m_pRowInfo[row].nCurSize;
				CWnd* pWnd = GetPane(row, col);
				_HxyDeferClientPos(&layout, pWnd, x, y, cx, cy, FALSE);
				y += cy + m_cySplitterGap;
			}
			x += cx + m_cxSplitterGap;
		}
	}

	// move and resize all the windows at once!
	if (layout.hDWP == NULL || !::EndDeferWindowPos(layout.hDWP))
		TRACE0("Warning: DeferWindowPos failed - low system resources.\n");

	// invalidate all the splitter bars (with NULL pDC)
	DrawAllSplitBars(NULL, rectInside.right, rectInside.bottom);

}
void CXDLSplitterWnd::OnDrawSplitter(CDC* pDC, ESplitType nType, const CRect& rectArg)
{
	COLORREF clr3DFace = GetTheme()->m_clrSplitterFace;
	COLORREF clr3DShadow = GetTheme()->m_clrSplitterBorders;
	
	
	// if pDC == NULL, then just invalidate
	if (pDC == NULL)
	{
		RedrawWindow(rectArg, NULL, RDW_INVALIDATE|RDW_NOCHILDREN);
		return;
	}
	ASSERT_VALID(pDC);
	
	// otherwise, actually draw
	CRect rect = rectArg;
	switch (nType)
	{
	case splitBorder:
		if (m_bFlatSplit)
		{
			if (!(m_dwxStyle & XT_SPLIT_NOBORDER))
			{
				pDC->Draw3dRect(rect, clr3DFace, clr3DFace);
				rect.InflateRect(-CX_BORDER, -CY_BORDER);
				pDC->Draw3dRect(rect, clr3DShadow, GetXtremeColor(COLOR_3DHILIGHT));
			} else
			{
				pDC->Draw3dRect(rect, clr3DFace, clr3DFace);
				rect.InflateRect(-CX_BORDER, -CY_BORDER);
				pDC->Draw3dRect(rect, clr3DFace, clr3DFace);
			}
		}
		else
		{
			pDC->Draw3dRect(rect, clr3DShadow, GetXtremeColor(COLOR_3DHILIGHT));
			rect.InflateRect(-CX_BORDER, -CY_BORDER);
			pDC->Draw3dRect(rect, GetXtremeColor(COLOR_WINDOWFRAME), clr3DFace);
		}
		return;
		
	case splitIntersection:
		ASSERT(!XTOSVersionInfo()->IsWin95OrGreater());
		break;
		
	case splitBox:
		if (m_bFlatSplit)
		{
			pDC->Draw3dRect(rect, clr3DFace, clr3DFace);
			rect.InflateRect(-CX_BORDER, -CY_BORDER);
			pDC->Draw3dRect(rect, GetXtremeColor(COLOR_3DHILIGHT), clr3DShadow);
			rect.InflateRect(-CX_BORDER, -CY_BORDER);
		}
		else
		{
			pDC->Draw3dRect(rect, clr3DFace, GetXtremeColor(COLOR_WINDOWFRAME));
			rect.InflateRect(-CX_BORDER, -CY_BORDER);
			pDC->Draw3dRect(rect, GetXtremeColor(COLOR_3DHILIGHT), clr3DShadow);
			rect.InflateRect(-CX_BORDER, -CY_BORDER);
		}
		break;
		
	case splitBar:
		break;
		
	default:
		ASSERT(FALSE);  // unknown splitter type
	}
	
	// fill the middle
	COLORREF clr = RGB(241, 241, 241);
	pDC->FillSolidRect(rect, clr);
}