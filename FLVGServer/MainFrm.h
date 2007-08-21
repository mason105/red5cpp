// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__F76F66F5_B040_44F2_92D9_5D3BC35D2C33__INCLUDED_)
#define AFX_MAINFRM_H__F76F66F5_B040_44F2_92D9_5D3BC35D2C33__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "ControlPropertiesTreeCtrl.h"
#include "XDLSplitterWnd.h"
#include "VODFilesFormView.h"
#include "RelayFormView.h"
#include "PerfomanceView.h"
#include "PublishPointFormView.h"
#include "ConnectionFormView.h"
#include "SettingFormView.h"
#include "LogFormView.h"
#include "Dog.h"
#include "GHttpServer.h"

class CControlFrameWnd;
class CMainFrame : public CXTMainFrm
{
	
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:
	CXTPDockingPaneManager m_paneManager;
	CXTPDockingPaneManager* GetDockingPaneManager() {
		return &m_paneManager;
	}
	void OnUDPDataHandleCallBack(sockaddr* from,
		char * pData,
		unsigned long DataLength);
// Operations
public:
	static void DefaultXDLSSetting(XDLS_Setting *pSetting);
	
	BOOL		InitializeCaptionBar();
	int			Helper_GetCurrentofConnections();
	virtual void GetWindowTitle (CString& rString);
	void		ExpandPaneTree(BOOL bExpand);

	FLVServer*	XFLVServer_Ptr(){
		return _FLVServer;
	}
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	//}}AFX_VIRTUAL

// Implementation
public:
	CString m_strBindIP;
	CString m_strOutWindowText;
	BOOL IsInited;
	void Run(){OnRun();}
	void Stop(){OnStop();}
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
public:  // control bar embedded members
	CString					strStartTime;
	CToolBar				m_wndToolBar;
	CControlPropertiesTreeCtrl m_wndControlPropertiesTreeCtrl;
	CImageList				m_ilTreeIcons;
	

	CXTCaption				m_wndCaption;
	CFont					m_fontCaption;

	CXDLSplitterWnd			m_wndSplitterCaption;
	CControlFrameWnd*		m_pControlFrameWnd;
	
	CPerfomanceView*		m_pPerfomanceView;
	CPublishPointFormView*	m_pPublishPointFormView;
	CVODFilesFormView*		m_pVODFilesFormView;
	CRelayFormView*			m_pRelayFormView;
	CConnectionFormView*	m_pConnectionFormView;
	CSettingFormView*		m_pSettingFormView;
	CLogFormView*			m_pLogFormView;
	
	CWnd*					m_pActiveView;
	 XDLS_Setting			m_XDLS_Setting;

	 FLVServer*				_FLVServer;
	 GHttpServer			_HttpServer;
public:
	void OnDelFile();
	void WatchVODPath();

	 void OnStop_inner();

	void OnFtpNewFile(LPVOID params);
// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnGetMinMaxInfo (MINMAXINFO FAR* lpMMI);
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnRun();
	afx_msg void OnUpdateRun(CCmdUI* pCmdUI);
	afx_msg void OnStop();
	afx_msg void OnUpdateStop(CCmdUI* pCmdUI);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnClose();
	afx_msg void OnNcPaint();
	afx_msg BOOL OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct);
	//}}AFX_MSG
	afx_msg LRESULT OnDockingPaneNotify (WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnControlPropertiesTreeSelected (WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnGetOut (WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__F76F66F5_B040_44F2_92D9_5D3BC35D2C33__INCLUDED_)
