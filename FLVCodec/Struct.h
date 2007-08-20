/******************************************************************************
*
*    Copyright WIS Technologies (c) (2003)
*    All Rights Reserved
*
*******************************************************************************
*
*    FILE: 
*        Struct.h
*
*    DESCRIPTION:
*        
*   
*
*    AUTHOR:
*		Jie Sun
*
*    <SOURCE CONTROL TAGS TBD>
*
******************************************************************************/

#ifndef	_STRUCT_H_
#define	_STRUCT_H_

#include "MultiMedia.h"

/*****************************************************************************
*
*   Video Common Sturction
*
*****************************************************************************/

#define MAX_NAME	64
#define MAX_DESC	256


typedef struct 
{
	char			name[MAX_NAME];			// configuration name
	char			desc[MAX_DESC];			// configuration description
	unsigned long	flags;					// valid flags for fields
	unsigned long	size;					// size of the structure, for version control
} TCFG_HEADER;

#define FLAGS_VALID							0x80000000
#define FLAGS_DEFAULT						0x40000000
#define FLAGS_NAME							0x20000000
#define FLAGS_DESC							0x10000000
#define FLAGS_USER							0x08000000

/*****************************************************************************
*
*   Video Decoder or Sensor Configuration
*
*****************************************************************************/

typedef enum
{
    TVStandard_None     = 0x00000000,  // This is a digital sensor
    TVStandard_NTSC_M   = 0x00000001,  //        75 IRE Setup
    TVStandard_NTSC_M_J = 0x00000002,  // Japan,  0 IRE Setup
    TVStandard_NTSC_433 = 0x00000004,

    TVStandard_PAL_B    = 0x00000010,
    TVStandard_PAL_D    = 0x00000020,
    TVStandard_PAL_G    = 0x00000040,
    TVStandard_PAL_H    = 0x00000080,
    TVStandard_PAL_I    = 0x00000100,
    TVStandard_PAL_M    = 0x00000200,
    TVStandard_PAL_N    = 0x00000400,

    TVStandard_PAL_60   = 0x00000800,

    TVStandard_SECAM_B  = 0x00001000,
    TVStandard_SECAM_D  = 0x00002000,
    TVStandard_SECAM_G  = 0x00004000,
    TVStandard_SECAM_H  = 0x00008000,
    TVStandard_SECAM_K  = 0x00010000,
    TVStandard_SECAM_K1 = 0x00020000,
    TVStandard_SECAM_L  = 0x00040000,
    TVStandard_SECAM_L1 = 0x00080000,

    TVStandard_NTSC_Mask  = 0x00000807,
    TVStandard_PAL_Mask   = 0x000007F0,
    TVStandard_SECAM_Mask = 0x000FF000,

	TVStandard_Default = 0xFFFFFFFF,	// used only in board module.
} TV_STANDARD;

typedef enum 
{
	VS_SVIDEO = 0x00000000,
	VS_COMPOSITE = 0x00000001,
	VS_TVTUNER = 0x00000002,
	VS_DEFAULT = 0xFFFFFFFF,	
} VIDEO_SOURCE;

typedef enum
{
	AS_TVTUNER,
	AS_LINEIN,
} AUDIO_SOURCE;

typedef struct
{
	TCFG_HEADER	header;				// common header: flags in system/sensor configuration is not used currently

	TV_STANDARD	tv_standard;		// analog tv standard	
	long		framerate;			// will devided by 1001, for example 30000 represents 29.97
	long		sensor_h;			// sensor valid pixels in horizontal
	long		sensor_v;			// sensor valid pixels in vertical
	char		format;				// 0 : YUV progressive, 1: YUV interlace, 2 : RGB Bayer
	char		pformat;			// 'MultiMedia.h': EPixelMode, valid only if sensor_format si RGB bayer

	char		sensor_656_mode;	// 1: input format is 656 mode
	char		valid_enable;
	char		valid_polar;
	char		href_polar;			// h reference polar mode, only valid in non-656 mode
	char		vref_polar;			// v reference polar mode
	char		field_id_polar;
	char		sensor_bit_width;	// 0: 8bits, 1: 10bits
	char		hv_resync_enable;	

	long		reserved;
} TCFGSYSTEM;

