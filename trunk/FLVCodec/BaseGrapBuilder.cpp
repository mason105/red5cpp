// BaseGrapBuilder.cpp: implementation of the CBaseGrapBuilder class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "BaseGrapBuilder.h"
#include "SampleCaptureFilter.h"

#ifdef _DEBUG
#pragma comment(lib, "../FLVCodec/strmbasd.lib")
#else
#pragma comment(lib, "../FLVCodec/strmbase.lib")
#endif
#pragma comment(lib, "winmm.lib")

#define BIT_COUNT_9                  9
#define BIT_COUNT_12                12
#define BIT_COUNT_16                16
#define BIT_COUNT_24                24
#define BIT_COUNT_32                32

int helper_GetBMISizeImage(BITMAPINFOHEADER bmiHeader)
{
	int D_X = bmiHeader.biWidth;
	int D_Y = bmiHeader.biHeight;
	int v   = 0;
	switch(bmiHeader.biCompression)
	{
	case mmioFOURCC('Y','U','Y','2'):
		return D_X * D_Y * BIT_COUNT_16 / 8 + v;
	case KS_BI_RGB:
		{
			if(bmiHeader.biBitCount == BIT_COUNT_16)
				return D_X * D_Y * BIT_COUNT_16 / 8 + v;
			else if(bmiHeader.biBitCount == BIT_COUNT_24)
				return D_X * D_Y * BIT_COUNT_24 / 8 + v;
			else
				return D_X * D_Y * BIT_COUNT_32 / 8 + v;
		}
	case mmioFOURCC('U','Y','V','Y'):
		return D_X * D_Y * BIT_COUNT_16 / 8 + v;
	case mmioFOURCC('Y','4','1','P'):
		return D_X * D_Y * BIT_COUNT_12 / 8 + v;
	case mmioFOURCC('Y','V','1','2'):
		return D_X * D_Y * BIT_COUNT_12 / 8 + v;
	case mmioFOURCC('Y','V','U','9'):
		return  D_X * D_Y * BIT_COUNT_9 / 8 + v;
	default:
		break;
	}
	return DIBSIZE(bmiHeader);
}
int GetFourCCPriority( int i_fourcc )
{
    switch( i_fourcc )
    {
    case MAKEFOURCC('I','4','2','0'):
    case MAKEFOURCC('f','l','3','2'):
        return 9;
    case MAKEFOURCC('Y','V','1','2'):
    case MAKEFOURCC('a','r','a','w'):
        return 8;
    case MAKEFOURCC('R','V','2','4'):
        return 7;
    case MAKEFOURCC('Y','U','Y','2'):
    case MAKEFOURCC('R','V','3','2'):
    case MAKEFOURCC('R','G','B','A'):
        return 6;
    }
	
    return 0;
}

AMTYPE inline GetAMMediaType(AM_MEDIA_TYPE am)
{
	AMTYPE at = AMTYPE_Unknown;
	if(am.majortype == MEDIATYPE_Video ||
		am.majortype == MEDIATYPE_AnalogVideo)
		at = AMTYPE_Video;
	else if(am.majortype == MEDIATYPE_Audio ||
		am.majortype == MEDIATYPE_AnalogAudio)
		at = AMTYPE_Audio;
	else 
	{
		if(am.formattype == FORMAT_MPEGVideo ||
			am.formattype == FORMAT_MPEG2Video ||
			am.formattype == FORMAT_VideoInfo ||
			am.formattype == FORMAT_VideoInfo2)
			at = AMTYPE_Video;
		else if(am.subtype == MEDIASUBTYPE_MPEG1Audio ||
			am.formattype == FORMAT_WaveFormatEx)
			at = AMTYPE_Audio;
		
	}
	return at;
}
VIDEOINFOHEADER	 *AMGetVideoInfoHeader(AM_MEDIA_TYPE am)
{
	VIDEOINFOHEADER *pvih = new VIDEOINFOHEADER;
	if(am.formattype == FORMAT_MPEGVideo)
	{
		MPEG1VIDEOINFO *p0 = (MPEG1VIDEOINFO*)am.pbFormat;
		memcpy(pvih, &p0->hdr, sizeof(VIDEOINFOHEADER));
	}
	else if(am.formattype == FORMAT_MPEG2Video)
	{
		MPEG2VIDEOINFO *p1 = (MPEG2VIDEOINFO*)am.pbFormat;
		pvih->AvgTimePerFrame	= p1->hdr.AvgTimePerFrame;
		pvih->bmiHeader			= p1->hdr.bmiHeader;
		pvih->dwBitErrorRate	= p1->hdr.dwBitErrorRate;
		pvih->dwBitRate			= p1->hdr.dwBitRate;
		pvih->rcSource			= p1->hdr.rcSource;
		pvih->rcTarget			= p1->hdr.rcTarget;
	}
	else if(am.formattype == FORMAT_VideoInfo)
	{
		VIDEOINFOHEADER *p2 = (VIDEOINFOHEADER*)am.pbFormat;
		memcpy(pvih, p2, sizeof(VIDEOINFOHEADER));
	}
	else if(am.formattype == FORMAT_VideoInfo2)
	{
		VIDEOINFOHEADER2 *p3 = (VIDEOINFOHEADER2*)am.pbFormat;
		pvih->AvgTimePerFrame	= p3->AvgTimePerFrame;
		pvih->bmiHeader			= p3->bmiHeader;
		pvih->dwBitErrorRate	= p3->dwBitErrorRate;
		pvih->dwBitRate			= p3->dwBitRate;
		pvih->rcSource			= p3->rcSource;
		pvih->rcTarget			= p3->rcTarget;
	}
	else
	{
		delete pvih;
		pvih = NULL;
	}
	return pvih;
}
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CBaseGrapBuilder::CBaseGrapBuilder()
{
	m_pCaptureBuilder	= NULL;
	m_pGraphBuilder		= NULL;
	m_pMediaControl		= NULL;
	m_pMediaSeeking	= NULL;
#ifdef _DEBUGAddGraphToROT
	m_dwRegister		= 0;
#endif
	pp_streams			= NULL;
	i_streams			= 0;
	i_current_stream	= NULL;
}

CBaseGrapBuilder::~CBaseGrapBuilder()
{

}
HRESULT	CBaseGrapBuilder::Initialize(TCHAR *szParam, IGraphBuilder* pGraphBuilder)
{
	HRESULT hr;
	do {
		if(pGraphBuilder)
		{
			m_pGraphBuilder = pGraphBuilder;
			m_pGraphBuilder->AddRef();
		}
		else
		{
			if (FAILED(hr = CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER, IID_IGraphBuilder, (void **)&m_pGraphBuilder)))
				break;
		}
		
		if (FAILED(hr = CoCreateInstance(CLSID_CaptureGraphBuilder2, NULL, CLSCTX_INPROC_SERVER, IID_ICaptureGraphBuilder2, (void **)&m_pCaptureBuilder))) 
			break;
		
		
		if (FAILED(hr = m_pCaptureBuilder->SetFiltergraph(m_pGraphBuilder)))
			break;
		
		
		if (FAILED(hr = m_pGraphBuilder->QueryInterface(IID_IMediaControl, (void **)&m_pMediaControl))) 
			break;

		if (FAILED(hr = m_pGraphBuilder->QueryInterface(IID_IMediaSeeking, (void **)&m_pMediaSeeking))) 
			break;
		
#ifdef _DEBUGAddGraphToROT
		if(FAILED(hr = AddGraphToROT()))
			break;
#endif
		i_streams = 0;
		
		if(FAILED(hr = RenderGrapBuilder(szParam)))
			break;
		
		if(FAILED(hr = ConstructStream()))
			break;
		
		return S_OK;	
	} while(false);
	Cleanup();
	
	return hr;
}
HRESULT CBaseGrapBuilder::Cleanup()
{
	
	HRESULT hr = S_OK;
	hr = ReleaseInterface();
	hr = DestructStream();
#ifdef _DEBUGAddGraphToROT
	hr = RemoveGraphFromROT();
#endif	
	SAFE_RELEASE(m_pMediaSeeking);	
	SAFE_RELEASE(m_pMediaControl);
	SAFE_RELEASE(m_pCaptureBuilder);

	SAFE_RELEASE(m_pGraphBuilder);
	return hr;
}
HRESULT CBaseGrapBuilder::Run()
{
	if(m_pMediaControl)
		return m_pMediaControl->Run();
	return E_NOINTERFACE;
	
}
HRESULT CBaseGrapBuilder::Stop()
{
	if(m_pMediaControl)
		return m_pMediaControl->Stop();
	return E_NOINTERFACE;
}
HRESULT CBaseGrapBuilder::Pause()
{
	if(m_pMediaControl)
		return m_pMediaControl->Pause();
	return E_NOINTERFACE;
}
HRESULT CBaseGrapBuilder::GetDuration(LONGLONG* pDuration)
{
	if(m_pMediaSeeking)
		return m_pMediaSeeking->GetDuration(pDuration);
	return E_NOINTERFACE;
}
HRESULT CBaseGrapBuilder::GetCurrentPosition(LONGLONG* pCurrent)
{
	if(m_pMediaSeeking)
		return m_pMediaSeeking->GetPositions(pCurrent, NULL);
	return E_NOINTERFACE;
}

HRESULT			CBaseGrapBuilder::CreateFilter_BySpecialCategoryAndName(REFCLSID clsidCategory,\
													  const TCHAR  *szName,\
													  BOOL  bAddtoGrapBuilder,\
													  IBaseFilter** ppOutFilter)
{
	USES_CONVERSION;

	HRESULT hr = S_OK;
	CComPtr<ICreateDevEnum>  pSysDevEnum;
	CComPtr<IEnumMoniker>	 pEnumCat;
	CComPtr<IMoniker>		 pMoniker;
	CComPtr<IPropertyBag>	 pPropBag;
	ULONG			cFetched	 = 1;
	IBaseFilter		*pFilter	 = NULL;
	VARIANT varName;
	varName.vt = VT_BSTR;

	hr = CoCreateInstance(CLSID_SystemDeviceEnum, 
		NULL, CLSCTX_INPROC, 
		IID_ICreateDevEnum, (void**)&pSysDevEnum);
	if(FAILED(hr))
	{
		goto Finally;
	}

	hr = pSysDevEnum->CreateClassEnumerator(clsidCategory, &pEnumCat, 0);
	if(FAILED(hr))
	{
		goto Finally;
	}
	if(pEnumCat == NULL)
	{
		hr = E_FAIL;
		goto Finally;
	}

	while(pEnumCat->Next(1, &pMoniker, &cFetched) == S_OK)
	{
		pPropBag.Release();
		hr = pMoniker->BindToStorage(0, 0, IID_IPropertyBag, (void**)&pPropBag);
		if(pPropBag)
		{
			hr = pPropBag->Read(L"FriendlyName", &varName, 0);
			if(SUCCEEDED(hr))
			{
				TCHAR FriendlyName[256];
				_tcsncpy(FriendlyName, W2T(varName.bstrVal), 255);
				if(_tcsicmp(FriendlyName, szName) == 0)
				{					
					hr = pMoniker->BindToObject(0, 0, IID_IBaseFilter, (void**)&pFilter);
					if(SUCCEEDED(hr))
					{
						SysFreeString(varName.bstrVal);
						goto find_ok;
					}
					SAFE_RELEASE(pFilter);											
				}
				SysFreeString(varName.bstrVal);
			}
		}

		pMoniker.Release();
	}
find_ok:

	if(pFilter == NULL)
	{
		hr = E_FAIL;
		*ppOutFilter = NULL;
		goto Finally;
	}
	if(bAddtoGrapBuilder)
	{
		hr = AddFilter_Simple(szName, &pFilter);
		if(SUCCEEDED(hr))
		{
			*ppOutFilter = pFilter;
		}
		else
		{
			*ppOutFilter = NULL;
		}
	}
	else
	{
		*ppOutFilter = pFilter;
	}
Finally:


	return hr;
}
HRESULT		CBaseGrapBuilder::CreateFilter_BySpecialCategoryAndName_SupportConnectPin(REFCLSID clsidCategory,\
																 const TCHAR  *szName,\
																 BOOL  bAddtoGrapBuilder,\
																 IPin  *pInPin,
																 bool  bStillConnect,
																 IBaseFilter** ppOutFilter)
{
	USES_CONVERSION;

	HRESULT hr = S_OK;
	CComPtr<ICreateDevEnum>  pSysDevEnum;
	CComPtr<IEnumMoniker>	 pEnumCat;
	CComPtr<IMoniker>		 pMoniker;
	CComPtr<IPropertyBag>	 pPropBag;
	ULONG			cFetched	 = 1;
	IBaseFilter		*pFilter	 = NULL;
	VARIANT varName;
	varName.vt = VT_BSTR;

	hr = CoCreateInstance(CLSID_SystemDeviceEnum, 
		NULL, CLSCTX_INPROC, 
		IID_ICreateDevEnum, (void**)&pSysDevEnum);
	if(FAILED(hr))
	{
		goto Finally;
	}

	hr = pSysDevEnum->CreateClassEnumerator(clsidCategory, &pEnumCat, 0);
	if(FAILED(hr))
	{
		goto Finally;
	}
	if(pEnumCat == NULL)
	{
		hr = E_FAIL;
		goto Finally;
	}

	while(pEnumCat->Next(1, &pMoniker, &cFetched) == S_OK)
	{
		pPropBag.Release();
		hr = pMoniker->BindToStorage(0, 0, IID_IPropertyBag, (void**)&pPropBag);
		if(pPropBag)
		{
			hr = pPropBag->Read(L"FriendlyName", &varName, 0);
			if(SUCCEEDED(hr))
			{
				TCHAR FriendlyName[256];
				_tcsncpy(FriendlyName, W2T(varName.bstrVal), 255);
				if(_tcsicmp(FriendlyName, szName) == 0)
				{
					
					hr = pMoniker->BindToObject(0, 0, IID_IBaseFilter, (void**)&pFilter);
					if(SUCCEEDED(hr))
					{
						hr = AddFilter_Simple(szName, &pFilter);
						if(SUCCEEDED(hr))
						{
							IPin* pUpStreamPin   = pInPin;
							CComPtr<IPin>		 pDownStreamPin;
							hr = GetPin_ByDirect(pFilter, PINDIR_INPUT, &pDownStreamPin);
							if(SUCCEEDED(hr) && pDownStreamPin)
							{
								hr = ConnectPin_Simple(pUpStreamPin, pDownStreamPin);
								if(SUCCEEDED(hr))
								{
									if(!bStillConnect)
									{
										pDownStreamPin->Disconnect();
										pUpStreamPin->Disconnect();	
									}
									SysFreeString(varName.bstrVal);
									if(!bAddtoGrapBuilder)
										RemoveFilter_Simple(&pFilter);
									goto find_ok;
								}
							}
						}
						RemoveFilter_Simple(&pFilter);
					}
					SAFE_RELEASE(pFilter);				
				}
				SysFreeString(varName.bstrVal);
			}
		}

		pMoniker.Release();
	}
find_ok:

	if(pFilter == NULL)
	{
		hr = E_FAIL;
		*ppOutFilter = NULL;
		goto Finally;
	}
	
	*ppOutFilter = pFilter;
	
Finally:


	return hr;
}

