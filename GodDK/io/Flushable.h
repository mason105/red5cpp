
#ifndef _INTERFACE_GOD_IO_FLUSHABLE_H
#define _INTERFACE_GOD_IO_FLUSHABLE_H

#ifdef __cplusplus

#include "io/IOException.h"
using namespace goddk::io;


namespace goddk {
	namespace io {
		class  Flushable
		{
		public:
			virtual ~Flushable() {}

			virtual void flush() throw (IOExceptionPtr) = 0;
		};
	}
}

#endif

#endif
