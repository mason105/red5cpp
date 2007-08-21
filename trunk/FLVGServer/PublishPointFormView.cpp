// PublishPointFormView.cpp : implementation file
//

#include "stdafx.h"
#include "XDigitalLifeServerApp.h"
#include "PublishPointFormView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPublishPointFormView

IMPLEMENT_DYNCREATE(CPublishPointFormView, CXTMainFormView)

CPublishPointFormView::CPublishPointFormView()
	: CXTMainFormView(CPublishPointFormView::IDD)
{
	//{{AFX_DATA_INIT(CPublishPointFormView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_pSetting = NULL;
	m_bInitialized = FALSE;
	m_wideFont.CreateFont(Frame_Height,                        // nHeight
		0,                         // nWidth
		0,                         // nEscapement
		0,                         // nOrientation
		700,                 // nWeight
		FALSE,                     // bItalic
		FALSE,                     // bUnderline
		0,                         // cStrikeOut
		ANSI_CHARSET,              // nCharSet
		OUT_DEFAULT_PRECIS,        // nOutPrecision
		CLIP_DEFAULT_PRECIS,       // nClipPrecision
		DEFAULT_QUALITY,           // nQuality
		DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
		_T("Arial"));
	m_thinFont.CreateFont(Frame_Height - 2,                        // nHeight
		0,                         // nWidth
		0,                         // nEscapement
		0,                         // nOrientation
		FW_NORMAL,                 // nWeight
		FALSE,                     // bItalic
		FALSE,                     // bUnderline
		0,                         // cStrikeOut
		ANSI_CHARSET,              // nCharSet
		OUT_DEFAULT_PRECIS,        // nOutPrecision
		CLIP_DEFAULT_PRECIS,       // nClipPrecision
		DEFAULT_QUALITY,           // nQuality
		DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
		_T("Arial"));
	
}

CPublishPointFormView::~CPublishPointFormView()
{
}

void CPublishPointFormView::DoDataExchange(CDataExchange* pDX)
{
	CXTMainFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPublishPointFormView)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPublishPointFormView, CXTMainFormView)
	//{{AFX_MSG_MAP(CPublishPointFormView)
	ON_WM_SIZE()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPublishPointFormView diagnostics

#ifdef _DEBUG
void CPublishPointFormView::AssertValid() const
{
	CXTMainFormView::AssertValid();
}

void CPublishPointFormView::Dump(CDumpContext& dc) const
{
	CXTMainFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPublishPointFormView message handlers

void CPublishPointFormView::OnInitialUpdate() 
{
	if(!m_bInitialized)
	{		
		m_jpgBackGround.Load(IDR_BACKGROUND);
	}
	CXTMainFormView::OnInitialUpdate();
	
	RecalcLayout();
	
}

void CPublishPointFormView::OnSize(UINT nType, int cx, int cy) 
{
	CXTMainFormView::OnSize(nType, cx, cy);
	SetScaleToFitSize(CSize(cx, cy));
	
	RecalcLayout();
	
}
void CPublishPointFormView::RecalcLayout()
{
	if(m_bInitialized)
	{
		
	}
}
void CPublishPointFormView::InitSetting(XDLS_Setting *pSetting)
{
	m_pSetting = pSetting;
}
void CPublishPointFormView::Server_Run()
{
	
}
void CPublishPointFormView::Server_Stop()
{
}
void CPublishPointFormView::OnTimerWork(UINT nID)
{
	if(nID == TIMERID_TWOSECOND)
	{
		CClientDC dc(this);
		OnDrawInfo(&dc);
	}
}

void CPublishPointFormView::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	OnDrawInfo(&dc);
	
	// Do not call CXTMainFormView::OnPaint() for painting messages
}
void CPublishPointFormView::OnDrawInfo(CDC *pDC)
{
	CRect rc;
	CXTPClientRect rcClient(this);
	CXTPBufferDC dc(pDC->GetSafeHdc(), rcClient);
	if(m_jpgBackGround.IsLoad())
	{
		CSize sz = m_jpgBackGround.GetImageSize(&dc);
		int row = rcClient.Width() / sz.cx + 1;
		int col = rcClient.Height()/ sz.cy + 1;
		for(int r = 0; r < row; r ++)
		{
			for(int c = 0; c < col; c ++)
			{
				rc.SetRect(r * sz.cx, c * sz.cy,
					(r + 1) * sz.cx, (c + 1) * sz.cy);
				m_jpgBackGround.Render(&dc, rc);
			}
		}
	}
	
	CFont *pOldFont = dc.SelectObject(&m_wideFont);
	int oldBkMode = dc.SetBkMode(TRANSPARENT);
	
	
	dc.SetBkMode(oldBkMode);
	dc.SelectObject(pOldFont);
}
void CPublishPointFormView::Wnd_Active(BOOL bActive)
{
	
}