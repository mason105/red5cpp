// XDLShellTree.cpp : implementation file
//

#include "stdafx.h"
#include "XDigitalLifeServerApp.h"
#include "XDLShellTree.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CXDLShellTree

CXDLShellTree::CXDLShellTree()
{
}

CXDLShellTree::~CXDLShellTree()
{
}


BEGIN_MESSAGE_MAP(CXDLShellTree, CXTShellTreeCtrl)
	//{{AFX_MSG_MAP(CXDLShellTree)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CXDLShellTree message handlers
CString CXDLShellTree::SetRootPath(CString strRootPath)
{
	CString strOld = m_strRootPath;
	m_strRootPath = strRootPath;
	EnableAutoInit(TRUE);
	DelayContentInit();
	TunnelTree(strRootPath);

	return strOld;
}
