// DeviceGrapBuilder.cpp: implementation of the CDeviceGrapBuilder class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DeviceGrapBuilder.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
string helper_getstring(TCHAR *szParam, char *valName)
{
	char			outParam[670];
	char*			p;
	int				i;
	
	p = strstr(szParam, valName);
	if(p)
	{
		p += strlen(valName);
		i = 0;
		
		while(*p != ';' &&
			*p != '\0')
		{
			outParam[i++] = *p;
			p ++;
		}
		outParam[i] = '\0';
	}
	else
		return "";

	return string(outParam);
}
int helper_getint(TCHAR *szParam, char *valName)
{
	int val = 0;
	
	char*			p;
	int				i;
	char			outParam[64] = "\0";
	
	p = strstr(szParam, valName);
	if(p)
	{
		p += strlen(valName);
		i = 0;
		
		while(*p != ';' &&
			*p != '\0')
		{
			outParam[i++] = *p;
			p ++;
		}
		outParam[i] = '\0';
	}
	else
		return 0;

	val = atoi(outParam);
	return val;
}
double helper_getdouble(TCHAR *szParam, char *valName)
{
	double val = 0.0;
	
	char*			p;
	int				i;
	char			outParam[64] = "\0";
	
	p = strstr(szParam, valName);
	if(p)
	{
		p += strlen(valName);
		i = 0;
		
		while(*p != ';' &&
			*p != '\0')
		{
			outParam[i++] = *p;
			p ++;
		}
		outParam[i] = '\0';
	}
	else
		return 0;
	
	val = atof(outParam);
	return val;
}
CDeviceGrapBuilder::CDeviceGrapBuilder()
{
	i_width = i_height = i_chroma = 0; f_fps = 0.0;
	i_channels = i_samplespersec = i_bitspersample = 0;
	i_achroma  = 0;
	m_pCrossBar					= NULL;
	m_pAnalogVideoDecoder		= NULL;
	b_dshowconfig		  = false;
	b_dshowtuner		  = false;
	i_PhysConnType		  = 0;
	i_VideoStandard		  = 0;
	i_vcodec			  = 0;
	i_acodec			  = 0;
	i_vb				  = 1024;
	i_ab				  = 128;
	m_pAudioPreviewStreamConfig	 = NULL;
	m_pAudioCaptureStreamConfig	 = NULL;
	m_pVideoPreviewStreamConfig	 = NULL;
	m_pVideoCaptureStreamConfig	 = NULL;
	m_pVideoCompressStreamConfig = NULL;
	m_pAudioCompressStreamConfig = NULL;
}

CDeviceGrapBuilder::~CDeviceGrapBuilder()
{

}
HRESULT CDeviceGrapBuilder::Cleanup()
{
	SAFE_DELETE(m_pCrossBar);	
	SAFE_RELEASE(m_pAnalogVideoDecoder);
	
	return CBaseGrapBuilder::Cleanup();
}

