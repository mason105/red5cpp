
#ifndef _CLASS_GOD_LANG_RUNTIMEEXCEPTION_H
#define _CLASS_GOD_LANG_RUNTIMEEXCEPTION_H

#ifdef __cplusplus

#include "lang/Exception.h"
using namespace goddk::lang;

namespace goddk {
	namespace lang {
		/*!\brief This class is the superclass of exceptions that can be thrown
		 *        during normal operation.
		 * \ingroup CXX_LANG_m
		 */
		class RuntimeException : public virtual  Exception
		{
		public:
			inline RuntimeException()
			{
			}
			inline RuntimeException(const char* message) : Exception(message)
			{
			}
			inline RuntimeException(const String* message) : Exception(message)
			{
			}
			inline RuntimeException(const Throwable* cause) : Exception(cause)
			{
			}
			inline ~RuntimeException()
			{
			}
		};
		typedef CSmartPtr<RuntimeException>		RuntimeExceptionPtr;
	}
}

#endif

#endif
