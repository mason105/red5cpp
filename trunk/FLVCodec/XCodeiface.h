//**********************************************************************************
// Filename: XCodeiface.h
//
// ViXS Systems Confidential and Proprietary
//
//*********************************************************************************

/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 440
#endif

#ifndef __XCodeiface_h__
#define __XCodeiface_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IXCodeKsproxyPropertyConfig_FWD_DEFINED__
#define __IXCodeKsproxyPropertyConfig_FWD_DEFINED__
typedef interface IXCodeKsproxyPropertyConfig IXCodeKsproxyPropertyConfig;
#endif 	/* __IXCodeKsproxyPropertyConfig_FWD_DEFINED__ */


#ifndef __XCodeKsProxyPropertyPage_FWD_DEFINED__
#define __XCodeKsProxyPropertyPage_FWD_DEFINED__

#ifdef __cplusplus
typedef class XCodeKsProxyPropertyPage XCodeKsProxyPropertyPage;
#else
typedef struct XCodeKsProxyPropertyPage XCodeKsProxyPropertyPage;
#endif /* __cplusplus */

#endif 	/* __XCodeKsProxyPropertyPage_FWD_DEFINED__ */


#ifndef __XCodeKsProxyEncoderPage_FWD_DEFINED__
#define __XCodeKsProxyEncoderPage_FWD_DEFINED__

#ifdef __cplusplus
typedef class XCodeKsProxyEncoderPage XCodeKsProxyEncoderPage;
#else
typedef struct XCodeKsProxyEncoderPage XCodeKsProxyEncoderPage;
#endif /* __cplusplus */

#endif 	/* __XCodeKsProxyEncoderPage_FWD_DEFINED__ */


#ifndef __XCodeKsProxyAudioEncoderPage_FWD_DEFINED__
#define __XCodeKsProxyAudioEncoderPage_FWD_DEFINED__

#ifdef __cplusplus
typedef class XCodeKsProxyAudioEncoderPage XCodeKsProxyAudioEncoderPage;
#else
typedef struct XCodeKsProxyAudioEncoderPage XCodeKsProxyAudioEncoderPage;
#endif /* __cplusplus */

#endif 	/* __XCodeKsProxyAudioEncoderPage_FWD_DEFINED__ */


#ifndef __XCodeKsProxyMultiplexerPage_FWD_DEFINED__
#define __XCodeKsProxyMultiplexerPage_FWD_DEFINED__

#ifdef __cplusplus
typedef class XCodeKsProxyMultiplexerPage XCodeKsProxyMultiplexerPage;
#else
typedef struct XCodeKsProxyMultiplexerPage XCodeKsProxyMultiplexerPage;
#endif /* __cplusplus */

#endif 	/* __XCodeKsProxyMultiplexerPage_FWD_DEFINED__ */


/* header files for imported files */
#include "unknwn.h"
#include "strmif.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 


#ifndef __XCodeKsproxyProperty_LIBRARY_DEFINED__
#define __XCodeKsproxyProperty_LIBRARY_DEFINED__

/* library XCodeKsproxyProperty */
/* [control][helpstring][version][uuid] */ 


DEFINE_GUID(LIBID_XCodeKsproxyProperty,0x28C5C736,0x1867,0x4800,0xAB,0xC2,0xB9,0x87,0x02,0x84,0x66,0x9A);

#ifndef __IXCodeKsproxyPropertyConfig_INTERFACE_DEFINED__
#define __IXCodeKsproxyPropertyConfig_INTERFACE_DEFINED__

/* interface IXCodeKsproxyPropertyConfig */
/* [unique][uuid][object] */ 


