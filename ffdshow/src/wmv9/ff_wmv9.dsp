# Microsoft Developer Studio Project File - Name="ff_wmv9" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=ff_wmv9 - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "ff_wmv9.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ff_wmv9.mak" CFG="ff_wmv9 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ff_wmv9 - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ff_wmv9 - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ff_wmv9 - Win32 Debug Unicode" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ff_wmv9 - Win32 Debug"

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
# ADD BASE CPP /nologo /MDd /I ""C:\Program Files\STLport\stlport"" /I "include" /I "../.." /ZI /W0 /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "DEBUG" /D "SUPPORT_INTERLACE" /D "FFDEBUG=0" /D "UCLIBCPP" /Gm /Gy /Yu"stdafx.h" /GZ /c /GX 
# ADD CPP /nologo /MDd /I ""C:\Program Files\STLport\stlport"" /I "include" /I "../.." /ZI /W0 /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "DEBUG" /D "SUPPORT_INTERLACE" /D "FFDEBUG=0" /D "UCLIBCPP" /Gm /Gy /Yu"stdafx.h" /GZ /c /GX 
# ADD BASE MTL /nologo /win32 
# ADD MTL /nologo /win32 
# ADD BASE RSC /l 1033 
# ADD RSC /l 1033 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo 
# ADD BSC32 /nologo 
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib msvcrtd.lib msvcprtd.lib kernel32.lib uuid.lib oleaut32.lib ole32.lib strmiids.lib dmoguids.lib oldnames.lib $(NOINHERIT) /nologo /dll /out:"..\..\..\..\bin\debug\ff_wmv9.dll" /incremental:yes /nodefaultlib /def:"ff_wmv9.def" /debug /pdbtype:sept /subsystem:windows /implib:"../../../../lib/debug/$(ProjectName).lib" /machine:ix86 
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib msvcrtd.lib msvcprtd.lib kernel32.lib uuid.lib oleaut32.lib ole32.lib strmiids.lib dmoguids.lib oldnames.lib $(NOINHERIT) /nologo /dll /out:"..\..\..\..\bin\debug\ff_wmv9.dll" /incremental:yes /nodefaultlib /def:"ff_wmv9.def" /debug /pdbtype:sept /subsystem:windows /implib:"../../../../lib/debug/$(ProjectName).lib" /machine:ix86 

!ELSEIF  "$(CFG)" == "ff_wmv9 - Win32 Release"

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
# ADD BASE CPP /nologo /MD /I ""C:\Program Files\STLport\stlport"" /I "include" /I "../.." /W4 /O1 /Og /Ob1 /Oi /Os /Oy /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "SUPPORT_INTERLACE" /D "FFDEBUG=0" /GF /Yu"stdafx.h" /c /GX 
# ADD CPP /nologo /MD /I ""C:\Program Files\STLport\stlport"" /I "include" /I "../.." /W4 /O1 /Og /Ob1 /Oi /Os /Oy /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "SUPPORT_INTERLACE" /D "FFDEBUG=0" /GF /Yu"stdafx.h" /c /GX 
# ADD BASE MTL /nologo /win32 
# ADD MTL /nologo /win32 
# ADD BASE RSC /l 1033 
# ADD RSC /l 1033 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo 
# ADD BSC32 /nologo 
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib msvcrt.lib msvcprt.lib kernel32.lib uuid.lib oleaut32.lib ole32.lib strmiids.lib dmoguids.lib oldnames.lib $(NOINHERIT) /nologo /dll /out:"..\..\..\..\bin\release\ff_wmv9.dll" /incremental:no /nodefaultlib /def:"ff_wmv9.def" /pdbtype:sept /subsystem:windows /opt:ref /opt:icf /implib:"../../../../lib/ff_wmv9.lib" /machine:ix86 
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib msvcrt.lib msvcprt.lib kernel32.lib uuid.lib oleaut32.lib ole32.lib strmiids.lib dmoguids.lib oldnames.lib $(NOINHERIT) /nologo /dll /out:"..\..\..\..\bin\release\ff_wmv9.dll" /incremental:no /nodefaultlib /def:"ff_wmv9.def" /pdbtype:sept /subsystem:windows /opt:ref /opt:icf /implib:"../../../../lib/ff_wmv9.lib" /machine:ix86 

