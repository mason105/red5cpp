

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0361 */
/* at Wed Oct 06 13:58:49 2004
 */
/* Compiler settings for .\WisProxyPCI.idl:
    Oicf, W1, Zp8, env=Win32 (32b run)
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __WisProxyPCI_h__
#define __WisProxyPCI_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IGOChipPCI_FWD_DEFINED__
#define __IGOChipPCI_FWD_DEFINED__
typedef interface IGOChipPCI IGOChipPCI;
#endif 	/* __IGOChipPCI_FWD_DEFINED__ */


#ifndef __VideoControlPropertyPage_FWD_DEFINED__
#define __VideoControlPropertyPage_FWD_DEFINED__

#ifdef __cplusplus
typedef class VideoControlPropertyPage VideoControlPropertyPage;
#else
typedef struct VideoControlPropertyPage VideoControlPropertyPage;
#endif /* __cplusplus */

#endif 	/* __VideoControlPropertyPage_FWD_DEFINED__ */


#ifndef __GOChipPCI_FWD_DEFINED__
#define __GOChipPCI_FWD_DEFINED__

#ifdef __cplusplus
typedef class GOChipPCI GOChipPCI;
#else
typedef struct GOChipPCI GOChipPCI;
#endif /* __cplusplus */

#endif 	/* __GOChipPCI_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 

/* interface __MIDL_itf_WisProxyPCI_0000 */
/* [local] */ 

typedef /* [public] */ 
enum __MIDL___MIDL_itf_WisProxyPCI_0000_0001
    {	MMSF_RAW	= 0,
	MMSF_AVI_WIS	= 1,
	MMSF_AVI_DIVX	= 2,
	MMSF_AVI_SIGMA	= 3,
	MMSF_AVI_MSFT	= 4,
	MMSF_MPEG1	= 5,
	MMSF_MPEG2	= 6,
	MMSF_WMV	= 7,
	MMSF_WMA	= 8,
	MMSF_MP2	= 9,
	MMSF_MP3	= 10,
	MMSF_NONE	= -1
    } 	EMMStrFormat;

typedef /* [public] */ 
enum __MIDL___MIDL_itf_WisProxyPCI_0000_0002
    {	AUDIO_MP1	= 0x1,
	AUDIO_MP2	= 0x2,
	AUDIO_MP3	= 0x3,
	VOICE_G7231	= 0x14
    } 	EAudioFormat;

typedef /* [public][public][public][public][public][public][public][public][public][public] */ 
enum __MIDL___MIDL_itf_WisProxyPCI_0000_0003
    {	MPEG1	= 0,
	MPEG2	= 0x1,
	H261	= 0x2,
	H263	= 0x3,
	MPEG4	= 0x4,
	MPEG4XGO	= 0x5,
	MPEG2X4	= 0x6,
	MOTIONJPEG	= 0x8,
	DV	= 0x9,
	H26L	= 0x20,
	GO	= 0x40
    } 	EVideoFormat;

typedef /* [public] */ 
enum __MIDL___MIDL_itf_WisProxyPCI_0000_0004
    {	UYVYP	= 0,
	UYVYI	= 1,
	BAYER_GB	= 2,
	BAYER_GR	= 3,
	BAYER_BG	= 4,
	BAYER_RG	= 5
    } 	EPixelMode;

typedef /* [public] */ 
enum __MIDL___MIDL_itf_WisProxyPCI_0000_0005
    {	DDRAW_YUY2	= 0x1,
	DDRAW_UYVY	= 0x2,
	DDRAW_YV12	= 0x8,
	DDRAW_RGB24	= 0x3,
	DDRAW_RGB32	= 0x4,
	DDRAW_RGB555	= 0x5,
	DDRAW_RGB565	= 0x6,
	DDRAW_DIB24	= 0x13,
	DDRAW_DIB32	= 0x14,
	DDRAW_DIB555	= 0x15,
	DDRAW_DIB565	= 0x16,
	DDRAW_NULL	= 0
    } 	EDDrawMode;

typedef /* [public][public][public][public][public][public][public][public][public][public] */ 
enum __MIDL___MIDL_itf_WisProxyPCI_0000_0006
    {	IONLY	= 1,
	IPONLY	= 2,
	IPB	= 3,
	IPBDROP	= 4
    } 	ESequenceMode;

typedef /* [public] */ 
enum __MIDL___MIDL_itf_WisProxyPCI_0000_0007
    {	I_FRAME	= 0,
	P_FRAME	= 1,
	B_FRAME	= 2,
	D_FRAME	= 3
    } 	EFrameType;

