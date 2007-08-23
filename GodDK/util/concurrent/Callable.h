#pragma once
#include "lang/Exception.h"
using namespace goddk::lang;
namespace goddk {
	namespace util {
		namespace concurrent {
				template<class V>
				class Callable:
					public virtual Object
				{
				public:
					bool instanceof(const char* class_name)const throw()
					{
						if(strcmp("Callable", class_name)== 0)
							return true;
						else
							return __super::instanceof(class_name);
					}
					virtual V call() throw (Exception) = 0;
				};
		}
	}
}