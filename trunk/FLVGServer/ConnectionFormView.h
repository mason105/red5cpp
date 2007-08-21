#if !defined(AFX_CONNECTIONFORMVIEW_H__8D629856_4EBC_462F_A2EE_395317549736__INCLUDED_)
#define AFX_CONNECTIONFORMVIEW_H__8D629856_4EBC_462F_A2EE_395317549736__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ConnectionFormView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CConnectionFormView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CConnectionFormView : public CXTMainFormView
{
protected:
	CConnectionFormView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CConnectionFormView)

	
	virtual ULONG STDMETHODCALLTYPE AddRef( void){return 1;}
	virtual ULONG STDMETHODCALLTYPE Release( void){return 0;}
	virtual HRESULT STDMETHODCALLTYPE RtspClientNew(unsigned char *psz_session ,
		unsigned char* ip, int i_client_port,
		unsigned char* psz_rtsp_path,
		unsigned int nCookie);
	virtual HRESULT STDMETHODCALLTYPE RtspClientDel(unsigned int nCookie);
	
// Form Data
public:
	//{{AFX_DATA(CConnectionFormView)
	enum { IDD = IDD_DIALOG_CONNECTION };
	CXTListCtrl	m_wndConnectList;
	//}}AFX_DATA

// Attributes
public:
	XDLS_Setting *m_pSetting;
	CPicture	m_jpgBackGround;
	// Operations
public:
	void RecalcLayout();
	void InitSetting(XDLS_Setting *pSetting);
	void Server_Run();
	void Server_Stop();
	void Wnd_Active(BOOL bActive);
	void OnTimerWork(UINT nID);
	void OnDrawInfo(CDC *pDC);
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConnectionFormView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CConnectionFormView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CConnectionFormView)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONNECTIONFORMVIEW_H__8D629856_4EBC_462F_A2EE_395317549736__INCLUDED_)