/*****************************************************************************
*
*   Stream Configuration
*
*****************************************************************************/

// gop mode
#define GOP_MODE_OPEN	0
#define GOP_MODE_CLOSE	1

typedef enum
{
	GO7007SB_MIDIAN		= 1,
	GO7007SB_LOWPASS	= 2,
	GO7007SB_NOFILTER	= 0
} FilterMode;

#define MIN_MPEG4_MODE		0
#define MAX_MPEG4_MODE		3

enum MPEG4_MODE
{
	WIS_MPEG4		=	0,
	DIVX_MPEG4		=	1,
	MICROSOFT_MPEG4	=	2,
	RCC_MPEG4		=	3,
	XVID_MPEG4		=	4,
};

typedef struct
{
	TCFG_HEADER		header;				// common header

	EVideoFormat	compress_mode;		// 'MultiMedia.h': EVideoFormat
	ESequenceMode	sequence;			// 'MultiMedia.h': ESequenceMode

	unsigned char   gop_mode;			// 0: open GOP, 1: closed GOP
	unsigned long	gop_size;			// maximum count of pictures in a group of picture

	unsigned char	mpeg4_mode;				// mpeg4 mode
	unsigned char   DVD_compliant;			// 0: diable, 1: enable
	unsigned char   deinterlace_mode;		// 0: use one field, 1: deinterlace, 2: interlace coding

	unsigned char	search_range;			// motion search range, should be 16,32,64 or 128
	unsigned char   gop_head_enable;		// 0: diable, 1: enable
	unsigned char   seq_head_enable;		// 0: diable, 1: enable
	unsigned char   aspect_ratio;			// 1= 1:1, 2= 4:3, 3= 16:9

	long	reserved;

} TCFGSTREAM;

enum FLAGS_STREAM
{
	FLAGS_STREAM_COMPRESS_MODE		=	0x00000001,
	FLAGS_STREAM_SEQUENCE_MODE		=	0x00000002,
	FLAGS_STREAM_GOP_MODE			=	0x00000004,
	FLAGS_STREAM_GOP_SIZE			=	0x00000008,
	FLAGS_STREAM_MPEG4_MODE			=	0x00000010,
	FLAGS_STREAM_DEINTERLACE_MODE	=	0x00000020,
	FLAGS_STREAM_SEARCH_RANGE		=	0x00000040,
	FLAGS_STREAM_GOPHEAD_ENABLE		=	0x00000080,
	FLAGS_STREAM_SEQHEAD_ENABLE		=	0x00000100,
	FLAGS_STREAM_ASPECT_RATIO		=	0x00000200,
	FLAGS_STREAM_DVD_COMPLIANT		=	0x00000400,
	FLAGS_STREAM_MPEG4_MANDETORY	=	FLAGS_STREAM_COMPRESS_MODE + FLAGS_STREAM_MPEG4_MODE,
};

/*****************************************************************************
*
*   Frame Rate Configuration
*
*****************************************************************************/

typedef struct
{
	TCFG_HEADER	header;				// common header

	TV_STANDARD		tv_standard;			// analog tv standard	
	unsigned long	frame_rate;				// output frame rate
	unsigned long	drop_frame;				// 0 : keep original, 1: 1/2 original, 2: 1/3 original ..
	unsigned char   ivtc_enable;			// inverse telecine enabled : 0: diable, 1: enable

	long	reserved;

} TCFGFRAMERATE;

enum FLAGS_FRAMERATE
{
	FLAGS_FRAMERATE_FRAMERATE		=	0x00000001,
	FLAGS_FRAMERATE_IVTC_ENABLE		=	0x00000002,
	FLAGS_FRAMERATE_DROP_FRAME		=	0x00000004,
	FLAGS_FRAMERATE_TVSTANDARD		=	0x00000008,

	FLAGS_FRAMERATE_MANDETORY		=	FLAGS_FRAMERATE_FRAMERATE + FLAGS_FRAMERATE_TVSTANDARD,
};

