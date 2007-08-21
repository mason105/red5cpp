// MRLRecentFileList.h: interface for the CMRLRecentFileList class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MRLRECENTFILELIST_H__CEC300F5_75F5_4492_B782_E39BA1C19275__INCLUDED_)
#define AFX_MRLRECENTFILELIST_H__CEC300F5_75F5_4492_B782_E39BA1C19275__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "afxpriv.h"
class CMRLRecentFileList : public CRecentFileList  
{
public:
	CMRLRecentFileList(UINT nStart, LPCTSTR lpszSection,
		LPCTSTR lpszEntryFormat, int nSize, int nMaxDispLen= AFX_ABBREV_FILENAME_LEN);
	virtual ~CMRLRecentFileList();

	virtual void Add(LPCTSTR lpszPathName);
};

#endif // !defined(AFX_MRLRECENTFILELIST_H__CEC300F5_75F5_4492_B782_E39BA1C19275__INCLUDED_)
