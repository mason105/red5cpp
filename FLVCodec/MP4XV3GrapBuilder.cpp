// MP4XV3GrapBuilder.cpp: implementation of the CMP4XV3GrapBuilder class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MP4XV3GrapBuilder.h"
#include "MP4XPCIV3_config_error.h"
#include "MP4XPCIV3_config_helper.h"
#include <assert.h>

#define ANALOGITUVIDEOPINNAME "Analog ITU Video"

const GUID CLSID_NullRenderer =
{0xC1F400A4,0x3F08,0x11D3,{0x9F,0x0B,0x00,0x60,0x08,0x03,0x9E,0x37}};

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
struct FORMAT_VIDEOFRAMERATE_PAIR
{
	char* name;
	float value;
	int  index;
};
const FORMAT_VIDEOFRAMERATE_PAIR VideoFrameRateList[]=
{
	{"29.97 fps",29.97,0},
	{"25 fps",25.00,1},
	{"15 fps",15.00,2},
	{"12.5 fps",12.50,3},
	{"10 fps",10.00,4}
};
CMP4XV3GrapBuilder::CMP4XV3GrapBuilder()
{
	m_pIGOChipPCI	 = NULL;
}

CMP4XV3GrapBuilder::~CMP4XV3GrapBuilder()
{

}


int CMP4XV3GrapBuilder::OpenDevice( CDeviceGrapBuilder *p_sys,
					   string devicename, 
					   string devicename_display,
						bool b_audio)
{
	if(i_vcodec && i_vb &&
		!strnicmp(devicename.c_str(), 
		MP4XV3DEVICE_NAME, 
		strlen(MP4XV3DEVICE_NAME)))
	{
		if(i_VideoStandard == 0)
			i_VideoStandard = AnalogVideo_PAL_D;
		if(f_fps == 0.0)
		{		
			switch(i_VideoStandard) 
			{
			case AnalogVideo_NTSC_M:
			case AnalogVideo_NTSC_M_J:
			case AnalogVideo_NTSC_433:
				f_fps = 30.0;
				break;
			case AnalogVideo_PAL_B:
			case AnalogVideo_PAL_D:
			case AnalogVideo_PAL_G:
			case AnalogVideo_PAL_H:
			case AnalogVideo_PAL_I:
			case AnalogVideo_PAL_M:
			case AnalogVideo_PAL_N:
			case AnalogVideo_PAL_60:
			default:
				f_fps = 25.0;
				break;
			}
		}
	
		return OpenMP4XV3Device(p_sys, devicename, devicename_display, b_audio);
	}
	else
	return CDeviceGrapBuilder1::OpenDevice(p_sys, devicename, devicename_display, b_audio);
}
BOOL CMP4XV3GrapBuilder::GetVideoProfiles(_VIDEO_CAPABILITIES* caps, _VIDEO_PROFILES* profiles)
{
	char windows_directory [ MAX_PATH ];
	::GetWindowsDirectory(windows_directory, MAX_PATH);
	strcat(windows_directory, "/video_profiles_7135.txt");
	
	PARSE_HANDLE handle = OpenConfigurationFile(windows_directory);
	enum CONFIG_ERROR error = ParseConfigurationFile(handle, caps, profiles);
	if ( error != ERROR_NONE )
	{
		error = GetParseErrorInformation(handle, NULL);
	}
	
	CloseConfigurationFile(handle);
	
	return error == ERROR_NONE;
}
int CMP4XV3GrapBuilder::OpenMP4XV3Device( CDeviceGrapBuilder *p_sys,
							 string devicename, 
							 string devicename_display,
							 bool b_audio)
{
	for( int i = 0; i < p_sys->i_streams; i++ )
    {
        if( devicename.size() &&
            p_sys->pp_streams[i]->devicename == devicename )
        {
            /* Already opened */
            return 0;
        }
    }
	
    list<string> list_devices;
    list<string> list_displayname;
	
    /* Enumerate devices and display their names */
    FindCaptureDevice(NULL, NULL, &list_devices, &list_displayname, b_audio);
	
    if( !list_devices.size() )
        return -1;
	
    list<string>::iterator iter;
    for( iter = list_devices.begin(); iter != list_devices.end(); iter++ )
        ATLTRACE( "found device: %s", iter->c_str() );
	
    /* If no device name was specified, pick the 1st one */
    if( devicename.size() == 0  ||
		devicename == string("Default"))
    {
        devicename = *list_devices.begin();
		devicename_display = *list_displayname.begin();
	}

	   // a capture/preview device, such as a desktop USB video camera.
    IBaseFilter *p_device_filter =
        FindCaptureDevice(&devicename, &devicename_display, 
		0, 0, b_audio );
    if( p_device_filter )
        ATLTRACE(  "using device: %s", devicename.c_str() );
    else
    {
        ATLTRACE(  "can't use device: %s, unsupported device type",
                 devicename.c_str() );
        return -1;
    }
    IBaseFilter *p_encoder_filter = NULL;

	SampleCaptureFilter *p_capture_filter = NULL;
	do {
		CComPtr<IPin> pAnalogVideoPin;
		
		if(FAILED(AddFilter_Simple(NULL, (IBaseFilter**)&p_device_filter)))
			break;
		
		if(FAILED(ConnectFilter_RenderStream(p_device_filter, NULL, NULL, false, true)))
			break;
		
		if(FAILED(RemoveFilter_DownStream(&p_device_filter)))
			break;
		
		if(FAILED(GetPin_ByName(p_device_filter, ANALOGITUVIDEOPINNAME, &pAnalogVideoPin)))
			break;

		if(FAILED(CreateFilter_BySpecialCategoryAndName_SupportConnectPin(KSCATEGORY_ENCODER, MP4XV3ENCODER_NAME, true, pAnalogVideoPin, true, &p_encoder_filter)))
			break;

		m_pDeviceFilter  = p_device_filter;
		m_pEncoderFilter = p_encoder_filter;
		
		if(FAILED(ApplyConfig()))
			break;
		
		
		if(b_dshowconfig)
		{
			ShowDeviceProperties(m_pCaptureBuilder,
				p_device_filter, 
				NULL, 
				b_audio);
			ShowDeviceProperties(m_pCaptureBuilder,
				p_encoder_filter, 
				NULL, 
				b_audio);
		}
		if(b_dshowtuner)
		{
			ShowTunerProperties(m_pCaptureBuilder,
				p_device_filter, NULL,
				b_audio );
		}
		
		AM_MEDIA_TYPE media_types[MAX_MEDIA_TYPES];
		size_t media_count =
			EnumDeviceCaps( this, p_encoder_filter, 
			b_audio ? p_sys->i_acodec: p_sys->i_vcodec,
			p_sys->i_width, p_sys->i_height,p_sys->f_fps,
			p_sys->i_channels,
			p_sys->i_samplespersec, 
			p_sys->i_bitspersample,
			media_types, MAX_MEDIA_TYPES );
		if(media_count == 0)
			break;
	
		bool b_stream_type = false;
		for(  i = 0; i < media_count; i++ )
		{
			if( media_types[i].majortype == MEDIATYPE_Stream )
			{
				b_stream_type = true;
				break;
			}
		}
		
		size_t mt_count = 0;
		AM_MEDIA_TYPE *mt = NULL;
		if( media_count > 0 )
		{
			mt = (AM_MEDIA_TYPE *)realloc( mt, sizeof(AM_MEDIA_TYPE) *
				(mt_count + media_count) );
			
			// Order and copy returned media types according to arbitrary
			// fourcc priority
			for( size_t c = 0; c < media_count; c++ )
			{
				int slot_priority =
					GetFourCCPriority(GetFourCCFromMediaType(media_types[c]));
				size_t slot_copy = c;
				for( size_t d = c+1; d < media_count; d++ )
				{
					int priority =
						GetFourCCPriority(GetFourCCFromMediaType(media_types[d]));
					if( priority > slot_priority )
					{
						slot_priority = priority;
						slot_copy = d;
					}
				}
				if( slot_copy != c )
				{
					mt[c+mt_count] = media_types[slot_copy];
					media_types[slot_copy] = media_types[c];
				}
				else
				{
					mt[c+mt_count] = media_types[c];
				}
			}
			mt_count += media_count;
		}
		
		p_capture_filter =
			new SampleCaptureFilter( this, mt, mt_count );
		
		if(FAILED(AddFilter_Simple(NULL, (IBaseFilter**)&p_capture_filter)))
			break;
		
		if(FAILED(ConnectFilter_Simple(p_encoder_filter , p_capture_filter)))
			break;
		{
			CComPtr<IBaseFilter> pNullRender;
			if(FAILED(CreateFilter_BySpecialCategoryAndName(CLSID_LegacyAmFilterCategory,
				_T("Null Renderer"), TRUE, &pNullRender)))
				break;
			CComPtr<IPin> ptmpPin1;
			CComPtr<IPin> ptmpPin2;
			if(FAILED((GetPin_ByName(m_pDeviceFilter, "Audio", &ptmpPin1))))
			{
				if(FAILED((GetPin_ByName(m_pDeviceFilter, "“Ù∆µ", &ptmpPin1))))
					break;
			}		
			if(FAILED( GetPin_FirstDisconnected(pNullRender, PINDIR_INPUT, &ptmpPin2)))
				break;
			if(FAILED( ConnectPin_Simple(ptmpPin1, ptmpPin2)))
				break;
		}
		if(false)
		{
			CComPtr<IBaseFilter> pNullRender;
			if(FAILED(CreateFilter_BySpecialCategoryAndName(CLSID_LegacyAmFilterCategory,
				_T("Null Renderer"), TRUE, &pNullRender)))
				break;
			CComPtr<IPin> ptmpPin1;
			CComPtr<IPin> ptmpPin2;
			if(FAILED((GetPin_ByName(m_pDeviceFilter, "Capture", &ptmpPin1))))
			{
				if(FAILED((GetPin_ByName(m_pDeviceFilter, "≤∂ªÒ", &ptmpPin1))))
					break;
			}		
			if(FAILED( GetPin_FirstDisconnected(pNullRender, PINDIR_INPUT, &ptmpPin2)))
				break;
			if(FAILED( ConnectPin_Simple(ptmpPin1, ptmpPin2)))
				break;
		}

		CDShowStream dshow_stream;
		dshow_stream.b_audio		= false;
	    dshow_stream.b_pts = false;
		dshow_stream.i_SampleCount = 0;
        dshow_stream.p_es = 0;
        dshow_stream.mt =
            p_capture_filter->CustomGetPin()->CustomGetMediaType();
		
		dshow_stream.i_fourcc = GetFourCCFromMediaType( dshow_stream.mt );
        if( dshow_stream.i_fourcc )
        {
            if( dshow_stream.mt.majortype == MEDIATYPE_Video )
            {
                dshow_stream.header.video =
                    *(VIDEOINFOHEADER *)dshow_stream.mt.pbFormat;
                ATLTRACE(  "MEDIATYPE_Video" );
                ATLTRACE(  "selected video pin accepts format: %4.4s",
					(char *)&dshow_stream.i_fourcc);
            }
            else if( dshow_stream.mt.majortype == MEDIATYPE_Audio )
            {
                dshow_stream.header.audio =
                    *(WAVEFORMATEX *)dshow_stream.mt.pbFormat;
                ATLTRACE(  "MEDIATYPE_Audio" );
                ATLTRACE(  "selected audio pin accepts format: %4.4s",
					(char *)&dshow_stream.i_fourcc);
            }
            else if( dshow_stream.mt.majortype == MEDIATYPE_Stream )
            {
                ATLTRACE(  "MEDIATYPE_Stream" );
                ATLTRACE(  "selected stream pin accepts format: %4.4s",
					(char *)&dshow_stream.i_fourcc);
            }
            else
            {
                ATLTRACE(  "unknown stream majortype" );
                break;
            }
	
            /* Add directshow elementary stream to our list */
            dshow_stream.p_device_filter  = p_device_filter;
            dshow_stream.p_capture_filter = p_capture_filter;
            dshow_stream.p_encoder_filter = p_encoder_filter;
			
            pp_streams = (CDShowStream **)realloc( pp_streams,
                sizeof(CDShowStream *) * (i_streams + 1) );
            pp_streams[i_streams] = new CDShowStream;
            *pp_streams[i_streams++] = dshow_stream;
			
			if(m_pCrossBar == NULL)
			{
				helper_GetCrossbarRoute(p_device_filter, &m_pCrossBar);
				if(FAILED(p_device_filter->QueryInterface((IID_IAMAnalogVideoDecoder), (void**)&m_pAnalogVideoDecoder)))
				{					
				}
			}
			return S_OK;
			//return 	AddCapturePinStream(p_device_filter);
        }
	} while(false);
	RemoveFilter_Simple((IBaseFilter**)&p_capture_filter);
	RemoveFilter_Simple((IBaseFilter**)&p_device_filter);
	RemoveFilter_Simple((IBaseFilter**)&p_encoder_filter);
				
	SAFE_RELEASE(p_capture_filter);
	SAFE_RELEASE(p_device_filter);
	SAFE_RELEASE(p_encoder_filter);

	m_pDeviceFilter = NULL;
	m_pEncoderFilter= NULL;

	return S_OK;
}

