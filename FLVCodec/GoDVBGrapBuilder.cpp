// GoDVBGrapBuilder.cpp: implementation of the CGoDVBGrapBuilder class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "GoDVBGrapBuilder.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGoDVBGrapBuilder::CGoDVBGrapBuilder()
{

}

CGoDVBGrapBuilder::~CGoDVBGrapBuilder()
{

}
int CGoDVBGrapBuilder::OpenDevice( CDeviceGrapBuilder *p_sys,
			   string devicename, 
			   string devicename_display,
		bool b_audio)
{
	if(b_audio)
		return S_OK;
	
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
		FindEncoderDevice(NULL, NULL, &list_devices, &list_displayname);
		
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
			FindEncoderDevice(&devicename, &devicename_display, 
			0, 0 );
		if( p_device_filter )
			ATLTRACE(  "using device: %s", devicename.c_str() );
		else
		{
			ATLTRACE(  "can't use device: %s, unsupported device type",
				devicename.c_str() );
			return -1;
		}
		HRESULT hr = S_OK;
		
		SampleCaptureFilter *p_capture_filter = NULL;
		do {
			CComPtr<IPin> pAnalogVideoPin;
			
			if(FAILED(hr = AddFilter_Simple(NULL, (IBaseFilter**)&p_device_filter)))
				break;
			
			AM_MEDIA_TYPE media_types[MAX_MEDIA_TYPES];
			size_t media_count =
				EnumDeviceCaps( this,  p_device_filter, 
				MAKEFOURCC( 'm', 'p', '2', 't' ),
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
			m_pDeviceFilter = p_device_filter;
			CComPtr<IPin> ptmpPin;
			if(FAILED(hr = (GetPin_ByName(m_pDeviceFilter, "Capture", &ptmpPin))))
			{
				if(FAILED(hr = (GetPin_ByName(m_pDeviceFilter, "²¶»ñ", &ptmpPin))))
					break;
			}
			
			CComPtr<IPin> ptmpPin1;			
			if (FAILED(hr = GetPin_FirstDisconnected(p_capture_filter, PINDIR_INPUT, &ptmpPin1))) 
				break;
			
			if (FAILED(hr = m_pGraphBuilder->Connect(ptmpPin, ptmpPin1)))
				break;
			
			
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
				dshow_stream.p_encoder_filter = NULL;
				
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
			}
		return S_OK;
	} while(false);
	return E_FAIL;
}