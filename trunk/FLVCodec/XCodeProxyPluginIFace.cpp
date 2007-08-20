//**********************************************************************************
// Filename: XCodeProxyPluginIFace.cpp
//
// ViXS Systems Confidential and Proprietary
//
//*********************************************************************************

#include "stdafx.h"
#include <streams.h>
#include <ks.h>
#include <ksmedia.h>
#include <tchar.h>

#include "XCodeProxyPluginIFace.h"
#include "xc2guids.h"



// This routine is invoked by DShow to create an instance of our interface handler.
// It is referred to in the g_Templates structure.
// 
// Arguments:
//		piOuterUnknown	- Specifies the outer unknown, if any.
//		phResult		- The place in which to put an error code.
// Return Value:
//		pointer to the nondelegating CUnknown portion of the object.
//
CUnknown* CXCodeProxyPluginIFace::CreateInstance( LPUNKNOWN piOuterUnknown, HRESULT* phResult )
{
    CXCodeProxyPluginIFace* pXCodeProxyPluginIFace = NULL;

    // We should receive pointer to KS proxy as our outer unknown.
    // Make sure that we got what we expect
    HRESULT hResult = S_OK;
    if( piOuterUnknown == NULL )
    {
        DbgLog(( LOG_ERROR | LOG_TRACE, 0, _T( "No outer unknown object passed to interface handler!" ) ));
        hResult = VFW_E_NEED_OWNER;
    }
    else
    {
        IKsPropertySet* piKsPropertySet;
        hResult = piOuterUnknown->QueryInterface(
                                        __uuidof( piKsPropertySet ),
                                        reinterpret_cast< void** >( &piKsPropertySet ) );
        if( FAILED( hResult ) )
            DbgLog(( LOG_ERROR | LOG_TRACE, 0, _T( "Outer unknown doesn't support IKsPropertySet" ) ));
        else
        {
            // Create interface handler object
			pXCodeProxyPluginIFace = new CXCodeProxyPluginIFace( piKsPropertySet );

            if( pXCodeProxyPluginIFace == NULL )
            {
                DbgLog(( LOG_ERROR | LOG_TRACE, 0, _T( "Out of memory" ) ));
                hResult = E_OUTOFMEMORY;
            }

            piKsPropertySet->Release();
        }
    }

    ASSERT( phResult != NULL );
    *phResult = hResult;

    return static_cast< CUnknown* >( pXCodeProxyPluginIFace );
}


// Typical DShow object's constructor
CXCodeProxyPluginIFace::CXCodeProxyPluginIFace( IKsPropertySet* piKsPropertySet ) :
    CUnknown( T_XCODEKSPROXYPROPERTY_INTHANDLER_TEXT, piKsPropertySet ),
    m_piKsPropertySet( piKsPropertySet ),
    m_piKsPropertyAudioInPinSet(piKsPropertySet),
    m_piKsPropertyVideoOutPinSet(piKsPropertySet),
    m_piKsPropertyVideoInPinSet(piKsPropertySet)
{
}


STDMETHODIMP CXCodeProxyPluginIFace::NonDelegatingQueryInterface( REFIID riid, void** ppv )
{
    if( ppv == NULL )
        return E_POINTER;
    else if( riid == __uuidof( IXCodeKsproxyPropertyConfig ) )
        return GetInterface( static_cast< IXCodeKsproxyPropertyConfig* >( this ), ppv );
    else
        return CUnknown::NonDelegatingQueryInterface( riid, ppv );
}



STDMETHODIMP CXCodeProxyPluginIFace::GetRate( long* plRate )
{
    DWORD dwReturned = 0;

	HRESULT hResult = m_piKsPropertySet->Get(
                                            XC2_CAP_VIDEO_FRATE,
											0,
											plRate,
                                            sizeof( *plRate ),
                                            plRate,
                                            sizeof( *plRate ),
                                            &dwReturned );

    if( SUCCEEDED( hResult ) )
    {
        ASSERT( dwReturned == sizeof( *plRate ) );
    }
    else
    {
        DbgLog((
            LOG_ERROR | LOG_TRACE,
            0,
            _T( "CXCodeProxyPluginIFace::GetRate: failed to get the rate. Error 0x%X" ),
            hResult ));
    }

    return hResult;
}


STDMETHODIMP CXCodeProxyPluginIFace::SetRate( long lRate )
{
    HRESULT hResult = m_piKsPropertySet->Set(
                                            XC2_CAP_VIDEO_FRATE,
                                            0,
                                            NULL,
                                            0,
                                            &lRate,
                                            sizeof( lRate ) );
    if( FAILED( hResult ) )
    {
        DbgLog((
            LOG_ERROR | LOG_TRACE,
            0,
            _T( "XCodeProxyPluginIFace::SetRate: failed to set the rate to %ld. Error 0x%X" ),
            lRate,
            hResult ));
    }

    return hResult;
}

STDMETHODIMP CXCodeProxyPluginIFace::SetFormat( long lFormat )
{
    HRESULT hResult = m_piKsPropertySet->Set(
                                            XC2_CAP_SYSTEM_FORMAT,
                                            0,
                                            NULL,
                                            0,
                                            &lFormat,
                                            sizeof( lFormat ) );
    if( FAILED( hResult ) )
    {
        DbgLog((
            LOG_ERROR | LOG_TRACE,
            0,
            _T( "XCodeProxyPluginIFace::SetFormat: failed to set the Format to %ld. Error 0x%X" ),
            lFormat,
            hResult ));
    }

    return hResult;
}

STDMETHODIMP CXCodeProxyPluginIFace::SetOutputWidth( long lWidth )
{
    HRESULT hResult = m_piKsPropertySet->Set(
                                            XC2_CAP_VIDEO_DISP_HORZ,
                                            0,
                                            NULL,
                                            0,
                                            &lWidth,
                                            sizeof( lWidth ) );
    if( FAILED( hResult ) )
    {
        DbgLog((
            LOG_ERROR | LOG_TRACE,
            0,
            _T( "XCodeProxyPluginIFace::SetWidth: failed to set the width to %ld. Error 0x%X" ),
            lWidth,
            hResult ));
    }

    return hResult;
}
STDMETHODIMP CXCodeProxyPluginIFace::SetOutputHeight( long lHeight )
{
    HRESULT hResult = m_piKsPropertySet->Set(
                                            XC2_CAP_VIDEO_DISP_VERT,
                                            0,
                                            NULL,
                                            0,
                                            &lHeight,
                                            sizeof( lHeight ) );
    if( FAILED( hResult ) )
    {
        DbgLog((
            LOG_ERROR | LOG_TRACE,
            0,
            _T( "XCodeProxyPluginIFace::SetHeight: failed to set the Height to %ld. Error 0x%X" ),
            lHeight,
            hResult ));
    }

    return hResult;
}

STDMETHODIMP CXCodeProxyPluginIFace::GetOutputWidth(long *plWidth)
{
	DWORD dwReturned = 0;
	HRESULT hResult = m_piKsPropertySet->Get(
                                            XC2_CAP_VIDEO_DISP_HORZ,
											0,
											plWidth,
                                            sizeof( *plWidth ),
                                            plWidth,
                                            sizeof( *plWidth ),
                                            &dwReturned );

    if( SUCCEEDED( hResult ) )
    {
        ASSERT( dwReturned == sizeof( *plWidth ) );
    }
    else
    {
        DbgLog((
            LOG_ERROR | LOG_TRACE,
            0,
            _T( "CXCodeProxyPluginIFace::GetOutputWidth: failed to get the width. Error 0x%X" ),
            hResult ));
    }

    return hResult;
}

