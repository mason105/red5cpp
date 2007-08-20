# Microsoft Developer Studio Project File - Name="libffmpeg" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=libffmpeg - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "libffmpeg.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "libffmpeg.mak" CFG="libffmpeg - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "libffmpeg - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "libffmpeg - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "libffmpeg - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
F90=df.exe
LINK32=link.exe
MTL=midl.exe
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I "./" /I "../../include" /I "./libavcodec" /I "./libavformat" /I "./libavutil" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /D "EMULATE_INTTYPES" /D "HAVE_AV_CONFIG_H" /YX /FD /c
# ADD BASE RSC /l 0x804 /d "NDEBUG"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "libffmpeg - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
F90=df.exe
LINK32=link.exe
MTL=midl.exe
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I "./" /I "../../include" /I "./libavcodec" /I "./libavformat" /I "./libavutil" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /D "EMULATE_INTTYPES" /D "HAVE_AV_CONFIG_H" /YX /FD /GZ /c
# ADD BASE RSC /l 0x804 /d "_DEBUG"
# ADD RSC /l 0x804 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ENDIF 

# Begin Target

# Name "libffmpeg - Win32 Release"
# Name "libffmpeg - Win32 Debug"
# Begin Group "libavcodec"

# PROP Default_Filter ""
# Begin Group "alpha"

# PROP Default_Filter ""
# End Group
# Begin Group "armv4l"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\libavcodec\armv4l\mpegvideo_arm.c
# End Source File
# End Group
# Begin Group "i386"

# PROP Default_Filter ""
# End Group
# Begin Group "libpostproc"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\libavcodec\libpostproc\postprocess.c
# End Source File
# End Group
# Begin Group "mlib"

# PROP Default_Filter ""
# End Group
# Begin Group "ppc"

# PROP Default_Filter ""
# End Group
# Begin Group "ps2"

# PROP Default_Filter ""
# End Group
# Begin Group "sh4"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\libavcodec\sh4\dsputil_sh4.c
# End Source File
# Begin Source File

SOURCE=.\libavcodec\sh4\idct_sh4.c
# End Source File
# End Group
# Begin Group "sparc"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\libavcodec\sparc\dsputil_vis.c
# End Source File
# End Group
# Begin Group "amrwb"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\libavcodec\amrwb_float\dec_acelp.c
# End Source File
# Begin Source File

SOURCE=.\libavcodec\amrwb_float\dec_dtx.c
# End Source File
# Begin Source File

SOURCE=.\libavcodec\amrwb_float\dec_gain.c
# End Source File
# Begin Source File

SOURCE=.\libavcodec\amrwb_float\dec_if.c
# End Source File
# Begin Source File

SOURCE=.\libavcodec\amrwb_float\dec_lpc.c
# End Source File
# Begin Source File

SOURCE=.\libavcodec\amrwb_float\dec_main.c
# End Source File
# Begin Source File

SOURCE=.\libavcodec\amrwb_float\dec_rom.c
# End Source File
# Begin Source File

SOURCE=.\libavcodec\amrwb_float\dec_util.c
# End Source File
# Begin Source File

SOURCE=.\libavcodec\amrwb_float\enc_acelp.c
# End Source File
# Begin Source File

SOURCE=.\libavcodec\amrwb_float\enc_dtx.c
# End Source File
# Begin Source File

SOURCE=.\libavcodec\amrwb_float\enc_gain.c
# End Source File
# Begin Source File

SOURCE=.\libavcodec\amrwb_float\enc_if.c
# End Source File
# Begin Source File

SOURCE=.\libavcodec\amrwb_float\enc_lpc.c
# End Source File
# Begin Source File

SOURCE=.\libavcodec\amrwb_float\enc_main.c
# End Source File
# Begin Source File

SOURCE=.\libavcodec\amrwb_float\enc_rom.c
# End Source File
# Begin Source File

SOURCE=.\libavcodec\amrwb_float\enc_util.c
# End Source File
# Begin Source File

SOURCE=.\libavcodec\amrwb_float\if_rom.c
# End Source File
# End Group
# Begin Group "amrnb"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\libavcodec\amr_float\interf_dec.c
# End Source File
# Begin Source File

SOURCE=.\libavcodec\amr_float\interf_enc.c
# End Source File
# Begin Source File

SOURCE=.\libavcodec\amr_float\sp_dec.c
# End Source File
# Begin Source File

SOURCE=.\libavcodec\amr_float\sp_enc.c
# End Source File
# End Group
# Begin Source File

