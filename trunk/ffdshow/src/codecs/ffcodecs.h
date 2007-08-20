#ifndef _FFCODECS_H_
#define _FFCODECS_H_

#define FFDSHOW_CODECS \
 CODEC_OP(CODEC_ID_UNSUPPORTED    ,-1,"unsupported") \
 CODEC_OP(CODEC_ID_NONE           , 0,"none") \
 \
 CODEC_OP(CODEC_ID_MPEG1VIDEO        , 1,"mpeg1video") \
 CODEC_OP(CODEC_ID_MPEG2VIDEO        ,49,"mpeg2video") \
 CODEC_OP(CODEC_ID_H263              , 2,"h263") \
 CODEC_OP(CODEC_ID_MJPEG             , 8,"mjpeg") \
 CODEC_OP(CODEC_ID_MPEG4             ,10,"mpeg4") \
 CODEC_OP(CODEC_ID_MSMPEG4V1         ,12,"msmpeg4v1") \
 CODEC_OP(CODEC_ID_MSMPEG4V2         ,13,"msmpeg4v2") \
 CODEC_OP(CODEC_ID_MSMPEG4V3         ,14,"msmpeg4v3") \
 CODEC_OP(CODEC_ID_WMV1              ,15,"wmv1") \
 CODEC_OP(CODEC_ID_WMV2              ,16,"wmv2") \
 CODEC_OP(CODEC_ID_WMV3              ,84,"wmv3") \
 CODEC_OP(CODEC_ID_H263P             ,17,"h263+") \
 CODEC_OP(CODEC_ID_HUFFYUV           ,26,"huffyuv") \
 CODEC_OP(CODEC_ID_FFVHUFF           ,83,"ffvhuff") \
 CODEC_OP(CODEC_ID_FFV1              ,43,"ffv1") \
 CODEC_OP(CODEC_ID_VP3               ,48,"vp3") \
 CODEC_OP(CODEC_ID_LJPEG             ,40,"ljpeg") \
 CODEC_OP(CODEC_ID_JPEGLS            ,98,"") \
 CODEC_OP(CODEC_ID_RV10              , 3,"rv10") \
 CODEC_OP(CODEC_ID_RV20              ,55,"rv20") \
 CODEC_OP(CODEC_ID_MP2               , 4,"") \
 CODEC_OP(CODEC_ID_MP3               , 5,"") \
 CODEC_OP(CODEC_ID_VORBIS            , 6,"vorbis") \
 CODEC_OP(CODEC_ID_AC3               , 7,"") \
 CODEC_OP(CODEC_ID_MJPEGB            , 9,"mjpegb") \
 CODEC_OP(CODEC_ID_CSCD              ,11,"camstudio") \
 CODEC_OP(CODEC_ID_H263I             ,18,"h263i") \
 CODEC_OP(CODEC_ID_SVQ1              ,19,"svq1") \
 CODEC_OP(CODEC_ID_DVVIDEO           ,20,"dvvideo") \
 CODEC_OP(CODEC_ID_DVAUDIO           ,21,"") \
 CODEC_OP(CODEC_ID_WMAV1             ,22,"wmav1") \
 CODEC_OP(CODEC_ID_WMAV2             ,23,"wmav2") \
 CODEC_OP(CODEC_ID_PCM_S16LE         ,27,"") \
 CODEC_OP(CODEC_ID_PCM_S16BE         ,28,"") \
 CODEC_OP(CODEC_ID_PCM_U16LE         ,29,"") \
 CODEC_OP(CODEC_ID_PCM_U16BE         ,30,"") \
 CODEC_OP(CODEC_ID_PCM_S8            ,31,"") \
 CODEC_OP(CODEC_ID_PCM_U8            ,32,"") \
 CODEC_OP(CODEC_ID_PCM_MULAW         ,33,"mulaw") \
 CODEC_OP(CODEC_ID_PCM_ALAW          ,34,"alaw") \
 CODEC_OP(CODEC_ID_ADPCM_IMA_QT      ,35,"adpcm ima qt") \
 CODEC_OP(CODEC_ID_ADPCM_IMA_WAV     ,36,"adpcm ima wav") \
 CODEC_OP(CODEC_ID_ADPCM_MS          ,37,"adpcm ms") \
 CODEC_OP(CODEC_ID_ADPCM_IMA_DK3     ,68,"adpcm ima dk3") \
 CODEC_OP(CODEC_ID_ADPCM_IMA_DK4     ,69,"adpcm ima dk4") \
 CODEC_OP(CODEC_ID_ADPCM_IMA_WS      ,70,"adpcm ima ws") \
 CODEC_OP(CODEC_ID_ADPCM_IMA_SMJPEG  ,71,"adpcm ima smjpeg") \
 CODEC_OP(CODEC_ID_ADPCM_4XM         ,72,"adpcm 4xm") \
 CODEC_OP(CODEC_ID_ADPCM_XA          ,73,"adpcm xa") \
 CODEC_OP(CODEC_ID_ADPCM_ADX         ,74,"adpcm adx") \
 CODEC_OP(CODEC_ID_ADPCM_EA          ,75,"adpcm ea") \
 CODEC_OP(CODEC_ID_ADPCM_G726        ,67,"adpcm g726") \
 CODEC_OP(CODEC_ID_ADPCM_CT          ,80,"adpcm ct") \
 CODEC_OP(CODEC_ID_ADPCM_SWF         ,85,"adpcm swf") \
 CODEC_OP(CODEC_ID_ADPCM_YAMAHA      ,89,"adpcm yamaha") \
 CODEC_OP(CODEC_ID_H264              ,38,"h264") \
 CODEC_OP(CODEC_ID_SVQ3              ,39,"svq3") \
 CODEC_OP(CODEC_ID_FLV1              ,41,"flv1") \
 CODEC_OP(CODEC_ID_ASV1              ,42,"asv1") \
 CODEC_OP(CODEC_ID_ASV2              ,50,"asv2") \
 CODEC_OP(CODEC_ID_CYUV              ,44,"cyuv") \
 CODEC_OP(CODEC_ID_INDEO3            ,45,"indeo3") \
 CODEC_OP(CODEC_ID_MSVIDEO1          ,46,"msvideo1") \
 CODEC_OP(CODEC_ID_CINEPAK           ,47,"cinepak") \
 CODEC_OP(CODEC_ID_VCR1              ,51,"vcr1") \
 CODEC_OP(CODEC_ID_MSRLE             ,52,"msrle") \
 CODEC_OP(CODEC_ID_SP5X              ,53,"") \
 CODEC_OP(CODEC_ID_THEORA            ,54,"theora") \
 CODEC_OP(CODEC_ID_MPEG2TS           ,56,"") \
 CODEC_OP(CODEC_ID_MSZH              ,57,"mszh") \
 CODEC_OP(CODEC_ID_ZLIB              ,58,"zlib") \
 CODEC_OP(CODEC_ID_AMR_NB            ,59,"amr nb") \
 CODEC_OP(CODEC_ID_8BPS              ,60,"8bps") \
 CODEC_OP(CODEC_ID_COREPNG           ,61,"corepng") \
 CODEC_OP(CODEC_ID_H261              ,62,"h261") \
 CODEC_OP(CODEC_ID_QTRLE             ,63,"qtrle") \
 CODEC_OP(CODEC_ID_RPZA              ,64,"rpza") \
 CODEC_OP(CODEC_ID_SMC               ,65,"") \
 CODEC_OP(CODEC_ID_TRUEMOTION1       ,66,"truemotion") \
 CODEC_OP(CODEC_ID_TRUEMOTION2       ,93,"truemotion2") \
 CODEC_OP(CODEC_ID_FLAC              ,76,"flac") \
 CODEC_OP(CODEC_ID_TSCC              ,77,"tscc") \
 CODEC_OP(CODEC_ID_SNOW              ,78,"snow") \
 CODEC_OP(CODEC_ID_GSM_MS            ,79,"gsm ms") \
 CODEC_OP(CODEC_ID_PNG               ,81,"png") \
 CODEC_OP(CODEC_ID_QPEG              ,82,"qpeg") \
 CODEC_OP(CODEC_ID_LOCO              ,86,"loco") \
 CODEC_OP(CODEC_ID_WNV1              ,87,"wnv1") \
 CODEC_OP(CODEC_ID_TTA               ,88,"tta") \
 CODEC_OP(CODEC_ID_DTS               ,90,"") \
 CODEC_OP(CODEC_ID_AAC               ,91,"") \
 CODEC_OP(CODEC_ID_QDM2              ,94,"qdm2") \
 CODEC_OP(CODEC_ID_MP3ADU            ,95,"") \
 CODEC_OP(CODEC_ID_MP3ON4            ,96,"") \
 CODEC_OP(CODEC_ID_DVD_SUBTITLE      ,92,"") \
 CODEC_OP(CODEC_ID_COOK              ,97,"cook") \
 CODEC_OP(CODEC_ID_TRUESPEECH        ,99,"truespeech") \
 \
 CODEC_OP(CODEC_ID_RAW           ,100,"raw") \
 CODEC_OP(CODEC_ID_YUY2          ,101,"raw") \
 CODEC_OP(CODEC_ID_RGB2          ,102,"raw") \
 CODEC_OP(CODEC_ID_RGB3          ,103,"raw") \
 CODEC_OP(CODEC_ID_RGB5          ,104,"raw") \
 CODEC_OP(CODEC_ID_RGB6          ,105,"raw") \
 CODEC_OP(CODEC_ID_BGR2          ,112,"raw") \
 CODEC_OP(CODEC_ID_BGR3          ,113,"raw") \
 CODEC_OP(CODEC_ID_BGR5          ,114,"raw") \
 CODEC_OP(CODEC_ID_BGR6          ,115,"raw") \
 CODEC_OP(CODEC_ID_YV12          ,106,"raw") \
 CODEC_OP(CODEC_ID_YVYU          ,107,"raw") \
 CODEC_OP(CODEC_ID_UYVY          ,108,"raw") \
 CODEC_OP(CODEC_ID_VYUY          ,121,"raw") \
 CODEC_OP(CODEC_ID_I420          ,109,"raw") \
 CODEC_OP(CODEC_ID_CLJR          ,110,"raw") \
 CODEC_OP(CODEC_ID_Y800          ,111,"raw") \
 CODEC_OP(CODEC_ID_444P          ,122,"raw") \
 CODEC_OP(CODEC_ID_422P          ,123,"raw") \
 CODEC_OP(CODEC_ID_411P          ,124,"raw") \
 CODEC_OP(CODEC_ID_410P          ,125,"raw") \
 CODEC_OP(CODEC_ID_NV12          ,116,"raw") \
 CODEC_OP(CODEC_ID_NV21          ,117,"raw") \
 CODEC_OP(CODEC_ID_PAL1          ,118,"raw") \
 CODEC_OP(CODEC_ID_PAL4          ,119,"raw") \
 CODEC_OP(CODEC_ID_PAL8          ,120,"raw") \
 CODEC_OP(CODEC_ID_LPCM          ,198,"raw") \
 CODEC_OP(CODEC_ID_PCM           ,199,"raw") \
 \
 CODEC_OP(CODEC_ID_XVID4         ,201,"xvid") \
 \
 CODEC_OP(CODEC_ID_LIBMPEG2      ,300,"libmpeg2") \
 \
 CODEC_OP(CODEC_ID_THEORA_LIB    ,400,"libtheora") \
 \
 CODEC_OP(CODEC_ID_MP3LIB        ,500,"mp3lib") \
 \
 CODEC_OP(CODEC_ID_LIBMAD        ,600,"libmad") \
 \
 CODEC_OP(CODEC_ID_LIBFAAD       ,700,"faad2") \
 \
 CODEC_OP(CODEC_ID_WMV9_LIB      ,900,"wmv9codec") \
 \
 CODEC_OP(CODEC_ID_AVISYNTH      ,1000,"avisynth") \
 \
 CODEC_OP(CODEC_ID_SKAL          ,1100,"skal's") \
 \
 CODEC_OP(CODEC_ID_X264          ,1200,"x264") \
 CODEC_OP(CODEC_ID_X264_LOSSLESS ,1201,"x264 lossless") \
 \
 CODEC_OP(CODEC_ID_LIBA52        ,1300,"liba52") \
 \
 CODEC_OP(CODEC_ID_SPDIF_AC3     ,1400,"s/pdif") \
 CODEC_OP(CODEC_ID_SPDIF_DTS     ,1401,"s/pdif") \
 \
 CODEC_OP(CODEC_ID_LIBDTS        ,1500,"libdts") \
 \
 CODEC_OP(CODEC_ID_TREMOR        ,1600,"tremor") \
 \
 CODEC_OP(CODEC_ID_REALAAC       ,1700,"realaac")

