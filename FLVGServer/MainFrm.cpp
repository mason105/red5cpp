// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "XDigitalLifeServerApp.h"
#include "MainFrm.h"
#include "ControlFrameWnd.h"
#include "msgdlg.h"
#include "MarkupSTL.h"
#include "PathWatcher.h"
#include "stdafx.h"
#include <conio.h>
#include <iostream>
#include "PathWatcher.h"
#include "Dog.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#define WM_GETOUT WM_USER + 1050
/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CXTMainFrm)

BEGIN_MESSAGE_MAP(CMainFrame, CXTMainFrm)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_GETMINMAXINFO()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_COMMAND(ID_RUN, OnRun)
	ON_UPDATE_COMMAND_UI(ID_RUN, OnUpdateRun)
	ON_COMMAND(ID_STOP, OnStop)
	ON_UPDATE_COMMAND_UI(ID_STOP, OnUpdateStop)
	ON_WM_TIMER()
	ON_WM_CLOSE()
	ON_WM_NCPAINT()
	ON_WM_COPYDATA()
	//}}AFX_MSG_MAP
	ON_MESSAGE(XTPWM_DOCKINGPANE_NOTIFY, OnDockingPaneNotify)
	ON_MESSAGE(WM_CONTROLPROPERTIESTREE_SELECTED, OnControlPropertiesTreeSelected)
	ON_MESSAGE(WM_GETOUT, OnGetOut)
END_MESSAGE_MAP()
static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

static CMainFrame* pMain;



