CFLAGS+= -I. -I../.. -I../../cygwin -I../../baseclasses -Iinclude -DSUPPORT_INTERLACE
       
SRCS=ff_wmv9.cpp GenProfile_lib.cpp nssBuffer.cpp videoenc.cpp writerSink.cpp \
     include/wmguids.cpp ../../imgFilters/ffImgfmt.cpp combase.cpp

SLIB=../../../bin/ff_wmv9.dll
DEF=ff_wmv9.def

GCCLIBS=-lstdc++ -lsupc++ -luuid -lole32 -loleaut32 -lwinmm -lgdi32 -ldxguid
CLLIBS=msvcprt.lib ole32.lib oleaut32.lib winmm.lib gdi32.lib dxguid.lib strmiids.lib uuid.lib

include ../../makefile_c.inc

CFLAGS+=-w

.all: $(SLIB)

clean: 
	rm -f *.o include/*.o *~ $(SLIB)

#
# include dependency files if they exist
#
ifneq ($(wildcard .depend),)
include .depend
endif