enum CodecID
{ 
 #define CODEC_OP(codecEnum,codecId,codecName) codecEnum=codecId,
 FFDSHOW_CODECS
 #undef CODEC_OP
};

#ifdef __cplusplus

//template<> struct isPOD<CodecID> {enum {is=true};};

const FOURCC* getCodecFOURCCs(CodecID codecId);
const char_t* getCodecName(CodecID codecId);

static __inline bool lavc_codec(int x)     {return x>    0 && x <100;}
static __inline bool raw_codec(int x)      {return x>= 100 && x <200;}
static __inline bool xvid_codec(int x)     {return x>= 200 && x <300;}
static __inline bool theora_codec(int x)   {return x==CODEC_ID_THEORA_LIB;}
static __inline bool mplayer_codec(int x)  {return x>= 500 && x <600;}
static __inline bool wmv9_codec(int x)     {return x>= 900 && x<1000;}
static __inline bool mpeg12_codec(int x)   {return x==CODEC_ID_MPEG1VIDEO || x==CODEC_ID_MPEG2VIDEO || x==CODEC_ID_LIBMPEG2;}
static __inline bool mpeg1_codec(int x)    {return x==CODEC_ID_MPEG1VIDEO || x==CODEC_ID_LIBMPEG2;}
static __inline bool mpeg2_codec(int x)    {return x==CODEC_ID_MPEG2VIDEO || x==CODEC_ID_LIBMPEG2;}
static __inline bool mpeg4_codec(int x)    {return x==CODEC_ID_MPEG4 || xvid_codec(x) || x==CODEC_ID_SKAL;}
static __inline bool spdif_codec(int x)    {return x>=1400 && x<1500;}
static __inline bool huffyuv_codec(int x)  {return x==CODEC_ID_HUFFYUV || x==CODEC_ID_FFVHUFF;}
static __inline bool x264_codec(int x)     {return x==CODEC_ID_X264 || x==CODEC_ID_X264_LOSSLESS;}