CString GetXDLifeServerAppPath()
{	
	TCHAR szFolder[512];
	GetModuleFileName(AfxGetInstanceHandle(), szFolder, 512);
	CString strPath(szFolder);
	int pos = strPath.ReverseFind('\\');
	if(pos != -1)
		return strPath.Left(pos);
	return strPath;
}
void LoadXDLSSetting(char *szFilePath, XDLS_Setting *pSetting)
{
	CMarkupSTL xml;
	xml.Load((LPCSTR)szFilePath);
	while ( xml.FindElem("XDSItem_VOD") )
	{
		xml.FindChildElem( "ServerAddress");
		strcpy(pSetting->szServerAddress,xml.GetChildData().c_str());
		xml.FindChildElem( "ServerPort");
		pSetting->nServerPort = atoi(xml.GetChildData().c_str());
		xml.FindChildElem( "VODFilePath");
		strcpy(pSetting->szVODFilePath,xml.GetChildData().c_str());
	}	
	
	while ( xml.FindElem("XDSItem_Web") )
	{
		xml.FindChildElem( "WebServerPort");
		pSetting->nWebServerPort = atoi(xml.GetChildData().c_str());
		xml.FindChildElem( "WebMaxOutputBitrate");
		pSetting->nWebMaxOutputBitrate = atoi(xml.GetChildData().c_str());
		xml.FindChildElem( "WebMaxRelays");
		pSetting->nWebMaxRelays = atoi(xml.GetChildData().c_str());
	}	
	while ( xml.FindElem("XDSItem_Relay") )
	{
		LPXDLS_RelayPoint pRP = new XDLS_RelayPoint;
		xml.FindChildElem( "Name");
		pRP->strName = xml.GetChildData().c_str();
		xml.FindChildElem( "Input");
		pRP->strInput = xml.GetChildData().c_str();
		xml.FindChildElem( "rt");
		pRP->rt = (RelayType)atoi(xml.GetChildData().c_str());
		xml.FindChildElem( "NetProcotol");
		pRP->strNetProcotol = xml.GetChildData().c_str();
		xml.FindChildElem( "EncapsulationMedthod");
		pRP->strEncapsulationMedthod = xml.GetChildData().c_str();
		xml.FindChildElem( "EncapsulationMedthod");
		pRP->strEncapsulationMedthod = xml.GetChildData().c_str();
		xml.FindChildElem( "NetAddress");
		pRP->strNetAddress = xml.GetChildData().c_str();
		xml.FindChildElem( "MifaceAddress");
		pRP->strMifaceAddress = xml.GetChildData().c_str();
		xml.FindChildElem( "NetNetPort");
		pRP->dwNetNetPort = atoi(xml.GetChildData().c_str());
		xml.FindChildElem( "NetRTSPPort");
		pRP->dwNetRTSPPort = atoi(xml.GetChildData().c_str());
		xml.FindChildElem( "WebSourceType");
		pRP->strWebSourceType = xml.GetChildData().c_str();
		xml.FindChildElem( "WebDescription");
		pRP->strWebDescription = xml.GetChildData().c_str();
		xml.FindChildElem( "WebRelayID");
		pRP->strWebRelayID = xml.GetChildData().c_str();
		xml.FindChildElem( "WebRelayBitrate");
		pRP->dwWebRelayBitrate = atoi(xml.GetChildData().c_str());
		pRP->pRelayPoint = NULL;
		pSetting->RelayList.push_back(pRP);
	}
	
}
void SaveXDLSSetting(char *szFilePath, XDLS_Setting *pSetting)
{
	CMarkupSTL xml;
	xml.AddElem("XDSItem_VOD");
	xml.IntoElem();
	xml.AddElem( "ServerAddress", pSetting->szServerAddress);
	xml.AddElem( "ServerPort",  pSetting->nServerPort);
	xml.AddElem( "VODFilePath",  pSetting->szVODFilePath);
	xml.OutOfElem();

	xml.AddElem("XDSItem_Web");
	xml.IntoElem();
	xml.AddElem( "WebServerPort", pSetting->nWebServerPort);
	xml.AddElem( "WebMaxOutputBitrate",  pSetting->nWebMaxOutputBitrate);
	xml.AddElem( "WebMaxRelays",  pSetting->nWebMaxRelays);
	xml.OutOfElem();
	
	RELAY_LIST_IT it = pSetting->RelayList.begin();
	for(; it != pSetting->RelayList.end(); it++)
	{
		LPXDLS_RelayPoint pRP = *it;
		if(pRP)
		{
			xml.AddElem("XDSItem_Relay");
			xml.IntoElem();
			xml.AddElem( "Name", pRP->strName);
			xml.AddElem( "Input", pRP->strInput);
			xml.AddElem( "rt", (int)pRP->rt);
			xml.AddElem( "NetProcotol", pRP->strNetProcotol);
			xml.AddElem( "EncapsulationMedthod", pRP->strEncapsulationMedthod);
			xml.AddElem( "NetAddress", pRP->strNetAddress);
			xml.AddElem( "MifaceAddress", pRP->strMifaceAddress);
			xml.AddElem( "NetNetPort", pRP->dwNetNetPort);
			xml.AddElem( "NetRTSPPort", pRP->dwNetRTSPPort);
			xml.AddElem( "WebSourceType", pRP->strWebSourceType);
			xml.AddElem( "WebDescription", pRP->strWebDescription);
			xml.AddElem( "WebRelayID", pRP->strWebRelayID);
			xml.AddElem( "WebRelayBitrate", pRP->dwWebRelayBitrate);
			
			xml.OutOfElem();
		}
				
	}		
	xml.Save((LPCSTR)szFilePath);
				
}
void ClearXDLSSetting(XDLS_Setting * pSetting)
{
	RELAY_LIST_IT it = pSetting->RelayList.begin();
	for(; it != pSetting->RelayList.end(); it++)
	{
		LPXDLS_RelayPoint pRP = *it;
		if(pRP)
		{
			delete pRP;
		}
	}
	pSetting->RelayList.clear();

}

CMainFrame::CMainFrame()
{
	m_pControlFrameWnd = NULL;
	m_pVODFilesFormView = NULL;
	m_pPerfomanceView = NULL;
	m_pPublishPointFormView = NULL;
	m_pRelayFormView = NULL;
	m_pConnectionFormView = NULL;
	m_pSettingFormView = NULL;
	m_pLogFormView = NULL;
	m_pActiveView = NULL;
	DefaultXDLSSetting(&m_XDLS_Setting);
	CString strSettingFilePath = GetXDLifeServerAppPath() + "\\XDLS_Setting.xml";
	LoadXDLSSetting((LPSTR)(LPCSTR)strSettingFilePath, &m_XDLS_Setting);
	IsInited = FALSE;
	if(!m_XDLS_Setting.szVODFilePath)
	{
	}
	_FLVServer = 0;
	
}

