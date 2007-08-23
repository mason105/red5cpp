

#ifndef _CLASS_GOD_NIO_READONLYBUFFEREXCEPTION_H
#define _CLASS_GOD_NIO_READONLYBUFFEREXCEPTION_H

#ifdef __cplusplus

#include "lang/UnsupportedOperationException.h"
using namespace goddk::lang;

namespace goddk {
	namespace nio {
		 /* \ingroup CXX_NIO_m
		 */
		class ReadOnlyBufferException : public  virtual UnsupportedOperationException
		{
		public:
			inline ReadOnlyBufferException()
			{
			}
			inline ReadOnlyBufferException(const char* message) : UnsupportedOperationException(message)
			{
			}
			inline ReadOnlyBufferException(const String* message) : UnsupportedOperationException(message)
			{
			}
			inline ~ReadOnlyBufferException()
			{
			}
		};
		typedef CSmartPtr<ReadOnlyBufferException>		ReadOnlyBufferExceptionPtr;
	}
}

#endif

#endif