HRESULT		    CBaseGrapBuilder::CreateFilter_BySpecialCLSIDString(TCHAR* szClsId, \
												  const TCHAR *szName,\
												  BOOL  bAddtoGrapBuilder,\
												  IBaseFilter **ppOutFilter)
{
	CLSID clsid;
	CComBSTR ccBs(szClsId);
	CLSIDFromString(ccBs,&clsid);
	return CreateFilter_BySpecialCLSID(clsid, szName, bAddtoGrapBuilder, ppOutFilter);

}
HRESULT			CBaseGrapBuilder::CreateFilter_BySpecialCLSID(CLSID ClsId, \
											const TCHAR *szName,\
											BOOL  bAddtoGrapBuilder,\
											IBaseFilter **ppOutFilter)
{
	USES_CONVERSION;

	HRESULT hr = S_OK;
	*ppOutFilter = NULL;

	IBaseFilter *pFilter = NULL;

	if (FAILED(hr = CoCreateInstance(ClsId, NULL, CLSCTX_INPROC_SERVER, IID_IBaseFilter, (void **)&pFilter)))
	{
		return hr;
	}
	if(bAddtoGrapBuilder)
	{
		if (FAILED(hr = AddFilter_Simple(szName, &pFilter))) 
		{
			SAFE_RELEASE(pFilter);
			return hr;
		}
		else
		{
			*ppOutFilter = pFilter;
		}
	}
	else
	{
		*ppOutFilter = pFilter;
	}

	return hr;
}
HRESULT			CBaseGrapBuilder::AddFilter_Simple(const TCHAR *szName,\
								 IBaseFilter **ppInFilter)
{
	USES_CONVERSION;

	if(ppInFilter == NULL || *ppInFilter == NULL)
		return E_POINTER;
	HRESULT hr = S_OK;

	if (FAILED(hr = m_pGraphBuilder->AddFilter(*ppInFilter, szName ? T2W(szName) : NULL)))
	{
		return hr;
	}

	return S_OK;	
}
HRESULT			CBaseGrapBuilder::RemoveFilter_Simple(IBaseFilter **ppInFilter)
{
	if(ppInFilter == NULL || *ppInFilter == NULL)
		return E_POINTER;
	HRESULT	hr= S_OK;

	if (FAILED(hr = m_pGraphBuilder->RemoveFilter(*ppInFilter))) 
	{
		return hr;
	}
	return hr;
}


HRESULT			CBaseGrapBuilder::GetPin_ByDirect(IBaseFilter *pInFilter, \
									PIN_DIRECTION PinDir,
									IPin **ppOutPin)
{
	if(pInFilter == NULL)
		return E_POINTER;

	HRESULT hr;
	*ppOutPin = NULL;

	CComPtr<IEnumPins> pEnum;
	if (FAILED(hr = pInFilter->EnumPins(&pEnum))) 
		return hr;

	ULONG cFetched = 1;
	IPin *pPin = NULL;
	while (pEnum->Next(1, &pPin, &cFetched) == S_OK)
	{
		PIN_DIRECTION _PinDir;
		if (FAILED(hr = pPin->QueryDirection(&_PinDir))) 
		{
			SAFE_RELEASE(pPin);
			break;
		}

		if (_PinDir == PinDir) 
		{
			*ppOutPin = pPin;
			break;
		} 
		else 
		{
			SAFE_RELEASE(pPin);
		}
	}


	if (!*ppOutPin) return E_FAIL;

	return S_OK;
}
HRESULT			CBaseGrapBuilder::GetPin_ByID(IBaseFilter *pInFilter, \
							const TCHAR* szID,
							IPin **ppOutPin)
{
	USES_CONVERSION;
	if(pInFilter == NULL)
		return E_FAIL;
	return pInFilter->FindPin(T2W(szID),ppOutPin);
}

HRESULT			CBaseGrapBuilder::GetPin_ByName(IBaseFilter *pInFilter, \
									const TCHAR* szName,
									IPin **ppOutPin)
{
	USES_CONVERSION;
	if(pInFilter == NULL)
		return E_FAIL;

	HRESULT hr = S_OK;
	CComPtr<IEnumPins> pEnumPins;
	IPin	  *pTempPin	 = NULL;
	ULONG	  cFetched = 1;
	*ppOutPin = NULL;
	hr = pInFilter->EnumPins(&pEnumPins);
	if(FAILED(hr))
		return hr;

	while(cFetched)
	{
		hr = pEnumPins->Next(1, &pTempPin, &cFetched);
		if(FAILED(hr) || pTempPin == NULL)
		{
			break;
		}
		PIN_INFO pi;
		memset(&pi, 0, sizeof(PIN_INFO));
		hr = pTempPin->QueryPinInfo(&pi);
		SAFE_RELEASE(pi.pFilter);
		if(FAILED(hr))
		{
			SAFE_RELEASE(pTempPin);
			continue;
		}
		if(_tcsnicmp(W2T(pi.achName), szName, _tcslen(szName)) == 0)
		{
			*ppOutPin = pTempPin;
			break;
		}
		SAFE_RELEASE(pTempPin);
	}

	if (!*ppOutPin) return E_FAIL;

	return S_OK;
}
HRESULT			CBaseGrapBuilder::GetPin_FirstDisconnected(IBaseFilter *pInFilter,
									PIN_DIRECTION PinDir,
									IPin **ppOutPin)
{
	if(pInFilter == NULL)
		return E_POINTER;
	*ppOutPin = NULL;

	HRESULT hr;
	ULONG cFetched = 1;
	CComPtr<IEnumPins> pEnumPins;
	IPin *pPin =  NULL;
	PIN_DIRECTION MyDir;
	PIN_DIRECTION dir = PinDir;

	hr = pInFilter->EnumPins(&pEnumPins);
	if(FAILED(hr))
		return hr;

	while (cFetched)
	{
		hr = pEnumPins->Next(1, &pPin, &cFetched);
		if(FAILED(hr) || pPin == NULL)
		{
			break;
		}
		hr = pPin->QueryDirection(&MyDir);
		if(FAILED(hr))
		{
			SAFE_RELEASE(pPin);
			continue;
		}
		if ( dir == MyDir)
		{
			IPin* pConn = NULL;
			pPin->ConnectedTo(&pConn);
			if(pConn == NULL)
			{
				*ppOutPin = pPin;
				break;
			}
			else
			{
				SAFE_RELEASE(pConn);
			}
		}
		SAFE_RELEASE(pPin);
	}


	if (!*ppOutPin) return E_FAIL;

	return S_OK;
}
BOOL	CBaseGrapBuilder::IsTheEndestFilter(IBaseFilter* pInFilter)
{
	if(pInFilter == NULL)
		return FALSE;
	
	HRESULT hr;
	ULONG	cFetched = 1;
	CComPtr<IEnumPins> pEnumPins;
	IPin *pPin =  NULL;
	PIN_DIRECTION MyDir;

	FILTER_INFO fi;
	memset(&fi, 0, sizeof(FILTER_INFO));
	hr = pInFilter->QueryFilterInfo(&fi);
	if(FAILED(hr))
		return FALSE;
	SAFE_RELEASE(fi.pGraph);
	if(!wcsnicmp(fi.achName, FILTER_NAME, wcslen(FILTER_NAME)) ||
		!wcsnicmp(fi.achName, NULL_RENDERER_NAME, wcslen(NULL_RENDERER_NAME)))
		return FALSE;
	
	hr = pInFilter->EnumPins(&pEnumPins);
	if(FAILED(hr))
		return FALSE;
	
	BOOL bIsTheEndestFilter = TRUE;
	while (cFetched && bIsTheEndestFilter)
	{
		hr = pEnumPins->Next(1, &pPin, &cFetched);
		if(FAILED(hr) || pPin == NULL)	
			break;
		
		hr = pPin->QueryDirection(&MyDir);
		if(FAILED(hr))
		{
			SAFE_RELEASE(pPin);
			continue;
		}

		if(MyDir == PINDIR_OUTPUT)
			bIsTheEndestFilter = FALSE;
	
		SAFE_RELEASE(pPin);
	}
	
	
	
	return bIsTheEndestFilter;
	
}
HRESULT			CBaseGrapBuilder::GetPin_ByType(IBaseFilter *pInFilter,\
											PIN_DIRECTION PinDir,\
											bool b_video,\
											IPin **ppOutPin)
{
	if(pInFilter == NULL)
		return E_POINTER;
	*ppOutPin = NULL;

	HRESULT hr;
	ULONG cFetched = 1;
	CComPtr<IEnumPins> pEnumPins;
	IPin *pPin =  NULL;
	PIN_DIRECTION MyDir;
	PIN_DIRECTION dir = PinDir;

	hr = pInFilter->EnumPins(&pEnumPins);
	if(FAILED(hr))
		return hr;

	while (cFetched)
	{
		hr = pEnumPins->Next(1, &pPin, &cFetched);
		if(FAILED(hr) || pPin == NULL)
		{
			break;
		}
		hr = pPin->QueryDirection(&MyDir);
		if(FAILED(hr))
		{
			SAFE_RELEASE(pPin);
			continue;
		}
		if ( dir == MyDir)
		{
			AM_MEDIA_TYPE am;
			if(SUCCEEDED(pPin->ConnectionMediaType(&am)))
			{
				if(b_video && GetAMMediaType(am) == AMTYPE_Video)
				{
					*ppOutPin = pPin;
				}
				else if(!b_video && GetAMMediaType(am) == AMTYPE_Audio)
				{
					*ppOutPin = pPin;

				}
				FreeMediaType(am);
				if(*ppOutPin)
					break;
			}
			else
			{
				CComPtr<IAMStreamConfig>	pAMStreamConfig;
				if(SUCCEEDED(pPin->QueryInterface(IID_IAMStreamConfig, (void**)&pAMStreamConfig)))
				{
					int caps_count = 0, caps_size = 0;
					VIDEO_STREAM_CONFIG_CAPS caps;					
					if(SUCCEEDED(pAMStreamConfig->GetNumberOfCapabilities(&caps_count, &caps_size)))
					{
						for(int i = 0; i < caps_count; i ++)
						{
							AM_MEDIA_TYPE* pam = NULL;
							hr = pAMStreamConfig->GetStreamCaps(i, &pam, (BYTE*)&caps);
							if(FAILED(hr))continue;

							if(b_video && GetAMMediaType(*pam) == AMTYPE_Video)
							{
								*ppOutPin = pPin;
							}
							else if(!b_video && GetAMMediaType(*pam) == AMTYPE_Audio)
							{
								*ppOutPin = pPin;

							}
							DeleteMediaType(pam);
							if(*ppOutPin)
								break;
						}
						if(*ppOutPin)
							break;
					}
				}
			}
		}
		SAFE_RELEASE(pPin);
	}


	if (!*ppOutPin) return E_FAIL;

	return S_OK;
}

