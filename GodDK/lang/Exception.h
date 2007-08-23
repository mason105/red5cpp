

#ifndef _CLASS_GOD_LANG_EXCEPTION_H
#define _CLASS_GOD_LANG_EXCEPTION_H

#ifdef __cplusplus

#include "lang/Throwable.h"
using namespace goddk::lang;

namespace goddk {
	namespace lang {
		/*!\brief This subclass of Throwable is used to indicate a problem
		 *        which the application may want to catch.
		 * \ingroup CXX_LANG_m
		 */
		class Exception : public virtual Throwable
		{
		public:
			inline Exception()
			{
			}
			inline Exception(const char* message) : Throwable(message)
			{
			}
			inline Exception(const String* message) : Throwable(message)
			{
			}
			inline Exception(const Throwable* cause) : Throwable(cause)
			{
			}
			inline ~Exception()
			{
			}

		};
		typedef CSmartPtr<Exception>		ExceptionPtr;
	}
}

#endif

#endif