HRESULT CDeviceGrapBuilder::RenderGrapBuilder(TCHAR *szParam)
{
	HRESULT hr = S_OK;
	
	vdevname			= helper_getstring(szParam, "dshow-vdev=");
	adevname			= helper_getstring(szParam, "dshow-adev=");
	vdevname_display	= helper_getstring(szParam, "dshow-vdev-display=");
	adevname_display	= helper_getstring(szParam, "dshow-adev-display=");

	i_width				= helper_getint(szParam, "Width=");
	i_height			= helper_getint(szParam, "Height=");
	i_chroma			= helper_getint(szParam, "dshow-chroma=");
	f_fps				= helper_getdouble(szParam, "dshow-fps=");
	i_channels			= helper_getint(szParam, "dshow-audio-channel=");
	i_samplespersec		= helper_getint(szParam, "dshow-audio-samplespersec=");
	i_bitspersample		= helper_getint(szParam, "dshow-audio-bitspersample=");
	i_achroma			= helper_getint(szParam, "dshow-achroma=");
	b_dshowconfig		= helper_getint(szParam, "dshow-config=");
	b_dshowtuner		= helper_getint(szParam, "dshow-tuner=");
	i_PhysConnType		= helper_getint(szParam, "dshow-PhysConnType=");
	i_VideoStandard		= helper_getint(szParam, "dshow-AnalogVideoStandard=");
	
	i_vcodec			= helper_getint(szParam, "dshow-vcodec=");
	i_acodec			= helper_getint(szParam, "dshow-acodec=");
	i_vb				= helper_getint(szParam, "dshow-vb=");
	i_ab				= helper_getint(szParam, "dshow-ab=");
	
	/*if(i_vcodec && IsSupportHardCodec(i_vcodec))
		i_chroma = i_vcodec;
	if(i_acodec && IsSupportHardCodec(i_acodec))
		i_achroma = i_acodec;*/
	if(OpenDevice(this, vdevname, vdevname_display, false) != 0)
		printf("\nOpen video Device error\n");
	
	if(OpenDevice(this, adevname, adevname_display, true) != 0)
		printf("\nOpen audio Device error\n");

	return DoMiscWork();
}
int CDeviceGrapBuilder::OpenDevice( CDeviceGrapBuilder *p_sys,
				string devicename, string devicename_display,
					   bool b_audio )
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
        printf( "found device: %s", iter->c_str() );
	
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
        printf(  "using device: %s", devicename.c_str() );
    else
    {
        printf(  "can't use device: %s, unsupported device type",
                 devicename.c_str() );
        return -1;
    }

    // Retreive acceptable media types supported by device
    AM_MEDIA_TYPE media_types[MAX_MEDIA_TYPES];
    size_t media_count =
        EnumDeviceCaps( this, p_device_filter, b_audio ? p_sys->i_achroma: p_sys->i_chroma,
                        p_sys->i_width, p_sys->i_height,p_sys->f_fps,
						p_sys->i_channels,
						p_sys->i_samplespersec, 
						p_sys->i_bitspersample,
						media_types, MAX_MEDIA_TYPES );

    /* Find out if the pin handles MEDIATYPE_Stream, in which case we
     * won't add a prefered media type as this doesn't seem to work well
     * -- to investigate. */
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

	//if(media_count <= 0)
	{
		if( !b_stream_type && !b_audio )
		{
			// Insert prefered video media type
			AM_MEDIA_TYPE mtr;
			VIDEOINFOHEADER vh;
			
			mtr.majortype            = MEDIATYPE_Video;
			mtr.subtype              = MEDIASUBTYPE_I420;
			mtr.bFixedSizeSamples    = TRUE;
			mtr.bTemporalCompression = FALSE;
			mtr.pUnk                 = NULL;
			mtr.formattype           = FORMAT_VideoInfo;
			mtr.cbFormat             = sizeof(vh);
			mtr.pbFormat             = (BYTE *)&vh;
			
			memset(&vh, 0, sizeof(vh));
			
			vh.bmiHeader.biSize   = sizeof(vh.bmiHeader);
			vh.bmiHeader.biWidth  = p_sys->i_width > 0 ? p_sys->i_width : 320;
			vh.bmiHeader.biHeight = p_sys->i_height > 0 ? p_sys->i_height : 240;
			vh.bmiHeader.biPlanes      = 3;
			vh.bmiHeader.biBitCount    = 12;
			vh.bmiHeader.biCompression = MAKEFOURCC('I','4','2','0');
			vh.bmiHeader.biSizeImage   = vh.bmiHeader.biWidth * 12 *
				vh.bmiHeader.biHeight / 8;
			mtr.lSampleSize            = vh.bmiHeader.biSizeImage;
			
			media_count = 1;
			mt = (AM_MEDIA_TYPE *)realloc( mt, sizeof(AM_MEDIA_TYPE) *
				(mt_count + media_count) );
			CopyMediaType(&mt[mt_count], &mtr);
			mt_count += media_count;
			
			
		}
		else if( !b_stream_type )
		{
			// Insert prefered audio media type
			AM_MEDIA_TYPE mtr;
			WAVEFORMATEX wf;
			
			mtr.majortype            = MEDIATYPE_Audio;
			mtr.subtype              = MEDIASUBTYPE_PCM;
			mtr.bFixedSizeSamples    = TRUE;
			mtr.bTemporalCompression = FALSE;
			mtr.lSampleSize          = 0;
			mtr.pUnk                 = NULL;
			mtr.formattype           = FORMAT_WaveFormatEx;
			mtr.cbFormat             = sizeof(wf);
			mtr.pbFormat             = (BYTE *)&wf;
			
			memset(&wf, 0, sizeof(wf));
			
			wf.wFormatTag = WAVE_FORMAT_PCM;
			wf.nChannels = 2;
			wf.nSamplesPerSec = 44100;
			wf.wBitsPerSample = 16;
			wf.nBlockAlign = wf.nSamplesPerSec * wf.wBitsPerSample / 8;
			wf.nAvgBytesPerSec = wf.nSamplesPerSec * wf.nBlockAlign;
			wf.cbSize = 0;
			
			
			media_count = 1;
			mt = (AM_MEDIA_TYPE *)realloc( mt, sizeof(AM_MEDIA_TYPE) *
				(mt_count + media_count) );
			CopyMediaType(&mt[mt_count], &mtr);
			mt_count += media_count;
		}
	}
	
	SampleCaptureFilter *p_capture_filter = NULL;
	do {
		p_capture_filter =
			new SampleCaptureFilter( this, mt, mt_count );
		if(FAILED(AddFilter_Simple(NULL, (IBaseFilter**)&p_capture_filter)))
			break;

		if(FAILED(AddFilter_Simple(NULL, (IBaseFilter**)&p_device_filter)))
			break;
		
		IBaseFilter* p_encoder_filter = NULL;
		if(FAILED(InsertEncoderFilter(p_device_filter,
			p_capture_filter, 
			b_audio,
			(IBaseFilter**)&p_encoder_filter)))
			break;

		CDShowStream dshow_stream;
		dshow_stream.b_audio		= b_audio;
		dshow_stream.i_SampleCount	= 0;
        dshow_stream.b_pts			= false;
        dshow_stream.p_es			= 0;
        dshow_stream.mt =
            p_capture_filter->CustomGetPin()->CustomGetMediaType();
		
		dshow_stream.i_fourcc = GetFourCCFromMediaType( dshow_stream.mt );
        if( dshow_stream.i_fourcc )
        {
            if( dshow_stream.mt.majortype == MEDIATYPE_Video )
            {
                dshow_stream.header.video =
                    *(VIDEOINFOHEADER *)dshow_stream.mt.pbFormat;
                printf(  "MEDIATYPE_Video" );
                printf(  "selected video pin accepts format: %4.4s",
					(char *)&dshow_stream.i_fourcc);
            }
            else if( dshow_stream.mt.majortype == MEDIATYPE_Audio )
            {
                dshow_stream.header.audio =
                    *(WAVEFORMATEX *)dshow_stream.mt.pbFormat;
                printf(  "MEDIATYPE_Audio" );
                printf(  "selected audio pin accepts format: %4.4s",
					(char *)&dshow_stream.i_fourcc);
            }
            else if( dshow_stream.mt.majortype == MEDIATYPE_Stream )
            {
                printf(  "MEDIATYPE_Stream" );
                printf(  "selected stream pin accepts format: %4.4s",
					(char *)&dshow_stream.i_fourcc);
            }
            else
            {
                printf(  "unknown stream majortype" );
                break;
            }
			if(b_dshowconfig)
			{
				ShowDeviceProperties(m_pCaptureBuilder,
					p_device_filter, 
					NULL, 
					b_audio);
			}
			if(b_dshowtuner)
			{
				ShowTunerProperties(m_pCaptureBuilder,
				p_device_filter, NULL,
				b_audio );
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
				SAFE_RELEASE(m_pAnalogVideoDecoder);
				if(SUCCEEDED(p_device_filter->QueryInterface((IID_IAMAnalogVideoDecoder), (void**)&m_pAnalogVideoDecoder)))
				{	
					if(i_VideoStandard)
					{
						if(FAILED(m_pAnalogVideoDecoder->put_TVFormat(i_VideoStandard)))
						{

						}
						
					}
				}
			}
			
			return 0;
        }
	} while(false);
	RemoveFilter_Simple((IBaseFilter**)&p_capture_filter);
	RemoveFilter_Simple((IBaseFilter**)&p_device_filter);
				
	SAFE_RELEASE(p_capture_filter);
	SAFE_RELEASE(p_device_filter);
	
	return -1;
}