typedef /* [public] */ 
enum __MIDL___MIDL_itf_WisProxyPCI_0000_0008
    {	MB_INTRA	= 0x1,
	MB_PATTERN	= 0x2,
	MB_BACKWARD	= 0x4,
	MB_FORWARD	= 0x8,
	MB_QUANT	= 0x10,
	MB_4V	= 0x20,
	MB_DIRECT	= 0x40
    } 	EMBType;

typedef /* [public] */ 
enum __MIDL___MIDL_itf_WisProxyPCI_0000_0009
    {	PIXEL_XI_YI	= 0,
	PIXEL_XH_YI	= 0x1,
	PIXEL_XI_YH	= 0x10,
	PIXEL_XH_YH	= 0x11
    } 	EFractionPixel;

typedef /* [public] */ 
enum __MIDL___MIDL_itf_WisProxyPCI_0000_0010
    {	FLHALF	= 1,
	FLQUATER	= 2,
	FLEIGHTH	= 3,
	FLINTEGER	= 0
    } 	EFractionLevel;

typedef /* [public] */ 
enum __MIDL___MIDL_itf_WisProxyPCI_0000_0011
    {	NOSEQUENCE_HEADER	= 0x1,
	NOGOP_HEADER	= 0x2,
	NOFRAME_HEADER	= 0x4,
	NOFRAME_TAIL	= 0x8,
	NOSEQUENCE_TAIL	= 0x10,
	NOIFRAME	= 0x20,
	NOPFRAME	= 0x40,
	NOBFRAME	= 0x80
    } 	ETranscodeOption;

typedef /* [public] */ struct __MIDL___MIDL_itf_WisProxyPCI_0000_0012
    {
    unsigned char interlace;
    unsigned char mode;
    unsigned char seq;
    int cols;
    int rows;
    double fps;
    unsigned char uvmode;
    unsigned char dqmode;
    unsigned char fpmode;
    unsigned char wismode;
    unsigned char acpred;
    unsigned char userq;
    unsigned char intraq[ 64 ];
    unsigned char interq[ 64 ];
    } 	TMP_StrInfo;

typedef /* [public] */ struct __MIDL___MIDL_itf_WisProxyPCI_0000_0013
    {
    double timeStamp;
    int nGOP;
    int nSubGOP;
    int nPicture;
    double fno;
    unsigned char ftype;
    double fq;
    } 	TMP_FrmInfo;

typedef /* [public] */ struct __MIDL___MIDL_itf_WisProxyPCI_0000_0014
    {
    int col;
    int row;
    int dc[ 6 ];
    int vx[ 6 ];
    int vy[ 6 ];
    unsigned char mbtype;
    unsigned char Q;
    unsigned char cbp;
    int ach[ 6 ][ 7 ];
    int acv[ 6 ][ 7 ];
    } 	TMP_BlkInfo;

typedef /* [public] */ struct __MIDL___MIDL_itf_WisProxyPCI_0000_0015
    {
    unsigned char run[ 6 ][ 64 ];
    int lvl[ 6 ][ 64 ];
    int pair[ 6 ];
    } 	TMP_BlkPair;

typedef /* [public] */ struct __MIDL___MIDL_itf_WisProxyPCI_0000_0016
    {
    unsigned char pproc;
    int rcLeft;
    int rcTop;
    int rcWidth;
    int rcHeight;
    } 	TMP_PPrcSet;

typedef /* [public] */ struct __MIDL___MIDL_itf_WisProxyPCI_0000_0017
    {
    int SBYT;
    int EBYT;
    unsigned char SBIT;
    unsigned char EBIT;
    unsigned char Q;
    unsigned char I;
    short GOBN;
    short MBA;
    short hmvp00;
    short vmvp00;
    short hmvp10;
    short vmvp10;
    } 	TMP_StrMBInfo;

typedef /* [public][public][public][public][public][public][public][public][public][public][public][public][public][public][public][public][public][public][public][public][public][public][public][public][public][public][public][public][public][public][public][public][public][public][public][public][public][public][public][public][public][public][public][public] */ struct __MIDL___MIDL_itf_WisProxyPCI_0000_0018
    {
    unsigned char name[ 64 ];
    unsigned char desc[ 256 ];
    unsigned long flags;
    unsigned long size;
    } 	TCFG_HEADER;