HRESULT CMP4XV3GrapBuilder::DoMiscWork()
{
	return CDeviceGrapBuilder1::DoMiscWork();
}
HRESULT		CMP4XV3GrapBuilder::ApplyConfig()
{
	HRESULT hr = S_OK;
	do{
		SAFE_RELEASE(m_pAnalogVideoDecoder);
		if(SUCCEEDED(m_pDeviceFilter->QueryInterface((IID_IAMAnalogVideoDecoder), (void**)&m_pAnalogVideoDecoder)))
		{	
			if(i_VideoStandard)
			{
				if(FAILED(hr = m_pAnalogVideoDecoder->put_TVFormat(i_VideoStandard)))
				{
					
				}
				
			}
		}

		if(FAILED(hr = m_pDeviceFilter->QueryInterface(__uuidof(IGOChipPCI), (void**)&m_pIGOChipPCI)))
			break;
		
		{
			CComPtr<IPin> ptmpPin;
			if(FAILED(hr = (GetPin_ByName(m_pDeviceFilter, "Preview", &ptmpPin))))
			{
				if(FAILED(hr = (GetPin_ByName(m_pDeviceFilter, "‘§¿¿", &ptmpPin))))
					break;
			}
			if(FAILED(hr = ptmpPin->QueryInterface(IID_IAMStreamConfig, (void**)&m_pVideoPreviewStreamConfig)))
				break;
		}
		{
			CComPtr<IPin> ptmpPin;
			if(FAILED(hr = (GetPin_ByName(m_pDeviceFilter, "Capture", &ptmpPin))))
			{
				if(FAILED(hr = (GetPin_ByName(m_pDeviceFilter, "≤∂ªÒ", &ptmpPin))))
					break;
			}
			if(FAILED(hr = ptmpPin->QueryInterface(IID_IAMStreamConfig, (void**)&m_pVideoCaptureStreamConfig)))
				break;
			
		}
		{
			CComPtr<IPin> ptmpPin;
			if(FAILED(hr = (GetPin_ByName(m_pDeviceFilter, "Audio", &ptmpPin))))
			{
				if(FAILED(hr = (GetPin_ByName(m_pDeviceFilter, "“Ù∆µ", &ptmpPin))))
					break;
			}
			if(FAILED(hr = ptmpPin->QueryInterface(IID_IAMStreamConfig, (void**)&m_pAudioCaptureStreamConfig)))
				break;
			
		}
		{
			CComPtr<IPin> ptmpPin;
			if(FAILED(hr = (GetPin_ByName(m_pEncoderFilter, "Capture", &ptmpPin))))
			{
				if(FAILED(hr = (GetPin_ByName(m_pEncoderFilter, "≤∂ªÒ", &ptmpPin))))
					break;
			}
			if(FAILED(hr = ptmpPin->QueryInterface(IID_IAMStreamConfig, (void**)&m_pVideoCompressStreamConfig)))
				break;
			
		}

		CollectMP4XPCIV3Config();
		ConvertMP4XPCIV3Config();
		SetMp4xVideoCodecBitRate(i_vcodec);
		
		unsigned long str_index, res_index, fps_index;
		str_index = FindStreamConfiguration(&m_VideoCaps, &m_videoConfig.strcfg);
		res_index = FindResolutionConfiguration(&m_VideoCaps, &m_videoConfig.rescfg);
		fps_index = FindFrameRateConfiguration(&m_VideoCaps, &m_videoConfig.fpscfg);
		if ( str_index == -1 || res_index == -1 || fps_index == -1 ) 
			return E_FAIL;
		m_videoConfig.rescfg.max_bitrate = 
			m_videoConfig.ctlcfg.target_bitrate * 1.1;
		m_videoConfig.rescfg.min_bitrate =
			m_videoConfig.ctlcfg.target_bitrate * 0.9;
		if ( m_videoConfig.ctlcfg.target_bitrate != 0 )
		{
			if (m_videoConfig.ctlcfg.target_bitrate < m_videoConfig.rescfg.min_bitrate ||
				m_videoConfig.ctlcfg.target_bitrate > m_videoConfig.rescfg.max_bitrate )
				return E_FAIL;
		}
		
		if(FAILED(hr = ApplyMP4XPCIV3VideoConfig(m_pVideoCompressStreamConfig, &m_videoConfig, HARDWARE_CAPTURE)))
			break;
		if(FAILED(hr = ApplyMP4XPCIV3VideoConfig(m_pVideoPreviewStreamConfig, &m_videoConfig, SOFTWAVE_PREVIEW)))
			break;
		if(FAILED(hr = ApplyMP4XPCIV3VideoConfig(m_pVideoCaptureStreamConfig, &m_videoConfig, SOFTWARE_CAPTURE)))
			break;
		if(FAILED(hr = ApplyMP4XPCIV3AudioConfig(m_pAudioCaptureStreamConfig, &m_audioConfig)))
			break;
	
		ReleaseInterface();
		return S_OK;
	}while(false);
	ReleaseInterface();
	return hr;	
}

