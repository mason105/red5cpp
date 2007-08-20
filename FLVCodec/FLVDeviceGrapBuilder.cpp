#include ".\flvdevicegrapbuilder.h"
extern "C"
{
#define  _ENUMTYPEDEF

#include "../owpixertool/include/pixertool/ffmpeg-pixertool.h"
}
#include "../owpixertool/include/pixertool/directx-pixertool.h"
#include "../owpixertool/include/pixertool/pixertool.h"

const TCHAR* szVideoCodec = "VP62? Heightened Sharpness Profile";
const TCHAR* szAudioCodec = "LAME Audio Encoder";


class CVideoCaptureTransInPlaceFilter :
	public CTransformFilter
{
public:	
	CFLVDeviceGrapBuilder* m_pVideoCaptureDirectX;
	pixosi _cachedPalette;
	struct _piximage* image_wrong_pix;
	struct _piximage* image_wrong_pix_flip;
	int m_nInWidth;
	int m_nInHeight;
	unsigned len_prepared_for_encoding;
	CMediaType inputMediaType;

	CVideoCaptureTransInPlaceFilter(LPUNKNOWN punk, HRESULT *phr) :
	CTransformFilter(TEXT("Video Capture TransFilter"), NULL, GUID_NULL)
		, m_pVideoCaptureDirectX(NULL)
		, _cachedPalette(PIX_OSI_UNSUPPORTED)
		, image_wrong_pix(NULL)
		, image_wrong_pix_flip(NULL)
		, m_nInWidth(320)
		, m_nInHeight(240)
		, len_prepared_for_encoding(0)
	{
	}

	virtual ~CVideoCaptureTransInPlaceFilter(void)
	{
		if(image_wrong_pix)
			pix_free(image_wrong_pix);
		if(image_wrong_pix_flip)
			pix_free(image_wrong_pix_flip);
	}
	virtual HRESULT DecideBufferSize(
		IMemAllocator*		  pAllocator,
		ALLOCATOR_PROPERTIES* pProperties)
	{
		HRESULT hr = S_OK;

		pProperties->cBuffers = 2;
		if(_cachedPalette != PIX_OSI_UNSUPPORTED)
		{
			pProperties->cbBuffer = pix_size (_cachedPalette,
				m_nInWidth,
				m_nInHeight) * 1.5;
		}
		else
			pProperties->cbBuffer = pix_size (PIX_OSI_RGB24,
			640,
			480) * 1.5;

		ASSERT(pProperties->cbBuffer);

		ALLOCATOR_PROPERTIES Actual;
		hr = pAllocator->SetProperties(pProperties,&Actual);
		if(FAILED(hr))
			return hr;

		if (Actual.cbBuffer < pProperties->cbBuffer ||
			Actual.cBuffers < pProperties->cBuffers) 
		{
			return E_INVALIDARG;
		}
		return S_OK;
	}
	HRESULT GetMediaType  (int iPosition, CMediaType *pMediaType)
	{
		if(m_pInput == NULL)
			return E_FAIL;
		CopyMediaType(pMediaType, &inputMediaType);
		return S_OK;
	}
	HRESULT CheckTransform(const CMediaType* mtIn, const CMediaType* mtOut)
	{
		if (*mtOut->FormatType() != FORMAT_VideoInfo)
			return VFW_E_INVALIDMEDIATYPE;

	
		return S_OK;
	}
	virtual HRESULT SetMediaType(PIN_DIRECTION direction,const CMediaType *pmt)
	{
		if(direction == PINDIR_INPUT)
		{
			VIDEOINFO *pVI = (VIDEOINFO *) pmt->Format();
			CheckPointer(pVI,E_UNEXPECTED);

			pixosi _tmpPalette = pix_directx_to_pix_osi(*pmt->Subtype( ));
			if(_tmpPalette == PIX_OSI_UNSUPPORTED)
				return E_FAIL;
			_cachedPalette = _tmpPalette;
			m_nInWidth = pVI->bmiHeader.biWidth;
			m_nInHeight= pVI->bmiHeader.biHeight;

			if(image_wrong_pix)
				pix_free(image_wrong_pix);

			image_wrong_pix = pix_alloc(PIX_OSI_YUV420P, m_nInWidth, m_nInHeight);
			image_wrong_pix_flip = pix_alloc(PIX_OSI_YUV420P, m_nInWidth, m_nInHeight);

			len_prepared_for_encoding = pix_size (PIX_OSI_YUV420P,
				m_nInWidth,
				m_nInHeight);
			CopyMediaType(&inputMediaType, pmt);
			BITMAPINFOHEADER *pbmi = &((VIDEOINFO*)inputMediaType.Format())->bmiHeader;
			pbmi->biSize = sizeof(BITMAPINFOHEADER);
			pbmi->biWidth = m_nInWidth;
			pbmi->biHeight =  m_nInHeight;
			pbmi->biPlanes = 1;
			pbmi->biBitCount = 12;
			pbmi->biCompression = MAKEFOURCC('I','4','2','0');
			pbmi->biSizeImage = len_prepared_for_encoding;
		}
		return CTransformFilter::SetMediaType(direction, pmt);
	}
	HRESULT CVideoCaptureTransInPlaceFilter::CheckInputType(const CMediaType *mtIn)
	{
		CheckPointer(mtIn,E_POINTER);

		if (*mtIn->FormatType() != FORMAT_VideoInfo)
		{
			return E_INVALIDARG;
		}

		if( *mtIn->Type( ) != MEDIATYPE_Video )
		{
			return E_INVALIDARG;
		}
		pixosi _tmpPalette = pix_directx_to_pix_osi(*mtIn->Subtype( ));
		if(_tmpPalette == PIX_OSI_UNSUPPORTED)
			return E_INVALIDARG;
	

		return NOERROR;
	}
	void frameBufferAvailable (piximage * image_captured, BYTE* pDst)
	{		
		pixosi scrpalette = image_captured->palette;
		if(image_captured->palette != PIX_OSI_YUV420P)
		{
			if(image_wrong_pix == NULL)
				image_wrong_pix = pix_alloc(PIX_OSI_YUV420P, m_nInWidth, m_nInHeight);
			pix_convert(PIX_NO_FLAG, image_wrong_pix, image_captured);
			image_captured = image_wrong_pix;
		}
		if(image_captured->palette == PIX_OSI_YUV420P &&
			scrpalette != PIX_OSI_BGR24)
		{
			if(image_wrong_pix_flip == NULL)
				image_wrong_pix_flip = pix_alloc(PIX_OSI_YUV420P, m_nInWidth, m_nInHeight);
			pix_convert(PIX_FLIP_HORIZONTALLY, image_wrong_pix_flip, image_captured);
			image_captured = image_wrong_pix_flip;
		}

		memcpy(pDst, image_captured->data, len_prepared_for_encoding);
	}
	HRESULT CVideoCaptureTransInPlaceFilter::Receive(IMediaSample *pSample)
	{

		CheckPointer(pSample,E_POINTER);

		BYTE * pSourceBuffer = NULL;

		if (pSample->GetPointer(&pSourceBuffer) != S_OK || !pSourceBuffer || m_State != State_Running)
			return S_OK;

		long sample_size = pSample->GetActualDataLength();

		REFERENCE_TIME rtStart, rtStop;
		BOOL gotValidTime = (pSample->GetTime(&rtStart, &rtStop) != VFW_E_SAMPLE_TIME_NOT_SET);
		if (sample_size <= 0 || pSourceBuffer == NULL || (gotValidTime && rtStart < 0))
			return S_OK;

		IMediaSample * pOutSample = NULL;
		BYTE * pDst = NULL;
		HRESULT hr = m_pOutput->GetDeliveryBuffer(&pOutSample, NULL, NULL, 0);
		if (hr == S_OK && pOutSample)
		{

			hr = pOutSample->GetPointer(&pDst);
			if (hr == S_OK && pDst)
			{
				piximage _capturedImage;
				_capturedImage.data = (uint8_t *) pSourceBuffer;
				_capturedImage.width = m_nInWidth;
				_capturedImage.height = m_nInHeight;
				_capturedImage.palette = _cachedPalette;

				long nOutSize = pOutSample->GetSize();
				if(FAILED(pOutSample->SetActualDataLength(len_prepared_for_encoding)))
					return S_OK;

				frameBufferAvailable(&_capturedImage, pDst);

				pOutSample->SetSyncPoint(pSample->IsSyncPoint());
				pOutSample->SetDiscontinuity(pSample->IsDiscontinuity());
				pOutSample->SetPreroll(pSample->IsPreroll());
				REFERENCE_TIME rtMStart, rtMStop;
				pSample->GetMediaTime(&rtMStart, &rtMStop);
				pOutSample->SetMediaTime(&rtMStart, &rtMStop);
				pOutSample->SetTime(&rtStart, &rtStop);
				
				m_pOutput->Deliver(pOutSample);
			}

			pOutSample->Release();
			return NOERROR;
		}

	
		return E_FAIL;
	}
	HRESULT Reconnect()
	{
		HRESULT hr = S_FALSE;

		if (m_pOutput && m_pOutput->IsConnected() && m_State == State_Stopped)
		{
			
			{
				CMediaType cmt;

				cmt.InitMediaType();
				GetMediaType(0, &cmt);

				if (S_OK == (hr = m_pOutput->GetConnected()->QueryAccept(&cmt)))
					hr = m_pGraph->Reconnect(m_pOutput);
				else
					hr = m_pOutput->SetMediaType(&cmt);
			}
		}

		return hr;
	}


};

