/******************************************************************************
 * Copyright (c) 2003-2004 VIXS Systems Inc. All rights reserved.
 *
 * ViXS Confidential material not for non-NDA distribution
 ******************************************************************************/
#ifndef _MPEGTYPE_H_
#define _MPEGTYPE_H_



#define _____UNKNOWN    0

//
// Video Stream Types
//
enum {
    _____MPEG1 = 1,
    _____MPEG2,
    _____MPEG4,
    _____MPEG2_CBR,
    _____MPEG4_CBR,
    _____YUY2,
    _____UYVY,
    _____VIXS_PLANAR,
};

#define _____YUYV   _____YUY2

#define _____MPEG1_BIT              (1<<_____MPEG1)
#define _____MPEG2_BIT              (1<<_____MPEG2)
#define _____MPEG4_BIT              (1<<_____MPEG4)
#define _____MPEG2_CBR_BIT          (1<<_____MPEG2_CBR)
#define _____MPEG4_CBR_BIT          (1<<_____MPEG4_CBR)


//
// Video Frame Types
//
enum {
    _____I = 1,
    _____P,
    _____B,
};


//
// Audio Stream type
//
enum {
    _____MP1 = 1,
    _____MP2,
    _____MP3,
    _____AC3,
    _____PCM,
    _____DV_IEC,
    _____DV_SMPTE,
    _____AAC,
    _____G726,
    _____AMR,
	_____MPEG4_AAC,
    _____AACPLUS,
};

#define _____MP1_BIT        (1<<_____MP1)
#define _____MP2_BIT        (1<<_____MP2)
#define _____MP3_BIT        (1<<_____MP3)
#define _____AC3_BIT        (1<<_____AC3)
#define _____AAC_BIT        (1<<_____AAC)
#define _____G726_BIT       (1<<_____G726)
#define _____AMR_BIT        (1<<_____AMR)
#define _____MPEG4_AAC_BIT  (1<<_____MPEG4_AAC)
#define _____AACPLUS_BIT    (1<<_____AACPLUS)

typedef enum _GOP_TYPE {
    GOP_DEFAULT = 0,
    GOP_B_DEFAULT = 0,
    GOP_0_B,
    GOP_1_B,
    GOP_2_B,
    GOP_3_B,

    GOP_P_DEFAULT = (0 <<8),
    GOP_0_P = (1<<8),
    GOP_1_P = (2<<8),
    GOP_2_P = (3<<8),
    GOP_3_P = (4<<8),
    GOP_4_P = (5<<8),
    GOP_5_P = (6<<8),

} GOP_TYPE;



typedef enum _PS_TYPE {
    PS_DEFAULT_PS = 0,
    PS_ISO_PS,
    PS_DVD_PS,
    PS_DVD_VR_PS,
    PS_CUSTOM_1_PS,
    PS_CUSTOM_2_PS,
    PS_CUSTOM_3_PS,
    PS_MCE_PS,
	// MP4 types
	PS_MP4_GEN_PS,
    PS_MP4_MSV_PS,
	PS_MP4_PSP_PS,
}  PS_TYPE;


#endif //_MPEGTYPE_H_
