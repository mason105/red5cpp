#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define _VIDEOINFO_
#define _VIDEOINFOHEADER_
#define _TRUECOLORINFO_
#include "xmpstd.h"
#define PTCHAR TCHAR* 
#include "GrapObjRef.h"
#include <string>
using namespace std;

static IBaseFilter *FindCaptureDevice( xmp_object_t *, string *,
									  list<string> *, xmp_bool_t, list<string> * p_displayname = NULL );

static IBaseFilter * FindCaptureDevice2( xmp_object_t *p_this, 
										string *p_devicename, 
										string *p_displayname,
										list<string> *p_listdevices, 
										list<string> *p_listdiplays,
										xmp_bool_t b_audio);

static int FindDevicesCallback( xmp_object_t *p_this, char const *psz_name,
                               xmp_value_t newval, xmp_value_t oldval, void * );
static int ConfigDevicesCallback( xmp_object_t *, char const *,
								 xmp_value_t, xmp_value_t, void * );
static int ConfigDevicesCallback2( xmp_object_t *, char const *,
								  xmp_value_t, xmp_value_t, void * );

static void ShowPropertyPage( IUnknown * );
static void ShowDeviceProperties( xmp_object_t *, ICaptureGraphBuilder2 *, 
								 IBaseFilter *, xmp_bool_t );
static void ShowTunerProperties( xmp_object_t *, ICaptureGraphBuilder2 *, 
								IBaseFilter *, xmp_bool_t );
static void ConfigTuner( xmp_object_t *, ICaptureGraphBuilder2 *,
						IBaseFilter * );

static int  AccessOpen ( xmp_object_t * );
static void AccessClose( xmp_object_t * );

static int  DemuxOpen ( xmp_object_t * );
static void DemuxClose( xmp_object_t * );
static int Demux( demux_t *p_demux );
static int DemuxControl( demux_t *p_demux, int i_query, va_list args );

static block_t *ReadCompressed( access_t * );
static int AccessControl ( access_t *, int, va_list );


static char *ppsz_vdev[] = { "", "none" };
static char *ppsz_vdev_text[] = { N_("Default"), N_("None") };
static char *ppsz_adev[] = { "", "none" };
static char *ppsz_adev_text[] = { N_("Default"), N_("None") };

static char *ppsz_vdev_display[] = { "", "none" };
static char *ppsz_vdev_text_display[] = { N_("Default"), N_("None") };
static char *ppsz_adev_display[] = { "", "none" };
static char *ppsz_adev_text_display[] = { N_("Default"), N_("None") };

static int  pi_tuner_input[] = { 0, 1, 2 };
static char *ppsz_tuner_input_text[] =
{N_("Default"), N_("Cable"), N_("Antenna")};



#define CACHING_TEXT N_("Caching value in ms")
#define CACHING_LONGTEXT N_( \
    "Allows you to modify the default caching value for DirectShow streams. " \
"This value should be set in milliseconds units." )
#define VDEV_TEXT N_("Video device name")
#define VDEV_LONGTEXT N_( \
    "You can specify the name of the video device that will be used by the " \
    "DirectShow plugin. If you don't specify anything, the default device " \
"will be used.")
#define ADEV_TEXT N_("Audio device name")
#define ADEV_LONGTEXT N_( \
    "You can specify the name of the audio device that will be used by the " \
    "DirectShow plugin. If you don't specify anything, the default device " \
"will be used.")
#define VDEV_TEXT_DISPLAY N_("Video device display name")
#define VDEV_LONGTEXT_DISPLAY N_( \
    "You can specify the display name of the video device that will be used by the " \
    "DirectShow plugin. If you don't specify anything, the default device " \
"will be used.")
#define ADEV_TEXT_DISPLAY N_("Audio device display name")
#define ADEV_LONGTEXT_DISPLAY N_( \
    "You can specify the display name of the audio device that will be used by the " \
    "DirectShow plugin. If you don't specify anything, the default device " \
"will be used.")
#define SIZE_TEXT N_("Video size")
#define SIZE_LONGTEXT N_( \
    "You can specify the size of the video that will be displayed by the " \
    "DirectShow plugin. If you don't specify anything the default size for " \
"your device will be used.")
#define CHROMA_TEXT N_("Video input chroma format")
#define CHROMA_LONGTEXT N_( \
    "Force the DirectShow video input to use a specific chroma format " \
"(eg. I420 (default), RV24, etc.)")
#define FPS_TEXT N_("Video input frame rate")
#define FPS_LONGTEXT N_( \
    "Force the DirectShow video input to use a specific frame rate" \
"(eg. 0 means default, 25, 29.97, 50, 59.94, etc.)")
#define AUDIO_CHANNEL_TEXT N_("Audio input Channel")
#define AUDIO_CHANNEL_LONGTEXT N_( \
    "Allows you to set the Audio channel the audio input will set to " \
"(0 means default)." )
#define AUDIO_SAMPLESPERSEC_TEXT N_("Audio input Sample rate")
#define AUDIO_SAMPLESPERSEC_LONGTEXT N_( \
    "Allows you to set the Sample rate the audio input will set to " \
"(0 means default)." )
#define AUDIO_BITSPERSAMPLE_TEXT N_("Audio input bit per sample")
#define AUDIO_BITSPERSAMPLE_LONGTEXT N_( \
    "Allows you to set the Audio bit per sample the audio input will set to " \
"(0 means default)." )
#define PHYSCONNTYPE_TEXT N_("PhysConnType")
#define PHYSCONNTYPE_LONGTEXT N_( \
    "Allows you to set the routing information for the capture data " \
"(0 means default)." )
#define ANALOGVIDEOSTANDARD_TEXT N_("AnalogVideoStandard")
#define ANALOGVIDEOSTANDARD_LONGTEXT N_( \
    "Allows you to set the AnalogVideoStandard for VideoStandard " \
"(0 means default)." )

#define CONFIG_TEXT N_("Device properties")
#define CONFIG_LONGTEXT N_( \
    "Show the properties dialog of the selected device before starting the " \
"stream.")
#define TUNER_TEXT N_("Tuner properties")
#define TUNER_LONGTEXT N_( \
"Show the tuner properties [channel selection] page." )
#define CHANNEL_TEXT N_("Tuner TV Channel")
#define CHANNEL_LONGTEXT N_( \
    "Allows you to set the TV channel the tuner will set to " \
"(0 means default)." )
#define COUNTRY_TEXT N_("Tuner country code")
#define COUNTRY_LONGTEXT N_( \
    "Allows you to set the tuner country code that establishes the current " \
"channel-to-frequency mapping (0 means default)." )
#define TUNER_INPUT_TEXT N_("Tuner input type")
#define TUNER_INPUT_LONGTEXT N_( \
    "Allows you to select the tuner input type (Cable/Antenna)." )

xmp_module_begin();
	set_shortname( _("DirectShow") );
	set_description( _("DirectShow input") );
	set_category( CAT_INPUT );
	set_subcategory( SUBCAT_INPUT_ACCESS );
	add_integer( "dshow-caching", (mtime_t)(0.16*CLOCK_FREQ) / 1000, NULL,
				CACHING_TEXT, CACHING_LONGTEXT, XMP_TRUE );

	add_string( "dshow-vdev", NULL, NULL, VDEV_TEXT, VDEV_LONGTEXT, XMP_FALSE);
	change_string_list( ppsz_vdev, ppsz_vdev_text, FindDevicesCallback );
	change_action_add( FindDevicesCallback, N_("Refresh list") );
	change_action_add( ConfigDevicesCallback, N_("Configure") );
	change_action_add( ConfigDevicesCallback2, N_("Configure2") );

	add_string( "dshow-adev", NULL, NULL, ADEV_TEXT, ADEV_LONGTEXT, XMP_FALSE);
	change_string_list( ppsz_adev, ppsz_adev_text, FindDevicesCallback );
	change_action_add( FindDevicesCallback, N_("Refresh list") );
	change_action_add( ConfigDevicesCallback, N_("Configure") );
	change_action_add( ConfigDevicesCallback2, N_("Configure2") );

	add_string( "dshow-vdev-display", NULL, NULL, VDEV_TEXT_DISPLAY, VDEV_LONGTEXT_DISPLAY, XMP_FALSE);
	change_string_list( ppsz_vdev_display, ppsz_vdev_text_display, NULL );
	add_string( "dshow-adev-display", NULL, NULL, ADEV_TEXT_DISPLAY, ADEV_LONGTEXT_DISPLAY, XMP_FALSE);
	change_string_list( ppsz_adev_display, ppsz_adev_text_display, NULL );

	add_string( "dshow-size", NULL, NULL, SIZE_TEXT, SIZE_LONGTEXT, XMP_FALSE);

	add_string( "dshow-chroma", NULL, NULL, CHROMA_TEXT, CHROMA_LONGTEXT,
			   XMP_TRUE );
	add_string( "dshow-deviceconfig", NULL, NULL, CHROMA_TEXT, "deviceconfig",
		XMP_TRUE );
	
	add_float( "dshow-fps", 0.0f, NULL, FPS_TEXT, FPS_LONGTEXT,
			  XMP_TRUE );

	add_integer( "dshow-audio-channel", 0, NULL, AUDIO_CHANNEL_TEXT,
				AUDIO_CHANNEL_LONGTEXT, XMP_TRUE );
	add_integer( "dshow-audio-samplespersec", 0, NULL, AUDIO_SAMPLESPERSEC_TEXT,
				AUDIO_SAMPLESPERSEC_LONGTEXT, XMP_TRUE );
	add_integer( "dshow-audio-bitspersample", 0, NULL, AUDIO_BITSPERSAMPLE_TEXT,
				AUDIO_BITSPERSAMPLE_LONGTEXT, XMP_TRUE );

	add_integer( "dshow-PhysConnType", 0, NULL, PHYSCONNTYPE_TEXT,
		PHYSCONNTYPE_LONGTEXT, XMP_TRUE );
	add_integer( "dshow-AnalogVideoStandard", 0, NULL, ANALOGVIDEOSTANDARD_TEXT,
		ANALOGVIDEOSTANDARD_LONGTEXT, XMP_TRUE );
	
	add_bool( "dshow-config", XMP_FALSE, NULL, CONFIG_TEXT, CONFIG_LONGTEXT,
			 XMP_TRUE );

	add_bool( "dshow-tuner", XMP_FALSE, NULL, TUNER_TEXT, TUNER_LONGTEXT,
			 XMP_TRUE );

	add_integer( "dshow-tuner-channel", 0, NULL, CHANNEL_TEXT,
				CHANNEL_LONGTEXT, XMP_TRUE );

	add_integer( "dshow-tuner-country", 0, NULL, COUNTRY_TEXT,
				COUNTRY_LONGTEXT, XMP_TRUE );

	add_integer( "dshow-tuner-input", 0, NULL, TUNER_INPUT_TEXT,
				TUNER_INPUT_LONGTEXT, XMP_TRUE );
	change_integer_list( pi_tuner_input, ppsz_tuner_input_text, 0 );

	add_shortcut( "dshow" );
	set_capability( "access_demux", 0 );
	set_callbacks( DemuxOpen, DemuxClose );

	add_submodule();
	set_description( _("DirectShow input") );
	add_shortcut( "dshow" );
	set_capability( "access2", 0 );
	set_callbacks( AccessOpen, AccessClose );