CMainFrame::~CMainFrame()
{
	CString strSettingFilePath = GetXDLifeServerAppPath() + "\\XDLS_Setting.xml";
	SaveXDLSSetting((LPSTR)(LPCSTR)strSettingFilePath, &m_XDLS_Setting);
	ClearXDLSSetting(&m_XDLS_Setting);

}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CXTMainFrm::OnCreate(lpCreateStruct) == -1)
		return -1;

	m_ilTreeIcons.Create(16, 16, ILC_MASK|ILC_COLOR8, 0, 1);
	CBitmap bmp;
	bmp.LoadBitmap(IDR_TREE_ICONS);	
	m_ilTreeIcons.Add(&bmp, RGB(255, 0, 255));
	
	if (!InitCommandBars())
		return -1;
	
	CXTPCommandBars* pCommandBars = GetCommandBars();
	
	//pCommandBars->SetMenu(_T("Menu Bar"), IDR_MAINFRAME);
	
	XTPImageManager()->SetMaskColor(RGB(0, 255, 0));
	
	CXTPToolBar* pStandardBar = (CXTPToolBar*)pCommandBars->Add(_T("Standard"), xtpBarTop);
	if (!pStandardBar ||
		!pStandardBar->LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;
	}
	
	pStandardBar->EnableDocking(xtpFlagAlignAny|xtpFlagFloating|xtpFlagStretched|xtpFlagHideWrap);
	
	CXTPPaintManager::SetCustomTheme(new CXDLTheme());
	
	XTP_COMMANDBARS_ICONSINFO* pIconsInfo = XTPPaintManager()->GetIconsInfo();
	pIconsInfo->bUseDisabledIcons = TRUE;			
	pCommandBars->GetCommandBarsOptions()->bLargeIcons = FALSE;
	pCommandBars->GetCommandBarsOptions()->szLargeIcons = CSize(24, 24);
	pCommandBars->GetCommandBarsOptions()->bShowExpandButtonAlways = FALSE;
	
	
	GetDockingPaneManager()->InstallDockingPanes(this);
	GetDockingPaneManager()->SetCustomTheme(new CXDLDockingTheme);
	
	CXTPDockingPaneLayout layoutNormal(GetDockingPaneManager());
	
	{
		CXTPDockingPane* panePreviewManager = GetDockingPaneManager()->CreatePane(
			ID_VIEW_CONTROLPROPERTIESTREE, CRect(0, 0, 200, 200), xtpPaneDockLeft);
		panePreviewManager->SetTitle("Control && Properties");
		panePreviewManager->SetOptions(xtpPaneNoCaption|xtpPaneNoHideable|xtpPaneNoCloseable);
		panePreviewManager->SetMinTrackSize(CSize(200, 200));
		
	}
	{
		CCreateContext cc;
		ZeroMemory(&cc, sizeof(cc));
		
		m_pPerfomanceView = (CPerfomanceView*)CPerfomanceView::CreateObject();
		m_pPerfomanceView->CreateEx(NULL, 
			NULL, NULL, 
			WS_CHILD|WS_VISIBLE, CRect(0, 0, 0, 0), 
			m_pControlFrameWnd, 0, &cc);
		m_pPerfomanceView->InitSetting(&m_XDLS_Setting);
		m_pPerfomanceView->OnInitialUpdate();
		
		m_pPublishPointFormView = (CPublishPointFormView*)CPublishPointFormView::CreateObject();
		m_pPublishPointFormView->CreateEx(NULL, 
			NULL, NULL, 
			WS_CHILD|WS_VISIBLE, CRect(0, 0, 0, 0), 
			m_pControlFrameWnd, IDD_DIALOG_PUBLISHPOINT, &cc);
		m_pPublishPointFormView->InitSetting(&m_XDLS_Setting);
		m_pPublishPointFormView->OnInitialUpdate();
				
		m_pVODFilesFormView = (CVODFilesFormView*)CVODFilesFormView::CreateObject();
		m_pVODFilesFormView->CreateEx(NULL, 
			NULL, NULL, 
			WS_CHILD|WS_VISIBLE, CRect(0, 0, 0, 0), 
			m_pControlFrameWnd, IDD_DIALOG_VODFILES, &cc);
		m_pVODFilesFormView->InitSetting(&m_XDLS_Setting);
		m_pVODFilesFormView->OnInitialUpdate();
		
		m_pRelayFormView = (CRelayFormView*)CRelayFormView::CreateObject();
		m_pRelayFormView->CreateEx(NULL, 
			NULL, NULL, 
			WS_CHILD|WS_VISIBLE, CRect(0, 0, 0, 0), 
			m_pControlFrameWnd, IDD_DIALOG_RELAY, &cc);
		m_pRelayFormView->OnInitialUpdate();
		m_pRelayFormView->InitSetting(&m_XDLS_Setting);

		m_pConnectionFormView = (CConnectionFormView*)CConnectionFormView::CreateObject();
		m_pConnectionFormView->CreateEx(NULL, 
			NULL, NULL, 
			WS_CHILD|WS_VISIBLE, CRect(0, 0, 0, 0), 
			m_pControlFrameWnd, IDD_DIALOG_CONNECTION, &cc);
		m_pConnectionFormView->InitSetting(&m_XDLS_Setting);
		m_pConnectionFormView->OnInitialUpdate();
		
		m_pSettingFormView = (CSettingFormView*)CSettingFormView::CreateObject();
		m_pSettingFormView->CreateEx(NULL, 
			NULL, NULL, 
			WS_CHILD|WS_VISIBLE, CRect(0, 0, 0, 0), 
			m_pControlFrameWnd, IDD_DIALOG_SETTING, &cc);
		m_pSettingFormView->InitSetting(&m_XDLS_Setting);
		m_pSettingFormView->OnInitialUpdate();

		m_pLogFormView = (CLogFormView*)CLogFormView::CreateObject();
		m_pLogFormView->CreateEx(NULL, 
			NULL, NULL, 
			WS_CHILD|WS_VISIBLE, CRect(0, 0, 0, 0), 
			m_pControlFrameWnd, IDD_DIALOG_LOG, &cc);
		m_pLogFormView->InitSetting(&m_XDLS_Setting);
		m_pLogFormView->OnInitialUpdate();
		
	}
	if (!m_wndControlPropertiesTreeCtrl.GetSafeHwnd())
	{
		if (!m_wndControlPropertiesTreeCtrl.Create (WS_CLIPCHILDREN|WS_CLIPSIBLINGS|WS_VISIBLE|TVS_HASLINES|TVS_LINESATROOT|TVS_HASBUTTONS|TVS_SHOWSELALWAYS,
			CRect(0,0,0,0), this, IDC_VIEW_CONTROLPROPERTIESTREE))
		{
			TRACE0( "Unable to create tree control.\n" );
			return -1;
		}
		
		m_wndControlPropertiesTreeCtrl.SetImageList(&m_ilTreeIcons, TVSIL_NORMAL);

		ExpandPaneTree(TRUE);
		
	}
	CXTPPaintManager::SetCustomTheme(new CXDLTheme());
	CXTPPaintManager::SetTheme(xtpThemeOffice2003);
	CenterWindow();

	
	SetTimer(TIMERID_ONESECOND , 1000, NULL);
	SetTimer(TIMERID_TWOSECOND , 2000, NULL);

	
	m_strBindIP = "127.0.0.1";

	char *pCmdLine = GetCommandLine();
	char *p = strstr(pCmdLine, "-d");
	if(p)
	{
		p+=3;
		int port = atoi(p);
		m_XDLS_Setting.nServerPort = port;
		CString strText;
		strText.Format("XDLServer_%s", p);
		SetWindowText(strText);

		ModifyStyleEx(WS_EX_APPWINDOW,WS_EX_TOOLWINDOW);   
		//显示隐藏   
		WINDOWPLACEMENT   wp;   
		wp.length=sizeof(WINDOWPLACEMENT);   
		wp.flags=WPF_RESTORETOMAXIMIZED;   
		wp.showCmd=SW_HIDE;   
		SetWindowPlacement(&wp);     
		OnRun();

		m_strOutWindowText = strText;
	}
	
	OnRun();
	
	return 0;
}
void	CMainFrame::ExpandPaneTree(BOOL bExpand)
{
	m_wndControlPropertiesTreeCtrl.DeleteAllItems();
	if(m_pActiveView && m_pActiveView->GetSafeHwnd())
	{
		m_pActiveView->ShowWindow(SW_HIDE);
		m_pActiveView = NULL;
	}
	if(bExpand)
	{
		TCHAR szBuffer[512];
		DWORD dwBufferSize = 512;
		GetComputerName(szBuffer, &dwBufferSize);
		
		CString strCaption;
		HTREEITEM htmpTreeItem;
		strCaption.Format("GOD FLV Server - %s", szBuffer);
		HTREEITEM hTreeItem = m_wndControlPropertiesTreeCtrl.InsertItem(strCaption, 0, 0);
		m_wndControlPropertiesTreeCtrl.SetItemData(hTreeItem, (DWORD)NULL);
		
		htmpTreeItem = m_wndControlPropertiesTreeCtrl.InsertItem(STR_ServerPerfomance, 5, 5, hTreeItem);
		m_wndControlPropertiesTreeCtrl.SetItemData(htmpTreeItem, (DWORD)m_pPerfomanceView);
		
		HTREEITEM hTreeItem1 = m_wndControlPropertiesTreeCtrl.InsertItem(STR_PublishPoint, 3, 3, hTreeItem);
		m_wndControlPropertiesTreeCtrl.SetItemData(hTreeItem1, (DWORD)m_pPublishPointFormView);
		
		htmpTreeItem = m_wndControlPropertiesTreeCtrl.InsertItem(STR_VODFiles, 6, 6, hTreeItem1);
		m_wndControlPropertiesTreeCtrl.SetItemData(htmpTreeItem, (DWORD)m_pVODFilesFormView);
		
		htmpTreeItem = m_wndControlPropertiesTreeCtrl.InsertItem(STR_Relay, 1, 1, hTreeItem1);
		m_wndControlPropertiesTreeCtrl.SetItemData(htmpTreeItem, (DWORD)m_pRelayFormView);
		
		htmpTreeItem = m_wndControlPropertiesTreeCtrl.InsertItem(STR_Connection, 4, 4, hTreeItem);
		m_wndControlPropertiesTreeCtrl.SetItemData(htmpTreeItem, (DWORD)m_pConnectionFormView);
		
		htmpTreeItem = m_wndControlPropertiesTreeCtrl.InsertItem(STR_Setting, 3, 3, hTreeItem);
		m_wndControlPropertiesTreeCtrl.SetItemData(htmpTreeItem, (DWORD)m_pSettingFormView);
		
		htmpTreeItem = m_wndControlPropertiesTreeCtrl.InsertItem(STR_Log, 2, 2, hTreeItem);
		m_wndControlPropertiesTreeCtrl.SetItemData(htmpTreeItem, (DWORD)m_pLogFormView);
		
		m_wndControlPropertiesTreeCtrl.Expand (hTreeItem, TVE_EXPAND);
		m_wndControlPropertiesTreeCtrl.Expand (hTreeItem1, TVE_EXPAND);
	}
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CXTMainFrm::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CXTMainFrm::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CXTMainFrm::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers
LRESULT CMainFrame::OnControlPropertiesTreeSelected(WPARAM wParam, LPARAM lParam)
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)wParam;

	CString strText = m_wndControlPropertiesTreeCtrl.GetItemText(pNMTreeView->itemNew.hItem);
	m_wndCaption.UpdateCaption(strText, GetIcon(IDR_XDIGITTYPE));
	m_wndCaption.Invalidate();
	if(pNMTreeView->itemOld.hItem)
	{
		CWnd *pOldView = (CWnd*)m_wndControlPropertiesTreeCtrl.GetItemData(pNMTreeView->itemOld.hItem);
		if(pOldView && pOldView->m_hWnd)
		{
			pOldView->ShowWindow(SW_HIDE);
			if(m_pPerfomanceView && 
				m_pPerfomanceView->m_hWnd == pOldView->m_hWnd)
				m_pPerfomanceView->Wnd_Active(FALSE);
			if(m_pPublishPointFormView &&
				m_pPublishPointFormView->m_hWnd == pOldView->m_hWnd)
				m_pPublishPointFormView->Wnd_Active(FALSE);
			if(m_pVODFilesFormView &&
				m_pVODFilesFormView->m_hWnd == pOldView->m_hWnd)
				m_pVODFilesFormView->Wnd_Active(FALSE);
			if(m_pRelayFormView &&
				m_pRelayFormView->m_hWnd == pOldView->m_hWnd)
				m_pRelayFormView->Wnd_Active(FALSE);
			if(m_pConnectionFormView &&
				m_pConnectionFormView->m_hWnd == pOldView->m_hWnd)				
				m_pConnectionFormView->Wnd_Active(FALSE);
			if(m_pSettingFormView &&
				m_pSettingFormView->m_hWnd == pOldView->m_hWnd)				
				m_pSettingFormView->Wnd_Active(FALSE);
			if(m_pLogFormView &&
				m_pLogFormView->m_hWnd == pOldView->m_hWnd)				
				m_pLogFormView->Wnd_Active(FALSE);
			
		}
	}
	CWnd *pNewView = (CWnd*)m_wndControlPropertiesTreeCtrl.GetItemData(pNMTreeView->itemNew.hItem);
	if(pNewView && pNewView->m_hWnd)
	{
		CRect rc;
		m_pControlFrameWnd->GetClientRect(&rc);
		pNewView->MoveWindow(&rc);
		pNewView->ShowWindow(SW_SHOW);

		m_pActiveView = pNewView;
		if(m_pPerfomanceView && 
			m_pPerfomanceView->m_hWnd == pNewView->m_hWnd)
			m_pPerfomanceView->Wnd_Active(TRUE);
		if(m_pPublishPointFormView &&
			m_pPublishPointFormView->m_hWnd == pNewView->m_hWnd)
			m_pPublishPointFormView->Wnd_Active(TRUE);
		if(m_pVODFilesFormView &&
			m_pVODFilesFormView->m_hWnd == pNewView->m_hWnd)
			m_pVODFilesFormView->Wnd_Active(TRUE);
		if(m_pRelayFormView &&
			m_pRelayFormView->m_hWnd == pNewView->m_hWnd)
			m_pRelayFormView->Wnd_Active(TRUE);
		if(m_pConnectionFormView &&
			m_pConnectionFormView->m_hWnd == pNewView->m_hWnd)				
			m_pConnectionFormView->Wnd_Active(TRUE);
		if(m_pSettingFormView &&
			m_pSettingFormView->m_hWnd == pNewView->m_hWnd)				
			m_pSettingFormView->Wnd_Active(TRUE);
		if(m_pLogFormView &&
			m_pLogFormView->m_hWnd == pNewView->m_hWnd)				
			m_pLogFormView->Wnd_Active(TRUE);
	}
	
	return 0;
}