SOURCE=.\libavcodec\8bps.c
# End Source File
# Begin Source File

SOURCE=.\libavcodec\a52dec.c
# End Source File
# Begin Source File

SOURCE=.\libavcodec\aasc.c
# End Source File
# Begin Source File

SOURCE=.\libavcodec\ac3enc.c
# End Source File
# Begin Source File

SOURCE=.\libavcodec\adpcm.c
# End Source File
# Begin Source File

SOURCE=.\libavcodec\adx.c
# End Source File
# Begin Source File

SOURCE=.\libavcodec\alac.c
# End Source File
# Begin Source File

SOURCE=.\libavcodec\allcodecs.c
# End Source File
# Begin Source File

SOURCE=.\libavcodec\apiexample.c
# End Source File
# Begin Source File

SOURCE=.\libavcodec\asv1.c
# End Source File
# Begin Source File

SOURCE=.\libavcodec\audioconvert.c
# End Source File
# Begin Source File

SOURCE=.\libavcodec\avcodec.c
# End Source File
# Begin Source File

SOURCE=.\libavcodec\avcodec_4xm.c
# End Source File
# Begin Source File

SOURCE=.\libavcodec\avcodec_amr.c
# End Source File
# Begin Source File

SOURCE=.\libavcodec\avcodec_dv.c
# End Source File
# Begin Source File

SOURCE=.\libavcodec\avcodec_flac.c
# End Source File
# Begin Source File

SOURCE=.\libavcodec\avcodec_h264.c
# End Source File
# Begin Source File

SOURCE=.\libavcodec\avcodec_mjpeg.c
# End Source File
# Begin Source File

SOURCE=.\libavcodec\avcodec_pthread.c
# ADD CPP /I "../../XMediaOS\Pthread"
# End Source File
# Begin Source File

SOURCE=.\libavcodec\avcodec_raw.c
# End Source File
# Begin Source File

SOURCE=.\libavcodec\avcodec_utils.c
# End Source File
# Begin Source File

SOURCE=.\libavcodec\avs.c
# End Source File
# Begin Source File

SOURCE=.\libavcodec\bitstream.c
# End Source File
# Begin Source File

SOURCE=.\libavcodec\bitstream_filter.c
# End Source File
# Begin Source File

SOURCE=.\libavcodec\bmp.c
# End Source File
# Begin Source File

SOURCE=.\libavcodec\cabac.c
# End Source File
# Begin Source File

SOURCE=.\libavcodec\cavs.c
# End Source File
# Begin Source File

SOURCE=.\libavcodec\cavsdsp.c
# End Source File
# Begin Source File

SOURCE=.\libavcodec\cinepak.c
# End Source File
# Begin Source File

SOURCE=.\libavcodec\cljr.c
# End Source File
# Begin Source File

SOURCE=.\libavcodec\cook.c
# End Source File
# Begin Source File

SOURCE=.\libavcodec\cscd.c
# End Source File
# Begin Source File

SOURCE=.\libavcodec\cyuv.c
# End Source File
# Begin Source File

SOURCE=.\libavcodec\dpcm.c
# End Source File
# Begin Source File

SOURCE=.\libavcodec\dsputil.c
# End Source File
# Begin Source File

SOURCE=.\libavcodec\dtsdec.c
# End Source File
# Begin Source File

SOURCE=.\libavcodec\dvbsub.c
# End Source File
# Begin Source File

SOURCE=.\libavcodec\dvbsubdec.c
# End Source File
# Begin Source File

SOURCE=.\libavcodec\dvdsub.c
# End Source File
# Begin Source File

SOURCE=.\libavcodec\dvdsubenc.c
# End Source File
# Begin Source File

SOURCE=.\libavcodec\error_resilience.c
# End Source File
# Begin Source File

SOURCE=.\libavcodec\eval.c
# End Source File
# Begin Source File

SOURCE=.\libavcodec\faac.c
# ADD CPP /I "../../library/faac/include" /I "../../library/faad2"
# End Source File
# Begin Source File

SOURCE=.\libavcodec\faad.c
# ADD CPP /I "../../library/faac/include" /I "../../library/faad2/include"
# End Source File
# Begin Source File

SOURCE=.\libavcodec\faandct.c
# End Source File
# Begin Source File

SOURCE=.\libavcodec\fdctref.c
# End Source File
# Begin Source File

SOURCE=.\libavcodec\ffv1.c
# End Source File
# Begin Source File

