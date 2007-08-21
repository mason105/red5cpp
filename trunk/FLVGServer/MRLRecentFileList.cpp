// MRLRecentFileList.cpp: implementation of the CMRLRecentFileList class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MRLRecentFileList.h"
BOOL AFXAPI AfxFullPath(LPTSTR lpszPathOut, LPCTSTR lpszFileIn);
BOOL AFXAPI AfxComparePath(LPCTSTR lpszPath1, LPCTSTR lpszPath2);

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMRLRecentFileList::CMRLRecentFileList(UINT nStart, LPCTSTR lpszSection,
									   LPCTSTR lpszEntryFormat, int nSize, int nMaxDispLen):
CRecentFileList(nStart, lpszSection, lpszEntryFormat, nSize, nMaxDispLen)
{

}

CMRLRecentFileList::~CMRLRecentFileList()
{

}
void CMRLRecentFileList::Add(LPCTSTR lpszPathName)
{
	ASSERT(m_arrNames != NULL);
	ASSERT(lpszPathName != NULL);
	ASSERT(AfxIsValidString(lpszPathName));
	
	// fully qualify the path name
	TCHAR szTemp[_MAX_PATH];
	//AfxFullPath(szTemp, lpszPathName);
	_tcscpy(szTemp, lpszPathName);
	// update the MRU list, if an existing MRU string matches file name
	for (int iMRU = 0; iMRU < m_nSize-1; iMRU++)
	{
		if (AfxComparePath(m_arrNames[iMRU], szTemp))
			break;      // iMRU will point to matching entry
	}
	// move MRU strings before this one down
	for (; iMRU > 0; iMRU--)
	{
		ASSERT(iMRU > 0);
		ASSERT(iMRU < m_nSize);
		m_arrNames[iMRU] = m_arrNames[iMRU-1];
	}
	// place this one at the beginning
	m_arrNames[0] = szTemp;
}