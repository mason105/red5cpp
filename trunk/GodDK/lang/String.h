
#ifndef _CLASS_GOD_LANG_STRING_H
#define _CLASS_GOD_LANG_STRING_H

#include "gcommon.h"

#ifdef __cplusplus

#include "lang/CharSequence.h"
#include "lang/Comparable.h"
#include "lang/Object.h"
#include "array.h"
using namespace goddk::lang;

#include <iostream>
#include <unicode/unistr.h>

namespace goddk {
	namespace lang {
		/*!\ingroup CXX_LANG_m
		 * \brief This class represents Unicode character strings.
		 *
		 */
		class  String : public goddk::lang::Object, public virtual goddk::lang::CharSequence, public virtual goddk::lang::Comparable<String>
		{
			friend class Character;
			friend class StringBuffer;
			friend class StringBuilder;

		private:
			array<jchar> _value;

			String(array<jchar>&);
			String(const array<jchar>&, const array<jchar>&);

		public:
			static String valueOf(bool b);
			static String valueOf(jchar c);
			static String valueOf(jint i);
			static String valueOf(jlong l);

		public:
			String();
			String(char);
			String(jchar);
			String(const char*);
			String(const jchar*, jint offset, jint length);
			String(const bytearray&);
			String(const array<jchar>&);
			String(const String& copy);
			String(const UnicodeString& copy);
			virtual ~String() {}

			String& operator=(const String& copy);

			bool instanceof(const char* class_name)const throw()
			{
				if(strcmp("String", class_name)== 0)
					return true;
				else
					return __super::instanceof(class_name);
			}
			jchar charAt(jint index) const throw ();
			virtual jint compareTo(const String& str) const throw ();
			jint compareToIgnoreCase(const String& str) const throw ();
			String concat(const String& str) const throw ();
			bool contains(const CharSequence& seq) const throw ();
			bool contentEquals(const CharSequence& seq) const throw ();
			bool endsWith(const String& suffix) const throw ();
			virtual bool equals(const ObjectImpl* obj) const throw ();
			bool equals(const String& str) const throw ();
			bool equalsIgnoreCase(const String& str) const throw ();
			virtual jint hashCode() const throw ();
			jint indexOf(jint ch, jint fromIndex = 0) const throw ();
			jint lastIndexOf(jint ch, jint fromIndex = 0) const throw ();
			jint indexOf(const String& str, jint fromIndex = 0) const throw ();
			virtual jint length() const throw ();
			bool startsWith(const String& prefix, jint offset = 0) const throw ();
			virtual CharSequence* subSequence(jint beginIndex, jint endIndex) const throw (IndexOutOfBoundsExceptionPtr);
			String substring(jint beginIndex) const throw (IndexOutOfBoundsExceptionPtr);
			String substring(jint beginIndex, jint endIndex) const throw (IndexOutOfBoundsExceptionPtr);
			String toLowerCase() const throw ();
			String toUpperCase() const throw ();
			const array<jchar>& toCharArray() const throw ();
			array<char>* toByteArray()  throw ();
			const char*	 ByteData() throw();
			virtual string toString() const throw ();
			UnicodeString toUnicodeString() const throw ();
			array<String*> split(jint ch);
			String trim();
		};
		typedef CSmartPtr<String>		StringPtr;

		
		goddk::lang::String operator+(const goddk::lang::String& s1, const goddk::lang::String& s2);

		
		bool operator<(const goddk::lang::String& s1, const goddk::lang::String& s2);

		
		std::ostream& operator<<(std::ostream& stream, const goddk::lang::String& str);
		
		std::ostream& operator<<(std::ostream& stream, const goddk::lang::String* str);
	}
}

#endif

#endif
