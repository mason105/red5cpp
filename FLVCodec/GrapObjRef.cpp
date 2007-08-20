// GrapObjRef.cpp: implementation of the CGrapObjRef class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "GrapObjRef.h"
#include "FileGrapBuilder.h"
#include "DeviceGrapBuilder.h"
#include "MP4XV3GrapBuilder.h"
#include "Go400GrapBuilder.h"
#include "GoDVBGrapBuilder.h"
#include "markupstl.h"
#include "FLVDeviceGrapBuilder.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


CGrapObjRef::CGrapObjRef()
{
//	m_pBaseGrapBuilder = NULL;
	m_pGraphBuilder	   = NULL;
	m_nGraphCountRef   = 0;
}

CGrapObjRef::~CGrapObjRef()
{

}
HRESULT	CGrapObjRef::Initialize(TCHAR *szParam, GrapBuilderType type)
{
	CoInitialize(0);
	HRESULT hr;
	if(m_pGraphBuilder == NULL || m_nGraphCountRef == 0)
	{
		if (FAILED(hr = CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER, IID_IGraphBuilder, (void **)&m_pGraphBuilder)))
			return hr;
	}
	InterlockedIncrement(&m_nGraphCountRef);
	
	string			vdevname, adevname;
	string			vdevname_display, adevname_display;

	vdevname			= helper_getstring(szParam, "dshow-vdev=");
	adevname			= helper_getstring(szParam, "dshow-adev=");
	vdevname_display	= helper_getstring(szParam, "dshow-vdev-display=");
	adevname_display	= helper_getstring(szParam, "dshow-adev-display=");

	string			filename;

	filename			= helper_getstring(szParam, "dshow-file=");

	CBaseGrapBuilder	*pBaseGrapBuilder;
	if(type == GrapBuilderType_Auto)
	{
		if(filename.size() || (!vdevname.size() || !adevname.size()))
		{
			pBaseGrapBuilder = new CFileGrapBuilder;
		}
		else if(vdevname.size() || adevname.size())
		{
			if(!strnicmp(vdevname.c_str(), 
				MP4XV3DEVICE_NAME, 
				strlen(MP4XV3DEVICE_NAME)))
				pBaseGrapBuilder = new CMP4XV3GrapBuilder;
			else if(!strnicmp(vdevname.c_str(), 
				GO400DEVICE_NAME, 
				strlen(GO400DEVICE_NAME)))
				pBaseGrapBuilder = new CGo400GrapBuilder;
			else if(!strnicmp(vdevname.c_str(), 
				GODVBDEVICE_NAME, 
				strlen(GODVBDEVICE_NAME)))
				pBaseGrapBuilder = new CGoDVBGrapBuilder;
			else
				pBaseGrapBuilder = new CDeviceGrapBuilder;
		}
	}
	else
	{
		switch(type) 
		{
		case GrapBuilderType_File:
			pBaseGrapBuilder = new CFileGrapBuilder;
			break;
		case GrapBuilderType_MP4XV3GrapBuilder:
			pBaseGrapBuilder = new CMP4XV3GrapBuilder;
			break;
		case GrapBuilderType_Go400GrapBuilder:
			pBaseGrapBuilder = new CGo400GrapBuilder;
			break;
		case GrapBuilderType_GoDVBGrapBuilder:
			pBaseGrapBuilder = new CGoDVBGrapBuilder;
			break;
		case GrapBuilderType_FLV:
			pBaseGrapBuilder = new CFLVDeviceGrapBuilder;
			break;
		case GrapBuilderType_DeviceGrapBuilder:
		default:
			pBaseGrapBuilder = new CDeviceGrapBuilder;
			break;
		}
	}
	
	m_list_BaseGrapBuilder.push_back(pBaseGrapBuilder);
	if(pBaseGrapBuilder)
		return pBaseGrapBuilder->Initialize(szParam, m_pGraphBuilder);
	return E_POINTER;
}
HRESULT	CGrapObjRef::InitializeFromConfig(TCHAR *szFile)
{
	HRESULT hr = S_OK;
	do {
		CMarkupSTL xml;
		xml.Load(szFile);
		while ( xml.FindElem("DshowDeviceParam") )
		{			
			string			vdevname, adevname;
			string			vdevname_display, adevname_display;
			
			int            i_width;
			int            i_height;
			int            i_chroma = 0;
			float		   f_fps;
			
			int			   i_channels;
			int			   i_samplespersec;
			int			   i_bitspersample;
			int            i_achroma = 0;
			
			bool			b_dshowconfig;
			bool			b_dshowtuner;
			
			int				i_PhysConnType;
			int				i_VideoStandard;
			
			int				i_vcodec = 0;
			int				i_acodec = 0;
			int				i_vb;
			int				i_ab;
			char			str_vcodec[32];
			char			str_acodec[32];
			char			str_chroma[32];
			
			xml.FindChildElem( "vdevname");
			vdevname = xml.GetChildData().c_str();
			xml.FindChildElem( "adevname");
			adevname = xml.GetChildData().c_str();
			xml.FindChildElem( "vdevname_display");
			vdevname_display = xml.GetChildData().c_str();
			xml.FindChildElem( "adevname_display");
			adevname_display = xml.GetChildData().c_str();

			xml.FindChildElem( "VideoWidth");
			i_width = atoi(xml.GetChildData().c_str());
			xml.FindChildElem( "VideoHeight");
			i_height = atoi(xml.GetChildData().c_str());
			xml.FindChildElem( "VideoChroma");
			strcpy(str_chroma, xml.GetChildData().c_str());
			if(strlen(str_chroma) && strcmp(str_chroma, "0"))
				i_chroma = MAKEFOURCC( str_chroma[0], str_chroma[1],
				str_chroma[2], str_chroma[3] );	
			xml.FindChildElem( "VideoFps");
			f_fps = (double)atoi(xml.GetChildData().c_str()) / 100.0;

			xml.FindChildElem( "AudioChannel");
			i_channels = atoi(xml.GetChildData().c_str());
			xml.FindChildElem( "AudioSamplespersec");
			i_samplespersec = atoi(xml.GetChildData().c_str());
			xml.FindChildElem( "AudioBitspersample");
			i_bitspersample = atoi(xml.GetChildData().c_str());
			xml.FindChildElem( "AudioChroma");
			strcpy(str_chroma, xml.GetChildData().c_str());
			if(strlen(str_chroma) && strcmp(str_chroma, "0"))
				i_achroma = MAKEFOURCC( str_chroma[0], str_chroma[1],
				str_chroma[2], str_chroma[3] );	
			
			xml.FindChildElem( "dshowconfig");
			b_dshowconfig = atoi(xml.GetChildData().c_str());
			xml.FindChildElem( "dshowtuner");
			b_dshowtuner = atoi(xml.GetChildData().c_str());
			
			xml.FindChildElem( "PhysConnType");
			i_PhysConnType = atoi(xml.GetChildData().c_str());
			xml.FindChildElem( "AnalogVideoStandard");
			i_VideoStandard = atoi(xml.GetChildData().c_str());
			
			xml.FindChildElem( "VideoCodec");
			strcpy(str_vcodec, xml.GetChildData().c_str());
			if(strlen(str_vcodec) && 
				strcmp(str_vcodec, "0") &&
				strcmp(str_vcodec, "None"))
			i_vcodec = MAKEFOURCC( str_vcodec[0], str_vcodec[1],
				str_vcodec[2], str_vcodec[3] );			
			xml.FindChildElem( "VideoBitrate");
			i_vb = atoi(xml.GetChildData().c_str());
			xml.FindChildElem( "AudioCodec");
			strcpy(str_acodec, xml.GetChildData().c_str());
			if(strlen(str_acodec)&& 
				strcmp(str_acodec, "0") &&
				strcmp(str_acodec, "None"))
				i_acodec = MAKEFOURCC( str_acodec[0], str_acodec[1],
				str_acodec[2], str_acodec[3] );
			xml.FindChildElem( "AudioBitrate");
			i_ab = atoi(xml.GetChildData().c_str());
			
			TCHAR szParam [2048] = "\0";
			sprintf(szParam, "dshow-vdev=%s;dshow-adev=%s;dshow-vdev-display=%s;\
dshow-adev-display=%s;Width=%d;\
Height=%d;dshow-chroma=%d;\
dshow-fps=%f;dshow-audio-channel=%d;\
dshow-audio-samplespersec=%d;\
dshow-audio-bitspersample=%d;dshow-config=%d;\
dshow-tuner=%d;dshow-PhysConnType=%d;\
dshow-AnalogVideoStandard=%d;\
dshow-vcodec=%d;dshow-acodec=%d;\
dshow-vb=%d;dshow-ab=%d;", 
				  vdevname.c_str(),
				  adevname.c_str(),
				  vdevname_display.c_str(),
				  adevname_display.c_str(),
				  i_width,
				  i_height,
				  i_chroma,
				  f_fps,
				  i_channels,
				  i_samplespersec,
				  i_bitspersample,
				  b_dshowconfig,
				  b_dshowtuner,
				  i_PhysConnType,
				  i_VideoStandard,
				  i_vcodec,
				  i_acodec,
				  i_vb,
				  i_ab);

			if(FAILED(hr = Initialize(szParam)))
				break;
		}
		return hr;
	} while(false);
	Cleanup();
	return hr;
}
HRESULT CGrapObjRef::Cleanup()
{
	HRESULT hr = S_OK;
	list_it_BaseGrapBuilder it = m_list_BaseGrapBuilder.begin();
	for(; it != m_list_BaseGrapBuilder.end(); it++)
	{
		CBaseGrapBuilder	*pBaseGrapBuilder = *it;
		pBaseGrapBuilder->Cleanup();
		delete pBaseGrapBuilder;
	}
	m_list_BaseGrapBuilder.clear();
	
	/*
	if(m_pBaseGrapBuilder)
	{
		hr = m_pBaseGrapBuilder->Cleanup();
		delete m_pBaseGrapBuilder;
		m_pBaseGrapBuilder = NULL;
	}*/

	if(m_nGraphCountRef >= 0)
	{
		if( !InterlockedDecrement(&m_nGraphCountRef) )
		{
			SAFE_RELEASE(m_pGraphBuilder);
		}
	}
	CoUninitialize();
	return hr;
}

