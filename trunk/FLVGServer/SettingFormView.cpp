// SettingFormView.cpp : implementation file
//

#include "stdafx.h"
#include "XDigitalLifeServerApp.h"
#include "SettingFormView.h"
#include "MainFrm.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSettingFormView

IMPLEMENT_DYNCREATE(CSettingFormView, CXTMainFormView)

CSettingFormView::CSettingFormView()
	: CXTMainFormView(CSettingFormView::IDD)
{
	//{{AFX_DATA_INIT(CSettingFormView)
	//}}AFX_DATA_INIT
	m_pSetting = NULL;
	m_bInitialized = FALSE;
	m_pSetting = NULL;
}

CSettingFormView::~CSettingFormView()
{
}

void CSettingFormView::DoDataExchange(CDataExchange* pDX)
{
	CXTMainFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSettingFormView)
	//}}AFX_DATA_MAP
//	DDX_Control(pDX, IDC_BUTTON_APPLY, m_btnApply);
//	DDX_Control(pDX, IDC_BUTTON_DEFAULT, m_btnDefault);
}


BEGIN_MESSAGE_MAP(CSettingFormView, CXTMainFormView)
	//{{AFX_MSG_MAP(CSettingFormView)
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON_DEFAULT, OnButtonDefault)
	ON_BN_CLICKED(IDC_BUTTON_APPLY, OnButtonApply)
	//}}AFX_MSG_MAP
	ON_MESSAGE(XTPWM_TASKPANEL_NOTIFY, OnPanelNotify)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSettingFormView diagnostics

#ifdef _DEBUG
void CSettingFormView::AssertValid() const
{
	CXTMainFormView::AssertValid();
}

void CSettingFormView::Dump(CDumpContext& dc) const
{
	CXTMainFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSettingFormView message handlers

void CSettingFormView::OnSize(UINT nType, int cx, int cy) 
{
	CXTMainFormView::OnSize(nType, cx, cy);
	
	SetScaleToFitSize(CSize(cx, cy));
	RecalcLayout();
	
}

void CSettingFormView::OnFinalRelease() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CXTMainFormView::OnFinalRelease();
}

void CSettingFormView::OnInitialUpdate() 
{
	if(!m_bInitialized)
	{
		m_jpgBackGround.Load(IDR_BACKGROUND);
		
		CXTMainFormView::OnInitialUpdate();
		

		if (!m_wndSettingPanel.Create(WS_CHILD|WS_VISIBLE, CRect(0,0,0,0),
			this, IDC_SETTINGPANEL))
		{
			TRACE0("Failed to create outlook bar.");
			return ;
		}
		m_wndSettingPanel.SetOwner(this);

		m_SettingVODDlg.Create(IDD_DIALOG_SETTING_VOD, &m_wndSettingPanel);
		m_SettingVODDlg.ShowWindow(SW_SHOW);
		m_SettingVODDlg.ModifyStyle(0, WS_VISIBLE, 0);

		CXTPTaskPanelGroup* pGroup = m_wndSettingPanel.AddGroup(IDS_VODSERVER);
		CXTPTaskPanelGroupItem* pItem = pGroup->AddControlItem(m_SettingVODDlg);
		pItem->GetMargins().SetRect(0, 0, 0, 0);
		m_SettingVODDlg.SetItem(pItem);
		
		pGroup = m_wndSettingPanel.AddGroup(IDS_SECURITY);
		
		m_wndSettingPanel.SetBehaviour(xtpTaskPanelBehaviourList);
		m_wndSettingPanel.SetSelectItemOnFocus(TRUE);
		
		m_wndSettingPanel.FindGroup(IDS_VODSERVER)->SetExpanded(TRUE);
		CString strTitle;
#ifdef LANG_CHINESE 
		strTitle = "Ó¦ÓÃ";
#else
		strTitle = "Apply";
#endif	
		m_btnApply.Create(strTitle, WS_VISIBLE|WS_CHILD|BS_PUSHLIKE, CRect(0, 0, 0, 0), this, IDC_BUTTON_APPLY);
#ifdef LANG_CHINESE 
		strTitle = "Ä¬ÈÏ";
#else
		strTitle = "Default";
#endif
		m_btnDefault.Create(strTitle, WS_VISIBLE|WS_CHILD|BS_PUSHLIKE, CRect(0, 0, 0, 0), this, IDC_BUTTON_DEFAULT);
	}
	
	RecalcLayout();
	
}
void CSettingFormView::RecalcLayout()
{
	if(m_bInitialized)
	{
		CRect rc, rcClient;
		GetClientRect(&rcClient);
		rc = rcClient;
		rc.DeflateRect(20, 20);
		rc.bottom -= 20;
		m_wndSettingPanel.MoveWindow(&rc);
		rc = rcClient;
		rc.bottom-= 12;
		rc.top   = rc.bottom - 24;
		rc.right -= 20;
		rc.left	 = rc.right - 60;
		m_btnApply.MoveWindow(&rc);
		rc.right = rc.left - 10;
		rc.left	 = rc.right - 60;	
		m_btnDefault.MoveWindow(&rc);
	}
}
void CSettingFormView::InitSetting(XDLS_Setting *pSetting)
{
	m_pSetting = pSetting;
	m_SettingVODDlg.InitSetting(pSetting);
}
void CSettingFormView::Server_Run()
{
	
}
void CSettingFormView::Server_Stop()
{
}
void CSettingFormView::OnTimerWork(UINT nID)
{
	
}

void CSettingFormView::Wnd_Active(BOOL bActive)
{
	
}
void CSettingFormView::OnDrawInfo(CDC *pDC)
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



void CSettingFormView::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	OnDrawInfo(&dc);
	
	// Do not call CXTMainFormView::OnPaint() for painting messages
}
LRESULT CSettingFormView::OnPanelNotify(WPARAM wParam, LPARAM lParam)
{
	switch (wParam)
	{
	case XTP_TPN_CLICK:
		{
			CXTPTaskPanelGroupItem* pItem = (CXTPTaskPanelGroupItem*)lParam;
				
		}
		break;
	case XTP_TPN_GROUPEXPANDED:
		{
		}
		break;
	case XTP_TPN_RCLICK:
		return TRUE;
	}
	
	return 0;
}

void CSettingFormView::OnButtonDefault() 
{
	CMainFrame::DefaultXDLSSetting(m_pSetting);
	InitSetting(m_pSetting);
}

void CSettingFormView::OnButtonApply() 
{	
	m_SettingVODDlg.ApplySetting(m_pSetting);	
}
