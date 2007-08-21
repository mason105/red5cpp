// RelayPropertyPage1.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "RelayPropertyPage1.h"
#include "RelayPropertySheet.h"
#include "MRLRecentFileList.h"

#include "SysInfo.h"
#include "SysUtils.h"
#include <sstream>
using namespace std;
#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CRelayPropertyPage1, CXTMainPropertyPage)
IMPLEMENT_DYNCREATE(CRelayPropertyPage2, CXTMainPropertyPage)
IMPLEMENT_DYNCREATE(CRelayPropertyPage3, CXTMainPropertyPage)


/////////////////////////////////////////////////////////////////////////////
// CRelayPropertyPage1 property page

CRelayPropertyPage1::CRelayPropertyPage1() : CXTMainPropertyPage(CRelayPropertyPage1::IDD)
{
	static long lcount = 0;
	//{{AFX_DATA_INIT(CRelayPropertyPage1)
	m_nType = 0;
	m_strInput = _T("");
	//}}AFX_DATA_INIT
	m_strName.Format("Noname_%d", lcount++);
	m_pMRU = NULL;
}

CRelayPropertyPage1::~CRelayPropertyPage1()
{
	if(m_pMRU)
	{
		m_pMRU->WriteList();
		delete m_pMRU;
	}
}

void CRelayPropertyPage1::DoDataExchange(CDataExchange* pDX)
{
	CXTMainPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRelayPropertyPage1)
	DDX_Control(pDX, IDC_EDIT_NAME, m_editName);
	DDX_Control(pDX, IDC_COMBO_TYPE, m_comboType);
	DDX_Control(pDX, IDC_COMBO_INPUT, m_comboInput);
	DDX_CBIndex(pDX, IDC_COMBO_TYPE, m_nType);
	DDX_CBString(pDX, IDC_COMBO_INPUT, m_strInput);
	DDX_Text(pDX, IDC_EDIT_NAME, m_strName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRelayPropertyPage1, CXTMainPropertyPage)
	//{{AFX_MSG_MAP(CRelayPropertyPage1)
	ON_CBN_SELCHANGE(IDC_COMBO_TYPE, OnSelchangeComboType)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CRelayPropertyPage2 property page

CRelayPropertyPage2::CRelayPropertyPage2() : CXTMainPropertyPage(CRelayPropertyPage2::IDD)
{
	static DWORD dwRTSPBasePort = 5000;
	//{{AFX_DATA_INIT(CNewSourcePropertyPage2)
	m_dwNetPort = 6789;
	m_strNetAddress = ("234.0.0.1");
	m_dwNetRTSPPort = dwRTSPBasePort ++;
	m_strMifaceAddress = _T("");
	//}}AFX_DATA_INIT
}

CRelayPropertyPage2::~CRelayPropertyPage2()
{
}

void CRelayPropertyPage2::DoDataExchange(CDataExchange* pDX)
{
	CXTMainPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRelayPropertyPage2)
	DDX_Control(pDX, IDC_EDIT_NETRTSPPORT, m_editNetRTSPPort);
	DDX_Control(pDX, IDC_EDIT_MIFACEADDRESS, m_comboMifaceAddress);
	DDX_Control(pDX, IDC_EDIT_NETPORT, m_editNetPort);
	DDX_Control(pDX, IDC_EDIT_NETADDRESS, m_editNetAddress);
	DDX_Control(pDX, IDC_COMBO_NETPROTOCOL, m_comboNetProtocol);
	DDX_Control(pDX, IDC_COMBO_ENCAPSULATIONMETHOD, m_comboEncapsulationMethod);
	DDX_Text(pDX, IDC_EDIT_NETPORT, m_dwNetPort);
	DDX_Text(pDX, IDC_EDIT_NETADDRESS, m_strNetAddress);
	DDX_Text(pDX, IDC_EDIT_NETRTSPPORT, m_dwNetRTSPPort);
	DDX_CBString(pDX, IDC_EDIT_MIFACEADDRESS, m_strMifaceAddress);
	DDX_CBString(pDX, IDC_COMBO_NETPROTOCOL, m_strNetProctol);
	DDX_CBString(pDX, IDC_COMBO_ENCAPSULATIONMETHOD, m_strEncapsulationMethod);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRelayPropertyPage2, CXTMainPropertyPage)
	//{{AFX_MSG_MAP(CRelayPropertyPage2)
	ON_CBN_SELCHANGE(IDC_COMBO_NETPROTOCOL, OnSelchangeComboNetprotocol)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()