DEFINE_GUID(IID_IXCodeKsproxyPropertyConfig,0xFBB43B29,0x4904,0x4910,0x92,0x46,0xE9,0x09,0x93,0x09,0xA8,0x7A);

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("FBB43B29-4904-4910-9246-E9099309A87A")
    IXCodeKsproxyPropertyConfig : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetRate( 
            /* [retval][out] */ long __RPC_FAR *plRate) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetOutputWidth( 
            /* [retval][out] */ long __RPC_FAR *plWidth) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetOutputHeight( 
            /* [retval][out] */ long __RPC_FAR *plHeight) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetSystemFormat( 
            /* [retval][out] */ long __RPC_FAR *plStd) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetPeakBitrate( 
            /* [retval][out] */ long __RPC_FAR *plBRate) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetBitrate( 
            /* [retval][out] */ long __RPC_FAR *plBRate) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetVideoType( 
            /* [retval][out] */ long __RPC_FAR *plVar) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetVideoFiltering( 
            /* [retval][out] */ long __RPC_FAR *plVideoFilter) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetClosedGOP( 
            /* [retval][out] */ long __RPC_FAR *plClosedGOP) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetTBC( 
            /* [retval][out] */ long __RPC_FAR *plTBC) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetInverseTelecine( 
            /* [retval][out] */ long __RPC_FAR *plITelecine) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetTVStandard( 
            /* [retval][out] */ long __RPC_FAR *plTVStd) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetFieldOrder( 
            /* [retval][out] */ long __RPC_FAR *plFieldOrder) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetAudioType( 
            /* [retval][out] */ long __RPC_FAR *plVar) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetInputAudioType( 
            /* [retval][out] */ long __RPC_FAR *plVar) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetAudioBRate( 
            /* [retval][out] */ long __RPC_FAR *plVar) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetAudioSRate( 
            /* [retval][out] */ long __RPC_FAR *plVar) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetInputAudioSRate( 
            /* [retval][out] */ long __RPC_FAR *plVar) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetAudioChannels( 
            /* [retval][out] */ long __RPC_FAR *plVar) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetAudioFrameCRC( 
            /* [retval][out] */ long __RPC_FAR *plVar) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetAudioOutPID( 
            /* [retval][out] */ long __RPC_FAR *plVar) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetVideoOutPID( 
            /* [retval][out] */ long __RPC_FAR *plVar) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetTSMode( 
            /* [retval][out] */ long __RPC_FAR *plVar) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetInitTimeStamp( 
            /* [retval][out] */ unsigned __int64 __RPC_FAR *plArg) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetRate( 
            /* [in] */ long lRate) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetOutputWidth( 
            /* [in] */ long lWidth) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetOutputHeight( 
            /* [in] */ long lHeight) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetFormat( 
            /* [in] */ long lFormat) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetVideoType( 
            /* [in] */ long lValue) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetBitrate( 
            /* [in] */ long lValue) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetPeakBitrate( 
            /* [in] */ long lValue) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetTimeStampMode( 
            /* [in] */ long lValue) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetInitTimeStamp( 
            /* [in] */ unsigned __int64 lValue) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetVideoFiltering( 
            /* [in] */ long lValue) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetClosedGOP( 
            /* [in] */ long lValue) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetTBC( 
            /* [in] */ long lValue) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetInverseTelecine( 
            /* [in] */ long lValue) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetTVStandard( 
            /* [in] */ long lValue) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetFieldOrder( 
            /* [in] */ long lValue) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetAudioType( 
            /* [in] */ long lValue) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetInputAudioType( 
            /* [in] */ long lValue) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetAudioBRate( 
            /* [in] */ long lValue) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetAudioSRate( 
            /* [in] */ long lValue) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetInputAudioSRate( 
            /* [in] */ long lValue) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetAudioChannels( 
            /* [in] */ long lValue) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetAudioFrameCRC( 
            /* [in] */ long lValue) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetAudioOutPID( 
            /* [in] */ long lValue) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetVideoOutPID( 
            /* [in] */ long lValue) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IXCodeKsproxyPropertyConfigVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IXCodeKsproxyPropertyConfig __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IXCodeKsproxyPropertyConfig __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IXCodeKsproxyPropertyConfig __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetRate )( 
            IXCodeKsproxyPropertyConfig __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *plRate);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetOutputWidth )( 
            IXCodeKsproxyPropertyConfig __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *plWidth);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetOutputHeight )( 
            IXCodeKsproxyPropertyConfig __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *plHeight);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetSystemFormat )( 
            IXCodeKsproxyPropertyConfig __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *plStd);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetPeakBitrate )( 
            IXCodeKsproxyPropertyConfig __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *plBRate);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetBitrate )( 
            IXCodeKsproxyPropertyConfig __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *plBRate);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetVideoType )( 
            IXCodeKsproxyPropertyConfig __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *plVar);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetVideoFiltering )( 
            IXCodeKsproxyPropertyConfig __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *plVideoFilter);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetClosedGOP )( 
            IXCodeKsproxyPropertyConfig __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *plClosedGOP);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTBC )( 
            IXCodeKsproxyPropertyConfig __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *plTBC);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetInverseTelecine )( 
            IXCodeKsproxyPropertyConfig __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *plITelecine);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTVStandard )( 
            IXCodeKsproxyPropertyConfig __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *plTVStd);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetFieldOrder )( 
            IXCodeKsproxyPropertyConfig __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *plFieldOrder);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetAudioType )( 
            IXCodeKsproxyPropertyConfig __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *plVar);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetInputAudioType )( 
            IXCodeKsproxyPropertyConfig __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *plVar);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetAudioBRate )( 
            IXCodeKsproxyPropertyConfig __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *plVar);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetAudioSRate )( 
            IXCodeKsproxyPropertyConfig __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *plVar);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetInputAudioSRate )( 
            IXCodeKsproxyPropertyConfig __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *plVar);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetAudioChannels )( 
            IXCodeKsproxyPropertyConfig __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *plVar);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetAudioFrameCRC )( 
            IXCodeKsproxyPropertyConfig __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *plVar);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetAudioOutPID )( 
            IXCodeKsproxyPropertyConfig __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *plVar);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetVideoOutPID )( 
            IXCodeKsproxyPropertyConfig __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *plVar);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTSMode )( 
            IXCodeKsproxyPropertyConfig __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *plVar);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetInitTimeStamp )( 
            IXCodeKsproxyPropertyConfig __RPC_FAR * This,
            /* [retval][out] */ unsigned __int64 __RPC_FAR *plArg);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetRate )( 
            IXCodeKsproxyPropertyConfig __RPC_FAR * This,
            /* [in] */ long lRate);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetOutputWidth )( 
            IXCodeKsproxyPropertyConfig __RPC_FAR * This,
            /* [in] */ long lWidth);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetOutputHeight )( 
            IXCodeKsproxyPropertyConfig __RPC_FAR * This,
            /* [in] */ long lHeight);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetFormat )( 
            IXCodeKsproxyPropertyConfig __RPC_FAR * This,
            /* [in] */ long lFormat);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetVideoType )( 
            IXCodeKsproxyPropertyConfig __RPC_FAR * This,
            /* [in] */ long lValue);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetBitrate )( 
            IXCodeKsproxyPropertyConfig __RPC_FAR * This,
            /* [in] */ long lValue);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetPeakBitrate )( 
            IXCodeKsproxyPropertyConfig __RPC_FAR * This,
            /* [in] */ long lValue);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetTimeStampMode )( 
            IXCodeKsproxyPropertyConfig __RPC_FAR * This,
            /* [in] */ long lValue);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetInitTimeStamp )( 
            IXCodeKsproxyPropertyConfig __RPC_FAR * This,
            /* [in] */ unsigned __int64 lValue);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetVideoFiltering )( 
            IXCodeKsproxyPropertyConfig __RPC_FAR * This,
            /* [in] */ long lValue);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetClosedGOP )( 
            IXCodeKsproxyPropertyConfig __RPC_FAR * This,
            /* [in] */ long lValue);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetTBC )( 
            IXCodeKsproxyPropertyConfig __RPC_FAR * This,
            /* [in] */ long lValue);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetInverseTelecine )( 
            IXCodeKsproxyPropertyConfig __RPC_FAR * This,
            /* [in] */ long lValue);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetTVStandard )( 
            IXCodeKsproxyPropertyConfig __RPC_FAR * This,
            /* [in] */ long lValue);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetFieldOrder )( 
            IXCodeKsproxyPropertyConfig __RPC_FAR * This,
            /* [in] */ long lValue);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetAudioType )( 
            IXCodeKsproxyPropertyConfig __RPC_FAR * This,
            /* [in] */ long lValue);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetInputAudioType )( 
            IXCodeKsproxyPropertyConfig __RPC_FAR * This,
            /* [in] */ long lValue);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetAudioBRate )( 
            IXCodeKsproxyPropertyConfig __RPC_FAR * This,
            /* [in] */ long lValue);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetAudioSRate )( 
            IXCodeKsproxyPropertyConfig __RPC_FAR * This,
            /* [in] */ long lValue);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetInputAudioSRate )( 
            IXCodeKsproxyPropertyConfig __RPC_FAR * This,
            /* [in] */ long lValue);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetAudioChannels )( 
            IXCodeKsproxyPropertyConfig __RPC_FAR * This,
            /* [in] */ long lValue);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetAudioFrameCRC )( 
            IXCodeKsproxyPropertyConfig __RPC_FAR * This,
            /* [in] */ long lValue);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetAudioOutPID )( 
            IXCodeKsproxyPropertyConfig __RPC_FAR * This,
            /* [in] */ long lValue);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetVideoOutPID )( 
            IXCodeKsproxyPropertyConfig __RPC_FAR * This,
            /* [in] */ long lValue);
        
        END_INTERFACE
    } IXCodeKsproxyPropertyConfigVtbl;

    interface IXCodeKsproxyPropertyConfig
    {
        CONST_VTBL struct IXCodeKsproxyPropertyConfigVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IXCodeKsproxyPropertyConfig_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IXCodeKsproxyPropertyConfig_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IXCodeKsproxyPropertyConfig_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IXCodeKsproxyPropertyConfig_GetRate(This,plRate)	\
    (This)->lpVtbl -> GetRate(This,plRate)

#define IXCodeKsproxyPropertyConfig_GetOutputWidth(This,plWidth)	\
    (This)->lpVtbl -> GetOutputWidth(This,plWidth)

#define IXCodeKsproxyPropertyConfig_GetOutputHeight(This,plHeight)	\
    (This)->lpVtbl -> GetOutputHeight(This,plHeight)

#define IXCodeKsproxyPropertyConfig_GetSystemFormat(This,plStd)	\
    (This)->lpVtbl -> GetSystemFormat(This,plStd)

#define IXCodeKsproxyPropertyConfig_GetPeakBitrate(This,plBRate)	\
    (This)->lpVtbl -> GetPeakBitrate(This,plBRate)

#define IXCodeKsproxyPropertyConfig_GetBitrate(This,plBRate)	\
    (This)->lpVtbl -> GetBitrate(This,plBRate)

#define IXCodeKsproxyPropertyConfig_GetVideoType(This,plVar)	\
    (This)->lpVtbl -> GetVideoType(This,plVar)

#define IXCodeKsproxyPropertyConfig_GetVideoFiltering(This,plVideoFilter)	\
    (This)->lpVtbl -> GetVideoFiltering(This,plVideoFilter)

#define IXCodeKsproxyPropertyConfig_GetClosedGOP(This,plClosedGOP)	\
    (This)->lpVtbl -> GetClosedGOP(This,plClosedGOP)

#define IXCodeKsproxyPropertyConfig_GetTBC(This,plTBC)	\
    (This)->lpVtbl -> GetTBC(This,plTBC)

#define IXCodeKsproxyPropertyConfig_GetInverseTelecine(This,plITelecine)	\
    (This)->lpVtbl -> GetInverseTelecine(This,plITelecine)

#define IXCodeKsproxyPropertyConfig_GetTVStandard(This,plTVStd)	\
    (This)->lpVtbl -> GetTVStandard(This,plTVStd)

#define IXCodeKsproxyPropertyConfig_GetFieldOrder(This,plFieldOrder)	\
    (This)->lpVtbl -> GetFieldOrder(This,plFieldOrder)

#define IXCodeKsproxyPropertyConfig_GetAudioType(This,plVar)	\
    (This)->lpVtbl -> GetAudioType(This,plVar)

#define IXCodeKsproxyPropertyConfig_GetInputAudioType(This,plVar)	\
    (This)->lpVtbl -> GetInputAudioType(This,plVar)

#define IXCodeKsproxyPropertyConfig_GetAudioBRate(This,plVar)	\
    (This)->lpVtbl -> GetAudioBRate(This,plVar)

#define IXCodeKsproxyPropertyConfig_GetAudioSRate(This,plVar)	\
    (This)->lpVtbl -> GetAudioSRate(This,plVar)

#define IXCodeKsproxyPropertyConfig_GetInputAudioSRate(This,plVar)	\
    (This)->lpVtbl -> GetInputAudioSRate(This,plVar)

#define IXCodeKsproxyPropertyConfig_GetAudioChannels(This,plVar)	\
    (This)->lpVtbl -> GetAudioChannels(This,plVar)

#define IXCodeKsproxyPropertyConfig_GetAudioFrameCRC(This,plVar)	\
    (This)->lpVtbl -> GetAudioFrameCRC(This,plVar)

#define IXCodeKsproxyPropertyConfig_GetAudioOutPID(This,plVar)	\
    (This)->lpVtbl -> GetAudioOutPID(This,plVar)

#define IXCodeKsproxyPropertyConfig_GetVideoOutPID(This,plVar)	\
    (This)->lpVtbl -> GetVideoOutPID(This,plVar)

#define IXCodeKsproxyPropertyConfig_GetTSMode(This,plVar)	\
    (This)->lpVtbl -> GetTSMode(This,plVar)

#define IXCodeKsproxyPropertyConfig_GetInitTimeStamp(This,plArg)	\
    (This)->lpVtbl -> GetInitTimeStamp(This,plArg)

#define IXCodeKsproxyPropertyConfig_SetRate(This,lRate)	\
    (This)->lpVtbl -> SetRate(This,lRate)

#define IXCodeKsproxyPropertyConfig_SetOutputWidth(This,lWidth)	\
    (This)->lpVtbl -> SetOutputWidth(This,lWidth)

#define IXCodeKsproxyPropertyConfig_SetOutputHeight(This,lHeight)	\
    (This)->lpVtbl -> SetOutputHeight(This,lHeight)

#define IXCodeKsproxyPropertyConfig_SetFormat(This,lFormat)	\
    (This)->lpVtbl -> SetFormat(This,lFormat)

#define IXCodeKsproxyPropertyConfig_SetVideoType(This,lValue)	\
    (This)->lpVtbl -> SetVideoType(This,lValue)

#define IXCodeKsproxyPropertyConfig_SetBitrate(This,lValue)	\
    (This)->lpVtbl -> SetBitrate(This,lValue)

#define IXCodeKsproxyPropertyConfig_SetPeakBitrate(This,lValue)	\
    (This)->lpVtbl -> SetPeakBitrate(This,lValue)

#define IXCodeKsproxyPropertyConfig_SetTimeStampMode(This,lValue)	\
    (This)->lpVtbl -> SetTimeStampMode(This,lValue)

#define IXCodeKsproxyPropertyConfig_SetInitTimeStamp(This,lValue)	\
    (This)->lpVtbl -> SetInitTimeStamp(This,lValue)

#define IXCodeKsproxyPropertyConfig_SetVideoFiltering(This,lValue)	\
    (This)->lpVtbl -> SetVideoFiltering(This,lValue)

#define IXCodeKsproxyPropertyConfig_SetClosedGOP(This,lValue)	\
    (This)->lpVtbl -> SetClosedGOP(This,lValue)

#define IXCodeKsproxyPropertyConfig_SetTBC(This,lValue)	\
    (This)->lpVtbl -> SetTBC(This,lValue)

#define IXCodeKsproxyPropertyConfig_SetInverseTelecine(This,lValue)	\
    (This)->lpVtbl -> SetInverseTelecine(This,lValue)

#define IXCodeKsproxyPropertyConfig_SetTVStandard(This,lValue)	\
    (This)->lpVtbl -> SetTVStandard(This,lValue)

#define IXCodeKsproxyPropertyConfig_SetFieldOrder(This,lValue)	\
    (This)->lpVtbl -> SetFieldOrder(This,lValue)

#define IXCodeKsproxyPropertyConfig_SetAudioType(This,lValue)	\
    (This)->lpVtbl -> SetAudioType(This,lValue)

#define IXCodeKsproxyPropertyConfig_SetInputAudioType(This,lValue)	\
    (This)->lpVtbl -> SetInputAudioType(This,lValue)

#define IXCodeKsproxyPropertyConfig_SetAudioBRate(This,lValue)	\
    (This)->lpVtbl -> SetAudioBRate(This,lValue)

#define IXCodeKsproxyPropertyConfig_SetAudioSRate(This,lValue)	\
    (This)->lpVtbl -> SetAudioSRate(This,lValue)

#define IXCodeKsproxyPropertyConfig_SetInputAudioSRate(This,lValue)	\
    (This)->lpVtbl -> SetInputAudioSRate(This,lValue)

#define IXCodeKsproxyPropertyConfig_SetAudioChannels(This,lValue)	\
    (This)->lpVtbl -> SetAudioChannels(This,lValue)

#define IXCodeKsproxyPropertyConfig_SetAudioFrameCRC(This,lValue)	\
    (This)->lpVtbl -> SetAudioFrameCRC(This,lValue)

#define IXCodeKsproxyPropertyConfig_SetAudioOutPID(This,lValue)	\
    (This)->lpVtbl -> SetAudioOutPID(This,lValue)

#define IXCodeKsproxyPropertyConfig_SetVideoOutPID(This,lValue)	\
    (This)->lpVtbl -> SetVideoOutPID(This,lValue)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IXCodeKsproxyPropertyConfig_GetRate_Proxy( 
    IXCodeKsproxyPropertyConfig __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *plRate);


void __RPC_STUB IXCodeKsproxyPropertyConfig_GetRate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IXCodeKsproxyPropertyConfig_GetOutputWidth_Proxy( 
    IXCodeKsproxyPropertyConfig __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *plWidth);


void __RPC_STUB IXCodeKsproxyPropertyConfig_GetOutputWidth_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IXCodeKsproxyPropertyConfig_GetOutputHeight_Proxy( 
    IXCodeKsproxyPropertyConfig __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *plHeight);


void __RPC_STUB IXCodeKsproxyPropertyConfig_GetOutputHeight_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IXCodeKsproxyPropertyConfig_GetSystemFormat_Proxy( 
    IXCodeKsproxyPropertyConfig __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *plStd);


void __RPC_STUB IXCodeKsproxyPropertyConfig_GetSystemFormat_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IXCodeKsproxyPropertyConfig_GetPeakBitrate_Proxy( 
    IXCodeKsproxyPropertyConfig __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *plBRate);


void __RPC_STUB IXCodeKsproxyPropertyConfig_GetPeakBitrate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IXCodeKsproxyPropertyConfig_GetBitrate_Proxy( 
    IXCodeKsproxyPropertyConfig __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *plBRate);


void __RPC_STUB IXCodeKsproxyPropertyConfig_GetBitrate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IXCodeKsproxyPropertyConfig_GetVideoType_Proxy( 
    IXCodeKsproxyPropertyConfig __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *plVar);


void __RPC_STUB IXCodeKsproxyPropertyConfig_GetVideoType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IXCodeKsproxyPropertyConfig_GetVideoFiltering_Proxy( 
    IXCodeKsproxyPropertyConfig __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *plVideoFilter);


void __RPC_STUB IXCodeKsproxyPropertyConfig_GetVideoFiltering_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IXCodeKsproxyPropertyConfig_GetClosedGOP_Proxy( 
    IXCodeKsproxyPropertyConfig __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *plClosedGOP);


void __RPC_STUB IXCodeKsproxyPropertyConfig_GetClosedGOP_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IXCodeKsproxyPropertyConfig_GetTBC_Proxy( 
    IXCodeKsproxyPropertyConfig __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *plTBC);


void __RPC_STUB IXCodeKsproxyPropertyConfig_GetTBC_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IXCodeKsproxyPropertyConfig_GetInverseTelecine_Proxy( 
    IXCodeKsproxyPropertyConfig __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *plITelecine);


void __RPC_STUB IXCodeKsproxyPropertyConfig_GetInverseTelecine_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IXCodeKsproxyPropertyConfig_GetTVStandard_Proxy( 
    IXCodeKsproxyPropertyConfig __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *plTVStd);


void __RPC_STUB IXCodeKsproxyPropertyConfig_GetTVStandard_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IXCodeKsproxyPropertyConfig_GetFieldOrder_Proxy( 
    IXCodeKsproxyPropertyConfig __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *plFieldOrder);


void __RPC_STUB IXCodeKsproxyPropertyConfig_GetFieldOrder_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IXCodeKsproxyPropertyConfig_GetAudioType_Proxy( 
    IXCodeKsproxyPropertyConfig __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *plVar);


void __RPC_STUB IXCodeKsproxyPropertyConfig_GetAudioType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IXCodeKsproxyPropertyConfig_GetInputAudioType_Proxy( 
    IXCodeKsproxyPropertyConfig __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *plVar);


void __RPC_STUB IXCodeKsproxyPropertyConfig_GetInputAudioType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IXCodeKsproxyPropertyConfig_GetAudioBRate_Proxy( 
    IXCodeKsproxyPropertyConfig __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *plVar);


void __RPC_STUB IXCodeKsproxyPropertyConfig_GetAudioBRate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IXCodeKsproxyPropertyConfig_GetAudioSRate_Proxy( 
    IXCodeKsproxyPropertyConfig __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *plVar);


void __RPC_STUB IXCodeKsproxyPropertyConfig_GetAudioSRate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IXCodeKsproxyPropertyConfig_GetInputAudioSRate_Proxy( 
    IXCodeKsproxyPropertyConfig __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *plVar);


void __RPC_STUB IXCodeKsproxyPropertyConfig_GetInputAudioSRate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IXCodeKsproxyPropertyConfig_GetAudioChannels_Proxy( 
    IXCodeKsproxyPropertyConfig __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *plVar);


void __RPC_STUB IXCodeKsproxyPropertyConfig_GetAudioChannels_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IXCodeKsproxyPropertyConfig_GetAudioFrameCRC_Proxy( 
    IXCodeKsproxyPropertyConfig __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *plVar);


void __RPC_STUB IXCodeKsproxyPropertyConfig_GetAudioFrameCRC_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IXCodeKsproxyPropertyConfig_GetAudioInPID_Proxy( 
    IXCodeKsproxyPropertyConfig __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *plVar);


void __RPC_STUB IXCodeKsproxyPropertyConfig_GetAudioInPID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IXCodeKsproxyPropertyConfig_GetVideoInPID_Proxy( 
    IXCodeKsproxyPropertyConfig __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *plVar);


void __RPC_STUB IXCodeKsproxyPropertyConfig_GetVideoInPID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IXCodeKsproxyPropertyConfig_GetAudioOutPID_Proxy( 
    IXCodeKsproxyPropertyConfig __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *plVar);


void __RPC_STUB IXCodeKsproxyPropertyConfig_GetAudioOutPID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IXCodeKsproxyPropertyConfig_GetVideoOutPID_Proxy( 
    IXCodeKsproxyPropertyConfig __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *plVar);


void __RPC_STUB IXCodeKsproxyPropertyConfig_GetVideoOutPID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IXCodeKsproxyPropertyConfig_GetTSMode_Proxy( 
    IXCodeKsproxyPropertyConfig __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *plVar);


void __RPC_STUB IXCodeKsproxyPropertyConfig_GetTSMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IXCodeKsproxyPropertyConfig_GetInitTimeStamp_Proxy( 
    IXCodeKsproxyPropertyConfig __RPC_FAR * This,
    /* [retval][out] */ unsigned __int64 __RPC_FAR *plArg);


void __RPC_STUB IXCodeKsproxyPropertyConfig_GetInitTimeStamp_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IXCodeKsproxyPropertyConfig_SetRate_Proxy( 
    IXCodeKsproxyPropertyConfig __RPC_FAR * This,
    /* [in] */ long lRate);


void __RPC_STUB IXCodeKsproxyPropertyConfig_SetRate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IXCodeKsproxyPropertyConfig_SetOutputWidth_Proxy( 
    IXCodeKsproxyPropertyConfig __RPC_FAR * This,
    /* [in] */ long lWidth);


void __RPC_STUB IXCodeKsproxyPropertyConfig_SetOutputWidth_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IXCodeKsproxyPropertyConfig_SetOutputHeight_Proxy( 
    IXCodeKsproxyPropertyConfig __RPC_FAR * This,
    /* [in] */ long lHeight);


void __RPC_STUB IXCodeKsproxyPropertyConfig_SetOutputHeight_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IXCodeKsproxyPropertyConfig_SetFormat_Proxy( 
    IXCodeKsproxyPropertyConfig __RPC_FAR * This,
    /* [in] */ long lFormat);


void __RPC_STUB IXCodeKsproxyPropertyConfig_SetFormat_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IXCodeKsproxyPropertyConfig_SetVideoType_Proxy( 
    IXCodeKsproxyPropertyConfig __RPC_FAR * This,
    /* [in] */ long lValue);


void __RPC_STUB IXCodeKsproxyPropertyConfig_SetVideoType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IXCodeKsproxyPropertyConfig_SetBitrate_Proxy( 
    IXCodeKsproxyPropertyConfig __RPC_FAR * This,
    /* [in] */ long lValue);


void __RPC_STUB IXCodeKsproxyPropertyConfig_SetBitrate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IXCodeKsproxyPropertyConfig_SetPeakBitrate_Proxy( 
    IXCodeKsproxyPropertyConfig __RPC_FAR * This,
    /* [in] */ long lValue);


void __RPC_STUB IXCodeKsproxyPropertyConfig_SetPeakBitrate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IXCodeKsproxyPropertyConfig_SetTimeStampMode_Proxy( 
    IXCodeKsproxyPropertyConfig __RPC_FAR * This,
    /* [in] */ long lValue);


void __RPC_STUB IXCodeKsproxyPropertyConfig_SetTimeStampMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IXCodeKsproxyPropertyConfig_SetInitTimeStamp_Proxy( 
    IXCodeKsproxyPropertyConfig __RPC_FAR * This,
    /* [in] */ unsigned __int64 lValue);


void __RPC_STUB IXCodeKsproxyPropertyConfig_SetInitTimeStamp_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IXCodeKsproxyPropertyConfig_SetVideoFiltering_Proxy( 
    IXCodeKsproxyPropertyConfig __RPC_FAR * This,
    /* [in] */ long lValue);


void __RPC_STUB IXCodeKsproxyPropertyConfig_SetVideoFiltering_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IXCodeKsproxyPropertyConfig_SetClosedGOP_Proxy( 
    IXCodeKsproxyPropertyConfig __RPC_FAR * This,
    /* [in] */ long lValue);


void __RPC_STUB IXCodeKsproxyPropertyConfig_SetClosedGOP_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IXCodeKsproxyPropertyConfig_SetTBC_Proxy( 
    IXCodeKsproxyPropertyConfig __RPC_FAR * This,
    /* [in] */ long lValue);


void __RPC_STUB IXCodeKsproxyPropertyConfig_SetTBC_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IXCodeKsproxyPropertyConfig_SetInverseTelecine_Proxy( 
    IXCodeKsproxyPropertyConfig __RPC_FAR * This,
    /* [in] */ long lValue);


void __RPC_STUB IXCodeKsproxyPropertyConfig_SetInverseTelecine_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IXCodeKsproxyPropertyConfig_SetTVStandard_Proxy( 
    IXCodeKsproxyPropertyConfig __RPC_FAR * This,
    /* [in] */ long lValue);


void __RPC_STUB IXCodeKsproxyPropertyConfig_SetTVStandard_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IXCodeKsproxyPropertyConfig_SetFieldOrder_Proxy( 
    IXCodeKsproxyPropertyConfig __RPC_FAR * This,
    /* [in] */ long lValue);


void __RPC_STUB IXCodeKsproxyPropertyConfig_SetFieldOrder_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IXCodeKsproxyPropertyConfig_SetAudioType_Proxy( 
    IXCodeKsproxyPropertyConfig __RPC_FAR * This,
    /* [in] */ long lValue);


void __RPC_STUB IXCodeKsproxyPropertyConfig_SetAudioType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IXCodeKsproxyPropertyConfig_SetInputAudioType_Proxy( 
    IXCodeKsproxyPropertyConfig __RPC_FAR * This,
    /* [in] */ long lValue);


void __RPC_STUB IXCodeKsproxyPropertyConfig_SetInputAudioType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IXCodeKsproxyPropertyConfig_SetAudioBRate_Proxy( 
    IXCodeKsproxyPropertyConfig __RPC_FAR * This,
    /* [in] */ long lValue);


void __RPC_STUB IXCodeKsproxyPropertyConfig_SetAudioBRate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IXCodeKsproxyPropertyConfig_SetAudioSRate_Proxy( 
    IXCodeKsproxyPropertyConfig __RPC_FAR * This,
    /* [in] */ long lValue);


void __RPC_STUB IXCodeKsproxyPropertyConfig_SetAudioSRate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IXCodeKsproxyPropertyConfig_SetInputAudioSRate_Proxy( 
    IXCodeKsproxyPropertyConfig __RPC_FAR * This,
    /* [in] */ long lValue);


void __RPC_STUB IXCodeKsproxyPropertyConfig_SetInputAudioSRate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IXCodeKsproxyPropertyConfig_SetAudioChannels_Proxy( 
    IXCodeKsproxyPropertyConfig __RPC_FAR * This,
    /* [in] */ long lValue);


void __RPC_STUB IXCodeKsproxyPropertyConfig_SetAudioChannels_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IXCodeKsproxyPropertyConfig_SetAudioFrameCRC_Proxy( 
    IXCodeKsproxyPropertyConfig __RPC_FAR * This,
    /* [in] */ long lValue);


void __RPC_STUB IXCodeKsproxyPropertyConfig_SetAudioFrameCRC_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IXCodeKsproxyPropertyConfig_SetAudioInPID_Proxy( 
    IXCodeKsproxyPropertyConfig __RPC_FAR * This,
    /* [in] */ long lValue);


void __RPC_STUB IXCodeKsproxyPropertyConfig_SetAudioInPID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IXCodeKsproxyPropertyConfig_SetVideoInPID_Proxy( 
    IXCodeKsproxyPropertyConfig __RPC_FAR * This,
    /* [in] */ long lValue);


void __RPC_STUB IXCodeKsproxyPropertyConfig_SetVideoInPID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IXCodeKsproxyPropertyConfig_SetAudioOutPID_Proxy( 
    IXCodeKsproxyPropertyConfig __RPC_FAR * This,
    /* [in] */ long lValue);


void __RPC_STUB IXCodeKsproxyPropertyConfig_SetAudioOutPID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IXCodeKsproxyPropertyConfig_SetVideoOutPID_Proxy( 
    IXCodeKsproxyPropertyConfig __RPC_FAR * This,
    /* [in] */ long lValue);


void __RPC_STUB IXCodeKsproxyPropertyConfig_SetVideoOutPID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IXCodeKsproxyPropertyConfig_INTERFACE_DEFINED__ */


DEFINE_GUID(CLSID_XCodeKsProxyPropertyPage,0xC7384532,0x47DE,0x4f80,0x84,0xE1,0xDE,0x01,0xE0,0xF4,0xBC,0x8C);

#ifdef __cplusplus

class DECLSPEC_UUID("C7384532-47DE-4f80-84E1-DE01E0F4BC8C")
XCodeKsProxyPropertyPage;
#endif

DEFINE_GUID(CLSID_XCodeKsProxyEncoderPage,0x0E3BA04E,0x6198,0x4f94,0xA4,0xAC,0x40,0x80,0x66,0x77,0xBD,0x13);

#ifdef __cplusplus

class DECLSPEC_UUID("0E3BA04E-6198-4f94-A4AC-40806677BD13")
XCodeKsProxyEncoderPage;
#endif

DEFINE_GUID(CLSID_XCodeKsProxyAudioEncoderPage,0xAFF23ADB,0x91FE,0x4376,0xB7,0x79,0x18,0xD4,0x7F,0x6B,0x79,0x6F);

#ifdef __cplusplus

class DECLSPEC_UUID("AFF23ADB-91FE-4376-B779-18D47F6B796F")
XCodeKsProxyAudioEncoderPage;
#endif

DEFINE_GUID(CLSID_XCodeKsProxyMultiplexerPage,0xF28218B6,0x1E94,0x4f47,0xBC,0x90,0xA0,0xDA,0x5C,0x19,0xE6,0x05);

#ifdef __cplusplus

class DECLSPEC_UUID("F28218B6-1E94-4f47-BC90-A0DA5C19E605")
XCodeKsProxyMultiplexerPage;
#endif
#endif /* __XCodeKsproxyProperty_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