/*****************************************************************************
*
*   Resolution Configuration
*
*****************************************************************************/

typedef struct
{
	TCFG_HEADER	header;				// common header

	TV_STANDARD		tv_standard;	// analog tv standard	
	unsigned long	width;			// output stream resolution: horizontal size
	unsigned long	height;			// output stream resolution: vertical size

	unsigned char   h_sub_window;	// horizontal crop enabled
	unsigned char   v_sub_window;	// vertical crop enabled
	unsigned long	h_sub_offset;	// cropping horizontal coordinate
	unsigned long	v_sub_offset;	// cropping vertical coordinate

	unsigned char   h_scale_enb;	// horizontal scale enabled
	unsigned char   v_scale_enb;	// vertical scale enabled
	unsigned char   sub_sample;		// pixel sub sample enabled

	unsigned long	max_bitrate;	// recommended maximum bitrate
	unsigned long	min_bitrate;	// recommended minimum bitrate

	long	reserved;

} TCFGRESOLUTION;


enum FLAGS_RESOLUTION
{
	FLAGS_RESOLUTION_WIDTH			=	0x00000001,
	FLAGS_RESOLUTION_HEIGHT			=	0x00000002,
	FLAGS_RESOLUTION_H_SUBWINDOW	=	0x00000004,
	FLAGS_RESOLUTION_V_SUBWINDOW	=	0x00000008,
	FLAGS_RESOLUTION_SCALE_OFFSET	=	0x00000010,
	FLAGS_RESOLUTION_SUBSAMPLE		=	0x00000100,
	FLAGS_RESOLUTION_TVSTANDARD		=	0x00000200,
	FLAGS_RESOLUTION_MAX_BITRATE	=	0x00000400,
	FLAGS_RESOLUTION_MIN_BITRATE	=	0x00000800,

	FLAGS_RESOLUTION_H_SUBOFFSET	=	0x00001000,			// used only in parser
	FLAGS_RESOLUTION_V_SUBOFFSET	=	0x00002000,			// used only in parser
	FLAGS_RESOLUTION_H_SCALE_ENABLE =	0x00004000,			// used only in parser
	FLAGS_RESOLUTION_V_SCALE_ENABLE =	0x00008000,			// used only in parser

	FLAGS_RESOLUTION_MANDETORY		=	FLAGS_RESOLUTION_WIDTH 
										+ FLAGS_RESOLUTION_HEIGHT
										+ FLAGS_RESOLUTION_TVSTANDARD
										+ FLAGS_RESOLUTION_MAX_BITRATE
										+ FLAGS_RESOLUTION_MIN_BITRATE,
};

/*****************************************************************************
*
*   Bitrate Configuration
*
*****************************************************************************/

typedef struct
{
	TCFG_HEADER	header;				// common header

	unsigned long	target_bitrate;		// target bitrate (bps), a non-zero value enables WIS adaptive bitrate control, 0 means no bit rate control
	unsigned long	peak_bitrate;		
	unsigned long	vbv_buffer;		
	unsigned char   converge_speed;		// [0, 100],
	unsigned char	lambda;				// [0, 100], from best picture quality to largest framerate

	unsigned long	Q;					// initial quantizer, will devided by 4, for exmaple, 7 represents 1.75
	unsigned char	IQ;					// fixed quantize scale of I frames, only valid for target_rate==0 and Q==0
	unsigned char	PQ;					// fixed quantize scale of P frames
	unsigned char	BQ;					// fixed quantize scale of B frames
	
	long	reserved;
} TCFGBRCTRL;

enum FLAGS_BITRATE
{
	FLAGS_BITRATE_TARGET			=	0x00000004,
	FLAGS_BITRATE_PEAK				=	0x00000008,
	FLAGS_BITRATE_VBV_BUFFER		=	0x00000010,
	FLAGS_BITRATE_CONVERGE_SPEED	=	0x00000020,
	FLAGS_BITRATE_LAMBDA			=	0x00000040,
	FLAGS_BITRATE_Q					=	0x00000080,
	FLAGS_BITRATE_IPBQ				=	0x00000100,

