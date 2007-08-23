

#ifndef _CLASS_GOD_LANG_LONG_H
#define _CLASS_GOD_LANG_LONG_H

#ifdef __cplusplus

#include "lang/String.h"
#include "lang/Number.h"
#include "lang/NumberFormatException.h"
using namespace goddk::lang;

namespace goddk {
	namespace lang {
		/*!\ingroup CXX_LANG_m
		 */
		class  Long : public goddk::lang::Number, public virtual goddk::lang::Comparable<Long>
		{
		private:
			jlong _val;

		public:
			static const jlong MIN_VALUE;
			static const jlong MAX_VALUE;

			static String toHexString(jlong l) throw ();
			static String toOctalString(jlong l) throw ();
			static String toString(jlong l) throw ();

			static jlong parseLong(const String& s) throw (NumberFormatExceptionPtr);

		public:
			Long(jlong value) throw ();
			Long(const String& s) throw (NumberFormatExceptionPtr);
			virtual ~Long() {}

			bool instanceof(const char* class_name)const throw()
			{
				if(strcmp("Long", class_name)== 0)
					return true;
				else
					return __super::instanceof(class_name);
			}
			virtual bool equals(const ObjectImpl* obj) const throw ();
			virtual jbyte byteValue() const throw ();
			virtual jint compareTo(const Long& anotherLong) const throw ();
			virtual jint hashCode() const throw ();
			virtual jint intValue() const throw ();
			virtual jlong longValue() const throw ();
			virtual jshort shortValue() const throw ();
			virtual string toString() const throw ();
			virtual jfloat floatValue() const throw ();
			virtual jdouble doubleValue() const throw ();

			static  Long* valueOf(jlong value)  throw ();
	};
		typedef CSmartPtr<Long>		LongPtr;
	}
}

#endif

#endif