BOOL CRelayPropertyPage1::OnSetActive() 
{
	UpdateCtrl();
	
	return CXTMainPropertyPage::OnSetActive();
}

BOOL CRelayPropertyPage2::OnSetActive() 
{
	CRelayPropertySheet* pParent=(CRelayPropertySheet*)GetParent();
	pParent->SetWizardButtons(PSWIZB_FINISH | PSWIZB_BACK);	
	
	return CXTMainPropertyPage::OnSetActive();
}
void CRelayPropertyPage1::UpdateCtrl()
{
	UpdateData();
	CRelayPropertySheet *pParent = (CRelayPropertySheet*)GetParent();
	ASSERT(pParent);
	pParent->SetWizardButtons(PSWIZB_NEXT);
}

void CRelayPropertyPage1::OnSelchangeComboType() 
{
	UpdateCtrl();
	
}

void CRelayPropertyPage2::OnSelchangeComboNetprotocol() 
{
	UpdateData();
	m_comboEncapsulationMethod.ResetContent();
	CString strText;
	GetDlgItem(IDC_COMBO_NETPROTOCOL)->GetWindowText(strText);
	if(strText == "rtp")
	{
		m_comboEncapsulationMethod.AddString("ts");
		GetDlgItem(IDC_EDIT_NETADDRESS)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_NETADDRESS)->SetWindowText("234.0.0.1");
		GetDlgItem(IDC_EDIT_NETRTSPPORT)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_MIFACEADDRESS)->EnableWindow(TRUE);
		SocketInfo sockInfo;
		for(list_string::iterator it = sockInfo.m_strlistIPAddress.begin();
		it != sockInfo.m_strlistIPAddress.end(); it ++)
		{
			((CXTFlatComboBox*)GetDlgItem(IDC_EDIT_MIFACEADDRESS))->AddString((*it).c_str());
		}
		GetDlgItem(IDC_EDIT_MIFACEADDRESS)->SetWindowText(sockInfo.getIPAddress().c_str());
		
	}
	else if(strText == "http")
	{
		m_comboEncapsulationMethod.AddString("asf");
		m_comboEncapsulationMethod.AddString("ts");
		GetDlgItem(IDC_EDIT_NETADDRESS)->SetWindowText("");
		GetDlgItem(IDC_EDIT_NETADDRESS)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_NETRTSPPORT)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_MIFACEADDRESS)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_MIFACEADDRESS)->SetWindowText("");
	}
	else if(strText == "mmsh")
	{
		m_comboEncapsulationMethod.AddString("asfh");
		m_comboEncapsulationMethod.AddString("ts");
		GetDlgItem(IDC_EDIT_NETADDRESS)->SetWindowText("");
		GetDlgItem(IDC_EDIT_NETADDRESS)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_NETRTSPPORT)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_MIFACEADDRESS)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_MIFACEADDRESS)->SetWindowText("");
	}
	else if(strText == "rtsp")
	{
		m_comboEncapsulationMethod.AddString("es");
		GetDlgItem(IDC_EDIT_NETADDRESS)->SetWindowText("");
		GetDlgItem(IDC_EDIT_NETADDRESS)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_NETRTSPPORT)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_MIFACEADDRESS)->SetWindowText("");
		GetDlgItem(IDC_EDIT_MIFACEADDRESS)->EnableWindow(FALSE);
	}
	else
	{
		ASSERT(0);
		return ;
	}
	m_comboEncapsulationMethod.SetCurSel(0);	
}

