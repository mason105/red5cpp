

#ifndef _INTERFACE_BEE_UTIL_CONCURRENT_LOCKS_CONDITION_H
#define _INTERFACE_BEE_UTIL_CONCURRENT_LOCKS_CONDITION_H

#ifdef __cplusplus

#include "lang/InterruptedException.h"
using namespace goddk::lang;

namespace goddk {
	namespace util {
		namespace concurrent {
			namespace locks {
			
				class  Condition:
					public virtual Object
				{
				public:
					virtual ~Condition() {}
					bool instanceof(const char* class_name)const throw()
					{
						if(strcmp("Condition", class_name)== 0)
							return true;
						else
							return Object::instanceof(class_name);
					}
					virtual void await() throw (InterruptedExceptionPtr) = 0;
					virtual void awaitUninterruptibly() = 0;
					virtual void signal() = 0;
					virtual void signalAll() = 0;
				};

				typedef CSmartPtr<Condition>  ConditionPtr;
			}
		}
	}
}

#endif

#endif
