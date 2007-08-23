
#ifndef _CLASS_GOD_LANG_CLASSCASTEXCEPTION_H
#define _CLASS_GOD_LANG_CLASSCASTEXCEPTION_H

#ifdef __cplusplus

#include "lang/RuntimeException.h"
using namespace goddk::lang;

namespace goddk {
	namespace lang {
		/* \ingroup CXX_LANG_m
		 */
		class ClassCastException : public  virtual RuntimeException
		{
		public:
			inline ClassCastException()
			{
			}
			inline ClassCastException(const char* message) : RuntimeException(message)
			{
			}
			inline ClassCastException(const String* message) : RuntimeException(message)
			{
			}
			inline ~ClassCastException()
			{
			}
			
		};
		typedef CSmartPtr<ClassCastException>		ClassCastExceptionPtr;
	}
}

#endif

#endif
