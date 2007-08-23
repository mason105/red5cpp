
#ifndef _CLASS_GOD_LANG_OUTOFMEMORYERROR_H
#define _CLASS_GOD_LANG_OUTOFMEMORYERROR_H

#ifdef __cplusplus

#include "lang/Error.h"
using namespace goddk::lang;

namespace goddk {
	namespace lang {
		/*!\brief This class is used to indicate that the application has run
		 *        out of memory.
		 * \ingroup CXX_LANG_m
		 */
		class OutOfMemoryError : public virtual  Error
		{
		public:
			inline OutOfMemoryError()
			{
			}
			inline OutOfMemoryError(const char* message) : Error(message)
			{
			}
			inline OutOfMemoryError(const String* message) : Error(message)
			{
			}
			inline ~OutOfMemoryError()
			{
			}
		};
		typedef CSmartPtr<OutOfMemoryError>		OutOfMemoryErrorPtr;
	}
}

#endif

#endif
