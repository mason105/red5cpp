// ControlPropertiesTreeCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "XDigitalLifeServerApp.h"
#include "ControlPropertiesTreeCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CControlPropertiesTreeCtrl

CControlPropertiesTreeCtrl::CControlPropertiesTreeCtrl()
{
}

CControlPropertiesTreeCtrl::~CControlPropertiesTreeCtrl()
{
}


BEGIN_MESSAGE_MAP(CControlPropertiesTreeCtrl, CXTTreeCtrl)
	//{{AFX_MSG_MAP(CControlPropertiesTreeCtrl)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		ON_NOTIFY_REFLECT(TVN_SELCHANGED, OnSelchanged)
		//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CControlPropertiesTreeCtrl message handlers
void CControlPropertiesTreeCtrl::OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	
	AfxGetMainWnd()->SendMessage(WM_CONTROLPROPERTIESTREE_SELECTED, (WPARAM)pNMHDR);
	
	*pResult = 0;
}