	FLAGS_BITRATE_IQ				=	0x00000200,			// used only in parser
	FLAGS_BITRATE_PQ				=	0x00000400,			// used only in parser
	FLAGS_BITRATE_BQ				=	0x00000800,			// used only in parser

	FLAGS_BITRATE_QMIN				=	0x00001000,
	FLAGS_BITRATE_QMAX				=	0x00002000,
	FLAGS_BITRATE_DUP_ENABLE		=	0x00004000,
	FLAGS_BITRATE_MBBRC_ENABLE		=	0x00008000,
	FLAGS_BITRATE_BRC_WINDOW		=	0x00010000,

	FLAGS_BITRATE_MANDETORY			=	FLAGS_BITRATE_TARGET + FLAGS_BITRATE_Q
};

/*****************************************************************************
*
*   Other Configuration
*
*****************************************************************************/

typedef struct
{
	TCFG_HEADER		header;				// common header

	unsigned char   av_sync_enable;			// 0: diable, 1: enable
	unsigned char   iip_enable;				// 0: diable, 1: enable
	unsigned char   vbi_enable;				// 0: diable, 1: enable
	unsigned char   four_channel_enable;	// 0: diable, 1: enable

	FilterMode		h_filter_mode;		// horizontal filter mode
	FilterMode		v_filter_mode;		// vertical filter mode
	char			filter_nAX;			// weight, only valid in mode 2
	char			filter_nBX;			// weight, only valid in mode 2
	char			filter_nCX;			// weight, only valid in mode 2
	char			filter_nAY;			// weight, only valid in mode 2
	char			filter_nBY;			// weight, only valid in mode 2
	char			filter_nCY;			// weight, only valid in mode 2

	long	reserved;

} TCFGMISC;

enum FLAGS_MISC
{
	FLAGS_MISC_AV_SYNC_ENABLE		=	0x00000001,
	FLAGS_MISC_IIP_ENABLE			=	0x00000002,
	FLAGS_MISC_VBI_ENABLE			=	0x00000004,
	FLAGS_MISC_FOUR_CHANNEL_ENABLE	=	0x00000008,
	FLAGS_MISC_FILTER				=	0x00000010,

	FLAGS_MISC_MANDETORY			=	0
};

/*****************************************************************************
*
*   Video Configuration
*
*****************************************************************************/

typedef struct
{
	TCFGMISC		misccfg;	// configuration for misc configuration
	TCFGSTREAM		strcfg;		// configuration for stream information
	TCFGRESOLUTION	rescfg;		// configuration for resolution information
	TCFGFRAMERATE	fpscfg;		// configuration for frame rate
	TCFGBRCTRL		ctlcfg;		// configuration for bitrate control
} TCFGVIDEO;

typedef struct
{
	TCFGSYSTEM		syscfg;		// configuration for system setting
	TCFGMISC		misccfg;	// configuration for misc configuration
	TCFGSTREAM		strcfg;		// configuration for stream information
	TCFGRESOLUTION	rescfg;		// configuration for resolution information
	TCFGFRAMERATE	fpscfg;		// configuration for frame rate
	TCFGBRCTRL		ctlcfg;		// configuration for bitrate control
} TCFGVIDEOEX;

typedef struct
{
	TCFGSTREAM		_stream;
	TCFGFRAMERATE	_framerate;
	TCFGRESOLUTION	_resolution;
	TCFGBRCTRL		_bitrate;
} TCFG_FORMAT_EXTENSION;

#define FORMAT_EXTENSION_SIZE sizeof(TCFG_FORMAT_EXTENSION)

typedef struct _SENSOR_PARAMETERS
{
	int Brightness;			// [0 : 100]    
	int BrightnessAuto;
	int Contrast;			// [0 : 100]
	int ContrastAuto;
	int Hue;				// [-50 : 50]
	int HueAuto;
	int Saturation;         // [0 : 100]
	int SaturationAuto;
	int Sharpness;
	int SharpnessAuto;
	int Gamma;
	int GammaAuto;
	int WhiteBalance;
	int WhiteBalanceAuto;
	int BacklightComp;
	int BacklightCompAuto;
	int ColorEnable;
}SENSOR_PARAMETERS;

