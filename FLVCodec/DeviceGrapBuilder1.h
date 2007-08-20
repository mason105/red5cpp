// DeviceGrapBuilder1.h: interface for the CDeviceGrapBuilder1 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DEVICEGRAPBUILDER1_H__2D8CEFF5_4375_4557_B1AF_19AB31409521__INCLUDED_)
#define AFX_DEVICEGRAPBUILDER1_H__2D8CEFF5_4375_4557_B1AF_19AB31409521__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DeviceGrapBuilder.h"

class CDeviceGrapBuilder1 : public CDeviceGrapBuilder  
{
public:
	CDeviceGrapBuilder1();
	virtual ~CDeviceGrapBuilder1();
	HRESULT		AddCapturePinStream(IBaseFilter* p_device_filter,
		const char *szPinName = "Capture");
	HRESULT		ApplyVideoConfig_Software_Pin(IAMStreamConfig* stream_config, 
				int width,
				int height);
protected:
	IBaseFilter*		m_pDeviceFilter;
	IBaseFilter*		m_pEncoderFilter;
	
};

#endif // !defined(AFX_DEVICEGRAPBUILDER1_H__2D8CEFF5_4375_4557_B1AF_19AB31409521__INCLUDED_)