typedef /* [public][public][public][public][public][public][public][public][public][public][public][public][public][public][public][public][public][public][public][public][public][public][public][public] */ 
enum __MIDL___MIDL_itf_WisProxyPCI_0000_0019
    {	TVStandard_None	= 0,
	TVStandard_NTSC_M	= 0x1,
	TVStandard_NTSC_M_J	= 0x2,
	TVStandard_NTSC_433	= 0x4,
	TVStandard_PAL_B	= 0x10,
	TVStandard_PAL_D	= 0x20,
	TVStandard_PAL_G	= 0x40,
	TVStandard_PAL_H	= 0x80,
	TVStandard_PAL_I	= 0x100,
	TVStandard_PAL_M	= 0x200,
	TVStandard_PAL_N	= 0x400,
	TVStandard_PAL_60	= 0x800,
	TVStandard_SECAM_B	= 0x1000,
	TVStandard_SECAM_D	= 0x2000,
	TVStandard_SECAM_G	= 0x4000,
	TVStandard_SECAM_H	= 0x8000,
	TVStandard_SECAM_K	= 0x10000,
	TVStandard_SECAM_K1	= 0x20000,
	TVStandard_SECAM_L	= 0x40000,
	TVStandard_SECAM_L1	= 0x80000,
	TVStandard_NTSC_Mask	= 0x807,
	TVStandard_PAL_Mask	= 0x7f0,
	TVStandard_SECAM_Mask	= 0xff000,
	TVStandard_Default	= 0xffffffff
    } 	TV_STANDARD;

typedef /* [public] */ 
enum __MIDL___MIDL_itf_WisProxyPCI_0000_0020
    {	VS_SVIDEO	= 0,
	VS_COMPOSITE	= 0x1,
	VS_TVTUNER	= 0x2,
	VS_DEFAULT	= 0xffffffff
    } 	VIDEO_SOURCE;

typedef /* [public] */ 
enum __MIDL___MIDL_itf_WisProxyPCI_0000_0021
    {	AS_TVTUNER	= 0,
	AS_LINEIN	= AS_TVTUNER + 1
    } 	AUDIO_SOURCE;

typedef /* [public][public][public][public][public] */ struct __MIDL___MIDL_itf_WisProxyPCI_0000_0022
    {
    TCFG_HEADER header;
    TV_STANDARD tv_standard;
    long framerate;
    long sensor_h;
    long sensor_v;
    unsigned char format;
    unsigned char pformat;
    unsigned char sensor_656_mode;
    unsigned char valid_enable;
    unsigned char valid_polar;
    unsigned char href_polar;
    unsigned char vref_polar;
    unsigned char field_id_polar;
    unsigned char sensor_bit_width;
    unsigned char hv_resync_enable;
    long reserved;
    } 	TCFGSYSTEM;

typedef /* [public][public][public][public][public][public][public][public][public] */ 
enum __MIDL___MIDL_itf_WisProxyPCI_0000_0023
    {	GO7007SB_MIDIAN	= 1,
	GO7007SB_LOWPASS	= 2,
	GO7007SB_NOFILTER	= 0
    } 	FilterMode;


enum MPEG4_MODE
    {	WIS_MPEG4	= 0,
	DIVX_MPEG4	= 1,
	MICROSOFT_MPEG4	= 2,
	RCC_MPEG4	= 3,
	XVID_MPEG4	= 4
    } ;
typedef /* [public][public][public][public][public][public][public][public][public] */ struct __MIDL___MIDL_itf_WisProxyPCI_0000_0024
    {
    TCFG_HEADER header;
    EVideoFormat compress_mode;
    ESequenceMode sequence;
    unsigned char gop_mode;
    unsigned long gop_size;
    unsigned char mpeg4_mode;
    unsigned char DVD_compliant;
    unsigned char deinterlace_mode;
    unsigned char search_range;
    unsigned char gop_head_enable;
    unsigned char seq_head_enable;
    unsigned char aspect_ratio;
    long reserved;
    } 	TCFGSTREAM;


enum FLAGS_STREAM
    {	FLAGS_STREAM_COMPRESS_MODE	= 0x1,
	FLAGS_STREAM_SEQUENCE_MODE	= 0x2,
	FLAGS_STREAM_GOP_MODE	= 0x4,
	FLAGS_STREAM_GOP_SIZE	= 0x8,
	FLAGS_STREAM_MPEG4_MODE	= 0x10,
	FLAGS_STREAM_DEINTERLACE_MODE	= 0x20,
	FLAGS_STREAM_SEARCH_RANGE	= 0x40,
	FLAGS_STREAM_GOPHEAD_ENABLE	= 0x80,
	FLAGS_STREAM_SEQHEAD_ENABLE	= 0x100,
	FLAGS_STREAM_ASPECT_RATIO	= 0x200,
	FLAGS_STREAM_DVD_COMPLIANT	= 0x400,
	FLAGS_STREAM_MPEG4_MANDETORY	= FLAGS_STREAM_COMPRESS_MODE + FLAGS_STREAM_MPEG4_MODE
    } ;
