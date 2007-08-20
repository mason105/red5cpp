// FileGrapBuilder.h: interface for the CFileGrapBuilder class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FILEGRAPBUILDER_H__FC080B16_6911_4DAD_B884_4286E043ED29__INCLUDED_)
#define AFX_FILEGRAPBUILDER_H__FC080B16_6911_4DAD_B884_4286E043ED29__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BaseGrapBuilder.h"

class CFileGrapBuilder : public CBaseGrapBuilder  
{
public:
	CFileGrapBuilder();
	virtual ~CFileGrapBuilder();
	
protected:
	virtual HRESULT RenderGrapBuilder(TCHAR *szParam);
};

#endif // !defined(AFX_FILEGRAPBUILDER_H__FC080B16_6911_4DAD_B884_4286E043ED29__INCLUDED_)