STDMETHODIMP CXCodeProxyPluginIFace::GetOutputHeight(long *plHeight)
{
	DWORD dwReturned = 0;
	HRESULT hResult = m_piKsPropertySet->Get(
                                            XC2_CAP_VIDEO_DISP_VERT,
											0,
											plHeight,
                                            sizeof( *plHeight ),
                                            plHeight,
                                            sizeof( *plHeight ),
                                            &dwReturned );

    if( SUCCEEDED( hResult ) )
    {
        ASSERT( dwReturned == sizeof( *plHeight ) );
    }
    else
    {
        DbgLog((
            LOG_ERROR | LOG_TRACE,
            0,
            _T( "CXCodeProxyPluginIFace::GetOutputHeight: failed to get the width. Error 0x%X" ),
            hResult ));
    }

    return hResult;
}
STDMETHODIMP CXCodeProxyPluginIFace::GetSystemFormat(long *plStd)
{
#if 1 // Not implemented in the driver
	DWORD dwReturned = 0;
	HRESULT hResult = m_piKsPropertySet->Get(
                                            XC2_CAP_SYSTEM_FORMAT,
											0,
											plStd,
                                            sizeof( *plStd ),
                                            plStd,
                                            sizeof( *plStd ),
                                            &dwReturned );

    if( SUCCEEDED( hResult ) )
    {
        ASSERT( dwReturned == sizeof( *plStd ) );
    }
    else
    {
        DbgLog((
            LOG_ERROR | LOG_TRACE,
            0,
            _T( "CXCodeProxyPluginIFace::GetSystemFormat: failed to get format. Error 0x%X" ),
            hResult ));
    }

    return hResult;
#else
	return S_OK;
#endif
}
STDMETHODIMP CXCodeProxyPluginIFace::SetAudioMiniI2SMstrMode(long lValue)
{
#if 1
    HRESULT hresult;

    hresult = m_piKsPropertySet->Set(XC2_CAP_AUDIO_XCMINI_I2S_MSTR_MODE, 0, NULL, 0, &lValue, sizeof(lValue));
    if (FAILED(hresult))
    {
        DbgLog((LOG_ERROR|LOG_TRACE, 0, _T("CXCodeProxyPluginIFace::SetAudioMiniI2SMstrMode(%ld): FAILED 0x%08lX"), lValue, hresult));
    }
    return hresult;
#else
	return S_OK;
#endif
}
STDMETHODIMP CXCodeProxyPluginIFace::SetProfile(long lValue)
{
    HRESULT hresult;
    DWORD dwReturned;

    dwReturned = 0;
    hresult = m_piKsPropertySet->Set(XC2_CAP_MPEG4_PROFILE, 0, NULL, 0, &lValue, sizeof(lValue));
     if (FAILED(hresult))
    {
	    DbgLog((LOG_ERROR|LOG_TRACE, 0, _T("CXCodeProxyPluginIFace::SetProfile: FAILED 0x%08lX"), hresult));
    }
    return hresult;
}

STDMETHODIMP CXCodeProxyPluginIFace::SetLevel(long lValue)
{
    HRESULT hresult;
    DWORD dwReturned;

    dwReturned = 0;
    hresult = m_piKsPropertySet->Set(XC2_CAP_MPEG4_LEVEL, 0, NULL, 0, &lValue, sizeof(lValue));
    if (FAILED(hresult))
    {
        DbgLog((LOG_ERROR|LOG_TRACE, 0, _T("CXCodeProxyPluginIFace::SetLevel: FAILED 0x%08lX"), hresult));
    }
    return hresult;
}

STDMETHODIMP CXCodeProxyPluginIFace::SetAspectRatio(long lValue)
{
    HRESULT hresult;

    hresult = m_piKsPropertySet->Set(XC2_CAP_ASPECT_RATIO, 0, NULL, 0, &lValue, sizeof(lValue));
    if (FAILED(hresult))
    {
        DbgLog((LOG_ERROR|LOG_TRACE, 0, _T("CXCodeProxyPluginIFace::SetAspectRatio(%ld): FAILED 0x%08lX"), lValue, hresult));
    }
    return hresult;
}

STDMETHODIMP CXCodeProxyPluginIFace::SetMP4AspectRatio(long lValue)
{
    HRESULT hresult;

    hresult = m_piKsPropertySet->Set(XC_CAP_MPEG4_ASPECT_RATIO, 0, NULL, 0, &lValue, sizeof(lValue));
    if (FAILED(hresult))
    {
        DbgLog((LOG_ERROR|LOG_TRACE, 0, _T("CXCodeProxyPluginIFace::SetMP4AspectRatio(%ld): FAILED 0x%08lX"), lValue, hresult));
    }
    return hresult;
}

STDMETHODIMP CXCodeProxyPluginIFace::GetMP4MdatInfo(PXCINFO_MDAT_SIZE_S pInfo)
{
    HRESULT hresult;
    DWORD dwReturned;

    hresult = m_piKsPropertySet->Get(XC_INFO, XCINFO_MDAT_SIZE, NULL, 0, pInfo, sizeof(*pInfo), &dwReturned);
    if (FAILED(hresult))
    {
        DbgLog((LOG_ERROR|LOG_TRACE, 0, _T("CXCodeProxyPluginIFace::GetMP4MdatInfo(%x): FAILED 0x%08lX"), pInfo, hresult));
    }
    return hresult;
}

STDMETHODIMP CXCodeProxyPluginIFace::GetMirrorCaps(unsigned int*plValue)
{
	DWORD dwReturned = 0;
    HRESULT hresult;

    hresult = m_piKsPropertySet->Get(XC_CAP_MIRROR_CAPS, 0, plValue, sizeof(*plValue), plValue, sizeof(*plValue), &dwReturned);
    if (SUCCEEDED(hresult))
    {
        ASSERT(dwReturned == sizeof(*plValue));
    }
    else
    {
        DbgLog((LOG_ERROR|LOG_TRACE, 0, _T("CXC2Config::GetMirror: FAILED 0x%08lX"), hresult));
    }
    return hresult;
}

STDMETHODIMP CXCodeProxyPluginIFace::SetMirrorInfoToDriver(BOOL status)
{
    HRESULT hresult;
	XCINFO_RUN_MIRROR_S RunMirror;

	RunMirror.Head.id = XCINFO_RUN_MIRROR;
	RunMirror.bRunMirror = status;

	hresult = m_piKsPropertySet->Set(XC_INFO, XCINFO_RUN_MIRROR, NULL, 0, &RunMirror, sizeof(RunMirror));
    if (FAILED(hresult))
    {
        DbgLog((LOG_ERROR|LOG_TRACE, 0, _T("CXC2Config::SetMirrorInfoToDriver(): FAILED 0x%08lX"), hresult));
    }
    return hresult;
}

STDMETHODIMP CXCodeProxyPluginIFace::SetFlushMessageToDriver()
{
    HRESULT hresult;
	XCINFO_FLUSH_S Flush;

	Flush.Head.id = XCINFO_FLUSH;
	Flush.Flush = TRUE;

	hresult = m_piKsPropertySet->Set(XC_INFO, XCINFO_FLUSH, NULL, 0, &Flush, sizeof(Flush));
    if (FAILED(hresult))
    {
        DbgLog((LOG_ERROR|LOG_TRACE, 0, _T("CXC2Config::SetFlushMessageToDriver(): FAILED 0x%08lX"), hresult));
    }
    return hresult;
}

STDMETHODIMP CXCodeProxyPluginIFace::SetFlushYUVSendMessageToDriver()
{
    HRESULT hresult;
	XCINFO_FLUSH_S Flush;

	Flush.Head.id = XCINFO_FLUSH;
	Flush.Flush = TRUE;

	hresult = m_piKsPropertySet->Set(XC_INFO, XCINFO_FLUSH, NULL, 0, &Flush, sizeof(Flush));
    if (FAILED(hresult))
    {
        DbgLog((LOG_ERROR|LOG_TRACE, 0, _T("CXC2Config::SetFlushYUVSendMessageToDriver(): FAILED 0x%08lX"), hresult));
    }
    return hresult;
}