xmp_module_end();
struct access_sys_t
{
    /* These 2 must be left at the beginning */
    xmp_mutex_t lock;
    xmp_cond_t  wait;
	CGrapObjRef* fgb;
};	

int  DemuxOpen ( xmp_object_t * p_this)
{
	demux_t      *p_demux = (demux_t *)p_this;
	access_sys_t *p_sys;
	int i;
	
	p_sys = (access_sys_t *)malloc( sizeof( access_sys_t ) );
	memset( p_sys, 0, sizeof( access_sys_t ) );
	p_demux->p_sys = (demux_sys_t *)p_sys;		
	p_sys->fgb = new CGrapObjRef;
	
    xmp_value_t  val;
	
    /* Get/parse options and open device(s) */
    string			vdevname, adevname;
	string			vdevname_display, adevname_display;
	int				i_width = 0, i_height = 0, i_chroma = 0;
	int				i_channels = 0;
	int				i_samplespersec = 0;
	int				i_bitspersample = 0;
	int				i_PhysConnType  = 0;
	int				i_AnalogVideoStandard = 0;
	int				i_vcodec = 0;
	int				i_acodec = 0;
	int				i_vb = 0;
	int				i_ab = 0;
	char			szDeviceConfigFile[512] = "";
	
    xmp_bool_t b_audio = XMP_TRUE;
	
    var_Create( p_this, "dshow-config", XMP_VAR_BOOL | XMP_VAR_DOINHERIT );
    var_Create( p_this, "dshow-tuner", XMP_VAR_BOOL | XMP_VAR_DOINHERIT );
	
    var_Create( p_this, "dshow-vdev", XMP_VAR_STRING | XMP_VAR_DOINHERIT );
    var_Get( p_this, "dshow-vdev", &val );
    if( val.psz_string ) vdevname = string( val.psz_string );
    if( val.psz_string ) free( val.psz_string );
	
    var_Create( p_this, "dshow-adev", XMP_VAR_STRING | XMP_VAR_DOINHERIT );
    var_Get( p_this, "dshow-adev", &val );
    if( val.psz_string ) adevname = string( val.psz_string );
    if( val.psz_string ) free( val.psz_string );
	
    var_Create( p_this, "dshow-vdev-display", XMP_VAR_STRING | XMP_VAR_DOINHERIT );
    var_Get( p_this, "dshow-vdev-display", &val );
    if( val.psz_string ) vdevname_display = string( val.psz_string );
    if( val.psz_string ) free( val.psz_string );
	
    var_Create( p_this, "dshow-adev-display", XMP_VAR_STRING | XMP_VAR_DOINHERIT );
    var_Get( p_this, "dshow-adev-display", &val );
    if( val.psz_string ) adevname_display = string( val.psz_string );
    if( val.psz_string ) free( val.psz_string );
	
    static struct {char *psz_size; int  i_width; int  i_height;} size_table[] =
    { { "subqcif", 128, 96 }, { "qsif", 160, 120 }, { "qcif", 176, 144 },
	{ "sif", 320, 240 }, { "cif", 352, 288 }, { "cif", 640, 480 },
	{ 0, 0, 0 },
    };
	
    var_Create( p_this, "dshow-size", XMP_VAR_STRING | XMP_VAR_DOINHERIT );
    var_Get( p_this, "dshow-size", &val );
    if( val.psz_string && *val.psz_string )
    {
        for( i = 0; size_table[i].psz_size; i++ )
        {
            if( !strcmp( val.psz_string, size_table[i].psz_size ) )
            {
                i_width = size_table[i].i_width;
                i_height = size_table[i].i_height;
                break;
            }
        }
        if( !size_table[i].psz_size ) /* Try to parse "WidthxHeight" */
        {
            char *psz_parser;
            i_width = strtol( val.psz_string, &psz_parser, 0 );
            if( *psz_parser == 'x' || *psz_parser == 'X')
            {
                i_height = strtol( psz_parser + 1, &psz_parser, 0 );
            }
            msg_Dbg( p_this, "Width x Height %dx%d", i_width, i_height );
        }
    }
    if( val.psz_string ) free( val.psz_string );
	
    var_Create( p_this, "dshow-chroma", XMP_VAR_STRING | XMP_VAR_DOINHERIT );
    var_Get( p_this, "dshow-chroma", &val );
    if( val.psz_string && strlen( val.psz_string ) >= 4 )
    {
        i_chroma = XMP_FOURCC( val.psz_string[0], val.psz_string[1],
			val.psz_string[2], val.psz_string[3] );
    }
    if( val.psz_string ) free( val.psz_string );

    var_Create( p_this, "dshow-deviceconfig", XMP_VAR_STRING | XMP_VAR_DOINHERIT );
    var_Get( p_this, "dshow-deviceconfig", &val );
    if( val.psz_string && strlen( val.psz_string ) >= 1 )
    {
        strcpy(szDeviceConfigFile, val.psz_string);
    }
    if( val.psz_string ) free( val.psz_string );
	
    var_Create( p_this, "dshow-fps", XMP_VAR_FLOAT | XMP_VAR_DOINHERIT );
	var_Create( p_this, "dshow-audio-channel",
		XMP_VAR_INTEGER | XMP_VAR_DOINHERIT );
	var_Create( p_this, "dshow-audio-samplespersec",
		XMP_VAR_INTEGER | XMP_VAR_DOINHERIT );
	var_Create( p_this, "dshow-audio-bitspersample",
		XMP_VAR_INTEGER | XMP_VAR_DOINHERIT );
	var_Create( p_this, "dshow-tuner-channel",
		XMP_VAR_INTEGER | XMP_VAR_DOINHERIT );
    var_Create( p_this, "dshow-tuner-country",
		XMP_VAR_INTEGER | XMP_VAR_DOINHERIT );
    var_Create( p_this, "dshow-tuner-input",
		XMP_VAR_INTEGER | XMP_VAR_DOINHERIT );
    var_Create( p_this, "dshow-PhysConnType",
		XMP_VAR_INTEGER | XMP_VAR_DOINHERIT );
    var_Create( p_this, "dshow-AnalogVideoStandard",
		XMP_VAR_INTEGER | XMP_VAR_DOINHERIT );
	
    var_Create( p_this, "dshow-caching", XMP_VAR_INTEGER | XMP_VAR_DOINHERIT );
	
	i_channels = var_GetInteger( p_this, "dshow-audio-channel" );
	i_samplespersec = var_GetInteger( p_this, "dshow-audio-samplespersec" );
	i_bitspersample = var_GetInteger( p_this, "dshow-audio-bitspersample" );
	i_PhysConnType	= var_GetInteger( p_this, "dshow-PhysConnType" );
	i_AnalogVideoStandard	= var_GetInteger( p_this, "dshow-AnalogVideoStandard" );

    float r_fps = var_GetFloat( p_this, "dshow-fps" );
	xmp_value_t val_dshowconfig;
	var_Get( p_this, "dshow-config", &val_dshowconfig );
	xmp_value_t val_dshowtuner;
	var_Get( p_this, "dshow-tuner", &val_dshowtuner );
	
	/* Initialize OLE/COM */
    CoInitialize( 0 );
		
    xmp_mutex_init( p_this, &p_sys->lock );
    xmp_cond_init( p_this, &p_sys->wait );

#define SOUT_CFG_PREFIX "sout-transcode-"
	sout_instance_t *p_sout= (sout_instance_t *)xmp_object_find(p_this,
		XMP_OBJECT_SOUT, FIND_ANYWHERE);
	if(p_sout)
	{
		sout_stream_t     *p_stream = (sout_stream_t*)p_sout->p_stream;
		if(p_stream)
		{
			xmp_value_t val_vcodec;
			var_Get( p_stream, SOUT_CFG_PREFIX "vcodec", &val_vcodec );
			xmp_value_t val_acodec;
			var_Get( p_stream, SOUT_CFG_PREFIX "acodec", &val_acodec );			
			xmp_value_t val_vb;
			var_Get( p_stream, SOUT_CFG_PREFIX "vb", &val_vb );
			xmp_value_t val_ab;
			var_Get( p_stream, SOUT_CFG_PREFIX "ab", &val_ab );

			if( val_vcodec.psz_string && (int)val_vcodec.psz_string != 0xcccccccc) 
			{
				i_vcodec = XMP_FOURCC( val_vcodec.psz_string[0], val_vcodec.psz_string[1],
					val_vcodec.psz_string[2], val_vcodec.psz_string[3] );
				free( val_vcodec.psz_string );
			}
			if( val_acodec.psz_string && (int)val_acodec.psz_string != 0xcccccccc)  
			{
				i_acodec = XMP_FOURCC( val_acodec.psz_string[0], val_acodec.psz_string[1],
					val_acodec.psz_string[2], val_acodec.psz_string[3] );
				free( val_acodec.psz_string );
			}
			i_vb = val_vb.i_int;
			i_ab = val_ab.i_int;
			
		}
		xmp_object_release( p_sout );
		
	}
	
	char psz_name[4098];
	sprintf(psz_name, "dshow-vdev=%s;\
dshow-adev=%s;\
dshow-vdev-display=%s;\
dshow-adev-display=%s;\
Width=%d;\
Height=%d;\
dshow-chroma=%d;\
dshow-fps=%f;\
dshow-audio-channel=%d;\
dshow-audio-samplespersec=%d;\
dshow-audio-bitspersample=%d;\
dshow-config=%d;\
dshow-tuner=%d;\
dshow-PhysConnType=%d;\
dshow-AnalogVideoStandard=%d;\
dshow-vcodec=%d;dshow-acodec=%d;\
dshow-vb=%d;dshow-ab=%d;", 
		vdevname.c_str(),
		adevname.c_str(),
		vdevname_display.c_str(),
		adevname_display.c_str(),
		i_width,
		i_height,
		i_chroma,
		r_fps,
		i_channels,
		i_samplespersec,
		i_bitspersample,
		val_dshowconfig.b_bool,
		val_dshowtuner.b_bool,
		i_PhysConnType,
		i_AnalogVideoStandard,
		i_vcodec,
		i_acodec,
		i_vb,
		i_ab);
	
	
	if(strlen(szDeviceConfigFile))
	{
		if(FAILED(p_sys->fgb->InitializeFromConfig(szDeviceConfigFile)))
		{
			AccessClose(p_this);
			return XMP_EGENERIC;		
		}
	}
	else
	{
		if(FAILED(p_sys->fgb->Initialize(psz_name)))
		{
			AccessClose(p_this);
			return XMP_EGENERIC;		
		}
	}

	if(p_sys->fgb->get_streamcount() <= 0)
		return XMP_EGENERIC;		
	

	CDShowStream *p_stream = p_sys->fgb->get_stream(0);	
	if(p_stream == NULL)
	{
		DemuxClose(p_this);
		return XMP_EGENERIC;
	}
	if( p_stream->mt.majortype == MEDIATYPE_Stream )
	{
		DemuxClose(p_this);
		return XMP_EGENERIC;		
	}
	p_demux->pf_demux   = Demux;
    p_demux->pf_control = DemuxControl;
    p_demux->info.i_update = 0;
    p_demux->info.i_title = 0;
    p_demux->info.i_seekpoint = 0;
	
    for( i = 0; i < p_sys->fgb->get_streamcount(); i++ )
    {
        CDShowStream *p_stream = p_sys->fgb->get_stream(i);
        es_format_t fmt;
		
        if( p_stream->mt.majortype == MEDIATYPE_Video )
        {
            es_format_Init( &fmt, VIDEO_ES, p_stream->i_fourcc );
			
            fmt.video.i_width  = p_stream->header.video.bmiHeader.biWidth;
            fmt.video.i_height = p_stream->header.video.bmiHeader.biHeight;
            fmt.video.i_aspect = 4 * VOUT_ASPECT_FACTOR / 3;
			
            if( !p_stream->header.video.bmiHeader.biCompression )
            {
                /* RGB DIB are coded from bottom to top */
                fmt.video.i_height = (unsigned int)(-(int)fmt.video.i_height);
            }
			
            /* Setup rgb mask for RGB formats */
            if( p_stream->i_fourcc == XMP_FOURCC('R','V','2','4') )
            {
                /* This is in BGR format */
                fmt.video.i_bmask = 0x00ff0000;
                fmt.video.i_gmask = 0x0000ff00;
                fmt.video.i_rmask = 0x000000ff;
            }
			
            if( p_stream->header.video.AvgTimePerFrame )
            {
                fmt.video.i_frame_rate = 10000000;
                fmt.video.i_frame_rate_base =
                    p_stream->header.video.AvgTimePerFrame;
            }
        }
        else if( p_stream->mt.majortype == MEDIATYPE_Audio )
        {
            es_format_Init( &fmt, AUDIO_ES, p_stream->i_fourcc );
			
            fmt.audio.i_channels = p_stream->header.audio.nChannels;
            fmt.audio.i_rate = p_stream->header.audio.nSamplesPerSec;
            fmt.audio.i_bitspersample = p_stream->header.audio.wBitsPerSample;
            fmt.audio.i_blockalign = fmt.audio.i_channels *
                fmt.audio.i_bitspersample / 8;
            fmt.i_bitrate = fmt.audio.i_channels * fmt.audio.i_rate *
                fmt.audio.i_bitspersample;
        }
		
        p_stream->p_es = es_out_Add( p_demux->out, &fmt );
    }	

	if(FAILED(p_sys->fgb->Run()))
	{
		DemuxClose(p_this);
		return XMP_EGENERIC;
	}
	
	Sleep(100);
	
	return XMP_SUCCESS;
}
static int AccessOpen( xmp_object_t *p_this )
{
    access_t     *p_access = (access_t*)p_this;
    access_sys_t *p_sys;
	int i;
	
    p_access->p_sys = p_sys = (access_sys_t *)malloc( sizeof( access_sys_t ) );
    memset( p_sys, 0, sizeof( access_sys_t ) );
	p_access->p_sys = (access_sys_t *)p_sys;		
	p_sys->fgb = new CGrapObjRef;
	
    xmp_value_t  val;
	
    /* Get/parse options and open device(s) */
    string			vdevname, adevname;
	string			vdevname_display, adevname_display;
	int				i_width = 0, i_height = 0, i_chroma = 0;
	int				i_channels = 0;
	int				i_samplespersec = 0;
	int				i_bitspersample = 0;
	int				i_PhysConnType  = 0;
	int				i_AnalogVideoStandard = 0;
	int				i_vcodec = 0;
	int				i_acodec = 0;
	int				i_vb = 0;
	int				i_ab = 0;
	char			szDeviceConfigFile[512] = "";
	
    xmp_bool_t b_audio = XMP_TRUE;
	
    var_Create( p_this, "dshow-config", XMP_VAR_BOOL | XMP_VAR_DOINHERIT );
    var_Create( p_this, "dshow-tuner", XMP_VAR_BOOL | XMP_VAR_DOINHERIT );
	
    var_Create( p_this, "dshow-vdev", XMP_VAR_STRING | XMP_VAR_DOINHERIT );
    var_Get( p_this, "dshow-vdev", &val );
    if( val.psz_string ) vdevname = string( val.psz_string );
    if( val.psz_string ) free( val.psz_string );
	
    var_Create( p_this, "dshow-adev", XMP_VAR_STRING | XMP_VAR_DOINHERIT );
    var_Get( p_this, "dshow-adev", &val );
    if( val.psz_string ) adevname = string( val.psz_string );
    if( val.psz_string ) free( val.psz_string );
	
    var_Create( p_this, "dshow-vdev-display", XMP_VAR_STRING | XMP_VAR_DOINHERIT );
    var_Get( p_this, "dshow-vdev-display", &val );
    if( val.psz_string ) vdevname_display = string( val.psz_string );
    if( val.psz_string ) free( val.psz_string );
	
    var_Create( p_this, "dshow-adev-display", XMP_VAR_STRING | XMP_VAR_DOINHERIT );
    var_Get( p_this, "dshow-adev-display", &val );
    if( val.psz_string ) adevname_display = string( val.psz_string );
    if( val.psz_string ) free( val.psz_string );
	
    static struct {char *psz_size; int  i_width; int  i_height;} size_table[] =
    { { "subqcif", 128, 96 }, { "qsif", 160, 120 }, { "qcif", 176, 144 },
	{ "sif", 320, 240 }, { "cif", 352, 288 }, { "cif", 640, 480 },
	{ 0, 0, 0 },
    };
	
    var_Create( p_this, "dshow-size", XMP_VAR_STRING | XMP_VAR_DOINHERIT );
    var_Get( p_this, "dshow-size", &val );
    if( val.psz_string && *val.psz_string )
    {
        for( i = 0; size_table[i].psz_size; i++ )
        {
            if( !strcmp( val.psz_string, size_table[i].psz_size ) )
            {
                i_width = size_table[i].i_width;
                i_height = size_table[i].i_height;
                break;
            }
        }
        if( !size_table[i].psz_size ) /* Try to parse "WidthxHeight" */
        {
            char *psz_parser;
            i_width = strtol( val.psz_string, &psz_parser, 0 );
            if( *psz_parser == 'x' || *psz_parser == 'X')
            {
                i_height = strtol( psz_parser + 1, &psz_parser, 0 );
            }
            msg_Dbg( p_this, "Width x Height %dx%d", i_width, i_height );
        }
    }
    if( val.psz_string ) free( val.psz_string );
	
    var_Create( p_this, "dshow-chroma", XMP_VAR_STRING | XMP_VAR_DOINHERIT );
    var_Get( p_this, "dshow-chroma", &val );
    if( val.psz_string && strlen( val.psz_string ) >= 4 )
    {
        i_chroma = XMP_FOURCC( val.psz_string[0], val.psz_string[1],
			val.psz_string[2], val.psz_string[3] );
    }
    if( val.psz_string ) free( val.psz_string );
	
	var_Create( p_this, "dshow-deviceconfig", XMP_VAR_STRING | XMP_VAR_DOINHERIT );
    var_Get( p_this, "dshow-deviceconfig", &val );
    if( val.psz_string && strlen( val.psz_string ) >= 1 )
    {
        strcpy(szDeviceConfigFile, val.psz_string);
    }
    if( val.psz_string ) free( val.psz_string );

    var_Create( p_this, "dshow-fps", XMP_VAR_FLOAT | XMP_VAR_DOINHERIT );
	var_Create( p_this, "dshow-audio-channel",
		XMP_VAR_INTEGER | XMP_VAR_DOINHERIT );
	var_Create( p_this, "dshow-audio-samplespersec",
		XMP_VAR_INTEGER | XMP_VAR_DOINHERIT );
	var_Create( p_this, "dshow-audio-bitspersample",
		XMP_VAR_INTEGER | XMP_VAR_DOINHERIT );
	var_Create( p_this, "dshow-tuner-channel",
		XMP_VAR_INTEGER | XMP_VAR_DOINHERIT );
    var_Create( p_this, "dshow-tuner-country",
		XMP_VAR_INTEGER | XMP_VAR_DOINHERIT );
    var_Create( p_this, "dshow-tuner-input",
		XMP_VAR_INTEGER | XMP_VAR_DOINHERIT );
    var_Create( p_this, "dshow-PhysConnType",
		XMP_VAR_INTEGER | XMP_VAR_DOINHERIT );
    var_Create( p_this, "dshow-AnalogVideoStandard",
		XMP_VAR_INTEGER | XMP_VAR_DOINHERIT );
	
    var_Create( p_this, "dshow-caching", XMP_VAR_INTEGER | XMP_VAR_DOINHERIT );
	
	i_channels = var_GetInteger( p_this, "dshow-audio-channel" );
	i_samplespersec = var_GetInteger( p_this, "dshow-audio-samplespersec" );
	i_bitspersample = var_GetInteger( p_this, "dshow-audio-bitspersample" );
	i_PhysConnType	= var_GetInteger( p_this, "dshow-PhysConnType" );
	i_AnalogVideoStandard	= var_GetInteger( p_this, "dshow-AnalogVideoStandard" );

    float r_fps = var_GetFloat( p_this, "dshow-fps" );
	xmp_value_t val_dshowconfig;
	var_Get( p_this, "dshow-config", &val_dshowconfig );
	xmp_value_t val_dshowtuner;
	var_Get( p_this, "dshow-tuner", &val_dshowtuner );
	
	/* Initialize OLE/COM */
    CoInitialize( 0 );
		
    xmp_mutex_init( p_this, &p_sys->lock );
    xmp_cond_init( p_this, &p_sys->wait );

#define SOUT_CFG_PREFIX "sout-transcode-"
	sout_instance_t *p_sout= (sout_instance_t *)xmp_object_find(p_this,
		XMP_OBJECT_SOUT, FIND_ANYWHERE);
	if(p_sout)
	{
		sout_stream_t     *p_stream = (sout_stream_t*)p_sout->p_stream;
		if(p_stream)
		{
			xmp_value_t val_vcodec;
			var_Get( p_stream, SOUT_CFG_PREFIX "vcodec", &val_vcodec );
			xmp_value_t val_acodec;
			var_Get( p_stream, SOUT_CFG_PREFIX "acodec", &val_acodec );			
			xmp_value_t val_vb;
			var_Get( p_stream, SOUT_CFG_PREFIX "vb", &val_vb );
			xmp_value_t val_ab;
			var_Get( p_stream, SOUT_CFG_PREFIX "ab", &val_ab );

			if( val_vcodec.psz_string && (int)val_vcodec.psz_string != 0xcccccccc) 
			{
				i_vcodec = XMP_FOURCC( val_vcodec.psz_string[0], val_vcodec.psz_string[1],
					val_vcodec.psz_string[2], val_vcodec.psz_string[3] );
				free( val_vcodec.psz_string );
			}
			if( val_acodec.psz_string && (int)val_acodec.psz_string != 0xcccccccc)  
			{
				i_acodec = XMP_FOURCC( val_acodec.psz_string[0], val_acodec.psz_string[1],
					val_acodec.psz_string[2], val_acodec.psz_string[3] );
				free( val_acodec.psz_string );
			}
			i_vb = val_vb.i_int;
			i_ab = val_ab.i_int;
			
		}
		xmp_object_release( p_sout );
		
	}
	
	char psz_name[4098];
	sprintf(psz_name, "dshow-vdev=%s;\
dshow-adev=%s;\
dshow-vdev-display=%s;\
dshow-adev-display=%s;\
Width=%d;\
Height=%d;\
dshow-chroma=%d;\
dshow-fps=%f;\
dshow-audio-channel=%d;\
dshow-audio-samplespersec=%d;\
dshow-audio-bitspersample=%d;\
dshow-config=%d;\
dshow-tuner=%d;\
dshow-PhysConnType=%d;\
dshow-AnalogVideoStandard=%d;\
dshow-vcodec=%d;dshow-acodec=%d;\
dshow-vb=%d;dshow-ab=%d;", 
		vdevname.c_str(),
		adevname.c_str(),
		vdevname_display.c_str(),
		adevname_display.c_str(),
		i_width,
		i_height,
		i_chroma,
		r_fps,
		i_channels,
		i_samplespersec,
		i_bitspersample,
		val_dshowconfig.b_bool,
		val_dshowtuner.b_bool,
		i_PhysConnType,
		i_AnalogVideoStandard,
		i_vcodec,
		i_acodec,
		i_vb,
		i_ab);
	
	if(strlen(szDeviceConfigFile))
	{
		if(FAILED(p_sys->fgb->InitializeFromConfig(szDeviceConfigFile)))
		{
			AccessClose(p_this);
			return XMP_EGENERIC;		
		}
	}
	else
	{
		if(FAILED(p_sys->fgb->Initialize(psz_name)))
		{
			AccessClose(p_this);
			return XMP_EGENERIC;		
		}
	}
	
    CDShowStream *p_stream = p_sys->fgb->get_stream(0);
	if(p_stream == NULL)
	{
		AccessClose(p_this);
		return XMP_EGENERIC;
		
	}
	
	
    /* Check if we need to force demuxers */
    if( !p_access->psz_demux || !*p_access->psz_demux )
    {
        if( p_stream->i_fourcc == XMP_FOURCC('d','v','s','l') ||
            p_stream->i_fourcc == XMP_FOURCC('d','v','s','d') ||
            p_stream->i_fourcc == XMP_FOURCC('d','v','h','d') )
        {
            p_access->psz_demux = strdup( "rawdv" );
        }
        else if( p_stream->i_fourcc == XMP_FOURCC('m','p','2','v') )
        {
            p_access->psz_demux = strdup("mpgv");
        }
		else if( p_stream->i_fourcc == XMP_FOURCC('m','p','1','v') )
        {
            p_access->psz_demux = strdup("mpgv");
        }
        else if( p_stream->i_fourcc == XMP_FOURCC('m', 'p', '2', 'p') )
        {
            p_access->psz_demux = strdup("ps");
        }
        else if( p_stream->i_fourcc == XMP_FOURCC('m', 'p', '2', 't') )
        {
            p_access->psz_demux = strdup("ts");
        }
	}
	
    /* Setup Access */
    p_access->pf_read = NULL;
    p_access->pf_block = ReadCompressed;
    p_access->pf_control = AccessControl;
    p_access->pf_seek = NULL;
    p_access->info.i_update = 0;
    p_access->info.i_size = 0;
    p_access->info.i_pos = 0;
    p_access->info.b_eof = XMP_FALSE;
    p_access->info.i_title = 0;
    p_access->info.i_seekpoint = 0;
    p_access->p_sys = p_sys;
	
    /* Everything is ready. Let's rock baby */
   	if(FAILED(p_sys->fgb->Run()))
	{
		AccessClose(p_this);
		return XMP_EGENERIC;
	}
	
	Sleep(100);
	
    return XMP_SUCCESS;
}
 void DemuxClose( xmp_object_t * p_this)
{
	 demux_t      *p_demux = (demux_t *)p_this;
	 access_sys_t *p_sys    = (access_sys_t*)p_demux->p_sys;
	 if(p_sys)
	 {
		 p_sys->fgb->Stop();
		 p_sys->fgb->Cleanup();	 
		 CoUninitialize();
		 delete p_sys->fgb;
		 xmp_mutex_destroy( &p_sys->lock );
		 xmp_cond_destroy( &p_sys->wait );
		 free(p_sys);
	 }
}
 static void AccessClose( xmp_object_t *p_this )
 {
	 demux_t      *p_demux = (demux_t *)p_this;
	 access_sys_t *p_sys    = (access_sys_t*)p_demux->p_sys;
	 if(p_sys)
	 {
		 p_sys->fgb->Stop();
		 p_sys->fgb->Cleanup();	 
		 CoUninitialize();
		 delete p_sys->fgb;
		 xmp_mutex_destroy( &p_sys->lock );
		 xmp_cond_destroy( &p_sys->wait );
		 free(p_sys);
	 }
 }
 static int Demux( demux_t *p_demux )
 {
	 access_sys_t *p_sys    = (access_sys_t*)p_demux->p_sys;
	 CDShowStream *p_stream = NULL;
	 XMPMediaSample sample;
	 int i_data_size, i_stream;	
	 uint8_t *p_data;
	 block_t *p_block;
	 xmp_mutex_lock( &p_sys->lock );
	 for( i_stream = 0; i_stream < p_sys->fgb->get_streamcount(); i_stream++ )
	 {
		 p_stream = p_sys->fgb->get_stream(i_stream);
		 if( p_stream->mt.majortype == MEDIATYPE_Audio &&
			 p_stream->p_capture_filter &&
			 p_stream->p_capture_filter->CustomGetPin()
			 ->CustomGetSample( &sample ) == S_OK )
		 {
			 break;
		 }
	 }
	 if( i_stream == p_sys->fgb->get_streamcount() )
	 {
		 for( i_stream = 0; i_stream < p_sys->fgb->get_streamcount(); i_stream++ )
		 {
			 p_stream = p_sys->fgb->get_stream(i_stream);
			 if( p_stream->p_capture_filter &&
				 p_stream->p_capture_filter->CustomGetPin()
				 ->CustomGetSample( &sample ) == S_OK )
			 {
				 break;
			 }
		 }
	 }
	  xmp_mutex_unlock( &p_sys->lock );

    if( i_stream == p_sys->fgb->get_streamcount() )
    {
        /* Sleep so we do not consume all the cpu, 10ms seems
         * like a good value (100fps) */
        msleep( 10000 );
        return 1;
    }
    i_data_size = sample.p_sample->GetActualDataLength();
    sample.p_sample->GetPointer( &p_data );
	
    REFERENCE_TIME i_pts, i_end_date;
    HRESULT hr = sample.p_sample->GetTime( &i_pts, &i_end_date );
    if( hr != VFW_S_NO_STOP_TIME && hr != S_OK ) i_pts = 0;
	
    if( !i_pts )
    {
        if( p_stream->mt.majortype == MEDIATYPE_Video || !p_stream->b_pts )
        {
            /* Use our data timestamp */
            i_pts = sample.i_timestamp;
            p_stream->b_pts = XMP_TRUE;
        }
    }
	
    i_pts /= 10; /* Dshow works with 100 nano-seconds resolution */
	
#if 0
    ATLTRACE("Read() stream: %i, size: %i, PTS: "I64Fd"\n",
		i_stream, i_data_size, i_pts );
#endif
	
    p_block = block_New( p_demux, i_data_size );
    p_demux->p_xmp->pf_memcpy( p_block->p_buffer, p_data, i_data_size );
    p_block->i_pts = p_block->i_dts = i_pts;
	if(sample.p_sample->IsSyncPoint())
		p_block->i_flags |= BLOCK_FLAG_TYPE_I;
    sample.p_sample->Release();
	
    es_out_Control( p_demux->out, ES_OUT_SET_PCR, i_pts > 0 ? i_pts : 0 );
    es_out_Send( p_demux->out,(es_out_id_t*) p_stream->p_es, p_block );
	
	 return 1;
 }
  int DemuxControl( demux_t *p_demux, int i_query, va_list args )
 {
	 xmp_bool_t *pb;
	 int64_t    *pi64;
	 access_sys_t *p_sys    = (access_sys_t*)p_demux->p_sys;
	 
	 switch( i_query )
	 {
		 /* Special for access_demux */
	 case DEMUX_CAN_PAUSE:
	 case DEMUX_SET_PAUSE_STATE:
	 case DEMUX_CAN_CONTROL_PACE:
		 pb = (xmp_bool_t*)va_arg( args, xmp_bool_t * );
		 *pb = XMP_FALSE;
		 return XMP_SUCCESS;
		 
	 case DEMUX_GET_PTS_DELAY:
		 pi64 = (int64_t*)va_arg( args, int64_t * );
		 *pi64 = 0;
		 return XMP_SUCCESS;
		 
	 case DEMUX_GET_TIME:
		 pi64 = (int64_t*)va_arg( args, int64_t * );
		 if(FAILED(p_sys->fgb->GetCurrentPosition(pi64)))
			 *pi64 = 0;
		 return XMP_SUCCESS;
		 
		 /* TODO implement others */
	 default:
		 return XMP_EGENERIC;
	 }
	 
	 return XMP_EGENERIC;
}

  static block_t *ReadCompressed( access_t *p_access )
  {
	  access_sys_t   *p_sys = p_access->p_sys;
	  CDShowStream *p_stream = NULL;
	  XMPMediaSample sample;
	  
	  /* Read 1 DV/MPEG frame (they contain the video and audio data) */
	  
	  /* There must be only 1 elementary stream to produce a valid stream
	  * of MPEG or DV data */
	  p_stream = p_sys->fgb->get_stream(0);
	  
	  while( 1 )
	  {
		  if( p_access->b_die || p_access->b_error ) return 0;
		  
		  /* Get new sample/frame from the elementary stream (blocking). */
		  xmp_mutex_lock( &p_sys->lock );
		  
		  if( p_stream->p_capture_filter->CustomGetPin()
              ->CustomGetSample( &sample ) != S_OK )
		  {
			  /* No data available. Wait until some data has arrived */
			  xmp_mutex_unlock( &p_sys->lock );
			  msleep(10);
			  continue;
		  }
		  
		  xmp_mutex_unlock( &p_sys->lock );
		  
		  /*
		  * We got our sample
		  */
		  block_t *p_block;
		  uint8_t *p_data;
		  int i_data_size = sample.p_sample->GetActualDataLength();
		  
		  if( !i_data_size || !(p_block = block_New( p_access, i_data_size )) )
		  {
			  sample.p_sample->Release();
			  continue;
		  }
		  
		  sample.p_sample->GetPointer( &p_data );
		  p_access->p_xmp->pf_memcpy( p_block->p_buffer, p_data, i_data_size );
		  sample.p_sample->Release();
		  
		  /* The caller got what he wanted */
		  return p_block;
	  }
	  
	  return 0; /* never reached */
  }
  static int AccessControl( access_t *p_access, int i_query, va_list args )
  {
	  xmp_bool_t   *pb_bool;
	  int          *pi_int;
	  int64_t      *pi_64;
	  
	  switch( i_query )
	  {
		  /* */
	  case ACCESS_CAN_SEEK:
	  case ACCESS_CAN_FASTSEEK:
	  case ACCESS_CAN_PAUSE:
	  case ACCESS_CAN_CONTROL_PACE:
		  pb_bool = (xmp_bool_t*)va_arg( args, xmp_bool_t* );
		  *pb_bool = XMP_FALSE;
		  break;
		  
		  /* */
	  case ACCESS_GET_MTU:
		  pi_int = (int*)va_arg( args, int * );
		  *pi_int = 0;
		  break;
		  
	  case ACCESS_GET_PTS_DELAY:
		  pi_64 = (int64_t*)va_arg( args, int64_t * );
		  *pi_64 = (int64_t)var_GetInteger( p_access, "dshow-caching" ) * 1000;
		  break;
		  
		  /* */
	  case ACCESS_SET_PAUSE_STATE:
	  case ACCESS_GET_TITLE_INFO:
	  case ACCESS_SET_TITLE:
	  case ACCESS_SET_SEEKPOINT:
	  case ACCESS_SET_PRIVATE_ID_STATE:
		  return XMP_EGENERIC;
		  
	  default:
		  msg_Warn( p_access, "unimplemented query in control" );
		  return XMP_EGENERIC;
	  }
	  
	  return XMP_SUCCESS;
  } 
