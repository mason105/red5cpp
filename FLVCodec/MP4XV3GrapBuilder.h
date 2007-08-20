// MP4XV3GrapBuilder.h: interface for the CMP4XV3GrapBuilder class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MP4XV3GRAPBUILDER_H__796A8991_91E0_4B58_99AF_8F1E7C16E5B3__INCLUDED_)
#define AFX_MP4XV3GRAPBUILDER_H__796A8991_91E0_4B58_99AF_8F1E7C16E5B3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DeviceGrapBuilder1.h"
#include "typedef.h"
#include "wisproxypci.h"
#include "config_text_parser.h"

#define FCC_FORMAT_DIVX_MPEG4 mmioFOURCC('D','X','5','0')
#define FCC_FORMAT_WIS_MPEG4 mmioFOURCC('W','M','P',0x04)
#define FCC_FORMAT_MICROSOFT_MPEG4 mmioFOURCC('M','P','4','S')
#define FCC_FORMAT_SIGMA_MPEG4 mmioFOURCC('R','M','P','4')
#define FCC_FORMAT_H263 mmioFOURCC('H','2','6','3')
#define FCC_FORMAT_MOTION_JPEG mmioFOURCC('M','J','P','G')
#define FCC_FORMAT_RCC_MPEG4 mmioFOURCC('D','I','V','X')
#define MP4XV3DEVICE_NAME	"Gotron MP-4X V3 Video"
#define MP4XV3ENCODER_NAME  "Gotron MP-4X V3 BDA MPEG VES Encoder"

class CMP4XV3GrapBuilder : public CDeviceGrapBuilder1  
{
public:
	CMP4XV3GrapBuilder();
	virtual ~CMP4XV3GrapBuilder();


protected:
	virtual int OpenDevice( CDeviceGrapBuilder *p_sys,
		string devicename, 
		string devicename_display,
		bool b_audio);
	virtual HRESULT DoMiscWork();
	virtual HRESULT ApplyConfig();
	virtual HRESULT	ReleaseInterface();
	virtual BOOL	IsSupportHardCodec(int i_codec);
	
	virtual int OpenMP4XV3Device( CDeviceGrapBuilder *p_sys,
		string devicename, 
		string devicename_display,
		bool b_audio);

	BOOL		GetVideoProfiles(_VIDEO_CAPABILITIES* caps, _VIDEO_PROFILES* profiles);
	void		CheckMP4XPCIV3Config();
	HRESULT		CollectMP4XPCIV3Config();
	void		CreateMP4XPCIV3VideoConfig();
	void		CreateMP4XPCIV3AudioConfig();
	void		ChangeMP4XPCIV3CodecVideoSetting(int codec_index);
	void		SetMp4xVideoCodecBitRate(int codec_index);
	void		ConvertMP4XPCIV3Config();
	HRESULT		ApplyMP4XPCIV3VideoConfig(IAMStreamConfig* stream_config, TCFGVIDEOEX* video_config, TYPE_VIDEOCONFIG type);
	HRESULT		ApplyMP4XPCIV3VideoConfig_Software_Capture(IAMStreamConfig* stream_config, TCFGVIDEOEX* video_config);
	HRESULT		ApplyMP4XPCIV3VideoConfig_Hardware_Capture(IAMStreamConfig* stream_config, TCFGVIDEOEX* video_config);
	HRESULT		ApplyMP4XPCIV3VideoConfig_Software_Preview(IAMStreamConfig* stream_config, TCFGVIDEOEX* video_config);
	HRESULT		ApplyMP4XPCIV3AudioConfig(IAMStreamConfig* stream_config, AUDIO_CONFIG* audio_config);
protected:
	TCFGVIDEOEX			m_videoConfig;
	AUDIO_CONFIG		m_audioConfig;


	IGOChipPCI*			m_pIGOChipPCI;	
	_VIDEO_CAPABILITIES	m_VideoCaps;
	_VIDEO_PROFILES		m_VideoProfiles;
	
};

#endif // !defined(AFX_MP4XV3GRAPBUILDER_H__796A8991_91E0_4B58_99AF_8F1E7C16E5B3__INCLUDED_)
