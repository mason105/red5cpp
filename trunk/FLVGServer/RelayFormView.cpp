// RelayFormView.cpp : implementation file
//

#include "stdafx.h"
#include "XDigitalLifeServerApp.h"
#include "RelayFormView.h"
#include "RelayPropertySheet.h"
#include "MainFrm.h"
#include "SysInfo.h"
#include "SysUtils.h"
#include <sstream>
#include "Base64.h"
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRelayFormView
extern void IDfromStr(char* id, const char *str);

IMPLEMENT_DYNCREATE(CRelayFormView, CXTMainFormView)

extern CString ParseInput(CString input,CString outname);

CRelayFormView::CRelayFormView()
	: CXTMainFormView(CRelayFormView::IDD)
{
	//{{AFX_DATA_INIT(CRelayFormView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_pSetting = NULL;
	m_bInitialized = FALSE;
}

CRelayFormView::~CRelayFormView()
{
}

void CRelayFormView::DoDataExchange(CDataExchange* pDX)
{
	CXTMainFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRelayFormView)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRelayFormView, CXTMainFormView)
	//{{AFX_MSG_MAP(CRelayFormView)
	ON_WM_SIZE()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON_DELRELAY, OnDelRelay)
	ON_BN_CLICKED(IDC_BUTTON_NEWRELAY, OnNewRelay)
	ON_BN_CLICKED(IDC_BUTTON_RUNRELAY, OnRunRelay)
	ON_BN_CLICKED(IDC_BUTTON_STOPRELAY, OnStopRelay)
	ON_BN_CLICKED(IDC_BUTTON_STOPALLRELAY, OnStopAllRelay)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRelayFormView diagnostics

#ifdef _DEBUG
void CRelayFormView::AssertValid() const
{
	CXTMainFormView::AssertValid();
}

