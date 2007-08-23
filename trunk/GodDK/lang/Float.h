

#ifndef _CLASS_GOD_LANG_FLOAT_H
#define _CLASS_GOD_LANG_FLOAT_H

#ifdef __cplusplus

#include "lang/String.h"
#include "lang/Number.h"
#include "lang/NumberFormatException.h"
using namespace goddk::lang;

namespace goddk {
	namespace lang {
		/*!\ingroup CXX_LANG_m
		 */
		class  Float : public goddk::lang::Number, public virtual goddk::lang::Comparable<Float>
		{
		private:
			jfloat _val;

		public:
			static const jfloat MIN_VALUE;
			static const jfloat MAX_VALUE;

			static String toHexString(jfloat l) throw ();
			static String toOctalString(jfloat l) throw ();
			static String toString(jfloat l) throw ();

			static jfloat parseFloat(const String& s) throw (NumberFormatExceptionPtr);

		public:
			Float(jfloat value) throw ();
			Float(const String& s) throw (NumberFormatExceptionPtr);
			virtual ~Float() {}
			
			virtual bool instanceof(const char* class_name)const throw();
			virtual bool equals(const ObjectImpl* obj) const throw ();
			virtual jint hashCode() const throw ();
			virtual jbyte byteValue() const throw ();
			virtual jshort shortValue() const throw ();
			virtual jint intValue() const throw ();
			virtual jlong longValue() const throw ();
			virtual jint compareTo(const Float& anotherFloat) const throw ();
			virtual string toString() const throw ();
			virtual jfloat floatValue() const throw ();
			virtual jdouble doubleValue() const throw ();

			static  Float* valueOf(jfloat value)  throw ();
		};
		typedef CSmartPtr<Float>		FloatPtr;
	}
}

#endif

#endif
