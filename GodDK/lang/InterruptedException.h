
#ifndef _CLASS_GOD_LANG_INTERRUPTEDEXCEPTION_H
#define _CLASS_GOD_LANG_INTERRUPTEDEXCEPTION_H

#ifdef __cplusplus

#include "lang/Exception.h"
using namespace goddk::lang;

namespace goddk {
	namespace lang {
		/* \ingroup CXX_LANG_m
		 */
		class InterruptedException : public virtual  Exception
		{
		public:
			inline InterruptedException()
			{
			}
			inline InterruptedException(const char* message) : Exception(message)
			{
			}
			inline InterruptedException(const String* message) : Exception(message)
			{
			}
			inline ~InterruptedException()
			{
			}
		};
		typedef CSmartPtr<InterruptedException>		InterruptedExceptionPtr;
	}
}

#endif

#endif