void CMP4XV3GrapBuilder::ConvertMP4XPCIV3Config()
{
	if(i_vcodec != 0)
		ChangeMP4XPCIV3CodecVideoSetting(i_vcodec);
	if(i_height)
		m_videoConfig.rescfg.height	= i_height;
	if(i_width)
		m_videoConfig.rescfg.width	= i_width;
/*	if(f_fps != 0)
	{
		int nFrameRateIndex = -1;
		if(f_fps == 30.0 ||
			f_fps == 29.97)
			nFrameRateIndex = 0;
		else if(f_fps == 25.0)
			nFrameRateIndex = 1;
		else if(f_fps == 15.0)
			nFrameRateIndex = 2;
		else if(f_fps == 12.50)
			nFrameRateIndex = 3;
		else if(f_fps == 10.0)
			nFrameRateIndex = 4;
		
		if(nFrameRateIndex != -1)
			m_videoConfig.fpscfg.frame_rate =(unsigned long)(VideoFrameRateList[nFrameRateIndex].value *1001.0 + 0.05);
	}*/

	if(i_channels)
		m_audioConfig.Channels = i_channels;
	if(i_samplespersec)
		m_audioConfig.SampleRate= i_samplespersec;
	if(i_bitspersample)
		m_audioConfig.SampleBits= i_bitspersample;	
}
void CMP4XV3GrapBuilder::SetMp4xVideoCodecBitRate(int codec_index)
{
	m_videoConfig.ctlcfg.target_bitrate = i_vb * 1000;
	if(codec_index == MAKEFOURCC('m','p','4','v'))
	{
		m_videoConfig.ctlcfg.peak_bitrate   = m_videoConfig.ctlcfg.target_bitrate *10;
		m_videoConfig.ctlcfg.vbv_buffer		= m_videoConfig.ctlcfg.target_bitrate *10;
	}
	else if(codec_index == MAKEFOURCC('m','p','4','s')||
		codec_index == MAKEFOURCC('W','M','V','2'))
	{
		m_videoConfig.ctlcfg.peak_bitrate   = m_videoConfig.ctlcfg.target_bitrate ;
		m_videoConfig.ctlcfg.vbv_buffer		= m_videoConfig.ctlcfg.target_bitrate ;
	}
	else if(codec_index == MAKEFOURCC('m','p','2','v'))
	{
		m_videoConfig.ctlcfg.peak_bitrate   = m_videoConfig.ctlcfg.target_bitrate * 10;
		m_videoConfig.ctlcfg.vbv_buffer		= m_videoConfig.ctlcfg.target_bitrate * 10;
	}
	else if(codec_index == MAKEFOURCC('m','p','1','v'))
	{
		m_videoConfig.ctlcfg.peak_bitrate   = m_videoConfig.ctlcfg.target_bitrate * 10;
		m_videoConfig.ctlcfg.vbv_buffer		= m_videoConfig.ctlcfg.target_bitrate * 10;
	}
	else
	{
		m_videoConfig.ctlcfg.peak_bitrate   = m_videoConfig.ctlcfg.target_bitrate * 10;
		m_videoConfig.ctlcfg.vbv_buffer		= m_videoConfig.ctlcfg.target_bitrate * 10;
	}
}
BOOL	CMP4XV3GrapBuilder::IsSupportHardCodec(int i_codec)
{
	if(i_codec == MAKEFOURCC('m','p','4','v'))
	{
		return TRUE;
	}
	else if(i_codec == MAKEFOURCC('m','p','4','s')||
		i_codec == MAKEFOURCC('M','P','4','S'))
	{
		return TRUE;
	}
	else if(i_codec == MAKEFOURCC('m','p','2','v'))
	{
		return TRUE;
	}
	else if(i_codec == MAKEFOURCC('m','p','1','v'))
	{
		return TRUE;
	}
	return FALSE;
}
void CMP4XV3GrapBuilder::ChangeMP4XPCIV3CodecVideoSetting(int codec_index)
{
	int SystemCapIndex = 0;
	int	StreamIndex  = 0;
	int FrameRateIndex = 0;
	int ResolutionIndex = 0;
	int BitrateIndex = 0;

	char StreamName[255];
	if(codec_index == MAKEFOURCC('m','p','4','v'))
	{
		strcpy(StreamName, "DIVX MPEG4, IP Only");
	}
	else if(codec_index == MAKEFOURCC('m','p','4','s')||
		codec_index == MAKEFOURCC('M','P','4','S'))
	{
		strcpy(StreamName, "Microsoft MPEG4, IP Only");
	}
	else if(codec_index == MAKEFOURCC('m','p','2','v'))
	{
		strcpy(StreamName, "MPEG2, IPONLY");
	}
	else if(codec_index == MAKEFOURCC('m','p','1','v'))
	{
		strcpy(StreamName, "MPEG1, IPB");
	}
	else
		return ;
	unsigned int CurSel = 0;
	for( unsigned int i = 0 ; i < m_VideoProfiles._num_of_stream_profiles ; i ++ )
		if ( strcmp((LPSTR)m_VideoProfiles._stream_profiles[i].header.name, StreamName) == 0 ) CurSel = i;
	StreamIndex = CurSel;

	char ResolutionName[256];
	char FrameRateName[256];
	//
	//2006/03/23 skytone.
	//
	float vfr = f_fps;
	AnalogVideoStandard VideoStandard = (AnalogVideoStandard)i_VideoStandard;
	if(VideoStandard <= TVStandard_NTSC_433)
	{
		strcpy(ResolutionName, "NTSC SD");
		if(vfr > 28.0)
			strcpy(FrameRateName, "NTSC 29.97fps");
		else if(vfr < 28.0 && vfr > 16)
			strcpy(FrameRateName, "NTSC 15fps");
		else if(vfr < 16.0 && vfr > 6)
			strcpy(FrameRateName, "NTSC 10fps");
		else
			strcpy(FrameRateName, "NTSC 5fps");
	}
	else if(VideoStandard > TVStandard_NTSC_433 && VideoStandard <= AnalogVideo_PAL_60)
	{
		strcpy(ResolutionName, "PAL SD");
		if(vfr > 20.0)
			strcpy(FrameRateName, "PAL 25fps");
		else
			strcpy(FrameRateName, "PAL 12.5fps");
	}
	else
	{
		strcpy(ResolutionName, "SECAM SD");
		if(vfr > 24.0)
			strcpy(FrameRateName, "SECAM 25fps");
		else
			strcpy(FrameRateName, "SECAM 12.5fps");
	}
	CurSel = 0;
	for( i = 0 ; i < m_VideoProfiles._num_of_resolution_profiles ; i ++ )
		if ( strcmp((LPSTR)m_VideoProfiles._resolution_profiles[i].header.name, ResolutionName) == 0 ) CurSel = i;
	ResolutionIndex = CurSel;
	
	CurSel = 0;
	for(  i = 0 ; i < m_VideoProfiles._num_of_framerate_profiles ; i ++ )
		if ( strcmp((LPSTR)m_VideoProfiles._framerate_profiles[i].header.name, FrameRateName) == 0 ) CurSel = i;
	FrameRateIndex = CurSel;

	char BitrateName[256];
	strcpy(BitrateName, "Constant 2M");
	for(  i = 0 ; i < m_VideoProfiles._num_of_bitrate_profiles ; i ++ )
		if ( strcmp((LPSTR)m_VideoProfiles._bitrate_profiles[i].header.name, BitrateName) == 0 ) CurSel = i;
	BitrateIndex = CurSel;

	long lCtlReserved = m_videoConfig.ctlcfg.reserved;
	m_videoConfig.strcfg = m_VideoProfiles._stream_profiles[StreamIndex];
	m_videoConfig.fpscfg = m_VideoProfiles._framerate_profiles[FrameRateIndex];
	m_videoConfig.rescfg = m_VideoProfiles._resolution_profiles[ResolutionIndex];
	m_videoConfig.ctlcfg = m_VideoProfiles._bitrate_profiles[BitrateIndex];
	if(codec_index == MAKEFOURCC('m','p','4','v'))
	{
		m_videoConfig.strcfg.compress_mode = MPEG4;
		m_videoConfig.strcfg.sequence	   = IPONLY;
		m_videoConfig.strcfg.mpeg4_mode	   = 1;
		m_videoConfig.strcfg.gop_mode	   = 1;
		m_videoConfig.strcfg.gop_size	   = 30;
		m_videoConfig.strcfg.search_range  = 128;
		m_videoConfig.strcfg.gop_head_enable = 1;
		m_videoConfig.strcfg.seq_head_enable = 1;
		m_videoConfig.strcfg.aspect_ratio	 = 1;
		m_videoConfig.strcfg.DVD_compliant	 = 0;
		m_videoConfig.strcfg.reserved		 = 0;
	}
	else if(codec_index == MAKEFOURCC('m','p','4','s')||
		codec_index == MAKEFOURCC('M','P','4','S'))
	{
		m_videoConfig.strcfg.compress_mode = MPEG4;
		m_videoConfig.strcfg.sequence	   = IPONLY;
		m_videoConfig.strcfg.mpeg4_mode	   = 2;
		m_videoConfig.strcfg.gop_mode	   = 0;
		m_videoConfig.strcfg.gop_size	   = 30;
		m_videoConfig.strcfg.search_range  = 64;
		m_videoConfig.strcfg.gop_head_enable = 0;
		m_videoConfig.strcfg.seq_head_enable = 0;
		m_videoConfig.strcfg.aspect_ratio	 = 1;
		m_videoConfig.strcfg.DVD_compliant	 = 0;
		m_videoConfig.strcfg.reserved		 = 0;
	}
	else if(codec_index == MAKEFOURCC('m','p','2','v'))
	{
		m_videoConfig.strcfg.compress_mode = MPEG2;
		m_videoConfig.strcfg.sequence	   = IPONLY;
		m_videoConfig.strcfg.gop_mode	   = 0;
		m_videoConfig.strcfg.gop_size	   = 15;
		m_videoConfig.strcfg.search_range  = 128;
		m_videoConfig.strcfg.gop_head_enable = 1;
		m_videoConfig.strcfg.seq_head_enable = 1;
		m_videoConfig.strcfg.aspect_ratio	 = 1;
		m_videoConfig.strcfg.DVD_compliant	 = 0;
		m_videoConfig.strcfg.reserved		 = 0;

		//m_videoConfig.ctlcfg.peak_bitrate	 = 9800000;
		//m_videoConfig.ctlcfg.vbv_buffer		 = 1835008;
	}
	else if(codec_index == MAKEFOURCC('m','p','1','v'))
	{
		m_videoConfig.strcfg.compress_mode = MPEG1;
		m_videoConfig.strcfg.sequence	   = IPB;
		m_videoConfig.strcfg.gop_mode	   = 0;
		m_videoConfig.strcfg.gop_size	   = 15;
		m_videoConfig.strcfg.search_range  = 128;
		m_videoConfig.strcfg.gop_head_enable = 1;
		m_videoConfig.strcfg.seq_head_enable = 1;
		m_videoConfig.strcfg.aspect_ratio	 = 1;
		m_videoConfig.strcfg.DVD_compliant	 = 0;

		//m_videoConfig.ctlcfg.peak_bitrate	 = 1151929;
		//m_videoConfig.ctlcfg.vbv_buffer		 = 327680;
	}
	/*
	m_videoConfig.ctlcfg.reserved	= lCtlReserved;
	m_videoConfig.fpscfg.reserved	= 0;
	m_videoConfig.misccfg.reserved	= 0;
	m_videoConfig.misccfg.header.flags	= 0;
	m_videoConfig.misccfg.header.size	= sizeof(TCFGMISC);
	m_videoConfig.strcfg.reserved	= 0;
	m_videoConfig.syscfg.reserved	= 0;*/


}
HRESULT CMP4XV3GrapBuilder::CollectMP4XPCIV3Config()
{
	HRESULT hr = S_OK;
	
	if(m_pIGOChipPCI)
	{
		hr = m_pIGOChipPCI->GetVideoConfig(&m_videoConfig);
		hr = m_pIGOChipPCI->GetVideoCapabilities(&m_VideoCaps);
		if ( FAILED(hr) ) return hr;
		m_VideoCaps._num_of_configurations = 0;
		m_VideoCaps._configurations = NULL;
		if ( GetVideoProfiles(&m_VideoCaps, &m_VideoProfiles) == FALSE )
			return E_NOINTERFACE;
		
	}
	else
		hr = E_NOINTERFACE;
	if(FAILED(hr))
		CreateMP4XPCIV3VideoConfig();
	
	if(m_pAudioCaptureStreamConfig)
	{
		AM_MEDIA_TYPE* pmt = NULL;
		if(SUCCEEDED(hr = m_pAudioCaptureStreamConfig->GetFormat(&pmt)))
		{
			if(pmt->formattype == FORMAT_WaveFormatEx)
			{
				WAVEFORMATEX *pwft = (WAVEFORMATEX*)pmt->pbFormat;
				
				m_audioConfig.Format		= pwft->wFormatTag;
				m_audioConfig.SampleRate	= pwft->nSamplesPerSec;
				m_audioConfig.Channels		= pwft->nChannels;
				m_audioConfig.SampleBits	= pwft->wBitsPerSample;
				m_audioConfig.ExtSize		=0;
				m_audioConfig.SamplesPerBlock = 0;
				m_audioConfig.BlockAlign	  = pwft->nBlockAlign;
				m_audioConfig.AvgBytesPerSec  = pwft->nAvgBytesPerSec;
			}
			else
				hr = E_UNEXPECTED;
			
			DeleteMediaType(pmt);
		}
	}
	else
		hr = E_NOINTERFACE;
	if(FAILED(hr))
		CreateMP4XPCIV3AudioConfig();
	
	return hr;
}
void CMP4XV3GrapBuilder::CreateMP4XPCIV3VideoConfig()
{
	//video config
	memset(&m_videoConfig, 0, sizeof(m_videoConfig));
	//m_AnalogVideoStandard	=	PhysConn_Video_Composite ;
	//m_PhysicalConnectorType	=	GetVideoInput();	

	char	strcfgName[255] = "MPEG4, DivX, IPB";
	int		iCurCompressMode	= 0x04;
	int		iCurSequence		= 0x03;
	int		iCurGOPMode		= 0x01;
	int		m_iGOPSize		= 90;
	int		iCurMPEG4Mode	= 0x01;
	int		iCurDeinterlaceMode	= 0x00;
	int		iCurSearchRange		= 128;
	int		m_bGOPHeadEnable	= 0x01;
	int		m_bSeqHeadEnable	= 0x01;
	int		iCurAspectRatio		= 0x01;
	int		m_bDVDCompliant		= 0x00;
	char	fpscfgName[255]		= "PAL 25 fps";
	int		iCurFrameRate		= 25025;
	int		m_iDropFrame		= 0x00;
	int		m_bIVTCEnable		= 0x00;
	char	rescfgName[255] = "720 x 576";
	int		iCurWidth			= 720;
	int		iCurHeight			= 576;
	int		m_bHSubWindow		= 0x01;
	int		m_bVSubWindow		= 0x01;
	int		m_iHSubOffset		= 0x00;
	int		m_iVSubOffset		= 0x00;
	int		m_bHScaleEnable		= 0x00;
	int		m_bVScaleEnable		= 0x00;
	int		m_bSubSample		= 0x00;
	int		iCurTVStandard		= TVStandard_PAL_Mask;
	char	ctlcfgName[255]		= "CBR: 1500000 bps";
	int		m_iTargetBitrate	= 1500000;
	int		m_iPeakBitrate		= 15000000;
	int		m_iVBVBuffer		= 15000000;
	int		m_iConvergeSpeed	= 50;
	int		m_iLambda			= 20;
	int		m_iQ				= 64; 
	int		m_iIQ				= 0x02;
	int		m_iPQ				= 0x02;
	int		m_iBQ				= 0x02;
	int		m_bCountQmin		= 2;
	int		m_bCountQmax		= 31;
	BOOL	m_bCountDupFrameEnable	= FALSE;
	BOOL	m_bCountMBBRCEnable		= FALSE;
	BOOL	m_bCountBRCWindowSize	= TRUE;

	//	DWORD	strFlag = 0x30000011;
	DWORD	strFlag				= 0x30000000 | FLAGS_STREAM_COMPRESS_MODE | FLAGS_STREAM_MPEG4_MODE\
		|FLAGS_STREAM_SEQUENCE_MODE|FLAGS_STREAM_GOP_MODE|FLAGS_STREAM_GOP_SIZE\
		|FLAGS_STREAM_ASPECT_RATIO|FLAGS_STREAM_SEARCH_RANGE|FLAGS_STREAM_DEINTERLACE_MODE\
		|FLAGS_STREAM_GOPHEAD_ENABLE|FLAGS_STREAM_SEQHEAD_ENABLE ;
	//	DWORD	fpsFlag = 0x30000009;
	DWORD	fpsFlag				= 0x30000000 | FLAGS_FRAMERATE_FRAMERATE |FLAGS_FRAMERATE_TVSTANDARD;

	//	DWORD	ctlFlag = 0x30000084;
	DWORD	ctlFlag				= 0x30000000 | FLAGS_BITRATE_TARGET | FLAGS_BITRATE_Q\
		|FLAGS_BITRATE_PEAK|FLAGS_BITRATE_VBV_BUFFER|FLAGS_BITRATE_CONVERGE_SPEED\
		|FLAGS_BITRATE_LAMBDA; 
	//	int		resFlag = 0x30000e0f;
	int		resFlag				= 0x30000000 | FLAGS_RESOLUTION_WIDTH | FLAGS_RESOLUTION_HEIGHT | FLAGS_RESOLUTION_TVSTANDARD \
		| FLAGS_RESOLUTION_MAX_BITRATE | FLAGS_RESOLUTION_MIN_BITRATE;

	ctlFlag |= (m_bCountQmin ? FLAGS_BITRATE_QMIN : 0x0);
	ctlFlag |= (m_bCountQmax ? FLAGS_BITRATE_QMAX : 0x0);
	ctlFlag |= (m_bCountDupFrameEnable ? FLAGS_BITRATE_DUP_ENABLE : 0x0);
	ctlFlag |= (m_bCountMBBRCEnable ? FLAGS_BITRATE_MBBRC_ENABLE : 0x0);
	ctlFlag |= (m_bCountBRCWindowSize ? FLAGS_BITRATE_BRC_WINDOW : 0x0);

	ctlFlag = 0x300131fc;

	strcpy((char*)(m_videoConfig.strcfg.header.name), strcfgName);
	strcpy((char*)(m_videoConfig.strcfg.header.desc), strcfgName);
	m_videoConfig.strcfg.header.flags = strFlag;
	m_videoConfig.strcfg.header.size = sizeof(TCFGSTREAM);
	m_videoConfig.strcfg.compress_mode = (EVideoFormat)iCurCompressMode;
	m_videoConfig.strcfg.sequence = (ESequenceMode)iCurSequence;
	m_videoConfig.strcfg.gop_mode = iCurGOPMode;
	m_videoConfig.strcfg.gop_size = m_iGOPSize;
	m_videoConfig.strcfg.mpeg4_mode = iCurMPEG4Mode;
	m_videoConfig.strcfg.deinterlace_mode = iCurDeinterlaceMode;
	m_videoConfig.strcfg.search_range = iCurSearchRange;
	m_videoConfig.strcfg.gop_head_enable = m_bGOPHeadEnable;
	m_videoConfig.strcfg.seq_head_enable = m_bSeqHeadEnable;
	m_videoConfig.strcfg.aspect_ratio = iCurAspectRatio;
	m_videoConfig.strcfg.DVD_compliant = m_bDVDCompliant;
	strcpy((char*)(m_videoConfig.fpscfg.header.name), fpscfgName);
	strcpy((char*)(m_videoConfig.fpscfg.header.desc), fpscfgName);
	m_videoConfig.fpscfg.header.flags = fpsFlag;
	m_videoConfig.fpscfg.header.size = sizeof(TCFGFRAMERATE);
	m_videoConfig.fpscfg.tv_standard = (TV_STANDARD)iCurTVStandard;
	m_videoConfig.fpscfg.frame_rate = iCurFrameRate;
	m_videoConfig.fpscfg.drop_frame = m_iDropFrame;
	m_videoConfig.fpscfg.ivtc_enable = m_bIVTCEnable;
	m_videoConfig.fpscfg.reserved	= 0;

	strcpy((char*)(m_videoConfig.rescfg.header.name), rescfgName);
	strcpy((char*)(m_videoConfig.rescfg.header.desc), rescfgName);
	m_videoConfig.rescfg.header.flags = resFlag;
	m_videoConfig.rescfg.header.size = sizeof(TCFGRESOLUTION);
	m_videoConfig.rescfg.width = iCurWidth;
	m_videoConfig.rescfg.height = iCurHeight;
	m_videoConfig.rescfg.h_sub_window = m_bHSubWindow;
	m_videoConfig.rescfg.v_sub_window = m_bVSubWindow;
	m_videoConfig.rescfg.h_sub_offset = m_iHSubOffset;
	m_videoConfig.rescfg.v_sub_offset = m_iVSubOffset;
	m_videoConfig.rescfg.h_scale_enb = m_bHScaleEnable;
	m_videoConfig.rescfg.v_scale_enb = m_bVScaleEnable;
	m_videoConfig.rescfg.sub_sample = m_bSubSample;
	m_videoConfig.rescfg.max_bitrate = 0; // no use
	m_videoConfig.rescfg.min_bitrate = 0; // no use
	m_videoConfig.rescfg.tv_standard = (TV_STANDARD)iCurTVStandard;
	m_videoConfig.rescfg.reserved	= 0;

	long lCtlReserved = 0;
	BOOL m_bDupFrameEnable = FALSE;
	BOOL m_bMBBRCEnable    = FALSE;
	int m_iBRCWindowSize   = 60;
	lCtlReserved |= (m_bCountQmin ? (m_bCountQmin&0x7f) : 0x0);
	lCtlReserved |= (m_bCountQmax ? (m_bCountQmax&0x7f)<<8 : 0x0);
	lCtlReserved |= (m_bCountDupFrameEnable ? (m_bDupFrameEnable ? 0x80 : 0x0) : 0x0);
	lCtlReserved |= (m_bCountMBBRCEnable ? (m_bMBBRCEnable ? 0x8000 : 0x0) : 0x0);
	lCtlReserved |= (m_bCountBRCWindowSize ? (m_iBRCWindowSize)<<16 : 0x0);

	strcpy((char*)(m_videoConfig.ctlcfg.header.name), ctlcfgName);
	strcpy((char*)(m_videoConfig.ctlcfg.header.desc), ctlcfgName);
	m_videoConfig.ctlcfg.header.flags = ctlFlag;
	m_videoConfig.ctlcfg.header.size = sizeof(TCFGBRCTRL);
	m_videoConfig.ctlcfg.target_bitrate = m_iTargetBitrate;
	m_videoConfig.ctlcfg.peak_bitrate = m_iPeakBitrate;
	m_videoConfig.ctlcfg.vbv_buffer = m_iVBVBuffer;
	m_videoConfig.ctlcfg.converge_speed = m_iConvergeSpeed;
	m_videoConfig.ctlcfg.lambda = m_iLambda;
	m_videoConfig.ctlcfg.Q = 64;
	m_videoConfig.ctlcfg.IQ = m_iIQ;
	m_videoConfig.ctlcfg.PQ = m_iPQ;
	m_videoConfig.ctlcfg.BQ = m_iBQ;
	m_videoConfig.ctlcfg.reserved	= lCtlReserved;

	m_videoConfig.fpscfg.reserved	= 0;
	m_videoConfig.misccfg.reserved	= 0;
	m_videoConfig.misccfg.header.flags	= 0;
	m_videoConfig.misccfg.header.size	= sizeof(TCFGMISC);
	m_videoConfig.strcfg.reserved	= 0;
	m_videoConfig.syscfg.reserved	= 0;


}
void CMP4XV3GrapBuilder::CreateMP4XPCIV3AudioConfig()
{
	//audio 
	memset(&m_audioConfig, 0, sizeof(m_audioConfig));
	int iCurAudioFormat = AUDIO_FORMAT_PCM;
	int iCurSamplingRate	= 0x0000bb80;
	int iCurChannel		= 0x02;
	int iCurSampleBits	= 0x10;
	m_audioConfig.Format = iCurAudioFormat;
	m_audioConfig.SampleRate = iCurSamplingRate;
	m_audioConfig.Channels = iCurChannel;
	m_audioConfig.SampleBits = iCurSampleBits;
	m_audioConfig.ExtSize =0;
	m_audioConfig.SamplesPerBlock = 0;
	if(m_audioConfig.Format == AUDIO_FORMAT_PCM)
	{
		m_audioConfig.BlockAlign = (unsigned short)(m_audioConfig.Channels * m_audioConfig.SampleBits / 8);
		m_audioConfig.AvgBytesPerSec = m_audioConfig.SampleRate * m_audioConfig.BlockAlign;
	}
	else
	{
		m_audioConfig.BlockAlign = 256;
		m_audioConfig.AvgBytesPerSec = m_audioConfig.SampleRate * m_audioConfig.Channels * m_audioConfig.SampleBits/8;
	}	

}
HRESULT	CMP4XV3GrapBuilder::ReleaseInterface()
{
	SAFE_RELEASE(m_pIGOChipPCI);
	
	return CDeviceGrapBuilder1::ReleaseInterface();
}
void    CMP4XV3GrapBuilder::CheckMP4XPCIV3Config()
{
	
	if ( ( m_videoConfig.rescfg.width % 16 ) != 0 || ( m_videoConfig.rescfg.height % 16 ) != 0 )
	{
		m_videoConfig.rescfg.width -= ( m_videoConfig.rescfg.width % 16);
		m_videoConfig.rescfg.height-= ( m_videoConfig.rescfg.height % 16);
	}

	if ( ( m_videoConfig.strcfg.compress_mode == H263 ) && ( m_videoConfig.strcfg.sequence == IPB ) )
	{
		m_videoConfig.strcfg.sequence = IPONLY;
	}

	if ( ( m_videoConfig.strcfg.compress_mode == MOTIONJPEG ) && ( m_videoConfig.strcfg.sequence != IONLY ) )
	{
		m_videoConfig.strcfg.sequence = IONLY;
	}

	if ( ( m_videoConfig.strcfg.compress_mode != MPEG2 && m_videoConfig.strcfg.compress_mode != MPEG1 ) && ( m_videoConfig.strcfg.DVD_compliant != 0 ) )
	{
		m_videoConfig.strcfg.DVD_compliant = 0;
	}

	if ( ( m_videoConfig.strcfg.DVD_compliant != 0 ) &&  ( m_videoConfig.ctlcfg.target_bitrate <= 0 ) )
	{	
		m_videoConfig.ctlcfg.target_bitrate = 2000000;
	}

	if ( ( m_videoConfig.strcfg.compress_mode != MPEG4 ) && ( m_videoConfig.strcfg.mpeg4_mode != 0 ) )
	{
		m_videoConfig.strcfg.mpeg4_mode	= DIVX_MPEG4;
	}

	if ( ( m_videoConfig.strcfg.compress_mode == MPEG4 ) && 
		( m_videoConfig.strcfg.mpeg4_mode > 4 
		|| m_videoConfig.strcfg.mpeg4_mode < 0 ) )
	{
		m_videoConfig.strcfg.mpeg4_mode = DIVX_MPEG4;
	}
	// PrintMsg(1, ("max:%d, min %d, this: %d", m_videoConfig.rescfg.max_bitrate, m_videoConfig.rescfg.min_bitrate, m_videoConfig.ctlcfg.target_bitrate));
	if ( ( m_videoConfig.ctlcfg.target_bitrate > 0 ) &&  
		( m_videoConfig.rescfg.max_bitrate < m_videoConfig.ctlcfg.target_bitrate 
		|| m_videoConfig.rescfg.min_bitrate > m_videoConfig.ctlcfg.target_bitrate  ) )
	{

	}
	if ( m_videoConfig.strcfg.aspect_ratio > 3 || m_videoConfig.strcfg.aspect_ratio < 1 )
	{
		m_videoConfig.strcfg.aspect_ratio = 1;
	}
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	// ivtc can only be enabled when following is true
	// 1. interlaced source
	// 2. deinterlace mode == 1
	// 3. NTSC SD
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	if ( ( m_videoConfig.fpscfg.ivtc_enable != 0 ) &&  ( ( m_videoConfig.strcfg.deinterlace_mode != 1 ) 
		|| ( m_videoConfig.rescfg.width != 720 || m_videoConfig.rescfg.height != 480 ) 
		|| ( ( m_videoConfig.syscfg.tv_standard & TVStandard_NTSC_Mask ) == 0 ) 
		|| ( m_videoConfig.syscfg.format != 1 ) ) )
	{
		m_videoConfig.fpscfg.ivtc_enable = 0;
	}

	if ( ( m_videoConfig.strcfg.compress_mode != MPEG2 ) && ( m_videoConfig.strcfg.deinterlace_mode == 2 ) )
	{
		m_videoConfig.strcfg.deinterlace_mode = 1;
	}

	if ( ( m_videoConfig.strcfg.sequence == IPB ) && ( ( m_videoConfig.strcfg.gop_size % 3 ) != 0 ) )
	{
		m_videoConfig.strcfg.gop_size -= (m_videoConfig.strcfg.gop_size % 3);
	}

	if ( ( m_videoConfig.strcfg.compress_mode == MPEG4 ) && ( m_videoConfig.strcfg.mpeg4_mode == MICROSOFT_MPEG4 ) && ( m_videoConfig.strcfg.sequence == IPB ) )
	{
		m_videoConfig.strcfg.sequence = IPONLY;
	}

	if ( ( m_videoConfig.strcfg.compress_mode == MPEG4 ) && ( m_videoConfig.strcfg.mpeg4_mode == RCC_MPEG4 ) && ( m_videoConfig.strcfg.sequence == IPB ) )
	{
		m_videoConfig.strcfg.sequence = IPONLY;
	}

	if ( m_videoConfig.strcfg.DVD_compliant != 0 && m_videoConfig.strcfg.compress_mode == MPEG2 ) 
	{
		if ( ( m_videoConfig.fpscfg.ivtc_enable != 0 ) && ( m_videoConfig.strcfg.gop_size != 12 ) )
		{
			m_videoConfig.strcfg.gop_size = 12;
		}

		if ( ( m_videoConfig.fpscfg.ivtc_enable == 0 ) && ( m_videoConfig.strcfg.gop_size != 15 ) )
		{
			m_videoConfig.strcfg.gop_size = 15;
		}
	}

	if ( m_videoConfig.syscfg.format == 1 && m_videoConfig.strcfg.deinterlace_mode == 0 )
	{
		if ( m_videoConfig.syscfg.framerate * 2 != m_videoConfig.fpscfg.frame_rate * ( m_videoConfig.fpscfg.drop_frame + 1 ) )
		{
			m_videoConfig.syscfg.framerate  = m_videoConfig.fpscfg.frame_rate * ( m_videoConfig.fpscfg.drop_frame + 1 ) / 2;
		}
	}
	else if ( m_videoConfig.fpscfg.drop_frame != 0 ) 
	{
		if ( m_videoConfig.syscfg.framerate != m_videoConfig.fpscfg.frame_rate * ( m_videoConfig.fpscfg.drop_frame + 1 ) )
		{
			m_videoConfig.syscfg.framerate = m_videoConfig.fpscfg.frame_rate * ( m_videoConfig.fpscfg.drop_frame + 1 );
		}
	}

	if ( (UINT32)(m_videoConfig.rescfg.width * ( 1 + m_videoConfig.rescfg.h_scale_enb )) > (UINT32)(m_videoConfig.syscfg.sensor_h / ( 1 + m_videoConfig.rescfg.sub_sample )) )
	{

	}

	if ( (UINT32)(m_videoConfig.rescfg.height * ( 1 + m_videoConfig.rescfg.v_scale_enb )) > (UINT32)(m_videoConfig.syscfg.sensor_v / ( 1 + m_videoConfig.rescfg.sub_sample )) )
	{

	}

	if ( m_videoConfig.strcfg.compress_mode == H263 && m_videoConfig.strcfg.search_range != 32 )
	{
		m_videoConfig.strcfg.search_range = 32;
	}	

	if ( m_videoConfig.strcfg.compress_mode == MPEG4 && m_videoConfig.strcfg.mpeg4_mode == MICROSOFT_MPEG4 )
	{
		if ( m_videoConfig.strcfg.search_range != 64 ) 
		{
			m_videoConfig.strcfg.search_range = 64;
		}
		if ( m_videoConfig.strcfg.gop_head_enable != 0 || m_videoConfig.strcfg.seq_head_enable != 0 )
		{
			m_videoConfig.strcfg.gop_head_enable = 0;
			m_videoConfig.strcfg.seq_head_enable = 0;
		}
	}

	if ( m_videoConfig.strcfg.compress_mode == MPEG4 && m_videoConfig.strcfg.mpeg4_mode == RCC_MPEG4 )
	{
		if ( m_videoConfig.strcfg.gop_head_enable != 0 ) 
		{	
			m_videoConfig.strcfg.gop_head_enable = 0;
		}
	}

	if ( m_videoConfig.strcfg.compress_mode == MPEG4 && m_videoConfig.strcfg.mpeg4_mode == DIVX_MPEG4 && m_videoConfig.strcfg.gop_mode != 1 )
	{
		m_videoConfig.strcfg.gop_mode = 1;
	}

	if ( m_videoConfig.strcfg.search_range != 32 &&
		m_videoConfig.strcfg.search_range != 64 &&
		m_videoConfig.strcfg.search_range != 128 )
	{
		m_videoConfig.strcfg.search_range = 64;
	}

	if ( m_videoConfig.syscfg.format != 1 && m_videoConfig.strcfg.deinterlace_mode == 0 )
	{
		m_videoConfig.strcfg.deinterlace_mode = 1;
	}

	if ( m_videoConfig.syscfg.format == 1 && m_videoConfig.strcfg.deinterlace_mode == 0 && m_videoConfig.fpscfg.drop_frame == 0 )
	{
		m_videoConfig.fpscfg.drop_frame = 1;
	}

	if ( m_videoConfig.ctlcfg.target_bitrate > 0x1000000)
	{
		m_videoConfig.ctlcfg.target_bitrate = 2000000;
	}

	if ( m_videoConfig.ctlcfg.peak_bitrate > 0x4000000 )
	{
		m_videoConfig.ctlcfg.peak_bitrate = 4000000;
	}
	if(m_videoConfig.rescfg.width <= 352)
	{
		m_videoConfig.misccfg.h_filter_mode = GO7007SB_MIDIAN;
		m_videoConfig.misccfg.v_filter_mode = GO7007SB_MIDIAN;
	}
	else
	{
		m_videoConfig.misccfg.h_filter_mode = GO7007SB_NOFILTER;
		m_videoConfig.misccfg.v_filter_mode = GO7007SB_NOFILTER;
	}
	if(m_audioConfig.Format == AUDIO_FORMAT_PCM)
	{
		m_audioConfig.BlockAlign = (unsigned short)(m_audioConfig.Channels * m_audioConfig.SampleBits / 8);
		m_audioConfig.AvgBytesPerSec = m_audioConfig.SampleRate * m_audioConfig.BlockAlign;
	}
	else
	{
		m_audioConfig.BlockAlign = 256;
		m_audioConfig.AvgBytesPerSec = m_audioConfig.SampleRate * m_audioConfig.Channels * m_audioConfig.SampleBits/8;
	}	

}

