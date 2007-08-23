

#ifndef _INTERFACE_GOD_LANG_CLONEABLE_H
#define _INTERFACE_GOD_LANG_CLONEABLE_H

#ifdef __cplusplus

#include "lang/Object.h"
#include "lang/CloneNotSupportedException.h"
using namespace goddk::lang;

namespace goddk {
	namespace lang {
		class  Cloneable:
			public virtual Object
		{
		public:
			virtual ~Cloneable() {}

			virtual Object* clone() const throw (CloneNotSupportedExceptionPtr) = 0;
		};
		typedef CSmartPtr<Cloneable>		CloneablePtr;
	}
}

#endif

#endif
