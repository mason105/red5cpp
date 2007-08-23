

#ifndef _INTERFACE_GOD_UTIL_ITERATOR_H
#define _INTERFACE_GOD_UTIL_ITERATOR_H

#ifdef __cplusplus

#include "util/NoSuchElementException.h"
using namespace goddk::util;

namespace goddk {
	namespace util {
		/*!\ingroup CXX_UTIL_m
		 */
		template<class E> class Iterator:
		public virtual Object
		{
		public:
			virtual ~Iterator() {}

			virtual bool hasNext() throw () = 0;
			virtual E* next() throw (NoSuchElementExceptionPtr) = 0;
			virtual void remove() = 0;
		};
	}
}

#endif

#endif