LRESULT CMainFrame::OnDockingPaneNotify(WPARAM wParam, LPARAM lParam)
{
	if (wParam == XTP_DPN_SHOWWINDOW)
	{
		CXTPDockingPane* pPane = (CXTPDockingPane*)lParam;
		
		if (!pPane->IsValid())
		{
			switch (pPane->GetID())
			{
			case ID_VIEW_CONTROLPROPERTIESTREE:
				if (!m_wndControlPropertiesTreeCtrl.GetSafeHwnd())
				{
					if (!m_wndControlPropertiesTreeCtrl.Create (WS_CLIPCHILDREN|WS_CLIPSIBLINGS|WS_VISIBLE|TVS_HASLINES|TVS_LINESATROOT|TVS_HASBUTTONS|TVS_SHOWSELALWAYS,
						CRect(0,0,0,0), this, IDC_VIEW_CONTROLPROPERTIESTREE))
					{
						TRACE0( "Unable to create tree control.\n" );
						return -1;
					}
					
					m_wndControlPropertiesTreeCtrl.SetImageList(&m_ilTreeIcons, TVSIL_NORMAL);
					
				}
				pPane->Attach(&m_wndControlPropertiesTreeCtrl);
				break;
			default:
				return 0;
				break;
			}
			return 1;
		}
	}
	return 0;
}
BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT /*lpcs*/, CCreateContext* /*pContext*/)
{
	// TODO: Add your specialized code here and/or call the base class
	m_wndSplitterCaption.CreateStatic(this, 2, 1);
	m_wndSplitterCaption.ModifyStyle(0, WS_CLIPCHILDREN|WS_CLIPSIBLINGS);
		
	if (!InitializeCaptionBar())
		return FALSE;
		
	m_pControlFrameWnd = (CControlFrameWnd*)CControlFrameWnd::CreateObject();
	m_pControlFrameWnd->CreateEx(NULL, NULL, NULL, WS_CHILD|WS_VISIBLE, CRect(0, 0, 0, 0), &m_wndSplitterCaption, m_wndSplitterCaption.IdFromRowCol(1, 0));
	
	m_wndSplitterCaption.SetSplitterStyle(XT_SPLIT_NOFULLDRAG | XT_SPLIT_NOSIZE | XT_SPLIT_NOBORDER);
	
	return TRUE;
}
BOOL CMainFrame::InitializeCaptionBar()
{
	if (!m_wndCaption.Create(&m_wndSplitterCaption, _T("GOD FLV Server"), NULL,
		WS_VISIBLE|SS_CENTER|SS_CENTERIMAGE, CRect(0,0,0,0), m_wndSplitterCaption.IdFromRowCol(0, 0)))
	{
		TRACE0("Failed to caption window.\n");
		return FALSE;
	}
	
	HICON hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	
	// set the caption colors.
	m_wndCaption.SetCaptionColors (GetXtremeColor(COLOR_DESKTOP),
		GetXtremeColor(COLOR_DESKTOP), GetXtremeColor(COLOR_CAPTIONTEXT) );
	
	LOGFONT lf;
	XTAuxData().fontBold.GetLogFont(&lf);
	lf.lfHeight = 18;
	m_fontCaption.CreateFontIndirect(&lf);
	
	// set the font and initial icon.
	m_wndCaption.ModifyCaptionStyle(0,
		&m_fontCaption, NULL, hIcon);
	
	// Sizing for splitter
	m_wndSplitterCaption.SetRowInfo (0, 22, 0);
	
	return TRUE;
}
void CMainFrame::OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI) 
{
	lpMMI->ptMinTrackSize.x = 1000;
	lpMMI->ptMinTrackSize.y = 600;
	
	CXTMainFrm::OnGetMinMaxInfo(lpMMI);
}

