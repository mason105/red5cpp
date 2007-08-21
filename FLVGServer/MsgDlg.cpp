// MsgDlg.cpp : implementation file
//

#include "stdafx.h"
#include "XDigitalLifeServerApp.h"
#include "MsgDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMsgDlg dialog


CMsgDlg::CMsgDlg(CString strMsg, CWnd* pParent /*=NULL*/)
	: CXTMainDlg(CMsgDlg::IDD, pParent),
	m_strMessage(strMsg)
{
	//{{AFX_DATA_INIT(CMsgDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CMsgDlg::DoDataExchange(CDataExchange* pDX)
{
	CXTMainDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMsgDlg)
	DDX_Control(pDX, IDCANCEL, m_btnCancel);
	DDX_Control(pDX, IDOK, m_btnOK);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMsgDlg, CXTMainDlg)
	//{{AFX_MSG_MAP(CMsgDlg)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMsgDlg message handlers

void CMsgDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	CRect rc;
	GetClientRect(&rc);

	CXTPBufferDC MDC(dc, rc);
	MDC.FillSolidRect(&rc, RGB(221, 221, 221));
	int oldBkMode = MDC.SetBkMode(TRANSPARENT);
	rc.top += 20;
	MDC.DrawText(m_strMessage, &rc, DT_CENTER|DT_VCENTER);
	MDC.SetBkMode(oldBkMode);
	// Do not call CXTMainDlg::OnPaint() for painting messages
}


BOOL CMsgDlg::OnInitDialog() 
{
	CXTMainDlg::OnInitDialog();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
int		XDLCMessageBox(CString strMsg, int nType)
{
	CMsgDlg dlg(strMsg);
	return dlg.DoModal();
}
