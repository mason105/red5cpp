// PerfomanceView.cpp : implementation file
//

#include "stdafx.h"
#include "XDigitalLifeServerApp.h"
#include "PerfomanceView.h"
#include "Mainfrm.h"
#include "SysUtils.h"
#include <sstream>
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPerfomanceView

#define XDLSERVER_VER	"1.0.0.0"

IMPLEMENT_DYNCREATE(CPerfomanceView, CView)

CPerfomanceView::CPerfomanceView()
{
	m_bInitialized = FALSE;
	m_bWndActive   = FALSE;
	m_pSetting = NULL;

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

CPerfomanceView::~CPerfomanceView()
{
}


BEGIN_MESSAGE_MAP(CPerfomanceView, CView)
	//{{AFX_MSG_MAP(CPerfomanceView)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPerfomanceView drawing

void CPerfomanceView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	OnDrawInfo(pDC);
}

/////////////////////////////////////////////////////////////////////////////
// CPerfomanceView diagnostics

#ifdef _DEBUG
void CPerfomanceView::AssertValid() const
{
	CView::AssertValid();
}

void CPerfomanceView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPerfomanceView message handlers

void CPerfomanceView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	RecalcLayout();
	
}
void CPerfomanceView::RecalcLayout()
{
	if(m_bInitialized)
	{

	}
}

void CPerfomanceView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();
	
	if(!m_bInitialized)
	{

		TCHAR szBuffer[512];
		DWORD dwBufferSize = 512;
		GetComputerName(szBuffer, &dwBufferSize);
		m_strComputerName = szBuffer;	
		UpdateSystemInfo();

		m_jpgBackGround.Load(IDR_BACKGROUND);
		m_bInitialized = TRUE;
	}
	RecalcLayout();
	
}
void CPerfomanceView::InitSetting(XDLS_Setting *pSetting)
{
	m_pSetting = pSetting;
	m_strBaseDisk = pSetting->szVODFilePath;
	m_strBaseDisk = m_strBaseDisk.Left(sizeof(TCHAR) * 3);
}
void CPerfomanceView::Server_Run()
{
	m_strBaseDisk = m_pSetting->szVODFilePath;
	m_strBaseDisk = m_strBaseDisk.Left(sizeof(TCHAR) * 3);
	
}
void CPerfomanceView::Server_Stop()
{
}
void CPerfomanceView::OnTimerWork(UINT nID)
{
	if(nID == TIMERID_TWOSECOND && m_bWndActive)
	{
		UpdateSystemInfo();
		CClientDC dc(this);
		OnDrawInfo(&dc);
	}
}
void CPerfomanceView::OnDrawInfo(CDC *pDC)
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

	rc.left = rcClient.left;
	rc.top	= rcClient.top + Frame_Height * 2;
	rc.right= rc.left + rcClient.Width() / 2 - Frame_Height * 2;
	rc.bottom= rc.top + Frame_Height;
	dc.SelectObject(&m_wideFont);
	CString strTitle;
#ifdef LANG_CHINESE 
	strTitle = "服务器:";
#else
	strTitle = "Server:";
#endif	
	dc.DrawText(strTitle, &rc, DT_RIGHT|DT_VCENTER);
	rc.left = rc.right + Frame_Height;
	rc.right= rcClient.right;
	dc.SelectObject(&m_thinFont);
	dc.DrawText(m_strComputerName, &rc, DT_LEFT|DT_VCENTER);
	
	rc.left = rcClient.left;
	rc.top	= rc.bottom + Frame_Height;
	rc.right= rc.left + rcClient.Width() / 2- Frame_Height * 2;
	rc.bottom= rc.top + Frame_Height;
	dc.SelectObject(&m_wideFont);
#ifdef LANG_CHINESE 
	strTitle = "状态:";
#else
	strTitle = "Status:";
#endif	
	dc.DrawText(strTitle, &rc, DT_RIGHT|DT_VCENTER);
	rc.left = rc.right + Frame_Height;
	rc.right= rcClient.right;
	dc.SelectObject(&m_thinFont);
	dc.DrawText(m_strStatus, &rc, DT_LEFT|DT_VCENTER);

	rc.left = rcClient.left;
	rc.top	= rc.bottom + Frame_Height;
	rc.right= rc.left + rcClient.Width() / 2- Frame_Height * 2;
	rc.bottom= rc.top + Frame_Height;
	dc.SelectObject(&m_wideFont);
#ifdef LANG_CHINESE 
	strTitle = "系统时间:";
#else
	strTitle = "Current Time On Server:";
#endif	
	dc.DrawText(strTitle, &rc, DT_RIGHT|DT_VCENTER);
	rc.left = rc.right + Frame_Height;
	rc.right= rcClient.right;
	dc.SelectObject(&m_thinFont);
	dc.DrawText(m_strNowTime, &rc, DT_LEFT|DT_VCENTER);

	rc.left = rcClient.left;
	rc.top	= rc.bottom + Frame_Height;
	rc.right= rc.left + rcClient.Width() / 2- Frame_Height * 2;
	rc.bottom= rc.top + Frame_Height;
	dc.SelectObject(&m_wideFont);
#ifdef LANG_CHINESE 
	strTitle = "版本:";
#else
	strTitle = "Server Version:";
