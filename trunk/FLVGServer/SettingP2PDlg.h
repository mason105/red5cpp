#if !defined(AFX_SETTIINGWebDLG_H__38F20224_3CC0_4B53_BD00_A14E37705D3A__INCLUDED_)
#define AFX_SETTIINGWebDLG_H__38F20224_3CC0_4B53_BD00_A14E37705D3A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SettiingWebDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSettingWebDlg dialog

class CSettingWebDlg : public CDialog
{
// Construction
public:
	CSettingWebDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSettingWebDlg)
	enum { IDD = IDD_DIALOG_SETTING_Web };
	CXTFlatEdit	m_editWebPort;
	CXTFlatEdit	m_editWebMaxRelays;
	CXTFlatEdit	m_editWebMaxOutputBitrate;
	DWORD	m_dwWebMaxOutputBitrate;
	DWORD	m_dwWebMaxRelays;
	DWORD	m_dwWebPort;
	//}}AFX_DATA

	CBrush m_brushBack;
	COLORREF m_clrBack;
	void UpdateColors();
	
	inline void SetItem(CXTPTaskPanelGroupItem* pItem) {m_pItem = pItem;}
	CXTPTaskPanelGroupItem* m_pItem;
	
	void InitSetting(XDLS_Setting *pSetting);
	void ApplySetting(XDLS_Setting *pSetting);
	
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSettingWebDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	XDLS_Setting *m_pSetting;
	
	// Generated message map functions
	//{{AFX_MSG(CSettingWebDlg)
		// NOTE: the ClassWizard will add member functions here
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnButtonBrowsh();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETTIINGWebDLG_H__38F20224_3CC0_4B53_BD00_A14E37705D3A__INCLUDED_)
