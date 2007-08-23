

#ifndef _INTERFACE_BEE_UTIL_CONCURRENT_LOCKS_LOCK_H
#define _INTERFACE_BEE_UTIL_CONCURRENT_LOCKS_LOCK_H

#ifdef __cplusplus

#include "lang/InterruptedException.h"
#include "util/concurrent/locks/Condition.h"
using namespace goddk::lang;
using namespace goddk::util::concurrent::locks;

namespace goddk {
	namespace util {
		namespace concurrent {
			namespace locks {
				
				class  Lock:
					public virtual Object
				{
				public:
					virtual ~Lock() {}
					bool instanceof(const char* class_name)const throw()
					{
						if(strcmp("Lock", class_name)== 0)
							return true;
						else
							return Object::instanceof(class_name);
					}
					virtual void lock() = 0;
					virtual void lockInterruptibly() throw (InterruptedExceptionPtr) = 0;
					virtual Condition* newCondition() = 0;
					virtual bool tryLock() = 0;
					virtual void unlock() = 0;
				};
				typedef CSmartPtr<Lock>  LockPtr;
			}
		}
	}
}

#endif

#endif
