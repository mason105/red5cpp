

#ifndef _CLASS_GOD_UTIL_NOSUCHELEMENTEXCEPTION_H
#define _CLASS_GOD_UTIL_NOSUCHELEMENTEXCEPTION_H

#ifdef __cplusplus

#include "lang/RuntimeException.h"
#include "lang/String.h"
using namespace goddk::lang;

namespace goddk {
	namespace util {
		/*!\ingroup CXX_UTIL_m
		 */
		class NoSuchElementException : public  virtual RuntimeException
		{
		public:
			inline NoSuchElementException()
			{
			}
			inline NoSuchElementException(const char* message) : RuntimeException(message)
			{
			}
			inline NoSuchElementException(const String* message) : RuntimeException(message)
			{
			}
			inline ~NoSuchElementException()
			{
			}
		};
		typedef CSmartPtr<NoSuchElementException>		NoSuchElementExceptionPtr;
	}
}

#endif

#endif
