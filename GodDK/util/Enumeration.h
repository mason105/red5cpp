
#ifndef _INTERFACE_GOD_UTIL_ENUMERATION_H
#define _INTERFACE_GOD_UTIL_ENUMERATION_H

#ifdef __cplusplus

#include "util/NoSuchElementException.h"
using namespace goddk::util;

namespace goddk {
	namespace util {
		/*!\ingroup CXX_UTIL_m
		 */
		template<class E> class Enumeration:
		public virtual Object
		{
		public:
			virtual ~Enumeration() {}

			virtual bool hasMoreElements() throw () = 0;
			virtual E* nextElement() throw (NoSuchElementExceptionPtr) = 0;
		};
	}
}

#endif

#endif