void CMainFrame::OnDestroy() 
{
	CXTMainFrm::OnDestroy();
}

void CMainFrame::OnSize(UINT nType, int cx, int cy) 
{
	CXTMainFrm::OnSize(nType, cx, cy);
	
	if(m_pActiveView&& m_pActiveView->m_hWnd)
	{
		CRect rc;
		m_pControlFrameWnd->GetClientRect(&rc);
		m_pActiveView->MoveWindow(&rc);
	}
	
}

void CMainFrame::OnRun() 
{
	if(_FLVServer)
		return;
	_FLVServer = new FLVServer;
	if(_FLVServer->Start(m_XDLS_Setting.nServerPort,
		m_XDLS_Setting.szVODFilePath))
	{
		if(m_pPerfomanceView)
			m_pPerfomanceView->Server_Run();
		if(m_pPublishPointFormView)
			m_pPublishPointFormView->Server_Run();
		if(m_pVODFilesFormView)
			m_pVODFilesFormView->Server_Run();
		if(m_pRelayFormView)
			m_pRelayFormView->Server_Run();
		if(m_pConnectionFormView)
			m_pConnectionFormView->Server_Run();
		if(m_pSettingFormView)
			m_pSettingFormView->Server_Run();
		if(m_pLogFormView)
			m_pLogFormView->Server_Run();

		CString strTmp = GetXDLifeServerAppPath();
		strTmp += "\\WebRoot\\";
		_HttpServer.Start(m_XDLS_Setting.nWebServerPort,
			(char*)(LPCSTR)strTmp);

		IsInited = TRUE;
	}
	else
	{
		OnStop_inner();
		XDLCMessageBox("Run Error");
	}
	
	
}

