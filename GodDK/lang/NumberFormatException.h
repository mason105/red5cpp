

#ifndef _CLASS_GOD_LANG_NUMBERFORMATEXCEPTION_H
#define _CLASS_GOD_LANG_NUMBERFORMATEXCEPTION_H

#ifdef __cplusplus

#include "lang/IllegalArgumentException.h"
using namespace goddk::lang;

namespace goddk {
	namespace lang {
		/*!\brief Thrown to indicate that the conversion from a String to a
		 *        numeric value due to an inappropriate format.
		 * \ingroup CXX_LANG_m
		 */
		class NumberFormatException : public  virtual IllegalArgumentException
		{
		public:
			inline NumberFormatException()
			{
			}
			inline NumberFormatException(const char* message) : IllegalArgumentException(message)
			{
			}
			inline NumberFormatException(const String* message) : IllegalArgumentException(message)
			{
			}
			inline ~NumberFormatException()
			{
			}
		};
		typedef CSmartPtr<NumberFormatException>		NumberFormatExceptionPtr;
	}
}

#endif

#endif
