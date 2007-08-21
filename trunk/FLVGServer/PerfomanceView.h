#if !defined(AFX_PERFOMANCEVIEW_H__A5FBE1F5_2BFA_4DFE_9613_738465096C30__INCLUDED_)
#define AFX_PERFOMANCEVIEW_H__A5FBE1F5_2BFA_4DFE_9613_738465096C30__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PerfomanceView.h : header file
//
#include "SysInfo.h"
#include "cpuusage.h"
#include <string>
#include "JPGPicture.h"
/////////////////////////////////////////////////////////////////////////////
// CPerfomanceView view

class CPerfomanceView : public CView
{
protected:
	CPerfomanceView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CPerfomanceView)

// Attributes
public:
	BOOL m_bInitialized;
	XDLS_Setting *m_pSetting;

	SysInfo m_sysInfo;
	CCpuUsage m_CpuUsage;
	
	CString m_strComputerName;
	CString m_strStatus;
	CString m_strNowTime;
	CString m_strMemUsage;
	CString m_strCPUUsage;
	CString m_strRemainDiskSpace;
	CString m_strCurrentofConnections;
	CString m_strBaseDisk;

	CPicture	m_jpgBackGround;
	CFont		m_wideFont;
	CFont		m_thinFont;

	BOOL		m_bWndActive;
	// Operations
public:
	void RecalcLayout();
	void InitSetting(XDLS_Setting *pSetting);	
	void Server_Run();
	void Server_Stop();
	void Wnd_Active(BOOL bActive);
	void OnTimerWork(UINT nID);

	void OnDrawInfo(CDC *pDC);

	void UpdateSystemInfo();
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPerfomanceView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CPerfomanceView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CPerfomanceView)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PERFOMANCEVIEW_H__A5FBE1F5_2BFA_4DFE_9613_738465096C30__INCLUDED_)
