// GrapObjRef.h: interface for the CGrapObjRef class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GRAPOBJREF_H__F77C689A_BB14_441F_9B2C_1670FEEBAE7B__INCLUDED_)
#define AFX_GRAPOBJREF_H__F77C689A_BB14_441F_9B2C_1670FEEBAE7B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BaseGrapBuilder.h"
typedef list<CBaseGrapBuilder*>			list_BaseGrapBuilder;
typedef list_BaseGrapBuilder::iterator	list_it_BaseGrapBuilder;
enum GrapBuilderType
{
	GrapBuilderType_Auto,
	GrapBuilderType_File,
	GrapBuilderType_MP4XV3GrapBuilder,
	GrapBuilderType_Go400GrapBuilder,
	GrapBuilderType_GoDVBGrapBuilder,
	GrapBuilderType_FLV,
	GrapBuilderType_DeviceGrapBuilder,
};

class CGrapObjRef  
{
public:
	CGrapObjRef();
	virtual ~CGrapObjRef();

	virtual HRESULT	Initialize(TCHAR *szParam, GrapBuilderType type = GrapBuilderType_Auto) ;
	virtual HRESULT	InitializeFromConfig(TCHAR *szFile);
	virtual HRESULT Cleanup();
	
	virtual HRESULT Run();
	virtual HRESULT Stop();
	virtual HRESULT Pause();
	
	virtual HRESULT GetDuration(LONGLONG* pDuration);
	virtual HRESULT GetCurrentPosition(LONGLONG* pCurrent);

	virtual HRESULT ShowFilterSettings(HWND hOwner,
					FilterSettingType type,
					bool b_audio);

	
	int				get_streamcount();
	CDShowStream*	get_stream(int i_stream);	
protected:
	//CBaseGrapBuilder	*m_pBaseGrapBuilder;
	list_BaseGrapBuilder m_list_BaseGrapBuilder;
	IGraphBuilder		*m_pGraphBuilder;
	long				 m_nGraphCountRef;
};

#endif // !defined(AFX_GRAPOBJREF_H__F77C689A_BB14_441F_9B2C_1670FEEBAE7B__INCLUDED_)
