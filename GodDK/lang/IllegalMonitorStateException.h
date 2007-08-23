

#ifndef _CLASS_GOD_LANG_ILLEGALMONITORSTATEEXCEPTION_H
#define _CLASS_GOD_LANG_ILLEGALMONITORSTATEEXCEPTION_H

#ifdef __cplusplus

#include "lang/RuntimeException.h"
using namespace goddk::lang;

namespace goddk {
	namespace lang {
		/* \ingroup CXX_LANG_m
		 */
		class IllegalMonitorStateException : public virtual RuntimeException
		{
		public:
			inline IllegalMonitorStateException()
			{
			}
			inline IllegalMonitorStateException(const char* message) : RuntimeException(message)
			{
			}
			inline IllegalMonitorStateException(const String* message) : RuntimeException(message)
			{
			}
			inline ~IllegalMonitorStateException()
			{
			}
		};
		typedef CSmartPtr<IllegalMonitorStateException>		IllegalMonitorStateExceptionPtr;
	}
}

#endif

#endif