void CMainFrame::OnUpdateRun(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(XFLVServer_Ptr()?FALSE:TRUE);
	
}
void CMainFrame::OnStop() 
{
	OnClose();
	
}
void CMainFrame::OnStop_inner() 
{

	if(_FLVServer)
	{
		_HttpServer.Stop();
		if(m_pPerfomanceView)
			m_pPerfomanceView->Server_Stop();
		if(m_pPublishPointFormView)
			m_pPublishPointFormView->Server_Stop();
		if(m_pVODFilesFormView)
			m_pVODFilesFormView->Server_Stop();
		if(m_pRelayFormView)
			m_pRelayFormView->Server_Stop();
		if(m_pConnectionFormView)
			m_pConnectionFormView->Server_Stop();
		if(m_pSettingFormView)
			m_pSettingFormView->Server_Stop();
		if(m_pLogFormView)
			m_pLogFormView->Server_Stop();
		_FLVServer->Stop();
		delete _FLVServer;	
		_FLVServer = 0;
	}
	IsInited = FALSE;
}

void CMainFrame::OnUpdateStop(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(XFLVServer_Ptr()?TRUE:FALSE);
	
}

void CMainFrame::DefaultXDLSSetting(XDLS_Setting *pSetting)
{
	ASSERT(pSetting);
	strcpy(pSetting->szServerAddress, "0.0.0.0");
	pSetting->nServerPort = 1935;

	CString strTmp = GetXDLifeServerAppPath();
	strTmp += "\\WorkFolder\\";
	
	strcpy(pSetting->szVODFilePath, (LPCSTR)strTmp);
	CreateDirectory(pSetting->szVODFilePath, NULL);
	strTmp = GetXDLifeServerAppPath();
	strTmp += "\\WebRoot\\";
	CreateDirectory((LPCSTR)strTmp, NULL);

	pSetting->nWebServerPort = 8200;
	pSetting->nWebMaxOutputBitrate = 0;
	pSetting->nWebMaxRelays = 5000;
	
}