HRESULT	CBaseGrapBuilder::ConnectPin_Simple(IPin *pOutPin, \
								  IPin *pInPin)
{
	if(pOutPin == NULL || pInPin == NULL)
		return E_POINTER;
	return m_pGraphBuilder->Connect(pOutPin, pInPin);	
}

HRESULT	CBaseGrapBuilder::ConnectPin_Direct(IPin *pOutPin, \
									IPin *pInPin, \
									const AM_MEDIA_TYPE *pmt)
{
	if(pOutPin == NULL || pInPin == NULL)
		return E_POINTER;
	return m_pGraphBuilder->ConnectDirect(pOutPin, pInPin, pmt);	

}
HRESULT	CBaseGrapBuilder::ConnectPin_Render(IPin *pInPin)
{
	if(pInPin == NULL)
		return E_POINTER;
	return m_pGraphBuilder->Render(pInPin);	
}

HRESULT	CBaseGrapBuilder::ConnectFilter_Simple(IBaseFilter *pUpStreamFilter, \
								IBaseFilter *pDownStreamFilter)
{
	CComPtr<IPin>	pOutPin_F1;
	CComPtr<IPin>	pInPin_F2;

	HRESULT hr;

	if (FAILED(hr = GetPin_FirstDisconnected(pUpStreamFilter, PINDIR_OUTPUT, &pOutPin_F1)))
		return hr;

	if (FAILED(hr = GetPin_FirstDisconnected(pDownStreamFilter, PINDIR_INPUT, &pInPin_F2))) 
		return hr;

	if (FAILED(hr = m_pGraphBuilder->Connect(pOutPin_F1, pInPin_F2)))
		return hr;

	return S_OK;
}

void 
CBaseGrapBuilder::ShowPropertyPage( IUnknown *obj, HWND hwnd )
{
	ISpecifyPropertyPages *p_spec;
	CAUUID cauuid;

	HRESULT hr = obj->QueryInterface( IID_ISpecifyPropertyPages,
		(void **)&p_spec );
	if( FAILED(hr) ) return;

	if( SUCCEEDED(p_spec->GetPages( &cauuid )) )
	{
		if( cauuid.cElems > 0 )
		{
			if(hwnd == NULL)
				hwnd = ::GetDesktopWindow();

			OleCreatePropertyFrame( hwnd, 0, 0, NULL, 1, &obj,
				cauuid.cElems, cauuid.pElems, 0, 0, NULL );

			CoTaskMemFree( cauuid.pElems );
		}
		p_spec->Release();
	}
}

HRESULT		CBaseGrapBuilder::ShowFilterSettings(HWND hOwner, IBaseFilter *pInFilter)
{
	if(pInFilter == NULL)
		return E_POINTER;
	HRESULT hr = S_OK;
	IAMVfwCompressDialogs * pVfwDlg = NULL;
	hr = pInFilter->QueryInterface(__uuidof(IAMVfwCompressDialogs),(void**) &pVfwDlg);
	if(pVfwDlg)
	{
		pVfwDlg->ShowDialog(VfwCompressDialog_Config,hOwner);
		pVfwDlg->Release();		
	}
	else
	{
		ISpecifyPropertyPages *pSpecify = NULL;
		hr = pInFilter->QueryInterface(IID_ISpecifyPropertyPages, (void **)&pSpecify);
		if (SUCCEEDED(hr)) 
		{
			FILTER_INFO FilterInfo;	
			memset(&FilterInfo, 0, sizeof(FILTER_INFO));
			pInFilter->QueryFilterInfo(&FilterInfo);

			CAUUID caGUID;
			pSpecify->GetPages(&caGUID);

			OleCreatePropertyFrame(
				hOwner,                   // Parent window
				0,                      // x (Reserved)
				0,                      // y (Reserved)
				FilterInfo.achName,     // Caption for the dialog box
				1,                      // Number of filters
				(IUnknown **)&pInFilter,  // Pointer to the filter 
				caGUID.cElems,          // Number of property pages
				caGUID.pElems,          // Pointer to property page CLSIDs
				0,                      // Locale identifier
				0,                      // Reserved
				NULL                    // Reserved
				);

			CoTaskMemFree(caGUID.pElems);
			FilterInfo.pGraph->Release();
		}

		if (pSpecify)
			pSpecify->Release();
	}


	return hr;
}
HRESULT		CBaseGrapBuilder::ShowFilterProperties(HWND hOwner, IBaseFilter *pInFilter, bool b_audio)
{
	if(m_pCaptureBuilder == NULL || pInFilter == NULL)
		return E_POINTER;
	HRESULT hr;
	/*
	* Video or audio capture filter page
	*/
	ShowPropertyPage( pInFilter,hOwner);

	/*
	* Audio capture pin
	*/
	if( m_pCaptureBuilder && b_audio )
	{
		IAMStreamConfig *p_SC;

		hr = m_pCaptureBuilder->FindInterface( &PIN_CATEGORY_CAPTURE,
			&MEDIATYPE_Audio, pInFilter,
			IID_IAMStreamConfig,
			(void **)&p_SC );
		if( SUCCEEDED(hr) )
		{
			ShowPropertyPage(p_SC,hOwner);
			p_SC->Release();
		}

		/*
		* TV Audio filter
		*/
		IAMTVAudio *p_TVA;
		HRESULT hr = m_pCaptureBuilder->FindInterface( &PIN_CATEGORY_CAPTURE,
			&MEDIATYPE_Audio, pInFilter,
			IID_IAMTVAudio, (void **)&p_TVA );
		if( SUCCEEDED(hr) )
		{
			ShowPropertyPage(p_TVA,hOwner);
			p_TVA->Release();
		}
	}

	/*
	* Video capture pin
	*/
	if( m_pCaptureBuilder && !b_audio )
	{
		IAMStreamConfig *p_SC;

		hr = m_pCaptureBuilder->FindInterface( &PIN_CATEGORY_CAPTURE,
			&MEDIATYPE_Interleaved,
			pInFilter,
			IID_IAMStreamConfig,
			(void **)&p_SC );
		if( FAILED(hr) )
		{
			hr = m_pCaptureBuilder->FindInterface( &PIN_CATEGORY_CAPTURE,
				&MEDIATYPE_Video,
				pInFilter,
				IID_IAMStreamConfig,
				(void **)&p_SC );
		}

		if( SUCCEEDED(hr) )
		{
			ShowPropertyPage(p_SC,hOwner);
			p_SC->Release();
		}
	}
	return hr;
}
HRESULT			CBaseGrapBuilder::ShowTunnerProperties(HWND hOwner, IBaseFilter *pInFilter, bool b_audio)
{
	HRESULT hr = E_UNEXPECTED;

	if( m_pCaptureBuilder && !b_audio )
	{
		IAMTVTuner *p_TV;
		hr = m_pCaptureBuilder->FindInterface( &PIN_CATEGORY_CAPTURE,
			&MEDIATYPE_Interleaved,
			pInFilter,
			IID_IAMTVTuner, (void **)&p_TV );
		if( FAILED(hr) )
		{
			hr = m_pCaptureBuilder->FindInterface( &PIN_CATEGORY_CAPTURE,
				&MEDIATYPE_Video,
				pInFilter,
				IID_IAMTVTuner,
				(void **)&p_TV );
		}

		if( SUCCEEDED(hr) )
		{
			ShowPropertyPage(p_TV,hOwner);
			p_TV->Release();
		}
	}
	return hr;
}
void CBaseGrapBuilder::ShowDeviceProperties(ICaptureGraphBuilder2 *p_capture_graph,							
					 IBaseFilter *p_device_filter,
					 HWND hPropertyOwner,
					 bool b_audio )
{
	HRESULT hr;
	if(p_capture_graph == NULL || p_device_filter == NULL)
		return ;
	/*
	* Video or audio capture filter page
	*/
	ShowPropertyPage( p_device_filter,hPropertyOwner);

	/*
	* Audio capture pin
	*/
	if( p_capture_graph && b_audio )
	{
		IAMStreamConfig *p_SC;


		hr = p_capture_graph->FindInterface( &PIN_CATEGORY_CAPTURE,
			&MEDIATYPE_Audio, p_device_filter,
			IID_IAMStreamConfig,
			(void **)&p_SC );
		if( SUCCEEDED(hr) )
		{
			ShowPropertyPage(p_SC,hPropertyOwner);
			p_SC->Release();
		}

		/*
		* TV Audio filter
		*/
		IAMTVAudio *p_TVA;
		HRESULT hr = p_capture_graph->FindInterface( &PIN_CATEGORY_CAPTURE,
			&MEDIATYPE_Audio, p_device_filter,
			IID_IAMTVAudio, (void **)&p_TVA );
		if( SUCCEEDED(hr) )
		{
			ShowPropertyPage(p_TVA,hPropertyOwner);
			p_TVA->Release();
		}
	}

	/*
	* Video capture pin
	*/
	if( p_capture_graph && !b_audio )
	{
		IAMStreamConfig *p_SC;


		hr = p_capture_graph->FindInterface( &PIN_CATEGORY_CAPTURE,
			&MEDIATYPE_Interleaved,
			p_device_filter,
			IID_IAMStreamConfig,
			(void **)&p_SC );
		if( FAILED(hr) )
		{
			hr = p_capture_graph->FindInterface( &PIN_CATEGORY_CAPTURE,
				&MEDIATYPE_Video,
				p_device_filter,
				IID_IAMStreamConfig,
				(void **)&p_SC );
		}

		if( SUCCEEDED(hr) )
		{
			ShowPropertyPage(p_SC,hPropertyOwner);
			p_SC->Release();
		}
	}
}
void CBaseGrapBuilder::ShowTunerProperties(ICaptureGraphBuilder2 *p_capture_graph,
										IBaseFilter *p_device_filter,
										HWND	hPropertyOwner,
										bool b_audio )
{
	HRESULT hr;

	if( p_capture_graph && !b_audio )
	{
		IAMTVTuner *p_TV;
		hr = p_capture_graph->FindInterface( &PIN_CATEGORY_CAPTURE,
			&MEDIATYPE_Interleaved,
			p_device_filter,
			IID_IAMTVTuner, (void **)&p_TV );
		if( FAILED(hr) )
		{
			hr = p_capture_graph->FindInterface( &PIN_CATEGORY_CAPTURE,
				&MEDIATYPE_Video,
				p_device_filter,
				IID_IAMTVTuner,
				(void **)&p_TV );
		}

		if( SUCCEEDED(hr) )
		{
			ShowPropertyPage(p_TV,hPropertyOwner);
			p_TV->Release();
		}
	}
}


#ifdef _DEBUGAddGraphToROT
HRESULT  CBaseGrapBuilder::AddGraphToROT()
{
	HRESULT hr;

	if (m_dwRegister != 0) return E_FAIL;

	CComPtr<IRunningObjectTable> pROT;
	if (FAILED(hr = GetRunningObjectTable(0, &pROT)))
		return hr;

	WCHAR wsz[128];
	swprintf(wsz, L"FilterGraph %08x pid %08x", (DWORD_PTR)m_pGraphBuilder, GetCurrentProcessId());

	CComPtr<IMoniker> pMoniker;
	if (FAILED(hr = CreateItemMoniker(L"!", wsz, &pMoniker))) 
		return hr;

	if (FAILED(hr = pROT->Register(0, m_pGraphBuilder, pMoniker, &m_dwRegister))) 
		return hr;


	return S_OK;
}
HRESULT  CBaseGrapBuilder::RemoveGraphFromROT()
{
	HRESULT hr;

	if (m_dwRegister == 0) return E_FAIL;

	CComPtr<IRunningObjectTable> pROT;
	if (FAILED(hr = GetRunningObjectTable(0, &pROT)))
		return hr;

	pROT->Revoke(m_dwRegister);

	m_dwRegister = 0;

	return S_OK;	
}
#endif

