
#ifndef _INTERFACE_GOD_LANG_RUNNABLE_H
#define _INTERFACE_GOD_LANG_RUNNABLE_H

#ifdef __cplusplus
#include "lang/Object.h"
using namespace goddk::lang;

namespace goddk {
	namespace lang {
		class  Runnable:
			public virtual Object
		{
		public:
			Runnable() {}

			virtual void run() = 0;
		};
		typedef CSmartPtr<Runnable>		RunnablePtr;

	
	}
}

#endif

#endif
