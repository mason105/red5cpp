
#ifndef _CLASS_GOD_LANG_CHARACTER_H
#define _CLASS_GOD_LANG_CHARACTER_H

#ifdef __cplusplus

#include "lang/String.h"
using namespace goddk::lang;

namespace goddk {
	namespace lang {
		/*!\ingroup CXX_LANG_m
		 */
		class  Character : public goddk::lang::Object, public virtual goddk::lang::Comparable<Character>
		{
		private:
			jchar _val;

		public:
			static const jchar MIN_VALUE;
			static const jchar MAX_VALUE;

			static const jchar MIN_HIGH_SURROGATE;
			static const jchar MAX_HIGH_SURROGATE;
			static const jchar MIN_LOW_SURROGATE;
			static const jchar MAX_LOW_SURROGATE;
			static const jchar MIN_SURROGATE;
			static const jchar MAX_SURROGATE;

			static const jint MIN_SUPPLEMENTARY_CODE_POINT;
			static const jint MIN_CODE_POINT;
			static const jint MAX_CODE_POINT;

			static const jint MIN_RADIX;
			static const jint MAX_RADIX;

			static String toString(jchar c) throw ();

			static bool isHighSurrogate(jchar ch) throw ();
			static bool isLowSurrogate(jchar ch) throw ();

		public:
			Character(jchar value) throw ();
			virtual ~Character() {}

			bool instanceof(const char* class_name)const throw()
			{
				if(strcmp("Character", class_name)== 0)
					return true;
				else
					return __super::instanceof(class_name);
			}
			virtual jint hashCode() const throw ();
			virtual jint compareTo(const Character& anotherCharacter) const throw ();
			virtual string toString() const throw ();
		};
		typedef CSmartPtr<Character>		CharacterPtr;
	}
}

#endif

#endif
