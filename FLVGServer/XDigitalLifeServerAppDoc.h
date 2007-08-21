// XDigitalLifeServerAppDoc.h : interface of the CXDigitalLifeServerAppDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_XDIGITALLIFESERVERAPPDOC_H__4ECB3AC4_27EB_4BF9_8124_99D9B4B8BD17__INCLUDED_)
#define AFX_XDIGITALLIFESERVERAPPDOC_H__4ECB3AC4_27EB_4BF9_8124_99D9B4B8BD17__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CXDigitalLifeServerAppDoc : public CDocument
{
protected: // create from serialization only
	CXDigitalLifeServerAppDoc();
	DECLARE_DYNCREATE(CXDigitalLifeServerAppDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXDigitalLifeServerAppDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual void SetTitle(LPCTSTR lpszTitle);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CXDigitalLifeServerAppDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CXDigitalLifeServerAppDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XDIGITALLIFESERVERAPPDOC_H__4ECB3AC4_27EB_4BF9_8124_99D9B4B8BD17__INCLUDED_)
