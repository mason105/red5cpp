
#ifndef _INTERFACE_GOD_UTIL_SET_H
#define _INTERFACE_GOD_UTIL_SET_H

#ifdef __cplusplus

#include "util/Collection.h"
using namespace goddk::util;

namespace goddk {
	namespace util {
		/*!\ingroup CXX_UTIL_m
		 */
		template<class E> class Set : public virtual Collection<E>
		{
		};
	}
}

#endif

#endif