HRESULT CDeviceGrapBuilder::helper_GetCrossbarRoute(IBaseFilter* pVCap, CCrossbar **ppCrossBar)
{
	if(pVCap == NULL || ppCrossBar == NULL)
		return VFW_E_NO_INTERFACE;
	HRESULT hr = S_OK;
	IPin        *pP = 0;
	IEnumPins   *pins=0;
	ULONG        n;
	PIN_INFO     pinInfo;
	BOOL         Found = FALSE;
	IKsPropertySet *pKs=0;
	GUID guid;
	DWORD dw;
	BOOL fMatch = FALSE;
	
	CCrossbar *pCrossbar = NULL;
	
	if(SUCCEEDED(pVCap->EnumPins(&pins)))
	{            
		while(!Found && (S_OK == pins->Next(1, &pP, &n)))
		{
			if(S_OK == pP->QueryPinInfo(&pinInfo))
			{
				pinInfo.pFilter->Release();
				if(pinInfo.dir == PINDIR_INPUT)
				{
					// is this pin an ANALOGVIDEOIN input pin?
					if(pP->QueryInterface(IID_IKsPropertySet,
						(void **)&pKs) == S_OK)
					{
						if(pKs->Get(AMPROPSETID_Pin,
							AMPROPERTY_PIN_CATEGORY, NULL, 0,
							&guid, sizeof(GUID), &dw) == S_OK)
						{
							if(guid == PIN_CATEGORY_ANALOGVIDEOIN)
								fMatch = TRUE;
						}
						pKs->Release();
					}
					
					if(fMatch)
					{
						HRESULT hrCreate=S_OK;
						pCrossbar = new CCrossbar(pP, &hrCreate);
						if (!pCrossbar || FAILED(hrCreate))
						{
							SAFE_DELETE(pCrossbar);
							break;
						}
						
						Found = TRUE;
					}
				}
			}
			pP->Release();
		}
		pins->Release();
	}
	*ppCrossBar = pCrossbar;
	return Found ? S_OK : E_NOINTERFACE;
}
HRESULT CDeviceGrapBuilder::DoMiscWork()
{
	HRESULT hr = S_OK;
	if(i_PhysConnType && m_pCrossBar)
	{
		LONG nCount = 0;
		m_pCrossBar->GetInputCount(&nCount);
		for( int i = nCount-1; i >= 0 ; --i )
        {
			LONG PhysicalType = 0;
			if(SUCCEEDED(m_pCrossBar->GetInputType(i, &PhysicalType)))
            {
				if(PhysicalType == i_PhysConnType)
				{
					m_pCrossBar->SetInputIndex(i);
					break;
				}
			}
        }
	}
	
	if(b_dshowconfig && m_pCrossBar)
	{
		LONG nCount = 0;
		m_pCrossBar->GetInputCount(&nCount);
		for( int i = nCount-1; i >= 0 ; --i )
        {
            IAMCrossbar *pXbar = NULL;
			if(SUCCEEDED(m_pCrossBar->GetCrossbar(i, &pXbar)))
            {
				IBaseFilter *p_XF;
				
				if(pXbar&& SUCCEEDED( pXbar->QueryInterface( IID_IBaseFilter,
					(void **)&p_XF ) ) )
				{
					ShowPropertyPage( p_XF, NULL );
					p_XF->Release();
				}
			}
        }
	}
	return hr;
}
HRESULT	CDeviceGrapBuilder::ReleaseInterface()
{
	SAFE_RELEASE(m_pAudioPreviewStreamConfig);
	SAFE_RELEASE(m_pAudioCaptureStreamConfig);
	SAFE_RELEASE(m_pVideoPreviewStreamConfig);
	SAFE_RELEASE(m_pVideoCaptureStreamConfig);
	SAFE_RELEASE(m_pVideoCompressStreamConfig);
	SAFE_RELEASE(m_pAudioCompressStreamConfig);
	SAFE_RELEASE(m_pAudioCompressStreamConfig);
	SAFE_RELEASE(m_pAnalogVideoDecoder);
	return S_OK;
}
HRESULT CDeviceGrapBuilder::InsertEncoderFilter(IBaseFilter* p_device_filter ,
												SampleCaptureFilter *p_capture_filter,bool b_audio,
												IBaseFilter** pp_encoder_filter)
{
	do {
		if(b_audio)
		{
			if(FAILED(ConnectFilter_Simple(p_device_filter, p_capture_filter)))
				break;
		}
		else
		{
			if(!ConnectFilters(this, p_device_filter, p_capture_filter))
				break;

		}		
		return S_OK;
	} while(false);
	return E_FAIL;
}	