STDMETHODIMP CXCodeProxyPluginIFace::SetFlushPCMSendMessageToDriver()
{
    HRESULT hresult;
	XCINFO_FLUSH_S Flush;

	Flush.Head.id = XCINFO_FLUSH;
	Flush.Flush = TRUE;

	hresult = m_piKsPropertySet->Set(XC_INFO, XCINFO_FLUSH, NULL, 0, &Flush, sizeof(Flush));
    if (FAILED(hresult))
    {
        DbgLog((LOG_ERROR|LOG_TRACE, 0, _T("CXC2Config::SetFlushPCMSendMessageToDriver(): FAILED 0x%08lX"), hresult));
    }
    return hresult;
}

STDMETHODIMP CXCodeProxyPluginIFace::SetFlushAESSendMessageToDriver()
{
    HRESULT hresult;
	XCINFO_FLUSH_S Flush;

	Flush.Head.id = XCINFO_FLUSH;
	Flush.Flush = TRUE;

	hresult = m_piKsPropertySet->Set(XC_INFO, XCINFO_FLUSH, NULL, 0, &Flush, sizeof(Flush));
    if (FAILED(hresult))
    {
        DbgLog((LOG_ERROR|LOG_TRACE, 0, _T("CXC2Config::SetFlushAESSendMessageToDriver(): FAILED 0x%08lX"), hresult));
    }
    return hresult;
}

STDMETHODIMP CXCodeProxyPluginIFace::SetFlushVESSendMessageToDriver()
{
    HRESULT hresult;
	XCINFO_FLUSH_S Flush;

	Flush.Head.id = XCINFO_FLUSH;
	Flush.Flush = TRUE;

	hresult = m_piKsPropertySet->Set(XC_INFO, XCINFO_FLUSH, NULL, 0, &Flush, sizeof(Flush));
    if (FAILED(hresult))
    {
        DbgLog((LOG_ERROR|LOG_TRACE, 0, _T("CXC2Config::SetFlushVESSendMessageToDriver(): FAILED 0x%08lX"), hresult));
    }
    return hresult;
}


STDMETHODIMP CXCodeProxyPluginIFace::GetFinishFlagFromDriver(BOOL *lValue)
{
    HRESULT hresult;
	ULONG dwReturned;
	XCINFO_FLUSH_S Flush;

	Flush.Head.id = XCINFO_FLUSH;

    hresult = m_piKsPropertySet->Get(XC_INFO, XCINFO_FLUSH, NULL, 0, &Flush, sizeof(Flush), &dwReturned);
    if (FAILED(hresult))
    {
        DbgLog((LOG_ERROR|LOG_TRACE, 0, _T("CXC2Config::GetFinishFlagFromDriver(): FAILED 0x%08lX"), hresult));
    }
	else
	{
		*lValue = Flush.Flush;
	}

    return hresult;
}

STDMETHODIMP CXCodeProxyPluginIFace::GetPeakBitrate(long *plArg)
{
#if 1
	DWORD dwReturned = 0;
	HRESULT hResult = m_piKsPropertySet->Get(
                                            XC2_CAP_VIDEO_PEAK_BITRATE,
											0,
											plArg,
                                            sizeof( *plArg ),
                                            plArg,
                                            sizeof( *plArg ),
                                            &dwReturned );

    if( SUCCEEDED( hResult ) )
    {
        ASSERT( dwReturned == sizeof( *plArg ) );
    }
    else
    {
        DbgLog((
            LOG_ERROR | LOG_TRACE,
            0,
            _T( "CXCodeProxyPluginIFace::GetPeakBitrate: failed to get Peak Bitrate. Error 0x%X" ),
            hResult ));
    }

    return hResult;
#else
	return S_OK;
#endif
}
STDMETHODIMP CXCodeProxyPluginIFace::GetBitrateMode(long *plArg)
{
	DWORD dwReturned = 0;
	HRESULT hResult = m_piKsPropertySet->Get(
                                            XC2_CAP_VIDEO_BITRATE_MODE,
											0,
											plArg,
                                            sizeof( *plArg ),
                                            plArg,
                                            sizeof( *plArg ),
                                            &dwReturned 
											);

    if( SUCCEEDED( hResult ) )
    {
        ASSERT( dwReturned == sizeof( *plArg ) );
    }
    else
    {
        DbgLog((
            LOG_ERROR | LOG_TRACE,
            0,
            _T( "CXCodeProxyPluginIFace::GetBitrateMode: failed to get Bitrate. Error 0x%X" ),
            hResult ));
    }

    return hResult;
}


STDMETHODIMP CXCodeProxyPluginIFace::GetBitrate(long *plArg)
{
	DWORD dwReturned = 0;
	HRESULT hResult = m_piKsPropertySet->Get(
                                            XC2_CAP_VIDEO_BITRATE,
											0,
											plArg,
                                            sizeof( *plArg ),
                                            plArg,
                                            sizeof( *plArg ),
                                            &dwReturned 
											);

    if( SUCCEEDED( hResult ) )
    {
        ASSERT( dwReturned == sizeof( *plArg ) );
    }
    else
    {
        DbgLog((
            LOG_ERROR | LOG_TRACE,
            0,
            _T( "CXCodeProxyPluginIFace::GetBitrate: failed to get Bitrate. Error 0x%X" ),
            hResult ));
    }

    return hResult;
}

STDMETHODIMP CXCodeProxyPluginIFace::GetVideoType(long *plArg)
{

	DWORD dwReturned = 0;
	HRESULT hResult = m_piKsPropertySet->Get(
                                            XC2_CAP_VIDEO_TYPE,
											0,
											plArg,
                                            sizeof( *plArg ),
                                            plArg,
                                            sizeof( *plArg ),
                                            &dwReturned 
											);

    if( SUCCEEDED( hResult ) )
    {
        ASSERT( dwReturned == sizeof( *plArg ) );
    }
    else
    {
        DbgLog((
            LOG_ERROR | LOG_TRACE,
            0,
            _T( "CXCodeProxyPluginIFace::GetVideoType: failed to get Bitrate. Error 0x%X" ),
            hResult ));
    }

    return hResult;
}
///////////////////////////////////////////////////////////////////////////////////////////////
//  Filter Caps Gets

STDMETHODIMP CXCodeProxyPluginIFace::GetFilterCaps      (ULONG *plArg)
{
	DWORD dwReturned = 0;
	HRESULT hResult = m_piKsPropertySet->Get(
                                            XC2_CAP_VIDEO_FILTER_CAPS,
											0,
											plArg,
                                            sizeof( *plArg ),
                                            plArg,
                                            sizeof( *plArg ),
                                            &dwReturned 
											);

    if( SUCCEEDED( hResult ) )
    {
        ASSERT( dwReturned == sizeof( *plArg ) );
    }
    else
    {
        DbgLog((
            LOG_ERROR | LOG_TRACE,
            0,
            _T( "CXCodeProxyPluginIFace::GetFilterCaps: failed to get Bitrate. Error 0x%X" ),
            hResult ));
    }

    return hResult;

}
STDMETHODIMP CXCodeProxyPluginIFace::GetFilters         (ULONG *plArg)
{
	DWORD dwReturned = 0;
	HRESULT hResult = m_piKsPropertySet->Get(
                                            XC2_CAP_VIDEO_FILTERS,
											0,
											plArg,
                                            sizeof( *plArg ),
                                            plArg,
                                            sizeof( *plArg ),
                                            &dwReturned 
											);

    if( SUCCEEDED( hResult ) )
    {
        ASSERT( dwReturned == sizeof( *plArg ) );
    }
    else
    {
        DbgLog((
            LOG_ERROR | LOG_TRACE,
            0,
            _T( "CXCodeProxyPluginIFace::GetFilters: failed to get Bitrate. Error 0x%X" ),
            hResult ));
    }

    return hResult;

}