void CRelayFormView::Dump(CDumpContext& dc) const
{
	CXTMainFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CRelayFormView message handlers

void CRelayFormView::OnInitialUpdate() 
{
	if(!m_bInitialized)
	{
		CXTMainFormView::OnInitialUpdate();

		m_jpgBackGround.Load(IDR_BACKGROUND);
		
		m_wndRelayList.Create(WS_BORDER|WS_CHILD|WS_VISIBLE|LVS_REPORT|LVS_SHOWSELALWAYS , CRect(0, 0, 0, 0), this, IDC_LIST_RELAY);
		m_wndRelayList.SetExtendedStyle (LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT|LVS_EX_FLATSB);
		
		CString strTitle;
#ifdef LANG_CHINESE 
		strTitle = "名字";
#else
		strTitle = "Name";
#endif	
		m_wndRelayList.InsertColumn(0, strTitle, LVCFMT_LEFT, 0);
#ifdef LANG_CHINESE 
		strTitle = "输入";
#else
		strTitle = "Input";
#endif	
		m_wndRelayList.InsertColumn(1, strTitle, LVCFMT_LEFT, 0);
#ifdef LANG_CHINESE 
		strTitle = "类型";
#else
		strTitle = "Type";
#endif	
		m_wndRelayList.InsertColumn(2, strTitle, LVCFMT_LEFT, 0);
#ifdef LANG_CHINESE 
		strTitle = "状态";
#else
		strTitle = "Status";
#endif	
		m_wndRelayList.InsertColumn(3, strTitle, LVCFMT_LEFT, 0);
#ifdef LANG_CHINESE 
		strTitle = "连接地址";
#else
		strTitle = "URL";
#endif	
		m_wndRelayList.InsertColumn(4, strTitle, LVCFMT_LEFT, 0);
		
#ifdef LANG_CHINESE 
		strTitle = "新建";
#else
		strTitle = "New";
#endif	
		m_btnNewRelay.Create(strTitle, WS_VISIBLE|WS_CHILD|BS_PUSHLIKE, CRect(0, 0, 0, 0), this, IDC_BUTTON_NEWRELAY);
#ifdef LANG_CHINESE 
		strTitle = "删除";
#else
		strTitle = "Delete";
#endif	
		m_btnDelRelay.Create(strTitle, WS_VISIBLE|WS_CHILD|BS_PUSHLIKE, CRect(0, 0, 0, 0), this, IDC_BUTTON_DELRELAY);
#ifdef LANG_CHINESE 
		strTitle = "运行";
#else
		strTitle = "Run";
#endif	
		m_btnRunRelay.Create(strTitle, WS_VISIBLE|WS_CHILD|BS_PUSHLIKE, CRect(0, 0, 0, 0), this, IDC_BUTTON_RUNRELAY);
#ifdef LANG_CHINESE 
		strTitle = "停止";
#else
		strTitle = "Stop";
#endif	
		m_btnStopRelay.Create(strTitle, WS_VISIBLE|WS_CHILD|BS_PUSHLIKE, CRect(0, 0, 0, 0), this, IDC_BUTTON_STOPRELAY);
#ifdef LANG_CHINESE 
		strTitle = "停止全部";
#else
		strTitle = "Stop All";
#endif	
		m_btnStopAllRelay.Create(strTitle, WS_VISIBLE|WS_CHILD|BS_PUSHLIKE, CRect(0, 0, 0, 0), this, IDC_BUTTON_STOPALLRELAY);
	}
	
	RecalcLayout();
}

void CRelayFormView::OnSize(UINT nType, int cx, int cy) 
{
	CXTMainFormView::OnSize(nType, cx, cy);
	
	SetScaleToFitSize(CSize(cx, cy));
	RecalcLayout();
	
}
void CRelayFormView::RecalcLayout()
{
	if(m_bInitialized)
	{
		CRect rc, rcClient;
		GetClientRect(&rcClient);
		rc = rcClient;
		rc.DeflateRect(20, 20);
		rc.right -= 70;
		m_wndRelayList.MoveWindow(&rc);

		rc.left = rc.right + 10;
		rc.right= rc.left + 60;
		rc.bottom = rc.top + 20;
		m_btnNewRelay.MoveWindow(&rc);

		rc.top = rc.bottom + 10;
		rc.bottom = rc.top + 20;
		m_btnDelRelay.MoveWindow(&rc);

		rc.top = rc.bottom + 20;
		rc.bottom = rc.top + 20;
		m_btnRunRelay.MoveWindow(&rc);
		
		rc.top = rc.bottom + 10;
		rc.bottom = rc.top + 20;
		m_btnStopRelay.MoveWindow(&rc);

		rc.top = rc.bottom + 10;
		rc.bottom = rc.top + 20;
		m_btnStopAllRelay.MoveWindow(&rc);
		
		m_wndRelayList.GetWindowRect(&rc);
		int nCX = rc.Width() / 5;
		for(int i = 0; i < 5; i ++)
		{
			if(i == 4 || i == 1)
				m_wndRelayList.SetColumnWidth(i, nCX/2*3);
			else if(i == 2 || i == 3)
				m_wndRelayList.SetColumnWidth(i, nCX/2);
			else
				m_wndRelayList.SetColumnWidth(i, nCX);
		}
		
	}
}
void CRelayFormView::InitSetting(XDLS_Setting *pSetting)
{
	m_pSetting = pSetting;
	RELAY_LIST_IT it = m_pSetting->RelayList.begin();
	for(; it != m_pSetting->RelayList.end(); it++)
	{
		LPXDLS_RelayPoint pRP = *it;
		int nIndex = m_wndRelayList.GetItemCount();
		m_wndRelayList.InsertItem(nIndex, pRP->strName);
		m_wndRelayList.SetItemText(nIndex, 1, pRP->strInput);
		m_wndRelayList.SetItemText(nIndex, 2, "Stopped");
		SocketInfo sockInfo;
		CString strNetStream;
		if(pRP->rt == RelayType_Broadcast)
		{
			if(pRP->strNetProcotol	 == "rtp")
			{
				strNetStream.Format("udp://@%s:%d", 
					pRP->strNetAddress,
					pRP->dwNetNetPort);
			}
			else if(pRP->strNetProcotol	 == "rtsp")
			{
				strNetStream.Format("rtsp://%s:%d/%s.sdp", 
					sockInfo.getIPAddress().c_str(),
					pRP->dwNetRTSPPort,
					pRP->strName);
				
			}
			else
			{
				strNetStream.Format("%s://%s:%d", 
					pRP->strNetProcotol	,
					sockInfo.getIPAddress().c_str(),
					pRP->dwNetNetPort);
				
			}
		}
		m_wndRelayList.SetItemText(nIndex, 4, strNetStream);
		m_wndRelayList.SetItemData(nIndex, (DWORD)pRP);
	}	

}
void CRelayFormView::Server_Run()
{
}
void CRelayFormView::Server_Stop()
{
	OnStopAllRelay();
}
void CRelayFormView::OnTimerWork(UINT nID)
{
	if(nID == TIMERID_ONESECOND)
	{
		CMainFrame *pMainFrm = (CMainFrame*)AfxGetMainWnd();
		
	}
}

void CRelayFormView::Wnd_Active(BOOL bActive)
{
	
}
void CRelayFormView::OnDrawInfo(CDC *pDC)
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

void CRelayFormView::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	OnDrawInfo(&dc);
	
	// Do not call CXTMainFormView::OnPaint() for painting messages
}
void CRelayFormView::OnNewRelay()
{

}
void CRelayFormView::OnDelRelay()
{
	int nSel = m_wndRelayList.GetSelectionMark();
	if(nSel == -1)
		return;
	LPXDLS_RelayPoint pRP = (LPXDLS_RelayPoint)m_wndRelayList.GetItemData(nSel);
	RELAY_LIST_IT it = m_pSetting->RelayList.begin();
	for(; it != m_pSetting->RelayList.end(); it++)
	{
		if(pRP == *it)
		{
			m_pSetting->RelayList.erase(it);
			break;
		}
	}	
	if(pRP->rt == RelayType_Broadcast)
	{
	
	}
	else if(pRP->rt == RelayType_Web)
	{
	}
	delete pRP;
	m_wndRelayList.DeleteItem(nSel);
}
void CRelayFormView::OnRunRelay()
{
	int nSel = m_wndRelayList.GetSelectionMark();
	if(nSel == -1)
		return;

	LPXDLS_RelayPoint pRP = (LPXDLS_RelayPoint)m_wndRelayList.GetItemData(nSel);
	if(pRP->rt == RelayType_Broadcast)
	{

	}
	else if(pRP->rt == RelayType_Web)
	{
	}
}
void CRelayFormView::OnStopRelay()
{
	int nSel = m_wndRelayList.GetSelectionMark();
	if(nSel == -1)
		return;
	LPXDLS_RelayPoint pRP = (LPXDLS_RelayPoint)m_wndRelayList.GetItemData(nSel);
	if(pRP->rt == RelayType_Broadcast)
	{
		
	}
	else if(pRP->rt == RelayType_Web)
	{	
	}
}
void CRelayFormView::OnStopAllRelay()
{
	for(int i = 0; i < m_wndRelayList.GetItemCount(); i ++)
	{
		LPXDLS_RelayPoint pRP = (LPXDLS_RelayPoint)m_wndRelayList.GetItemData(i);
		if(pRP->rt == RelayType_Broadcast)
		{
			
		}
		else if(pRP->rt == RelayType_Web)
		{	
		}
	}
}
void CRelayFormView::EnumChCallBack(char *szName, 
									char *szInput,
								 char *szStatus,
								 char *szSrcType,
								 int nBitrate,
								 char* szDesc,
								 char *szStreamPath,
								 char *IDStr,
								 void *pChCookie,
								 void *pContext)
{
	reinterpret_cast<CRelayFormView*>(pContext)->OnEnumChCallBack(szName, szInput, szStatus, szSrcType, nBitrate, 
		szDesc, szStreamPath, IDStr, pChCookie);
}
void CRelayFormView::OnEnumChCallBack(char *szName, 
									  char *szInput,
								   char *szStatus,
								   char *szSrcType,
								   int nBitrate,
								   char* szDesc,
								   char *szStreamPath,
								   char *IDStr,
								   void *pChCookie)
{
	CMainFrame *pMainFrm = (CMainFrame*)AfxGetMainWnd();
	if(pMainFrm)
	{
		BOOL bFind = FALSE;
		for(int i = 0; i < m_wndRelayList.GetItemCount(); i ++)
		{
			LPXDLS_RelayPoint pRP = (LPXDLS_RelayPoint)m_wndRelayList.GetItemData(i);
			if(pRP && pRP->rt == RelayType_Web)
				if(pRP->pRelayPoint == pChCookie)
				{
					bFind = TRUE;
					break;
				}
		}	
		if(!bFind)
		{
			LPXDLS_RelayPoint pRP = new XDLS_RelayPoint;
			pRP->strName = szName;
			pRP->strInput= szInput;
			pRP->rt		 = RelayType_Web;
			pRP->dwNetNetPort				= 0;
			pRP->dwNetRTSPPort				= 0;
			
			pRP->strWebSourceType			= szSrcType;
			pRP->strWebDescription			= szDesc;
			pRP->strWebRelayID				= IDStr;
			pRP->dwWebRelayBitrate			= nBitrate;
			
			pRP->pRelayPoint				= NULL;
			m_pSetting->RelayList.push_back(pRP);
			
			int nIndex = m_wndRelayList.GetItemCount();
			m_wndRelayList.InsertItem(nIndex, pRP->strName);
			m_wndRelayList.SetItemData(nIndex, (DWORD)pRP);
			m_wndRelayList.SetItemText(nIndex, 1, pRP->strInput);
			m_wndRelayList.SetItemText(nIndex, 2, pRP->rt == RelayType_Broadcast? "Broadcast" : "Web");
			m_wndRelayList.SetItemText(nIndex, 3, szStatus);
			SocketInfo sockInfo;
			CString strNetStream;
			{
				strNetStream.Format("%s?tip=%s:%d",
					pRP->strWebRelayID,
					sockInfo.getIPAddress().c_str(),
					m_pSetting->nWebServerPort);
			}
			m_wndRelayList.SetItemText(nIndex, 4, strNetStream);
		}
		else
		{

		}
	}
}

