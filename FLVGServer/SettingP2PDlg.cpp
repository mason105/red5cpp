// SettiingWebDlg.cpp : implementation file
//

#include "stdafx.h"
#include "xdigitallifeserverapp.h"
#include "Settingp2pDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSettingWebDlg dialog


CSettingWebDlg::CSettingWebDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSettingWebDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSettingWebDlg)
	m_dwWebMaxOutputBitrate = 0;
	m_dwWebMaxRelays = 5000;
	m_dwWebPort = 7144;
	//}}AFX_DATA_INIT
	m_pItem = NULL;
	m_pSetting = NULL;
}


void CSettingWebDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSettingWebDlg)
	DDX_Control(pDX, IDC_EDIT_WebPORT, m_editWebPort);
	DDX_Control(pDX, IDC_EDIT_WebMAXRELAYS, m_editWebMaxRelays);
	DDX_Control(pDX, IDC_EDIT_WebMAXOUTPUTBITRATE, m_editWebMaxOutputBitrate);
	DDX_Text(pDX, IDC_EDIT_WebMAXOUTPUTBITRATE, m_dwWebMaxOutputBitrate);
	DDX_Text(pDX, IDC_EDIT_WebMAXRELAYS, m_dwWebMaxRelays);
	DDX_Text(pDX, IDC_EDIT_WebPORT, m_dwWebPort);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSettingWebDlg, CDialog)
	//{{AFX_MSG_MAP(CSettingWebDlg)
		// NOTE: the ClassWizard will add message map macros here
		ON_WM_SIZE()
		ON_WM_ERASEBKGND()
		ON_WM_CTLCOLOR()
		//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSettingWebDlg message handlers
void CSettingWebDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
	
	Invalidate(FALSE);
	
}

void CSettingWebDlg::UpdateColors()
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


BOOL CSettingWebDlg::OnEraseBkgnd(CDC* pDC)
{
	UpdateColors();
	
	pDC->FillSolidRect(CXTPClientRect(this), m_clrBack);
	
	return TRUE;
}

HBRUSH CSettingWebDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	if (nCtlColor != CTLCOLOR_BTN && nCtlColor !=CTLCOLOR_STATIC)
		return CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	UpdateColors();
	pDC->SetBkMode(TRANSPARENT);
	
	return m_brushBack;
}



BOOL CSettingWebDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
void CSettingWebDlg::InitSetting(XDLS_Setting *pSetting)
{
	m_pSetting = pSetting;
	m_dwWebPort = m_pSetting->nWebServerPort;
	m_dwWebMaxRelays		 = m_pSetting->nWebMaxRelays;
	m_dwWebMaxOutputBitrate	 = m_pSetting->nWebMaxOutputBitrate;
	if(m_editWebPort.m_hWnd)
	{
		UpdateData(FALSE);
	}
}
void CSettingWebDlg::ApplySetting(XDLS_Setting *pSetting)
{
	m_pSetting = pSetting;
	if(m_editWebPort.m_hWnd)
	{
		UpdateData(TRUE);
		m_pSetting->nWebServerPort = m_dwWebPort;
		m_pSetting->nWebMaxRelays = m_dwWebMaxRelays;
		m_pSetting->nWebMaxOutputBitrate = m_dwWebMaxOutputBitrate;
	}
}