STDMETHODIMP CXCodeProxyPluginIFace::SetFilters         (ULONG ulValue)
{
    HRESULT hResult = m_piKsPropertySet->Set(
                                            XC2_CAP_VIDEO_FILTERS,
                                            0,
                                            NULL,
                                            0,
                                            &ulValue,
                                            sizeof( ulValue ) );
    if( FAILED( hResult ) )
    {
        DbgLog((
            LOG_ERROR | LOG_TRACE,
            0,
            _T( "XCodeProxyPluginIFace::SetFilters: failed to set the Video Type to %ld. Error 0x%X" ),
            ulValue,
            hResult ));
    }

    return hResult;

}

///////////////////////////////////////////////////////////////////////////////////////
	
STDMETHODIMP CXCodeProxyPluginIFace::SetVideoType       (long lArg)
{
    HRESULT hResult = m_piKsPropertySet->Set(
                                            XC2_CAP_VIDEO_TYPE,
                                            0,
                                            NULL,
                                            0,
                                            &lArg,
                                            sizeof( lArg ) );
    if( FAILED( hResult ) )
    {
        DbgLog((
            LOG_ERROR | LOG_TRACE,
            0,
            _T( "XCodeProxyPluginIFace::SetVideoType: failed to set the Video Type to %ld. Error 0x%X" ),
            lArg,
            hResult ));
    }

    return hResult;
}
STDMETHODIMP CXCodeProxyPluginIFace::SetBitrateMode         (long lArg)
{
    HRESULT hResult = m_piKsPropertySet->Set(
                                            XC2_CAP_VIDEO_BITRATE_MODE,
                                            0,
                                            NULL,
                                            0,
                                            &lArg,
                                            sizeof( lArg ) 
											);
    if( FAILED( hResult ) )
    {
        DbgLog((
            LOG_ERROR | LOG_TRACE,
            0,
            _T( "XCodeProxyPluginIFace::SetBitrateMode: failed to set the Bitrate to %ld. Error 0x%X" ),
            lArg,
            hResult ));
    }

    return hResult;
}

STDMETHODIMP CXCodeProxyPluginIFace::SetBitrate         (long lArg)
{
    HRESULT hResult = m_piKsPropertySet->Set(
                                            XC2_CAP_VIDEO_BITRATE,
                                            0,
                                            NULL,
                                            0,
                                            &lArg,
                                            sizeof( lArg ) 
											);
    if( FAILED( hResult ) )
    {
        DbgLog((
            LOG_ERROR | LOG_TRACE,
            0,
            _T( "XCodeProxyPluginIFace::SetBitrate: failed to set the Bitrate to %ld. Error 0x%X" ),
            lArg,
            hResult ));
    }

    return hResult;
}

STDMETHODIMP CXCodeProxyPluginIFace::SetPeakBitrate     (long lArg)
{
    HRESULT hResult = m_piKsPropertySet->Set(
                                            XC2_CAP_VIDEO_PEAK_BITRATE,
                                            0,
                                            NULL,
                                            0,
                                            &lArg,
                                            sizeof( lArg ) 
											);
    if( FAILED( hResult ) )
    {
        DbgLog((
            LOG_ERROR | LOG_TRACE,
            0,
            _T( "XCodeProxyPluginIFace::SetPeakBitrate: failed to set the Peak Bitrate to %ld. Error 0x%X" ),
            lArg,
            hResult ));
    }

    return hResult;
}

STDMETHODIMP CXCodeProxyPluginIFace::GetTSMode(long *plArg)
{

	DWORD dwReturned = 0;
	HRESULT hResult = m_piKsPropertySet->Get(
                                            XC2_CAP_TIMESTAMP_MODE,
											0,
											plArg,
                                            sizeof( *plArg ),
                                            plArg,
                                            sizeof( *plArg ),
                                            &dwReturned 
											);

    if( SUCCEEDED( hResult ) )
    {
        ASSERT( dwReturned == sizeof( *plArg ) );
    }
    else
    {
        DbgLog((
            LOG_ERROR | LOG_TRACE,
            0,
            _T( "CXCodeProxyPluginIFace::GetTSMode: failed to get Bitrate. Error 0x%X" ),
            hResult ));
    }

    return hResult;
}
	

STDMETHODIMP CXCodeProxyPluginIFace::SetTimeStampMode   (long lArg)
{
	
	//MessageBox(NULL, "TS Mode set: Property not there in the driver !", "XC2 Error", 0);
#if 1
	HRESULT hResult = m_piKsPropertySet->Set(
                                            XC2_CAP_TIMESTAMP_MODE,
                                            0,
                                            NULL,
                                            0,
                                            &lArg,
                                            sizeof( lArg ) 
											);
    if( FAILED( hResult ) )
    {
        DbgLog((
            LOG_ERROR | LOG_TRACE,
            0,
            _T( "XCodeProxyPluginIFace::SetTimeStampMode: failed to set the Peak Bitrate to %ld. Error 0x%X" ),
            lArg,
            hResult ));
    }

    return hResult;
#else

	return S_OK;

#endif
}

STDMETHODIMP CXCodeProxyPluginIFace::SetInitTimeStamp   (ULONGLONG lArg)
{

	HRESULT hResult = m_piKsPropertySet->Set(
                                            XC2_CAP_INIT_TIMESTAMP,
                                            0,
                                            NULL,
                                            0,
                                            &lArg,
                                            sizeof( ULONGLONG ) 
											);
    if( FAILED( hResult ) )
    {
        DbgLog((
            LOG_ERROR | LOG_TRACE,
            0,
            _T( "XCodeProxyPluginIFace::SetInitTimeStamp: failed to set the Initial Timestamp to %ld. Error 0x%X" ),
            lArg,
            hResult ));
    }

    return hResult;
}

STDMETHODIMP CXCodeProxyPluginIFace::GetInitTimeStamp(ULONGLONG *plArg)
{

	DWORD dwReturned = 0;
	HRESULT hResult = m_piKsPropertySet->Get(
                                            XC2_CAP_INIT_TIMESTAMP,
											0,
											plArg,
                                            sizeof( *plArg ),
                                            plArg,
                                            sizeof( *plArg  ),
                                            &dwReturned 
											);

    if( SUCCEEDED( hResult ) )
    {
        ASSERT( dwReturned == sizeof( *plArg  ) );
    }
    else
    {
        DbgLog((
            LOG_ERROR | LOG_TRACE,
            0,
            _T( "CXCodeProxyPluginIFace::GetInitTimeStamp: failed to get Bitrate. Error 0x%X" ),
            hResult ));
    }

    return hResult;
}


////////////////////////////////////////////////////////////////////////////////////////////////////|
////////////////////////////////////////////////////////////////////////////////////////////////////|
//#############################@@@@   Properties added for Encoder @@@@#############################|
////////////////////////////////////////////////////////////////////////////////////////////////////|


STDMETHODIMP CXCodeProxyPluginIFace::GetVideoFiltering  (long *plVideoFilter)
{
	DWORD dwReturned = 0;
	HRESULT hResult = m_piKsPropertySet->Get(
                                            XC2_CAP_VIDEO_FILTERING,
											0,
											plVideoFilter,
                                            sizeof( *plVideoFilter ),
                                            plVideoFilter,
                                            sizeof( *plVideoFilter ),
                                            &dwReturned );

    if( SUCCEEDED( hResult ) )
    {
        ASSERT( dwReturned == sizeof( *plVideoFilter ) );
    }
    else
    {
        DbgLog((
            LOG_ERROR | LOG_TRACE,
            0,
            _T( "CXCodeProxyPluginIFace::GetVideoFiltering: failed to get format. Error 0x%X" ),
            hResult ));
    }

    return hResult;
}

