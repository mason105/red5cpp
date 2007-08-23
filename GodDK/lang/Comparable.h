

#ifndef _INTERFACE_GOD_LANG_COMPARABLE_H
#define _INTERFACE_GOD_LANG_COMPARABLE_H

#include "gcommon.h"

#ifdef __cplusplus

namespace goddk {
	namespace lang {
		template<typename T> class Comparable
		{
		public:
			virtual ~Comparable() {}

			virtual jint compareTo(const T&) const throw () = 0;
		};
	}
}

#endif

#endif