/*****************************************************************************
*
*   Capabilities and Profiles
*
*****************************************************************************/

enum ASSOCIATION_TYPE
{
	TYPE_SYSTEM_CONFIG,
	TYPE_STREAM_CONFIG,
	TYPE_RESOLUTION_CONFIG,
	TYPE_BITRATE_CONFIG,
	TYPE_FRAMERATE_CONFIG
};

enum ASSOCIATION_INDEX
{
	ASSOCIATION_ALL	 = 0xFFFFFFFF
};

enum ASSOCIATION_PERMISSION
{
	ASSOCIATION_TYPE_ALLOW  =	0,
	ASSOCIATION_TYPE_DENY	=	1,
};

typedef struct
{
	enum ASSOCIATION_TYPE	_master_type;
	unsigned long			_master_id;
	enum ASSOCIATION_TYPE	_slave_type;
	unsigned long			_slave_id;
	unsigned char			_associate_type;
} TCFGASSOCIATION;

#define MAX_SYSTEM_CONFIG		16
#define MAX_STREAM_CONFIG		30
#define MAX_RESOLUTION_CONFIG	30
#define MAX_BITRATE_CONFIG		30
#define MAX_FRAMERATE_CONFIG	30
#define MAX_ASSOCIATION			300

typedef struct
{
	unsigned long stream_index;
	unsigned long resolution_index;
	unsigned long framerate_index;
} TVCFG_ENTRY;

typedef struct
{
	unsigned long		_num_of_system_configs;			// system/sensor configuration count
	TCFGSYSTEM			_system_configs[MAX_SYSTEM_CONFIG];

	unsigned long		_num_of_stream_configs;			// stream configuration count
	TCFGSTREAM			_stream_configs[MAX_STREAM_CONFIG];

	unsigned long		_num_of_resolution_configs;		// resolution configuration count
	TCFGRESOLUTION		_resolution_configs[MAX_RESOLUTION_CONFIG];

	unsigned long		_num_of_framerate_configs;		// frame rate configuration count
	TCFGFRAMERATE		_framerate_configs[MAX_FRAMERATE_CONFIG];

	unsigned long		_num_of_associations;			// number of associations
	TCFGASSOCIATION		_associations[MAX_ASSOCIATION];

	unsigned long		_num_of_configurations;
	TVCFG_ENTRY*		_configurations;

} _VIDEO_CAPABILITIES;

typedef struct
{
	unsigned long		_num_of_stream_profiles;			// stream configuration count
	TCFGSTREAM			_stream_profiles[MAX_STREAM_CONFIG];
	unsigned long		_stream_profile_cap_index[MAX_STREAM_CONFIG];

	unsigned long		_num_of_resolution_profiles;		// resolution configuration count
	TCFGRESOLUTION		_resolution_profiles[MAX_RESOLUTION_CONFIG];
	unsigned long		_resolution_profile_cap_index[MAX_RESOLUTION_CONFIG];

	unsigned long		_num_of_bitrate_profiles;		// bitrate control configuration count
	TCFGBRCTRL			_bitrate_profiles[MAX_BITRATE_CONFIG];
	unsigned long		_bitrate_profile_cap_index[MAX_BITRATE_CONFIG];

	unsigned long		_num_of_framerate_profiles;		// frame rate configuration count
	TCFGFRAMERATE		_framerate_profiles[MAX_FRAMERATE_CONFIG];
	unsigned long		_framerate_profile_cap_index[MAX_FRAMERATE_CONFIG];
} _VIDEO_PROFILES;


/*****************************************************************************
*
*   Audio Configuration
*
*****************************************************************************/

