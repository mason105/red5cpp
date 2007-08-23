
#ifndef _CLASS_GOD_LANG_INDEXOUTOFBOUNDSEXCEPTION_H
#define _CLASS_GOD_LANG_INDEXOUTOFBOUNDSEXCEPTION_H

#ifdef __cplusplus

#include "lang/RuntimeException.h"
using namespace goddk::lang;

namespace goddk {
	namespace lang {
		/* \ingroup CXX_LANG_m
		 */
		class IndexOutOfBoundsException : public  virtual RuntimeException
		{
		public:
			inline IndexOutOfBoundsException()
			{
			}
			inline IndexOutOfBoundsException(const char* message) : RuntimeException(message)
			{
			}
			inline IndexOutOfBoundsException(const String* message) : RuntimeException(message)
			{
			}
			inline ~IndexOutOfBoundsException()
			{
			}
		};
		typedef CSmartPtr<IndexOutOfBoundsException>		IndexOutOfBoundsExceptionPtr;
	}
}

#endif

#endif
