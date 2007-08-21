// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__498F7653_B63D_4B1A_BE2A_C0BB67DE4E98__INCLUDED_)
#define AFX_STDAFX_H__498F7653_B63D_4B1A_BE2A_C0BB67DE4E98__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers
#define   _WIN32_WINNT   0x0500  
#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT
#include <comutil.h>
#include <atlbase.h>
#include "afxsock.h"

#include <XTToolkitPro.h>

#include "XTMainFrm.h"
#include "XDLTheme.h"
#include "XDigitalLifeServerAppDef.h"
#include "JPGPicture.h"
#include "../FLVLibrary/FLVServer.h"
#include "../FLVLibrary/FLVPlatform.h"

#define LANG_ENGLISH
#undef  LANG_CHINESE
#define WM_NEW_FILE WM_USER+100
// #pragma   comment(linker,   "/FORCE:MULTIPLE")

//{{AFX_INSERT_LOCATION}}

#endif // !defined(AFX_STDAFX_H__498F7653_B63D_4B1A_BE2A_C0BB67DE4E98__INCLUDED_)
