

#ifndef _INTERFACE_GOD_LANG_CHARSEQUENCE_H
#define _INTERFACE_GOD_LANG_CHARSEQUENCE_H

#ifdef __cplusplus

#include "lang/IndexOutOfBoundsException.h"
using namespace goddk::lang;

namespace goddk {
	namespace lang {
		class  CharSequence
		{
		public:
			virtual ~CharSequence() {}

			virtual jchar charAt(jint index) const throw (IndexOutOfBoundsExceptionPtr) = 0;
			virtual jint length() const throw () = 0;
			virtual CharSequence* subSequence(jint beginIndex, jint endIndex) const throw (IndexOutOfBoundsExceptionPtr) = 0;
			virtual string toString() const throw () = 0;
		};
	}
}

#endif

#endif
