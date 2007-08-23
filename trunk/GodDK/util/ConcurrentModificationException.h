
#ifndef _CLASS_GOD_UTIL_CONCURRENTMODIFICATIONEXCEPTION_H
#define _CLASS_GOD_UTIL_CONCURRENTMODIFICATIONEXCEPTION_H

#ifdef __cplusplus

#include "lang/RuntimeException.h"
#include "lang/String.h"
using namespace goddk::lang;

namespace goddk {
	namespace util {
		/*!\ingroup CXX_UTIL_m
		 */
		class ConcurrentModificationException : public  virtual RuntimeException
		{
		public:
			inline ConcurrentModificationException()
			{
			}
			inline ConcurrentModificationException(const char* message) : RuntimeException(message)
			{
			}
			inline ConcurrentModificationException(const String* message) : RuntimeException(message)
			{
			}
			inline ~ConcurrentModificationException()
			{
			}
		};
		typedef CSmartPtr<ConcurrentModificationException>		ConcurrentModificationExceptionPtr;
	}
}

#endif

#endif
