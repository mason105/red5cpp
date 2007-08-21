// LogFormView.cpp : implementation file
//

#include "stdafx.h"
#include "XDigitalLifeServerApp.h"
#include "LogFormView.h"
#include "mainfrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLogFormView
/* Message types */
/** standard messages */
#define XMP_MSG_INFO  0
/** error messages */
#define XMP_MSG_ERR   1
/** warning messages */
#define XMP_MSG_WARN  2
/** debug messages */
#define XMP_MSG_DBG   3


IMPLEMENT_DYNCREATE(CLogFormView, CXTMainFormView)

CLogFormView::CLogFormView()
	: CXTMainFormView(CLogFormView::IDD)
{
	//{{AFX_DATA_INIT(CLogFormView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_pSetting = NULL;
	m_pRichEditView = NULL;
	m_bInitialized = FALSE;
	m_bActive		= FALSE;
}

CLogFormView::~CLogFormView()
{
}

void CLogFormView::DoDataExchange(CDataExchange* pDX)
{
	CXTMainFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLogFormView)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLogFormView, CXTMainFormView)
	//{{AFX_MSG_MAP(CLogFormView)
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_CLEARMSG, OnClearMsg)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLogFormView diagnostics

#ifdef _DEBUG
void CLogFormView::AssertValid() const
{
	CXTMainFormView::AssertValid();
}

void CLogFormView::Dump(CDumpContext& dc) const
{
	CXTMainFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CLogFormView message handlers

void CLogFormView::OnSize(UINT nType, int cx, int cy) 
{
	CXTMainFormView::OnSize(nType, cx, cy);
	SetScaleToFitSize(CSize(cx, cy));
	RecalcLayout();
	
}

void CLogFormView::OnInitialUpdate() 
{
	if(!m_bInitialized)
	{
		CRect rectDummy(0, 0, 0, 0);
		CCreateContext cc;
		ZeroMemory(&cc, sizeof(cc));
		
		m_pRichEditView = (CRichEditView*)RUNTIME_CLASS(CRichEditView)->CreateObject();
		if(m_pRichEditView == NULL  ||
			!((CWnd *)m_pRichEditView)->Create(NULL, NULL, WS_CHILD|WS_VISIBLE|WS_BORDER, 
			rectDummy, this, 0xff, &cc))
			return ;
		m_pRichEditView->GetRichEditCtrl().SetFont(GetFont());
		m_pRichEditView->GetRichEditCtrl().SetReadOnly(TRUE);
		CString strTitle;
#ifdef LANG_CHINESE 
		strTitle = "Çå³ý";
#else
		strTitle = "Clear";
#endif
		m_btnClear.Create(strTitle, 
			WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON, 
			rectDummy, this, IDC_CLEARMSG);
		m_btnClear.ShowWindow(SW_SHOW);
		
			
		m_jpgBackGround.Load(IDR_BACKGROUND);
		
	}
	CXTMainFormView::OnInitialUpdate();
	
	RecalcLayout();
	
}
void CLogFormView::RecalcLayout()
{
	if(m_bInitialized)
	{
		if(m_pRichEditView)
		{
			CXTPClientRect rcClient(this);
			int cx = rcClient.Width();
			int cy = rcClient.Height();
			CRect rc(0, 0, cx, cy);
			rc.DeflateRect(20, 20);
			rc.bottom -= 24;
			m_pRichEditView->MoveWindow(&rc);
			rc.SetRect(cx - 75, cy - 35, cx - 20, cy - 12);
			m_btnClear.MoveWindow(&rc);
		}		
	}
}
void CLogFormView::InitSetting(XDLS_Setting *pSetting)
{
	m_pSetting = pSetting;
}
void CLogFormView::Server_Run()
{
	
}
void CLogFormView::Server_Stop()
{
}
void CLogFormView::OnTimerWork(UINT nID)
{
	if(m_bActive && nID == TIMERID_TWOSECOND)
	{
		CMainFrame *pMainFrm = (CMainFrame*)AfxGetMainWnd();
		
	}
}

void CLogFormView::Wnd_Active(BOOL bActive)
{
	m_bActive = bActive;	
}
void CLogFormView::OnClearMsg()
{
	if(m_pRichEditView)
	{
		int iTotalTextLength = m_pRichEditView->GetRichEditCtrl().GetWindowTextLength();
		m_pRichEditView->GetRichEditCtrl().SetSel(0, iTotalTextLength);
		m_pRichEditView->GetRichEditCtrl().ReplaceSel((LPCTSTR)"");
	}
}
HRESULT STDMETHODCALLTYPE CLogFormView::OnUpdateMsg(BSTR psz_module, int i_type, BSTR psz_msg)
{
	USES_CONVERSION;
	// Formating the string that will be changed
	CHARFORMAT cf;
	cf.cbSize		= sizeof (CHARFORMAT);  
	cf.dwMask		= CFM_COLOR | CFM_UNDERLINE | CFM_BOLD;
	cf.dwEffects	= (unsigned long)~(CFE_AUTOCOLOR | CFE_UNDERLINE | CFE_BOLD);
	cf.dwEffects   |= CFE_BOLD;
	cf.crTextColor	= RGB(0, 0, 0); 
			 
	CString strMsg;
	strMsg.Format("%s", W2A(psz_module));
	switch( i_type )
	{
	case XMP_MSG_INFO:
		strMsg += (": ");
		break;
	case XMP_MSG_ERR:
		strMsg += (" error: ");
		cf.crTextColor	= RGB(200, 0, 0); 
		break;
	case XMP_MSG_WARN:
		strMsg += (" warning: ");
		cf.crTextColor	= RGB(0, 100, 0); 
		break;
	case XMP_MSG_DBG:
	default:
		strMsg += (" debug: ");
		break;
	}
	strMsg +=  W2A(psz_msg);
	strMsg +=  "\n";
	
	int iTotalTextLength = m_pRichEditView->GetRichEditCtrl().GetWindowTextLength();
	m_pRichEditView->GetRichEditCtrl().SetSel(iTotalTextLength, iTotalTextLength);
	
	CHARFORMAT cfSel;
	m_pRichEditView->GetRichEditCtrl().GetSelectionCharFormat(cfSel);
	m_pRichEditView->GetRichEditCtrl().ReplaceSel((LPCTSTR)strMsg);
	int iStartPos = iTotalTextLength;
	
	
	int iEndPos = m_pRichEditView->GetRichEditCtrl().GetWindowTextLength();
	m_pRichEditView->GetRichEditCtrl().SetSel(iStartPos, iEndPos);
	m_pRichEditView->GetRichEditCtrl().SetSelectionCharFormat(cf); 
	m_pRichEditView->GetRichEditCtrl().HideSelection(TRUE, FALSE);
	m_pRichEditView->GetRichEditCtrl().SetSel(m_pRichEditView->GetWindowTextLength(),m_pRichEditView->GetWindowTextLength());
	m_pRichEditView->GetRichEditCtrl().SetSelectionCharFormat(cfSel);
	m_pRichEditView->GetRichEditCtrl().HideSelection(TRUE, FALSE);
	
	return S_OK;
}
void CLogFormView::OnDrawInfo(CDC *pDC)
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
}

void CLogFormView::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	OnDrawInfo(&dc);
	
	// Do not call CXTMainFormView::OnPaint() for painting messages
}

void CLogFormView::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	
	CXTMainFormView::OnTimer(nIDEvent);
}
