// BaseGrapBuilder.h: interface for the CBaseGrapBuilder class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BASEGRAPBUILDER_H__D06FAEA2_1F6B_41E7_BB39_9343F10E86CD__INCLUDED_)
#define AFX_BASEGRAPBUILDER_H__D06FAEA2_1F6B_41E7_BB39_9343F10E86CD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <stdio.h>
#include <windows.h>
#include <tchar.h>
#include <Streams.h>
#include <dvdmedia.h>
#include <winioctl.h>
#include <mmreg.h>
#include <ks.h>
#include <ksproxy.h>
#include <ksmedia.h>
#include <atlbase.h>
#include <list>
#include <string.h>
#include <string>
#include "SampleCaptureFilter.h"
using namespace std;
#define  _DEBUGAddGraphToROT 

typedef pair<string, string> deviceInfo; 
typedef list<deviceInfo>	 listdevices;

#define SAFE_RELEASE(pv) { if(pv) { (pv)->Release(); (pv) = NULL; } }
#define SAFE_DELETE(pv) if(pv){delete pv; pv = NULL;}
#define SAFE_FREE(pv) if(pv){free( pv); pv = NULL;}
#define MAX_MEDIA_TYPES 32
enum FilterSettingType
{
	FilterSettingType_Device,
	FilterSettingType_Encode
};
const GUID MEDIASUBTYPE_I420 = {0x30323449, 0x0000, 0x0010, {0x80, 0x00, 0x00, 0xaa, 0x00, 0x38, 0x9b, 0x71}};

class CDShowStream
{
public:
    string					devicename;
    IBaseFilter				*p_device_filter;
	IBaseFilter				*p_encoder_filter;
	SampleCaptureFilter		*p_capture_filter;
    AM_MEDIA_TYPE			mt;
	bool					b_audio;
	
    union
    {
		VIDEOINFOHEADER video;
		WAVEFORMATEX    audio;
		
    } header;
	
    int						i_fourcc;
    void					*p_es;
	
	int						 i_SampleCount;
    bool					 b_pts;	
} ;

class CBaseGrapBuilder  
{
public:
	CBaseGrapBuilder();
	virtual ~CBaseGrapBuilder();
	
	virtual HRESULT	Initialize(TCHAR *szParam, IGraphBuilder* pGraphBuilder) ;
	virtual HRESULT Cleanup();

	virtual HRESULT Run();
	virtual HRESULT Stop();
	virtual HRESULT Pause();

	virtual HRESULT GetDuration(LONGLONG* pDuration);
	virtual HRESULT GetCurrentPosition(LONGLONG* pCurrent);

	virtual HRESULT ShowFilterSettings(HWND hOwner, FilterSettingType type,
			bool b_audio);

	static IBaseFilter *
		FindCaptureDevice(string *p_devicename, 
		string *p_displayname,
		list<string> *p_listdevices, 
		list<string> *p_listdiplays, 
		bool b_audio);
	static IBaseFilter *
		FindEncoderDevice(string *p_devicename, 
		string *p_displayname,
		list<string> *p_listdevices, 
		list<string> *p_listdiplays);
	IBaseFilter *FindEncoderFilter(string szEncoderName,
		bool b_audio);
protected:
	virtual HRESULT RenderGrapBuilder(TCHAR *szParam){return E_FAIL;}
	virtual HRESULT	ConstructStream();
	virtual HRESULT	DestructStream();
	virtual HRESULT	ReleaseInterface(){return S_OK;}
	
	BOOL	IsTheEndestFilter(IBaseFilter* pInFilter);
	HRESULT	ReplaceSampleSampleCaptureFilterAndAddStream(IBaseFilter* pInFilter);
	HRESULT	AddStreamByPin(IPin* pInPin);
	
	//filter method
	HRESULT			CreateFilter_BySpecialCategoryAndName(REFCLSID clsidCategory,\
		const TCHAR  *szName,\
		BOOL  bAddtoGrapBuilder,\
		IBaseFilter** ppOutFilter);
	HRESULT			CreateFilter_BySpecialCategoryAndName_SupportConnectPin(REFCLSID clsidCategory,\
		const TCHAR  *szName,\
		BOOL  bAddtoGrapBuilder,\
		IPin  *pInPin,\
		bool  bStillConnect,\
		IBaseFilter** ppOutFilter);
	HRESULT		    CreateFilter_BySpecialCLSIDString(TCHAR* szClsId, \
		const TCHAR *szName,\
		BOOL  bAddtoGrapBuilder,\
		IBaseFilter **ppOutFilter);
	HRESULT			CreateFilter_BySpecialCLSID(CLSID ClsId, \
		const TCHAR *szName,\
		BOOL  bAddtoGrapBuilder,\
		IBaseFilter **ppOutFilter);
	HRESULT			AddFilter_Simple(const TCHAR *szName,\
		IBaseFilter **ppInFilter);
	virtual HRESULT			RemoveFilter_Simple(IBaseFilter **ppInFilter);
	
