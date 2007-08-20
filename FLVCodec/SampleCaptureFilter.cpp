// SampleSampleCaptureFilter.cpp: implementation of the SampleSampleCaptureFilter class.
//
//////////////////////////////////////////////////////////////////////
//#define XMP_CL
#ifdef XMP_CL
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define _VIDEOINFO_
#define _VIDEOINFOHEADER_
#define _TRUECOLORINFO_
#include "xmpstd.h"
#define PTCHAR TCHAR* 
#endif
#include "stdafx.h"
#include "BaseGrapBuilder.h"
#include "SampleCaptureFilter.h"

/* Microsoft RLE video */
#define FOURCC_1            MAKEFOURCC( 1,  0,  0,  0 )

/* MPEG4 video */
#define FOURCC_DIVX         MAKEFOURCC('D','I','V','X')
#define FOURCC_divx         MAKEFOURCC('d','i','v','x')
#define FOURCC_DIV1         MAKEFOURCC('D','I','V','1')
#define FOURCC_div1         MAKEFOURCC('d','i','v','1')
#define FOURCC_MP4S         MAKEFOURCC('M','P','4','S')
#define FOURCC_mp4s         MAKEFOURCC('m','p','4','s')
#define FOURCC_M4S2         MAKEFOURCC('M','4','S','2')
#define FOURCC_m4s2         MAKEFOURCC('m','4','s','2')
#define FOURCC_xvid         MAKEFOURCC('x','v','i','d')
#define FOURCC_XVID         MAKEFOURCC('X','V','I','D')
#define FOURCC_XviD         MAKEFOURCC('X','v','i','D')
#define FOURCC_DX50         MAKEFOURCC('D','X','5','0')
#define FOURCC_dx50         MAKEFOURCC('d','x','5','0')
#define FOURCC_mp4v         MAKEFOURCC('m','p','4','v')
#define FOURCC_4            MAKEFOURCC( 4,  0,  0,  0 )

/* MSMPEG4 v2 */
#define FOURCC_MPG4         MAKEFOURCC('M','P','G','4')
#define FOURCC_mpg4         MAKEFOURCC('m','p','g','4')
#define FOURCC_DIV2         MAKEFOURCC('D','I','V','2')
#define FOURCC_div2         MAKEFOURCC('d','i','v','2')
#define FOURCC_MP42         MAKEFOURCC('M','P','4','2')
#define FOURCC_mp42         MAKEFOURCC('m','p','4','2')

/* MSMPEG4 v3 / M$ mpeg4 v3 */
#define FOURCC_MPG3         MAKEFOURCC('M','P','G','3')
#define FOURCC_mpg3         MAKEFOURCC('m','p','g','3')
#define FOURCC_div3         MAKEFOURCC('d','i','v','3')
#define FOURCC_MP43         MAKEFOURCC('M','P','4','3')
#define FOURCC_mp43         MAKEFOURCC('m','p','4','3')

/* DivX 3.20 */
#define FOURCC_DIV3         MAKEFOURCC('D','I','V','3')
#define FOURCC_DIV4         MAKEFOURCC('D','I','V','4')
#define FOURCC_div4         MAKEFOURCC('d','i','v','4')
#define FOURCC_DIV5         MAKEFOURCC('D','I','V','5')
#define FOURCC_div5         MAKEFOURCC('d','i','v','5')
#define FOURCC_DIV6         MAKEFOURCC('D','I','V','6')
#define FOURCC_div6         MAKEFOURCC('d','i','v','6')

/* AngelPotion stuff */
#define FOURCC_AP41         MAKEFOURCC('A','P','4','1')

/* 3IVX */
#define FOURCC_3IV1         MAKEFOURCC('3','I','V','1')
#define FOURCC_3iv1         MAKEFOURCC('2','i','v','1')
#define FOURCC_3IV2         MAKEFOURCC('3','I','V','2')
#define FOURCC_3iv2         MAKEFOURCC('3','i','v','2')
#define FOURCC_3IVD         MAKEFOURCC('3','I','V','D')
#define FOURCC_3ivd         MAKEFOURCC('3','i','v','d')
#define FOURCC_3VID         MAKEFOURCC('3','V','I','D')
#define FOURCC_3vid         MAKEFOURCC('3','v','i','d')

/* H261*/
#define FOURCC_H261         MAKEFOURCC('H','2','6','1')
#define FOURCC_h261         MAKEFOURCC('h','2','6','1')

/* H263 and H263i */
#define FOURCC_H263         MAKEFOURCC('H','2','6','3')
#define FOURCC_h263         MAKEFOURCC('h','2','6','3')
#define FOURCC_U263         MAKEFOURCC('U','2','6','3')
#define FOURCC_I263         MAKEFOURCC('I','2','6','3')
#define FOURCC_i263         MAKEFOURCC('i','2','6','3')

/* H264 */
#define FOURCC_H264         MAKEFOURCC('H','2','6','4')
#define FOURCC_h264         MAKEFOURCC('h','2','6','4')
#define FOURCC_VSSH         MAKEFOURCC('V','S','S','H')

/* WMV */
#define FOURCC_WMV3         MAKEFOURCC('W','M','V','3')
#define FOURCC_WMV2         MAKEFOURCC('W','M','V','2')
#define FOURCC_WMV1         MAKEFOURCC('W','M','V','1')
#define FOURCC_wmv3         MAKEFOURCC('w','m','v','3')
#define FOURCC_wmv2         MAKEFOURCC('w','m','v','2')
#define FOURCC_wmv1         MAKEFOURCC('w','m','v','1')

/*MJPEG*/
#define FOURCC_MJPEG		MAKEFOURCC('M','J','P','G')
#define FOURCC_mjpeg		MAKEFOURCC('m','j','p','g')

/*Real Video*/
#define FOURCC_RV10			MAKEFOURCC('R','V','1','0')
#define FOURCC_rv10			MAKEFOURCC('r','v','1','0')
#define FOURCC_RV20			MAKEFOURCC('R','V','2','0')
#define FOURCC_rv20			MAKEFOURCC('r','v','2','0')