HRESULT  CBaseGrapBuilder::SetDefaultSyncClock()
{
	USES_CONVERSION;

	if(m_pGraphBuilder == NULL)
		return E_HANDLE;

	HRESULT hr = S_OK;

	ULONG cFetched = 1;
	IBaseFilter* pFilter = NULL;
	CComPtr<IEnumFilters>	pEnumFilters;
	CComPtr<IMediaFilter>	pMedia;
	CComPtr<IReferenceClock> pClock;

	hr = m_pGraphBuilder->EnumFilters(&pEnumFilters);
	while (cFetched && pEnumFilters)
	{
		hr = pEnumFilters->Next(1, &pFilter, &cFetched);
		if(cFetched == 0)
			break;		
		hr = pFilter->QueryInterface(__uuidof(IReferenceClock),(void**)&pClock);		
		SAFE_RELEASE(pFilter);
		if(pClock)
			break;
	}
	if( pClock )
	{
		hr = m_pGraphBuilder->QueryInterface(__uuidof(IMediaFilter),(void**)&pMedia);
		if(pMedia)
		{
			pMedia->SetSyncSource(pClock);
		}		
	}
	SAFE_RELEASE(pFilter);
	return hr;	
}






VIDEOINFOHEADER	 * CBaseGrapBuilder::GetVideoInfoHeader(AM_MEDIA_TYPE am)
{
	VIDEOINFOHEADER *pvih = new VIDEOINFOHEADER;
	if(am.formattype == FORMAT_MPEGVideo)
	{
		MPEG1VIDEOINFO *p0 = (MPEG1VIDEOINFO*)am.pbFormat;
		memcpy(pvih, &p0->hdr, sizeof(VIDEOINFOHEADER));
	}
	else if(am.formattype == FORMAT_MPEG2Video)
	{
		MPEG2VIDEOINFO *p1 = (MPEG2VIDEOINFO*)am.pbFormat;
		pvih->AvgTimePerFrame	= p1->hdr.AvgTimePerFrame;
		pvih->bmiHeader			= p1->hdr.bmiHeader;
		pvih->dwBitErrorRate	= p1->hdr.dwBitErrorRate;
		pvih->dwBitRate			= p1->hdr.dwBitRate;
		pvih->rcSource			= p1->hdr.rcSource;
		pvih->rcTarget			= p1->hdr.rcTarget;
	}
	else if(am.formattype == FORMAT_VideoInfo)
	{
		VIDEOINFOHEADER *p2 = (VIDEOINFOHEADER*)am.pbFormat;
		memcpy(pvih, p2, sizeof(VIDEOINFOHEADER));
	}
	else if(am.formattype == FORMAT_VideoInfo2)
	{
		VIDEOINFOHEADER2 *p3 = (VIDEOINFOHEADER2*)am.pbFormat;
		pvih->AvgTimePerFrame	= p3->AvgTimePerFrame;
		pvih->bmiHeader			= p3->bmiHeader;
		pvih->dwBitErrorRate	= p3->dwBitErrorRate;
		pvih->dwBitRate			= p3->dwBitRate;
		pvih->rcSource			= p3->rcSource;
		pvih->rcTarget			= p3->rcTarget;
	}
	else
	{
		delete pvih;
		pvih = NULL;
	}
	return pvih;
}
WAVEFORMATEX*	CBaseGrapBuilder::GetWaveFormatEx(AM_MEDIA_TYPE am)
{
	WAVEFORMATEX *pWfex = new WAVEFORMATEX;
	if(am.formattype == FORMAT_WaveFormatEx)
	{
		memcpy(pWfex, (WAVEFORMATEX*)am.pbFormat, sizeof(WAVEFORMATEX));
	}
	else
	{
		delete pWfex;
		return NULL;
	}
	return pWfex;
}
IBaseFilter *CBaseGrapBuilder::FindEncoderFilter(string szEncoderName,
							   bool b_audio)
{
	HRESULT hr;
	IBaseFilter *p_Encoder_filter= NULL;
	hr = this->CreateFilter_BySpecialCategoryAndName(b_audio ? CLSID_AudioCompressorCategory : CLSID_VideoCompressorCategory,
		szEncoderName.c_str(),
		FALSE,
		&p_Encoder_filter);
	if(FAILED(hr) || p_Encoder_filter == NULL)
	{
		hr = this->CreateFilter_BySpecialCategoryAndName( CLSID_LegacyAmFilterCategory,
			szEncoderName.c_str(),
			FALSE,
			&p_Encoder_filter);
		if(FAILED(hr) || p_Encoder_filter == NULL)
		{
			return NULL;
		}
	}
	return p_Encoder_filter;
}

