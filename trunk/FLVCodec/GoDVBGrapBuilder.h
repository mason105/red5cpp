// GoDVBGrapBuilder.h: interface for the CGoDVBGrapBuilder class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GODVBGRAPBUILDER_H__E5378C0C_5BE5_4E41_9F9D_EE21557593D9__INCLUDED_)
#define AFX_GODVBGRAPBUILDER_H__E5378C0C_5BE5_4E41_9F9D_EE21557593D9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DeviceGrapBuilder1.h"
#define GODVBDEVICE_NAME "Gotron GoDVB ASI TS Capture"

class CGoDVBGrapBuilder : public CDeviceGrapBuilder1  
{
public:
	CGoDVBGrapBuilder();
	virtual ~CGoDVBGrapBuilder();

	virtual int OpenDevice( CDeviceGrapBuilder *p_sys,
		string devicename, 
		string devicename_display,
		bool b_audio);
	
};

#endif // !defined(AFX_GODVBGRAPBUILDER_H__E5378C0C_5BE5_4E41_9F9D_EE21557593D9__INCLUDED_)
