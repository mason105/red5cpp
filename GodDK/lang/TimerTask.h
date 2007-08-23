#pragma	  once
#include "lang/Runnable.h"
#include "lang/Object.h"
using namespace goddk::lang;

namespace goddk {
	namespace lang {
		class TimerTask:
			public virtual Runnable
			{
			public:

				static const int VIRGIN = 0;
				static const int SCHEDULED   = 1;
				static const int EXECUTED    = 2;
				static const int CANCELLED   = 3;

				TimerTask() {
					state = VIRGIN;
					period = 0;
					lock = new Object();
				}
				virtual ~TimerTask()
				{
					delete lock;
				}
				virtual void run() = 0;

				bool cancel() 
				{
					synchronized(lock) ;
					{
						bool result = (state == SCHEDULED);
						state = CANCELLED;
						return result;
					}
				}

			
				jlong scheduledExecutionTime() 
				{
					synchronized(lock);
					{
						return (period < 0 ? nextExecutionTime + period
							: nextExecutionTime - period);
					}
				}

			public:
				jlong nextExecutionTime;
				jlong period ;
				int	  state;
				Object* lock;
			};
		typedef CSmartPtr<TimerTask>		TimerTaskPtr;
	}
}
