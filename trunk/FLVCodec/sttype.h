/**********************************************************************
 * Copyright (c) 2003-2004 VIXS Systems Inc. All rights reserved.
 *
 * ViXS Confidential material not for non-NDA distribution
 *
 * $Header: /cvs/gw/commsdk/include/sttype.h,v 1.8.2.9.4.1 2006/05/11 22:56:44 sso Exp $
 **********************************************************************/
#ifndef _STTYPE_H_
#define _STTYPE_H_

#include "mpegtype.h"

#ifdef __cplusplus
extern "C"
{
#endif

//
// input/output video types
//
typedef enum {
    MPEG1_STREAM    = _____MPEG1,           // input type: mpeg1
    MPEG2_VBR       = _____MPEG2,           // input type: mpeg2
                                            // output type: mpeg2 vbr
    MPEG4_VBR       = _____MPEG4,           // inout type: mpeg4
                                            // output type: mpeg4 vbr
    MPEG2_CBR       = _____MPEG2_CBR,       // output type: mpeg2 cbr
    MPEG4_CBR       = _____MPEG4_CBR,       // output type: mpeg4 cbr

} xcode_video_type, *pxcode_video_type;


//
// input/output audio types
//
typedef enum {
    MP1 = _____MP1,
    MP2 = _____MP2,
    MP3 = _____MP3,
    AC3 = _____AC3,
    PCM = _____PCM,
    D_V_IEC = _____DV_IEC,
    D_V_SMPTE = _____DV_SMPTE,
    A_A_C = _____AAC,
    G726 = _____G726,
    AMR = _____AMR,
	MPEG4_AAC = _____MPEG4_AAC,
    AACPLUS =  _____AACPLUS,

} xcode_audio_type, *pxcode_audio_type;


typedef enum _input_video_type
{
    SRC_VIDEO_DEFAULT = 0,
    SRC_VIDEO_NTSC_4_43,
    SRC_VIDEO_NTSC_J,
    SRC_VIDEO_NTSC_M,
    SRC_VIDEO_NTSC_NON_INTERLACED,
    SRC_VIDEO_PAL_M,
    SRC_VIDEO_PAL_B_B1_G_H,
    SRC_VIDEO_PAL_D,
    SRC_VIDEO_PAL_I,
    SRC_VIDEO_PAL_N,
    SRC_VIDEO_PAL_Nc,


} input_video_type, *pinput_video_type;


typedef enum _video_sharpness
{
    SHARPNESS_DEFAULT = 0,
    SHARPNESS_SMOOTH,
    SHARPNESS_MEDIUM,
    SHARPNESS_SHARP

} video_sharpness, *pvideo_sharpness;

typedef enum _combfiltersetting
{
    ADAPTIVE_3D_COMB = 0,
    NON_ADAPTIVE_3D_COMB
} combfiltersetting, *pcombfiltersetting;

typedef enum _xcode_mpeg4_profile
{
    PROFILE_DEFAULT = 0,
    PROFILE_SIMPLE,
    PROFILE_ADVANCED_SIMPLE,
	PROFILE_CUSTOM_0 = 256,
} xcode_mpeg4_profile, *pxcode_mpeg4_profile;

typedef enum _xcode_mpeg4_level
{
	LEVEL_DEFAULT = 0,
	LEVEL_0,
	LEVEL_1,
	LEVEL_2,
	LEVEL_3,
	LEVEL_4,
	LEVEL_5 // mpeg4 ASP can have level5 max
} xcode_mpeg4_level, *pxcode_mpeg4_level;

typedef enum _xcode_mpeg4_quanttype
{
	QUANTTYPE_DEFAULT = 0,
	QUANTTYPE_0, // H.263
	QUANTTYPE_1, // MPEG

} xcode_mpeg4_quanttype, *pxcode_mpeg4_quanttype;

typedef enum _disp_aspect_ratio
{
    ASPECT_RATIO_DEFAULT = 0,
    ASPECT_RATIO_1_TO_1,
    ASPECT_RATIO_4_TO_3,
    ASPECT_RATIO_16_TO_9,
    ASPECT_RATIO_2_POINT_1_TO_1,

	MPEG4_ASPECT_RATIO_DEFAULT = 0,
	MPEG4_ASPECT_RATIO_1_TO_1,
	MPEG4_ASPECT_RATIO_12_TO_11,
	MPEG4_ASPECT_RATIO_10_TO_11,
	MPEG4_ASPECT_RATIO_16_TO_11,
	MPEG4_ASPECT_RATIO_40_TO_33,	


} disp_aspect_ratio, *pdisp_aspect_ratio;


typedef enum _cc_standard
{
    CC_STANDARD_DEFAULT = 0,
    CC_STANDARD_ATVCC,

} cc_standard, *pcc_standard;

typedef enum _BLACKOUTCOLOUR
{
    BLACKOUT_DEFAULT = 0,
    BLACKOUT_BLACK,
    BLACKOUT_GRAY,
    BLACKOUT_BLUE,
    BLACKOUT_GREEN,
    BLACKOUT_RED
} BLACKOUTCOLOUR;

typedef enum _BLACKOUTMODE
{
    BLACKOUTMODE_DEFAULT = 0, //both
    BLACKOUTMODE_VIDEOONLY,
    BLACKOUTMODE_AUDIOONLY
} BLACKOUTMODE;

typedef enum _MOSIACCOLOURMODE
{
    MOSIAC_CONSTANT = 0,
    MOSIAC_BLEND
} MOSIACCOLOURMODE;

#define FILTER_FLAG_NR_SPATIAL_ENABLE       0x00000001
#define FILTER_FLAG_NR_TEMPORAL_ENABLE      0x00000002
#define FILTER_FLAG_COMB_Y_ENABLE           0x00000004
#define FILTER_FLAG_COMB_C_ENABLE           0x00000008
#define FILTER_FLAG_NOISE_ENABLE			(FILTER_FLAG_NR_SPATIAL_ENABLE | FILTER_FLAG_NR_TEMPORAL_ENABLE)
#define FILTER_FLAG_COMB_ENABLE             (FILTER_FLAG_COMB_Y_ENABLE | FILTER_FLAG_COMB_C_ENABLE)
#define FILTER_FLAG_ENABLE_MASK				(FILTER_FLAG_NOISE_ENABLE | FILTER_FLAG_COMB_ENABLE)
#define FILTER_FLAG_NR_TEMPORAL_USE_SETTING 0x00010000
#define FILTER_FLAG_NR_SPATIAL_USE_SETTING  0x00020000
#define FILTER_FLAG_COMB_USE_SETTING        0x00040000

#define TSCTRL_GET_INFO_PSI_LOCK		0x00000001
#define TSCTRL_GET_INFO_VIDEO_LOCK		0x00000002
#define TSCTRL_GET_INFO_AUDIO_LOCK		0x00000004
#define TSCTRL_GET_INFO_PCR_LOCK		0x00000008
#define TSCTRL_GET_INFO_VIDEO_CC_ERR	0x00000010
#define TSCTRL_GET_INFO_AUDIO_CC_ERR	0x00000020
#define TSCTRL_GET_INFO_NO_TS_OUTPUT	0x00000040
#define TSCTRL_GET_INFO_NO_VIDEO_OUTPUT	0x00000080
#define TSCTRL_GET_INFO_NO_AUDIO_OUTPUT	0x00000100
// Dynamic variable framerate defines for 
// low bitrate applications
#define VFR_MODE_ENABLE 				0x80000000
#define VFR_MODE_ALLOW_THIRD	0x00001000
#define VFR_MODE_ALLOW_HALF		0x00000100	
#define VFR_MODE_ALLOW_FULL		0x00000010

#define VFR_MODE_DEBUG_INDICATE	0x00000001

typedef enum 
{
	VFR_THRES_ZERO,
	VFR_THRES_ONE,
	VFR_THRES_TWO,
	VFR_THRES_THREE,
	VFR_THRES_FOUR
} VFRTHRESHOLD;

typedef enum 
{
    MP4_VERSION0 = 0,
    MP4_VERSION1,
} MP4VERSION;

#ifdef __cplusplus
}
#endif
#endif //_STTYPE_H_