__int64 mymdate( void )
{

	/* We don't need the real date, just the value of a high precision timer */
	static __int64 freq = (-1);
	__int64 usec_time;

	if( freq == (-1) )
	{
		
		freq = ( QueryPerformanceFrequency( (LARGE_INTEGER *)&freq ) &&
			(freq == (1193182) || freq == (3579545) ) )
			? freq : 0;
	}

	if( freq != 0 )
	{
		/* Microsecond resolution */
		QueryPerformanceCounter( (LARGE_INTEGER *)&usec_time );
		return ( usec_time * 1000000 ) / freq;
	}
	else
	{
	/* Fallback on GetTickCount() which has a milisecond resolution
	* (actually, best case is about 10 ms resolution)
	* GetTickCount() only returns a DWORD thus will wrap after
		* about 49.7 days so we try to detect the wrapping. */
		
		static CRITICAL_SECTION date_lock;
		static __int64 i_previous_time = (-1);
		static int i_wrap_counts = -1;
		
		if( i_wrap_counts == -1 )
		{
			/* Initialization */
			i_previous_time = (1000) * GetTickCount();
			InitializeCriticalSection( &date_lock );
			i_wrap_counts = 0;
		}
		
		EnterCriticalSection( &date_lock );
		usec_time = (1000) *
			(i_wrap_counts * (0x100000000) + GetTickCount());
		if( i_previous_time > usec_time )
		{
			/* Counter wrapped */
			i_wrap_counts++;
			usec_time += (0x100000000000);
		}
		i_previous_time = usec_time;
		LeaveCriticalSection( &date_lock );
		
		return usec_time;
	}
 }
const GUID MEDIASUBTYPE_DX50 = {0x30355844,0x0000,0x0010,{0x80,0x00,0x00,0xAA,0x00,0x38,0x9B,0x71}};