SOURCE=.\libavcodec\flashsv.c
# End Source File
# Begin Source File

SOURCE=.\libavcodec\flicvideo.c
# End Source File
# Begin Source File

SOURCE=.\libavcodec\fraps.c
# End Source File
# Begin Source File

SOURCE=.\libavcodec\g726.c
# End Source File
# Begin Source File

SOURCE=.\libavcodec\golomb.c
# End Source File
# Begin Source File

SOURCE=.\libavcodec\h261.c
# End Source File
# Begin Source File

SOURCE=.\libavcodec\h263.c
# End Source File
# Begin Source File

SOURCE=.\libavcodec\h263dec.c
# End Source File
# Begin Source File

SOURCE=.\libavcodec\h264idct.c
# End Source File
# Begin Source File

SOURCE=.\libavcodec\huffyuv.c
# End Source File
# Begin Source File

SOURCE=.\libavcodec\idcinvideo.c
# End Source File
# Begin Source File

SOURCE=.\libavcodec\imgconvert.c
# End Source File
# Begin Source File

SOURCE=.\libavcodec\imgresample.c
# End Source File
# Begin Source File

SOURCE=.\libavcodec\indeo2.c
# End Source File
# Begin Source File

SOURCE=.\libavcodec\indeo3.c
# End Source File
# Begin Source File

SOURCE=.\libavcodec\interplayvideo.c
# End Source File
# Begin Source File

SOURCE=.\libavcodec\jfdctfst.c
# End Source File
# Begin Source File

SOURCE=.\libavcodec\jfdctint.c
# End Source File
# Begin Source File

SOURCE=.\libavcodec\jrevdct.c
# End Source File
# Begin Source File

SOURCE=.\libavcodec\lcl.c
# End Source File
# Begin Source File

SOURCE=.\libavcodec\libavcodec_common.c
# End Source File
# Begin Source File

SOURCE=.\libavcodec\libavcodec_fft.c
# End Source File
# Begin Source File

SOURCE=.\libavcodec\libavcodec_mdct.c
# End Source File
# Begin Source File

SOURCE=.\libavcodec\loco.c
# End Source File
# Begin Source File

SOURCE=.\libavcodec\lzo.c
# End Source File
# Begin Source File

SOURCE=.\libavcodec\mace.c
# End Source File
# Begin Source File

SOURCE=.\libavcodec\mmvideo.c
# End Source File
# Begin Source File

SOURCE=.\libavcodec\motion_est.c
# End Source File
# Begin Source File

SOURCE=.\libavcodec\mp3lameaudio.c
# ADD CPP /I "../../library/lame/include"
# End Source File
# Begin Source File

SOURCE=.\libavcodec\mpeg12.c
# End Source File
# Begin Source File

SOURCE=.\libavcodec\mpegaudio.c
# End Source File
# Begin Source File

SOURCE=.\libavcodec\mpegaudiodec.c
# End Source File
# Begin Source File

SOURCE=.\libavcodec\mpegvideo.c
# End Source File
# Begin Source File

SOURCE=.\libavcodec\msmpeg4.c
# End Source File
# Begin Source File

SOURCE=.\libavcodec\msrle.c
# End Source File
# Begin Source File

SOURCE=.\libavcodec\msvideo1.c
# End Source File
# Begin Source File

SOURCE=.\libavcodec\nuv.c
# End Source File
# Begin Source File

SOURCE=.\libavcodec\oggvorbis.c
# ADD CPP /I "../../library/libvorbis\include" /I "../../library/libogg/include"
# End Source File
# Begin Source File

SOURCE=.\libavcodec\opt.c
# End Source File
# Begin Source File

SOURCE=.\libavcodec\opts.c
# End Source File
# Begin Source File

SOURCE=.\libavcodec\os2thread.c
# End Source File
# Begin Source File

SOURCE=.\libavcodec\parser.c
# End Source File
# Begin Source File

SOURCE=.\libavcodec\pcm.c
# End Source File
# Begin Source File

SOURCE=.\libavcodec\qdm2.c
# End Source File
# Begin Source File

SOURCE=.\libavcodec\qdrw.c
# End Source File
# Begin Source File

SOURCE=.\libavcodec\qpeg.c
# End Source File
# Begin Source File

SOURCE=.\libavcodec\qtrle.c
# End Source File
# Begin Source File

SOURCE=.\libavcodec\ra144.c
# End Source File
# Begin Source File

SOURCE=.\libavcodec\ra288.c
# End Source File
# Begin Source File

