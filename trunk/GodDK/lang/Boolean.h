
#ifndef _CLASS_GOD_LANG_BOOLEAN_H
#define _CLASS_GOD_LANG_BOOLEAN_H

#ifdef __cplusplus

#include "lang/String.h"
#include "lang/Number.h"
#include "lang/NumberFormatException.h"
using namespace goddk::lang;

namespace goddk {
	namespace lang {
		/*!\ingroup CXX_LANG_m
		 */
		class  Boolean : public goddk::lang::Number, public virtual goddk::lang::Comparable<Boolean>
		{
		private:
			jbyte _val;

		public:
			static  Boolean VALUE_TRUE;
			static  Boolean VALUE_FALSE;

			static String toHexString(jbyte l) throw ();
			static String toOctalString(jbyte l) throw ();
			static String toString(jbyte l) throw ();

			static jbyte parseBoolean(const String& s) throw (NumberFormatExceptionPtr);

		public:
			Boolean(jbyte value) throw ();
			Boolean(const String& s) throw (NumberFormatExceptionPtr);
			virtual ~Boolean() {}
			virtual void setValue(jbyte value)
			{
				_val= value;
			}

			virtual bool instanceof(const char* class_name)const throw();
			virtual bool equals(const ObjectImpl* obj) const throw ();
			virtual jint hashCode() const throw ();
			virtual jbyte byteValue() const throw ();
			virtual jshort shortValue() const throw ();
			virtual jint intValue() const throw ();
			virtual jlong longValue() const throw ();
			virtual jint compareTo(const Boolean& anotherBoolean) const throw ();
			virtual string toString() const throw ();
			virtual jfloat floatValue() const throw ();
			virtual jdouble doubleValue() const throw ();

			static  Boolean* valueOf(jbyte value)  throw ();
		};
		typedef CSmartPtr<Boolean>		BooleanPtr;
	}
}

#endif

#endif