static IBaseFilter *
FindCaptureDevice( xmp_object_t *p_this, string *p_devicename,
                   list<string> *p_listdevices, xmp_bool_t b_audio , list<string> * p_displayname)
{
    IBaseFilter *p_base_filter = NULL;
    IMoniker *p_moniker = NULL;
    ULONG i_fetched;
    HRESULT hr;

    /* Create the system device enumerator */
    ICreateDevEnum *p_dev_enum = NULL;

    hr = CoCreateInstance( CLSID_SystemDeviceEnum, NULL, CLSCTX_INPROC,
                           IID_ICreateDevEnum, (void **)&p_dev_enum );
    if( FAILED(hr) )
    {
        msg_Err( p_this, "failed to create the device enumerator (0x%lx)", hr);
        return NULL;
    }

    /* Create an enumerator for the video capture devices */
    IEnumMoniker *p_class_enum = NULL;
    if( !b_audio )
        hr = p_dev_enum->CreateClassEnumerator( CLSID_VideoInputDeviceCategory,
                                                &p_class_enum, 0 );
    else
        hr = p_dev_enum->CreateClassEnumerator( CLSID_AudioInputDeviceCategory,
                                                &p_class_enum, 0 );
    p_dev_enum->Release();
    if( FAILED(hr) )
    {
        msg_Err( p_this, "failed to create the class enumerator (0x%lx)", hr );
        return NULL;
    }

    /* If there are no enumerators for the requested type, then
     * CreateClassEnumerator will succeed, but p_class_enum will be NULL */
    if( p_class_enum == NULL )
    {
        msg_Err( p_this, "no capture device was detected" );
        return NULL;
    }

    /* Enumerate the devices */

    /* Note that if the Next() call succeeds but there are no monikers,
     * it will return S_FALSE (which is not a failure). Therefore, we check
     * that the return code is S_OK instead of using SUCCEEDED() macro. */

    while( p_class_enum->Next( 1, &p_moniker, &i_fetched ) == S_OK )
    {
        /* Getting the property page to get the device name */
        IPropertyBag *p_bag;
        hr = p_moniker->BindToStorage( 0, 0, IID_IPropertyBag,
                                       (void **)&p_bag );
        if( SUCCEEDED(hr) )
        {
            VARIANT var;
            var.vt = VT_BSTR;
            hr = p_bag->Read( L"FriendlyName", &var, NULL );
            p_bag->Release();
            if( SUCCEEDED(hr) )
            {
                int i_convert = WideCharToMultiByte(CP_ACP, 0, var.bstrVal,
                        SysStringLen(var.bstrVal), NULL, 0, NULL, NULL);
                char *p_buf = (char *)alloca( i_convert+1 ); p_buf[0] = 0;
                WideCharToMultiByte( CP_ACP, 0, var.bstrVal,
                        SysStringLen(var.bstrVal), p_buf, i_convert, NULL, NULL );
                SysFreeString(var.bstrVal);
                p_buf[i_convert] = '\0';
                if( p_listdevices ) p_listdevices->push_back( p_buf );

				LPOLESTR strMonikerName=0;
				if(p_displayname && SUCCEEDED(p_moniker->GetDisplayName(NULL, NULL, &strMonikerName)))
				{
					USES_CONVERSION;
					TCHAR szMonikerName[256] = _T("");
					_tcsncpy(szMonikerName, W2T(strMonikerName), 255);
					if( p_displayname ) p_displayname->push_back( szMonikerName );
				}
				

                if( p_devicename && *p_devicename == string(p_buf) )
                {
                    /* Bind Moniker to a filter object */
                    hr = p_moniker->BindToObject( 0, 0, IID_IBaseFilter,
                                                  (void **)&p_base_filter );
                    if( FAILED(hr) )
                    {
                        msg_Err( p_this, "couldn't bind moniker to filter "
                                 "object (0x%lx)", hr );
                        p_moniker->Release();
                        p_class_enum->Release();
                        return NULL;
                    }
                    p_moniker->Release();
                    p_class_enum->Release();
                    return p_base_filter;
                }
            }
        }

        p_moniker->Release();
    }

    p_class_enum->Release();
    return NULL;
}
static IBaseFilter *
FindEncoderDevice( xmp_object_t *p_this, string *p_devicename,
                   list<string> *p_listdevices, xmp_bool_t b_audio , list<string> * p_displayname)
{
    IBaseFilter *p_base_filter = NULL;
    IMoniker *p_moniker = NULL;
    ULONG i_fetched;
    HRESULT hr;

    /* Create the system device enumerator */
    ICreateDevEnum *p_dev_enum = NULL;

    hr = CoCreateInstance( CLSID_SystemDeviceEnum, NULL, CLSCTX_INPROC,
                           IID_ICreateDevEnum, (void **)&p_dev_enum );
    if( FAILED(hr) )
    {
        msg_Err( p_this, "failed to create the device enumerator (0x%lx)", hr);
        return NULL;
    }

    /* Create an enumerator for the video capture devices */
    IEnumMoniker *p_class_enum = NULL;
     hr = p_dev_enum->CreateClassEnumerator( KSCATEGORY_ENCODER,
                                                &p_class_enum, 0 );
   
    p_dev_enum->Release();
    if( FAILED(hr) )
    {
        msg_Err( p_this, "failed to create the class enumerator (0x%lx)", hr );
        return NULL;
    }

    /* If there are no enumerators for the requested type, then
     * CreateClassEnumerator will succeed, but p_class_enum will be NULL */
    if( p_class_enum == NULL )
    {
        msg_Err( p_this, "no capture device was detected" );
        return NULL;
    }

    /* Enumerate the devices */

    /* Note that if the Next() call succeeds but there are no monikers,
     * it will return S_FALSE (which is not a failure). Therefore, we check
     * that the return code is S_OK instead of using SUCCEEDED() macro. */

    while( p_class_enum->Next( 1, &p_moniker, &i_fetched ) == S_OK )
    {
        /* Getting the property page to get the device name */
        IPropertyBag *p_bag;
        hr = p_moniker->BindToStorage( 0, 0, IID_IPropertyBag,
                                       (void **)&p_bag );
        if( SUCCEEDED(hr) )
        {
            VARIANT var;
            var.vt = VT_BSTR;
            hr = p_bag->Read( L"FriendlyName", &var, NULL );
            p_bag->Release();
            if( SUCCEEDED(hr) )
            {
                int i_convert = WideCharToMultiByte(CP_ACP, 0, var.bstrVal,
                        SysStringLen(var.bstrVal), NULL, 0, NULL, NULL);
                char *p_buf = (char *)alloca( i_convert+1 ); p_buf[0] = 0;
                WideCharToMultiByte( CP_ACP, 0, var.bstrVal,
                        SysStringLen(var.bstrVal), p_buf, i_convert, NULL, NULL );
                SysFreeString(var.bstrVal);
                p_buf[i_convert] = '\0';
                if( p_listdevices ) p_listdevices->push_back( p_buf );

				LPOLESTR strMonikerName=0;
				if(p_displayname && SUCCEEDED(p_moniker->GetDisplayName(NULL, NULL, &strMonikerName)))
				{
					USES_CONVERSION;
					TCHAR szMonikerName[256] = _T("");
					_tcsncpy(szMonikerName, W2T(strMonikerName), 255);
					if( p_displayname ) p_displayname->push_back( szMonikerName );
				}
				

                if( p_devicename && *p_devicename == string(p_buf) )
                {
                    /* Bind Moniker to a filter object */
                    hr = p_moniker->BindToObject( 0, 0, IID_IBaseFilter,
                                                  (void **)&p_base_filter );
                    if( FAILED(hr) )
                    {
                        msg_Err( p_this, "couldn't bind moniker to filter "
                                 "object (0x%lx)", hr );
                        p_moniker->Release();
                        p_class_enum->Release();
                        return NULL;
                    }
                    p_moniker->Release();
                    p_class_enum->Release();
                    return p_base_filter;
                }
            }
        }

        p_moniker->Release();
    }

    p_class_enum->Release();
    return NULL;
}
static int FindDevicesCallback( xmp_object_t *p_this, char const *psz_name,
                               xmp_value_t newval, xmp_value_t oldval, void * )
{
    module_config_t *p_item;
    xmp_bool_t b_audio = XMP_FALSE;
    int i;
	
    p_item = config_FindConfig( p_this, psz_name );
    if( !p_item ) return XMP_SUCCESS;
	
    if( !strcmp( psz_name, "dshow-adev" ) ) b_audio = XMP_TRUE;
	
    /* Clear-up the current list */
    if( p_item->i_list )
    {
        /* Keep the 2 first entries */
        for( i = 2; i < p_item->i_list; i++ )
        {
            free( p_item->ppsz_list[i] );
            free( p_item->ppsz_list_text[i] );
        }
        /* TODO: Remove when no more needed */
        p_item->ppsz_list[i] = NULL;
        p_item->ppsz_list_text[i] = NULL;
    }
    p_item->i_list = 2;
	
    /* Find list of devices */
    list<string> list_devices;
    list<string> list_displayname;
	
    /* Initialize OLE/COM */
    CoInitialize( 0 );
	
    FindCaptureDevice( p_this, NULL, &list_devices, b_audio, &list_displayname );
	if(!b_audio)
		FindEncoderDevice( p_this, NULL, &list_devices, b_audio, &list_displayname );
	
    /* Uninitialize OLE/COM */
    CoUninitialize();
	
    if( !list_devices.size() ) return XMP_SUCCESS;
	
    p_item->ppsz_list =
        (char **)realloc( p_item->ppsz_list,
		(list_devices.size()+3) * sizeof(char *) );
    p_item->ppsz_list_text =
        (char **)realloc( p_item->ppsz_list_text,
		(list_devices.size()+3) * sizeof(char *) );
	
    list<string>::iterator iter, iter1;
    for( iter = list_devices.begin(), iter1 = list_displayname.begin(), i = 2; 
	iter != list_devices.end() &&
		iter1 != list_displayname.end();
	iter++, iter1++, i++ )
    {
        p_item->ppsz_list[i] = strdup( iter->c_str() );
        p_item->ppsz_list_text[i] = strdup( iter1->c_str() );
        p_item->i_list++;
    }
    p_item->ppsz_list[i] = NULL;
    p_item->ppsz_list_text[i] = NULL;
	
    /* Signal change to the interface */
    p_item->b_dirty = XMP_TRUE;
	
    return XMP_SUCCESS;
}


