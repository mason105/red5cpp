#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define _VIDEOINFO_
#define _VIDEOINFOHEADER_
#define _TRUECOLORINFO_
#include "xmpstd.h"
#define PTCHAR TCHAR* 
#include "GrapObjRef.h"

static int  Open ( xmp_object_t * );
static void Close( xmp_object_t * );
static int Demux( demux_t *p_demux );
static int DemuxControl( demux_t *p_demux, int i_query, va_list args );

xmp_module_begin();
	set_shortname( _("DirectShow File") );
	set_description( _("DirectShow File") );
	set_category( CAT_INPUT );
	set_subcategory( SUBCAT_INPUT_ACCESS );
	add_shortcut( "dsfile" );
	set_capability( "access_demux", 0 );
	set_callbacks( Open, Close );
xmp_module_end();

struct access_sys_t
{
    /* These 2 must be left at the beginning */
    xmp_mutex_t lock;
    xmp_cond_t  wait;
	CGrapObjRef* fgb;
	
	
};	
 int  Open ( xmp_object_t * p_this)
{
	demux_t      *p_demux = (demux_t *)p_this;
	access_sys_t *p_sys;
	int i;
	
	p_sys = (access_sys_t *)malloc( sizeof( access_sys_t ) );
	memset( p_sys, 0, sizeof( access_sys_t ) );
	p_demux->p_sys = (demux_sys_t *)p_sys;		
	p_sys->fgb = new CGrapObjRef;

    char *psz_name = strdup( p_demux->psz_path );
	if( !strcasecmp( p_demux->psz_access, "dsfile" )
                && ('/' == psz_name[0]) && psz_name[1]
                && (':' == psz_name[2]) && ('/' == psz_name[3]) )
    {
        ++psz_name;
    }
    CoInitialize( 0 );

    xmp_mutex_init( p_this, &p_sys->lock );
    xmp_cond_init( p_this, &p_sys->wait );
	
	if(FAILED(p_sys->fgb->Initialize(psz_name)))
	{
		free(psz_name);
		return XMP_EGENERIC;
	}

	if(FAILED(p_sys->fgb->Run()))
	{
		free(psz_name);
		return XMP_EGENERIC;
	}
	free(psz_name);

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
	return XMP_SUCCESS;
}
 void Close( xmp_object_t * p_this)
{
	 demux_t      *p_demux = (demux_t *)p_this;
	 access_sys_t *p_sys    = (access_sys_t*)p_demux->p_sys;

	 p_sys->fgb->Stop();
	 p_sys->fgb->Cleanup();	 
	 CoUninitialize();
	 delete p_sys->fgb;
	 xmp_mutex_destroy( &p_sys->lock );
	 xmp_cond_destroy( &p_sys->wait );
	 free(p_sys);
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
    msg_Dbg( p_demux, "Read() stream: %i, size: %i, PTS: "I64Fd,
		i_stream, i_data_size, i_pts );
#endif
	
    p_block = block_New( p_demux, i_data_size );
    p_demux->p_xmp->pf_memcpy( p_block->p_buffer, p_data, i_data_size );
    p_block->i_pts = p_block->i_dts = i_pts;
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