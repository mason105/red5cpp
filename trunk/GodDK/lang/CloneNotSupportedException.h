

#ifndef _CLASS_GOD_LANG_CLONENOTSUPPORTEDEXCEPTION_H
#define _CLASS_GOD_LANG_CLONENOTSUPPORTEDEXCEPTION_H

#ifdef __cplusplus

#include "lang/Exception.h"
using namespace goddk::lang;

namespace goddk {
	namespace lang {
		/* \ingroup CXX_LANG_m
		 */
		class CloneNotSupportedException : public virtual  Exception
		{
		public:
			inline CloneNotSupportedException()
			{
			}
			inline CloneNotSupportedException(const char* message) : Exception(message)
			{
			}
			inline CloneNotSupportedException(const String* message) : Exception(message)
			{
			}
			inline CloneNotSupportedException(const String& message) : Exception(&message)
			{
			}
			inline ~CloneNotSupportedException()
			{
			}
		
		};
		typedef CSmartPtr<CloneNotSupportedException>		CloneNotSupportedExceptionPtr;
	}
}

#endif

#endif