static int ConfigDevicesCallback( xmp_object_t *p_this, char const *psz_name,
                               xmp_value_t newval, xmp_value_t oldval, void * )
{
    module_config_t *p_item;
    xmp_bool_t b_audio = XMP_FALSE;

    /* Initialize OLE/COM */
    CoInitialize( 0 );

    p_item = config_FindConfig( p_this, psz_name );
    if( !p_item ) return XMP_SUCCESS;

    if( !strcmp( psz_name, "dshow-adev" ) ) b_audio = XMP_TRUE;

    string devicename;

    if( newval.psz_string && *newval.psz_string )
    {
        devicename = newval.psz_string;
    }
    else
    {
        /* If no device name was specified, pick the 1st one */
        list<string> list_devices;

        /* Enumerate devices */
        FindCaptureDevice( p_this, NULL, &list_devices, b_audio );
        if( !list_devices.size() ) return XMP_EGENERIC;
        devicename = *list_devices.begin();
    }

    IBaseFilter *p_device_filter =
        FindCaptureDevice( p_this, &devicename, NULL, b_audio );
    if( p_device_filter )
    {
        ShowPropertyPage( p_device_filter );
    }
    else
    {
        /* Uninitialize OLE/COM */
        CoUninitialize();

        msg_Err( p_this, "didn't find device: %s", devicename.c_str() );
        return XMP_EGENERIC;
    }

    /* Uninitialize OLE/COM */
    CoUninitialize();

    return XMP_SUCCESS;
}
static int ConfigDevicesCallback2( xmp_object_t *p_this, char const *psz_name,
								 xmp_value_t newval, xmp_value_t oldval, void * )
{
    module_config_t *p_item;
    xmp_bool_t b_audio = XMP_FALSE;
	
    /* Initialize OLE/COM */
    CoInitialize( 0 );
	
    p_item = config_FindConfig( p_this, psz_name );
    if( !p_item ) return XMP_SUCCESS;
	
    if( !strcmp( psz_name, "dshow-adev" ) ) b_audio = XMP_TRUE;
	
    string devicename;
    string displayname;
	
    if( newval.p_list && newval.p_list->i_count == 2)
    {
		xmp_list_t  list_val;
		list_val = *newval.p_list;
		
        devicename = (list_val.p_values[0]).psz_string;
		displayname = (list_val.p_values[1]).psz_string;
	}
    else
    {
        /* If no device name was specified, pick the 1st one */
        list<string> list_devices;
		list<string> list_displays;
		
        /* Enumerate devices */
        FindCaptureDevice2( p_this, NULL, NULL, 
			&list_devices,&list_displays,
			b_audio );
        if( !list_devices.size() ) return XMP_EGENERIC;
        devicename = *list_devices.begin();
		displayname= *list_displays.begin();
    }
	
    IBaseFilter *p_device_filter =
        FindCaptureDevice2( p_this, 
		&devicename, &displayname, 
		NULL, NULL, b_audio );
	if(b_audio && p_device_filter == NULL)
	{
		
	}
    if( p_device_filter )
    {
        ShowPropertyPage( p_device_filter );
    }
    else
    {
        /* Uninitialize OLE/COM */
        CoUninitialize();
		
        msg_Err( p_this, "didn't find device: %s", devicename.c_str() );
        return XMP_EGENERIC;
    }
	
    /* Uninitialize OLE/COM */
    CoUninitialize();
	
    return XMP_SUCCESS;
}
/*****************************************************************************
 * Properties
 *****************************************************************************/
