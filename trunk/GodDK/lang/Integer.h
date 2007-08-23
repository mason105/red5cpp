

#ifndef _CLASS_GOD_LANG_INTEGER_H
#define _CLASS_GOD_LANG_INTEGER_H

#ifdef __cplusplus

#include "lang/String.h"
#include "lang/Number.h"
#include "lang/NumberFormatException.h"
using namespace goddk::lang;

namespace goddk {
	namespace lang {
		/*!\ingroup CXX_LANG_m
		 */
		class  Integer : public goddk::lang::Number, public virtual goddk::lang::Comparable<Integer>
		{
		private:
			jint _val;

		public:
			static const jint MIN_VALUE;
			static const jint MAX_VALUE;

			static String toHexString(jint l) throw ();
			static String toOctalString(jint l) throw ();
			static String toString(jint l) throw ();

			static jint parseInteger(const String& s) throw (NumberFormatExceptionPtr);

		public:
			Integer(jint value) throw ();
			Integer(const String& s) throw (NumberFormatExceptionPtr);
			virtual ~Integer() {}
			virtual bool instanceof(const char* class_name)const throw();
			virtual bool equals(const ObjectImpl* obj) const throw ();
			virtual jint hashCode() const throw ();
			virtual jbyte byteValue() const throw ();
			virtual jshort shortValue() const throw ();
			virtual jint intValue() const throw ();
			virtual jlong longValue() const throw ();
			virtual jint compareTo(const Integer& anotherInteger) const throw ();
			virtual string toString() const throw ();
			virtual jfloat floatValue() const throw ();
			virtual jdouble doubleValue() const throw ();

			static  Integer* valueOf(jint value)  throw ();
		};
		typedef CSmartPtr<Integer>		IntegerPtr;
	}
}

#endif

#endif
