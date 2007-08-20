// FileGrapBuilder.cpp: implementation of the CFileGrapBuilder class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "FileGrapBuilder.h"
#include "SampleCaptureFilter.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFileGrapBuilder::CFileGrapBuilder()
{

}

CFileGrapBuilder::~CFileGrapBuilder()
{

}


HRESULT CFileGrapBuilder::RenderGrapBuilder(TCHAR *szParam)
{
	HRESULT hr = E_FAIL;
	do {
		if(m_pGraphBuilder == NULL)
			break;
		USES_CONVERSION;
		
		if(FAILED(hr = m_pGraphBuilder->RenderFile(T2W(szParam), NULL)))
			break;

		return S_OK;
	} while(false);
	return hr;
}
