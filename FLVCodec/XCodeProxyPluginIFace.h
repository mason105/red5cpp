//**********************************************************************************
// Filename: XCodeProxyPluginIFace.h
//
// ViXS Systems Confidential and Proprietary
//
//*********************************************************************************

#ifndef __XCODEPROXYPLUGINIFACE_H__
#define __XCODEPROXYPLUGINIFACE_H__

#include "XCodeiface.h"
#include "xcinfo.h"

#define L_XCODEKSPROXYPROPERTY_INTHANDLER_TEXT  L"XCode Avstream Interface Handler"
#define T_XCODEKSPROXYPROPERTY_INTHANDLER_TEXT  _T( "XCode Avstream Interface Handler" )

#define L_XCODEKSPROXYPROPERTY_INTHANDLER_TEXT_FOR_ENCODER  L"XCode Avstream Encoder Interface Handler"
#define T_XCODEKSPROXYPROPERTY_INTHANDLER_TEXT_FOR_ENCODER  _T( "XCode Avstream Encoder Interface Handler" )


class CXCodeProxyPluginIFace : public CUnknown, public IXCodeKsproxyPropertyConfig
{
public:
    // Interface handler creation routine
    static CUnknown* CALLBACK CreateInstance( LPUNKNOWN piOuterUnknown, HRESULT* phResult );

    // This exposes supported interfaces
    STDMETHODIMP NonDelegatingQueryInterface( REFIID riid, void** ppv );
    DECLARE_IUNKNOWN

private:

    IKsPropertySet* m_piKsPropertySet;  // Interface to proxy
    IKsPropertySet* m_piKsPropertyVideoInPinSet; //Video Pin Interface to proxy
    IKsPropertySet* m_piKsPropertyAudioInPinSet; //Audio Pin Interface to proxy
    IKsPropertySet* m_piKsPropertyVideoOutPinSet; //Video Pin Interface to proxy


public:

    CXCodeProxyPluginIFace( IKsPropertySet* piKsPropertySet );

	// IXCodeKsproxyPropertyConfig overriden methods:
	STDMETHODIMP GetRate            (long* plRate );
	STDMETHODIMP GetOutputWidth     (long *plWidth);
	STDMETHODIMP GetOutputHeight    (long *plHeight);
	STDMETHODIMP GetSystemFormat    (long *plStd);
	STDMETHODIMP GetPeakBitrate     (long *plPBitrate);
	STDMETHODIMP GetBitrate         (long *plBitrate);

	STDMETHODIMP GetVideoFiltering  (long *plVideoFilter);
	STDMETHODIMP GetClosedGOP       (long *plClosedGOP);
	STDMETHODIMP GetTBC             (long *plTBC);
	STDMETHODIMP GetInverseTelecine (long *plITelecine);
	STDMETHODIMP GetTVStandard      (long *plTVStd);
	STDMETHODIMP GetFieldOrder      (long *plFieldOrder);

	STDMETHODIMP GetAudioType       (long *plVar);
	STDMETHODIMP GetInputAudioType  (long *plVar); // New
	STDMETHODIMP GetAudioBRate      (long *plVar);
	STDMETHODIMP GetAudioSRate      (long *plVar);
	STDMETHODIMP GetInputAudioSRate (long *plVar); // New
	STDMETHODIMP GetAudioChannels   (long *plVar);
	STDMETHODIMP GetAudioFrameCRC   (long *plVar);

	STDMETHODIMP GetAudioInPID      (long *plVar);
	STDMETHODIMP GetVideoInPID      (long *plVar);
	STDMETHODIMP GetAudioOutPID     (long *plVar);
	STDMETHODIMP GetVideoOutPID     (long *plVar);
	STDMETHODIMP GetVideoType       (long *plArg);
	STDMETHODIMP GetTSMode          (long *plArg);
	STDMETHODIMP GetInitTimeStamp   (ULONGLONG *plArg);

	STDMETHODIMP GetFilterCaps      (ULONG *plVar);
	STDMETHODIMP GetFilters         (ULONG *plVar);


	STDMETHODIMP SetRate            (long lRate  );
	STDMETHODIMP SetOutputWidth     (long lWidth );
	STDMETHODIMP SetOutputHeight    (long lHeight);
	STDMETHODIMP SetFormat          (long lFormat);

	STDMETHODIMP SetVideoType       (long lValue);
	STDMETHODIMP SetBitrate         (long lValue);
	STDMETHODIMP SetPeakBitrate     (long lValue);

	STDMETHODIMP SetTimeStampMode   (long lValue);
	STDMETHODIMP SetInitTimeStamp   (ULONGLONG lValue);

	STDMETHODIMP SetVideoFiltering  (long lValue);
	STDMETHODIMP SetClosedGOP       (long lValue);
	STDMETHODIMP SetTBC             (long lValue);
	STDMETHODIMP SetInverseTelecine (long lValue);
	STDMETHODIMP SetTVStandard      (long lValue);
	STDMETHODIMP SetFieldOrder      (long lValue);

	STDMETHODIMP SetAudioType       (long lValue);
	STDMETHODIMP SetInputAudioType  (long lValue);
	STDMETHODIMP SetAudioBRate      (long lValue);
	STDMETHODIMP SetAudioSRate      (long lValue);
	STDMETHODIMP SetInputAudioSRate (long lValue);
	STDMETHODIMP SetAudioChannels   (long lValue);
	STDMETHODIMP SetAudioFrameCRC   (long lValue);


	STDMETHODIMP SetAudioInPID      (long lValue);
	STDMETHODIMP SetVideoInPID      (long lValue);
	STDMETHODIMP SetAudioOutPID     (long lValue);
	STDMETHODIMP SetVideoOutPID     (long lValue);

	STDMETHODIMP SetFilters         (ULONG ulValue);

    STDMETHODIMP SetAudioMiniI2SMstrMode(long lValue);
    STDMETHODIMP SetProfile(long lValue);
    STDMETHODIMP SetLevel(long lValue);
    STDMETHODIMP SetAspectRatio(long lValue);
    STDMETHODIMP SetMP4AspectRatio(long lValue);

    // IXCodeKsproxyPropertyConfig overriden methods for Pin:
    STDMETHODIMP GetMP4MdatInfo(PXCINFO_MDAT_SIZE_S lValue);
    STDMETHODIMP SetFlushMessageToDriver();
    STDMETHODIMP GetFinishFlagFromDriver(BOOL *lValue);
    STDMETHODIMP SetMirrorInfoToDriver(BOOL status);

    STDMETHODIMP GetMirrorCaps(unsigned int *lValue);

    STDMETHODIMP SetFlushYUVSendMessageToDriver();
    STDMETHODIMP SetFlushPCMSendMessageToDriver();
    STDMETHODIMP SetFlushVESSendMessageToDriver();
    STDMETHODIMP SetFlushAESSendMessageToDriver();

	STDMETHODIMP GetGOPnB(long *lValue);
	STDMETHODIMP SetGOPnB(long lValue);

	STDMETHODIMP GetBitrateMode(long *lValue);
	STDMETHODIMP SetBitrateMode(long lValue);

	STDMETHODIMP GetGOPnP(long *lValue);
	STDMETHODIMP SetGOPnP(long lValue);

	STDMETHODIMP GetQuantType(long *lValue);
	STDMETHODIMP SetQuantType(long lValue);

	STDMETHODIMP GetMirror(long *lValue);
	STDMETHODIMP SetMirror(long lValue);
};


#endif  // __XCODEPROXYPLUGINIFACE_H__
