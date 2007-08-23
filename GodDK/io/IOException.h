
#ifndef _CLASS_GOD_IO_IOEXCEPTION_H
#define _CLASS_GOD_IO_IOEXCEPTION_H

#ifdef __cplusplus

#include "lang/Exception.h"
using namespace goddk::lang;

namespace goddk {
	namespace io {
		/*!\ingroup CXX_IO_m
		 */
		class IOException : public Exception
		{
		public:
			inline IOException()
			{
			}
			inline IOException(const char* message) : Exception(message)
			{
			}
			inline IOException(const String* message) : Exception(message)
			{
			}
			inline ~IOException()
			{
			}
		};
		typedef CSmartPtr<IOException>		IOExceptionPtr;
	}
}

#endif

#endif
