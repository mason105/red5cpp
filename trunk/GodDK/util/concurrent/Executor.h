#pragma once
#include "lang/Runnable.h"
using namespace goddk::lang;

namespace goddk {
	namespace util {
		namespace concurrent {
			class Executor:
				public virtual Object
			{
			public:
				Executor(void);
				~Executor(void);

				virtual void execute(RunnablePtr command) = 0;
			};
			typedef CSmartPtr<Executor>  ExecutorPtr;
		}
	}
}