// DeviceGrapBuilder1.cpp: implementation of the CDeviceGrapBuilder1 class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DeviceGrapBuilder1.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDeviceGrapBuilder1::CDeviceGrapBuilder1()
{
	m_pDeviceFilter  = NULL;
	m_pEncoderFilter = NULL;
	
}

CDeviceGrapBuilder1::~CDeviceGrapBuilder1()
{

}
HRESULT		CDeviceGrapBuilder1::AddCapturePinStream(IBaseFilter* p_device_filter,
													 const char *szPinName)
{
	HRESULT hr = E_FAIL;
    bool b_audio = false;
	CDeviceGrapBuilder *p_sys = this;
	int i = 0;

 	
	SampleCaptureFilter *p_capture_filter = NULL;
	do {
		CComPtr<IPin> ptmpPin;
		if(FAILED((GetPin_ByName(p_device_filter, szPinName, &ptmpPin))))
		{
			if(FAILED((GetPin_ByName(p_device_filter, "²¶»ñ", &ptmpPin))))
				break;
		}		
		
		AM_MEDIA_TYPE media_types[MAX_MEDIA_TYPES];
		size_t media_count =
			EnumDeviceCaps( this, ptmpPin, b_audio ? p_sys->i_achroma: p_sys->i_chroma,
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

		{
			CComPtr<IPin> ptmpPin1;
			CComPtr<IPin> ptmpPin2;
			if(FAILED((GetPin_ByName(p_device_filter, szPinName, &ptmpPin1))))
			{
				if(FAILED((GetPin_ByName(p_device_filter, "²¶»ñ", &ptmpPin1))))
					break;
			}		
			if(FAILED( GetPin_FirstDisconnected(p_capture_filter, PINDIR_INPUT, &ptmpPin2)))
				break;
			if(FAILED( ConnectPin_Simple(ptmpPin1, ptmpPin2)))
				break;
		}

		CDShowStream dshow_stream;
		dshow_stream.b_audio		= false;
		dshow_stream.i_SampleCount = 0;
        dshow_stream.b_pts = false;
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
            dshow_stream.p_encoder_filter = NULL;
			
            pp_streams = (CDShowStream **)realloc( pp_streams,
                sizeof(CDShowStream *) * (i_streams + 1) );
            pp_streams[i_streams] = new CDShowStream;
            *pp_streams[i_streams++] = dshow_stream;
			
			
			return 0;
        }
	} while(false);
	if(p_capture_filter)
	{
		RemoveFilter_Simple((IBaseFilter**)&p_capture_filter);				
		SAFE_RELEASE(p_capture_filter);
	}
	
	return hr;
}
HRESULT CDeviceGrapBuilder1::ApplyVideoConfig_Software_Pin(IAMStreamConfig* stream_config, 
														 int width,
														 int height)
{
	HRESULT hr =S_OK;
	if(stream_config == NULL)
		return hr;
	int caps_count = 0, caps_size = 0;
	
	bool bFlag = true;
	BOOL bSetConfig = FALSE;
	AM_MEDIA_TYPE* pmt = NULL;
	VIDEO_STREAM_CONFIG_CAPS caps;
	hr = 	stream_config->GetNumberOfCapabilities(&caps_count, &caps_size);
	if(FAILED(hr) || caps_count == 0)
		return hr;
	for(int i = 0; i < caps_count; i ++)
	{
		hr = stream_config->GetStreamCaps(i, &pmt, (BYTE*)&caps);
		if(FAILED(hr))
			continue;
		
		VIDEOINFOHEADER* format = (VIDEOINFOHEADER*)pmt->pbFormat;
		if ( pmt->formattype != FORMAT_VideoInfo )
			goto next_stream_caps;
		
		bFlag = true;
		if(format->AvgTimePerFrame !=(ULONGLONG)((double)10000000/f_fps))
			bFlag = false;
		if(width && format->bmiHeader.biWidth != width )
			bFlag = false;
		if(height && format->bmiHeader.biHeight != height)
			bFlag = false;
		
		if(bFlag)
		{
			hr = stream_config->SetFormat(pmt);
			DeleteMediaType(pmt);
			if(FAILED(hr))
				goto next_stream_caps;
			bSetConfig = TRUE;
			break;
		}
		else
		{
			
			VIDEOINFOHEADER* format = (VIDEOINFOHEADER*)pmt->pbFormat;
			format->AvgTimePerFrame=(ULONGLONG)((double)10000000/f_fps);
			if(width)
				format->bmiHeader.biWidth  = width;
			if(height)
				format->bmiHeader.biHeight = height;
			
			format->bmiHeader.biSizeImage = helper_GetBMISizeImage(format->bmiHeader);
			/*format->rcSource.right = format->bmiHeader.biWidth;
			format->rcSource.bottom = format->bmiHeader.biHeight;
			format->rcTarget.right = format->bmiHeader.biWidth;
			format->rcTarget.bottom= format->bmiHeader.biHeight;
			format->dwBitRate	   = format->bmiHeader.biSizeImage * f_fps;*/
			
			hr = stream_config->SetFormat(pmt);
			if(SUCCEEDED(hr))
			{
				DeleteMediaType(pmt);
				bSetConfig = TRUE;
				break;
			}
			
		}
next_stream_caps:
		DeleteMediaType(pmt);
	}
	
	return hr;
}