SOURCE=.\libavcodec\rangecoder.c
# End Source File
# Begin Source File

SOURCE=.\libavcodec\ratecontrol.c
# End Source File
# Begin Source File

SOURCE=.\libavcodec\resample.c
# End Source File
# Begin Source File

SOURCE=.\libavcodec\resample2.c
# End Source File
# Begin Source File

SOURCE=.\libavcodec\roqvideo.c
# End Source File
# Begin Source File

SOURCE=.\libavcodec\rpza.c
# End Source File
# Begin Source File

SOURCE=.\libavcodec\rv10.c
# End Source File
# Begin Source File

SOURCE=.\libavcodec\shorten.c
# End Source File
# Begin Source File

SOURCE=.\libavcodec\simple_idct.c
# End Source File
# Begin Source File

SOURCE=.\libavcodec\smacker.c
# End Source File
# Begin Source File

SOURCE=.\libavcodec\smc.c
# End Source File
# Begin Source File

SOURCE=.\libavcodec\sonic.c
# End Source File
# Begin Source File

SOURCE=.\libavcodec\svq1.c
# End Source File
# Begin Source File

SOURCE=.\libavcodec\truemotion1.c
# End Source File
# Begin Source File

SOURCE=.\libavcodec\truemotion2.c
# End Source File
# Begin Source File

SOURCE=.\libavcodec\truespeech.c
# End Source File
# Begin Source File

SOURCE=.\libavcodec\tscc.c
# End Source File
# Begin Source File

SOURCE=.\libavcodec\ulti.c
# End Source File
# Begin Source File

SOURCE=.\libavcodec\vc1.c
# End Source File
# Begin Source File

SOURCE=.\libavcodec\vc1dsp.c
# End Source File
# Begin Source File

SOURCE=.\libavcodec\vcr1.c
# End Source File
# Begin Source File

SOURCE=.\libavcodec\vmdav.c
# End Source File
# Begin Source File

SOURCE=.\libavcodec\vp3.c
# End Source File
# Begin Source File

SOURCE=.\libavcodec\vp3dsp.c
# End Source File
# Begin Source File

SOURCE=.\libavcodec\vqavideo.c
# End Source File
# Begin Source File

SOURCE=.\libavcodec\wmadec.c
# End Source File
# Begin Source File

SOURCE=.\libavcodec\wnv1.c
# End Source File
# Begin Source File

SOURCE=".\libavcodec\ws-snd1.c"
# End Source File
# Begin Source File

SOURCE=.\libavcodec\xan.c
# End Source File
# Begin Source File

SOURCE=.\libavcodec\xl.c
# End Source File
# Begin Source File

SOURCE=.\libavcodec\xvmcvideo.c
# End Source File
# Begin Source File

SOURCE=.\libavcodec\zmbv.c
# End Source File
# End Group
# Begin Group "libavformat"

# PROP Default_Filter ""
# Begin Group "libpng"

# PROP Default_Filter ""
# End Group
# Begin Source File

SOURCE=.\libavformat\4xm.c
# End Source File
# Begin Source File

SOURCE=.\libavformat\allformats.c
# End Source File
# Begin Source File

SOURCE=.\libavformat\amr.c
# End Source File
# Begin Source File

SOURCE=".\libavformat\asf-enc.c"
# End Source File
# Begin Source File

SOURCE=.\libavformat\avformat_asf.c
# End Source File
# Begin Source File

SOURCE=.\libavformat\avformat_au.c
# End Source File
# Begin Source File

SOURCE=.\libavformat\avformat_http.c
# End Source File
# Begin Source File

SOURCE=.\libavformat\avformat_ogg.c
# ADD CPP /I "../../library/libogg/include"
# End Source File
# Begin Source File

SOURCE=.\libavformat\avformat_rtsp.c
# End Source File
# Begin Source File

SOURCE=.\libavformat\avformat_tcp.c
# End Source File
# Begin Source File

SOURCE=.\libavformat\avformat_udp.c
# End Source File
# Begin Source File

SOURCE=.\libavformat\avformat_wav.c
# End Source File
# Begin Source File

SOURCE=.\libavformat\avidec.c
# End Source File
# Begin Source File

SOURCE=.\libavformat\avienc.c
# End Source File
# Begin Source File

SOURCE=.\libavformat\avio.c
# End Source File
# Begin Source File

SOURCE=.\libavformat\aviobuf.c
# End Source File
# Begin Source File

SOURCE=.\libavformat\barpainet.c
# End Source File
# Begin Source File