#endif	
	dc.DrawText(strTitle, &rc, DT_RIGHT|DT_VCENTER);
	rc.left = rc.right + Frame_Height;
	rc.right= rcClient.right;
	dc.SelectObject(&m_thinFont);
	dc.DrawText(XDLSERVER_VER, &rc, DT_LEFT|DT_VCENTER);

	rc.left = rcClient.left;
	rc.top	= rc.bottom + Frame_Height;
	rc.right= rc.left + rcClient.Width() / 2- Frame_Height * 2;
	rc.bottom= rc.top + Frame_Height;
	dc.SelectObject(&m_wideFont);
#ifdef LANG_CHINESE 
	strTitle = "CPU 使用:";
#else
	strTitle = "CPU Load:";
#endif	
	dc.DrawText(strTitle, &rc, DT_RIGHT|DT_VCENTER);
	rc.left = rc.right + Frame_Height;
	rc.right= rcClient.right;
	dc.SelectObject(&m_thinFont);
	dc.DrawText(m_strCPUUsage, &rc, DT_LEFT|DT_VCENTER);

	rc.left = rcClient.left;
	rc.top	= rc.bottom + Frame_Height;
	rc.right= rc.left + rcClient.Width() / 2- Frame_Height * 2;
	rc.bottom= rc.top + Frame_Height;
	dc.SelectObject(&m_wideFont);
#ifdef LANG_CHINESE 
	strTitle = "内存使用:";
#else
	strTitle = "Mem Usage:";
#endif	
	dc.DrawText(strTitle, &rc, DT_RIGHT|DT_VCENTER);
	rc.left = rc.right + Frame_Height;
	rc.right= rcClient.right;
	dc.SelectObject(&m_thinFont);
	dc.DrawText(m_strMemUsage, &rc, DT_LEFT|DT_VCENTER);

	rc.left = rcClient.left;
	rc.top	= rc.bottom + Frame_Height;
	rc.right= rc.left + rcClient.Width() / 2- Frame_Height * 2;
	rc.bottom= rc.top + Frame_Height;
	dc.SelectObject(&m_wideFont);
#ifdef LANG_CHINESE 
	strTitle = "点播磁盘剩余空间:";
#else
	strTitle = "Remain VOD-Disk Space:";
#endif	
	dc.DrawText(strTitle, &rc, DT_RIGHT|DT_VCENTER);
	rc.left = rc.right + Frame_Height;
	rc.right= rcClient.right;
	dc.SelectObject(&m_thinFont);
	dc.DrawText(m_strRemainDiskSpace, &rc, DT_LEFT|DT_VCENTER);

	rc.left = rcClient.left;
	rc.top	= rc.bottom + Frame_Height;
	rc.right= rc.left + rcClient.Width() / 2- Frame_Height * 2;
	rc.bottom= rc.top + Frame_Height;
	dc.SelectObject(&m_wideFont);
#ifdef LANG_CHINESE 
	strTitle = "连接数目:";
#else
	strTitle = "Current # of Connections:";
#endif	
	dc.DrawText(strTitle, &rc, DT_RIGHT|DT_VCENTER);
	rc.left = rc.right + Frame_Height;
	rc.right= rcClient.right;
	dc.SelectObject(&m_thinFont);
	dc.DrawText(m_strCurrentofConnections, &rc, DT_LEFT|DT_VCENTER);

	dc.SetBkMode(oldBkMode);
	dc.SelectObject(pOldFont);
}
void CPerfomanceView::UpdateSystemInfo()
{
	CMainFrame *pMainFrm = (CMainFrame*)AfxGetMainWnd();

	long cpuusage = 0;
	m_CpuUsage.GetCpuUsage(&cpuusage);
	m_strCPUUsage.Format("%d%%", cpuusage);
	
	m_sysInfo.determineSysInfo();
	
	DWORD dwAvailPageFile = 0;
	DWORD dwTotalPageFile = 0;
	m_sysInfo.mem_getAvailPageFile(&dwAvailPageFile);
	m_sysInfo.mem_getTotalPageFile(&dwTotalPageFile);
	dwAvailPageFile = dwTotalPageFile - dwAvailPageFile;
	ostringstream os1, os2;
	os1 << SysUtils::ByteToStr(dwAvailPageFile + MemoryInfo::MEMORY_OFFSET);
	os2 << SysUtils::ByteToStr(dwTotalPageFile + MemoryInfo::MEMORY_OFFSET);
	
	m_strMemUsage.Format("%s/%s", 
		os1.str().c_str(), 
		os2.str().c_str());
	
	const vector<DriveStats>& rvDriveStats = m_sysInfo.getDriveStats();
	for (vector<DriveStats>::const_iterator i = rvDriveStats.begin();
	i != rvDriveStats.end(); ++i)
	{
		if(stricmp((LPCSTR)m_strBaseDisk, i->getName().c_str()) == 0)
		{
			m_strRemainDiskSpace.Format("%s/%s", i->getFreeSpace().c_str(), i->getTotalSpace().c_str());
			break;
		}
	}
		
	if(pMainFrm)
		m_strStatus = pMainFrm->XFLVServer_Ptr() ? "Running" : "Stopped";
	else
		m_strStatus = "Stopped";

	m_strNowTime = CTime::GetCurrentTime().Format("%A, %B %d, %Y %H:%m:%S");

	if(pMainFrm)
		m_strCurrentofConnections.Format("%d", pMainFrm->Helper_GetCurrentofConnections());
	else
		m_strCurrentofConnections = "0";
}
void CPerfomanceView::Wnd_Active(BOOL bActive)
{
	m_bWndActive = bActive;	
}