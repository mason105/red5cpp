
#ifndef _CLASS_GOD_LANG_NULLPOINTEREXCEPTION_H
#define _CLASS_GOD_LANG_NULLPOINTEREXCEPTION_H

#ifdef __cplusplus

#include "lang/RuntimeException.h"
using namespace goddk::lang;

namespace goddk {
	namespace lang {
		/*!\brief This class is used to indicate that an application has
		 *        found a null pointer where an object was required.
		 * \ingroup CXX_LANG_m
		 */
		class NullPointerException : public  virtual RuntimeException
		{
		public:
			inline NullPointerException()
			{
			}
			inline NullPointerException(const char* message) : RuntimeException(message)
			{
			}
			inline NullPointerException(const String* message) : RuntimeException(message)
			{
			}
			inline ~NullPointerException()
			{
			}
		};
		typedef CSmartPtr<NullPointerException>		NullPointerExceptionPtr;
	}
}

#endif

#endif
