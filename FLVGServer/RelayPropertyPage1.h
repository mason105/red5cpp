// RelayPropertyPage1.h : header file
//

#ifndef __RELAYPROPERTYPAGE1_H__
#define __RELAYPROPERTYPAGE1_H__

/////////////////////////////////////////////////////////////////////////////
// CRelayPropertyPage1 dialog
class CMRLRecentFileList;

class CRelayPropertyPage1 : public CXTMainPropertyPage
{
	DECLARE_DYNCREATE(CRelayPropertyPage1)

// Construction
public:
	CRelayPropertyPage1();
	~CRelayPropertyPage1();

// Dialog Data
	//{{AFX_DATA(CRelayPropertyPage1)
	enum { IDD = IDD_PROPPAGE1 };
	CXTFlatEdit	m_editName;
	CXTFlatComboBox	m_comboType;
	CXTFlatComboBox	m_comboInput;
	int		m_nType;
	CString	m_strInput;
	CString	m_strName;
	//}}AFX_DATA

	CMRLRecentFileList*	m_pMRU;
	
// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CRelayPropertyPage1)
	public:
	virtual BOOL OnSetActive();
	virtual BOOL OnWizardFinish();
	virtual LRESULT OnWizardNext();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	void UpdateCtrl();
// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CRelayPropertyPage1)
	afx_msg void OnSelchangeComboType();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};


/////////////////////////////////////////////////////////////////////////////
// CRelayPropertyPage2 dialog

class CRelayPropertyPage2 : public CXTMainPropertyPage
{
	DECLARE_DYNCREATE(CRelayPropertyPage2)

// Construction
public:
	CRelayPropertyPage2();
	~CRelayPropertyPage2();

// Dialog Data
	//{{AFX_DATA(CRelayPropertyPage2)
	enum { IDD = IDD_PROPPAGE2 };
	CXTFlatEdit	m_editNetRTSPPort;
	CXTFlatComboBox	m_comboMifaceAddress;
	CXTFlatEdit	m_editNetPort;
	CXTFlatEdit	m_editNetAddress;
	CXTFlatComboBox	m_comboNetProtocol;
	CXTFlatComboBox	m_comboEncapsulationMethod;
	DWORD	m_dwNetPort;
	CString	m_strNetAddress;
	CString m_strNetProctol;
	DWORD	m_dwNetRTSPPort;
	CString	m_strMifaceAddress;
	CString		m_strEncapsulationMethod;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CRelayPropertyPage2)
	public:
	virtual BOOL OnSetActive();
	virtual BOOL OnWizardFinish();
	virtual LRESULT OnWizardBack();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CRelayPropertyPage2)
	afx_msg void OnSelchangeComboNetprotocol();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};



/////////////////////////////////////////////////////////////////////////////
// CRelayPropertyPage3 dialog

class CRelayPropertyPage3 : public CXTMainPropertyPage
{
	DECLARE_DYNCREATE(CRelayPropertyPage3)
		
		// Construction
public:
	CRelayPropertyPage3();
	~CRelayPropertyPage3();
	
	// Dialog Data
	//{{AFX_DATA(CRelayPropertyPage3)
	enum { IDD = IDD_PROPPAGE3 };
	CXTFlatComboBox	m_comboWebSourceType;
	CXTFlatEdit	m_editWebRelayID;
	CXTFlatEdit	m_editDescription;
	CXTFlatEdit	m_editWebRelayBitrate;
	CString		m_strWebSourceType;
	CString	m_strWebDescription;
	CString	m_strWebRelayID;
	DWORD	m_dwWebRelayBitrate;
	//}}AFX_DATA
	
	
	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CRelayPropertyPage3)
public:
	virtual BOOL OnSetActive();
	virtual BOOL OnWizardFinish();
	virtual LRESULT OnWizardBack ();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
	
	// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CRelayPropertyPage3)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
		
};


#endif // __RELAYPROPERTYPAGE1_H__