HRESULT CGrapObjRef::Run()
{
	list_it_BaseGrapBuilder it = m_list_BaseGrapBuilder.begin();
	for(; it != m_list_BaseGrapBuilder.end(); it++)
	{
		CBaseGrapBuilder	*pBaseGrapBuilder = *it;
		return pBaseGrapBuilder->Run();
	}
	//if(m_pBaseGrapBuilder)
	//	return m_pBaseGrapBuilder->Run();
	return E_POINTER;
}
HRESULT CGrapObjRef::Stop()
{
	list_it_BaseGrapBuilder it = m_list_BaseGrapBuilder.begin();
	for(; it != m_list_BaseGrapBuilder.end(); it++)
	{
		CBaseGrapBuilder	*pBaseGrapBuilder = *it;
		return pBaseGrapBuilder->Stop();
	}
//	if(m_pBaseGrapBuilder)
//		return m_pBaseGrapBuilder->Stop();
	return E_POINTER;
}
HRESULT CGrapObjRef::Pause()
{
	list_it_BaseGrapBuilder it = m_list_BaseGrapBuilder.begin();
	for(; it != m_list_BaseGrapBuilder.end(); it++)
	{
		CBaseGrapBuilder	*pBaseGrapBuilder = *it;
		return pBaseGrapBuilder->Pause();
	}
//	if(m_pBaseGrapBuilder)
//		return m_pBaseGrapBuilder->Pause();
	return E_POINTER;
}

