

#ifndef _CLASS_BEE_UTIL_CONCURRENT_LOCKS_REENTRANTLOCK_H
#define _CLASS_BEE_UTIL_CONCURRENT_LOCKS_REENTRANTLOCK_H

#ifdef __cplusplus

#include "lang/Object.h"
#include "util/concurrent/locks/Condition.h"
#include "util/concurrent/locks/Lock.h"
using namespace goddk::lang;
using namespace goddk::util::concurrent::locks;

namespace goddk {
	namespace util {
		namespace concurrent {
			namespace locks {
				
				class  ReentrantLock : public virtual Object, public virtual Lock
				{
				private:
					class  Cond : public virtual Object, public virtual Condition
					{
					private:
						Object* lock;

					public:
						Cond(Object*);
						virtual ~Cond() {}

						virtual void await() throw (InterruptedExceptionPtr);
						virtual void awaitUninterruptibly();
						virtual void signal();
						virtual void signalAll();
					};

					bool _fair;

				public:
					ReentrantLock(bool fair = false);
					virtual ~ReentrantLock() {}
					bool instanceof(const char* class_name)const throw()
					{
						if(strcmp("ReentrantLock", class_name)== 0)
							return true;
						else
							return Lock::instanceof(class_name);
					}
					virtual void lock();
					virtual void lockInterruptibly() throw (InterruptedExceptionPtr);
					virtual Condition* newCondition();
					virtual bool tryLock();
					virtual void unlock();
				};
				typedef CSmartPtr<ReentrantLock>  ReentrantLockPtr;
			}
		}
	}
}

#endif

#endif
