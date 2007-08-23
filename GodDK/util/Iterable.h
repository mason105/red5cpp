

#ifndef _INTERFACE_GOD_UTIL_ITERABLE_H
#define _INTERFACE_GOD_UTIL_ITERABLE_H

#ifdef __cplusplus

#include "util/Iterator.h"
using namespace goddk::util;

namespace goddk {
	namespace util {
		template<class E> class Iterable:
		public virtual Object
		{
		public:
			virtual ~Iterable() {}

			virtual Iterator<E>* iterator() = 0;
		};
	}
}

#endif

#endif