void CRelayFormView::WebOnNewRelay(int type,LPVOID params)
{

	
}

CString CRelayFormView::GetParamValue(CString ParamName, CString lpBuf)
{
	CString str;
	int nLen;
	int nTmp;
	str = lpBuf;
	nTmp = str.Find(ParamName);
	if( nTmp == -1)
		return "NoThisParam";
	else
	{

		nLen = str.GetLength();
		str = str.Right(nLen-nTmp);
		str = str.Left(str.Find("\r\n"));
		str.Replace(ParamName+"=","");
	}
	return str;
}

BOOL CRelayFormView::WebOnDelRelay(CString strName)
{
	int nCur = -1;
	for(int i=0; i<m_wndRelayList.GetItemCount();i++)
	{
		if(m_wndRelayList.GetItemText(i,0) == strName)
		{
			nCur = i;
			break;
		}
	}
	if(nCur == -1)
	{
		return FALSE;
	}
	LPXDLS_RelayPoint pRP = (LPXDLS_RelayPoint)m_wndRelayList.GetItemData(nCur);
	RELAY_LIST_IT it = m_pSetting->RelayList.begin();
	for(; it != m_pSetting->RelayList.end(); it++)
	{
		if(pRP == *it)
		{
			m_pSetting->RelayList.erase(it);
			break;
		}
	}	
	if(pRP->rt == RelayType_Broadcast)
	{
		
	}
	else if(pRP->rt == RelayType_Web)
	{
	}
	delete pRP;
	m_wndRelayList.DeleteItem(nCur);
	return TRUE;
}

BOOL CRelayFormView::WebOnModify(LPVOID params)
{
	return FALSE;	
}

CString CRelayFormView::WebOnGetRelayList()
{
	return "";
}
