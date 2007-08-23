

#ifndef _CLASS_GOD_LANG_ILLEGALSTATEEXCEPTION_H
#define _CLASS_GOD_LANG_ILLEGALSTATEEXCEPTION_H

#ifdef __cplusplus

#include "lang/RuntimeException.h"
using namespace goddk::lang;

namespace goddk {
	namespace lang {
		/*!\brief This class is used to indicate that a method was called at
		 *        an illegal or inappropriate time, e.g. before an object
		 *        was initialized.
		 * \ingroup CXX_LANG_m
		 */
		class IllegalStateException : public virtual  RuntimeException
		{
		public:
			inline IllegalStateException()
			{
			}
			inline IllegalStateException(const char* message) : RuntimeException(message)
			{
			}
			inline IllegalStateException(const String* message) : RuntimeException(message)
			{
			}
			inline ~IllegalStateException()
			{
			}
		};
		typedef CSmartPtr<IllegalStateException>		IllegalStateExceptionPtr;
	}
}

#endif

#endif
