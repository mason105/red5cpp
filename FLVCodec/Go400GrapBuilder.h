// Go400GrapBuilder.h: interface for the CGo400GrapBuilder class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GO400GRAPBUILDER_H__2C1B3BDA_C5E2_4D1E_9B93_29F698471C6B__INCLUDED_)
#define AFX_GO400GRAPBUILDER_H__2C1B3BDA_C5E2_4D1E_9B93_29F698471C6B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DeviceGrapBuilder1.h"
#include "XCodeProxyPluginIFace.h"

#define GO400DEVICE_NAME "GOTRON MP-400 Capture"

class CGo400GrapBuilder : public CDeviceGrapBuilder1
{
public:
	CGo400GrapBuilder();
	virtual ~CGo400GrapBuilder();

	virtual HRESULT Stop();
	
	virtual int OpenDevice( CDeviceGrapBuilder *p_sys,
		string devicename, 
		string devicename_display,
		bool b_audio);

	virtual HRESULT ApplyConfig();
	int OpenGo400VideoDevice( CDeviceGrapBuilder *p_sys,
							 string devicename, 
							 string devicename_display,
							 bool b_audio);	
	int OpenGo400AudioDevice( CDeviceGrapBuilder *p_sys,
							 string devicename, 
							 string devicename_display,
							 bool b_audio);	
	virtual HRESULT	ReleaseInterface();
	
protected:
	IKsPropertySet* m_piKsPropertySet;      // Interface to proxy 
    CXCodeProxyPluginIFace*    m_piConfig;  // Easy interface to our functions
	
	IKsPropertySet* m_piKsPropertyVideoOutPinSet;      // Interface to proxy 
    CXCodeProxyPluginIFace*    m_piVideoOutPinConfig;  // Easy interface to our functions
	
	XCINFO_MDAT_SIZE_S m_datainfo;
};

#endif // !defined(AFX_GO400GRAPBUILDER_H__2C1B3BDA_C5E2_4D1E_9B93_29F698471C6B__INCLUDED_)