STDMETHODIMP CXCodeProxyPluginIFace::GetClosedGOP       (long *plClosedGOP)
{
#if 1 // Doesn't exist in the driver
	DWORD dwReturned = 0;
	HRESULT hResult = m_piKsPropertySet->Get(
                                            XC2_CAP_CLOSED_GOP,
											0,
											plClosedGOP,
                                            sizeof( *plClosedGOP ),
                                            plClosedGOP,
                                            sizeof( *plClosedGOP ),
                                            &dwReturned );

    if( SUCCEEDED( hResult ) )
    {
        ASSERT( dwReturned == sizeof( *plClosedGOP ) );
    }
    else
    {
        DbgLog((
            LOG_ERROR | LOG_TRACE,
            0,
			_T( "CXCodeProxyPluginIFace::GetClosedGOP: failed to get format. Error 0x%X" ),
            hResult ));
    }

    return hResult;
#else
	return S_OK;
#endif
}

STDMETHODIMP CXCodeProxyPluginIFace::GetTBC             (long *plTBC)
{
	DWORD dwReturned = 0;
	HRESULT hResult = m_piKsPropertySet->Get(
                                            XC2_CAP_TBC,
											0,
											plTBC,
                                            sizeof( *plTBC ),
                                            plTBC,
                                            sizeof( *plTBC ),
                                            &dwReturned );

    if( SUCCEEDED( hResult ) )
    {
        ASSERT( dwReturned == sizeof( *plTBC ) );
    }
    else
    {
        DbgLog((
            LOG_ERROR | LOG_TRACE,
            0,
            _T( "CXCodeProxyPluginIFace::GetTBC: failed to get format. Error 0x%X" ),
            hResult ));
    }

    return hResult;
}

STDMETHODIMP CXCodeProxyPluginIFace::GetInverseTelecine (long *plITelecine)
{
	DWORD dwReturned = 0;
	HRESULT hResult = m_piKsPropertySet->Get(
                                            XC2_CAP_INVERSE_TELECINE,
											0,
											plITelecine,
                                            sizeof( *plITelecine ),
                                            plITelecine,
                                            sizeof( *plITelecine ),
                                            &dwReturned );

    if( SUCCEEDED( hResult ) )
    {
        ASSERT( dwReturned == sizeof( *plITelecine ) );
    }
    else
    {
        DbgLog((
            LOG_ERROR | LOG_TRACE,
            0,
            _T( "CXCodeProxyPluginIFace::GetInverseTelecine: failed to get format. Error 0x%X" ),
            hResult ));
    }

    return hResult;
}

STDMETHODIMP CXCodeProxyPluginIFace::GetTVStandard      (long *plTVStd)
{
	DWORD dwReturned = 0;
	HRESULT hResult = m_piKsPropertySet->Get(
                                            XC2_CAP_SRC_TV_STANDARD,
											0,
											plTVStd,
                                            sizeof( *plTVStd ),
                                            plTVStd,
                                            sizeof( *plTVStd ),
                                            &dwReturned );

    if( SUCCEEDED( hResult ) )
    {
        ASSERT( dwReturned == sizeof( *plTVStd ) );
    }
    else
    {
        DbgLog((
            LOG_ERROR | LOG_TRACE,
            0,
            _T( "CXCodeProxyPluginIFace::GetTVStandard: failed to get format. Error 0x%X" ),
            hResult ));
    }

    return hResult;
}

STDMETHODIMP CXCodeProxyPluginIFace::GetFieldOrder      (long *plFieldOrder)
{
	DWORD dwReturned = 0;
	HRESULT hResult = m_piKsPropertySet->Get(
                                            XC2_CAP_VIDEO_FIELD_ORDER,
											0,
											plFieldOrder,
                                            sizeof( *plFieldOrder ),
                                            plFieldOrder,
                                            sizeof( *plFieldOrder ),
                                            &dwReturned );

    if( SUCCEEDED( hResult ) )
    {
        ASSERT( dwReturned == sizeof( *plFieldOrder ) );
    }
    else
    {
        DbgLog((
            LOG_ERROR | LOG_TRACE,
            0,
            _T( "CXCodeProxyPluginIFace::GetFieldOrder: failed to get format. Error 0x%X" ),
            hResult ));
    }

    return hResult;
}

STDMETHODIMP CXCodeProxyPluginIFace::SetVideoFiltering  (long lValue)
{
    HRESULT hResult = m_piKsPropertySet->Set(
                                            XC2_CAP_VIDEO_FILTERING,
                                            0,
                                            NULL,
                                            0,
                                            &lValue,
                                            sizeof( lValue ) );
    if( FAILED( hResult ) )
    {
        DbgLog((
            LOG_ERROR | LOG_TRACE,
            0,
            _T( "XCodeProxyPluginIFace::SetVideoFiltering: failed to set the width to %ld. Error 0x%X" ),
            lValue,
            hResult ));
    }

    return hResult;
}

STDMETHODIMP CXCodeProxyPluginIFace::SetClosedGOP       (long lValue)
{
    HRESULT hResult = m_piKsPropertySet->Set(
                                            XC2_CAP_CLOSED_GOP,
                                            0,
                                            NULL,
                                            0,
                                            &lValue,
                                            sizeof( lValue ) );
    if( FAILED( hResult ) )
    {
        DbgLog((
            LOG_ERROR | LOG_TRACE,
            0,
            _T( "XCodeProxyPluginIFace::SetClosedGOP: failed to set the width to %ld. Error 0x%X" ),
            lValue,
            hResult ));
    }

    return hResult;
}

STDMETHODIMP CXCodeProxyPluginIFace::SetTBC             (long lValue)
{
    HRESULT hResult = m_piKsPropertySet->Set(
                                            XC2_CAP_TBC,
                                            0,
                                            NULL,
                                            0,
                                            &lValue,
                                            sizeof( lValue ) );
    if( FAILED( hResult ) )
    {
        DbgLog((
            LOG_ERROR | LOG_TRACE,
            0,
            _T( "XCodeProxyPluginIFace::SetTBC: failed to set the width to %ld. Error 0x%X" ),
            lValue,
            hResult ));
    }

    return hResult;
}

STDMETHODIMP CXCodeProxyPluginIFace::SetInverseTelecine (long lValue)
{
    HRESULT hResult = m_piKsPropertySet->Set(
                                            XC2_CAP_INVERSE_TELECINE,
                                            0,
                                            NULL,
                                            0,
                                            &lValue,
                                            sizeof( lValue ) );
    if( FAILED( hResult ) )
    {
        DbgLog((
            LOG_ERROR | LOG_TRACE,
            0,
            _T( "XCodeProxyPluginIFace::SetInverseTelecine: failed to set the width to %ld. Error 0x%X" ),
            lValue,
            hResult ));
    }

    return hResult;
}

STDMETHODIMP CXCodeProxyPluginIFace::SetTVStandard      (long lValue)
{
    HRESULT hResult = m_piKsPropertySet->Set(
                                            XC2_CAP_SRC_TV_STANDARD,
                                            0,
                                            NULL,
                                            0,
                                            &lValue,
                                            sizeof( lValue ) );
    if( FAILED( hResult ) )
    {
        DbgLog((
            LOG_ERROR | LOG_TRACE,
            0,
            _T( "XCodeProxyPluginIFace::SetTVStandard: failed to set the width to %ld. Error 0x%X" ),
            lValue,
            hResult ));
    }

    return hResult;
}