void CMainFrame::OnTimer(UINT nIDEvent) 
{
	if(m_pPerfomanceView)
		m_pPerfomanceView->OnTimerWork(nIDEvent);
	if(m_pPublishPointFormView)
		m_pPublishPointFormView->OnTimerWork(nIDEvent);
	if(m_pVODFilesFormView)
		m_pVODFilesFormView->OnTimerWork(nIDEvent);
	if(m_pRelayFormView)
		m_pRelayFormView->OnTimerWork(nIDEvent);
	if(m_pConnectionFormView)
		m_pConnectionFormView->OnTimerWork(nIDEvent);
	if(m_pSettingFormView)
		m_pSettingFormView->OnTimerWork(nIDEvent);
	if(m_pLogFormView)
		m_pLogFormView->OnTimerWork(nIDEvent);
	
	CXTMainFrm::OnTimer(nIDEvent);
}
int  CMainFrame::Helper_GetCurrentofConnections()
{
	return 0;
}

void CMainFrame::OnClose() 
{
	
	CString strTitle;
#ifdef LANG_CHINESE 
	strTitle = "确定退出?";
#else
	strTitle = "Are you sure quit?";
#endif	
	if(XDLCMessageBox(strTitle) == IDOK)
	{
		OnStop_inner();
		CXTMainFrm::OnClose();
	}	
	
}