!ELSEIF  "$(CFG)" == "ff_wmv9 - Win32 Debug Unicode"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "debug_unicode"
# PROP BASE Intermediate_Dir "debug_unicode"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "debug_unicode"
# PROP Intermediate_Dir "debug_unicode"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /I ""C:\Program Files\STLport\stlport"" /I "include" /I "../.." /ZI /W0 /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "DEBUG" /D "SUPPORT_INTERLACE" /D "FFDEBUG=0" /D "UCLIBCPP" /D "_UNICODE" /Gm /Gy /Yu"stdafx.h" /GZ /c /GX 
# ADD CPP /nologo /MDd /I ""C:\Program Files\STLport\stlport"" /I "include" /I "../.." /ZI /W0 /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "DEBUG" /D "SUPPORT_INTERLACE" /D "FFDEBUG=0" /D "UCLIBCPP" /D "_UNICODE" /Gm /Gy /Yu"stdafx.h" /GZ /c /GX 
# ADD BASE MTL /nologo /win32 
# ADD MTL /nologo /win32 
# ADD BASE RSC /l 1033 
# ADD RSC /l 1033 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo 
# ADD BSC32 /nologo 
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib msvcrtd.lib msvcprtd.lib kernel32.lib uuid.lib oleaut32.lib ole32.lib strmiids.lib dmoguids.lib oldnames.lib $(NOINHERIT) /nologo /dll /out:"..\..\..\bin\ff_wmv9.dll" /incremental:yes /nodefaultlib /def:"ff_wmv9.def" /debug /pdbtype:sept /subsystem:windows /implib:"$(OutDir)/$(ProjectName).lib" /machine:ix86 
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib msvcrtd.lib msvcprtd.lib kernel32.lib uuid.lib oleaut32.lib ole32.lib strmiids.lib dmoguids.lib oldnames.lib $(NOINHERIT) /nologo /dll /out:"..\..\..\bin\ff_wmv9.dll" /incremental:yes /nodefaultlib /def:"ff_wmv9.def" /debug /pdbtype:sept /subsystem:windows /implib:"$(OutDir)/$(ProjectName).lib" /machine:ix86 

!ENDIF

# Begin Target

# Name "ff_wmv9 - Win32 Debug"
# Name "ff_wmv9 - Win32 Release"
# Name "ff_wmv9 - Win32 Debug Unicode"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;def;odl;idl;hpj;bat;asm"
# Begin Source File

SOURCE=combase.cpp
# End Source File
# Begin Source File

SOURCE=ff_wmv9.cpp
# End Source File
# Begin Source File

SOURCE=..\imgFilters\ffImgfmt.cpp
# End Source File
# Begin Source File

SOURCE=GenProfile_lib.cpp
# End Source File
# Begin Source File

SOURCE=nssBuffer.cpp
# End Source File
# Begin Source File

SOURCE=stdafx.cpp

!IF  "$(CFG)" == "ff_wmv9 - Win32 Debug"

# ADD CPP /nologo /Yc"stdafx.h" /GZ /GX 
!ELSEIF  "$(CFG)" == "ff_wmv9 - Win32 Release"

# ADD CPP /nologo /Yc"stdafx.h" /GX 
!ELSEIF  "$(CFG)" == "ff_wmv9 - Win32 Debug Unicode"

# ADD CPP /nologo /Yc"stdafx.h" /GZ /GX 
!ENDIF

# End Source File
# Begin Source File

SOURCE=videoenc.cpp
# End Source File
# Begin Source File

SOURCE=writerSink.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;inc"
# Begin Source File

SOURCE=combase.h
# End Source File
# Begin Source File

SOURCE=encappErr.h
# End Source File
# Begin Source File

SOURCE=encode.h
# End Source File
# Begin Source File

SOURCE=ff_wmv9.h
# End Source File
# Begin Source File

SOURCE=GenProfile_lib.h
# End Source File
# Begin Source File

SOURCE=nssBuffer.h
# End Source File
# Begin Source File

SOURCE=stdafx.h
# End Source File
# Begin Source File

SOURCE=Tdll.h
# End Source File
# Begin Source File

SOURCE=videoenc.h
# End Source File
# Begin Source File

SOURCE=writerSink.h
# End Source File
# End Group
# Begin Source File

SOURCE=ff_wmv9.def
# End Source File
# End Target
# End Project