static void ShowPropertyPage( IUnknown *obj )
{
    ISpecifyPropertyPages *p_spec;
    CAUUID cauuid;

    HRESULT hr = obj->QueryInterface( IID_ISpecifyPropertyPages,
                                      (void **)&p_spec );
    if( FAILED(hr) ) return;

    if( SUCCEEDED(p_spec->GetPages( &cauuid )) )
    {
        if( cauuid.cElems > 0 )
        {
            HWND hwnd_desktop = ::GetDesktopWindow();

            OleCreatePropertyFrame( hwnd_desktop, 30, 30, NULL, 1, &obj,
                                    cauuid.cElems, cauuid.pElems, 0, 0, NULL );

            CoTaskMemFree( cauuid.pElems );
        }
        p_spec->Release();
    }
}

static void ShowDeviceProperties( xmp_object_t *p_this,
                                  ICaptureGraphBuilder2 *p_graph,
                                  IBaseFilter *p_device_filter,
                                  xmp_bool_t b_audio )
{
    HRESULT hr;
    msg_Dbg( p_this, "Configuring Device Properties" );

    /*
     * Video or audio capture filter page
     */
    ShowPropertyPage( p_device_filter );

    /*
     * Audio capture pin
     */
    if( p_graph && b_audio )
    {
        IAMStreamConfig *p_SC;

        msg_Dbg( p_this, "Showing WDM Audio Configuration Pages" );

        hr = p_graph->FindInterface( &PIN_CATEGORY_CAPTURE,
                                     &MEDIATYPE_Audio, p_device_filter,
                                     IID_IAMStreamConfig, (void **)&p_SC );
        if( SUCCEEDED(hr) )
        {
            ShowPropertyPage(p_SC);
            p_SC->Release();
        }

        /*
         * TV Audio filter
         */
        IAMTVAudio *p_TVA;
        HRESULT hr = p_graph->FindInterface( &PIN_CATEGORY_CAPTURE,
                                             &MEDIATYPE_Audio, p_device_filter,
                                             IID_IAMTVAudio, (void **)&p_TVA );
        if( SUCCEEDED(hr) )
        {
            ShowPropertyPage(p_TVA);
            p_TVA->Release();
        }
    }

    /*
     * Video capture pin
     */
    if( p_graph && !b_audio )
    {
        IAMStreamConfig *p_SC;

        msg_Dbg( p_this, "Showing WDM Video Configuration Pages" );

        hr = p_graph->FindInterface( &PIN_CATEGORY_CAPTURE,
                                     &MEDIATYPE_Interleaved, p_device_filter,
                                     IID_IAMStreamConfig, (void **)&p_SC );
        if( FAILED(hr) )
        {
            hr = p_graph->FindInterface( &PIN_CATEGORY_CAPTURE,
                                         &MEDIATYPE_Video, p_device_filter,
                                         IID_IAMStreamConfig, (void **)&p_SC );
        }

        if( FAILED(hr) )
        {
            hr = p_graph->FindInterface( &PIN_CATEGORY_CAPTURE,
                                         &MEDIATYPE_Stream, p_device_filter,
                                         IID_IAMStreamConfig, (void **)&p_SC );
        }

        if( SUCCEEDED(hr) )
        {
            ShowPropertyPage(p_SC);
            p_SC->Release();
        }
    }
}

