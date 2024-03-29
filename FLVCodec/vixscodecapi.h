//
// ViXS ICodecAPI definitions
//
// Copyright (c) 2004 VIXS Systems Inc. All rights reserved.
//
// ViXS Confidential material not for non-NDA distribution
//
// $Header: /cvs/gw/commwdm/include/vixscodecapi.h,v 1.10 2006/01/18 22:24:24 hhua Exp $
//
#ifndef _VIXSCODECAPI_H_
#define _VIXSCODECAPI_H_

#include "sttype.h"

#ifdef __cplusplus
extern "C"
{
#endif

// XC2_CAP_VIDEO_TYPE
typedef xcode_video_type    VIXS_CODEC_VIDEO_FORMAT_TYPE;

// XC2_CAP_GOP_N_P
typedef GOP_TYPE            VIXS_CODEC_GOP_N_P;

// XC2_CAP_GOP_N_B
typedef GOP_TYPE            VIXS_CODEC_GOP_N_B;

// XC2_CAP_ASPECT_RATIO
typedef disp_aspect_ratio   VIXS_CODEC_ASPECT_RATIO;

// XC2_CAP_VIDEO_FILTERING
typedef video_sharpness     VIXS_CODEC_VIDEO_FILTERING;

//XC_CAP_MPEG4_QUANT_TYPE
typedef xcode_mpeg4_quanttype   VIXS_CODEC_VIDEO_QUANTTYPE;


// XC2_CAP_TBC
typedef enum {
    VIXS_TBC_DEFAULT = 0,  /// set to VIXS_TBC_DISABLED
    VIXS_TBC_ENABLED,
    VIXS_TBC_DISABLED
} VIXS_CODEC_TBC;

// XC2_CAP_3DYC_FILTER
typedef enum {
    VIXS_3DYC_FILTER_DEFAULT = 0,
    VIXS_3DYC_FILTER_ENABLED,
    VIXS_3DYC_FILTER_DISABLED
} VIXS_CODEC_3DYC_FILTER;

// XC2_CAP_INVERSE_TELECINE
typedef enum {
    VIXS_INVERSE_TELECINE_DEFAULT = 0, /// set to VIXS_INVERSE_TELECINE_ENABLED
    VIXS_INVERSE_TELECINE_ENABLED,
    VIXS_INVERSE_TELECINE_DISABLED
} VIXS_CODEC_INVERSE_TELECINE;

// XC2_CAP_SRC_TV_STANDARD
typedef input_video_type    VIXS_CODEC_TV_STANDARD;

// XC2_CAP_VIDEO_FIELD_ORDER
typedef enum {
    VIXS_CODEC_FIELD_ORDER_DEFAULT = 0, /// set to VIXS_CODEC_FIELD_ORDER_BOTTOM_FIELD_FIRST
    VIXS_CODEC_FIELD_ORDER_TOP_FIELD_FIRST,
    VIXS_CODEC_FIELD_ORDER_BOTTOM_FIELD_FIRST
} VIXS_CODEC_VIDEO_FIELD_ORDER;

typedef enum
{
    VIXS_FRAME_RATE_FORBIDDEN       = 0,    // do not use
    VIXS_FRAME_RATE_23976,                // 24000 / 1001
    VIXS_FRAME_RATE_24000,                //
    VIXS_FRAME_RATE_25000,                //
    VIXS_FRAME_RATE_29970,                // 30000 / 1001
    VIXS_FRAME_RATE_30000,                //
    VIXS_FRAME_RATE_50000,                //
    VIXS_FRAME_RATE_59940,                // 60000 / 1001
    VIXS_FRAME_RATE_60000,                //
    VIXS_FRAME_RATE_15000,
    VIXS_FRAME_RATE_14985,
    VIXS_FRAME_RATE_12000,
    VIXS_FRAME_RATE_10000,
    VIXS_FRAME_RATE_8000,
    VIXS_FRAME_RATE_5000,
    VIXS_FRAME_RATE_2000
} VIXS_FRAME_RATE_MODE;


// XC2_CAP_MPEG4_PROFILE
typedef enum
{
    VIXS_MPEG4_PROFILE_SIMPLE = PROFILE_SIMPLE,
    VIXS_MPEG4_PROFILE_ADVANCED_SIMPLE = PROFILE_ADVANCED_SIMPLE

} VIXS_CODEC_MPEG4_PROFILE;


// XC2_CAP_MPEG4_LEVEL
typedef enum
{
    VIXS_MPEG4_LEVEL_DEFAAULT = 0,
    VIXS_MPEG4_LEVEL_0,
    VIXS_MPEG4_LEVEL_1,
    VIXS_MPEG4_LEVEL_2,
    VIXS_MPEG4_LEVEL_3,
    VIXS_MPEG4_LEVEL_4,
    VIXS_MPEG4_LEVEL_5,

} VIXS_CODEC_MPEG4_LEVEL;


// XC2_CAP_CC_INSERT_MODE
typedef enum {
    VIXS_CODEC_NO_CC_INSERTION = 0,
    VIXS_CODEC_CC_INSERT_IN_PICTURE,
    VIXS_CODEC_CC_INSERT_IN_GOP
} VIXS_CODEC_CC_INSERT_MODE;

// XC2_CAP_DATA_INSERT_MODE
typedef enum {
    VIXS_CODEC_NO_DATA_INSERTION = 0,
    VIXS_CODEC_DATA_INSERT_IN_SEQ,
    VIXS_CODEC_DATA_INSERT_IN_GOP
} VIXS_CODEC_DATA_INSERT_MODE;

// XC2_CAP_AUDIO_TYPE
typedef xcode_audio_type    VIXS_CODEC_AUDIO_FORMAT_TYPE;

// XC2_CAP_AUDIO_FRAME_CRC
typedef enum {
    VIXS_CODEC_AUDIO_CRC_DEFAULT = 0,
    VIXS_CODEC_AUDIO_CRC_ENABLED,
    VIXS_CODEC_AUDIO_CRC_DISABLED
} VIXS_CODEC_AUDIO_FRAME_CRC;

// XC2_CAP_AUDIO_XCMINI_I2S_MSTR_MODE
typedef enum {
    VIXS_CODEC_AUDIO_I2S_MSTR_MODE_DEFAULT = 0,
    VIXS_CODEC_AUDIO_I2S_MSTR_MODE_ENABLED,
    VIXS_CODEC_AUDIO_I2S_MSTR_MODE_DISABLED
} VIXS_CODEC_AUDIO_XCMINI_I2S_MSTR_MODE;

// XC2_CAP_PS_STANDARD
typedef enum {
    VIXS_CODEC_MUX_DEFAULT = 0,
    VIXS_CODEC_MUX_ISO,
    VIXS_CODEC_MUX_DVD,
    VIXS_CODEC_MUX_DVD_MINUS_VR,
    VIXS_CODEC_MUX_MCE,
    VIXS_CODEC_MUX_MP4_GENERAL,
    VIXS_CODEC_MUX_MP4_MSV,
    VIXS_CODEC_MUX_MP4_PSP
} VIXS_CODEC_MUX_STANDARD;

#define VIXS_CODEC_DVD          VIXS_CODEC_MUX_DVD
#define VIXS_CODEC_DVD_MINUS_VR VIXS_CODEC_MUX_DVD_MINUS_VR


// XC2_CAP_TIMESTAMP_MODE
typedef enum {
    VIXS_CODEC_TIMESTAMP_MODE_DEFAULT = 0,
    VIXS_CODEC_SOURCE_TIMESTAMP,
    VIXS_CODEC_LOCAL_TIMESTAMP
} VIXS_CODEC_TIMESTAMP_MODE;


typedef enum
{
    VIXS_AUDIO_BITRATE_224K = 224000,
    VIXS_AUDIO_BITRATE_256K = 256000,
    VIXS_AUDIO_BITRATE_320K = 320000,
    VIXS_AUDIO_BITRATE_384K = 384000,
    VIXS_AUDIO_BITRATE_192K = 192000,
    VIXS_AUDIO_BITRATE_160K = 160000,
    VIXS_AUDIO_BITRATE_128K = 128000,
    VIXS_AUDIO_BITRATE_112K = 112000,
    VIXS_AUDIO_BITRATE_96K = 96000,
    VIXS_AUDIO_BITRATE_80K = 80000,
    VIXS_AUDIO_BITRATE_64K = 64000,
    VIXS_AUDIO_BITRATE_56K = 56000,
    VIXS_AUDIO_BITRATE_48K = 48000,
    VIXS_AUDIO_BITRATE_32K = 32000,

} VIXS_AUDIO_BITRATE_MODE;


typedef enum
{
    VIXS_AUDIO_SAMPLE_RATE_44100Hz  = 0,
    VIXS_AUDIO_SAMPLE_RATE_48000Hz,
    VIXS_AUDIO_SAMPLE_RATE_32000Hz,
    VIXS_AUDIO_SAMPLE_RATE_24000Hz,
    VIXS_AUDIO_SAMPLE_RATE_8000Hz,
    VIXS_AUDIO_SAMPLE_RATE_Reserved,
} VIXS_AUDIO_SAMPLE_RATE_MODE;


typedef enum
{
    VIXS_AUDIO_NUM_CHANNEL_STEREO           = 0,
    VIXS_AUDIO_NUM_CHANNEL_JOINTSTEREO,
    VIXS_AUDIO_NUM_CHANNEL_DUALCHANNEL,
    VIXS_AUDIO_NUM_CHANNEL_SINGLECHANNEL
} VIXS_AUDIO_NUM_CHANNEL_MODE;


#ifdef __cplusplus
}
#endif
#endif //_VIXSCODECAPI_H_