typedef /* [public][public][public][public][public][public][public][public][public] */ struct __MIDL___MIDL_itf_WisProxyPCI_0000_0025
    {
    TCFG_HEADER header;
    TV_STANDARD tv_standard;
    unsigned long frame_rate;
    unsigned long drop_frame;
    unsigned char ivtc_enable;
    long reserved;
    } 	TCFGFRAMERATE;


enum FLAGS_FRAMERATE
    {	FLAGS_FRAMERATE_FRAMERATE	= 0x1,
	FLAGS_FRAMERATE_IVTC_ENABLE	= 0x2,
	FLAGS_FRAMERATE_DROP_FRAME	= 0x4,
	FLAGS_FRAMERATE_TVSTANDARD	= 0x8,
	FLAGS_FRAMERATE_MANDETORY	= FLAGS_FRAMERATE_FRAMERATE + FLAGS_FRAMERATE_TVSTANDARD
    } ;
typedef /* [public][public][public][public][public][public][public][public][public] */ struct __MIDL___MIDL_itf_WisProxyPCI_0000_0026
    {
    TCFG_HEADER header;
    TV_STANDARD tv_standard;
    unsigned long width;
    unsigned long height;
    unsigned char h_sub_window;
    unsigned char v_sub_window;
    unsigned long h_sub_offset;
    unsigned long v_sub_offset;
    unsigned char h_scale_enb;
    unsigned char v_scale_enb;
    unsigned char sub_sample;
    unsigned long max_bitrate;
    unsigned long min_bitrate;
    long reserved;
    } 	TCFGRESOLUTION;


enum FLAGS_RESOLUTION
    {	FLAGS_RESOLUTION_WIDTH	= 0x1,
	FLAGS_RESOLUTION_HEIGHT	= 0x2,
	FLAGS_RESOLUTION_H_SUBWINDOW	= 0x4,
	FLAGS_RESOLUTION_V_SUBWINDOW	= 0x8,
	FLAGS_RESOLUTION_SCALE_OFFSET	= 0x10,
	FLAGS_RESOLUTION_SUBSAMPLE	= 0x100,
	FLAGS_RESOLUTION_TVSTANDARD	= 0x200,
	FLAGS_RESOLUTION_MAX_BITRATE	= 0x400,
	FLAGS_RESOLUTION_MIN_BITRATE	= 0x800,
	FLAGS_RESOLUTION_H_SUBOFFSET	= 0x1000,
	FLAGS_RESOLUTION_V_SUBOFFSET	= 0x2000,
	FLAGS_RESOLUTION_H_SCALE_ENABLE	= 0x4000,
	FLAGS_RESOLUTION_V_SCALE_ENABLE	= 0x8000,
	FLAGS_RESOLUTION_MANDETORY	= FLAGS_RESOLUTION_WIDTH + FLAGS_RESOLUTION_HEIGHT + FLAGS_RESOLUTION_TVSTANDARD + FLAGS_RESOLUTION_MAX_BITRATE + FLAGS_RESOLUTION_MIN_BITRATE
    } ;
typedef /* [public][public][public][public][public][public][public] */ struct __MIDL___MIDL_itf_WisProxyPCI_0000_0027
    {
    TCFG_HEADER header;
    unsigned long target_bitrate;
    unsigned long peak_bitrate;
    unsigned long vbv_buffer;
    unsigned char converge_speed;
    unsigned char lambda;
    unsigned long Q;
    unsigned char IQ;
    unsigned char PQ;
    unsigned char BQ;
    long reserved;
    } 	TCFGBRCTRL;


