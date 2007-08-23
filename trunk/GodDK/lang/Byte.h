

#ifndef _CLASS_GOD_LANG_BYTE_H
#define _CLASS_GOD_LANG_BYTE_H

#ifdef __cplusplus

#include "lang/String.h"
#include "lang/Number.h"
#include "lang/NumberFormatException.h"
using namespace goddk::lang;

namespace goddk {
	namespace lang {
		/*!\ingroup CXX_LANG_m
		 */
		class  Byte : public goddk::lang::Number, public virtual goddk::lang::Comparable<Byte>
		{
		private:
			jbyte _val;

		public:

			static String toHexString(jbyte l) throw ();
			static String toOctalString(jbyte l) throw ();
			static String toString(jbyte l) throw ();

			static jbyte parseByte(const String& s) throw (NumberFormatExceptionPtr);

		public:
			Byte(jbyte value) throw ();
			Byte(const String& s) throw (NumberFormatExceptionPtr);
			virtual ~Byte() {}

			virtual bool instanceof(const char* class_name)const throw();
			virtual bool equals(const ObjectImpl* obj) const throw ();
			virtual jint hashCode() const throw ();
			virtual jbyte byteValue() const throw ();
			virtual jshort shortValue() const throw ();
			virtual jint intValue() const throw ();
			virtual jlong longValue() const throw ();
			virtual jint compareTo(const Byte& anotherByte) const throw ();
			virtual string toString() const throw ();
			virtual jfloat floatValue() const throw ();
			virtual jdouble doubleValue() const throw ();

			static  Byte* valueOf(jbyte value)  throw ();
		};
		typedef CSmartPtr<Byte>		BytePtr;
	}
}

#endif

#endif
