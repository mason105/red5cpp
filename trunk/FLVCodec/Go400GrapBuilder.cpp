// Go400GrapBuilder.cpp: implementation of the CGo400GrapBuilder class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Go400GrapBuilder.h"
#include "vixscodecapi.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
#define VIDEOOUTPINNAME "Video Out"
#define GO400ENCODER_NAME "GOTRON MP-400 Encoder"

int GetPIDFromCoder(int i_codec);

CGo400GrapBuilder::CGo400GrapBuilder()
{
	m_piKsPropertySet = NULL;
	m_piConfig = NULL;
	m_piKsPropertyVideoOutPinSet = NULL;
	m_piVideoOutPinConfig = NULL;

}

CGo400GrapBuilder::~CGo400GrapBuilder()
{

}
int CGo400GrapBuilder::OpenDevice( CDeviceGrapBuilder *p_sys,
			   string devicename, 
			   string devicename_display,
		bool b_audio)
{
	if(!b_audio)
		return OpenGo400VideoDevice(p_sys, devicename, devicename_display, b_audio);
	else
		return OpenGo400AudioDevice(p_sys, devicename, devicename_display, b_audio);
}
int CGo400GrapBuilder::OpenGo400AudioDevice( CDeviceGrapBuilder *p_sys,
											string devicename, 
											string devicename_display,
											bool b_audio)
{
	HRESULT hr = E_FAIL;
	int i;
	if(m_pDeviceFilter == NULL || m_pEncoderFilter == NULL)
		return hr;
	SampleCaptureFilter* p_capture_filter = NULL;
	do {

		CComPtr<IPin> ptmpPin;
		if(FAILED(hr = (GetPin_ByName(m_pDeviceFilter, "Audio Out", &ptmpPin))))
		{
			if(FAILED(hr = (GetPin_ByName(m_pDeviceFilter, "音频输出", &ptmpPin))))
				break;
		}
		CComPtr<IPin> ptmpPin1;
		if(FAILED(hr = (GetPin_ByName(m_pEncoderFilter, "Audio In", &ptmpPin1))))
		{
			if(FAILED(hr = (GetPin_ByName(m_pEncoderFilter, "音频输入", &ptmpPin1))))
				break;
		}
		if (FAILED(hr = m_pGraphBuilder->Connect(ptmpPin, ptmpPin1)))
			break;
		//return AddCapturePinStream(m_pDeviceFilter, "Audio Capture");
		return S_OK;

		CComPtr<IPin> ptmpPin_Out;
		if(m_pEncoderFilter)
		{
			if(FAILED(hr = (GetPin_ByName(m_pEncoderFilter, "Audio ES Out", &ptmpPin_Out))))
				break;
		}
		else
		{
			if(FAILED(hr = (GetPin_ByName(m_pDeviceFilter, "Audio Capture", &ptmpPin_Out))))
				break;
		}		
		AM_MEDIA_TYPE media_types[MAX_MEDIA_TYPES];
		size_t media_count =
			EnumDeviceCaps( this,  ptmpPin_Out, 
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
		
		if(FAILED(hr = AddFilter_Simple(NULL, (IBaseFilter**)&p_capture_filter)))
			break;
		
		CComPtr<IPin> ptmpPin2;
		if(FAILED(hr = (GetPin_ByName(m_pEncoderFilter, "Audio ES Out", &ptmpPin2))))
			break;
		CComPtr<IPin> ptmpPin3;
		if (FAILED(hr = GetPin_FirstDisconnected(p_capture_filter, PINDIR_INPUT, &ptmpPin3))) 
			break;
		if (FAILED(hr = m_pGraphBuilder->Connect(ptmpPin2, ptmpPin3)))
			break;
		
		return hr;
	} while(false);

	RemoveFilter_Simple((IBaseFilter**)&p_capture_filter);
				
	SAFE_RELEASE(p_capture_filter);
	
	return hr;
}
int CGo400GrapBuilder::OpenGo400VideoDevice( CDeviceGrapBuilder *p_sys,
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
	HRESULT hr = S_OK;
    IBaseFilter *p_encoder_filter = NULL;

	SampleCaptureFilter *p_capture_filter = NULL;
	do {
		CComPtr<IPin> pAnalogVideoPin;
		
		if(FAILED(hr = AddFilter_Simple(NULL, (IBaseFilter**)&p_device_filter)))
			break;

		if(FAILED(hr = ConnectFilter_RenderStream(p_device_filter, NULL, NULL, false, true)))
			break;

		if(FAILED(hr = RemoveFilter_DownStream(&p_device_filter)))
			break;
		
		if(FAILED(GetPin_ByName(p_device_filter, VIDEOOUTPINNAME, &pAnalogVideoPin)))
			break;
		
		if(FAILED(CreateFilter_BySpecialCategoryAndName_SupportConnectPin(KSCATEGORY_ENCODER, 
			GO400ENCODER_NAME, 
			true, 
			pAnalogVideoPin, 
			false, 
			&p_encoder_filter)))
			break;
		
		m_pDeviceFilter  = p_device_filter;
		m_pEncoderFilter = p_encoder_filter;
		
		if(FAILED(hr = ApplyConfig()))
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

		CComPtr<IPin> ptmpPin_Out;
		if(p_encoder_filter)
		{
			if(FAILED(hr = (GetPin_ByName(p_encoder_filter, "PS Out", &ptmpPin_Out))))
				break;
		}
		else
		{
			if(FAILED(hr = (GetPin_ByName(p_device_filter, "Video Capture", &ptmpPin_Out))))
				break;
		}
		if(ptmpPin_Out == NULL)
		{
			hr = E_FAIL;
			break;
		}
		
		AM_MEDIA_TYPE media_types[MAX_MEDIA_TYPES];
		size_t media_count =
			EnumDeviceCaps( this,  ptmpPin_Out, 
			MAKEFOURCC( 'm', 'p', '2', 'p' ),
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
		
		if(FAILED(hr = AddFilter_Simple(NULL, (IBaseFilter**)&p_capture_filter)))
			break;
		
		if(p_encoder_filter)
		{
			CComPtr<IPin> ptmpPin;
			if(FAILED(hr = (GetPin_ByName(m_pDeviceFilter, "Video Out", &ptmpPin))))
			{
				if(FAILED(hr = (GetPin_ByName(m_pDeviceFilter, "视频输出", &ptmpPin))))
					break;
			}
			CComPtr<IPin> ptmpPin1;
			if(FAILED(hr = (GetPin_ByName(p_encoder_filter, "Video In", &ptmpPin1))))
			{
				if(FAILED(hr = (GetPin_ByName(p_encoder_filter, "视频输入", &ptmpPin1))))
					break;
			}
			if (FAILED(hr = m_pGraphBuilder->Connect(ptmpPin, ptmpPin1)))
				break;



			CComPtr<IPin> ptmpPin2;
			if(FAILED(hr = (GetPin_ByName(p_encoder_filter, "PS Out", &ptmpPin2))))
				break;
			CComPtr<IPin> ptmpPin3;
			if (FAILED(hr = GetPin_FirstDisconnected(p_capture_filter, PINDIR_INPUT, &ptmpPin3))) 
				break;
			if (FAILED(hr = m_pGraphBuilder->Connect(ptmpPin2, ptmpPin3)))
				break;
			
		}
		else
		{
			
			CComPtr<IPin> ptmpPin;
			if(FAILED(hr = (GetPin_ByName(m_pDeviceFilter, "Video Capture", &ptmpPin))))
			{
				if(FAILED(hr = (GetPin_ByName(m_pDeviceFilter, "视频捕获", &ptmpPin))))
					break;
			}
			
			CComPtr<IPin> ptmpPin1;			
			if (FAILED(hr = GetPin_FirstDisconnected(p_capture_filter, PINDIR_INPUT, &ptmpPin1))) 
				break;

			if (FAILED(hr = m_pGraphBuilder->Connect(ptmpPin, ptmpPin1)))
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
			//return AddCapturePinStream(p_device_filter, "Video Capture");
			return S_OK;
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
HRESULT		CGo400GrapBuilder::ApplyConfig()
{
	HRESULT hr = E_FAIL;
	do{
		SAFE_RELEASE(m_pAnalogVideoDecoder);
		if(m_pDeviceFilter == NULL || m_pEncoderFilter == NULL)
			break;
		
			if(SUCCEEDED(m_pDeviceFilter->QueryInterface((IID_IAMAnalogVideoDecoder), (void**)&m_pAnalogVideoDecoder)))
			{	
				if(i_VideoStandard)
				{
					if(FAILED(hr = m_pAnalogVideoDecoder->put_TVFormat(i_VideoStandard)))
					{
						
					}
					
				}
			}

			{
				CComPtr<IPin> ptmpPin;
				if(FAILED(hr = (GetPin_ByName(m_pDeviceFilter, "Video Capture", &ptmpPin))))
				{
					if(FAILED(hr = (GetPin_ByName(m_pDeviceFilter, "视频捕获", &ptmpPin))))
						break;
				}
				if(FAILED(hr = ptmpPin->QueryInterface(IID_IAMStreamConfig, (void**)&m_pVideoCaptureStreamConfig)))
					break;
				
			}

			if(FAILED(hr = ApplyVideoConfig_Software_Pin(m_pVideoPreviewStreamConfig, i_width, i_height)))
				break;
			if(FAILED(hr = ApplyVideoConfig_Software_Pin(m_pVideoCaptureStreamConfig, i_width, i_height)))
				break;
			
			if(FAILED(hr = m_pEncoderFilter->QueryInterface(__uuidof( m_piKsPropertySet ),
				reinterpret_cast< void** >( &m_piKsPropertySet ) )))
				break;
			m_piConfig = new CXCodeProxyPluginIFace(m_piKsPropertySet);
			
			CComPtr<IPin> ptmpPin_Out;			
			if(FAILED(hr = (GetPin_ByName(m_pEncoderFilter, "PS Out", &ptmpPin_Out))))
				break;
			
			if(FAILED(hr = ptmpPin_Out->QueryInterface(__uuidof( m_piKsPropertyVideoOutPinSet ),
				reinterpret_cast< void** >( &m_piKsPropertyVideoOutPinSet ) )))
				break;
			m_piVideoOutPinConfig = new CXCodeProxyPluginIFace(m_piKsPropertyVideoOutPinSet);
			
			if(FAILED(hr = m_piConfig->SetOutputWidth(i_width)))
				break;
		
			if(FAILED(hr = m_piConfig->SetOutputWidth(i_height)))
				break;

			if(FAILED(hr = m_piConfig->SetBitrate(i_vb * 1000)))
				break;

			if(FAILED(hr = m_piConfig->SetPeakBitrate(i_vb * 1000)))
				break;

			UINT FrameRate = VIXS_FRAME_RATE_25000;
			if(f_fps == 30.0)
				FrameRate = VIXS_FRAME_RATE_30000;
				
			if(f_fps == 25.0)
				FrameRate = VIXS_FRAME_RATE_25000;
				
			if(f_fps == 15.0)
				FrameRate = VIXS_FRAME_RATE_15000;
				
			if(f_fps == 10.0)
				FrameRate = VIXS_FRAME_RATE_10000;
				
			if(f_fps == 5.0)
				FrameRate = VIXS_FRAME_RATE_5000;
				
		
			if(FAILED(hr = m_piConfig->SetRate(FrameRate)))
				break;
			
			if(FAILED(hr = m_piConfig->SetFormat(VIXS_CODEC_MUX_ISO)))
				break;
			
			UINT VideoType = _____MPEG4_CBR;
			switch(i_vcodec) {
			case MAKEFOURCC( 'm', 'p', '1', 'v' ):
			case MAKEFOURCC( 'M', 'P', '1', 'V' ):
				VideoType = _____MPEG1;
				break;
			case MAKEFOURCC( 'm', 'p', '2', 'v' ):
			case MAKEFOURCC( 'M', 'P', '2', 'V' ):
				VideoType = _____MPEG2_CBR;
				break;
			case MAKEFOURCC( 'm', 'p', '4', 'v' ):
			case MAKEFOURCC( 'M', 'P', '4', 'V' ):
				VideoType = _____MPEG4_CBR;
				break;
			default:
				break;
			}

			if(FAILED(hr = m_piConfig->SetVideoType(VideoType)))
				break;

			UINT AudioSRate = VIXS_AUDIO_SAMPLE_RATE_48000Hz;
			switch(i_samplespersec) {
			case 48000:
				AudioSRate = VIXS_AUDIO_SAMPLE_RATE_48000Hz;
				break;
			case 44100:
				AudioSRate = VIXS_AUDIO_SAMPLE_RATE_44100Hz;
				break;
			case 32000:
				AudioSRate = VIXS_AUDIO_SAMPLE_RATE_32000Hz;
				break;
			case 24000:
				AudioSRate = VIXS_AUDIO_SAMPLE_RATE_24000Hz;
				break;
			case 8000:
				AudioSRate = VIXS_AUDIO_SAMPLE_RATE_8000Hz;
				break;
			default:
				break;
			}
			if(FAILED(hr = m_piConfig->SetAudioSRate(AudioSRate)))
				break;
			
			UINT AudioType = _____MPEG4_AAC;
			switch(i_acodec) {
			case MAKEFOURCC( 'm','p','g','a' ):
				AudioType = _____MP2;
				break;
			case MAKEFOURCC( 'm','p','3',' ' ):
				AudioType = _____MP3;
				break;
			case MAKEFOURCC( 'a', 'r', 'a', 'w' ):
				AudioType = _____PCM;
				break;
			case MAKEFOURCC( 'a', '5', '2', ' ' ):
				AudioType = _____AC3;
				break;
			case MAKEFOURCC( 's', 'a', 'm', 'r' ):
				AudioType = _____AMR;
				break;
			case MAKEFOURCC( 'm', 'p', '4', 'a' ):
			default:
				break;
			}
			if(FAILED(hr = m_piConfig->SetAudioType(AudioType)))
				break;
			
			if(FAILED(hr = m_piConfig->SetAudioMiniI2SMstrMode(VIXS_CODEC_AUDIO_I2S_MSTR_MODE_DEFAULT)))
				break;

			if(FAILED(hr = m_piConfig->SetAspectRatio(ASPECT_RATIO_DEFAULT)))
				break;
			
			if(FAILED(hr = m_piConfig->SetProfile(VIXS_MPEG4_PROFILE_ADVANCED_SIMPLE)))
				break;
			
			if(FAILED(hr = m_piConfig->SetLevel(VIXS_MPEG4_LEVEL_3)))
				break;
			
			if(FAILED(hr = m_piConfig->SetGOPnB(0)))
				break;
			
			if(FAILED(hr = m_piConfig->SetGOPnP(0)))
				break;
			
			if(FAILED(hr = m_piConfig->SetQuantType(0)))
				break;
			
			if(FAILED(hr = m_piConfig->SetBitrateMode(0)))
				break;
			
			if(FAILED(hr = m_piConfig->SetAudioBRate(i_ab * 1000)))
				break;

			if(FAILED(hr = m_piConfig->SetTimeStampMode(0)))
				break;

			int VideoOutPID = GetPIDFromCoder(i_vcodec);
			int AudioOutPID = GetPIDFromCoder(i_acodec);

			if(FAILED(hr = m_piConfig->SetAudioOutPID(AudioOutPID)))
				break;

			if(FAILED(hr = m_piConfig->SetVideoOutPID(VideoOutPID)))
				break;
			
			return hr;
	}while (false);
	return hr;
}

HRESULT	CGo400GrapBuilder::ReleaseInterface()
{
	HRESULT hr = CDeviceGrapBuilder1::ReleaseInterface();
	if(m_piConfig)
    {
        delete m_piConfig;
        m_piConfig=NULL;
    }
	if(m_piVideoOutPinConfig)
    {
        delete m_piVideoOutPinConfig;
        m_piVideoOutPinConfig=NULL;
    }
	
    // Free IKsPropertySet interface to the filter
    if(m_piKsPropertySet)
    {
        m_piKsPropertySet->Release();
        m_piKsPropertySet=NULL;
    }
	
	if(m_piKsPropertyVideoOutPinSet)
	{
		m_piKsPropertyVideoOutPinSet->Release();
		m_piKsPropertyVideoOutPinSet = NULL;
	}
	return hr;
}
HRESULT CGo400GrapBuilder::Stop()
{
	HRESULT hr;
	if(m_piVideoOutPinConfig)
    {
		BOOL flag = FALSE;
		int maxcount = 5;
		do 
		{
			hr = m_piVideoOutPinConfig->GetFinishFlagFromDriver(&flag);
		}while(!flag && SUCCEEDED(hr) && maxcount -- > 0);
    
		hr = m_piVideoOutPinConfig->GetMP4MdatInfo(&m_datainfo);
	}
	
	return CDeviceGrapBuilder1::Stop();
}
int GetPIDFromCoder(int i_codec)
{
	int i_stream_id = 0;
	switch( i_codec )
    {
	case MAKEFOURCC( 'm', 'p', '1', 'v' ):
		i_stream_id =
			 0xe0;
		break;
	case MAKEFOURCC( 'm', 'p', '2', 'v' ):
	case MAKEFOURCC( 'm', 'p', 'g', 'v' ):
		i_stream_id =
			 0xe0;
		break;
	case MAKEFOURCC( 'm', 'p', '4', 'v' ):
		i_stream_id =
		 0xe0;
		break;
	case MAKEFOURCC( 'h', '2', '6', '4' ):
		i_stream_id =
			 0xe0;
		break;
	case MAKEFOURCC( 'l', 'p', 'c', 'm' ):
		i_stream_id =
			0xbd00 | 0xa0;
		break;
	case MAKEFOURCC( 'd', 't', 's', ' ' ):
		i_stream_id =
			0xbd00 | 0x88;
		break;
	case MAKEFOURCC( 'a', '5', '2', ' ' ):
		i_stream_id =
			0xbd00 | 0x80;
		break;
	case MAKEFOURCC( 'm', 'p', 'g', 'a' ):
		i_stream_id =
			 0xc0;
		break;
	case MAKEFOURCC( 'm', 'p', '4', 'a' ):
		i_stream_id =
			0xc0;
		break;
	case MAKEFOURCC( 's', 'p', 'u', ' ' ):
		i_stream_id =
			0xbd00 |  0x20;
		break;
	default:
		i_stream_id = 0;
		break;
    }
	return i_stream_id;
}