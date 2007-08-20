#pragma once
#include "devicegrapbuilder.h"

class CVideoCaptureTransInPlaceFilter;
class CFLVDeviceGrapBuilder :
	public CDeviceGrapBuilder
{
public:
	CFLVDeviceGrapBuilder(void);
	~CFLVDeviceGrapBuilder(void);

	virtual HRESULT InsertEncoderFilter(IBaseFilter* p_device_filter ,
		SampleCaptureFilter *p_capture_filter,bool b_audio,
		IBaseFilter** pp_encoder_filter);
	virtual HRESULT Cleanup();
protected:
	IBaseFilter* p_video_encoder_filter;
	IBaseFilter* p_audio_encoder_filter;
	CVideoCaptureTransInPlaceFilter* m_pGrabber;
};
