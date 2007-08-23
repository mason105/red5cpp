
#ifndef _INTERFACE_GOD_UTIL_RANDOMACCESS_H
#define _INTERFACE_GOD_UTIL_RANDOMACCESS_H

#ifdef __cplusplus

#include "util/Iterator.h"
using namespace goddk::util;

namespace goddk {
	namespace util {
		class  RandomAccess:
			public virtual Object
		{
		};
		typedef CSmartPtr<RandomAccess>		RandomAccessPtr;
	}
}

#endif

#endif