enum AUDIO_CAPS
{
	CAP_AUDIO_FORMAT_PCM		= 0x00000001,
	CAP_AUDIO_FORMAT_ADPCM_MS	= 0x00000002,
	CAP_AUDIO_FORMAT_ADPCM_IMA	= 0x00000004,
	CAP_AUDIO_FORMAT_ALAW		= 0x00000008,
	CAP_AUDIO_FORMAT_ULAW		= 0x00000010,
	CAP_AUDIO_FORMAT_MP3		= 0x00000020,
	CAP_AUDIO_I2S_MASTER_MODE   = 0x00000040,

	CAP_AUDIO_SAMPLERATE_8K		= 0x00000100,
	CAP_AUDIO_SAMPLERATE_11025	= 0x00000200,
	CAP_AUDIO_SAMPLERATE_16K	= 0x00000400,
	CAP_AUDIO_SAMPLERATE_22050	= 0x00000800,
	CAP_AUDIO_SAMPLERATE_32K	= 0x00001000,
	CAP_AUDIO_SAMPLERATE_44100	= 0x00002000,
	CAP_AUDIO_SAMPLERATE_48K	= 0x00004000,

	CAP_AUDIO_CHANNEL_MONO		= 0x00010000,
	CAP_AUDIO_CHANNEL_STEREO	= 0x00020000,

	CAP_AUDIO_SAMPLE_4BIT		= 0x00040000,
	CAP_AUDIO_SAMPLE_8BIT		= 0x00080000,
	CAP_AUDIO_SAMPLE_16BIT		= 0x00100000,
};

enum AUDIO_FORMAT
{
	AUDIO_FORMAT_PCM			= 0x1,
	AUDIO_FORMAT_ADPCM_MS		= 0x2,
	AUDIO_FORMAT_ALAW			= 0x6,
	AUDIO_FORMAT_ULAW			= 0x7,
	AUDIO_FORMAT_ADPCM_IMA		= 0x11,
	AUDIO_FORMAT_MP3 			= 0x55
};

typedef struct _AUDIO_CONFIG
{
	unsigned long	Format;				// Equal to Tag
	unsigned long	SampleRate;
	unsigned long	Channels;
	unsigned long	SampleBits;

	unsigned short	BlockAlign;
	unsigned long	AvgBytesPerSec;
	unsigned short	SamplesPerBlock; 
	unsigned short	ExtSize;			// PCM =0;  MS ADPCM=32; ...

} AUDIO_CONFIG;

/*****************************************************************************
*   audio configuration
*****************************************************************************/

typedef struct 
{
	unsigned short main_divider;
	unsigned short BCLK_divider;
	unsigned short OKI_mode;
	unsigned short OKI_short_frame_mode;
	unsigned short clock_generator_enable;
	unsigned short I2S_master_mode;
	unsigned short I2S_mode;
	unsigned short invert_phase_BCLK;
	unsigned short OKI_shoftframe_mode;
	unsigned short word_length;
	unsigned short auto_SOF_generation;
	unsigned short left_channel_only;
	unsigned short higher_8_bit_combine;
	unsigned short AC97_enable;
	unsigned short signature_bit_selection;
	unsigned short buffer_config;
	unsigned short sample_mapping_reg1;
	unsigned short sample_mapping_reg2;
	unsigned short sample_mapping_reg3;
	unsigned short sample_mapping_reg4;
	unsigned short sample_mapping_reg5;
	unsigned short sample_mapping_reg6;
	unsigned short sample_mapping_reg7;
	unsigned short adpcm_enable;
	unsigned short adpcm_mode;
	unsigned short bytes_per_block;
	unsigned short bpredictor;
	unsigned short idelta_left;
	unsigned short idelta_right;
	unsigned short icoef1_left;
	unsigned short icoef1_right;
	unsigned short icoef2_left;
	unsigned short icoef2_right;

	int	reserved;
} TCFGAUDIO;


typedef struct 
{
	unsigned long	_format_index;
	unsigned long	_samplerate_index;
	unsigned long	_samplebits_index;
	unsigned long	_channel_index;
	unsigned long	_extension_size;
	void*			_extension;
} TACFG_ENTRY;

