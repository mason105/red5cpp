

#ifndef _CLASS_GOD_LANG_STRINGBUILDER_H
#define _CLASS_GOD_LANG_STRINGBUILDER_H

#ifdef __cplusplus

#include "lang/Appendable.h"
#include "lang/String.h"
using namespace goddk::lang;

namespace goddk {
	namespace lang {
		/*!\ingroup CXX_LANG_m
		 */
		class  StringBuilder : public goddk::lang::Object, public virtual goddk::lang::Appendable, public virtual goddk::lang::CharSequence
		{
			friend class String;

		private:
			array<jchar> _buffer;
			int _used;

		public:
			StringBuilder();
			StringBuilder(const char*);
			StringBuilder(const String&);
			virtual ~StringBuilder() {}

			virtual Appendable& append(jchar c);
			virtual Appendable& append(const CharSequence& cseq);

			StringBuilder& append(bool b);
			StringBuilder& append(char c);
			StringBuilder& append(jint i);
			StringBuilder& append(jlong l);
			StringBuilder& append(const char*);
			StringBuilder& append(const String& s);
			StringBuilder& append(const StringBuilder& s);
			StringBuilder& append(const Object* obj);

			StringBuilder& reverse();

			bool instanceof(const char* class_name)const throw()
			{
				if(strcmp("StringBuilder", class_name)== 0)
					return true;
				else
					return __super::instanceof(class_name);
			}
			virtual jchar charAt(jint index) const throw (IndexOutOfBoundsExceptionPtr);
			void ensureCapacity(jint minimum);
			virtual jint length() const throw ();
			virtual CharSequence* subSequence(jint beginIndex, jint endIndex) const throw (IndexOutOfBoundsExceptionPtr);
			virtual string toString() const throw ();
		};
		typedef CSmartPtr<StringBuilder>		StringBuilderPtr;
	}
}

#endif

#endif
