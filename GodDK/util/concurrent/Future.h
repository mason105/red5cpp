#pragma once
#include "TimeUnit.h"
using namespace goddk::util::concurrent;

namespace goddk {
	namespace util {
		namespace concurrent {

			template<class V>
			class Future:
				public virtual Object
			{
			public:
				bool instanceof(const char* class_name)const throw()
				{
					if(strcmp("Future", class_name)== 0)
						return true;
					else
						return __super::instanceof(class_name);
				}
				virtual boolean cancel(boolean mayInterruptIfRunning) = 0;
				virtual boolean isCancelled() = 0;
				virtual boolean isDone() = 0;
				virtual V* get() throw () = 0;
				virtual V* get(long timeout, TimeUnitPtr unit)throw () = 0;
			};

		}
	}
}