enum FLAGS_BITRATE
    {	FLAGS_BITRATE_TARGET	= 0x4,
	FLAGS_BITRATE_PEAK	= 0x8,
	FLAGS_BITRATE_VBV_BUFFER	= 0x10,
	FLAGS_BITRATE_CONVERGE_SPEED	= 0x20,
	FLAGS_BITRATE_LAMBDA	= 0x40,
	FLAGS_BITRATE_Q	= 0x80,
	FLAGS_BITRATE_IPBQ	= 0x100,
	FLAGS_BITRATE_IQ	= 0x200,
	FLAGS_BITRATE_PQ	= 0x400,
	FLAGS_BITRATE_BQ	= 0x800,
	FLAGS_BITRATE_QMIN	= 0x1000,
	FLAGS_BITRATE_QMAX	= 0x2000,
	FLAGS_BITRATE_DUP_ENABLE	= 0x4000,
	FLAGS_BITRATE_MBBRC_ENABLE	= 0x8000,
	FLAGS_BITRATE_BRC_WINDOW	= 0x10000,
	FLAGS_BITRATE_MANDETORY	= FLAGS_BITRATE_TARGET + FLAGS_BITRATE_Q
    } ;
typedef /* [public][public][public][public] */ struct __MIDL___MIDL_itf_WisProxyPCI_0000_0028
    {
    TCFG_HEADER header;
    unsigned char av_sync_enable;
    unsigned char iip_enable;
    unsigned char vbi_enable;
    unsigned char four_channel_enable;
    FilterMode h_filter_mode;
    FilterMode v_filter_mode;
    unsigned char filter_nAX;
    unsigned char filter_nBX;
    unsigned char filter_nCX;
    unsigned char filter_nAY;
    unsigned char filter_nBY;
    unsigned char filter_nCY;
    long reserved;
    } 	TCFGMISC;


enum FLAGS_MISC
    {	FLAGS_MISC_AV_SYNC_ENABLE	= 0x1,
	FLAGS_MISC_IIP_ENABLE	= 0x2,
	FLAGS_MISC_VBI_ENABLE	= 0x4,
	FLAGS_MISC_FOUR_CHANNEL_ENABLE	= 0x8,
	FLAGS_MISC_FILTER	= 0x10,
	FLAGS_MISC_MANDETORY	= 0
    } ;
typedef /* [public] */ struct __MIDL___MIDL_itf_WisProxyPCI_0000_0029
    {
    TCFGMISC misccfg;
    TCFGSTREAM strcfg;
    TCFGRESOLUTION rescfg;
    TCFGFRAMERATE fpscfg;
    TCFGBRCTRL ctlcfg;
    } 	TCFGVIDEO;

typedef /* [public][public] */ struct __MIDL___MIDL_itf_WisProxyPCI_0000_0030
    {
    TCFGSYSTEM syscfg;
    TCFGMISC misccfg;
    TCFGSTREAM strcfg;
    TCFGRESOLUTION rescfg;
    TCFGFRAMERATE fpscfg;
    TCFGBRCTRL ctlcfg;
    } 	TCFGVIDEOEX;

typedef /* [public][public] */ struct __MIDL___MIDL_itf_WisProxyPCI_0000_0031
    {
    TCFGSTREAM _stream;
    TCFGFRAMERATE _framerate;
    TCFGRESOLUTION _resolution;
    TCFGBRCTRL _bitrate;
    } 	TCFG_FORMAT_EXTENSION;

typedef struct _SENSOR_PARAMETERS
    {
    int Brightness;
    int BrightnessAuto;
    int Contrast;
    int ContrastAuto;
    int Hue;
    int HueAuto;
    int Saturation;
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
    } 	SENSOR_PARAMETERS;


enum ASSOCIATION_TYPE
    {	TYPE_SYSTEM_CONFIG	= 0,
	TYPE_STREAM_CONFIG	= TYPE_SYSTEM_CONFIG + 1,
	TYPE_RESOLUTION_CONFIG	= TYPE_STREAM_CONFIG + 1,
	TYPE_BITRATE_CONFIG	= TYPE_RESOLUTION_CONFIG + 1,
	TYPE_FRAMERATE_CONFIG	= TYPE_BITRATE_CONFIG + 1
    } ;

enum ASSOCIATION_INDEX
    {	ASSOCIATION_ALL	= 0xffffffff
    } ;

enum ASSOCIATION_PERMISSION
    {	ASSOCIATION_TYPE_ALLOW	= 0,
	ASSOCIATION_TYPE_DENY	= 1
    } ;
typedef /* [public][public][public] */ struct __MIDL___MIDL_itf_WisProxyPCI_0000_0032
    {
    enum ASSOCIATION_TYPE _master_type;
    unsigned long _master_id;
    enum ASSOCIATION_TYPE _slave_type;
    unsigned long _slave_id;
    unsigned char _associate_type;
    } 	TCFGASSOCIATION;

