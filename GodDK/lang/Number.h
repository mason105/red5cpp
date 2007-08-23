

#ifndef _ABSTRACT_CLASS_GOD_LANG_NUMBER_H
#define _ABSTRACT_CLASS_GOD_LANG_NUMBER_H

#ifdef __cplusplus

#include "lang/Object.h"
using namespace goddk::lang;

namespace goddk {
	namespace lang {
		/*!\ingroup CXX_LANG_m
		 */
		class  Number : public goddk::lang::Object
		{
		public:
			virtual ~Number() {}

			bool instanceof(const char* class_name)const throw()
			{
				if(strcmp("Number", class_name)== 0)
					return true;
				else
					return __super::instanceof(class_name);
			}
			virtual jbyte byteValue() const throw () = 0;
			virtual jint intValue() const throw () = 0;
			virtual jlong longValue() const throw () = 0;
			virtual jshort shortValue() const throw () = 0;
			virtual jfloat floatValue() const throw () = 0;
			virtual jdouble doubleValue() const throw () = 0;
		};
		typedef CSmartPtr<Number>		NumberPtr;
	}
}

#endif

#endif
