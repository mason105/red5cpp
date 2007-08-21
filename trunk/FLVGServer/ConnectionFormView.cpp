// ConnectionFormView.cpp : implementation file
//

#include "stdafx.h"
#include "XDigitalLifeServerApp.h"
#include "ConnectionFormView.h"
#include "mainfrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CConnectionFormView
int g_counter;
IMPLEMENT_DYNCREATE(CConnectionFormView, CXTMainFormView)

CConnectionFormView::CConnectionFormView()
	: CXTMainFormView(CConnectionFormView::IDD)
{
	//{{AFX_DATA_INIT(CConnectionFormView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_pSetting = NULL;
	m_bInitialized = FALSE;
	g_counter = 0;
}

CConnectionFormView::~CConnectionFormView()
{
}

void CConnectionFormView::DoDataExchange(CDataExchange* pDX)
{
	CXTMainFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConnectionFormView)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CConnectionFormView, CXTMainFormView)
	//{{AFX_MSG_MAP(CConnectionFormView)
	ON_WM_SIZE()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConnectionFormView diagnostics

#ifdef _DEBUG
void CConnectionFormView::AssertValid() const
{
	CXTMainFormView::AssertValid();
}

void CConnectionFormView::Dump(CDumpContext& dc) const
{
	CXTMainFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CConnectionFormView message handlers

void CConnectionFormView::OnSize(UINT nType, int cx, int cy) 
{
	CXTMainFormView::OnSize(nType, cx, cy);
	SetScaleToFitSize(CSize(cx, cy));
	
	RecalcLayout();
	
}

void CConnectionFormView::OnInitialUpdate() 
{
	if(!m_bInitialized)
	{		
		m_jpgBackGround.Load(IDR_BACKGROUND);

		CRect rc;
		GetClientRect(&rc);
		int cx = rc.Width();
		int cy = rc.Height();
		SetScaleToFitSize(CSize(cx, cy));
		CXTMainFormView::OnInitialUpdate();

		m_wndConnectList.Create(WS_BORDER|WS_CHILD|WS_VISIBLE|LVS_REPORT, CRect(0, 0, 0, 0), this, IDC_LIST_CONNECTION);
		m_wndConnectList.SetExtendedStyle (LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT|LVS_EX_FLATSB);
		
		m_wndConnectList.InsertColumn(0, "Address", LVCFMT_LEFT, 0);
		m_wndConnectList.InsertColumn(1, "Type", LVCFMT_LEFT, 0);
		m_wndConnectList.InsertColumn(2, "Path", LVCFMT_LEFT, 0);
		m_wndConnectList.InsertColumn(3, "Session", LVCFMT_LEFT, 0);
	}
	
	RecalcLayout();
	
}
void CConnectionFormView::RecalcLayout()
{
	if(m_bInitialized)
	{
		CRect rc;
		GetClientRect(&rc);
		rc.DeflateRect(20, 20);
		m_wndConnectList.MoveWindow(&rc);

		m_wndConnectList.GetWindowRect(&rc);
		int nCX = rc.Width() / 4;
		for(int i = 0; i < 4; i ++)
			m_wndConnectList.SetColumnWidth(i, nCX);
	}
}
void CConnectionFormView::InitSetting(XDLS_Setting *pSetting)
{
	m_pSetting = pSetting;
}
void CConnectionFormView::Server_Run()
{
	CMainFrame *pMainFrm = (CMainFrame*)AfxGetMainWnd();
	
}
void CConnectionFormView::Server_Stop()
{
	CMainFrame *pMainFrm = (CMainFrame*)AfxGetMainWnd();
	
	m_wndConnectList.DeleteAllItems();
}
void CConnectionFormView::OnTimerWork(UINT nID)
{

}

void CConnectionFormView::Wnd_Active(BOOL bActive)
{

}
void CConnectionFormView::OnDrawInfo(CDC *pDC)
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

void CConnectionFormView::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	OnDrawInfo(&dc);
	
	// Do not call CXTMainFormView::OnPaint() for painting messages
}
HRESULT STDMETHODCALLTYPE CConnectionFormView::RtspClientNew(unsigned char *psz_session ,
												unsigned char* ip, int i_client_port,
												unsigned char* psz_rtsp_path,
												unsigned int nCookie)
{

	g_counter++;
	int nIndex = m_wndConnectList.GetItemCount();
	CString strAddress;
	//strAddress.Format("%s:%d", ip, i_client_port);
	strAddress.Format("%d",g_counter);
	nIndex = m_wndConnectList.InsertItem(nIndex, strAddress);
	m_wndConnectList.SetItemText(nIndex, 1, "VOD");
	m_wndConnectList.SetItemText(nIndex, 2, (char*)psz_rtsp_path);
	m_wndConnectList.SetItemText(nIndex, 3, (char*)psz_session);
	m_wndConnectList.SetItemData(nIndex, (DWORD)nCookie);
	
	return S_OK;
}
HRESULT STDMETHODCALLTYPE CConnectionFormView::RtspClientDel(unsigned int nCookie)
{
	for(int i = 0; i < m_wndConnectList.GetItemCount(); i ++)
	{
		if(m_wndConnectList.GetItemData(i) == nCookie)
		{
			m_wndConnectList.DeleteItem(i);
			break;
		}
	}
	
	return S_OK;
}