typedef /* [public][public][public] */ struct __MIDL___MIDL_itf_WisProxyPCI_0000_0033
    {
    unsigned long stream_index;
    unsigned long resolution_index;
    unsigned long framerate_index;
    } 	TVCFG_ENTRY;

typedef /* [public][public] */ struct __MIDL___MIDL_itf_WisProxyPCI_0000_0034
    {
    unsigned long _num_of_system_configs;
    TCFGSYSTEM _system_configs[ 16 ];
    unsigned long _num_of_stream_configs;
    TCFGSTREAM _stream_configs[ 30 ];
    unsigned long _num_of_resolution_configs;
    TCFGRESOLUTION _resolution_configs[ 30 ];
    unsigned long _num_of_framerate_configs;
    TCFGFRAMERATE _framerate_configs[ 30 ];
    unsigned long _num_of_associations;
    TCFGASSOCIATION _associations[ 300 ];
    unsigned long _num_of_configurations;
    TVCFG_ENTRY *_configurations;
    } 	_VIDEO_CAPABILITIES;

typedef /* [public] */ struct __MIDL___MIDL_itf_WisProxyPCI_0000_0035
    {
    unsigned long _num_of_stream_profiles;
    TCFGSTREAM _stream_profiles[ 30 ];
    unsigned long _stream_profile_cap_index[ 30 ];
    unsigned long _num_of_resolution_profiles;
    TCFGRESOLUTION _resolution_profiles[ 30 ];
    unsigned long _resolution_profile_cap_index[ 30 ];
    unsigned long _num_of_bitrate_profiles;
    TCFGBRCTRL _bitrate_profiles[ 30 ];
    unsigned long _bitrate_profile_cap_index[ 30 ];
    unsigned long _num_of_framerate_profiles;
    TCFGFRAMERATE _framerate_profiles[ 30 ];
    unsigned long _framerate_profile_cap_index[ 30 ];
    } 	_VIDEO_PROFILES;


enum AUDIO_CAPS
    {	CAP_AUDIO_FORMAT_PCM	= 0x1,
	CAP_AUDIO_FORMAT_ADPCM_MS	= 0x2,
	CAP_AUDIO_FORMAT_ADPCM_IMA	= 0x4,
	CAP_AUDIO_FORMAT_ALAW	= 0x8,
	CAP_AUDIO_FORMAT_ULAW	= 0x10,
	CAP_AUDIO_FORMAT_MP3	= 0x20,
	CAP_AUDIO_I2S_MASTER_MODE	= 0x40,
	CAP_AUDIO_SAMPLERATE_8K	= 0x100,
	CAP_AUDIO_SAMPLERATE_11025	= 0x200,
	CAP_AUDIO_SAMPLERATE_16K	= 0x400,
	CAP_AUDIO_SAMPLERATE_22050	= 0x800,
	CAP_AUDIO_SAMPLERATE_32K	= 0x1000,
	CAP_AUDIO_SAMPLERATE_44100	= 0x2000,
	CAP_AUDIO_SAMPLERATE_48K	= 0x4000,
	CAP_AUDIO_CHANNEL_MONO	= 0x10000,
	CAP_AUDIO_CHANNEL_STEREO	= 0x20000,
	CAP_AUDIO_SAMPLE_4BIT	= 0x40000,
	CAP_AUDIO_SAMPLE_8BIT	= 0x80000,
	CAP_AUDIO_SAMPLE_16BIT	= 0x100000
    } ;

enum AUDIO_FORMAT
    {	AUDIO_FORMAT_PCM	= 0x1,
	AUDIO_FORMAT_ADPCM_MS	= 0x2,
	AUDIO_FORMAT_ALAW	= 0x6,
	AUDIO_FORMAT_ULAW	= 0x7,
	AUDIO_FORMAT_ADPCM_IMA	= 0x11,
	AUDIO_FORMAT_MP3	= 0x55
    } ;
typedef struct _AUDIO_CONFIG
    {
    unsigned long Format;
    unsigned long SampleRate;
    unsigned long Channels;
    unsigned long SampleBits;
    unsigned short BlockAlign;
    unsigned long AvgBytesPerSec;
    unsigned short SamplesPerBlock;
    unsigned short ExtSize;
    } 	AUDIO_CONFIG;

typedef /* [public] */ struct __MIDL___MIDL_itf_WisProxyPCI_0000_0036
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
    int reserved;
    } 	TCFGAUDIO;

