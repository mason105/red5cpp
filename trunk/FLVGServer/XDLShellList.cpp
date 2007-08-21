// XDLShellList.cpp : implementation file
//

#include "stdafx.h"
#include "XDigitalLifeServerApp.h"
#include "XDLShellList.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CXDLShellList

CXDLShellList::CXDLShellList()
{
}

CXDLShellList::~CXDLShellList()
{
}


BEGIN_MESSAGE_MAP(CXDLShellList, CXTShellListCtrl)
	//{{AFX_MSG_MAP(CXDLShellList)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CXDLShellList message handlers
void CXDLShellList::RefreshList()
{
	if ( !m_pTreeCtrl || !::IsWindow( m_pTreeCtrl->m_hWnd ) )
		return;
	
	CTreeCtrl* pTreeCtrl = ( CTreeCtrl* )m_pTreeCtrl;
	if ( !pTreeCtrl->IsKindOf( RUNTIME_CLASS( CTreeCtrl ) ) )
		return;
	
	HTREEITEM hItem = pTreeCtrl->GetSelectedItem( );
	if ( !hItem )
		return;
	
	CObject* pObject = ( CObject* )pTreeCtrl->GetItemData( hItem );
	if ( !pObject )
		return;
	
	SendMessage( XTWM_SHELL_NOTIFY,
		( WPARAM )SHN_XT_TREESELCHANGE, ( LPARAM )pObject );
}

void CXDLShellList::OnShowContextMenu(int idCmd, CMINVOKECOMMANDINFO& cmi)
{
	UNREFERENCED_PARAMETER(idCmd);
	UNREFERENCED_PARAMETER(cmi);
	
	// Refresh list if items were deleted.
	if ( idCmd == 17 )
	{
		RefreshList( );
	}
}
