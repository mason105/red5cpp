
#ifndef _CLASS_GOD_LANG_SYSTEM_H
#define _CLASS_GOD_LANG_SYSTEM_H

#include "gcommon.h"

#ifdef __cplusplus

#include "io/InputStream.h"
#include "io/PrintStream.h"
using namespace goddk::io;

namespace goddk {
	namespace lang {
		/*!\ingroup CXX_LANG_m
		 */
		class  System
		{
		public:
			static InputStream& in;
			static PrintStream& out;
			static PrintStream& err;
			static jlong currentTimeMillis();
		};
	}
}

#endif

#endif