	//pin method
	HRESULT			GetPin_ByDirect(IBaseFilter *pInFilter, \
		PIN_DIRECTION PinDir,
		IPin **ppOutPin);
	HRESULT			GetPin_ByName(IBaseFilter *pInFilter, \
		const TCHAR* szName,
		IPin **ppOutPin);
	HRESULT			GetPin_ByID(IBaseFilter *pInFilter, \
								const TCHAR* szID,
								IPin **ppOutPin);
	HRESULT			GetPin_FirstDisconnected(IBaseFilter *pInFilter,
		PIN_DIRECTION PinDir,
		IPin **ppOutPin);
	HRESULT			GetPin_ByType(IBaseFilter *pInFilter,\
		PIN_DIRECTION PinDir,\
		bool b_video,\
		IPin **ppOutPin);
	
	//connect method
	HRESULT			ConnectPin_Simple(IPin *pOutPin, \
		IPin *pInPin);
	HRESULT			ConnectPin_Direct(IPin *pOutPin, \
		IPin *pInPin, \
		const AM_MEDIA_TYPE *pmt);
	HRESULT			ConnectPin_Render(IPin *pInPin);
	
	
	HRESULT			ConnectFilter_Simple(IBaseFilter *pUpStreamFilter, \
		IBaseFilter *pDownStreamFilter);
	bool			ConnectFilters( CBaseGrapBuilder *p_sys, 
		IBaseFilter *p_filter,
		SampleCaptureFilter *p_capture_filter );
	bool			ConnectFilters_Custom(CBaseGrapBuilder *p_sys,
		IBaseFilter *p_filter,
		SampleCaptureFilter *p_capture_filter);
	
	//misc method
	void			ShowPropertyPage( IUnknown *obj, HWND hwnd );
	HRESULT			ShowFilterSettings(HWND hOwner, IBaseFilter *pInFilter);
	HRESULT			ShowFilterProperties(HWND hOwner, IBaseFilter *pInFilter, bool b_audio = false);
	HRESULT			ShowTunnerProperties(HWND hOwner, IBaseFilter *pInFilter, bool b_audio = false);
	void			ShowDeviceProperties(ICaptureGraphBuilder2 *p_capture_graph,							
		IBaseFilter *p_device_filter,
		HWND hPropertyOwner,
		bool b_audio );	
	void			ShowTunerProperties(ICaptureGraphBuilder2 *p_capture_graph,
		IBaseFilter *p_device_filter,
		HWND	hPropertyOwner,
		bool b_audio );
	VIDEOINFOHEADER	 *GetVideoInfoHeader(AM_MEDIA_TYPE am);
	WAVEFORMATEX	 *GetWaveFormatEx(AM_MEDIA_TYPE am);
#ifdef _DEBUGAddGraphToROT
	HRESULT  AddGraphToROT();
	HRESULT  RemoveGraphFromROT();	
#endif
	HRESULT ResizeVideoPreviewWindow(IVideoWindow*	pVideoWindow);
	HRESULT SetDefaultSyncClock();
	
	HRESULT			ConnectFilter_RenderStream(IBaseFilter *p_source_filter,
		IBaseFilter *p_Intermediate_filter,
		IBaseFilter *p_capture_filter , 
		bool b_audio,
		bool b_preview);
	HRESULT			ConnectFilter_RenderStream_AnalogVideo(IBaseFilter *p_source_filter,
		IBaseFilter *p_Intermediate_filter,
		IBaseFilter *p_capture_filter);
	HRESULT			RemoveFilter_DownStream(IBaseFilter **ppInFilter);
	HRESULT			RemoveFilter_DownStream_NoRemoveSpecial1(IBaseFilter **ppInFilter, IBaseFilter **ppSpecialFilter);
	HRESULT			RemoveFilter_DisconAllPin(IBaseFilter **ppInFilter);												  
	
	static size_t EnumDeviceCaps( CBaseGrapBuilder *p_this,
		IBaseFilter *p_filter,
		int i_fourcc, int i_width, int i_height,float r_fps,
		int i_channels, int i_samplespersec,
		int i_bitspersample, AM_MEDIA_TYPE *mt,
		size_t mt_max );
	static size_t EnumDeviceCaps( CBaseGrapBuilder *p_this,
		IPin *p_pin,
		int i_fourcc, int i_width, int i_height,float r_fps,
		int i_channels, int i_samplespersec,
		int i_bitspersample, AM_MEDIA_TYPE *mt,
		size_t mt_max );
	
	//////////////////////////////////////////////////////////////////////////
protected:
	ICaptureGraphBuilder2			*m_pCaptureBuilder;
	IGraphBuilder					*m_pGraphBuilder;
	IMediaControl					*m_pMediaControl;
	IMediaSeeking					*m_pMediaSeeking;
#ifdef _DEBUGAddGraphToROT
	DWORD							 m_dwRegister;
#endif
public:	
	CDShowStream **pp_streams;
    int            i_streams;
    int            i_current_stream;
	
};
typedef enum _AMTYPE
{
	AMTYPE_Video,
		AMTYPE_Audio,
		AMTYPE_Unknown,
}AMTYPE;
AMTYPE inline GetAMMediaType(AM_MEDIA_TYPE am);
VIDEOINFOHEADER	 *AMGetVideoInfoHeader(AM_MEDIA_TYPE am);

int GetFourCCPriority( int i_fourcc );
int helper_GetBMISizeImage(BITMAPINFOHEADER bmiHeader);

#endif // !defined(AFX_BASEGRAPBUILDER_H__D06FAEA2_1F6B_41E7_BB39_9343F10E86CD__INCLUDED_)