#define MAX_AUDIO_FORMATS_CONFIG		16
#define MAX_AUDIO_SAMPLERATES_CONFIG	16
#define MAX_AUDIO_SAMPLEBITS_CONFIG	16
#define MAX_AUDIO_CHANNELS_CONFIG		16
#define MAX_AUDIO_CONFIGUATIONS			200

typedef struct
{
	unsigned long		_num_of_format_config;
	unsigned long		_audio_format_table[MAX_AUDIO_FORMATS_CONFIG];

	unsigned long		_num_of_samplerate_config;
	unsigned long		_audio_samplerate_table[MAX_AUDIO_SAMPLERATES_CONFIG];

	unsigned long		_num_of_samplebits_config;
	unsigned long		_audio_samplebits_table[MAX_AUDIO_SAMPLEBITS_CONFIG];

	unsigned long		_num_of_channel_config;
	unsigned long		_audio_channel_table[MAX_AUDIO_CHANNELS_CONFIG];

	unsigned long		_num_of_audio_configuration;
	TACFG_ENTRY			_audio_configuration[MAX_AUDIO_CONFIGUATIONS];
} _AUDIO_CAPABILITIES;


//for motion detection
typedef struct sMotionThresholdPackage 
{
	unsigned short u16MotionThresholdMarker;            // actual value need to get from firmware 
	unsigned short u16SADThresholdValues[7];            // Give the SAD thresholds in order of region 1, region 2, ? region 7 
	unsigned short u16MVThresholdValues[7];             //Give the Motion Vector thresholds in order of region 1, region 2, ? region 7 
	unsigned short u16SensitivityValues[7];
	unsigned short u16Reserved[10];                     // set to 0 
} motionThresholdPackage_t;

typedef struct sMotionMacroblockMapPackage 
{
	unsigned short u16MotionPackageMarker;              //actual value TBD 
	unsigned short u16StartingMacroblockNumber;         // macroblock number must be divisible by 5, or the value 0 
	unsigned short u16MacroblockMap[30];				// bits 0-2, 3-5, 6-8, 9-11, 12-15 represent a macroblock, in that order.  Bit 16 is reserved 
} motionMacroblockMapPackage_t;

#define MD_TOTAL_MB_MAP 9
typedef struct MDInterfaceData
{
	motionThresholdPackage_t MTP;				//!!!!!note: if there is need to support bigger screen MBMap need to be changed(send whole screen is a waste anyway!!!!!
	motionMacroblockMapPackage_t MBMap[MD_TOTAL_MB_MAP];		//the largest 720*480 = 1350 MB /150 MB per MBMap 
}MDInterfaceData_T;

typedef	void (*CALLBACK_NEVENT)(unsigned long data);	

/*****************************************************************************
*
*   Misc Configuration
*
*****************************************************************************/

typedef struct 
{
#ifdef _WINDOWS
	unsigned __int64 VideoByte;
#else
	unsigned VideoByte;
#endif
	unsigned long  FrameCount;
} STATISTIC;

typedef struct {
	int DriverMajor;
	int DriverMinor;
	int BoardRevision;
	char BoardName[MAX_NAME];
	int BoardCapability;
	int MaxBandWidth;
	int SourceWidth;
	int SourceHeight;
} REVISION_INFO;

#define MAX_OSDSTRING_LEN 255
typedef struct 
{
	//lzh20050727(�޸�)
	unsigned short 	int TotalLength;
	
	unsigned short text[MAX_OSDSTRING_LEN];
} OSDTextoutInfo;

/*****************************************************************************
*
*   Events
*
*****************************************************************************/

typedef enum
{
	NT_FATALERROR = 100,
	NT_VSYNCLOST,
	NT_AVOUTOFSYNC,
	NT_TIMEOUT,
	NT_SNAPSHOT,
	NT_REPORTTS,
	NT_MOTIONDETECT,
	NT_DEVICEREMOVED,
	NT_TVTUNERCHANGED,
	NT_TVAUDIOCHANGED,
	NT_VIDEODECODERCHANGED,
}NOTIFY_TYPE;

#endif

/********************************* end of Struct.h ***************************/
