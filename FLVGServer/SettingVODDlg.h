#if !defined(AFX_SETTINGVODDLG_H__58DE064D_3A07_4101_BB2D_C461D56AB7BA__INCLUDED_)
#define AFX_SETTINGVODDLG_H__58DE064D_3A07_4101_BB2D_C461D56AB7BA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SettingVODDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSettingVODDlg dialog

class CSettingVODDlg : public CDialog
{
// Construction
public:
	CSettingVODDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSettingVODDlg)
	enum { IDD = IDD_DIALOG_SETTING_VOD };
	CXTFlatEdit	m_editVODPort;
	CXTFlatEdit	m_editVODFilePath;
	CXTFlatEdit	m_editVODAddress;
	CXTButton	m_btnBrowsh;
	DWORD	m_dwVODPort;
	CString	m_strVODFilePath;
	CString	m_strVODAddress;
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
	//{{AFX_VIRTUAL(CSettingVODDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	XDLS_Setting *m_pSetting;
	// Generated message map functions
	//{{AFX_MSG(CSettingVODDlg)
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

#endif // !defined(AFX_SETTINGVODDLG_H__58DE064D_3A07_4101_BB2D_C461D56AB7BA__INCLUDED_)
