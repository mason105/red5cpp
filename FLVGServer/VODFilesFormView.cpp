// VODFilesFormView.cpp : implementation file
//

#include "stdafx.h"
#include "XDigitalLifeServerApp.h"
#include "VODFilesFormView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVODFilesFormView

IMPLEMENT_DYNCREATE(CVODFilesFormView, CXTMainFormView)

CVODFilesFormView::CVODFilesFormView()
	: CXTMainFormView(CVODFilesFormView::IDD)
{
	//{{AFX_DATA_INIT(CVODFilesFormView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_bInitialized = FALSE;
	m_pSetting = NULL;
}

CVODFilesFormView::~CVODFilesFormView()
{
}

void CVODFilesFormView::DoDataExchange(CDataExchange* pDX)
{
	CXTMainFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CVODFilesFormView)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CVODFilesFormView, CXTMainFormView)
	//{{AFX_MSG_MAP(CVODFilesFormView)
	ON_WM_SIZE()
	ON_WM_CREATE()
	ON_BN_CLICKED(IDC_BUTTON_PREVPATH, OnBtnPrevPathClicked)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVODFilesFormView diagnostics

#ifdef _DEBUG
void CVODFilesFormView::AssertValid() const
{
	CXTMainFormView::AssertValid();
}

void CVODFilesFormView::Dump(CDumpContext& dc) const
{
	CXTMainFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CVODFilesFormView message handlers

void CVODFilesFormView::OnInitialUpdate() 
{
	CXTMainFormView::OnInitialUpdate();
	
	if(!m_bInitialized)
	{
		m_comboAddressBar.SetFont(&XTAuxData().font);
		m_btnPrevPath.SetFont(&XTAuxData().font);
		
		m_shellList.AssociateTree(&m_shellTree);
		m_shellTree.AssociateList(&m_shellList);
		m_shellTree.AssociateCombo(&m_comboAddressBar);
			
		m_bInitialized = TRUE;
	}
	
	RecalcLayout();
}

void CVODFilesFormView::OnSize(UINT nType, int cx, int cy) 
{
	CXTMainFormView::OnSize(nType, cx, cy);
	
	SetScaleToFitSize(CSize(cx, cy));
	
	RecalcLayout();

}
void CVODFilesFormView::RecalcLayout()
{
	if(m_bInitialized)
	{
		const int nComboAddressBarHeight = 22;
		const int nBtnPrevPathWidth = 40;
		
		CRect rcClient, rc;
		GetClientRect(&rcClient);

		if(m_comboAddressBar.GetSafeHwnd())
		{
			rc.SetRect(rcClient.left + nBtnPrevPathWidth, rcClient.top,
				rcClient.right ,
				rcClient.top + nComboAddressBarHeight * 4);
			m_comboAddressBar.MoveWindow(&rc);
		}
		if(m_btnPrevPath.GetSafeHwnd())
		{
			rc.SetRect(rcClient.left,
				rcClient.top,
				rcClient.left + nBtnPrevPathWidth,
				rcClient.top + nComboAddressBarHeight);
			rc.DeflateRect(2,2);
			m_btnPrevPath.MoveWindow(&rc);
		}
		if(m_shellTree.GetSafeHwnd())
		{
			rc.SetRect(rcClient.left, 
				nComboAddressBarHeight, 
				rcClient.right, rcClient.bottom);
			m_shellList.MoveWindow(&rc);
		}
	}
}

int CVODFilesFormView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CXTMainFormView::OnCreate(lpCreateStruct) == -1)
		return -1;
	m_shellTree.EnableAutoInit(FALSE);
	if( !m_shellTree.Create(WS_VISIBLE, 
		CRect(0,0,0,0), this, IDC_SHELLTREE_VIEW))
	{
		TRACE0( "Unable to create tree control.\n" );
		return -1;
	}
	if (!m_shellList.Create(WS_VISIBLE | WS_CHILD | WS_CLIPCHILDREN
		| LVS_REPORT | LVS_SHAREIMAGELISTS | LVS_EDITLABELS,
		CRect(0,0,0,0), this, IDC_SHELLLIST_VIEW))
	{
		TRACE0("Failed to create list control.\n");
		return -1;
	}
	if (!m_comboAddressBar.Create(CBS_DROPDOWN | WS_CHILD,
		CRect(0,0,0,0), this, IDC_COMBO_ADDRESSBAR))
	{
		TRACE0("Failed to create combobox\n");
		return -1;      // fail to create
	}
	if(!m_btnPrevPath.Create("...", BS_PUSHLIKE|WS_CHILD,
		CRect(0,0,0,0), this, IDC_BUTTON_PREVPATH))
	{
		TRACE0("Failed to create m_btnPrevPath\n");
		return -1;      // fail to create
		
	}
	m_comboAddressBar.ShowWindow(SW_SHOW);
	m_btnPrevPath.ShowWindow(SW_SHOW);
	
	m_shellList.GetFlatHeaderCtrl()->EnableAutoSize();
	m_shellList.SetMinimumColSize(15);
	

	return 0;
}
void KillSpelicalChar(char *szString , char nCh)
{
	int nLen = strlen(szString);
	if(szString[nLen-1] != nCh)
		return;
	for(int i = nLen -1; i >= 0; i --)
	{
		if(szString[i] == nCh)
			szString[i] = '\0';
		else
			break;
	}
}
char *StrFind(char *szSrc, char *szFind)
{
	int nSrcLen = strlen(szSrc);
	int nFindLen= strlen(szFind);
	for(int i = 0; i < nSrcLen; i ++)
	{
		if(strnicmp(&szSrc[i], szFind, nFindLen) == 0)
			return &szSrc[i];
	}
	return NULL;
}

void CVODFilesFormView::OnBtnPrevPathClicked()
{
	CString strNewPath;
	m_comboAddressBar.GetWindowText(strNewPath);
	
	if (strNewPath.GetLength())
	{
		KillSpelicalChar((LPSTR)(LPCSTR)strNewPath, '\\');
		int nPos = strNewPath.ReverseFind('\\');
		if(nPos != -1)
			strNewPath.SetAt(nPos, '\0');
		CString strRootPath = m_shellTree.GetRootPath();
		KillSpelicalChar((LPSTR)(LPCSTR)strRootPath, '\\');	
		if(StrFind((LPSTR)(LPCSTR)strNewPath, (LPSTR)(LPCSTR)strRootPath))
		{
			TCHAR sztmpPath[2048];
			_tcscpy(sztmpPath, (LPCSTR)strNewPath);
			_tcscat(sztmpPath, "\\");
			m_shellTree.TunnelTree(sztmpPath);
		}
	}
}
void CVODFilesFormView::InitSetting(XDLS_Setting *pSetting)
{
	m_pSetting = pSetting;
}
void CVODFilesFormView::Server_Run()
{
	if(m_pSetting)
	{
		m_shellTree.SetRootPath(m_pSetting->szVODFilePath);
		
	}
}
void CVODFilesFormView::Server_Stop()
{
}
void CVODFilesFormView::OnTimerWork(UINT nID)
{
	
}

void CVODFilesFormView::Wnd_Active(BOOL bActive)
{
	
}