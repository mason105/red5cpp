
#ifndef _CLASS_GOD_IO_EOFEXCEPTION_H
#define _CLASS_GOD_IO_EOFEXCEPTION_H

#ifdef __cplusplus

#include "io/IOException.h"
using namespace goddk::io;

namespace goddk {
	namespace io {
		/*!\ingroup CXX_IO_m
		 */
		class EOFException : public IOException
		{
		public:
			inline EOFException()
			{
			}
			inline EOFException(const char* message) : IOException(message)
			{
			}
			inline EOFException(const String* message) : IOException(message)
			{
			}
			inline ~EOFException()
			{
			}
		};
		typedef CSmartPtr<EOFException>		EOFExceptionPtr;
	}
}

#endif

#endif
