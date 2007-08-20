// SampleSampleCaptureFilter.h: interface for the SampleSampleCaptureFilter class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SAMPLESampleCaptureFILTER_H__8B25672A_9ED7_403C_94DF_931FCD5FD97B__INCLUDED_)
#define AFX_SAMPLESampleCaptureFILTER_H__8B25672A_9ED7_403C_94DF_931FCD5FD97B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <deque>
using namespace std;

class SampleCaptureFilter;
typedef struct XMPMediaSample
{
    IMediaSample *p_sample;
    __int64		 i_timestamp;
	
} XMPMediaSample;
int GetFourCCFromMediaType(const AM_MEDIA_TYPE &media_type);

class SampleCapturePin: public IPin, public IMemInputPin
{
    friend class SampleCaptureEnumMediaTypes;

    void* p_input;
    SampleCaptureFilter  *p_filter;

    IPin *p_connected_pin;

    AM_MEDIA_TYPE *media_types;
    size_t media_type_count;

    AM_MEDIA_TYPE cx_media_type;

    deque<XMPMediaSample> samples_queue;

    long i_ref;

	//Godzilar 
	CRITICAL_SECTION	m_mylock;
  public:
    SampleCapturePin( void *_p_input, 
                SampleCaptureFilter *_p_filter,
                AM_MEDIA_TYPE *mt, size_t mt_count );
    virtual ~SampleCapturePin();

    /* IUnknown methods */
    STDMETHODIMP QueryInterface(REFIID riid, void **ppv);
    STDMETHODIMP_(ULONG) AddRef();
    STDMETHODIMP_(ULONG) Release();

    /* IPin methods */
    STDMETHODIMP Connect( IPin * pReceivePin, const AM_MEDIA_TYPE *pmt );
    STDMETHODIMP ReceiveConnection( IPin * pConnector,
                                    const AM_MEDIA_TYPE *pmt );
    STDMETHODIMP Disconnect();
    STDMETHODIMP ConnectedTo( IPin **pPin );
    STDMETHODIMP ConnectionMediaType( AM_MEDIA_TYPE *pmt );
    STDMETHODIMP QueryPinInfo( PIN_INFO * pInfo );
    STDMETHODIMP QueryDirection( PIN_DIRECTION * pPinDir );
    STDMETHODIMP QueryId( LPWSTR * Id );
    STDMETHODIMP QueryAccept( const AM_MEDIA_TYPE *pmt );
    STDMETHODIMP EnumMediaTypes( IEnumMediaTypes **ppEnum );
    STDMETHODIMP QueryInternalConnections( IPin* *apPin, ULONG *nPin );
    STDMETHODIMP EndOfStream( void );

    STDMETHODIMP BeginFlush( void );
    STDMETHODIMP EndFlush( void );
    STDMETHODIMP NewSegment( REFERENCE_TIME tStart, REFERENCE_TIME tStop,
                             double dRate );

    /* IMemInputPin methods */
    STDMETHODIMP GetAllocator( IMemAllocator **ppAllocator );
    STDMETHODIMP NotifyAllocator(  IMemAllocator *pAllocator, BOOL bReadOnly );
    STDMETHODIMP GetAllocatorRequirements( ALLOCATOR_PROPERTIES *pProps );
    STDMETHODIMP Receive( IMediaSample *pSample );
    STDMETHODIMP ReceiveMultiple( IMediaSample **pSamples, long nSamples,
                                  long *nSamplesProcessed );
    STDMETHODIMP ReceiveCanBlock( void );

    /* Custom methods */
    HRESULT CustomGetSample( XMPMediaSample * );
    AM_MEDIA_TYPE &CustomGetMediaType();
};
#define FILTER_NAME  L"XMediaPlatform SampleCapture Filter"
#define PIN_NAME     L"SampleCapture"
#define NULL_RENDERER_NAME  L"Null Renderer"

/****************************************************************************
 * Declaration of our dummy directshow filter class
 ****************************************************************************/
class SampleCaptureFilter : public IBaseFilter
{
    friend class SampleCapturePin;