static void ShowTunerProperties( xmp_object_t *p_this,
                                 ICaptureGraphBuilder2 *p_graph,
                                 IBaseFilter *p_device_filter,
                                 xmp_bool_t b_audio )
{
    HRESULT hr;
    msg_Dbg( p_this, "Configuring Tuner Properties" );

    if( !p_graph || b_audio ) return;

    IAMTVTuner *p_TV;
    hr = p_graph->FindInterface( &PIN_CATEGORY_CAPTURE,
                                 &MEDIATYPE_Interleaved, p_device_filter,
                                 IID_IAMTVTuner, (void **)&p_TV );
    if( FAILED(hr) )
    {
        hr = p_graph->FindInterface( &PIN_CATEGORY_CAPTURE,
                                     &MEDIATYPE_Video, p_device_filter,
                                     IID_IAMTVTuner, (void **)&p_TV );
    }

    if( FAILED(hr) )
    {
        hr = p_graph->FindInterface( &PIN_CATEGORY_CAPTURE,
                                     &MEDIATYPE_Stream, p_device_filter,
                                     IID_IAMTVTuner, (void **)&p_TV );
    }

    if( SUCCEEDED(hr) )
    {
        ShowPropertyPage(p_TV);
        p_TV->Release();
    }
}

static void ConfigTuner( xmp_object_t *p_this, ICaptureGraphBuilder2 *p_graph,
                         IBaseFilter *p_device_filter )
{
    int i_channel, i_country, i_input;
    long l_modes = 0;
    IAMTVTuner *p_TV;
    HRESULT hr;

    if( !p_graph ) return;

    i_channel = var_GetInteger( p_this, "dshow-tuner-channel" );
    i_country = var_GetInteger( p_this, "dshow-tuner-country" );
    i_input = var_GetInteger( p_this, "dshow-tuner-input" );

    if( !i_channel && !i_country && !i_input ) return; /* Nothing to do */

    msg_Dbg( p_this, "tuner config: channel %i, country %i, input type %i",
             i_channel, i_country, i_input );

    hr = p_graph->FindInterface( &PIN_CATEGORY_CAPTURE, &MEDIATYPE_Interleaved,
                                 p_device_filter, IID_IAMTVTuner,
                                 (void **)&p_TV );
    if( FAILED(hr) )
    {
        hr = p_graph->FindInterface( &PIN_CATEGORY_CAPTURE, &MEDIATYPE_Video,
                                     p_device_filter, IID_IAMTVTuner,
                                     (void **)&p_TV );
    }

    if( FAILED(hr) )
    {
        hr = p_graph->FindInterface( &PIN_CATEGORY_CAPTURE, &MEDIATYPE_Stream,
                                     p_device_filter, IID_IAMTVTuner,
                                     (void **)&p_TV );
    }

    if( FAILED(hr) )
    {
        msg_Dbg( p_this, "couldn't find tuner interface" );
        return;
    }

    hr = p_TV->GetAvailableModes( &l_modes );
    if( SUCCEEDED(hr) && (l_modes & AMTUNER_MODE_TV) )
    {
        hr = p_TV->put_Mode( AMTUNER_MODE_TV );
    }

    if( i_input == 1 ) p_TV->put_InputType( 0, TunerInputCable );
    else if( i_input == 2 ) p_TV->put_InputType( 0, TunerInputAntenna );

    p_TV->put_CountryCode( i_country );
    p_TV->put_Channel( i_channel, AMTUNER_SUBCHAN_NO_TUNE,
                       AMTUNER_SUBCHAN_NO_TUNE );
    p_TV->Release();
}
static IBaseFilter *
FindCaptureDevice2( xmp_object_t *p_this, 
				   string *p_devicename, 
				   string *p_displayname,
                   list<string> *p_listdevices, 
				   list<string> *p_listdiplays, 
				   xmp_bool_t b_audio)
{
    IBaseFilter *p_base_filter = NULL;
    IMoniker *p_moniker = NULL;
    ULONG i_fetched;
    HRESULT hr;

    /* Create the system device enumerator */
    ICreateDevEnum *p_dev_enum = NULL;

    hr = CoCreateInstance( CLSID_SystemDeviceEnum, NULL, CLSCTX_INPROC,
                           IID_ICreateDevEnum, (void **)&p_dev_enum );
    if( FAILED(hr) )
    {
        msg_Err( p_this, "failed to create the device enumerator (0x%lx)", hr);
        return NULL;
    }

    /* Create an enumerator for the video capture devices */
    IEnumMoniker *p_class_enum = NULL;
    if( !b_audio )
        hr = p_dev_enum->CreateClassEnumerator( CLSID_VideoInputDeviceCategory,
                                                &p_class_enum, 0 );
    else
        hr = p_dev_enum->CreateClassEnumerator( CLSID_AudioInputDeviceCategory,
                                                &p_class_enum, 0 );
    p_dev_enum->Release();
    if( FAILED(hr) )
    {
        msg_Err( p_this, "failed to create the class enumerator (0x%lx)", hr );
        return NULL;
    }

    /* If there are no enumerators for the requested type, then
     * CreateClassEnumerator will succeed, but p_class_enum will be NULL */
    if( p_class_enum == NULL )
    {
        msg_Err( p_this, "no capture device was detected" );
        return NULL;
    }

    /* Enumerate the devices */

    /* Note that if the Next() call succeeds but there are no monikers,
     * it will return S_FALSE (which is not a failure). Therefore, we check
     * that the return code is S_OK instead of using SUCCEEDED() macro. */

    while( p_class_enum->Next( 1, &p_moniker, &i_fetched ) == S_OK )
    {
        /* Getting the property page to get the device name */
        IPropertyBag *p_bag;
        hr = p_moniker->BindToStorage( 0, 0, IID_IPropertyBag,
                                       (void **)&p_bag );
        if( SUCCEEDED(hr) )
        {
            VARIANT var;
            var.vt = VT_BSTR;
            hr = p_bag->Read( L"FriendlyName", &var, NULL );
            p_bag->Release();
            if( SUCCEEDED(hr) )
            {
                int i_convert = WideCharToMultiByte(CP_ACP, 0, var.bstrVal,
                        SysStringLen(var.bstrVal), NULL, 0, NULL, NULL);
                char *p_buf = (char *)alloca( i_convert+1 ); p_buf[0] = 0;
                WideCharToMultiByte( CP_ACP, 0, var.bstrVal,
                        SysStringLen(var.bstrVal), p_buf, i_convert, NULL, NULL );
                SysFreeString(var.bstrVal);
                p_buf[i_convert] = '\0';
                if( p_listdevices ) p_listdevices->push_back( p_buf );

				LPOLESTR strMonikerName=0;
				TCHAR szMonikerName[256] = _T("");
				if(SUCCEEDED(p_moniker->GetDisplayName(NULL, NULL, &strMonikerName)))
				{
					USES_CONVERSION;
					_tcsncpy(szMonikerName, W2T(strMonikerName), 255);
					if(p_listdiplays)
						p_listdiplays->push_back(szMonikerName);
				}
				
                if( p_devicename && *p_devicename == string(p_buf) )
                {
					if(p_displayname && p_displayname->size())
                    {
						if(*p_displayname == string(szMonikerName))
						{
							/* Bind Moniker to a filter object */
							hr = p_moniker->BindToObject( 0, 0, IID_IBaseFilter,
														  (void **)&p_base_filter );
							if( FAILED(hr) )
							{
								msg_Err( p_this, "couldn't bind moniker to filter "
										 "object (0x%lx)", hr );
								p_moniker->Release();
								p_class_enum->Release();
								return NULL;
							}
							p_moniker->Release();
							p_class_enum->Release();
							return p_base_filter;
						}
					}
					else
					{
						/* Bind Moniker to a filter object */
						hr = p_moniker->BindToObject( 0, 0, IID_IBaseFilter,
							(void **)&p_base_filter );
						if( FAILED(hr) )
						{
							msg_Err( p_this, "couldn't bind moniker to filter "
								"object (0x%lx)", hr );
							p_moniker->Release();
							p_class_enum->Release();
							return NULL;
						}
						p_moniker->Release();
						p_class_enum->Release();
						return p_base_filter;
					}
                }
            }
        }

        p_moniker->Release();
    }

    p_class_enum->Release();
    return NULL;
}
bool IsRawVideo(int i_fourcc)
{
	switch(i_fourcc) 
	{
	case MAKEFOURCC( 'R', 'G', 'B', '1' ):
		
	case MAKEFOURCC( 'R', 'G', 'B', '4' ):
	case MAKEFOURCC( 'R', 'G', 'B', '8' ):
	case MAKEFOURCC( 'R', 'V', '1', '5' ):
	case MAKEFOURCC( 'R', 'V', '1', '6' ):
	case MAKEFOURCC( 'R', 'V', '2', '4' ):
	case MAKEFOURCC( 'R', 'V', '3', '2' ):
	case MAKEFOURCC( 'R', 'G', 'B', 'A' ):
		
		/* Planar YUV formats */
	case MAKEFOURCC( 'I', '4', '2', '0' ):
	case MAKEFOURCC( 'I', '4', '1', '1' ):
	case MAKEFOURCC( 'Y', 'V', '1', '2' ):
	case MAKEFOURCC( 'Y', 'V', 'U', '9' ):
		
		/* Packed YUV formats */
	case MAKEFOURCC( 'Y', 'V', 'Y', 'U' ):
	case MAKEFOURCC( 'I', '4', '1', 'N' ):
	case MAKEFOURCC( 'Y', '2', '1', '1' ):
	case MAKEFOURCC( 'Y', 'U', 'Y', '2' ):
	case MAKEFOURCC( 'U', 'Y', 'V', 'Y' ):
		return true;
	default:
		break;
	}
	
	return false;
}
unsigned long FormatMPEG4StreamSEQHeader(int w, int h,
										 char** ppSeqHeader)
{
	
#define MAX_MPEG4_SEQ_HEADER_LEN 200
	static char mpeg4_seqheader[MAX_MPEG4_SEQ_HEADER_LEN];
	
	unsigned long mpeg4_seqheader_length = 18;
	
	mpeg4_seqheader[0] = (char)0x0;
	mpeg4_seqheader[1] = (char)0x0;
	mpeg4_seqheader[2] = (char)0x1;
	mpeg4_seqheader[3] = (char)0x0;
	
	mpeg4_seqheader[4] = (char)0x0;
	mpeg4_seqheader[5] = (char)0x0;
	mpeg4_seqheader[6] = (char)0x1;
	mpeg4_seqheader[7] = (char)0x20;
	
	mpeg4_seqheader[8] = (char)0x0;
	mpeg4_seqheader[9] = (char)0x84;
	mpeg4_seqheader[10] = (char)0x5D;
	mpeg4_seqheader[11] = (char)0x4C;
	
	mpeg4_seqheader[12] = (char)(0x28 + ( ( w >> 10 ) & 0x7 ));
	mpeg4_seqheader[13] = (char)(w >> 2);
	mpeg4_seqheader[14] = (char)(0x20 + ( ( h >> 8 ) & 0x1F ));
	mpeg4_seqheader[15] = (char)(h & 0xFF);
	
	mpeg4_seqheader[16] = (char)0xA3;
	mpeg4_seqheader[17] = (char)0x1F;
	
	*ppSeqHeader = mpeg4_seqheader;
	return mpeg4_seqheader_length;
}
bool IsMP4XV3DeviceSource (input_thread_t *p_input)
{
	for(int i = 0; i < p_input->input.p_item->i_options; i ++)
	{
		if(strnicmp(p_input->input.p_item->ppsz_options[i],
			"Gotron MP-4X V3", strlen("Gotron MP-4X V3")) == 0)
			return true;
	}
	return false;
}