STDMETHODIMP CXCodeProxyPluginIFace::SetFieldOrder      (long lValue)
{
    HRESULT hResult = m_piKsPropertySet->Set(
                                            XC2_CAP_VIDEO_FIELD_ORDER,
                                            0,
                                            NULL,
                                            0,
                                            &lValue,
                                            sizeof( lValue ) );
    if( FAILED( hResult ) )
    {
        DbgLog((
            LOG_ERROR | LOG_TRACE,
            0,
            _T( "XCodeProxyPluginIFace::SetFieldOrder: failed to set the width to %ld. Error 0x%X" ),
            lValue,
            hResult ));
    }

    return hResult;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////  
//////////////   Audio Functions
//////////////


STDMETHODIMP CXCodeProxyPluginIFace::GetAudioType       (long *plVar)
{
	DWORD dwReturned = 0;
	HRESULT hResult = m_piKsPropertySet->Get(
                                            XC2_CAP_AUDIO_TYPE,
											0,
											plVar,
                                            sizeof( *plVar ),
                                            plVar,
                                            sizeof( *plVar ),
                                            &dwReturned );

    if( SUCCEEDED( hResult ) )
    {
        ASSERT( dwReturned == sizeof( *plVar ) );
    }
    else
    {
        DbgLog((
            LOG_ERROR | LOG_TRACE,
            0,
            _T( "CXCodeProxyPluginIFace::GetAudioType: failed to get format. Error 0x%X" ),
            hResult ));
    }

    return hResult;
}


STDMETHODIMP CXCodeProxyPluginIFace::GetInputAudioType       (long *plVar)
{
	DWORD dwReturned = 0;
	HRESULT hResult = m_piKsPropertySet->Get(
                                            XC2_CAP_INPUT_AUDIO_TYPE,
											0,
											plVar,
                                            sizeof( *plVar ),
                                            plVar,
                                            sizeof( *plVar ),
                                            &dwReturned );

    if( SUCCEEDED( hResult ) )
    {
        ASSERT( dwReturned == sizeof( *plVar ) );
    }
    else
    {
        DbgLog((
            LOG_ERROR | LOG_TRACE,
            0,
            _T( "CXCodeProxyPluginIFace::GetInputAudioType: failed to get audio type. Error 0x%X" ),
            hResult ));
    }

    return hResult;
}


STDMETHODIMP CXCodeProxyPluginIFace::GetAudioBRate      (long *plVar)
{
	DWORD dwReturned = 0;
	HRESULT hResult = m_piKsPropertySet->Get(
                                            XC2_CAP_AUDIO_BRATE,
											0,
											plVar,
                                            sizeof( *plVar ),
                                            plVar,
                                            sizeof( *plVar ),
                                            &dwReturned );

    if( SUCCEEDED( hResult ) )
    {
        ASSERT( dwReturned == sizeof( *plVar ) );
    }
    else
    {
        DbgLog((
            LOG_ERROR | LOG_TRACE,
            0,
            _T( "CXCodeProxyPluginIFace::GetAudioBRate: failed to get format. Error 0x%X" ),
            hResult ));
    }

    return hResult;
}

STDMETHODIMP CXCodeProxyPluginIFace::GetAudioSRate      (long *plVar)
{
	DWORD dwReturned = 0;
	HRESULT hResult = m_piKsPropertySet->Get(
                                            XC2_CAP_AUDIO_SRATE,
											0,
											plVar,
                                            sizeof( *plVar ),
                                            plVar,
                                            sizeof( *plVar ),
                                            &dwReturned );

    if( SUCCEEDED( hResult ) )
    {
        ASSERT( dwReturned == sizeof( *plVar ) );
    }
    else
    {
        DbgLog((
            LOG_ERROR | LOG_TRACE,
            0,
            _T( "CXCodeProxyPluginIFace::GetAudioSRate: failed to get format. Error 0x%X" ),
            hResult ));
    }

    return hResult;
}

STDMETHODIMP CXCodeProxyPluginIFace::GetInputAudioSRate      (long *plVar)
{
	DWORD dwReturned = 0;
	HRESULT hResult = m_piKsPropertySet->Get(
                                            XC2_CAP_AUDIO_INPUT_SRATE,
											0,
											plVar,
                                            sizeof( *plVar ),
                                            plVar,
                                            sizeof( *plVar ),
                                            &dwReturned );

    if( SUCCEEDED( hResult ) )
    {
        ASSERT( dwReturned == sizeof( *plVar ) );
    }
    else
    {
        DbgLog((
            LOG_ERROR | LOG_TRACE,
            0,
            _T( "CXCodeProxyPluginIFace::GetInputAudioSRate: failed to get format. Error 0x%X" ),
            hResult ));
    }

    return hResult;
}


STDMETHODIMP CXCodeProxyPluginIFace::GetAudioChannels   (long *plVar)
{
	DWORD dwReturned = 0;
	HRESULT hResult = m_piKsPropertySet->Get(
                                            XC2_CAP_AUDIO_CHANNELS,
											0,
											plVar,
                                            sizeof( *plVar ),
                                            plVar,
                                            sizeof( *plVar ),
                                            &dwReturned );

    if( SUCCEEDED( hResult ) )
    {
        ASSERT( dwReturned == sizeof( *plVar ) );
    }
    else
    {
        DbgLog((
            LOG_ERROR | LOG_TRACE,
            0,
            _T( "CXCodeProxyPluginIFace::GetAudioChannels: failed to get format. Error 0x%X" ),
            hResult ));
    }

    return hResult;
}

STDMETHODIMP CXCodeProxyPluginIFace::GetAudioFrameCRC   (long *plVar)
{
	DWORD dwReturned = 0;
	HRESULT hResult = m_piKsPropertySet->Get(
                                            XC2_CAP_AUDIO_FRAME_CRC,
											0,
											plVar,
                                            sizeof( *plVar ),
                                            plVar,
                                            sizeof( *plVar ),
                                            &dwReturned );

    if( SUCCEEDED( hResult ) )
    {
        ASSERT( dwReturned == sizeof( *plVar ) );
    }
    else
    {
        DbgLog((
            LOG_ERROR | LOG_TRACE,
            0,
            _T( "CXCodeProxyPluginIFace::GetAudioFrameCRC: failed to get format. Error 0x%X" ),
            hResult ));
    }

    return hResult;
}
////////////////////////////////////////////////////////////////////////////////////////////////
///////////\\\\\\\\\\\\\\\\\\\\\\\//////////////////////////||\\\\\\\\\\\\\\\\\\\\\|/////////////
STDMETHODIMP CXCodeProxyPluginIFace::SetAudioType       (long lValue)
{
    HRESULT hResult = m_piKsPropertySet->Set(
                                            XC2_CAP_AUDIO_TYPE,
                                            0,
                                            NULL,
                                            0,
                                            &lValue,
                                            sizeof( lValue ) );
    if( FAILED( hResult ) )
    {
        DbgLog((
            LOG_ERROR | LOG_TRACE,
            0,
            _T( "XCodeProxyPluginIFace::SetAudioType: failed to set the width to %ld. Error 0x%X" ),
            lValue,
            hResult ));
    }

    return hResult;
}

STDMETHODIMP CXCodeProxyPluginIFace::SetInputAudioType       (long lValue)
{
    HRESULT hResult = m_piKsPropertySet->Set(
                                            XC2_CAP_INPUT_AUDIO_TYPE,
                                            0,
                                            NULL,
                                            0,
                                            &lValue,
                                            sizeof( lValue ) );
    if( FAILED( hResult ) )
    {
        DbgLog((
            LOG_ERROR | LOG_TRACE,
            0,
            _T( "XCodeProxyPluginIFace::SetInputAudioType: failed to set the width to %ld. Error 0x%X" ),
            lValue,
            hResult ));
    }

    return hResult;
}


////////////////////////////////////////////////////////////////////////////////////////////////////

STDMETHODIMP CXCodeProxyPluginIFace::SetAudioBRate      (long lValue)
{
    HRESULT hResult = m_piKsPropertySet->Set(
                                            XC2_CAP_AUDIO_BRATE,
                                            0,
                                            NULL,
                                            0,
                                            &lValue,
                                            sizeof( lValue ) );
    if( FAILED( hResult ) )
    {
        DbgLog((
            LOG_ERROR | LOG_TRACE,
            0,
            _T( "XCodeProxyPluginIFace::SetAudioBRate: failed to set the width to %ld. Error 0x%X" ),
            lValue,
            hResult ));
    }

    return hResult;
}
////////////////////////////////////////////////////////////////////////////////////////////////////

STDMETHODIMP CXCodeProxyPluginIFace::SetAudioSRate      (long lValue)
{
    HRESULT hResult = m_piKsPropertySet->Set(
                                            XC2_CAP_AUDIO_SRATE,
                                            0,
                                            NULL,
                                            0,
                                            &lValue,
                                            sizeof( lValue ) );
    if( FAILED( hResult ) )
    {
        DbgLog((
            LOG_ERROR | LOG_TRACE,
            0,
            _T( "XCodeProxyPluginIFace::SetAudioSRate: failed to set the width to %ld. Error 0x%X" ),
            lValue,
            hResult ));
    }

    return hResult;
}

STDMETHODIMP CXCodeProxyPluginIFace::SetInputAudioSRate      (long lValue)
{
    HRESULT hResult = m_piKsPropertySet->Set(
                                            XC2_CAP_AUDIO_INPUT_SRATE,
                                            0,
                                            NULL,
                                            0,
                                            &lValue,
                                            sizeof( lValue ) );
    if( FAILED( hResult ) )
    {
        DbgLog((
            LOG_ERROR | LOG_TRACE,
            0,
            _T( "XCodeProxyPluginIFace::SetAudioSRate: failed to set the width to %ld. Error 0x%X" ),
            lValue,
            hResult ));
    }

    return hResult;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

STDMETHODIMP CXCodeProxyPluginIFace::SetAudioChannels   (long lValue)
{
    HRESULT hResult = m_piKsPropertySet->Set(
                                            XC2_CAP_AUDIO_CHANNELS,
                                            0,
                                            NULL,
                                            0,
                                            &lValue,
                                            sizeof( lValue ) );
    if( FAILED( hResult ) )
    {
        DbgLog((
            LOG_ERROR | LOG_TRACE,
            0,
            _T( "XCodeProxyPluginIFace::SetAudioChannels: failed to set the width to %ld. Error 0x%X" ),
            lValue,
            hResult ));
    }

    return hResult;
}
////////////////////////////////////////////////////////////////////////////////////////////////////

STDMETHODIMP CXCodeProxyPluginIFace::SetAudioFrameCRC   (long lValue)
{
    HRESULT hResult = m_piKsPropertySet->Set(
                                            XC2_CAP_AUDIO_FRAME_CRC,
                                            0,
                                            NULL,
                                            0,
                                            &lValue,
                                            sizeof( lValue ) );
    if( FAILED( hResult ) )
    {
        DbgLog((
            LOG_ERROR | LOG_TRACE,
            0,
            _T( "XCodeProxyPluginIFace::SetAudioFrameCRC: failed to set the width to %ld. Error 0x%X" ),
            lValue,
            hResult ));
    }

    return hResult;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////// PIDs ////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

// For Transcoder
//#define STATIC_XC2_TRANSCODER_PLUGIN_PAGE \
//0xfbb43b29, 0x4904, 0x4910, 0x92, 0x46, 0xe9, 0x9, 0x93, 0x9, 0xa8, 0x7a
DEFINE_GUIDSTRUCT( "0009CB79-61D8-418f-9CBE-143A6B503825", DUMMY_GUID_AUDIO_IN_PID );
#define DUMMY_GUID_AUDIO_IN_PID DEFINE_GUIDNAMED( DUMMY_GUID_AUDIO_IN_PID )

DEFINE_GUIDSTRUCT( "918C8DC4-CD9F-47d4-A5C3-51A8E68DB3FA", DUMMY_GUID_AUDIO_OUT_PID );
#define DUMMY_GUID_AUDIO_OUT_PID DEFINE_GUIDNAMED( DUMMY_GUID_AUDIO_OUT_PID )

DEFINE_GUIDSTRUCT( "C1E823EE-7ECF-4763-BC99-450D91F2C15A", DUMMY_GUID_VIDEO_IN_PID );
#define DUMMY_GUID_VIDEO_IN_PID DEFINE_GUIDNAMED( DUMMY_GUID_VIDEO_IN_PID )

DEFINE_GUIDSTRUCT( "708B8A21-3C2C-4d44-A6B5-E2A219E7808C", DUMMY_GUID_VIDEO_OUT_PID );
#define DUMMY_GUID_VIDEO_OUT_PID DEFINE_GUIDNAMED( DUMMY_GUID_VIDEO_OUT_PID )


/*
// CLSID_WAVEFORMATEX_SUBTYPE
DEFINE_GUID(CLSID_WAVEFORMATEX_SUBTYPE,
0x00010001, 0x0001, 0x0018, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
708B8A21-3C2C-4d44-A6B5-E2A219E7808C
*/



STDMETHODIMP CXCodeProxyPluginIFace::GetAudioInPID      (long *plVar)
{
	DWORD dwReturned = 0;
	HRESULT hResult = m_piKsPropertySet->Get(
                                            XC2_CAP_AUDIOIN_PID,
											0,
											plVar,
                                            sizeof( *plVar ),
                                            plVar,
                                            sizeof( *plVar ),
                                            &dwReturned );

    if( SUCCEEDED( hResult ) )
    {
        ASSERT( dwReturned == sizeof( *plVar ) );
    }
    else
    {
        DbgLog((
            LOG_ERROR | LOG_TRACE,
            0,
            _T( "CXCodeProxyPluginIFace::GetAudioInPID: failed to get format. Error 0x%X" ),
            hResult ));
    }

    return hResult;
}

STDMETHODIMP CXCodeProxyPluginIFace::GetVideoInPID      (long *plVar)
{
	DWORD dwReturned = 0;
	HRESULT hResult = m_piKsPropertySet->Get(
                                            XC2_CAP_VIDEOIN_PID,
											0,
											plVar,
                                            sizeof( *plVar ),
                                            plVar,
                                            sizeof( *plVar ),
                                            &dwReturned );

    if( SUCCEEDED( hResult ) )
    {
        ASSERT( dwReturned == sizeof( *plVar ) );
    }
    else
    {
        DbgLog((
            LOG_ERROR | LOG_TRACE,
            0,
            _T( "CXCodeProxyPluginIFace::GetVideoInPID: failed to get format. Error 0x%X" ),
            hResult ));
    }

    return hResult;
}

STDMETHODIMP CXCodeProxyPluginIFace::GetAudioOutPID     (long *plVar)
{
	DWORD dwReturned = 0;
	HRESULT hResult = m_piKsPropertySet->Get(
                                            XC2_CAP_AUDIOOUT_PID,
											0,
											plVar,
                                            sizeof( *plVar ),
                                            plVar,
                                            sizeof( *plVar ),
                                            &dwReturned );

    if( SUCCEEDED( hResult ) )
    {
        ASSERT( dwReturned == sizeof( *plVar ) );
    }
    else
    {
        DbgLog((
            LOG_ERROR | LOG_TRACE,
            0,
            _T( "CXCodeProxyPluginIFace::GetAudioOutPID: failed to get format. Error 0x%X" ),
            hResult ));
    }

    return hResult;
}

STDMETHODIMP CXCodeProxyPluginIFace::GetVideoOutPID     (long *plVar)
{
	DWORD dwReturned = 0;
	HRESULT hResult = m_piKsPropertySet->Get(
                                            XC2_CAP_VIDEOOUT_PID,
											0,
											plVar,
                                            sizeof( *plVar ),
                                            plVar,
                                            sizeof( *plVar ),
                                            &dwReturned );

    if( SUCCEEDED( hResult ) )
    {
        ASSERT( dwReturned == sizeof( *plVar ) );
    }
    else
    {
        DbgLog((
            LOG_ERROR | LOG_TRACE,
            0,
            _T( "CXCodeProxyPluginIFace::GetVideoOutPID: failed to get format. Error 0x%X" ),
            hResult ));
    }

    return hResult;
}



STDMETHODIMP CXCodeProxyPluginIFace::SetAudioInPID      (long lValue)
{
    HRESULT hResult = m_piKsPropertySet->Set(
                                            XC2_CAP_AUDIOIN_PID,
                                            0,
                                            NULL,
                                            0,
                                            &lValue,
                                            sizeof( lValue ) );
    if( FAILED( hResult ) )
    {
        DbgLog((
            LOG_ERROR | LOG_TRACE,
            0,
            _T( "XCodeProxyPluginIFace::SetAudioInPID: failed to set the width to %ld. Error 0x%X" ),
            lValue,
            hResult ));
    }

    return hResult;
}

STDMETHODIMP CXCodeProxyPluginIFace::SetVideoInPID      (long lValue)
{
    HRESULT hResult = m_piKsPropertySet->Set(
                                            XC2_CAP_VIDEOIN_PID,
                                            0,
                                            NULL,
                                            0,
                                            &lValue,
                                            sizeof( lValue ) );
    if( FAILED( hResult ) )
    {
        DbgLog((
            LOG_ERROR | LOG_TRACE,
            0,
            _T( "XCodeProxyPluginIFace::SetVideoInPID: failed to set the width to %ld. Error 0x%X" ),
            lValue,
            hResult ));
    }

    return hResult;
}

STDMETHODIMP CXCodeProxyPluginIFace::SetAudioOutPID     (long lValue)
{
    HRESULT hResult = m_piKsPropertySet->Set(
                                            XC2_CAP_AUDIOOUT_PID,
                                            0,
                                            NULL,
                                            0,
                                            &lValue,
                                            sizeof( lValue ) );
    if( FAILED( hResult ) )
    {
        DbgLog((
            LOG_ERROR | LOG_TRACE,
            0,
            _T( "XCodeProxyPluginIFace::SetAudioOutPID: failed to set the width to %ld. Error 0x%X" ),
            lValue,
            hResult ));
    }

    return hResult;
}

STDMETHODIMP CXCodeProxyPluginIFace::SetVideoOutPID     (long lValue)
{
    HRESULT hResult = m_piKsPropertySet->Set(
                                            XC2_CAP_VIDEOOUT_PID,
                                            0,
                                            NULL,
                                            0,
                                            &lValue,
                                            sizeof( lValue ) );
    if( FAILED( hResult ) )
    {
        DbgLog((
            LOG_ERROR | LOG_TRACE,
            0,
            _T( "XCodeProxyPluginIFace::SetVideoOutPID: failed to set the width to %ld. Error 0x%X" ),
            lValue,
            hResult ));
    }

    return hResult;
}

STDMETHODIMP CXCodeProxyPluginIFace::GetGOPnB     (long * plVar)
{
  	DWORD dwReturned = 0;
	HRESULT hResult = m_piKsPropertySet->Get(
                                            XC_CAP_GOP_N_B,
											0,
											plVar,
                                            sizeof( *plVar ),
                                            plVar,
                                            sizeof( *plVar ),
                                            &dwReturned );
    if( FAILED( hResult ) )
    {
        DbgLog((
            LOG_ERROR | LOG_TRACE,
            0,
            _T( "XCodeProxyPluginIFace::GetGOPnB: failed " )));
    }

    return hResult;
}

STDMETHODIMP CXCodeProxyPluginIFace::SetGOPnB     (long lValue)
{
    HRESULT hResult = m_piKsPropertySet->Set(
                                            XC_CAP_GOP_N_B,
                                            0,
                                            NULL,
                                            0,
                                            &lValue,
                                            sizeof( lValue ) );
    if( FAILED( hResult ) )
    {
        DbgLog((
            LOG_ERROR | LOG_TRACE,
            0,
            _T( "XCodeProxyPluginIFace::SetGOPnB: failed " )));
    }

    return hResult;
}

STDMETHODIMP CXCodeProxyPluginIFace::GetGOPnP     (long * plVar)
{
  	DWORD dwReturned = 0;
	HRESULT hResult = m_piKsPropertySet->Get(
                                            XC_CAP_GOP_N_P,
											0,
											plVar,
                                            sizeof( *plVar ),
                                            plVar,
                                            sizeof( *plVar ),
                                            &dwReturned );
    if( FAILED( hResult ) )
    {
        DbgLog((
            LOG_ERROR | LOG_TRACE,
            0,
            _T( "XCodeProxyPluginIFace::GetGOPnP: failed " )));
    }

    return hResult;
}

STDMETHODIMP CXCodeProxyPluginIFace::SetGOPnP     (long lValue)
{
    HRESULT hResult = m_piKsPropertySet->Set(
                                            XC_CAP_GOP_N_P,
                                            0,
                                            NULL,
                                            0,
                                            &lValue,
                                            sizeof( lValue ) );
    if( FAILED( hResult ) )
    {
        DbgLog((
            LOG_ERROR | LOG_TRACE,
            0,
            _T( "XCodeProxyPluginIFace::SetGOPnP: failed " )));
    }

    return hResult;
}


STDMETHODIMP CXCodeProxyPluginIFace::GetQuantType     (long * plVar)
{
  	DWORD dwReturned = 0;
	HRESULT hResult = m_piKsPropertySet->Get(
                                            XC_CAP_MPEG4_QUANT_TYPE,
											0,
											plVar,
                                            sizeof( *plVar ),
                                            plVar,
                                            sizeof( *plVar ),
                                            &dwReturned );
    if( FAILED( hResult ) )
    {
        DbgLog((
            LOG_ERROR | LOG_TRACE,
            0,
            _T( "XCodeProxyPluginIFace::GetQuantType: failed " )));
    }

    return hResult;
}

STDMETHODIMP CXCodeProxyPluginIFace::SetQuantType     (long lValue)
{
    HRESULT hResult = m_piKsPropertySet->Set(
                                            XC_CAP_MPEG4_QUANT_TYPE,
                                            0,
                                            NULL,
                                            0,
                                            &lValue,
                                            sizeof( lValue ) );
    if( FAILED( hResult ) )
    {
        DbgLog((
            LOG_ERROR | LOG_TRACE,
            0,
            _T( "XCodeProxyPluginIFace::SetQuantType: failed " )));
    }

    return hResult;
}

STDMETHODIMP CXCodeProxyPluginIFace::GetMirror     (long * plVar)
{
	DWORD dwReturned = 0;
	HRESULT hResult = m_piKsPropertySet->Get(
                                            XC_CAP_ENABLE_MIRROR,
											0,
											plVar,
                                            sizeof( *plVar ),
                                            plVar,
                                            sizeof( *plVar ),
                                            &dwReturned );
    if( FAILED( hResult ) )
    {
        DbgLog((
            LOG_ERROR | LOG_TRACE,
            0,
            _T( "XCodeProxyPluginIFace::GetMirror: failed " )));
    }
	else
	{
		ASSERT(dwReturned == sizeof(*plVar));
	}

    return hResult;
}
STDMETHODIMP CXCodeProxyPluginIFace::SetMirror     (long lValue)
{
    HRESULT hResult = m_piKsPropertySet->Set(
                                            XC_CAP_ENABLE_MIRROR,
                                            0,
                                            NULL,
                                            0,
                                            &lValue,
                                            sizeof( lValue ) );
    if( FAILED( hResult ) )
    {
        DbgLog((
            LOG_ERROR | LOG_TRACE,
            0,
            _T( "XCodeProxyPluginIFace::SetMirror: failed " )));
    }

    return hResult;
}