static __inline bool lossless_codec(int x) {return huffyuv_codec(x) || x==CODEC_ID_LJPEG || x==CODEC_ID_FFV1 || x==CODEC_ID_DVVIDEO || x==CODEC_ID_X264_LOSSLESS;}

//I'm not sure of all these
static __inline bool sup_CBR(int x)           {return !lossless_codec(x) && !raw_codec(x);}
static __inline bool sup_VBR_QUAL(int x)      {return !lossless_codec(x) && !raw_codec(x) && x!=CODEC_ID_SKAL;}
static __inline bool sup_VBR_QUANT(int x)     {return (lavc_codec(x) || xvid_codec(x) || theora_codec(x) || x==CODEC_ID_SKAL || x==CODEC_ID_X264) && !lossless_codec(x) && x!=CODEC_ID_SNOW;}
static __inline bool sup_XVID2PASS(int x)     {return sup_VBR_QUANT(x) && x!=CODEC_ID_X264 && x!=CODEC_ID_SNOW;}
static __inline bool sup_LAVC2PASS(int x)     {return (lavc_codec(x) && !lossless_codec(x) && x!=CODEC_ID_MJPEG && !raw_codec(x)) || x==CODEC_ID_X264;}

static __inline bool sup_interlace(int x)         {return x==CODEC_ID_MPEG4 || x==CODEC_ID_MPEG2VIDEO || xvid_codec(x) || x==CODEC_ID_SKAL;}
static __inline bool sup_gray(int x)              {return x!=CODEC_ID_LJPEG && x!=CODEC_ID_FFV1 && x!=CODEC_ID_SNOW && !theora_codec(x) && !wmv9_codec(x) && !raw_codec(x) && x!=CODEC_ID_SKAL && x!=CODEC_ID_DVVIDEO && !x264_codec(x);}
static __inline bool sup_globalheader(int x)      {return x==CODEC_ID_MPEG4;}
static __inline bool sup_part(int x)              {return x==CODEC_ID_MPEG4;}
static __inline bool sup_packedBitstream(int x)   {return xvid_codec(x);}
static __inline bool sup_minKeySet(int x)         {return x!=CODEC_ID_MJPEG && x!=CODEC_ID_SNOW && (!lossless_codec(x) || x==CODEC_ID_X264_LOSSLESS) && !wmv9_codec(x) && !raw_codec(x);}
static __inline bool sup_maxKeySet(int x)         {return x!=CODEC_ID_MJPEG && (!lossless_codec(x) || x==CODEC_ID_X264_LOSSLESS) && !raw_codec(x);}
static __inline bool sup_bframes(int x)           {return x==CODEC_ID_MPEG4 || x==CODEC_ID_MPEG1VIDEO || x==CODEC_ID_MPEG2VIDEO || xvid_codec(x) || x264_codec(x);}
static __inline bool sup_adaptiveBframes(int x)   {return lavc_codec(x) || x==CODEC_ID_X264;}
static __inline bool sup_closedGop(int x)         {return sup_bframes(x) && !x264_codec(x);}
static __inline bool sup_lavcme(int x)            {return lavc_codec(x) && x!=CODEC_ID_MJPEG && !lossless_codec(x);}
static __inline bool sup_quantProps(int x)        {return !lossless_codec(x) && !theora_codec(x) && !wmv9_codec(x) && !raw_codec(x) && x!=CODEC_ID_SNOW;}
static __inline bool sup_trellisQuant(int x)      {return x==CODEC_ID_MPEG4 || x==CODEC_ID_MPEG1VIDEO || x==CODEC_ID_MPEG2VIDEO || x==CODEC_ID_XVID4 || x==CODEC_ID_H263 || x==CODEC_ID_H263P || x==CODEC_ID_SKAL || x==CODEC_ID_X264;}
static __inline bool sup_masking(int x)           {return x==CODEC_ID_MPEG4 || x==CODEC_ID_H263 || x==CODEC_ID_H263P || x==CODEC_ID_MPEG1VIDEO || x==CODEC_ID_MPEG2VIDEO || xvid_codec(x) || x==CODEC_ID_SKAL || x==CODEC_ID_X264;}
static __inline bool sup_lavcOnePass(int x)       {return (lavc_codec(x) && !lossless_codec(x)) || x==CODEC_ID_X264;}
static __inline bool sup_perFrameQuant(int x)     {return !lossless_codec(x) && !wmv9_codec(x) && !raw_codec(x) && !x264_codec(x) && x!=CODEC_ID_SNOW;}
static __inline bool sup_4mv(int x)               {return x==CODEC_ID_MPEG4 || x==CODEC_ID_H263 || x==CODEC_ID_H263P || x==CODEC_ID_SNOW || x==CODEC_ID_SKAL;}
static __inline bool sup_aspect(int x)            {return x==CODEC_ID_MPEG4 || x==CODEC_ID_MPEG1VIDEO || x==CODEC_ID_MPEG2VIDEO || x==CODEC_ID_XVID4 || x==CODEC_ID_THEORA_LIB || x264_codec(x);}
static __inline bool sup_PSNR(int x)              {return (lavc_codec(x) && !lossless_codec(x)) || xvid_codec(x) || x==CODEC_ID_SKAL || x264_codec(x);}
static __inline bool sup_quantBias(int x)         {return lavc_codec(x) && !lossless_codec(x);}
static __inline bool sup_MPEGquant(int x)         {return x==CODEC_ID_MPEG4 || x==CODEC_ID_MSMPEG4V3 || x==CODEC_ID_MPEG2VIDEO || xvid_codec(x) || x==CODEC_ID_SKAL;}
static __inline bool sup_lavcQuant(int x)         {return lavc_codec(x) && sup_quantProps(x);}
static __inline bool sup_customQuantTables(int x) {return x==CODEC_ID_MPEG4 || xvid_codec(x) || x==CODEC_ID_MPEG1VIDEO || x==CODEC_ID_MPEG2VIDEO || x==CODEC_ID_SKAL || x==CODEC_ID_X264;}
static __inline bool sup_qpel(int x)              {return x==CODEC_ID_MPEG4 || x==CODEC_ID_SNOW || xvid_codec(x) || x==CODEC_ID_SKAL;}
static __inline bool sup_gmc(int x)               {return xvid_codec(x) || x==CODEC_ID_SKAL;}
static __inline bool sup_me_mv0(int x)            {return sup_lavcme(x) && x!=CODEC_ID_SNOW;}
static __inline bool sup_cbp_rd(int x)            {return x==CODEC_ID_MPEG4;}
static __inline bool sup_qns(int x)               {return lavc_codec(x) && sup_quantProps(x) && x!=CODEC_ID_MSMPEG4V3 && x!=CODEC_ID_MSMPEG4V2 && x!=CODEC_ID_MSMPEG4V1 && x!=CODEC_ID_WMV1 && x!=CODEC_ID_WMV2 && x!=CODEC_ID_MJPEG && x!=CODEC_ID_SNOW;}
static __inline bool sup_threads(int x)           {return x==CODEC_ID_DVVIDEO || x==CODEC_ID_MPEG1VIDEO || x==CODEC_ID_MPEG2VIDEO || x==CODEC_ID_H263 || x==CODEC_ID_H263P || x==CODEC_ID_FLV1 || x==CODEC_ID_RV10 || x==CODEC_ID_MPEG4 || x==CODEC_ID_MSMPEG4V1 || x==CODEC_ID_MSMPEG4V2 || x==CODEC_ID_MSMPEG4V3 || x==CODEC_ID_WMV1 || x==CODEC_ID_WMV2 || x==CODEC_ID_MJPEG || x264_codec(x);}
static __inline bool sup_palette(int x)           {return x==CODEC_ID_MSVIDEO1 || x==CODEC_ID_8BPS || x==CODEC_ID_QTRLE || x==CODEC_ID_TSCC || x==CODEC_ID_QPEG || x==CODEC_ID_PNG;}

#endif

#endif