void CMainFrame::GetWindowTitle (CString& rString)
{
	if(m_strOutWindowText.GetLength())
	{
		rString = m_strOutWindowText;
		return ;
	}
	CString version;
	version.LoadString(IDS_FILEVERSION);
#ifdef LANG_CHINESE 
	rString.Format("GOD FLV Server %s (Professional)- %s", (LPCSTR)version, XFLVServer_Ptr() ? "运行" : "停止");
#else
	rString.Format("GOD FLV Server %s (Professional)- %s", (LPCSTR)version, XFLVServer_Ptr() ? "Running" : "Stopped");
#endif
}

void CMainFrame::OnFtpNewFile(LPVOID params)
{
	
}

void CMainFrame::WatchVODPath()
{
	
}

void CMainFrame::OnDelFile()
{

}


void CMainFrame::OnNcPaint() 
{
	// TODO: Add your message handler code here
	
	// Do not call CXTMainFrm::OnNcPaint() for painting messages
	CXTMainFrm::OnNcPaint();
}

BOOL CMainFrame::OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct) 
{

	return CXTMainFrm::OnCopyData(pWnd, pCopyDataStruct);
}

LRESULT CMainFrame::OnGetOut (WPARAM wParam, LPARAM lParam)
{
	return 1;
}

void CMainFrame::OnUDPDataHandleCallBack(sockaddr* from,
							 char * pData,
		unsigned long DataLength)
{
	if( DataLength == 4)
	{
		ATLTRACE("Exit %s\n", (LPCSTR)m_strOutWindowText);
		OnStop();
		exit(-1);
		CXTMainFrm::OnClose();
	}
}