int GetFourCCFromMediaType( const AM_MEDIA_TYPE &media_type )
{
 int i_fourcc = 0;
	
    if( media_type.majortype == MEDIATYPE_Video )
    {
        /* currently only support this type of video info format */
        if( 1 /* media_type.formattype == FORMAT_VideoInfo */ )
        {
            /* Packed RGB formats */
            if( media_type.subtype == MEDIASUBTYPE_RGB1 )
				i_fourcc = MAKEFOURCC( 'R', 'G', 'B', '1' );
            else if( media_type.subtype == MEDIASUBTYPE_RGB4 )
				i_fourcc = MAKEFOURCC( 'R', 'G', 'B', '4' );
            else if( media_type.subtype == MEDIASUBTYPE_RGB8 )
				i_fourcc = MAKEFOURCC( 'R', 'G', 'B', '8' );
            else if( media_type.subtype == MEDIASUBTYPE_RGB555 )
				i_fourcc = MAKEFOURCC( 'R', 'V', '1', '5' );
            else if( media_type.subtype == MEDIASUBTYPE_RGB565 )
				i_fourcc = MAKEFOURCC( 'R', 'V', '1', '6' );
            else if( media_type.subtype == MEDIASUBTYPE_RGB24 )
				i_fourcc = MAKEFOURCC( 'R', 'V', '2', '4' );
            else if( media_type.subtype == MEDIASUBTYPE_RGB32 )
				i_fourcc = MAKEFOURCC( 'R', 'V', '3', '2' );
            else if( media_type.subtype == MEDIASUBTYPE_ARGB32 )
				i_fourcc = MAKEFOURCC( 'R', 'G', 'B', 'A' );
			
            /* Planar YUV formats */
            else if( media_type.subtype == MEDIASUBTYPE_I420 )
				i_fourcc = MAKEFOURCC( 'I', '4', '2', '0' );
            else if( media_type.subtype == MEDIASUBTYPE_Y41P )
				i_fourcc = MAKEFOURCC( 'I', '4', '1', '1' );
            else if( media_type.subtype == MEDIASUBTYPE_YV12 )
				i_fourcc = MAKEFOURCC( 'Y', 'V', '1', '2' );
            else if( media_type.subtype == MEDIASUBTYPE_IYUV )
				i_fourcc = MAKEFOURCC( 'Y', 'V', '1', '2' );
            else if( media_type.subtype == MEDIASUBTYPE_YVU9 )
				i_fourcc = MAKEFOURCC( 'Y', 'V', 'U', '9' );
			
            /* Packed YUV formats */
            else if( media_type.subtype == MEDIASUBTYPE_YVYU )
				i_fourcc = MAKEFOURCC( 'Y', 'V', 'Y', 'U' );
            else if( media_type.subtype == MEDIASUBTYPE_YUYV )
				i_fourcc = MAKEFOURCC( 'Y', 'U', 'Y', '2' );
            else if( media_type.subtype == MEDIASUBTYPE_Y411 )
				i_fourcc = MAKEFOURCC( 'I', '4', '1', 'N' );
            else if( media_type.subtype == MEDIASUBTYPE_Y211 )
				i_fourcc = MAKEFOURCC( 'Y', '2', '1', '1' );
            else if( media_type.subtype == MEDIASUBTYPE_YUY2 )
				i_fourcc = MAKEFOURCC( 'Y', 'U', 'Y', '2' );
            else if( media_type.subtype == MEDIASUBTYPE_UYVY )
				i_fourcc = MAKEFOURCC( 'U', 'Y', 'V', 'Y' );
			
            /* MPEG2 video elementary stream */
            else if( media_type.subtype == MEDIASUBTYPE_MPEG2_VIDEO )
				i_fourcc = MAKEFOURCC( 'm', 'p', '2', 'v' );
			
            /* DV formats */
            else if( media_type.subtype == MEDIASUBTYPE_dvsl )
				i_fourcc = MAKEFOURCC( 'd', 'v', 's', 'l' );
            else if( media_type.subtype == MEDIASUBTYPE_dvsd )
				i_fourcc = MAKEFOURCC( 'd', 'v', 's', 'd' );
            else if( media_type.subtype == MEDIASUBTYPE_dvhd )
				i_fourcc = MAKEFOURCC( 'd', 'v', 'h', 'd' );
        }

		if(media_type.subtype == MEDIASUBTYPE_MPEG1Payload ||
			media_type.subtype	== MEDIASUBTYPE_MPEG1Packet)
		{
			i_fourcc = MAKEFOURCC( 'm', 'p', '1', 'v' );
		}
		else if(media_type.subtype == MEDIASUBTYPE_MPEG2_VIDEO)
		{
			i_fourcc = MAKEFOURCC( 'm', 'p', '2', 'v' );
		}

		switch(media_type.subtype.Data1)
		{
		case FOURCC_1:
		case FOURCC_DIV1:
		case FOURCC_div1:
		case FOURCC_MPG4:
		case FOURCC_mpg4:
		case FOURCC_DIV2:
		case FOURCC_div2:
		case FOURCC_MP42:
		case FOURCC_mp42:
		case FOURCC_MPG3:
		case FOURCC_mpg3:
		case FOURCC_div3:
		case FOURCC_MP43:
		case FOURCC_mp43:
		case FOURCC_DIV3:
		case FOURCC_DIV4:
		case FOURCC_div4:
		case FOURCC_DIV5:
		case FOURCC_div5:
		case FOURCC_DIV6:
		case FOURCC_div6:
		case FOURCC_AP41:
		case FOURCC_3IV1:
		case FOURCC_3iv1:
		case FOURCC_3IVD:
		case FOURCC_3ivd:
		case FOURCC_3VID:
		case FOURCC_3vid:
		case FOURCC_DIVX:
		case FOURCC_divx:
		case FOURCC_xvid:
		case FOURCC_XVID:
		case FOURCC_XviD:
		case FOURCC_DX50:
		case FOURCC_dx50:
		case FOURCC_mp4v:
		case FOURCC_4:
		case FOURCC_3IV2:
		case FOURCC_3iv2:
			i_fourcc = MAKEFOURCC('m','p','4','v');
			break;
		case FOURCC_MP4S:
		case FOURCC_mp4s:
		case FOURCC_M4S2:
		case FOURCC_m4s2:
			i_fourcc = MAKEFOURCC('M','P','4','S');
			break;
		case FOURCC_H261:
		case FOURCC_h261:
			i_fourcc = MAKEFOURCC('h','2','6','1');
			break;
		case FOURCC_H263:
		case FOURCC_h263:
		case FOURCC_U263:
		case FOURCC_I263:
		case FOURCC_i263:
			i_fourcc = MAKEFOURCC('H','2','6','3');
			break;
		case FOURCC_H264:
		case FOURCC_h264:
		case FOURCC_VSSH:
			i_fourcc = MAKEFOURCC('h','2','6','4');
			break;
		case FOURCC_WMV3:
		case FOURCC_wmv3:
		case FOURCC_WMV2:
		case FOURCC_wmv2:
		case FOURCC_WMV1:
		case FOURCC_wmv1:
			i_fourcc = MAKEFOURCC('w','m','v','2');
			break;
		case FOURCC_RV10:
		case FOURCC_rv10:
		case FOURCC_RV20:
		case FOURCC_rv20:
			i_fourcc = media_type.subtype.Data1;
			break;
		default:
			break;
		}
	
    }
    else if( media_type.majortype == MEDIATYPE_Audio )
    {
		if(media_type.subtype == MEDIASUBTYPE_MPEG1Payload ||
			media_type.subtype	== MEDIASUBTYPE_MPEG1Packet)
		{
			i_fourcc = MAKEFOURCC( 'm','p','3',' ' );
		}
		else if(media_type.subtype == MEDIASUBTYPE_MPEG2_AUDIO)
		{
			i_fourcc = MAKEFOURCC( 'm','p','g','a' );
		}
		else
		{
			if( media_type.formattype == FORMAT_WaveFormatEx )
			{
				if( media_type.subtype == MEDIASUBTYPE_PCM )
					i_fourcc = MAKEFOURCC( 'a', 'r', 'a', 'w' );
				else if( media_type.subtype == MEDIASUBTYPE_IEEE_FLOAT )
					i_fourcc = MAKEFOURCC( 'f', 'l', '3', '2' );
			}
		}
    }
    else if( media_type.majortype == MEDIATYPE_Stream )
    {
        if( media_type.subtype == MEDIASUBTYPE_MPEG2_PROGRAM )
            i_fourcc = MAKEFOURCC( 'm', 'p', '2', 'p' );
        else if( media_type.subtype == MEDIASUBTYPE_MPEG2_TRANSPORT )
            i_fourcc = MAKEFOURCC( 'm', 'p', '2', 't' );
		else
			i_fourcc = media_type.subtype.Data1;
    }
	if(i_fourcc == 0)
	{
		if(media_type.formattype == FORMAT_MPEGVideo)
			i_fourcc = MAKEFOURCC( 'm', 'p', '1', 'v' );
		else if(media_type.formattype == FORMAT_MPEG2Video)
			i_fourcc = MAKEFOURCC( 'm', 'p', '2', 'v' );		
	}
	if(i_fourcc == 0)
	{
		i_fourcc = media_type.subtype.Data1;
	}
    return i_fourcc;
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


/****************************************************************************
 * Implementation of our dummy directshow filter pin class
 ****************************************************************************/

SampleCapturePin::SampleCapturePin( void *_p_input,
                        SampleCaptureFilter *_p_filter,
                        AM_MEDIA_TYPE *mt, size_t mt_count )
  : p_input( _p_input ), p_filter( _p_filter ),
    p_connected_pin( NULL ),  media_types(mt), media_type_count(mt_count),
    i_ref( 1 )
{
    cx_media_type.majortype = mt ? mt[0].majortype : GUID_NULL;
    cx_media_type.subtype   = GUID_NULL;
    cx_media_type.pbFormat  = NULL;
    cx_media_type.cbFormat  = 0;
    cx_media_type.pUnk      = NULL;
	InitializeCriticalSection(&m_mylock);
}

SampleCapturePin::~SampleCapturePin()
{
#ifdef DEBUG_DSHOW
    ATLTRACE(  "SampleCapturePin::~SampleCapturePin" );
#endif
    for( size_t c=0; c<media_type_count; c++ )
    {
        FreeMediaType(media_types[c]);
    }
	free(media_types);
	media_types = NULL;
    FreeMediaType(cx_media_type);
	DeleteCriticalSection(&m_mylock);
}

HRESULT SampleCapturePin::CustomGetSample( XMPMediaSample *xmp_sample )
{
#if 0 //def DEBUG_DSHOW
    ATLTRACE(  "SampleCapturePin::CustomGetSample" );
#endif

 	EnterCriticalSection(&m_mylock);
   if( samples_queue.size() )
    {
        *xmp_sample = samples_queue.back();
        samples_queue.pop_back();
  		LeaveCriticalSection(&m_mylock);
        return S_OK;
    }
   LeaveCriticalSection(&m_mylock);
    return S_FALSE;
}

AM_MEDIA_TYPE &SampleCapturePin::CustomGetMediaType()
{
    return cx_media_type;
}

/* IUnknown methods */
STDMETHODIMP SampleCapturePin::QueryInterface(REFIID riid, void **ppv)
{
#ifdef DEBUG_DSHOW_L1
    ATLTRACE(  "SampleCapturePin::QueryInterface" );
#endif

    if( riid == IID_IUnknown ||
        riid == IID_IPin )
    {
        AddRef();
        *ppv = (IPin *)this;
        return NOERROR;
    }
    if( riid == IID_IMemInputPin )
    {
        AddRef();
        *ppv = (IMemInputPin *)this;
        return NOERROR;
    }
    else
    {
#ifdef DEBUG_DSHOW_L1
        ATLTRACE(  "SampleCapturePin::QueryInterface() failed for: "
                 "%04X-%02X-%02X-%02X%02X%02X%02X%02X%02X%02X%02X",
                 (int)riid.Data1, (int)riid.Data2, (int)riid.Data3,
                 static_cast<int>(riid.Data4[0]), (int)riid.Data4[1],
                 (int)riid.Data4[2], (int)riid.Data4[3],
                 (int)riid.Data4[4], (int)riid.Data4[5],
                 (int)riid.Data4[6], (int)riid.Data4[7] );
#endif
        *ppv = NULL;
        return E_NOINTERFACE;
    }
}

STDMETHODIMP_(ULONG) SampleCapturePin::AddRef()
{
   // ATLTRACE(  "==================SampleCapturePin::AddRef (ref: %i)\n", i_ref + 1);

    return InterlockedIncrement(&i_ref);
};
STDMETHODIMP_(ULONG) SampleCapturePin::Release()
{
  //  ATLTRACE(  "==================SampleCapturePin::Release (ref: %i)\n", i_ref - 1);

	long i_save = i_ref;
    if( !InterlockedDecrement(&i_ref) ) delete this;

    return i_save - 1;
};

/* IPin methods */
STDMETHODIMP SampleCapturePin::Connect( IPin * pReceivePin,
                                  const AM_MEDIA_TYPE *pmt )
{
    if( State_Running == p_filter->state )
    {
        ATLTRACE(  "SampleCapturePin::Connect [not stopped]" );
        return VFW_E_NOT_STOPPED;
    }

    if( p_connected_pin )
    {
        ATLTRACE(  "SampleCapturePin::Connect [already connected]" );
        return VFW_E_ALREADY_CONNECTED;
    }

    if( !pmt ) return S_OK;
                
    if( GUID_NULL != pmt->majortype &&
        media_types[0].majortype != pmt->majortype )
    {
        ATLTRACE(  "SampleCapturePin::Connect [media major type mismatch]" );
        return S_FALSE;
    }

    if( GUID_NULL != pmt->subtype && !GetFourCCFromMediaType(*pmt) )
    {
        ATLTRACE(  "SampleCapturePin::Connect [media subtype type "
                 "not supported]" );
        return S_FALSE;
    }

    if( pmt->pbFormat && pmt->majortype == MEDIATYPE_Video  )
    {
        if( !((VIDEOINFOHEADER *)pmt->pbFormat)->bmiHeader.biHeight ||
            !((VIDEOINFOHEADER *)pmt->pbFormat)->bmiHeader.biWidth )
        {
            ATLTRACE(  "SampleCapturePin::Connect "
                     "[video width/height == 0 ]" );
            return S_FALSE;
        }
    }

    ATLTRACE(  "SampleCapturePin::Connect [OK]" );
    return S_OK;
}
STDMETHODIMP SampleCapturePin::ReceiveConnection( IPin * pConnector,
                                            const AM_MEDIA_TYPE *pmt )
{
    if( State_Stopped != p_filter->state )
    {
        ATLTRACE(  "SampleCapturePin::ReceiveConnection [not stopped]" );
        return VFW_E_NOT_STOPPED;
    }

    if( !pConnector || !pmt )
    {
        ATLTRACE(  "SampleCapturePin::ReceiveConnection [null pointer]" );
        return E_POINTER;
    }

    if( p_connected_pin )
    {
        ATLTRACE(  "SampleCapturePin::ReceiveConnection [already connected]");
        return VFW_E_ALREADY_CONNECTED;
    }

    if( S_OK != QueryAccept(pmt) )
    {
        ATLTRACE(  "SampleCapturePin::ReceiveConnection "
                 "[media type not accepted]" );
        return VFW_E_TYPE_NOT_ACCEPTED;
    }

    ATLTRACE(  "SampleCapturePin::ReceiveConnection [OK]" );

    p_connected_pin = pConnector;
    p_connected_pin->AddRef();

    FreeMediaType( cx_media_type );
    return CopyMediaType( &cx_media_type, pmt );
}
STDMETHODIMP SampleCapturePin::Disconnect()
{
    if( ! p_connected_pin )
    {
        ATLTRACE(  "SampleCapturePin::Disconnect [not connected]" );
        return S_FALSE;
    }

    ATLTRACE(  "SampleCapturePin::Disconnect [OK]" );

    /* samples_queue was already flushed in EndFlush() */
	XMPMediaSample xmp_sample;
	
   	EnterCriticalSection(&m_mylock);
	while( samples_queue.size() )
    {
        xmp_sample = samples_queue.back();
        samples_queue.pop_back();
        xmp_sample.p_sample->Release();
    }
	LeaveCriticalSection(&m_mylock);
	
    p_connected_pin->Release();
    p_connected_pin = NULL;
    //FreeMediaType( cx_media_type );
    //cx_media_type.subtype = GUID_NULL;

    return S_OK;
}
STDMETHODIMP SampleCapturePin::ConnectedTo( IPin **pPin )
{
    if( !p_connected_pin )
    {
        ATLTRACE(  "SampleCapturePin::ConnectedTo [not connected]" );
        return VFW_E_NOT_CONNECTED;
    }

    p_connected_pin->AddRef();
    *pPin = p_connected_pin;

    ATLTRACE(  "SampleCapturePin::ConnectedTo [OK]" );

    return S_OK;
}
STDMETHODIMP SampleCapturePin::ConnectionMediaType( AM_MEDIA_TYPE *pmt )
{
    if( !p_connected_pin )
    {
        ATLTRACE(  "SampleCapturePin::ConnectionMediaType [not connected]" );
        return VFW_E_NOT_CONNECTED;
    }

    return CopyMediaType( pmt, &cx_media_type );
}
STDMETHODIMP SampleCapturePin::QueryPinInfo( PIN_INFO * pInfo )
{
#ifdef DEBUG_DSHOW
    ATLTRACE(  "SampleCapturePin::QueryPinInfo" );
#endif

    pInfo->pFilter = p_filter;
    if( p_filter ) p_filter->AddRef();

    memcpy(pInfo->achName, PIN_NAME, sizeof(PIN_NAME));
    pInfo->dir = PINDIR_INPUT;

    return NOERROR;
}
STDMETHODIMP SampleCapturePin::QueryDirection( PIN_DIRECTION * pPinDir )
{
#ifdef DEBUG_DSHOW
    ATLTRACE(  "SampleCapturePin::QueryDirection" );
#endif

    *pPinDir = PINDIR_INPUT;
    return NOERROR;
}
STDMETHODIMP SampleCapturePin::QueryId( LPWSTR * Id )
{
#ifdef DEBUG_DSHOW
    ATLTRACE(  "SampleCapturePin::QueryId" );
#endif

    *Id = L"XMediaPlatform SampleCapture Pin";

    return S_OK;
}
STDMETHODIMP SampleCapturePin::QueryAccept( const AM_MEDIA_TYPE *pmt )
{
    if( State_Stopped != p_filter->state || media_types == NULL)
    {
        ATLTRACE(  "SampleCapturePin::QueryAccept [not stopped]" );
        return S_FALSE;
    }

    if( media_types[0].majortype != pmt->majortype )
    {
        ATLTRACE(  "SampleCapturePin::QueryAccept [media type mismatch]" );
        return S_FALSE;
    }

    int i_fourcc = GetFourCCFromMediaType(*pmt);
    if( !i_fourcc )
    {   
        ATLTRACE(  "SampleCapturePin::QueryAccept "
                 "[media type not supported]" );
        return S_FALSE;
    }

    if( pmt->majortype == MEDIATYPE_Video )
    {
        /*if( pmt->pbFormat &&
            ( (((VIDEOINFOHEADER *)pmt->pbFormat)->bmiHeader.biHeight == 0) ||
              (((VIDEOINFOHEADER *)pmt->pbFormat)->bmiHeader.biWidth == 0) ) )
        {
            ATLTRACE(  "SampleCapturePin::QueryAccept [video size wxh == 0]");
            return S_FALSE;
        }*/
		VIDEOINFOHEADER	 * pSourceVHI = AMGetVideoInfoHeader(*pmt);
		if(pSourceVHI == NULL)
			return S_FALSE;

		BOOL bMatch = FALSE;
		for(int i = 0; i < media_type_count; i++)
		{		
			if(GetFourCCFromMediaType(media_types[i]) == i_fourcc)
			{
				VIDEOINFOHEADER	 * pVHI = AMGetVideoInfoHeader(media_types[i]);
				if(pVHI)
				{
					
					if(pVHI->bmiHeader.biHeight == pSourceVHI->bmiHeader.biHeight &&
						pVHI->bmiHeader.biWidth == pSourceVHI->bmiHeader.biWidth &&
						pVHI->bmiHeader.biCompression == pSourceVHI->bmiHeader.biCompression)
					{
						bMatch = TRUE;
						delete pVHI;
						break;
					}
					
					delete pVHI;
				}
			}
		}

		delete pSourceVHI;
		if(!bMatch)
		{
			return S_FALSE;
		}
		ATLTRACE(  "SampleCapturePin::QueryAccept [OK] "
                 "(width=%ld, height=%ld, chroma=%4.4s)",
                 ((VIDEOINFOHEADER *)pmt->pbFormat)->bmiHeader.biWidth,
                 ((VIDEOINFOHEADER *)pmt->pbFormat)->bmiHeader.biHeight,
                 (char *)&i_fourcc );
    }
    else if( pmt->majortype == MEDIATYPE_Audio )
    {
		BOOL bMatch = FALSE;
		WAVEFORMATEX *pWfx = reinterpret_cast<WAVEFORMATEX*>(pmt->pbFormat);
		for(int i = 0; i < media_type_count; i++)
		{
			WAVEFORMATEX *pWfxSrc = reinterpret_cast<WAVEFORMATEX*>(media_types[i].pbFormat);
			if(pWfx && pWfxSrc)
			{
				bMatch = TRUE;
				if(pWfxSrc->nChannels && pWfxSrc->nChannels != pWfx->nChannels)
					bMatch = FALSE;
				if(pWfxSrc->nSamplesPerSec && pWfxSrc->nSamplesPerSec != pWfx->nSamplesPerSec)
					bMatch = FALSE;
				if(pWfxSrc->wBitsPerSample && pWfxSrc->wBitsPerSample != pWfx->wBitsPerSample)
					bMatch = FALSE;
				if(bMatch)
					break;
					
			}
		}
		if(!bMatch)
			return S_FALSE;
        ATLTRACE(  "SampleCapturePin::QueryAccept [OK] (channels=%d, "
                 "samples/sec=%lu, bits/samples=%d, format=%4.4s)",
                 ((WAVEFORMATEX *)pmt->pbFormat)->nChannels,
                 ((WAVEFORMATEX *)pmt->pbFormat)->nSamplesPerSec,
                 ((WAVEFORMATEX *)pmt->pbFormat)->wBitsPerSample,
                 (char *)&i_fourcc );
    }   
    else
    {
        ATLTRACE(  "SampleCapturePin::QueryAccept [OK] (stream format=%4.4s)",
                 (char *)&i_fourcc );
    }

    if( p_connected_pin )
    {
        FreeMediaType( cx_media_type );
        CopyMediaType( &cx_media_type, pmt );
    }

    return S_OK;
}
STDMETHODIMP SampleCapturePin::EnumMediaTypes( IEnumMediaTypes **ppEnum )
{
#ifdef DEBUG_DSHOW_L1
    ATLTRACE(  "SampleCapturePin::EnumMediaTypes" );
#endif

    *ppEnum = new SampleCaptureEnumMediaTypes(p_input,  this, NULL );

    if( *ppEnum == NULL ) return E_OUTOFMEMORY;

    return NOERROR;
}
STDMETHODIMP SampleCapturePin::QueryInternalConnections( IPin* *apPin, ULONG *nPin )
{
#ifdef DEBUG_DSHOW_L1
    ATLTRACE(  "SampleCapturePin::QueryInternalConnections" );
#endif
    return E_NOTIMPL;
}
STDMETHODIMP SampleCapturePin::EndOfStream( void )
{
#ifdef DEBUG_DSHOW
    ATLTRACE(  "SampleCapturePin::EndOfStream" );
#endif
    return S_OK;
}
STDMETHODIMP SampleCapturePin::BeginFlush( void )
{
#ifdef DEBUG_DSHOW
    ATLTRACE(  "SampleCapturePin::BeginFlush" );
#endif
    return S_OK;
}
STDMETHODIMP SampleCapturePin::EndFlush( void )
{
#ifdef DEBUG_DSHOW
    ATLTRACE(  "SampleCapturePin::EndFlush" );
#endif

    XMPMediaSample xmp_sample;

   	EnterCriticalSection(&m_mylock);
	while( samples_queue.size() )
    {
        xmp_sample = samples_queue.back();
        samples_queue.pop_back();
        xmp_sample.p_sample->Release();
    }
	LeaveCriticalSection(&m_mylock);

    return S_OK;
}
STDMETHODIMP SampleCapturePin::NewSegment( REFERENCE_TIME tStart,
                                     REFERENCE_TIME tStop,
                                     double dRate )
{
#ifdef DEBUG_DSHOW
    ATLTRACE(  "SampleCapturePin::NewSegment" );
#endif
    return S_OK;
}

/* IMemInputPin methods */
STDMETHODIMP SampleCapturePin::GetAllocator( IMemAllocator **ppAllocator )
{
#ifdef DEBUG_DSHOW
    ATLTRACE(  "SampleCapturePin::GetAllocator" );
#endif

    return VFW_E_NO_ALLOCATOR;
}
STDMETHODIMP SampleCapturePin::NotifyAllocator( IMemAllocator *pAllocator,
                                          BOOL bReadOnly )
{
#ifdef DEBUG_DSHOW
    ATLTRACE(  "SampleCapturePin::NotifyAllocator" );
#endif

    return S_OK;
}
STDMETHODIMP SampleCapturePin::GetAllocatorRequirements( ALLOCATOR_PROPERTIES *pProps )
{
#ifdef DEBUG_DSHOW
    ATLTRACE(  "SampleCapturePin::GetAllocatorRequirements" );
#endif

    return E_NOTIMPL;
}
STDMETHODIMP SampleCapturePin::Receive( IMediaSample *pSample )
{
#if 1 //def DEBUG_DSHOW
 //   ATLTRACE(  "SampleCapturePin::Receive 0x%x %d\n", this, samples_queue.size() );
#endif
    pSample->AddRef();
#ifdef XMP_CL
    __int64 i_timestamp = mdate() * 10;
#else
	__int64 i_timestamp = mymdate() * 10;
#endif
    XMPMediaSample xmp_sample = {pSample, i_timestamp};

	EnterCriticalSection(&m_mylock);
	
    samples_queue.push_front( xmp_sample );

    /* Make sure we don't cache too many samples */
    if( samples_queue.size() > 50 )
    {
        xmp_sample = samples_queue.back();
        samples_queue.pop_back();
        ATLTRACE(  "SampleCapturePin::Receive trashing late input sample\n" );
        xmp_sample.p_sample->Release();
    }

//    xmp_cond_signal( &p_sys->wait );
	LeaveCriticalSection(&m_mylock);

    return S_OK;
}
STDMETHODIMP SampleCapturePin::ReceiveMultiple( IMediaSample **pSamples,
                                          long nSamples,
                                          long *nSamplesProcessed )
{
    HRESULT hr = S_OK;

    *nSamplesProcessed = 0;
    while( nSamples-- > 0 )
    {
         hr = Receive( pSamples[*nSamplesProcessed] );
         if( hr != S_OK ) break;
         (*nSamplesProcessed)++;
    }
    return hr;
}
STDMETHODIMP SampleCapturePin::ReceiveCanBlock( void )
{
#ifdef DEBUG_DSHOW
    ATLTRACE(  "SampleCapturePin::ReceiveCanBlock" );
#endif

    return S_FALSE; /* Thou shalt not block */
}

/****************************************************************************
 * Implementation of our dummy directshow filter class
 ****************************************************************************/
SampleCaptureFilter::SampleCaptureFilter( void *_p_input, 
                              AM_MEDIA_TYPE *mt, size_t mt_count )
  : p_input( _p_input ),
    p_pin( new SampleCapturePin( _p_input, this, mt, mt_count ) ),
    state( State_Stopped ), i_ref( 1 ) 
{
}

SampleCaptureFilter::~SampleCaptureFilter()
{
#ifdef DEBUG_DSHOW
    ATLTRACE(  "SampleCaptureFilter::~SampleCaptureFilter" );
#endif
    p_pin->Release();
}

/* IUnknown methods */
STDMETHODIMP SampleCaptureFilter::QueryInterface( REFIID riid, void **ppv )
{
#ifdef DEBUG_DSHOW_L1
    ATLTRACE(  "SampleCaptureFilter::QueryInterface" );
#endif

    if( riid == IID_IUnknown )
    {
        AddRef();
        *ppv = (IUnknown *)this;
        return NOERROR;
    }
    if( riid == IID_IPersist )
    {
        AddRef();
        *ppv = (IPersist *)this;
        return NOERROR;
    }
    if( riid == IID_IMediaFilter )
    {
        AddRef();
        *ppv = (IMediaFilter *)this;
        return NOERROR;
    }
    if( riid == IID_IBaseFilter )
    {
        AddRef();
        *ppv = (IBaseFilter *)this;
        return NOERROR;
    }
    else
    {
#ifdef DEBUG_DSHOW_L1
        ATLTRACE(  "SampleCaptureFilter::QueryInterface() failed for: "
                 "%04X-%02X-%02X-%02X%02X%02X%02X%02X%02X%02X%02X",
                 (int)riid.Data1, (int)riid.Data2, (int)riid.Data3,
                 static_cast<int>(riid.Data4[0]), (int)riid.Data4[1],
                 (int)riid.Data4[2], (int)riid.Data4[3],
                 (int)riid.Data4[4], (int)riid.Data4[5],
                 (int)riid.Data4[6], (int)riid.Data4[7] );
#endif
        *ppv = NULL;
        return E_NOINTERFACE;
    }
};
STDMETHODIMP_(ULONG) SampleCaptureFilter::AddRef()
{
    //ATLTRACE(  "=================SampleCaptureFilter::AddRef (ref: %i)\n", i_ref + 1);

    return InterlockedIncrement(&i_ref);
};
STDMETHODIMP_(ULONG) SampleCaptureFilter::Release()
{
    //ATLTRACE(  "=================SampleCaptureFilter::Release (ref: %i)\n", i_ref - 1);

   	long i_save = i_ref;
    if( !InterlockedDecrement(&i_ref) ) delete this;
	
    return i_save - 1;
};

/* IPersist method */
STDMETHODIMP SampleCaptureFilter::GetClassID(CLSID *pClsID)
{
#ifdef DEBUG_DSHOW
    ATLTRACE(  "SampleCaptureFilter::GetClassID" );
#endif
    return E_NOTIMPL;
};

/* IMediaFilter methods */
STDMETHODIMP SampleCaptureFilter::GetState(DWORD dwMSecs, FILTER_STATE *State)
{
#ifdef DEBUG_DSHOW
    ATLTRACE(  "SampleCaptureFilter::GetState %i", state );
#endif

    *State = state;
    return S_OK;
};
STDMETHODIMP SampleCaptureFilter::SetSyncSource(IReferenceClock *pClock)
{
#ifdef DEBUG_DSHOW
    ATLTRACE(  "SampleCaptureFilter::SetSyncSource" );
#endif

    return S_OK;
};
STDMETHODIMP SampleCaptureFilter::GetSyncSource(IReferenceClock **pClock)
{
#ifdef DEBUG_DSHOW
    ATLTRACE(  "SampleCaptureFilter::GetSyncSource" );
#endif

    *pClock = NULL;
    return NOERROR;
};
STDMETHODIMP SampleCaptureFilter::Stop()
{
#ifdef DEBUG_DSHOW
    ATLTRACE(  "SampleCaptureFilter::Stop" );
#endif

    p_pin->EndFlush();

    state = State_Stopped;
    return S_OK;
};
STDMETHODIMP SampleCaptureFilter::Pause()
{
#ifdef DEBUG_DSHOW
    ATLTRACE(  "SampleCaptureFilter::Pause" );
#endif

    state = State_Paused;
    return S_OK;
};
STDMETHODIMP SampleCaptureFilter::Run(REFERENCE_TIME tStart)
{
#ifdef DEBUG_DSHOW
    ATLTRACE(  "SampleCaptureFilter::Run" );
#endif

    state = State_Running;
    return S_OK;
};

/* IBaseFilter methods */
STDMETHODIMP SampleCaptureFilter::EnumPins( IEnumPins ** ppEnum )
{
#ifdef DEBUG_DSHOW
    ATLTRACE(  "SampleCaptureFilter::EnumPins" );
#endif

    /* Create a new ref counted enumerator */
    *ppEnum = new SampleCaptureEnumPins(p_input,  this, NULL );
    return *ppEnum == NULL ? E_OUTOFMEMORY : NOERROR;
};
STDMETHODIMP SampleCaptureFilter::FindPin( LPCWSTR Id, IPin ** ppPin )
{
#ifdef DEBUG_DSHOW
    ATLTRACE(  "SampleCaptureFilter::FindPin" );
#endif
    return E_NOTIMPL;
};
STDMETHODIMP SampleCaptureFilter::QueryFilterInfo( FILTER_INFO * pInfo )
{
#ifdef DEBUG_DSHOW
    ATLTRACE(  "SampleCaptureFilter::QueryFilterInfo" );
#endif

    memcpy(pInfo->achName, FILTER_NAME, sizeof(FILTER_NAME));

    pInfo->pGraph = p_graph;
    if( p_graph ) p_graph->AddRef();

    return NOERROR;
};
STDMETHODIMP SampleCaptureFilter::JoinFilterGraph( IFilterGraph * pGraph,
                                             LPCWSTR pName )
{
#ifdef DEBUG_DSHOW
    ATLTRACE(  "SampleCaptureFilter::JoinFilterGraph" );
#endif

    p_graph = pGraph;

    return NOERROR;
};
STDMETHODIMP SampleCaptureFilter::QueryVendorInfo( LPWSTR* pVendorInfo )
{
#ifdef DEBUG_DSHOW
    ATLTRACE(  "SampleCaptureFilter::QueryVendorInfo" );
#endif
    return E_NOTIMPL;
};

/* Custom methods */
SampleCapturePin *SampleCaptureFilter::CustomGetPin()
{
    return p_pin;
}

/****************************************************************************
 * Implementation of our dummy directshow enumpins class
 ****************************************************************************/

SampleCaptureEnumPins::SampleCaptureEnumPins( void *_p_input,
                                  SampleCaptureFilter *_p_filter,
                                  SampleCaptureEnumPins *pEnumPins )
  : p_input( _p_input ), p_filter( _p_filter ), i_ref( 1 )
{
    /* Hold a reference count on our filter */
    p_filter->AddRef();

    /* Are we creating a new enumerator */

    if( pEnumPins == NULL )
    {
        i_position = 0;
    }
    else
    {
        i_position = pEnumPins->i_position;
    }
}

SampleCaptureEnumPins::~SampleCaptureEnumPins()
{
#ifdef DEBUG_DSHOW_L1
    ATLTRACE(  "SampleCaptureEnumPins::~SampleCaptureEnumPins" );
#endif
    p_filter->Release();
}

/* IUnknown methods */
STDMETHODIMP SampleCaptureEnumPins::QueryInterface( REFIID riid, void **ppv )
{
#ifdef DEBUG_DSHOW_L1
    ATLTRACE(  "SampleCaptureEnumPins::QueryInterface" );
#endif

    if( riid == IID_IUnknown ||
        riid == IID_IEnumPins )
    {
        AddRef();
        *ppv = (IEnumPins *)this;
        return NOERROR;
    }
    else
    {
        *ppv = NULL;
        return E_NOINTERFACE;
    }
};
STDMETHODIMP_(ULONG) SampleCaptureEnumPins::AddRef()
{
#ifdef DEBUG_DSHOW_L1
    ATLTRACE(  "SampleCaptureEnumPins::AddRef (ref: %i)", i_ref + 1 );
#endif

    return i_ref++;
};
STDMETHODIMP_(ULONG) SampleCaptureEnumPins::Release()
{
#ifdef DEBUG_DSHOW_L1
    ATLTRACE(  "SampleCaptureEnumPins::Release (ref: %i)", i_ref - 1);
#endif

    if( !InterlockedDecrement(&i_ref) ) delete this;

    return 0;
};

/* IEnumPins */
STDMETHODIMP SampleCaptureEnumPins::Next( ULONG cPins, IPin ** ppPins,
                                    ULONG * pcFetched )
{
#ifdef DEBUG_DSHOW_L1
    ATLTRACE(  "SampleCaptureEnumPins::Next" );
#endif

    unsigned int i_fetched = 0;

    if( i_position < 1 && cPins > 0 )
    {
        IPin *pPin = p_filter->CustomGetPin();
        *ppPins = pPin;
        pPin->AddRef();
        i_fetched = 1;
        i_position++;
    }

    if( pcFetched ) *pcFetched = i_fetched;

    return (i_fetched == cPins) ? S_OK : S_FALSE;
};
STDMETHODIMP SampleCaptureEnumPins::Skip( ULONG cPins )
{
#ifdef DEBUG_DSHOW_L1
    ATLTRACE(  "SampleCaptureEnumPins::Skip" );
#endif

    i_position += cPins;

    if( i_position > 1 )
    {
        return S_FALSE;
    }

    return S_OK;
};
STDMETHODIMP SampleCaptureEnumPins::Reset()
{
#ifdef DEBUG_DSHOW_L1
    ATLTRACE(  "SampleCaptureEnumPins::Reset" );
#endif

    i_position = 0;
    return S_OK;
};
STDMETHODIMP SampleCaptureEnumPins::Clone( IEnumPins **ppEnum )
{
#ifdef DEBUG_DSHOW_L1
    ATLTRACE(  "SampleCaptureEnumPins::Clone" );
#endif

    *ppEnum = new SampleCaptureEnumPins(p_input,  p_filter, this );
    if( *ppEnum == NULL ) return E_OUTOFMEMORY;

    return NOERROR;
};

/****************************************************************************
 * Implementation of our dummy directshow enummediatypes class
 ****************************************************************************/
SampleCaptureEnumMediaTypes::SampleCaptureEnumMediaTypes( void *_p_input,
    SampleCapturePin *_p_pin, SampleCaptureEnumMediaTypes *pEnumMediaTypes )
  : p_input( _p_input ), p_pin( _p_pin ), i_ref( 1 )
{
    /* Hold a reference count on our filter */
    p_pin->AddRef();

    /* Are we creating a new enumerator */
    if( pEnumMediaTypes == NULL )
    {
        CopyMediaType(&cx_media_type, &p_pin->cx_media_type); 
        i_position = 0;
    }
    else
    {
        CopyMediaType(&cx_media_type, &pEnumMediaTypes->cx_media_type); 
        i_position = pEnumMediaTypes->i_position;
    }
}

SampleCaptureEnumMediaTypes::~SampleCaptureEnumMediaTypes()
{
#ifdef DEBUG_DSHOW_L1
    ATLTRACE(  "SampleCaptureEnumMediaTypes::~SampleCaptureEnumMediaTypes" );
#endif
    FreeMediaType(cx_media_type);
    p_pin->Release();
}

/* IUnknown methods */
STDMETHODIMP SampleCaptureEnumMediaTypes::QueryInterface( REFIID riid, void **ppv )
{
#ifdef DEBUG_DSHOW_L1
    ATLTRACE(  "SampleCaptureEnumMediaTypes::QueryInterface" );
#endif

    if( riid == IID_IUnknown ||
        riid == IID_IEnumMediaTypes )
    {
        AddRef();
        *ppv = (IEnumMediaTypes *)this;
        return NOERROR;
    }
    else
    {
        *ppv = NULL;
        return E_NOINTERFACE;
    }
};
STDMETHODIMP_(ULONG) SampleCaptureEnumMediaTypes::AddRef()
{
#ifdef DEBUG_DSHOW_L1
    ATLTRACE(  "SampleCaptureEnumMediaTypes::AddRef (ref: %i)", i_ref );
#endif

    return i_ref++;
};
STDMETHODIMP_(ULONG) SampleCaptureEnumMediaTypes::Release()
{
#ifdef DEBUG_DSHOW_L1
    ATLTRACE(  "SampleCaptureEnumMediaTypes::Release (ref: %i)", i_ref );
#endif

    if( !InterlockedDecrement(&i_ref) ) delete this;

    return 0;
};

/* IEnumMediaTypes */
STDMETHODIMP SampleCaptureEnumMediaTypes::Next( ULONG cMediaTypes,
                                          AM_MEDIA_TYPE ** ppMediaTypes,
                                          ULONG * pcFetched )
{
#ifdef DEBUG_DSHOW_L1
    ATLTRACE(  "SampleCaptureEnumMediaTypes::Next " );
#endif
    ULONG copied = 0;
    ULONG offset = 0;
    ULONG max = p_pin->media_type_count;

    if( ! ppMediaTypes ) 
        return E_POINTER;

    if( (! pcFetched)  && (cMediaTypes > 1) )
       return E_POINTER;

    /*
    ** use connection media type as first entry in iterator if it exists
    */
    copied = 0;
    if( cx_media_type.subtype != GUID_NULL )
    {
        ++max;
		//godzilar
		++offset;
		if( i_position == 0 )
        {
            ppMediaTypes[copied] =
                (AM_MEDIA_TYPE *)CoTaskMemAlloc(sizeof(AM_MEDIA_TYPE));
            if( CopyMediaType(ppMediaTypes[copied], &cx_media_type) != S_OK )
                return E_OUTOFMEMORY;
            ++i_position; 
            ++copied;
        }
    }

    while( (copied < cMediaTypes) && (i_position < max)  )
    {
        ppMediaTypes[copied] =
            (AM_MEDIA_TYPE *)CoTaskMemAlloc(sizeof(AM_MEDIA_TYPE));
        if( CopyMediaType( ppMediaTypes[copied],
                           &p_pin->media_types[i_position-offset]) != S_OK )
            return E_OUTOFMEMORY;

        ++copied;
        ++i_position; 
    }

    if( pcFetched )  *pcFetched = copied;

    return (copied == cMediaTypes) ? S_OK : S_FALSE;
};
STDMETHODIMP SampleCaptureEnumMediaTypes::Skip( ULONG cMediaTypes )
{
    ULONG max =  p_pin->media_type_count;
    if( cx_media_type.subtype != GUID_NULL )
    {
        max = 1;
    }
#ifdef DEBUG_DSHOW_L1
    ATLTRACE(  "SampleCaptureEnumMediaTypes::Skip" );
#endif

    i_position += cMediaTypes;
    return (i_position < max) ? S_OK : S_FALSE;
};
STDMETHODIMP SampleCaptureEnumMediaTypes::Reset()
{
#ifdef DEBUG_DSHOW_L1
    ATLTRACE(  "SampleCaptureEnumMediaTypes::Reset" );
#endif

    FreeMediaType(cx_media_type);
    CopyMediaType(&cx_media_type, &p_pin->cx_media_type); 
    i_position = 0;
    return S_OK;
};
STDMETHODIMP SampleCaptureEnumMediaTypes::Clone( IEnumMediaTypes **ppEnum )
{
#ifdef DEBUG_DSHOW_L1
    ATLTRACE(  "SampleCaptureEnumMediaTypes::Clone" );
#endif

    *ppEnum = new SampleCaptureEnumMediaTypes(p_input,  p_pin, this );
    if( *ppEnum == NULL ) return E_OUTOFMEMORY;

    return NOERROR;
};