SOURCE=.\libavformat\cutils.c
# End Source File
# Begin Source File

SOURCE=.\libavformat\dv.c
# End Source File
# Begin Source File

SOURCE=.\libavformat\ffm.c
# End Source File
# Begin Source File

SOURCE=.\libavformat\file.c
# End Source File
# Begin Source File

SOURCE=.\libavformat\flic.c
# End Source File
# Begin Source File

SOURCE=.\libavformat\flvdec.c
# End Source File
# Begin Source File

SOURCE=.\libavformat\flvenc.c
# End Source File
# Begin Source File

SOURCE=.\libavformat\framehook.c
# End Source File
# Begin Source File

SOURCE=.\libavformat\gif.c
# End Source File
# Begin Source File

SOURCE=.\libavformat\gifdec.c
# End Source File
# Begin Source File

SOURCE=.\libavformat\idcin.c
# End Source File
# Begin Source File

SOURCE=.\libavformat\idroq.c
# End Source File
# Begin Source File

SOURCE=.\libavformat\img.c
# End Source File
# Begin Source File

SOURCE=.\libavformat\ipmovie.c
# End Source File
# Begin Source File

SOURCE=.\libavformat\jpeg.c
# End Source File
# Begin Source File

SOURCE=.\libavformat\libavformat_crc.c
# End Source File
# Begin Source File

SOURCE=.\libavformat\libavformat_utils.c
# End Source File
# Begin Source File

SOURCE=.\libavformat\matroska.c
# End Source File
# Begin Source File

SOURCE=.\libavformat\mov.c
# End Source File
# Begin Source File

SOURCE=.\libavformat\movenc.c
# End Source File
# Begin Source File

SOURCE=.\libavformat\mp3.c
# End Source File
# Begin Source File

SOURCE=.\libavformat\mpeg.c
# End Source File
# Begin Source File

SOURCE=.\libavformat\mpegts.c
# End Source File
# Begin Source File

SOURCE=.\libavformat\mpegtsenc.c
# End Source File
# Begin Source File

SOURCE=.\libavformat\mpjpeg.c
# End Source File
# Begin Source File

SOURCE=.\libavformat\nut.c
# End Source File
# Begin Source File

SOURCE=.\libavformat\os_support.c
# End Source File
# Begin Source File

SOURCE=.\libavformat\png.c
# End Source File
# Begin Source File

SOURCE=.\libavformat\pnm.c
# End Source File
# Begin Source File

SOURCE=.\libavformat\psxstr.c
# End Source File
# Begin Source File

SOURCE=.\libavformat\raw.c
# End Source File
# Begin Source File

SOURCE=.\libavformat\rm.c
# End Source File
# Begin Source File

SOURCE=.\libavformat\rtp.c
# End Source File
# Begin Source File

SOURCE=.\libavformat\rtpproto.c
# End Source File
# Begin Source File

SOURCE=.\libavformat\segafilm.c
# End Source File
# Begin Source File

SOURCE=.\libavformat\sgi.c
# End Source File
# Begin Source File

SOURCE=.\libavformat\sierravmd.c
# End Source File
# Begin Source File

SOURCE=.\libavformat\swf.c
# End Source File
# Begin Source File

SOURCE=.\libavformat\wc3movie.c
# End Source File
# Begin Source File

SOURCE=.\libavformat\westwood.c
# End Source File
# Begin Source File

SOURCE=.\libavformat\yuv.c
# End Source File
# Begin Source File

SOURCE=.\libavformat\yuv4mpeg.c
# End Source File
# End Group
# Begin Group "vhook"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\vhook\null.c
# End Source File
# End Group
# Begin Group "libavutil"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\libavutil\adler32.c
# End Source File
# Begin Source File

SOURCE=.\libavutil\crc.c
# End Source File
# Begin Source File

SOURCE=.\libavutil\integer.c
# End Source File
# Begin Source File

SOURCE=.\libavutil\intfloat_readwrite.c
# End Source File
# Begin Source File

SOURCE=.\libavutil\lls.c
# End Source File
# Begin Source File

SOURCE=.\libavutil\log.c
# End Source File
# Begin Source File

SOURCE=.\libavutil\mathematics.c
# End Source File
# Begin Source File

SOURCE=.\libavutil\md5.c
# End Source File
# Begin Source File

SOURCE=.\libavutil\mem.c
# End Source File
# Begin Source File

SOURCE=.\libavutil\rational.c
# End Source File
# End Group
# End Target
# End Project