    void   *p_input;
    SampleCapturePin     *p_pin;
    IFilterGraph   *p_graph;
    //AM_MEDIA_TYPE  media_type;
    FILTER_STATE   state;

    long i_ref;

  public:
    SampleCaptureFilter( void*_p_input,
                   AM_MEDIA_TYPE *mt, size_t mt_count );
    virtual ~SampleCaptureFilter();

    /* IUnknown methods */
    STDMETHODIMP QueryInterface(REFIID riid, void **ppv);
    STDMETHODIMP_(ULONG) AddRef();
    STDMETHODIMP_(ULONG) Release();

    /* IPersist method */
    STDMETHODIMP GetClassID(CLSID *pClsID);

    /* IMediaFilter methods */
    STDMETHODIMP GetState(DWORD dwMSecs, FILTER_STATE *State);
    STDMETHODIMP SetSyncSource(IReferenceClock *pClock);
    STDMETHODIMP GetSyncSource(IReferenceClock **pClock);
    STDMETHODIMP Stop();
    STDMETHODIMP Pause();
    STDMETHODIMP Run(REFERENCE_TIME tStart);

    /* IBaseFilter methods */
    STDMETHODIMP EnumPins( IEnumPins ** ppEnum );
    STDMETHODIMP FindPin( LPCWSTR Id, IPin ** ppPin );
    STDMETHODIMP QueryFilterInfo( FILTER_INFO * pInfo );
    STDMETHODIMP JoinFilterGraph( IFilterGraph * pGraph, LPCWSTR pName );
    STDMETHODIMP QueryVendorInfo( LPWSTR* pVendorInfo );

    /* Custom methods */
    SampleCapturePin *CustomGetPin();
};

/****************************************************************************
 * Declaration of our dummy directshow enumpins class
 ****************************************************************************/
class SampleCaptureEnumPins : public IEnumPins
{
    void*p_input;
    SampleCaptureFilter  *p_filter;

    int i_position;
    long i_ref;

public:
    SampleCaptureEnumPins( void*_p_input, SampleCaptureFilter *_p_filter,
                     SampleCaptureEnumPins *pEnumPins );
    virtual ~SampleCaptureEnumPins();

    // IUnknown
    STDMETHODIMP QueryInterface( REFIID riid, void **ppv );
    STDMETHODIMP_(ULONG) AddRef();
    STDMETHODIMP_(ULONG) Release();

    // IEnumPins
    STDMETHODIMP Next( ULONG cPins, IPin ** ppPins, ULONG * pcFetched );
    STDMETHODIMP Skip( ULONG cPins );
    STDMETHODIMP Reset();
    STDMETHODIMP Clone( IEnumPins **ppEnum );
};

/****************************************************************************
 * Declaration of our dummy directshow enummediatypes class
 ****************************************************************************/
class SampleCaptureEnumMediaTypes : public IEnumMediaTypes
{
    void*p_input;
    SampleCapturePin     *p_pin;
    AM_MEDIA_TYPE cx_media_type;

    size_t i_position;
    long i_ref;

public:
    SampleCaptureEnumMediaTypes( void*_p_input, SampleCapturePin *_p_pin,
                           SampleCaptureEnumMediaTypes *pEnumMediaTypes );

    virtual ~SampleCaptureEnumMediaTypes();

    // IUnknown
    STDMETHODIMP QueryInterface( REFIID riid, void **ppv );
    STDMETHODIMP_(ULONG) AddRef();
    STDMETHODIMP_(ULONG) Release();

    // IEnumMediaTypes
    STDMETHODIMP Next( ULONG cMediaTypes, AM_MEDIA_TYPE ** ppMediaTypes,
                       ULONG * pcFetched );
    STDMETHODIMP Skip( ULONG cMediaTypes );
    STDMETHODIMP Reset();
    STDMETHODIMP Clone( IEnumMediaTypes **ppEnum );
};


#endif // !defined(AFX_SAMPLESampleCaptureFILTER_H__8B25672A_9ED7_403C_94DF_931FCD5FD97B__INCLUDED_)
