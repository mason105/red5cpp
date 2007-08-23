
#ifndef _CLASS_GOD_LANG_ERROR_H
#define _CLASS_GOD_LANG_ERROR_H

#ifdef __cplusplus

#include "lang/Throwable.h"
using namespace goddk::lang;

namespace goddk {
	namespace lang {
		/*!\brief This subclass of Throwable is used to indicate a serious
		 *        problem, which should not be caught by the application.
		 * \ingroup CXX_LANG_m
		 */
		class Error : public Throwable
		{
		public:
			inline Error()
			{
			}
			inline Error(const char* message) : Throwable(message)
			{
			}
			inline Error(const String* message) : Throwable(message)
			{
			}
			inline ~Error()
			{
			}

		};
		typedef CSmartPtr<Error>		ErrorPtr;
	}
}

#endif

#endif
