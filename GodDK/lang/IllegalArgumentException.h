
#ifndef _CLASS_GOD_LANG_ILLEGALARGUMENTEXCEPTION_H
#define _CLASS_GOD_LANG_ILLEGALARGUMENTEXCEPTION_H

#ifdef __cplusplus

#include "lang/RuntimeException.h"
using namespace goddk::lang;

namespace goddk {
	namespace lang {
		/*!\brief This class is used to indicate that a method was passed an
		 *        illegal or inappropriate argument.
		 * \ingroup CXX_LANG_m
		 */
		class IllegalArgumentException : public virtual RuntimeException
		{
		public:
			inline IllegalArgumentException()
			{
			}
			inline IllegalArgumentException(const char* message)
			{
			}
			inline IllegalArgumentException(const String* message)
			{
			}
			inline ~IllegalArgumentException()
			{
			}
			
		};
		typedef CSmartPtr<IllegalArgumentException>		IllegalArgumentExceptionPtr;
	}
}

#endif

#endif
