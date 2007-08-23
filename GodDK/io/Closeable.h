
#ifndef _INTERFACE_GOD_IO_CLOSEABLE_H
#define _INTERFACE_GOD_IO_CLOSEABLE_H

#ifdef __cplusplus

#include "io/IOException.h"
using namespace goddk::io;

namespace goddk {
	namespace io {
		class  Closeable
		{
		public:
			virtual ~Closeable() {}

			virtual void close() throw (IOExceptionPtr) = 0;
		};
	}
}

#endif

#endif
