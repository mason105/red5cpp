

#ifndef _CLASS_GOD_LANG_ARITHMETICEXCEPTION_H
#define _CLASS_GOD_LANG_ARITHMETICEXCEPTION_H

#ifdef __cplusplus

#include "lang/RuntimeException.h"
using namespace goddk::lang;

namespace goddk {
	namespace lang {
		/* \ingroup CXX_LANG_m
		 */
		class ArithmeticException : public virtual  RuntimeException
		{
		public:
			inline ArithmeticException()
			{
			}
			inline ArithmeticException(const char* message) : RuntimeException(message)
			{
			}
			inline ArithmeticException(const String* message) : RuntimeException(message)
			{
			}
			inline ~ArithmeticException()
			{
			}
		

		};
		typedef CSmartPtr<ArithmeticException>		ArithmeticExceptionPtr;
	}
}

#endif

#endif