IBaseFilter *
CBaseGrapBuilder::
	FindCaptureDevice(string *p_devicename, 
				   string *p_displayname,
                   list<string> *p_listdevices, 
				   list<string> *p_listdiplays, 
				   bool b_audio)
{
    IBaseFilter *p_base_filter = NULL;
    CComPtr<IMoniker> p_moniker;
    ULONG i_fetched;
    HRESULT hr;

    /* Create the system device enumerator */
    CComPtr<ICreateDevEnum> p_dev_enum;

    hr = CoCreateInstance( CLSID_SystemDeviceEnum, NULL, CLSCTX_INPROC,
                           IID_ICreateDevEnum, (void **)&p_dev_enum );
    if( FAILED(hr) )
    {
        ATLTRACE( "failed to create the device enumerator (0x%lx)", hr);
        return NULL;
    }

    /* Create an enumerator for the video capture devices */
    CComPtr<IEnumMoniker> p_class_enum;
    if( !b_audio )
        hr = p_dev_enum->CreateClassEnumerator( CLSID_VideoInputDeviceCategory,
                                                &p_class_enum, 0 );
    else
        hr = p_dev_enum->CreateClassEnumerator( CLSID_AudioInputDeviceCategory,
                                                &p_class_enum, 0 );
    if( FAILED(hr) )
    {
        ATLTRACE( "failed to create the class enumerator (0x%lx)", hr );
        return NULL;
    }

    /* If there are no enumerators for the requested type, then
     * CreateClassEnumerator will succeed, but p_class_enum will be NULL */
    if( p_class_enum == NULL )
    {
        ATLTRACE( "no capture device was detected" );
        return NULL;
    }

    /* Enumerate the devices */

    /* Note that if the Next() call succeeds but there are no monikers,
     * it will return S_FALSE (which is not a failure). Therefore, we check
     * that the return code is S_OK instead of using SUCCEEDED() macro. */

    while( p_class_enum->Next( 1, &p_moniker, &i_fetched ) == S_OK )
    {
        /* Getting the property page to get the device name */
        CComPtr<IPropertyBag> p_bag;
        hr = p_moniker->BindToStorage( 0, 0, IID_IPropertyBag,
                                       (void **)&p_bag );
        if( SUCCEEDED(hr) )
        {
            VARIANT var;
            var.vt = VT_BSTR;
            hr = p_bag->Read( L"FriendlyName", &var, NULL );
            if( SUCCEEDED(hr) )
            {
                int i_convert = WideCharToMultiByte(CP_ACP, 0, var.bstrVal,
                        SysStringLen(var.bstrVal), NULL, 0, NULL, NULL);
                char *p_buf = (char *)alloca( i_convert+1 ); p_buf[0] = 0;
                WideCharToMultiByte( CP_ACP, 0, var.bstrVal,
                        SysStringLen(var.bstrVal), p_buf, i_convert, NULL, NULL );
                SysFreeString(var.bstrVal);
                p_buf[i_convert] = '\0';
                if( p_listdevices ) p_listdevices->push_back( p_buf );

				LPOLESTR strMonikerName=0;
				TCHAR szMonikerName[256] = _T("");
				if(SUCCEEDED(p_moniker->GetDisplayName(NULL, NULL, &strMonikerName)))
				{
					USES_CONVERSION;
					_tcsncpy(szMonikerName, W2T(strMonikerName), 255);
					if(p_listdiplays)
						p_listdiplays->push_back(szMonikerName);
				}
				
                if( p_devicename && strcmp(p_devicename->c_str(), p_buf) == 0 )
                {
					if(p_displayname && p_displayname->size())
                    {
						if(strcmp(p_displayname->c_str() ,szMonikerName) == 0)
						{
							/* Bind Moniker to a filter object */
							hr = p_moniker->BindToObject( 0, 0, IID_IBaseFilter,
														  (void **)&p_base_filter );
							if( FAILED(hr) )
							{
								ATLTRACE( "couldn't bind moniker to filter "
										 "object (0x%lx)", hr );
								return NULL;
							}
							return p_base_filter;
						}
					}
					else
					{
						/* Bind Moniker to a filter object */
						hr = p_moniker->BindToObject( 0, 0, IID_IBaseFilter,
							(void **)&p_base_filter );
						if( FAILED(hr) )
						{
							ATLTRACE( "couldn't bind moniker to filter "
								"object (0x%lx)", hr );
							return NULL;
						}
						return p_base_filter;
					}
                }
            }
        }
		p_moniker.Release();
    }

    return NULL;
}
IBaseFilter *
CBaseGrapBuilder::
	FindEncoderDevice(string *p_devicename, 
				   string *p_displayname,
                   list<string> *p_listdevices, 
				   list<string> *p_listdiplays)
{
    IBaseFilter *p_base_filter = NULL;
    CComPtr<IMoniker> p_moniker;
    ULONG i_fetched;
    HRESULT hr;

    /* Create the system device enumerator */
    CComPtr<ICreateDevEnum> p_dev_enum;

    hr = CoCreateInstance( CLSID_SystemDeviceEnum, NULL, CLSCTX_INPROC,
                           IID_ICreateDevEnum, (void **)&p_dev_enum );
    if( FAILED(hr) )
    {
        ATLTRACE( "failed to create the device enumerator (0x%lx)", hr);
        return NULL;
    }

    /* Create an enumerator for the video capture devices */
    CComPtr<IEnumMoniker>	p_class_enum;
    hr = p_dev_enum->CreateClassEnumerator( KSCATEGORY_ENCODER,
                                                &p_class_enum, 0 );
    if( FAILED(hr) )
    {
        ATLTRACE( "failed to create the class enumerator (0x%lx)", hr );
        return NULL;
    }

    /* If there are no enumerators for the requested type, then
     * CreateClassEnumerator will succeed, but p_class_enum will be NULL */
    if( p_class_enum == NULL )
    {
        ATLTRACE( "no capture device was detected" );
        return NULL;
    }

    /* Enumerate the devices */

    /* Note that if the Next() call succeeds but there are no monikers,
     * it will return S_FALSE (which is not a failure). Therefore, we check
     * that the return code is S_OK instead of using SUCCEEDED() macro. */

    while( p_class_enum->Next( 1, &p_moniker, &i_fetched ) == S_OK )
    {
        /* Getting the property page to get the device name */
        CComPtr<IPropertyBag> p_bag;
        hr = p_moniker->BindToStorage( 0, 0, IID_IPropertyBag,
                                       (void **)&p_bag );
        if( SUCCEEDED(hr) )
        {
            VARIANT var;
            var.vt = VT_BSTR;
            hr = p_bag->Read( L"FriendlyName", &var, NULL );
            if( SUCCEEDED(hr) )
            {
                int i_convert = WideCharToMultiByte(CP_ACP, 0, var.bstrVal,
                        SysStringLen(var.bstrVal), NULL, 0, NULL, NULL);
                char *p_buf = (char *)alloca( i_convert+1 ); p_buf[0] = 0;
                WideCharToMultiByte( CP_ACP, 0, var.bstrVal,
                        SysStringLen(var.bstrVal), p_buf, i_convert, NULL, NULL );
                SysFreeString(var.bstrVal);
                p_buf[i_convert] = '\0';
                if( p_listdevices ) p_listdevices->push_back( p_buf );

				LPOLESTR strMonikerName=0;
				TCHAR szMonikerName[256] = _T("");
				if(SUCCEEDED(p_moniker->GetDisplayName(NULL, NULL, &strMonikerName)))
				{
					USES_CONVERSION;
					_tcsncpy(szMonikerName, W2T(strMonikerName), 255);
					if(p_listdiplays)
						p_listdiplays->push_back(szMonikerName);
				}
				
                if( p_devicename && strcmp(p_devicename->c_str(), p_buf) == 0 )
                {
					if(p_displayname && p_displayname->size())
                    {
						if(strcmp(p_displayname->c_str() ,szMonikerName) == 0)
						{
							/* Bind Moniker to a filter object */
							hr = p_moniker->BindToObject( 0, 0, IID_IBaseFilter,
														  (void **)&p_base_filter );
							if( FAILED(hr) )
							{
								ATLTRACE( "couldn't bind moniker to filter "
										 "object (0x%lx)", hr );
								return NULL;
							}
							return p_base_filter;
						}
					}
					else
					{
						/* Bind Moniker to a filter object */
						hr = p_moniker->BindToObject( 0, 0, IID_IBaseFilter,
							(void **)&p_base_filter );
						if( FAILED(hr) )
						{
							ATLTRACE( "couldn't bind moniker to filter "
								"object (0x%lx)", hr );
							return NULL;
						}
						return p_base_filter;
					}
                }
            }
        }
		p_moniker.Release();
    }

    return NULL;
}
HRESULT	CBaseGrapBuilder::ConnectFilter_RenderStream(IBaseFilter *p_source_filter,
												  IBaseFilter *p_Intermediate_filter,
												  IBaseFilter *p_capture_filter , 
												  bool b_audio,
												  bool b_preview)
{
	HRESULT hr = S_OK;
	
	
	GUID majortype = b_audio ? MEDIATYPE_Audio : MEDIATYPE_Video;
	GUID category  = b_preview ? PIN_CATEGORY_PREVIEW : PIN_CATEGORY_CAPTURE;
	
	if( FAILED(hr = this->m_pCaptureBuilder->
		RenderStream( &category, &majortype,
		p_source_filter,p_Intermediate_filter, p_capture_filter )) )
	{
		majortype = b_audio ? MEDIATYPE_AnalogAudio : MEDIATYPE_AnalogVideo;
		
		if( FAILED(hr = this->m_pCaptureBuilder->
			RenderStream( &category, &majortype,
			p_source_filter,p_Intermediate_filter, (IBaseFilter *)p_capture_filter )) )
		{
			majortype = MEDIATYPE_Interleaved;
			
			if( FAILED(hr = this->m_pCaptureBuilder->
				RenderStream( &category, &majortype,
				p_source_filter,p_Intermediate_filter, (IBaseFilter *)p_capture_filter )) )
			{
				return hr;
			}
		}
	}
	
	return S_OK;	
}
bool CBaseGrapBuilder::ConnectFilters_Custom(CBaseGrapBuilder *p_sys,
						   IBaseFilter *p_filter,
						   SampleCaptureFilter *p_capture_filter)
{
	HRESULT hr = S_OK;
	
    SampleCapturePin *p_input_pin = p_capture_filter->CustomGetPin();
	
	CComPtr<IEnumPins> p_enumpins;
	IPin *p_pin;
	
	if( S_OK != p_filter->EnumPins( &p_enumpins ) ) return false;
	
	while( S_OK == p_enumpins->Next( 1, &p_pin, NULL ) )
	{
		PIN_DIRECTION pin_dir;
		p_pin->QueryDirection( &pin_dir );
		
		if( pin_dir == PINDIR_OUTPUT &&
			p_sys->m_pGraphBuilder->ConnectDirect( p_pin, (IPin *)p_input_pin,
			0 ) == S_OK )
		{
			p_pin->Release();
			return true;
		}
		p_pin->Release();
	}
	
	return false;
}
bool CBaseGrapBuilder::ConnectFilters( CBaseGrapBuilder *p_sys, 
                            IBaseFilter *p_filter,
                            SampleCaptureFilter *p_capture_filter )
{
    SampleCapturePin *p_input_pin = p_capture_filter->CustomGetPin();

    AM_MEDIA_TYPE mediaType = p_input_pin->CustomGetMediaType();

    if( p_sys->m_pCaptureBuilder )
    {
		if( FAILED(p_sys->m_pCaptureBuilder->
			RenderStream( &PIN_CATEGORY_CAPTURE, &mediaType.majortype,
			p_filter, 0, (IBaseFilter *)p_capture_filter ) ))
        {
			if(!ConnectFilters_Custom(this, p_filter, p_capture_filter))
			{
				CComPtr<IEnumPins> p_enumpins;
				IPin *p_pin;
				
				if( S_OK != p_filter->EnumPins( &p_enumpins ) ) return false;
				
				while( S_OK == p_enumpins->Next( 1, &p_pin, NULL ) )
				{
					PIN_DIRECTION pin_dir;
					p_pin->QueryDirection( &pin_dir );
					
					if( pin_dir == PINDIR_OUTPUT &&
						p_sys->m_pGraphBuilder->ConnectDirect( p_pin, (IPin *)p_input_pin,
						0 ) == S_OK )
					{
						p_pin->Release();
						return true;
					}
					p_pin->Release();
				}
				
				return false;
			}
        }

        // Sort out all the possible video inputs
        // The class needs to be given the capture filters ANALOGVIDEO input pin
        CComPtr<IEnumPins> pins;
        if( ( mediaType.majortype == MEDIATYPE_Video ||
              mediaType.majortype == MEDIATYPE_Stream ) &&
            SUCCEEDED(p_filter->EnumPins(&pins)) )
        {
            IPin        *pP = 0;
            ULONG        n;
            PIN_INFO     pinInfo;
            BOOL         Found = FALSE;
            IKsPropertySet *pKs=0;
            GUID guid;
            DWORD dw;

            while( !Found && ( S_OK == pins->Next(1, &pP, &n) ) )
            {
				memset(&pinInfo, 0, sizeof(PIN_INFO));
                if( S_OK == pP->QueryPinInfo(&pinInfo) )
                {
                    // is this pin an ANALOGVIDEOIN input pin?
                    if( pinInfo.dir == PINDIR_INPUT &&
                        pP->QueryInterface( IID_IKsPropertySet,
                                            (void **)&pKs ) == S_OK )
                    {
                        if( pKs->Get( AMPROPSETID_Pin,
                                      AMPROPERTY_PIN_CATEGORY, NULL, 0,
                                      &guid, sizeof(GUID), &dw ) == S_OK )
                        {
                            if( guid == PIN_CATEGORY_ANALOGVIDEOIN )
                            {
                                // recursively search crossbar routes
                               
                                // found it
                                Found = TRUE;
                            }
                        }
                        pKs->Release();
                    }
                    pinInfo.pFilter->Release();
                }
                pP->Release();
            }
        }
        return true;
    }
    else
    {
        CComPtr<IEnumPins> p_enumpins;
        IPin *p_pin;

        if( S_OK != p_filter->EnumPins( &p_enumpins ) ) return false;

        while( S_OK == p_enumpins->Next( 1, &p_pin, NULL ) )
        {
            PIN_DIRECTION pin_dir;
            p_pin->QueryDirection( &pin_dir );

            if( pin_dir == PINDIR_OUTPUT &&
                p_sys->m_pGraphBuilder->ConnectDirect( p_pin, (IPin *)p_input_pin,
                                               0 ) == S_OK )
            {
                p_pin->Release();
                return true;
            }
            p_pin->Release();
        }

        return false;
    }
}
HRESULT			CBaseGrapBuilder::ConnectFilter_RenderStream_AnalogVideo(IBaseFilter *p_source_filter,
																	  IBaseFilter *p_Intermediate_filter,
																	  IBaseFilter *p_capture_filter)
{
	HRESULT hr = S_OK;
	
	
	GUID category  = PIN_CATEGORY_ANALOGVIDEOIN;
	GUID majortype = MEDIATYPE_AnalogVideo;
	if( FAILED(hr = this->m_pCaptureBuilder->
		RenderStream( &category, &majortype,
		p_source_filter,p_Intermediate_filter, p_capture_filter )) )
	{
		majortype = MEDIATYPE_Video;
		if( FAILED(hr = this->m_pCaptureBuilder->
			RenderStream( &category, &majortype,
			p_source_filter,p_Intermediate_filter, p_capture_filter )) )
		{
			category =PIN_CATEGORY_CAPTURE; 
			if( FAILED(hr = this->m_pCaptureBuilder->
				RenderStream( &category, &majortype,
				p_source_filter,p_Intermediate_filter, p_capture_filter )) )
			{
				majortype = MEDIATYPE_AnalogVideo;
				if( FAILED(hr = this->m_pCaptureBuilder->
					RenderStream( &category, &majortype,
					p_source_filter,p_Intermediate_filter, p_capture_filter )) )
				{
					return hr;
				}
			}
		}
	}
	
	return hr;
}
HRESULT		CBaseGrapBuilder::RemoveFilter_DownStream(IBaseFilter **ppInFilter)
{
	if(ppInFilter == NULL || *ppInFilter == NULL)
		return S_OK;
	HRESULT hr = S_OK;
	
	ULONG cFetched = 1;
	CComPtr<IEnumPins>	pEnumPins;
	IPin *pPin =  NULL;
	PIN_DIRECTION MyDir;
	
	hr =(*ppInFilter)->EnumPins(&pEnumPins);
	if(FAILED(hr))
		return hr;
	
	while (cFetched)
	{
		hr = pEnumPins->Next(1, &pPin, &cFetched);
		if(FAILED(hr) || pPin == NULL)
		{
			break;
		}
		hr = pPin->QueryDirection(&MyDir);
		if(FAILED(hr))
		{
			SAFE_RELEASE(pPin);
			continue;
		}
		if ( PINDIR_OUTPUT == MyDir)
		{
			CComPtr<IPin> pConn;
			hr = pPin->ConnectedTo(&pConn);
			if(SUCCEEDED(hr) && pConn != NULL)
			{
				PIN_INFO pi;
				memset(&pi, 0, sizeof(PIN_INFO));
				if(SUCCEEDED(hr = pConn->QueryPinInfo(&pi)))
				{
					RemoveFilter_DownStream(&pi.pFilter);
					FILTER_INFO fi;
					memset(&fi, 0, sizeof(FILTER_INFO));
					if(SUCCEEDED(hr = pi.pFilter->QueryFilterInfo(&fi)))
					{
						hr = fi.pGraph->RemoveFilter(pi.pFilter);
						SAFE_RELEASE(fi.pGraph);
					}
					SAFE_RELEASE(pi.pFilter);
				}
				hr = pConn->Disconnect();
				hr = pPin->Disconnect();
			}
			
		}
		SAFE_RELEASE(pPin);
	}
	
	return hr;
}
HRESULT			CBaseGrapBuilder::RemoveFilter_DownStream_NoRemoveSpecial1(IBaseFilter **ppInFilter, IBaseFilter **ppSpecialFilter)
{
	if(ppInFilter == NULL || *ppInFilter == NULL)
		return S_OK;
	HRESULT hr = S_OK;
	
	ULONG cFetched = 1;
	CComPtr<IEnumPins> pEnumPins;
	IPin *pPin =  NULL;
	PIN_DIRECTION MyDir;
	
	hr =(*ppInFilter)->EnumPins(&pEnumPins);
	if(FAILED(hr))
		return hr;
	
	while (cFetched)
	{
		hr = pEnumPins->Next(1, &pPin, &cFetched);
		if(FAILED(hr) || pPin == NULL)
		{
			break;
		}
		hr = pPin->QueryDirection(&MyDir);
		if(FAILED(hr))
		{
			SAFE_RELEASE(pPin);
			continue;
		}
		if ( PINDIR_OUTPUT == MyDir)
		{
			bool bDisconnect = true;
			CComPtr<IPin> pConn;
			hr = pPin->ConnectedTo(&pConn);
			if(SUCCEEDED(hr) && pConn != NULL)
			{
				PIN_INFO pi;
				memset(&pi, 0, sizeof(PIN_INFO));
				if(SUCCEEDED(hr = pConn->QueryPinInfo(&pi)))
				{
					if(pi.pFilter != *ppSpecialFilter)
					{
						RemoveFilter_DownStream_NoRemoveSpecial1(&pi.pFilter, ppSpecialFilter);
						FILTER_INFO fi;
						memset(&fi, 0, sizeof(FILTER_INFO));
						if(SUCCEEDED(hr = pi.pFilter->QueryFilterInfo(&fi)))
						{
							hr = fi.pGraph->RemoveFilter(pi.pFilter);
							SAFE_RELEASE(fi.pGraph);
						}
					}
					else
					{
						bDisconnect = false;
					}
					SAFE_RELEASE(pi.pFilter);
				}
				if(bDisconnect)
				{
					hr = pConn->Disconnect();
					hr = pPin->Disconnect();
				}
			}
			
		}
		SAFE_RELEASE(pPin);
	}
	
	return hr;
}
HRESULT			CBaseGrapBuilder::RemoveFilter_DisconAllPin(IBaseFilter **ppInFilter)
{
	if(ppInFilter == NULL || *ppInFilter == NULL)
		return S_OK;
	HRESULT hr = S_OK;
	
	ULONG cFetched = 1;
	CComPtr<IEnumPins> pEnumPins;
	IPin *pPin =  NULL;
	
	hr =(*ppInFilter)->EnumPins(&pEnumPins);
	if(FAILED(hr))
		return hr;
	FILTER_INFO fi;
	memset(&fi, 0, sizeof(FILTER_INFO));
	if(FAILED(hr = (*ppInFilter)->QueryFilterInfo(&fi)))
		return hr;

	while (cFetched)
	{
		hr = pEnumPins->Next(1, &pPin, &cFetched);
		if(FAILED(hr) || pPin == NULL)
		{
			break;
		}
		
		CComPtr<IPin> pConn;
		hr = pPin->ConnectedTo(&pConn);
		if(SUCCEEDED(hr) && pConn != NULL)
		{
			hr = fi.pGraph->Disconnect(pConn);
			hr = fi.pGraph->Disconnect(pPin);
		}
		SAFE_RELEASE(pPin);
	}
	SAFE_RELEASE(fi.pGraph);
	hr = RemoveFilter_Simple(ppInFilter);
	
	return hr;
}