HRESULT CMP4XV3GrapBuilder::ApplyMP4XPCIV3VideoConfig(IAMStreamConfig* stream_config, TCFGVIDEOEX* video_config, TYPE_VIDEOCONFIG type)
{

	if(type == SOFTWARE_CAPTURE)
	{
		return ApplyMP4XPCIV3VideoConfig_Software_Capture(stream_config, video_config);
	}
	else if(type == HARDWARE_CAPTURE)
	{
		return ApplyMP4XPCIV3VideoConfig_Hardware_Capture(stream_config, video_config);
	}
	else if(type == SOFTWAVE_PREVIEW)
	{
		return ApplyMP4XPCIV3VideoConfig_Software_Preview(stream_config, video_config);
	}
	else
		return VFW_E_CHANGING_FORMAT;

}
HRESULT CMP4XV3GrapBuilder::ApplyMP4XPCIV3VideoConfig_Hardware_Capture(IAMStreamConfig* stream_config, TCFGVIDEOEX* video_config)
{
	HRESULT hr =S_OK;
	int caps_count = 0, caps_size = 0;

	AM_MEDIA_TYPE* pmt;
	VIDEO_STREAM_CONFIG_CAPS caps;

	BOOL bOK = FALSE;

	if ( stream_config == NULL ) 
	{	
		if(bOK)
			return S_OK;
		else
			return E_FAIL;
	}
	stream_config->GetNumberOfCapabilities(&caps_count, &caps_size);

	char szDebugInfo[1000];

	for ( int i = 0 ; i < caps_count ; i ++ )
	{
		hr = stream_config->GetStreamCaps(i, &pmt, (BYTE*)&caps);
		if ( FAILED(hr) ) { OutputDebugString("[App]: GetSteamCaps Failed!"); continue; }

		unsigned long normal_format_size;
		TCFG_FORMAT_EXTENSION* extension = NULL;
		switch ( video_config->strcfg.compress_mode )
		{
		case MPEG1:
			{
					if ( pmt->subtype != MEDIASUBTYPE_MPEG1Payload ) goto next_stream_caps;
					if ( pmt->formattype != FORMAT_MPEGVideo ) goto next_stream_caps;
					MPEG1VIDEOINFO* format = (MPEG1VIDEOINFO*)pmt->pbFormat;
					if ( format->hdr.bmiHeader.biWidth != (int)video_config->rescfg.width ) goto next_stream_caps;
					if ( format->hdr.bmiHeader.biHeight != (int)video_config->rescfg.height ) goto next_stream_caps;

					normal_format_size = SIZE_MPEG1VIDEOINFO(format);

					format->hdr.AvgTimePerFrame = (ULONGLONG)((double)(10000000) / f_fps);
					format->hdr.bmiHeader.biWidth = video_config->rescfg.width;
					format->hdr.bmiHeader.biHeight = video_config->rescfg.height;
					format->hdr.bmiHeader.biSizeImage = video_config->rescfg.width * video_config->rescfg.height * 3 / 2;
					format->hdr.dwBitRate = video_config->ctlcfg.target_bitrate;
					// mpeg1 sequence header??

					if ( pmt->cbFormat > normal_format_size )
					{
						assert( pmt->cbFormat == normal_format_size + sizeof(TCFG_FORMAT_EXTENSION) );
						extension = (TCFG_FORMAT_EXTENSION*)(pmt->pbFormat + normal_format_size);
						extension->_stream = video_config->strcfg;
						extension->_framerate = video_config->fpscfg;
						extension->_resolution = video_config->rescfg;
						extension->_bitrate = video_config->ctlcfg;
					}

					sprintf(szDebugInfo, "[App]: MPEG1 width=%d height=%d; fps=%d; bps=%d\r\n", 
							format->hdr.bmiHeader.biWidth,
							format->hdr.bmiHeader.biHeight,
							/*long10010000000/*/format->hdr.AvgTimePerFrame,
							format->hdr.dwBitRate);

					OutputDebugString(szDebugInfo);
					break;
			}
		case MPEG2:
			{
					if ( pmt->subtype != MEDIASUBTYPE_MPEG2_VIDEO ) goto next_stream_caps;
					if ( pmt->formattype != FORMAT_MPEG2Video ) goto next_stream_caps;
					MPEG2VIDEOINFO* format = (MPEG2VIDEOINFO*)pmt->pbFormat;
					if ( format->hdr.bmiHeader.biWidth != (int)video_config->rescfg.width ) goto next_stream_caps;
					if ( format->hdr.bmiHeader.biHeight != (int)video_config->rescfg.height ) goto next_stream_caps;

					normal_format_size = SIZE_MPEG2VIDEOINFO(format);
					
					//
					//2006/03/23 skytone.
					//
					//format->hdr.AvgTimePerFrame = /*(ULONGLONG)(1001000000) /*/ video_config->fpscfg.frame_rate;
					format->hdr.AvgTimePerFrame = (ULONGLONG)((double)(10000000)/f_fps);
					format->hdr.bmiHeader.biWidth = video_config->rescfg.width;
					format->hdr.bmiHeader.biHeight = video_config->rescfg.height;
					format->hdr.bmiHeader.biSizeImage = video_config->rescfg.width * video_config->rescfg.height * 3 / 2;
					format->hdr.dwBitRate = video_config->ctlcfg.target_bitrate;
					format->hdr.dwPictAspectRatioX = video_config->rescfg.width;
					format->hdr.dwPictAspectRatioY = video_config->rescfg.height;
	
					if ( pmt->cbFormat > normal_format_size )
					{
						assert( pmt->cbFormat == normal_format_size + sizeof(TCFG_FORMAT_EXTENSION) );
						extension = (TCFG_FORMAT_EXTENSION*)(pmt->pbFormat + normal_format_size);
						extension->_stream = video_config->strcfg;
						extension->_framerate = video_config->fpscfg;
						extension->_resolution = video_config->rescfg;
						extension->_bitrate = video_config->ctlcfg;
					}					

					sprintf(szDebugInfo, "MPEG2 width: %d height: %d fps: %d bps: %d", 
							format->hdr.bmiHeader.biWidth,
							format->hdr.bmiHeader.biHeight,
							long(format->hdr.AvgTimePerFrame),
							format->hdr.dwBitRate);

					OutputDebugString(szDebugInfo);

					break;

					
			}
		case MPEG4:
		case H263:
		case MOTIONJPEG:
			{
				if ( pmt->formattype != FORMAT_VideoInfo ) goto next_stream_caps;
				VIDEOINFOHEADER* format = (VIDEOINFOHEADER*)pmt->pbFormat;
				if ( format->bmiHeader.biWidth != (int)video_config->rescfg.width ) goto next_stream_caps;
				if ( format->bmiHeader.biHeight != (int)video_config->rescfg.height ) goto next_stream_caps;
				if ( video_config->strcfg.compress_mode == MPEG4 )
				{
					switch ( video_config->strcfg.mpeg4_mode )
					{
					case DIVX_MPEG4:
						if ( format->bmiHeader.biCompression != FCC_FORMAT_DIVX_MPEG4 ) goto next_stream_caps;
						break;
					case RCC_MPEG4:
						if ( format->bmiHeader.biCompression != FCC_FORMAT_RCC_MPEG4 ) goto next_stream_caps;
						break;
					case MICROSOFT_MPEG4:
						if ( format->bmiHeader.biCompression != FCC_FORMAT_MICROSOFT_MPEG4 ) goto next_stream_caps;
						break;
					case WIS_MPEG4:
						if ( format->bmiHeader.biCompression != FCC_FORMAT_WIS_MPEG4 ) goto next_stream_caps;
						break;
					default:
						assert(false);
					}
				}
				else if ( video_config->strcfg.compress_mode == H263 )
				{
					if ( format->bmiHeader.biCompression != FCC_FORMAT_H263 ) goto next_stream_caps;
				} 
				else if ( video_config->strcfg.compress_mode == MOTIONJPEG )
				{
					if ( format->bmiHeader.biCompression != FCC_FORMAT_MOTION_JPEG ) goto next_stream_caps;
				}

				normal_format_size = format->bmiHeader.biSize + SIZE_PREHEADER - sizeof(TCFG_FORMAT_EXTENSION);
				
				//
				//2006/03/23 skytone.
				//
				//format->AvgTimePerFrame = /*(ULONGLONG)(10010000000) /*/ video_config->fpscfg.frame_rate;
				format->AvgTimePerFrame =(ULONGLONG)((double)10000000/f_fps);
				format->bmiHeader.biWidth = video_config->rescfg.width;
				format->bmiHeader.biHeight = video_config->rescfg.height;
				format->bmiHeader.biSizeImage = video_config->rescfg.width * video_config->rescfg.height * 3 / 2;
				format->dwBitRate = video_config->ctlcfg.target_bitrate;

				unsigned int error = -1;
				if ( pmt->cbFormat > normal_format_size )
				{

					assert( pmt->cbFormat == normal_format_size + sizeof(TCFG_FORMAT_EXTENSION) );
					extension = (TCFG_FORMAT_EXTENSION*)(pmt->pbFormat + normal_format_size);
					extension->_stream = video_config->strcfg;
					extension->_framerate = video_config->fpscfg;
					extension->_resolution = video_config->rescfg;
					extension->_bitrate = video_config->ctlcfg;

					if ( video_config->strcfg.mpeg4_mode == MICROSOFT_MPEG4 )
					{
						char* seq_header;
						UINT32 seq_length = FormatMPEG4StreamSEQHeader(extension, &seq_header);
						memcpy( pmt->pbFormat + normal_format_size - seq_length, seq_header, seq_length);
					}
				}					

				break;
			}
		default:
			assert(false);
			DeleteMediaType(pmt);
			return hr;
		}
		if(m_pIGOChipPCI == NULL)
		{
			m_pEncoderFilter->QueryInterface(__uuidof(IGOChipPCI), (void**)&m_pIGOChipPCI);
		}
		if(m_pIGOChipPCI && extension)
		{
			unsigned int error;
		    m_pIGOChipPCI->SetVideoConfig(extension, &error);
			sprintf(szDebugInfo, "[App]: Patch: VIDEOINFO, IGOChip->SetVideoConfig error = %d\r\n", error);
			OutputDebugString(szDebugInfo);
		}
		SAFE_RELEASE(m_pIGOChipPCI);

		hr = stream_config->SetFormat(pmt);
		if ( FAILED(hr) ) 
		{ 
			OutputDebugString("[App]: set video config failed");
		};
		DeleteMediaType(pmt);

		return hr;

next_stream_caps:
		DeleteMediaType(pmt);
	}
	if(bOK)
		return S_OK;
	else
		return E_FAIL;
}
HRESULT CMP4XV3GrapBuilder::ApplyMP4XPCIV3VideoConfig_Software_Capture(IAMStreamConfig* stream_config, TCFGVIDEOEX* video_config)
{
	HRESULT hr =S_OK;
	int caps_count = 0, caps_size = 0;

	BOOL bSetConfig = FALSE;
	AM_MEDIA_TYPE* pmt = NULL;
	VIDEO_STREAM_CONFIG_CAPS caps;
	hr = 	stream_config->GetNumberOfCapabilities(&caps_count, &caps_size);
	if(FAILED(hr) || caps_count == 0)
		return hr;
	for(int i = 0; i < caps_count; i ++)
	{
		hr = stream_config->GetStreamCaps(i, &pmt, (BYTE*)&caps);
		if(FAILED(hr))continue;
	
		VIDEOINFOHEADER* format = (VIDEOINFOHEADER*)pmt->pbFormat;
		if ( pmt->formattype != FORMAT_VideoInfo ) goto next_stream_caps;

		if(format->bmiHeader.biCompression == mmioFOURCC('Y','U','Y','2'))
		{
			//
			//2006/03/23 skytone
			//
			//@if(format->AvgTimePerFrame == /*(ULONGLONG)(10010000000) /*/ video_config->fpscfg.frame_rate &&
			if(format->AvgTimePerFrame ==(ULONGLONG)((double)10000000/f_fps) &&
				format->bmiHeader.biWidth == video_config->rescfg.width &&
				format->bmiHeader.biHeight == video_config->rescfg.height)
			{
				hr = stream_config->SetFormat(pmt);
				DeleteMediaType(pmt);
				if(FAILED(hr))
					continue;
				bSetConfig = TRUE;
				break;
			}
			else
			{

				VIDEOINFOHEADER* format = (VIDEOINFOHEADER*)pmt->pbFormat;
//				format->rcSource.left	= video_config->rescfg.width;
//				format->rcSource.right  = video_config->rescfg.height;
//				format->rcTarget		= format->rcSource;
//				format->dwBitRate		= video_config->rescfg.width * video_config->rescfg.height * 16 * framerate;

//				format->AvgTimePerFrame = /*(ULONGLONG)(10010000000) /*/ video_config->fpscfg.frame_rate;
				
				//
				//2006/03/23 skytone
				//

				//format->AvgTimePerFrame = video_config->fpscfg.frame_rate;
				format->AvgTimePerFrame=(ULONGLONG)((double)10000000/f_fps);
				format->bmiHeader.biWidth  = video_config->rescfg.width;
				format->bmiHeader.biHeight = video_config->rescfg.height;
				format->bmiHeader.biSizeImage = helper_GetBMISizeImage(format->bmiHeader);

				hr = stream_config->SetFormat(pmt);
				if(SUCCEEDED(hr))
				{
					DeleteMediaType(pmt);
					bSetConfig = TRUE;
					break;
				}

			}
		}
next_stream_caps:
		DeleteMediaType(pmt);
	}

	return hr;
}
HRESULT CMP4XV3GrapBuilder::ApplyMP4XPCIV3VideoConfig_Software_Preview(IAMStreamConfig* stream_config, TCFGVIDEOEX* video_config)
{
	HRESULT hr =S_OK;
	int caps_count = 0, caps_size = 0;

	BOOL bSetConfig = FALSE;
	AM_MEDIA_TYPE* pmt = NULL;
	VIDEO_STREAM_CONFIG_CAPS caps;
	hr = 	stream_config->GetNumberOfCapabilities(&caps_count, &caps_size);
	if(FAILED(hr) || caps_count == 0)
		return hr;
	for(int i = 0; i < caps_count; i ++)
	{
		hr = stream_config->GetStreamCaps(i, &pmt, (BYTE*)&caps);
		if(FAILED(hr))continue;

		VIDEOINFOHEADER* format = (VIDEOINFOHEADER*)pmt->pbFormat;

		//fix select mmioFOURCC('Y','U','Y','2') color space
		if(format->bmiHeader.biCompression == mmioFOURCC('Y','U','Y','2'))
		{
			//
			//2006/03/23 skytone
			//

			//if(format->AvgTimePerFrame == /*(ULONGLONG)(10010000000) /*/ video_config->fpscfg.frame_rate &&
			if(format->AvgTimePerFrame=(ULONGLONG)((double)10000000/f_fps) && 			
				format->bmiHeader.biWidth == video_config->rescfg.width &&
				format->bmiHeader.biHeight == video_config->rescfg.height)
			{
				hr = stream_config->SetFormat(pmt);
				DeleteMediaType(pmt);
				if(FAILED(hr))
					continue;
				bSetConfig = TRUE;
				break;
			}
			else
			{

				VIDEOINFOHEADER* format = (VIDEOINFOHEADER*)pmt->pbFormat;
				format->rcSource.left	= video_config->rescfg.width;
				format->rcSource.right  = video_config->rescfg.height;
				format->rcTarget		= format->rcSource;
				format->dwBitRate		= video_config->rescfg.width * video_config->rescfg.height * 16 * f_fps;
			
				//
				//2006/03/23 skytone
				//
				//format->AvgTimePerFrame = /*(ULONGLONG)(10010000000) /*/ video_config->fpscfg.frame_rate;
				format->AvgTimePerFrame = (ULONGLONG)((double)10000000/f_fps);
				format->bmiHeader.biWidth  = video_config->rescfg.width;
				format->bmiHeader.biHeight = video_config->rescfg.height;
				format->bmiHeader.biSizeImage = helper_GetBMISizeImage(format->bmiHeader);

				hr = stream_config->SetFormat(pmt);
				DeleteMediaType(pmt);
				bSetConfig = TRUE;
				break;

			}
		}
		DeleteMediaType(pmt);
	}

	return S_OK;
}
HRESULT CMP4XV3GrapBuilder::ApplyMP4XPCIV3AudioConfig(IAMStreamConfig* stream_config, AUDIO_CONFIG* audio_config)
{
	AM_MEDIA_TYPE* pmt;
	AUDIO_STREAM_CONFIG_CAPS caps;
	WAVEFORMATEX* format;

	if ( stream_config == NULL ) return E_POINTER;

	int caps_count = 0, caps_size = 0;
	stream_config->GetNumberOfCapabilities(&caps_count, &caps_size);

	//	char szDebugInfo[1000];

	for ( int i = 0 ; i < caps_count ; i ++ )
	{
		HRESULT hr = stream_config->GetStreamCaps(i, &pmt, (BYTE*)&caps);
		if ( FAILED(hr) ) { OutputDebugString("[DeviceControl]: GetSteamCaps Failed!"); continue; }

		if ( !IsEqualGUID(pmt->formattype, FORMAT_WaveFormatEx) )
		{
			goto next_stream_caps;
		}
		format = (WAVEFORMATEX*)pmt->pbFormat;			 

		switch ( format->wFormatTag )
		{
		case WAVE_FORMAT_PCM:
			if(format->wFormatTag != audio_config->Format){
				goto next_stream_caps;	
			}
			format->nChannels =  (WORD)audio_config->Channels;
			format->nSamplesPerSec = audio_config->SampleRate;
			format->wBitsPerSample = (WORD)audio_config->SampleBits;
			format->nBlockAlign = audio_config->BlockAlign;
			format->nAvgBytesPerSec = audio_config->AvgBytesPerSec;
			break;

		case WAVE_FORMAT_ADPCM:
			if(format->wFormatTag != audio_config->Format){
				goto next_stream_caps;	
			}
			format->nChannels =  (WORD)audio_config->Channels;
			format->nSamplesPerSec = audio_config->SampleRate;
			format->wBitsPerSample = (WORD)audio_config->SampleBits;
			format->nBlockAlign = audio_config->BlockAlign;
			format->nAvgBytesPerSec = audio_config->AvgBytesPerSec;
			break;

		case WAVE_FORMAT_IMA_ADPCM:
			if(format->wFormatTag != audio_config->Format){
				goto next_stream_caps;	
			}
			format->nChannels =  (WORD)audio_config->Channels;
			format->nSamplesPerSec = audio_config->SampleRate;
			format->wBitsPerSample = (WORD)audio_config->SampleBits;
			format->nBlockAlign = audio_config->BlockAlign;
			format->nAvgBytesPerSec = audio_config->AvgBytesPerSec;
			break;

		default:

			DeleteMediaType(pmt);
			return E_UNEXPECTED;
		}

		hr = stream_config->SetFormat(pmt);
		if ( FAILED(hr) ) { OutputDebugString("DeviceControl: set pin format failed"); };
		DeleteMediaType(pmt);

		return hr;

next_stream_caps:
		DeleteMediaType(pmt);
	}
	return E_UNEXPECTED;
}