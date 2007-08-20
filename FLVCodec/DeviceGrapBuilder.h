// DeviceGrapBuilder.h: interface for the CDeviceGrapBuilder class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DEVICEGRAPBUILDER_H__D4D1DA7E_1497_48C8_AD10_574C4DE970ED__INCLUDED_)
#define AFX_DEVICEGRAPBUILDER_H__D4D1DA7E_1497_48C8_AD10_574C4DE970ED__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BaseGrapBuilder.h"
#include "crossbar.h"

string helper_getstring(TCHAR *szParam, char *valName);
int helper_getint(TCHAR *szParam, char *valName);
enum	TYPE_VIDEOCONFIG
{
	SOFTWARE_CAPTURE, 
	HARDWARE_CAPTURE, 
	SOFTWAVE_PREVIEW, 
	HARDWARE_PREVIEW
};

class CDeviceGrapBuilder : public CBaseGrapBuilder  
{
public:
	CDeviceGrapBuilder();
	virtual ~CDeviceGrapBuilder();

	virtual HRESULT Cleanup();
	
protected:
	virtual HRESULT RenderGrapBuilder(TCHAR *szParam);

	virtual int OpenDevice( CDeviceGrapBuilder *p_sys,
						string devicename, 
						string devicename_display,
						bool b_audio);
	virtual HRESULT DoMiscWork();	
	virtual HRESULT ApplyConfig(){return S_OK;}
	virtual HRESULT	ReleaseInterface();
	virtual BOOL	IsSupportHardCodec(int i_codec){return FALSE;}
	virtual HRESULT InsertEncoderFilter(IBaseFilter* p_device_filter ,
		SampleCaptureFilter *p_capture_filter,bool b_audio,
		IBaseFilter** pp_encoder_filter);

	HRESULT helper_GetCrossbarRoute(IBaseFilter* pVCap, CCrossbar **ppCrossBar);
public:
	string			vdevname, adevname;
	string			vdevname_display, adevname_display;

	int            i_width;
    int            i_height;
    int            i_chroma;
	float		   f_fps;
	
	int			   i_channels;
	int			   i_samplespersec;
	int			   i_bitspersample;
    int            i_achroma;
	
	bool			b_dshowconfig;
	bool			b_dshowtuner;

	int				i_PhysConnType;
	int				i_VideoStandard;

	int				i_vcodec;
	int				i_acodec;
	int				i_vb;
	int				i_ab;

	CCrossbar*					m_pCrossBar;
	IAMAnalogVideoDecoder*		m_pAnalogVideoDecoder;
	IAMStreamConfig*	m_pAudioPreviewStreamConfig;
	IAMStreamConfig*	m_pAudioCaptureStreamConfig;
	IAMStreamConfig*	m_pVideoPreviewStreamConfig;
	IAMStreamConfig*	m_pVideoCaptureStreamConfig;
	IAMStreamConfig*	m_pVideoCompressStreamConfig;	
	IAMStreamConfig*	m_pAudioCompressStreamConfig;	
	
};

#endif // !defined(AFX_DEVICEGRAPBUILDER_H__D4D1DA7E_1497_48C8_AD10_574C4DE970ED__INCLUDED_)