typedef /* [public][public] */ struct __MIDL___MIDL_itf_WisProxyPCI_0000_0037
    {
    unsigned long _format_index;
    unsigned long _samplerate_index;
    unsigned long _samplebits_index;
    unsigned long _channel_index;
    unsigned long _extension_size;
    void *_extension;
    } 	TACFG_ENTRY;

typedef /* [public] */ struct __MIDL___MIDL_itf_WisProxyPCI_0000_0038
    {
    unsigned long _num_of_format_config;
    unsigned long _audio_format_table[ 16 ];
    unsigned long _num_of_samplerate_config;
    unsigned long _audio_samplerate_table[ 16 ];
    unsigned long _num_of_samplebits_config;
    unsigned long _audio_samplebits_table[ 16 ];
    unsigned long _num_of_channel_config;
    unsigned long _audio_channel_table[ 16 ];
    unsigned long _num_of_audio_configuration;
    TACFG_ENTRY _audio_configuration[ 200 ];
    } 	_AUDIO_CAPABILITIES;

typedef struct sMotionThresholdPackage
    {
    unsigned short u16MotionThresholdMarker;
    unsigned short u16SADThresholdValues[ 7 ];
    unsigned short u16MVThresholdValues[ 7 ];
    unsigned short u16Reserved[ 17 ];
    } 	motionThresholdPackage_t;

typedef struct sMotionMacroblockMapPackage
    {
    unsigned short u16MotionPackageMarker;
    unsigned short u16StartingMacroblockNumber;
    unsigned short u16MacroblockMap[ 30 ];
    } 	motionMacroblockMapPackage_t;

typedef struct MDInterfaceData
    {
    motionThresholdPackage_t MTP;
    motionMacroblockMapPackage_t MBMap[ 9 ];
    } 	MDInterfaceData_T;

typedef void ( *CALLBACK_NEVENT )( 
    unsigned long data);

typedef /* [public][public] */ struct __MIDL___MIDL_itf_WisProxyPCI_0000_0039
    {
    unsigned __int64 VideoByte;
    unsigned long FrameCount;
    } 	STATISTIC;

typedef /* [public] */ struct __MIDL___MIDL_itf_WisProxyPCI_0000_0040
    {
    int DriverMajor;
    int DriverMinor;
    int BoardRevision;
    unsigned char BoardName[ 64 ];
    int BoardCapability;
    int MaxBandWidth;
    int SourceWidth;
    int SourceHeight;
    } 	REVISION_INFO;

typedef /* [public] */ struct __MIDL___MIDL_itf_WisProxyPCI_0000_0041
    {
    int X;
    int Y;
    unsigned short text[ 255 ];
    } 	OSDTextoutInfo;

typedef /* [public] */ 
enum __MIDL___MIDL_itf_WisProxyPCI_0000_0042
    {	NT_FATALERROR	= 0,
	NT_VSYNCLOST	= NT_FATALERROR + 1,
	NT_AVOUTOFSYNC	= NT_VSYNCLOST + 1,
	NT_TIMEOUT	= NT_AVOUTOFSYNC + 1,
	NT_SNAPSHOT	= NT_TIMEOUT + 1,
	NT_REPORTTS	= NT_SNAPSHOT + 1,
	NT_MOTIONDETECT	= NT_REPORTTS + 1,
	NT_DEVICEREMOVED	= NT_MOTIONDETECT + 1,
	NT_TVTUNERCHANGED	= NT_DEVICEREMOVED + 1,
	NT_TVAUDIOCHANGED	= NT_TVTUNERCHANGED + 1,
	NT_VIDEODECODERCHANGED	= NT_TVAUDIOCHANGED + 1
    } 	NOTIFY_TYPE;



extern RPC_IF_HANDLE __MIDL_itf_WisProxyPCI_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_WisProxyPCI_0000_v0_0_s_ifspec;

#ifndef __IGOChipPCI_INTERFACE_DEFINED__
#define __IGOChipPCI_INTERFACE_DEFINED__

