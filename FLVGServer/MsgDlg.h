#if !defined(AFX_MSGDLG_H__31E15ABA_8EA6_44EA_A219_095D5607DA44__INCLUDED_)
#define AFX_MSGDLG_H__31E15ABA_8EA6_44EA_A219_095D5607DA44__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MsgDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMsgDlg dialog

class CMsgDlg : public CXTMainDlg
{
// Construction
public:
	CMsgDlg(CString strMsg, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMsgDlg)
	enum { IDD = IDD_DIALOG_MSG };
	CXTButton	m_btnCancel;
	CXTButton	m_btnOK;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMsgDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CString m_strMessage;
	CString m_strThemePath;
	// Generated message map functions
	//{{AFX_MSG(CMsgDlg)
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
int		XDLCMessageBox(CString strMsg, int nType = MB_OK);

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MSGDLG_H__31E15ABA_8EA6_44EA_A219_095D5607DA44__INCLUDED_)
