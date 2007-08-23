
#ifndef _CLASS_GOD_LANG_DOUBLE_H
#define _CLASS_GOD_LANG_DOUBLE_H

#ifdef __cplusplus

#include "lang/String.h"
#include "lang/Number.h"
#include "lang/NumberFormatException.h"
using namespace goddk::lang;

namespace goddk {
	namespace lang {
		/*!\ingroup CXX_LANG_m
		 */
		class  Double : public goddk::lang::Number, public virtual goddk::lang::Comparable<Double>
		{
		private:
			jdouble _val;

		public:
			static const jdouble MIN_VALUE;
			static const jdouble MAX_VALUE;

			static String toHexString(jdouble l) throw ();
			static String toOctalString(jdouble l) throw ();
			static String toString(jdouble l) throw ();

			static jdouble parseDouble(const String& s) throw (NumberFormatExceptionPtr);

		public:
			Double(jdouble value) throw ();
			Double(const String& s) throw (NumberFormatExceptionPtr);
			virtual ~Double() {}

			virtual bool instanceof(const char* class_name)const throw();
			virtual bool equals(const ObjectImpl* obj) const throw ();
			virtual jint hashCode() const throw ();
			virtual jbyte byteValue() const throw ();
			virtual jshort shortValue() const throw ();
			virtual jint intValue() const throw ();
			virtual jlong longValue() const throw ();
			virtual jint compareTo(const Double& anotherDouble) const throw ();
			virtual string toString() const throw ();
			virtual jfloat floatValue() const throw ();
			virtual jdouble doubleValue() const throw ();

			static  Double* valueOf(jdouble value)  throw ();
		};
		typedef CSmartPtr<Double>		DoublePtr;
	}
}

#endif

#endif
