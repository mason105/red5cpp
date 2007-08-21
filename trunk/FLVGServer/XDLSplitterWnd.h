// XDLSplitterWnd.h: interface for the CXDLSplitterWnd class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_XDLSPLITTERWND_H__1C286CFE_724E_498D_BC37_9EA0D1EC3624__INCLUDED_)
#define AFX_XDLSPLITTERWND_H__1C286CFE_724E_498D_BC37_9EA0D1EC3624__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CXDLSplitterWnd : public CXTSplitterWnd  
{
public:
	CXDLSplitterWnd();
	virtual ~CXDLSplitterWnd();
	
	void	Helper_RecalcLayout(){RecalcLayout();}
protected:
	virtual void StartTracking(int ht);
	virtual void RecalcLayout();
	virtual void OnDrawSplitter(CDC* pDC, ESplitType nType, const CRect& rectArg);
	
};

#endif // !defined(AFX_XDLSPLITTERWND_H__1C286CFE_724E_498D_BC37_9EA0D1EC3624__INCLUDED_)
