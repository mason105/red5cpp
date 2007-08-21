#if !defined(AFX_RELAYFORMVIEW_H__FB80F14D_9FBA_4EE8_B4CD_43B129ACE75C__INCLUDED_)
#define AFX_RELAYFORMVIEW_H__FB80F14D_9FBA_4EE8_B4CD_43B129ACE75C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RelayFormView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRelayFormView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CRelayFormView : public CXTMainFormView
{
protected:
	CRelayFormView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CRelayFormView)

// Form Data
public:
	//{{AFX_DATA(CRelayFormView)
	enum { IDD = IDD_DIALOG_RELAY };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

// Attributes
public:
	XDLS_Setting *m_pSetting;
	CPicture	m_jpgBackGround;
	CXTListCtrl m_wndRelayList;
	CXTButton	m_btnNewRelay;
	CXTButton	m_btnDelRelay;
	CXTButton	m_btnRunRelay;
	CXTButton	m_btnStopRelay;
	CXTButton	m_btnStopAllRelay;
	// Operations
public:
	CString WebOnGetRelayList();
	BOOL WebOnModify(LPVOID params);
	BOOL WebOnDelRelay(CString strName);
	CString GetParamValue(CString ParamName,CString lpBuf);
	void WebOnNewRelay(int type,LPVOID params);
	void InitSetting(XDLS_Setting *pSetting);	
	void Server_Run();
	void Server_Stop();
	void Wnd_Active(BOOL bActive);
	void OnDrawInfo(CDC *pDC);
	void OnTimerWork(UINT nID);
	
	void RecalcLayout();
	static void EnumChCallBack(char *szName, 
		char *szInput,
		char *szStatus,
		char *szSrcType,
		int nBitrate,
		char* szDesc,
		char *szStreamPath,
		char *IDStr,
		void *pChCookie,
		void *pContext);
	void OnEnumChCallBack(char *szName, 
		char *szInput,
		char *szStatus,
		char *szSrcType,
		int nBitrate,
		char* szDesc,
		char *szStreamPath,
		char *IDStr,
		void *pChCookie);
	
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRelayFormView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CRelayFormView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CRelayFormView)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	//}}AFX_MSG
	afx_msg void OnNewRelay();
	afx_msg void OnDelRelay();
	afx_msg void OnRunRelay();
	afx_msg void OnStopRelay();
	afx_msg void OnStopAllRelay();
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RELAYFORMVIEW_H__FB80F14D_9FBA_4EE8_B4CD_43B129ACE75C__INCLUDED_)
