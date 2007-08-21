// XDigitalLifeServerApp.h : main header file for the XDIGITALLIFESERVERAPP application
//

#if !defined(AFX_XDIGITALLIFESERVERAPP_H__9A919FF5_E4EB_46AB_9F1D_D79EEECFFEC4__INCLUDED_)
#define AFX_XDIGITALLIFESERVERAPP_H__9A919FF5_E4EB_46AB_9F1D_D79EEECFFEC4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CXDigitalLifeServerAppApp:
// See XDigitalLifeServerApp.cpp for the implementation of this class
//

class CXDigitalLifeServerAppApp : public CWinApp
{
public:
	CXDigitalLifeServerAppApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXDigitalLifeServerAppApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CXDigitalLifeServerAppApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	virtual int ExitInstance();
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XDIGITALLIFESERVERAPP_H__9A919FF5_E4EB_46AB_9F1D_D79EEECFFEC4__INCLUDED_)