BOOL CRelayPropertyPage2::OnInitDialog() 
{
	CXTMainPropertyPage::OnInitDialog();
	

	OnSelchangeComboNetprotocol();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CRelayPropertyPage2::OnWizardFinish() 
{
	CXTMainPropertyPage::UpdateData();
	
	return CXTMainPropertyPage::OnWizardFinish();
}

BOOL CRelayPropertyPage1::OnWizardFinish() 
{
	CXTMainPropertyPage::UpdateData();
	if(m_pMRU)
		m_pMRU->Add(m_strInput);
	
	return CXTMainPropertyPage::OnWizardFinish();
}

LRESULT CRelayPropertyPage1::OnWizardNext() 
{
	CXTMainPropertyPage::UpdateData();
	if(m_pMRU)
		m_pMRU->Add(m_strInput);
	if(m_nType == 0)
		return IDD_PROPPAGE2;
	else
		return IDD_PROPPAGE3;
//	return CXTMainPropertyPage::OnWizardNext();
}

BOOL CRelayPropertyPage1::OnInitDialog() 
{
	CXTMainPropertyPage::OnInitDialog();
	
	{
		CString strTmp;
		m_pMRU = new CMRLRecentFileList(1, MRL_MRURegKey, MRL_MRUValueFormat, 10);
		m_pMRU->ReadList();
		if(m_pMRU->GetSize())
		{
			for ( int i = 0; i < m_pMRU->GetSize(); i++ )
			{
				if ( (*m_pMRU)[i].GetLength() > 0 )
				{			
					m_comboInput.AddString((LPSTR)(LPCSTR)(*m_pMRU)[i]);
				}
			}	
		}
		if(m_comboInput.GetCount())
			m_comboInput.SetCurSel(0);
	}	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
//////////////////////////////////////////////////////////////////////////
void IDtoStr(char* id, char *str)
{
	
	str[0] = 0;
	for(int i=0; i<16; i++)
	{
		char tmp[8];
		unsigned char ipb = id[i];
		
		sprintf(tmp,"%02X",ipb);
		strcat(str,tmp);
	}	
}
void IDfromStr(char* id, const char *str)
{
	
	if (strlen(str) < 32)
		return;
	
	char buf[8];
	
	buf[2] = 0;
	
	for(int i=0; i<16; i++)
	{
		buf[0] = str[i*2];
		buf[1] = str[i*2+1];
		id[i] = (unsigned char)strtoul(buf,NULL,16);
	}
	
}
CRelayPropertyPage3::CRelayPropertyPage3() : CXTMainPropertyPage(CRelayPropertyPage3::IDD)
{
	//{{AFX_DATA_INIT(CRelayPropertyPage3)
	m_dwWebRelayBitrate = 0;
	m_strWebSourceType	= "TS";
	//}}AFX_DATA_INIT
	static char id[16];
	memset(id, 0, 16);
	id[0] = 1;
	char str[64];
	IDtoStr(id, str);
	
	m_strWebRelayID.Format("%s", str);
	id[15] ++;

}

CRelayPropertyPage3::~CRelayPropertyPage3()
{
}

void CRelayPropertyPage3::DoDataExchange(CDataExchange* pDX)
{
	CXTMainPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRelayPropertyPage3)
	DDX_Control(pDX, IDC_COMBO_WebSOURCETYPE, m_comboWebSourceType);
	DDX_Control(pDX, IDC_EDIT_WebRELAYID, m_editWebRelayID);
	DDX_Control(pDX, IDC_EDIT_DESCRIPTION, m_editDescription);
	DDX_Control(pDX, IDC_EDIT_BITRATE, m_editWebRelayBitrate);
	DDX_CBString(pDX, IDC_COMBO_WebSOURCETYPE, m_strWebSourceType);
	DDX_Text(pDX, IDC_EDIT_DESCRIPTION, m_strWebDescription);
	DDX_Text(pDX, IDC_EDIT_WebRELAYID, m_strWebRelayID);
	DDX_Text(pDX, IDC_EDIT_BITRATE, m_dwWebRelayBitrate);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRelayPropertyPage3, CXTMainPropertyPage)
//{{AFX_MSG_MAP(CRelayPropertyPage3)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()



BOOL CRelayPropertyPage3::OnSetActive() 
{
	CRelayPropertySheet* pParent=(CRelayPropertySheet*)GetParent();
	pParent->SetWizardButtons(PSWIZB_FINISH | PSWIZB_BACK);	
	
	return CXTMainPropertyPage::OnSetActive();
}
BOOL CRelayPropertyPage3::OnWizardFinish() 
{
	CXTMainPropertyPage::UpdateData();
	
	return CXTMainPropertyPage::OnWizardFinish();
}
BOOL CRelayPropertyPage3::OnInitDialog() 
{
	CXTMainPropertyPage::OnInitDialog();
	m_editWebRelayID.SetLimitText(32);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

LRESULT CRelayPropertyPage2::OnWizardBack() 
{
	return IDD_PROPPAGE1;
	
	return CXTMainPropertyPage::OnWizardBack();
}
LRESULT CRelayPropertyPage3::OnWizardBack() 
{
	return IDD_PROPPAGE1;
	
	return CXTMainPropertyPage::OnWizardBack();
}