/* interface IGOChipPCI */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IGOChipPCI;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("E4957E5C-BB64-4186-905E-8FC119DBA5E2")
    IGOChipPCI : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetVideoConfig( 
            TCFG_FORMAT_EXTENSION *pConfig,
            unsigned int *pError) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetStatisticInfo( 
            /* [out][in] */ STATISTIC *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetVideoCapabilities( 
            _VIDEO_CAPABILITIES *pCaps) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetVideoConfig( 
            TCFGVIDEOEX *pConfig) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ReadCBusRegFW( 
            /* [in] */ unsigned short Addr,
            /* [out] */ unsigned short *pData) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE WriteCBusRegFW( 
            /* [in] */ unsigned short Addr,
            /* [in] */ unsigned short Data) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IGOChipPCIVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IGOChipPCI * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IGOChipPCI * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IGOChipPCI * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetVideoConfig )( 
            IGOChipPCI * This,
            TCFG_FORMAT_EXTENSION *pConfig,
            unsigned int *pError);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetStatisticInfo )( 
            IGOChipPCI * This,
            /* [out][in] */ STATISTIC *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetVideoCapabilities )( 
            IGOChipPCI * This,
            _VIDEO_CAPABILITIES *pCaps);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetVideoConfig )( 
            IGOChipPCI * This,
            TCFGVIDEOEX *pConfig);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ReadCBusRegFW )( 
            IGOChipPCI * This,
            /* [in] */ unsigned short Addr,
            /* [out] */ unsigned short *pData);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *WriteCBusRegFW )( 
            IGOChipPCI * This,
            /* [in] */ unsigned short Addr,
            /* [in] */ unsigned short Data);
        
        END_INTERFACE
    } IGOChipPCIVtbl;

    interface IGOChipPCI
    {
        CONST_VTBL struct IGOChipPCIVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IGOChipPCI_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IGOChipPCI_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IGOChipPCI_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IGOChipPCI_SetVideoConfig(This,pConfig,pError)	\
    (This)->lpVtbl -> SetVideoConfig(This,pConfig,pError)

#define IGOChipPCI_GetStatisticInfo(This,pVal)	\
    (This)->lpVtbl -> GetStatisticInfo(This,pVal)

#define IGOChipPCI_GetVideoCapabilities(This,pCaps)	\
    (This)->lpVtbl -> GetVideoCapabilities(This,pCaps)

#define IGOChipPCI_GetVideoConfig(This,pConfig)	\
    (This)->lpVtbl -> GetVideoConfig(This,pConfig)

#define IGOChipPCI_ReadCBusRegFW(This,Addr,pData)	\
    (This)->lpVtbl -> ReadCBusRegFW(This,Addr,pData)

#define IGOChipPCI_WriteCBusRegFW(This,Addr,Data)	\
    (This)->lpVtbl -> WriteCBusRegFW(This,Addr,Data)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IGOChipPCI_SetVideoConfig_Proxy( 
    IGOChipPCI * This,
    TCFG_FORMAT_EXTENSION *pConfig,
    unsigned int *pError);


void __RPC_STUB IGOChipPCI_SetVideoConfig_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IGOChipPCI_GetStatisticInfo_Proxy( 
    IGOChipPCI * This,
    /* [out][in] */ STATISTIC *pVal);


void __RPC_STUB IGOChipPCI_GetStatisticInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IGOChipPCI_GetVideoCapabilities_Proxy( 
    IGOChipPCI * This,
    _VIDEO_CAPABILITIES *pCaps);


void __RPC_STUB IGOChipPCI_GetVideoCapabilities_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IGOChipPCI_GetVideoConfig_Proxy( 
    IGOChipPCI * This,
    TCFGVIDEOEX *pConfig);


void __RPC_STUB IGOChipPCI_GetVideoConfig_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IGOChipPCI_ReadCBusRegFW_Proxy( 
    IGOChipPCI * This,
    /* [in] */ unsigned short Addr,
    /* [out] */ unsigned short *pData);


void __RPC_STUB IGOChipPCI_ReadCBusRegFW_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IGOChipPCI_WriteCBusRegFW_Proxy( 
    IGOChipPCI * This,
    /* [in] */ unsigned short Addr,
    /* [in] */ unsigned short Data);


void __RPC_STUB IGOChipPCI_WriteCBusRegFW_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IGOChipPCI_INTERFACE_DEFINED__ */



#ifndef __WISPROXYLib_LIBRARY_DEFINED__
#define __WISPROXYLib_LIBRARY_DEFINED__

/* library WISPROXYLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_WISPROXYLib;

EXTERN_C const CLSID CLSID_VideoControlPropertyPage;

#ifdef __cplusplus

class DECLSPEC_UUID("35D3657A-6C20-46B0-B44A-DC8E861F1205")
VideoControlPropertyPage;
#endif

EXTERN_C const CLSID CLSID_GOChipPCI;

#ifdef __cplusplus

class DECLSPEC_UUID("E67DDCB1-652E-4843-958F-95099EEDEC8D")
GOChipPCI;
#endif
#endif /* __WISPROXYLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


