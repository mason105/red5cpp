
#ifndef _CLASS_GOD_LANG_SHORT_H
#define _CLASS_GOD_LANG_SHORT_H

#ifdef __cplusplus

#include "lang/String.h"
#include "lang/Number.h"
#include "lang/NumberFormatException.h"
using namespace goddk::lang;

namespace goddk {
	namespace lang {
		/*!\ingroup CXX_LANG_m
		 */
		class  Short : public goddk::lang::Number, public virtual goddk::lang::Comparable<Short>
		{
		private:
			jshort _val;

		public:
			static const jint MIN_VALUE;
			static const jint MAX_VALUE;

			static String toHexString(jshort l) throw ();
			static String toOctalString(jshort l) throw ();
			static String toString(jshort l) throw ();

			static jshort parseShort(const String& s) throw (NumberFormatExceptionPtr);

		public:
			Short(jshort value) throw ();
			Short(const String& s) throw (NumberFormatExceptionPtr);
			virtual ~Short() {}
			virtual bool instanceof(const char* class_name)const throw();
			virtual bool equals(const ObjectImpl* obj) const throw ();
			virtual jint hashCode() const throw ();
			virtual jbyte byteValue() const throw ();
			virtual jshort shortValue() const throw ();
			virtual jint intValue() const throw ();
			virtual jlong longValue() const throw ();
			virtual jint compareTo(const Short& anotherShort) const throw ();
			virtual string toString() const throw ();
			virtual jfloat floatValue() const throw ();
			virtual jdouble doubleValue() const throw ();

			static  Short* valueOf(jshort value)  throw ();
		};
		typedef CSmartPtr<Short>		ShortPtr;
	}
}

#endif

#endif
