
#ifndef _CLASS_GOD_LANG_ILLEGALTHREADSTATEEXCEPTION_H
#define _CLASS_GOD_LANG_ILLEGALTHREADSTATEEXCEPTION_H

#ifdef __cplusplus

#include "lang/IllegalArgumentException.h"
using namespace goddk::lang;

namespace goddk {
	namespace lang {
		/* \ingroup CXX_LANG_m
		 */
		class IllegalThreadStateException : public virtual  IllegalArgumentException
		{
		public:
			inline IllegalThreadStateException()
			{
			}
			inline IllegalThreadStateException(const char* message) : IllegalArgumentException(message)
			{
			}
			inline IllegalThreadStateException(const String* message) : IllegalArgumentException(message)
			{
			}
			inline ~IllegalThreadStateException()
			{
			}
		};
		typedef CSmartPtr<IllegalThreadStateException>		IllegalThreadStateExceptionPtr;
	}
}

#endif

#endif