CFLVDeviceGrapBuilder::CFLVDeviceGrapBuilder(void)
{
	p_video_encoder_filter = NULL;
	p_audio_encoder_filter = NULL;
	m_pGrabber			   = NULL;
}

CFLVDeviceGrapBuilder::~CFLVDeviceGrapBuilder(void)
{
}
HRESULT CFLVDeviceGrapBuilder::InsertEncoderFilter(IBaseFilter* p_device_filter ,
							SampleCaptureFilter *p_capture_filter,
							bool b_audio,
							IBaseFilter** pp_encoder_filter)
{
	IBaseFilter* p_tmp_encoder_filter = NULL;
	do {
		if(b_audio ==  false)
		{	
			HRESULT hr = S_OK;
			m_pGrabber	= new CVideoCaptureTransInPlaceFilter(0, &hr);
			m_pGrabber->AddRef();
			if (FAILED(hr = m_pGraphBuilder->AddFilter(m_pGrabber, NULL)))
				break;
			if(FAILED(CreateFilter_BySpecialCategoryAndName(CLSID_VideoCompressorCategory, 
				szVideoCodec, 
				TRUE, 
				&p_tmp_encoder_filter)) || p_tmp_encoder_filter == NULL)
				break;		
			if(FAILED(ConnectFilter_RenderStream(p_device_filter,
				m_pGrabber,
				p_tmp_encoder_filter, 
				b_audio, 
				false)))
				break;
			if(FAILED(ConnectFilter_Simple(p_tmp_encoder_filter,
				p_capture_filter)))
				break;	
		
			/*
			CComPtr<IBaseFilter> pNullRender;
			if(FAILED(CreateFilter_BySpecialCategoryAndName(CLSID_LegacyAmFilterCategory,
				_T("Null Renderer"), TRUE, &pNullRender)))
				break;
			if(FAILED(ConnectFilter_RenderStream(p_device_filter,
				m_pGrabber,
				pNullRender, 
				b_audio, 
				false)))
				break;
			IBaseFilter *ptmpFilter = m_pGrabber;
			RemoveFilter_DownStream(&ptmpFilter);
			if(FAILED(CreateFilter_BySpecialCategoryAndName(CLSID_VideoCompressorCategory, 
				szVideoCodec, 
				TRUE, 
				&p_tmp_encoder_filter)) || p_tmp_encoder_filter == NULL)
				break;		
			if(FAILED(ConnectFilter_Simple(m_pGrabber,
				p_tmp_encoder_filter)))
				break;	
			if(FAILED(ConnectFilter_Simple(m_pGrabber,
				p_capture_filter)))
				break;*/
			p_video_encoder_filter = p_tmp_encoder_filter;
			*pp_encoder_filter	   = p_tmp_encoder_filter;
		}
		else
		{
			//return CDeviceGrapBuilder::InsertEncoderFilter(p_device_filter, p_capture_filter, b_audio, pp_encoder_filter);	
			if(FAILED(CreateFilter_BySpecialCategoryAndName(CLSID_LegacyAmFilterCategory, 
				szAudioCodec, 
				TRUE, 
				&p_tmp_encoder_filter)) || p_tmp_encoder_filter == NULL)
				break;
			if(FAILED(ConnectFilter_RenderStream(p_device_filter,
				p_tmp_encoder_filter,
				p_capture_filter, b_audio, false)))
				break;
			/*CComPtr<IBaseFilter> pNullRender;
			if(FAILED(CreateFilter_BySpecialCategoryAndName(CLSID_LegacyAmFilterCategory,
				_T("Null Renderer"), TRUE, &pNullRender)))
				break;
			if(FAILED(ConnectFilter_RenderStream(p_device_filter,
				NULL,
				pNullRender, b_audio, true)))
				break;*/
			p_audio_encoder_filter = p_tmp_encoder_filter;
			*pp_encoder_filter	   = p_tmp_encoder_filter;
		}
		return S_OK;	
	} while(false);
	SAFE_RELEASE(p_tmp_encoder_filter);
	return E_FAIL;
}
HRESULT CFLVDeviceGrapBuilder::Cleanup()
{
	//SAFE_RELEASE(p_video_encoder_filter);
	//SAFE_RELEASE(p_audio_encoder_filter);
	p_video_encoder_filter = 0;
	p_audio_encoder_filter = 0;
	if(m_pGrabber)
	{
		m_pGrabber->Release();
		m_pGrabber = 0;
	}

	return CDeviceGrapBuilder::Cleanup();
}