HRESULT CGrapObjRef::GetDuration(LONGLONG* pDuration)
{
	list_it_BaseGrapBuilder it = m_list_BaseGrapBuilder.begin();
	for(; it != m_list_BaseGrapBuilder.end(); it++)
	{
		CBaseGrapBuilder	*pBaseGrapBuilder = *it;
		return pBaseGrapBuilder->GetDuration(pDuration);
	}
//	if(m_pBaseGrapBuilder)
//		return m_pBaseGrapBuilder->GetDuration(pDuration);
	return E_POINTER;
}
HRESULT CGrapObjRef::GetCurrentPosition(LONGLONG* pCurrent)
{
	list_it_BaseGrapBuilder it = m_list_BaseGrapBuilder.begin();
	for(; it != m_list_BaseGrapBuilder.end(); it++)
	{
		CBaseGrapBuilder	*pBaseGrapBuilder = *it;
		return pBaseGrapBuilder->GetCurrentPosition(pCurrent);
	}
//	if(m_pBaseGrapBuilder)
//		return m_pBaseGrapBuilder->GetCurrentPosition(pCurrent);
	return E_POINTER;
	
}
HRESULT  CGrapObjRef::ShowFilterSettings(HWND hOwner,
										 FilterSettingType type,
						   bool b_audio)
{
	list_it_BaseGrapBuilder it = m_list_BaseGrapBuilder.begin();
	for(; it != m_list_BaseGrapBuilder.end(); it++)
	{
		CBaseGrapBuilder	*pBaseGrapBuilder = *it;
		return pBaseGrapBuilder->ShowFilterSettings(hOwner, type, b_audio);
	}
	//	if(m_pBaseGrapBuilder)
	//		return m_pBaseGrapBuilder->ShowFilterSettings(type, b_audio);
	return E_POINTER;
}
int				CGrapObjRef::get_streamcount()
{
	long streamcount = 0;
	list_it_BaseGrapBuilder it = m_list_BaseGrapBuilder.begin();
	for(; it != m_list_BaseGrapBuilder.end(); it++)
	{
		CBaseGrapBuilder	*pBaseGrapBuilder = *it;
		streamcount += pBaseGrapBuilder->i_streams;
	}
	return streamcount;
//	if(m_pBaseGrapBuilder)
//		return m_pBaseGrapBuilder->i_streams;
	return 0;	
}
CDShowStream*	CGrapObjRef::get_stream(int i_stream)
{
	long streamindex = 0;
	list_it_BaseGrapBuilder it = m_list_BaseGrapBuilder.begin();
	for(; it != m_list_BaseGrapBuilder.end(); it++)
	{
		CBaseGrapBuilder	*pBaseGrapBuilder = *it;
		if(pBaseGrapBuilder->pp_streams == NULL ||
			pBaseGrapBuilder->i_streams == 0)
			continue;
		if(pBaseGrapBuilder->i_streams + streamindex > i_stream)
		{
			return pBaseGrapBuilder->pp_streams[i_stream - streamindex];
		}
		else
			streamindex += pBaseGrapBuilder->i_streams;
	}
/*	if(m_pBaseGrapBuilder)
	{
		if(m_pBaseGrapBuilder->pp_streams == NULL)
			return 0;
		if(m_pBaseGrapBuilder->i_streams < i_stream)
			return 0;
		return m_pBaseGrapBuilder->pp_streams[i_stream];
	}*/
	return 0;	
	
}