size_t CBaseGrapBuilder::EnumDeviceCaps( CBaseGrapBuilder *p_this, IBaseFilter *p_filter,
                              int i_fourcc, int i_width, int i_height,float r_fps,
                              int i_channels, int i_samplespersec,
                              int i_bitspersample, AM_MEDIA_TYPE *mt,
                              size_t mt_max )
{
    CComPtr<IEnumPins>	p_enumpins;
    IPin *p_output_pin;
    size_t mt_count = 0;

    LONGLONG i_AvgTimePerFrame = 0;
    
    if( r_fps )
        i_AvgTimePerFrame = 10000000000L/(LONGLONG)(r_fps*1000.0f);

    if( FAILED(p_filter->EnumPins( &p_enumpins )) )
    {
        ATLTRACE(  "EnumDeviceCaps failed: no pin enumeration !");
        return 0;
    }

    while( S_OK == p_enumpins->Next( 1, &p_output_pin, NULL ) )
    {
        PIN_INFO info;
		memset(&info, 0, sizeof(PIN_INFO));
        if( S_OK == p_output_pin->QueryPinInfo( &info ) )
        {
            ATLTRACE(  "EnumDeviceCaps: %s pin: %S",
                     info.dir == PINDIR_INPUT ? "input" : "output",
                     info.achName );
            if( info.pFilter ) info.pFilter->Release();
        }

        p_output_pin->Release();
    }

    p_enumpins->Reset();

    while( !mt_count && p_enumpins->Next( 1, &p_output_pin, NULL ) == S_OK )
    {
        PIN_INFO info;
		memset(&info, 0, sizeof(PIN_INFO));
        if( S_OK == p_output_pin->QueryPinInfo( &info ) )
        {
            if( info.pFilter ) info.pFilter->Release();
            if( info.dir == PINDIR_INPUT )
            {
                p_output_pin->Release();
                continue;
            }
            ATLTRACE(  "EnumDeviceCaps: trying pin %S", info.achName );
        }

        AM_MEDIA_TYPE *p_mt;

        /*
        ** Configure pin with a default compatible media if possible
        */

        CComPtr<IAMStreamConfig> pSC;
        if( SUCCEEDED(p_output_pin->QueryInterface( IID_IAMStreamConfig,
                                            (void **)&pSC )) )
        {
			int old_slot_priority = 0;
            int piCount, piSize;
            if( SUCCEEDED(pSC->GetNumberOfCapabilities(&piCount, &piSize)) )
            {
                BYTE *pSCC= (BYTE *)CoTaskMemAlloc(piSize);
                if( NULL != pSCC )
                {
                    for( int i=0; i<piCount; ++i )
                    {
                        if( SUCCEEDED(pSC->GetStreamCaps(i, &p_mt, pSCC)) )
                        {
                            int i_current_fourcc = GetFourCCFromMediaType( *p_mt );
							int slot_priority =
								GetFourCCPriority(i_current_fourcc);
							
                            if( !i_current_fourcc || (i_fourcc && (i_current_fourcc != i_fourcc)) 
								|| slot_priority < old_slot_priority)
                            {
                                // incompatible or unrecognized chroma, try next media type
                                FreeMediaType( *p_mt );
                                CoTaskMemFree( (PVOID)p_mt );
                                continue;
                            }

                            if( GetAMMediaType(*p_mt) == AMTYPE_Video )
                            {
                                VIDEO_STREAM_CONFIG_CAPS *pVSCC = reinterpret_cast<VIDEO_STREAM_CONFIG_CAPS*>(pSCC);
                                VIDEOINFOHEADER *pVih = reinterpret_cast<VIDEOINFOHEADER*>(p_mt->pbFormat);

                                if( i_AvgTimePerFrame )
                                {
                                    if( pVSCC->MinFrameInterval > i_AvgTimePerFrame
                                      || i_AvgTimePerFrame > pVSCC->MaxFrameInterval )
                                    {
										if(i_AvgTimePerFrame == 333333 &&
											pVSCC->MinFrameInterval != 333666 &&
											pVSCC->MinFrameInterval != 333667)
                                        {
											// required frame rate not compatible, try next media type
											FreeMediaType( *p_mt );
											CoTaskMemFree( (PVOID)p_mt );
											continue;
										}
                                    }
                                    pVih->AvgTimePerFrame = i_AvgTimePerFrame;
                                }

                                if( i_width )
                                {
                                    if( i_width % pVSCC->OutputGranularityX
                                     || pVSCC->MinOutputSize.cx > i_width
                                     || i_width > pVSCC->MaxOutputSize.cx )
                                    {
                                        // required width not compatible, try next media type
										if(pVih->bmiHeader.biWidth != i_width)
                                        {
											FreeMediaType( *p_mt );
											CoTaskMemFree( (PVOID)p_mt );
											continue;
										}
                                    }
                                    pVih->bmiHeader.biWidth = i_width;
                                }

                                if( i_height )
                                {
                                    if( i_height % pVSCC->OutputGranularityY
                                     || pVSCC->MinOutputSize.cy > i_height 
                                     || i_height > pVSCC->MaxOutputSize.cy )
                                    {
                                        // required height not compatible, try next media type
										if(pVih->bmiHeader.biHeight != i_height)
                                        {
											FreeMediaType( *p_mt );
											CoTaskMemFree( (PVOID)p_mt );
											continue;
										}
                                    }
                                    pVih->bmiHeader.biHeight = i_height;
                                }

                                // Set the sample size and image size.
                                // (Round the image width up to a DWORD boundary.)
                                p_mt->lSampleSize = pVih->bmiHeader.biSizeImage = 
                                    ((pVih->bmiHeader.biWidth + 3) & ~3) *
                                    pVih->bmiHeader.biHeight * (pVih->bmiHeader.biBitCount>>3);

                                // no cropping, use full video input buffer
                                memset(&(pVih->rcSource), 0, sizeof(RECT));
                                memset(&(pVih->rcTarget), 0, sizeof(RECT));

                                // select this format as default
                                if( SUCCEEDED( pSC->SetFormat(p_mt) ) )
                                {
                                    ATLTRACE(  "EnumDeviceCaps: input pin video format configured");
									old_slot_priority = slot_priority;
									if(old_slot_priority == 9)
										i = piCount;
                                }
                                else FreeMediaType( *p_mt );
                            }
                            else if( p_mt->majortype == MEDIATYPE_Audio
                                    && p_mt->formattype == FORMAT_WaveFormatEx )
                            {
                                AUDIO_STREAM_CONFIG_CAPS *pASCC = reinterpret_cast<AUDIO_STREAM_CONFIG_CAPS*>(pSCC);
                                WAVEFORMATEX *pWfx = reinterpret_cast<WAVEFORMATEX*>(p_mt->pbFormat);
							
                                if( i_channels )
                                {
                                    if( i_channels % pASCC->ChannelsGranularity
                                     || (unsigned int)i_channels < pASCC->MinimumChannels
                                     || (unsigned int)i_channels > pASCC->MaximumChannels )
                                    {
										if(i_channels != pWfx->nChannels)
										{
											// required channels not compatible, try next media type
											FreeMediaType( *p_mt );
											CoTaskMemFree( (PVOID)p_mt );
											continue;
										}
                                    }
                                    pWfx->nChannels = i_channels;
                                }

                                if( i_samplespersec )
                                {
                                    if( i_samplespersec % pASCC->BitsPerSampleGranularity
                                     || (unsigned int)i_samplespersec < pASCC->MinimumSampleFrequency
                                     || (unsigned int)i_samplespersec > pASCC->MaximumSampleFrequency )
                                    {
                                        // required sampling rate not compatible, try next media type
										if(i_samplespersec != pWfx->nSamplesPerSec)
										{
											FreeMediaType( *p_mt );
											CoTaskMemFree( (PVOID)p_mt );
											continue;
										}
                                    }
                                    pWfx->nSamplesPerSec = i_samplespersec;
                                }

                                if( i_bitspersample )
                                {
                                    if( i_bitspersample % pASCC->BitsPerSampleGranularity
                                     || (unsigned int)i_bitspersample < pASCC->MinimumBitsPerSample
                                     || (unsigned int)i_bitspersample > pASCC->MaximumBitsPerSample )
                                    {
                                        // required sample size not compatible, try next media type
										if(i_bitspersample != pWfx->wBitsPerSample)
										{
											FreeMediaType( *p_mt );
											CoTaskMemFree( (PVOID)p_mt );
											continue;
										}
                                    }
                                    pWfx->wBitsPerSample = i_bitspersample;
                                }

                                // select this format as default
                                if( SUCCEEDED( pSC->SetFormat(p_mt) ) )
                                {
                                    ATLTRACE(  "EnumDeviceCaps: input pin default format configured");
                                    old_slot_priority = slot_priority;
									if(old_slot_priority == 9)
										i = piCount;
                                }
                            }
                            FreeMediaType( *p_mt );
                            CoTaskMemFree( (PVOID)p_mt );
                        }
                    }
                    CoTaskMemFree( (LPVOID)pSCC );
                }
            }
        }

        /*
        ** Probe pin for available medias (may be a previously configured one)
        */

        CComPtr<IEnumMediaTypes> p_enummt;
		if( FAILED( p_output_pin->EnumMediaTypes( &p_enummt ) ) )
        {
            p_output_pin->Release();
            continue;
        }
		p_enummt->Reset();
		ULONG ul = 1;
		bool bCustomAddMediaType = false;
        while( p_enummt->Next( 1, &p_mt, &ul ) == S_OK && 0 != ul)
        {
            int i_current_fourcc = GetFourCCFromMediaType( *p_mt );
            //if( i_current_fourcc && p_mt->majortype == MEDIATYPE_Video
            //    && p_mt->formattype == FORMAT_VideoInfo )
            if( i_current_fourcc && GetAMMediaType(*p_mt) == AMTYPE_Video )
            {
				VIDEOINFOHEADER * pVIH	= AMGetVideoInfoHeader(*p_mt);
				if(pVIH != NULL)
				{
					int i_current_width		= pVIH->bmiHeader.biWidth;
					int i_current_height	= pVIH->bmiHeader.biHeight;
					LONGLONG i_current_atpf = pVIH->AvgTimePerFrame;
					if(i_current_atpf == 333666 ||
						i_current_atpf == 333667)
						i_current_atpf = 333333;

					if( i_current_height < 0 )
						i_current_height = -i_current_height; 

					ATLTRACE(  "EnumDeviceCaps: input pin "
							 "accepts chroma: %4.4s, width:%i, height:%i, fps:%f\n",
							 (char *)&i_current_fourcc, i_current_width,
							 i_current_height, (10000000.0f/((float)i_current_atpf)) );

					if( ( !i_fourcc || i_fourcc == i_current_fourcc ) &&
						( !i_width || i_width == i_current_width ) &&
						( !i_height || i_height == i_current_height ) &&
						( !i_AvgTimePerFrame || i_AvgTimePerFrame == i_current_atpf ) &&
						mt_count < mt_max )
					{
						/* Pick match */
						mt[mt_count++] = *p_mt;
					}
					else
					{
						if(!bCustomAddMediaType && !mt_count)
						{
							if(p_mt->formattype == FORMAT_MPEGVideo)
							{
								MPEG1VIDEOINFO *p0 = (MPEG1VIDEOINFO*)p_mt->pbFormat;
								if(i_width)
									p0->hdr.bmiHeader.biWidth = i_width;
								if(i_height)
									p0->hdr.bmiHeader.biHeight= i_height;
								p0->hdr.bmiHeader.biSizeImage = helper_GetBMISizeImage(p0->hdr.bmiHeader);
								p0->hdr.rcSource.right = i_width;
								p0->hdr.rcSource.bottom= i_height;
								p0->hdr.rcTarget.right = i_width;
								p0->hdr.rcTarget.bottom= i_height;
								if(i_AvgTimePerFrame)
									p0->hdr.AvgTimePerFrame = i_AvgTimePerFrame;
								mt[mt_count++] = *p_mt;
								bCustomAddMediaType = true;
							}
							else if(p_mt->formattype == FORMAT_MPEG2Video)
							{
								MPEG2VIDEOINFO *p1 = (MPEG2VIDEOINFO*)p_mt->pbFormat;
								if(i_width)
									p1->hdr.bmiHeader.biWidth = i_width;
								if(i_height)
									p1->hdr.bmiHeader.biHeight= i_height;
								if(i_AvgTimePerFrame)
									p1->hdr.AvgTimePerFrame = i_AvgTimePerFrame;
								p1->hdr.bmiHeader.biSizeImage = helper_GetBMISizeImage(p1->hdr.bmiHeader);
								p1->hdr.rcSource.right = i_width;
								p1->hdr.rcSource.bottom= i_height;
								p1->hdr.rcTarget.right = i_width;
								p1->hdr.rcTarget.bottom= i_height;
								mt[mt_count++] = *p_mt;
								bCustomAddMediaType = true;
							}
							else if(p_mt->formattype == FORMAT_VideoInfo)
							{
								VIDEOINFOHEADER *p2 = (VIDEOINFOHEADER*)p_mt->pbFormat;
								if(i_width)
									p2->bmiHeader.biWidth = i_width;
								if(i_height)
									p2->bmiHeader.biHeight= i_height;
								if(i_AvgTimePerFrame)
									p2->AvgTimePerFrame = i_AvgTimePerFrame;
								p2->bmiHeader.biSizeImage = helper_GetBMISizeImage(p2->bmiHeader);
								p2->rcSource.right = i_width;
								p2->rcSource.bottom= i_height;
								p2->rcTarget.right = i_width;
								p2->rcTarget.bottom= i_height;
								mt[mt_count++] = *p_mt;
								bCustomAddMediaType = true;
							}
							else if(p_mt->formattype == FORMAT_VideoInfo2)
							{
								VIDEOINFOHEADER2 *p3 = (VIDEOINFOHEADER2*)p_mt->pbFormat;
								if(i_width)
									p3->bmiHeader.biWidth = i_width;
								if(i_height)
									p3->bmiHeader.biHeight= i_height;
								if(i_AvgTimePerFrame)
									p3->AvgTimePerFrame = i_AvgTimePerFrame;
								p3->bmiHeader.biSizeImage = helper_GetBMISizeImage(p3->bmiHeader);
								p3->rcSource.right = i_width;
								p3->rcSource.bottom= i_height;
								p3->rcTarget.right = i_width;
								p3->rcTarget.bottom= i_height;
								mt[mt_count++] = *p_mt;
								bCustomAddMediaType = true;
							}

						}
						else
						FreeMediaType( *p_mt );
					}

					delete pVIH;
				}
				else
					FreeMediaType( *p_mt );

            }
            else if( i_current_fourcc && p_mt->majortype == MEDIATYPE_Audio 
                    && p_mt->formattype == FORMAT_WaveFormatEx)
            {
                int i_current_channels =
                    ((WAVEFORMATEX *)p_mt->pbFormat)->nChannels;
                int i_current_samplespersec =
                    ((WAVEFORMATEX *)p_mt->pbFormat)->nSamplesPerSec;
                int i_current_bitspersample =
                    ((WAVEFORMATEX *)p_mt->pbFormat)->wBitsPerSample;

                ATLTRACE(  "EnumDeviceCaps: input pin "
                         "accepts format: %4.4s, channels:%i, "
                         "samples/sec:%i bits/sample:%i\n",
                         (char *)&i_current_fourcc, i_current_channels,
                         i_current_samplespersec, i_current_bitspersample);

                if( (!i_channels || i_channels == i_current_channels) &&
                    (!i_samplespersec ||
                     i_samplespersec == i_current_samplespersec) &&
                    (!i_bitspersample ||
                     i_bitspersample == i_current_bitspersample) &&
                    mt_count < mt_max )
                {
                    /* Pick  match */
                    mt[mt_count++] = *p_mt;

                    /* Setup a few properties like the audio latency */
                    IAMBufferNegotiation *p_ambuf;
                    if( SUCCEEDED( p_output_pin->QueryInterface(
                          IID_IAMBufferNegotiation, (void **)&p_ambuf ) ) )
                    {
                        ALLOCATOR_PROPERTIES AllocProp;
                        AllocProp.cbAlign = -1;

                        /* 100 ms of latency */
                        AllocProp.cbBuffer = i_current_channels *
                          i_current_samplespersec *
                          i_current_bitspersample / 8 / 10;

                        AllocProp.cbPrefix = -1;
                        AllocProp.cBuffers = -1;
                        p_ambuf->SuggestAllocatorProperties( &AllocProp );
                        p_ambuf->Release();
                    }
                }
                else FreeMediaType( *p_mt );
            }
            else if( i_current_fourcc && p_mt->majortype == MEDIATYPE_Stream )
            {
                ATLTRACE(  "EnumDeviceCaps: input pin "
                         "accepts stream format: %4.4s",
                         (char *)&i_current_fourcc );

                if( ( !i_fourcc || i_fourcc == i_current_fourcc ) &&
                    mt_count < mt_max )
                {
                    /* Pick match */
                    mt[mt_count++] = *p_mt;
                    i_fourcc = i_current_fourcc;
                }
                else FreeMediaType( *p_mt );
            }
            else
            {
                char *psz_type = "unknown";
                if( p_mt->majortype == MEDIATYPE_Video ) psz_type = "video";
                if( p_mt->majortype == MEDIATYPE_Audio ) psz_type = "audio";
                if( p_mt->majortype == MEDIATYPE_Stream ) psz_type = "stream";
                ATLTRACE(  "EnumDeviceCaps: input pin media: unknown format "
                         "(%s %4.4s)", psz_type, (char *)&p_mt->subtype );
                FreeMediaType( *p_mt );
            }
            CoTaskMemFree( (PVOID)p_mt );
        }

        p_enummt.Release();
        p_output_pin->Release();
    }

    return mt_count;
}
size_t CBaseGrapBuilder::EnumDeviceCaps( CBaseGrapBuilder *p_this, IPin *p_pin,
                              int i_fourcc, int i_width, int i_height,float r_fps,
                              int i_channels, int i_samplespersec,
                              int i_bitspersample, AM_MEDIA_TYPE *mt,
                              size_t mt_max )
{
	if(p_pin == NULL)
		return 0;
    IPin *p_output_pin = p_pin;
    CComPtr<IEnumMediaTypes>	p_enummt;
    size_t mt_count = 0;

    LONGLONG i_AvgTimePerFrame = 0;
    if( r_fps )
        i_AvgTimePerFrame = 10000000000L/(LONGLONG)(r_fps*1000.0f);
	do
    {
        PIN_INFO info;
		memset(&info, 0, sizeof(PIN_INFO));
        if( S_OK == p_output_pin->QueryPinInfo( &info ) )
        {
            if( info.pFilter ) info.pFilter->Release();
            if( info.dir == PINDIR_INPUT )
            {
                break;
            }
            ATLTRACE(  "EnumDeviceCaps: trying pin %S", info.achName );
        }

        AM_MEDIA_TYPE *p_mt;

        /*
        ** Configure pin with a default compatible media if possible
        */

        CComPtr<IAMStreamConfig>	pSC;
        if( SUCCEEDED(p_output_pin->QueryInterface( IID_IAMStreamConfig,
                                            (void **)&pSC )) )
        {
			int old_slot_priority = 0;
			int piCount, piSize;
            if( SUCCEEDED(pSC->GetNumberOfCapabilities(&piCount, &piSize)) )
            {
                BYTE *pSCC= (BYTE *)CoTaskMemAlloc(piSize);
                if( NULL != pSCC )
                {
                    for( int i=0; i<piCount; ++i )
                    {
                        if( SUCCEEDED(pSC->GetStreamCaps(i, &p_mt, pSCC)) )
                        {
                            int i_current_fourcc = GetFourCCFromMediaType( *p_mt );
							int slot_priority =
								GetFourCCPriority(i_current_fourcc);
							
                            if( !i_current_fourcc || (i_fourcc && (i_current_fourcc != i_fourcc)) 
								|| slot_priority < old_slot_priority)
                            {
                                // incompatible or unrecognized chroma, try next media type
                                FreeMediaType( *p_mt );
                                CoTaskMemFree( (PVOID)p_mt );
                                continue;
                            }

                            if( MEDIATYPE_Video == p_mt->majortype
                                    && FORMAT_VideoInfo == p_mt->formattype )
                            {
                                VIDEO_STREAM_CONFIG_CAPS *pVSCC = reinterpret_cast<VIDEO_STREAM_CONFIG_CAPS*>(pSCC);
                                VIDEOINFOHEADER *pVih = reinterpret_cast<VIDEOINFOHEADER*>(p_mt->pbFormat);

                                if( i_AvgTimePerFrame )
                                {
                                    if( pVSCC->MinFrameInterval > i_AvgTimePerFrame
                                      || i_AvgTimePerFrame > pVSCC->MaxFrameInterval )
                                    {
                                        // required frame rate not compatible, try next media type
                                        FreeMediaType( *p_mt );
                                        CoTaskMemFree( (PVOID)p_mt );
                                        continue;
                                    }
                                    pVih->AvgTimePerFrame = i_AvgTimePerFrame;
                                }

                                if( i_width )
                                {
                                    if( i_width % pVSCC->OutputGranularityX
                                     || pVSCC->MinOutputSize.cx > i_width
                                     || i_width > pVSCC->MaxOutputSize.cx )
                                    {
                                        // required width not compatible, try next media type
										if(pVih->bmiHeader.biWidth != i_width)
                                        {
											FreeMediaType( *p_mt );
											CoTaskMemFree( (PVOID)p_mt );
											continue;
										}
                                    }
                                    pVih->bmiHeader.biWidth = i_width;
                                }

                                if( i_height )
                                {
                                    if( i_height % pVSCC->OutputGranularityY
                                     || pVSCC->MinOutputSize.cy > i_height 
                                     || i_height > pVSCC->MaxOutputSize.cy )
                                    {
                                        // required height not compatible, try next media type
										if(pVih->bmiHeader.biHeight != i_height)
                                        {
											FreeMediaType( *p_mt );
											CoTaskMemFree( (PVOID)p_mt );
											continue;
										}
                                    }
                                    pVih->bmiHeader.biHeight = i_height;
                                }

                                // Set the sample size and image size.
                                // (Round the image width up to a DWORD boundary.)
                                p_mt->lSampleSize = pVih->bmiHeader.biSizeImage = 
                                    ((pVih->bmiHeader.biWidth + 3) & ~3) *
                                    pVih->bmiHeader.biHeight * (pVih->bmiHeader.biBitCount>>3);

                                // no cropping, use full video input buffer
                                memset(&(pVih->rcSource), 0, sizeof(RECT));
                                memset(&(pVih->rcTarget), 0, sizeof(RECT));

                                // select this format as default
                                if( SUCCEEDED( pSC->SetFormat(p_mt) ) )
                                {
                                    ATLTRACE(  "EnumDeviceCaps: input pin video format configured");
                                    // no need to check any more media types 
                                    old_slot_priority = slot_priority;
									if(old_slot_priority == 9)
										i = piCount;
                                }
                                else FreeMediaType( *p_mt );
                            }
                            else if( p_mt->majortype == MEDIATYPE_Audio
                                    && p_mt->formattype == FORMAT_WaveFormatEx )
                            {
                                AUDIO_STREAM_CONFIG_CAPS *pASCC = reinterpret_cast<AUDIO_STREAM_CONFIG_CAPS*>(pSCC);
                                WAVEFORMATEX *pWfx = reinterpret_cast<WAVEFORMATEX*>(p_mt->pbFormat);
							
                                if( i_channels )
                                {
                                    if( i_channels % pASCC->ChannelsGranularity
                                     || (unsigned int)i_channels < pASCC->MinimumChannels
                                     || (unsigned int)i_channels > pASCC->MaximumChannels )
                                    {
										if(i_channels != pWfx->nChannels)
										{
											// required channels not compatible, try next media type
											FreeMediaType( *p_mt );
											CoTaskMemFree( (PVOID)p_mt );
											continue;
										}
                                    }
                                    pWfx->nChannels = i_channels;
                                }

                                if( i_samplespersec )
                                {
                                    if( i_samplespersec % pASCC->BitsPerSampleGranularity
                                     || (unsigned int)i_samplespersec < pASCC->MinimumSampleFrequency
                                     || (unsigned int)i_samplespersec > pASCC->MaximumSampleFrequency )
                                    {
                                        // required sampling rate not compatible, try next media type
										if(i_samplespersec != pWfx->nSamplesPerSec)
										{
											FreeMediaType( *p_mt );
											CoTaskMemFree( (PVOID)p_mt );
											continue;
										}
                                    }
                                    pWfx->nSamplesPerSec = i_samplespersec;
                                }

                                if( i_bitspersample )
                                {
                                    if( i_bitspersample % pASCC->BitsPerSampleGranularity
                                     || (unsigned int)i_bitspersample < pASCC->MinimumBitsPerSample
                                     || (unsigned int)i_bitspersample > pASCC->MaximumBitsPerSample )
                                    {
                                        // required sample size not compatible, try next media type
										if(i_bitspersample != pWfx->wBitsPerSample)
										{
											FreeMediaType( *p_mt );
											CoTaskMemFree( (PVOID)p_mt );
											continue;
										}
                                    }
                                    pWfx->wBitsPerSample = i_bitspersample;
                                }

                                // select this format as default
                                if( SUCCEEDED( pSC->SetFormat(p_mt) ) )
                                {
                                    ATLTRACE(  "EnumDeviceCaps: input pin default format configured");
                                    // no need to check any more media types 
                                    old_slot_priority = slot_priority;
									if(old_slot_priority == 9)
										i = piCount;
                                }
                            }
                            FreeMediaType( *p_mt );
                            CoTaskMemFree( (PVOID)p_mt );
                        }
                    }
                    CoTaskMemFree( (LPVOID)pSCC );
                }
            }
        }

        /*
        ** Probe pin for available medias (may be a previously configured one)
        */

        if( FAILED( p_output_pin->EnumMediaTypes( &p_enummt ) ) )
        {
            break;
        }
		p_enummt->Reset();
		ULONG ul = 1;
        while( p_enummt->Next( 1, &p_mt, &ul ) == S_OK && 0 != ul)
        {
            int i_current_fourcc = GetFourCCFromMediaType( *p_mt );
            if( i_current_fourcc && p_mt->majortype == MEDIATYPE_Video
                && p_mt->formattype == FORMAT_VideoInfo )
            {
                int i_current_width = ((VIDEOINFOHEADER *)p_mt->pbFormat)->bmiHeader.biWidth;
                int i_current_height = ((VIDEOINFOHEADER *)p_mt->pbFormat)->bmiHeader.biHeight;
                LONGLONG i_current_atpf = ((VIDEOINFOHEADER *)p_mt->pbFormat)->AvgTimePerFrame;

                if( i_current_height < 0 )
                    i_current_height = -i_current_height; 

                ATLTRACE(  "EnumDeviceCaps: input pin "
                         "accepts chroma: %4.4s, width:%i, height:%i, fps:%f",
                         (char *)&i_current_fourcc, i_current_width,
                         i_current_height, (10000000.0f/((float)i_current_atpf)) );

                if( ( !i_fourcc || i_fourcc == i_current_fourcc ) &&
                    ( !i_width || i_width == i_current_width ) &&
                    ( !i_height || i_height == i_current_height ) &&
                    ( !i_AvgTimePerFrame || i_AvgTimePerFrame == i_current_atpf ) &&
                    mt_count < mt_max )
                {
                    /* Pick match */
                    mt[mt_count++] = *p_mt;
                }
                else FreeMediaType( *p_mt );
            }
            else if( i_current_fourcc && p_mt->majortype == MEDIATYPE_Audio 
                    && p_mt->formattype == FORMAT_WaveFormatEx)
            {
                int i_current_channels =
                    ((WAVEFORMATEX *)p_mt->pbFormat)->nChannels;
                int i_current_samplespersec =
                    ((WAVEFORMATEX *)p_mt->pbFormat)->nSamplesPerSec;
                int i_current_bitspersample =
                    ((WAVEFORMATEX *)p_mt->pbFormat)->wBitsPerSample;

                ATLTRACE(  "EnumDeviceCaps: input pin "
                         "accepts format: %4.4s, channels:%i, "
                         "samples/sec:%i bits/sample:%i",
                         (char *)&i_current_fourcc, i_current_channels,
                         i_current_samplespersec, i_current_bitspersample);

                if( (!i_channels || i_channels == i_current_channels) &&
                    (!i_samplespersec ||
                     i_samplespersec == i_current_samplespersec) &&
                    (!i_bitspersample ||
                     i_bitspersample == i_current_bitspersample) &&
                    mt_count < mt_max )
                {
                    /* Pick  match */
                    mt[mt_count++] = *p_mt;

                    /* Setup a few properties like the audio latency */
                    IAMBufferNegotiation *p_ambuf;
                    if( SUCCEEDED( p_output_pin->QueryInterface(
                          IID_IAMBufferNegotiation, (void **)&p_ambuf ) ) )
                    {
                        ALLOCATOR_PROPERTIES AllocProp;
                        AllocProp.cbAlign = -1;

                        /* 100 ms of latency */
                        AllocProp.cbBuffer = i_current_channels *
                          i_current_samplespersec *
                          i_current_bitspersample / 8 / 10;

                        AllocProp.cbPrefix = -1;
                        AllocProp.cBuffers = -1;
                        p_ambuf->SuggestAllocatorProperties( &AllocProp );
                        p_ambuf->Release();
                    }
                }
                else FreeMediaType( *p_mt );
            }
            else if( i_current_fourcc && p_mt->majortype == MEDIATYPE_Stream )
            {
                ATLTRACE(  "EnumDeviceCaps: input pin "
                         "accepts stream format: %4.4s",
                         (char *)&i_current_fourcc );

                if( ( !i_fourcc || i_fourcc == i_current_fourcc ) &&
                    mt_count < mt_max )
                {
                    /* Pick match */
                    mt[mt_count++] = *p_mt;
                    i_fourcc = i_current_fourcc;
                }
                else FreeMediaType( *p_mt );
            }
            else
            {
                char *psz_type = "unknown";
                if( p_mt->majortype == MEDIATYPE_Video ) psz_type = "video";
                if( p_mt->majortype == MEDIATYPE_Audio ) psz_type = "audio";
                if( p_mt->majortype == MEDIATYPE_Stream ) psz_type = "stream";
                ATLTRACE(  "EnumDeviceCaps: input pin media: unknown format "
                         "(%s %4.4s)", psz_type, (char *)&p_mt->subtype );
				if( ( !i_fourcc || i_fourcc == i_current_fourcc ) &&
                    mt_count < mt_max )
                {
                    /* Pick match */
                    mt[mt_count++] = *p_mt;
                    i_fourcc = i_current_fourcc;
                }
                else FreeMediaType( *p_mt );
                //FreeMediaType( *p_mt );
            }
            CoTaskMemFree( (PVOID)p_mt );
        }

		
		return mt_count;

   }while(false);

    return 0;
}
HRESULT	CBaseGrapBuilder::DestructStream()
{
	for(int i = 0; i < i_streams; i ++)
	{
		if(pp_streams[i])
		{
			RemoveFilter_Simple((IBaseFilter**)& pp_streams[i]->p_capture_filter);
			RemoveFilter_Simple((IBaseFilter**)& pp_streams[i]->p_encoder_filter);
			RemoveFilter_Simple((IBaseFilter**)& pp_streams[i]->p_device_filter);
			//SAFE_RELEASE(pp_streams[i]->p_capture_filter);
			//SAFE_RELEASE(pp_streams[i]->p_encoder_filter);
			//SAFE_RELEASE(pp_streams[i]->p_device_filter);
			long lref = pp_streams[i]->p_capture_filter->Release();
			if(pp_streams[i]->p_encoder_filter)
				lref = pp_streams[i]->p_encoder_filter->Release();
			lref = pp_streams[i]->p_device_filter->Release();

			
			delete pp_streams[i];
		}
	}
	SAFE_FREE(pp_streams);

	pp_streams = NULL;
	i_streams  = 0;
	
	return S_OK;
}
HRESULT CBaseGrapBuilder::ShowFilterSettings(HWND hOwner, FilterSettingType type,
						   bool b_audio)
{
	for(int i = 0; i < i_streams; i ++)
	{
		if(pp_streams[i] && pp_streams[i]->b_audio == b_audio)
		{
			switch(type)
			{
			case FilterSettingType_Device:
				{
					if(pp_streams[i]->p_device_filter)
						ShowFilterSettings(hOwner, pp_streams[i]->p_device_filter);
				}
				break;
			case FilterSettingType_Encode:
				{
					if(pp_streams[i]->p_encoder_filter)
						ShowFilterSettings(hOwner, pp_streams[i]->p_encoder_filter);
				}
				break;
			default:
				break;
			}	
		}
	}
	return S_OK;
}
HRESULT	CBaseGrapBuilder::AddStreamByPin(IPin* pInPin)
{
	AM_MEDIA_TYPE media_types[MAX_MEDIA_TYPES];
    size_t media_count =
        EnumDeviceCaps( this, pInPin, 0,
		0, 0, 0,
		0,
		0, 
		0,
		media_types, MAX_MEDIA_TYPES );
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
	SampleCaptureFilter *p_capture_filter = NULL;
	do {
		p_capture_filter =
			new SampleCaptureFilter( this, mt, mt_count );
		if(FAILED(AddFilter_Simple(NULL, (IBaseFilter**)&p_capture_filter)))
			break;
		if(FAILED(m_pGraphBuilder->Connect(pInPin, p_capture_filter->CustomGetPin())))
			break;
		CDShowStream dshow_stream;
		dshow_stream.b_audio		  = false;
        dshow_stream.b_pts			  = false;
        dshow_stream.p_device_filter  = NULL;
		dshow_stream.p_encoder_filter = NULL;
		dshow_stream.p_capture_filter = NULL;
		dshow_stream.i_fourcc		  = NULL;
		dshow_stream.p_es			  = 0;
		memset(&dshow_stream.header, 0, sizeof(dshow_stream.header));
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
			PIN_INFO pi;
			memset(&pi, 0, sizeof(PIN_INFO));
			if(FAILED(pInPin->QueryPinInfo(&pi)))
				break;
			//SAFE_RELEASE(pi.pFilter);
			
            /* Add directshow elementary stream to our list */
            dshow_stream.p_device_filter  = pi.pFilter;
            dshow_stream.p_capture_filter = p_capture_filter;
            dshow_stream.p_encoder_filter = NULL;
			
            pp_streams = (CDShowStream **)realloc( pp_streams,
                sizeof(CDShowStream *) * (i_streams + 1) );
            pp_streams[i_streams] = new CDShowStream;
            *pp_streams[i_streams++] = dshow_stream;
			
			return S_OK;
        }
	} while(false);
	RemoveFilter_Simple((IBaseFilter**)& p_capture_filter);
	SAFE_RELEASE(p_capture_filter);
	return E_FAIL;
}
HRESULT CBaseGrapBuilder::ReplaceSampleSampleCaptureFilterAndAddStream(IBaseFilter* pInFilter)
{
	if(pInFilter == NULL)
		return E_POINTER;
	
	list<IPin*>		Pin_List;

	HRESULT hr;	
	CComPtr<IEnumPins>	pEnum;
	if (FAILED(hr = pInFilter->EnumPins(&pEnum))) 	
		return hr;	
	
	ULONG cFetched = 1;
	IPin *pPin = NULL;
	while (pEnum->Next(1, &pPin, &cFetched) == S_OK)
	{
		PIN_DIRECTION _PinDir;
		if (FAILED(hr = pPin->QueryDirection(&_PinDir))) 
		{
			SAFE_RELEASE(pPin);
			break;
		}
		
		if (_PinDir == PINDIR_INPUT) 
		{
			IPin *pConPin = NULL;
			if(SUCCEEDED(pPin->ConnectedTo(&pConPin)))
			{
				if(pConPin)
				{
					pConPin->Disconnect();
					Pin_List.push_back(pConPin);
				}
			}
		} 
	
		SAFE_RELEASE(pPin);
		
	}
	
	
	RemoveFilter_Simple(&pInFilter);

	list<IPin*>::iterator it = Pin_List.begin();
	for(; it != Pin_List.end(); it++)
	{
		IPin *pConPin = *it;

		AddStreamByPin(pConPin);

		SAFE_RELEASE(pConPin);
	}

	return S_OK;
}
HRESULT	CBaseGrapBuilder::ConstructStream()
{
	HRESULT hr = E_FAIL;
	IBaseFilter*		pFilter = NULL;
	CComPtr<IEnumFilters>		pEnumFilters;
	do {
		if(m_pGraphBuilder == NULL)
			break;
		list<IBaseFilter*> Filter_List;
		
		ULONG				cFetched = 1;
		
		if(FAILED(hr = m_pGraphBuilder->EnumFilters(&pEnumFilters)))
			break;
		while (cFetched && pEnumFilters)
		{
			if(FAILED(hr = pEnumFilters->Next(1, &pFilter, &cFetched)))
				break;
			if(cFetched == 0)
				break;		
			if(IsTheEndestFilter(pFilter))
			{
				Filter_List.push_back(pFilter);
				
			}
			else
				SAFE_RELEASE(pFilter);	
		}
		
		list<IBaseFilter*>::iterator it = Filter_List.begin();
		for(; it != Filter_List.end(); it ++)
		{
			pFilter = *it;
			
			ReplaceSampleSampleCaptureFilterAndAddStream(pFilter);
			
			SAFE_RELEASE(pFilter);	
		}
		return S_OK;
	} while(false);
	SAFE_RELEASE(pFilter);	
	
	return hr;
}