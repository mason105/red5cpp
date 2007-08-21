// SettingVODDlg.cpp : implementation file
//

#include "stdafx.h"
#include "xdigitallifeserverapp.h"
#include "SettingVODDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSettingVODDlg dialog


CSettingVODDlg::CSettingVODDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSettingVODDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSettingVODDlg)
	m_dwVODPort = 554;
	m_strVODFilePath = _T("");
	m_strVODAddress = _T("0.0.0.0");
	//}}AFX_DATA_INIT
	m_pItem = NULL;
	m_pSetting = NULL;
}


void CSettingVODDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSettingVODDlg)
	DDX_Control(pDX, IDC_EDIT_VODPORT, m_editVODPort);
	DDX_Control(pDX, IDC_EDIT_VODFILEPATH, m_editVODFilePath);
	DDX_Control(pDX, IDC_EDIT_VODADDRESS, m_editVODAddress);
	DDX_Control(pDX, IDC_BUTTON_BROWSH, m_btnBrowsh);
	DDX_Text(pDX, IDC_EDIT_VODPORT, m_dwVODPort);
	DDV_MinMaxDWord(pDX, m_dwVODPort, 0, 20000);
	DDX_Text(pDX, IDC_EDIT_VODFILEPATH, m_strVODFilePath);
	DDX_Text(pDX, IDC_EDIT_VODADDRESS, m_strVODAddress);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSettingVODDlg, CDialog)
	//{{AFX_MSG_MAP(CSettingVODDlg)
		ON_WM_SIZE()
		ON_WM_ERASEBKGND()
		ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON_BROWSH, OnButtonBrowsh)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSettingVODDlg message handlers
void CSettingVODDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
	
	Invalidate(FALSE);
	
}

void CSettingVODDlg::UpdateColors()
{
	if (!m_pItem)
		return;
	
	COLORREF clrBack = m_pItem->GetBackColor();
	
	if (!m_brushBack.GetSafeHandle() || clrBack != m_clrBack)
	{
		m_brushBack.DeleteObject();
		m_brushBack.CreateSolidBrush(clrBack);
		m_clrBack = clrBack;
	}
}


BOOL CSettingVODDlg::OnEraseBkgnd(CDC* pDC)
{
	UpdateColors();
	
	pDC->FillSolidRect(CXTPClientRect(this), m_clrBack);
	
	return TRUE;
}

HBRUSH CSettingVODDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	if (nCtlColor != CTLCOLOR_BTN && nCtlColor !=CTLCOLOR_STATIC)
		return CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	UpdateColors();
	pDC->SetBkMode(TRANSPARENT);
	
	return m_brushBack;
}

void CSettingVODDlg::OnButtonBrowsh() 
{
	CXTBrowseDialog dlg(this);
	dlg.SetSelPath((LPSTR)(LPCSTR)m_strVODFilePath);
	if(dlg.DoModal())
	{
		m_strVODFilePath = dlg.GetSelPath();
		UpdateData(FALSE);
	}
	
}

BOOL CSettingVODDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void CSettingVODDlg::InitSetting(XDLS_Setting *pSetting)
{
	m_pSetting = pSetting;
	m_strVODFilePath = m_pSetting->szVODFilePath;
	m_dwVODPort		 = m_pSetting->nServerPort;
	m_strVODAddress	 = m_pSetting->szServerAddress;
	if(m_editVODPort.m_hWnd)
	{
		UpdateData(FALSE);
	}
}
void CSettingVODDlg::ApplySetting(XDLS_Setting *pSetting)
{
	m_pSetting = pSetting;
	if(m_editVODPort.m_hWnd)
	{
		UpdateData(TRUE);
		strcpy(m_pSetting->szVODFilePath, (LPCSTR)m_strVODFilePath);
		m_pSetting->nServerPort = m_dwVODPort;
		strcpy(m_pSetting->szServerAddress, (LPCSTR)m_strVODAddress);
	}
}