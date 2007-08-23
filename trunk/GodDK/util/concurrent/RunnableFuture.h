#pragma once
#include "future.h"
using namespace goddk::util::concurrent;
namespace goddk {
	namespace util {
		namespace concurrent {
			template<class V>
			class RunnableFuture:
				public virtual Runnable,
				public virtual Future<V>
			{
			public:

				bool instanceof(const char* class_name)const throw()
				{
					if(strcmp("RunnableFuture", class_name)== 0)
						return true;
					else if( Runnable::instanceof(class_name))
						return true;
					else
						return Future<V>::instanceof(class_name);
				}
				virtual void run() = 0;
			};
		}
	}
}