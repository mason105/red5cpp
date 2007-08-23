
#ifndef _CLASS_GOD_NIO_INVALIDMARKEXCEPTION_H
#define _CLASS_GOD_NIO_INVALIDMARKEXCEPTION_H

#ifdef __cplusplus

#include "lang/IllegalStateException.h"
using namespace goddk::lang;

namespace goddk {
	namespace nio {
		/*!\ingroup CXX_NIO_m
		 */
		class InvalidMarkException : public  virtual IllegalStateException
		{
		public:
			inline InvalidMarkException()
			{
			}
			inline InvalidMarkException(const char* message) : IllegalStateException(message)
			{
			}
			inline InvalidMarkException(const String* message) : IllegalStateException(message)
			{
			}
			inline ~InvalidMarkException()
			{
			}
		};
		typedef CSmartPtr<InvalidMarkException>		InvalidMarkExceptionPtr;
	}
}

#endif

#endif
