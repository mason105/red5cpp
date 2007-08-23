
#ifndef _CLASS_GOD_LANG_STRINGBUFFER_H
#define _CLASS_GOD_LANG_STRINGBUFFER_H

#ifdef __cplusplus

#include "lang/Appendable.h"
#include "lang/String.h"
using namespace goddk::lang;

namespace goddk {
	namespace lang {
		/*!\ingroup CXX_LANG_m
		 */
		class  StringBuffer : public goddk::lang::Object, public virtual goddk::lang::Appendable, public virtual goddk::lang::CharSequence
		{
			friend class String;

		private:
			array<jchar> _buffer;
			jint _used;

			void core_ensureCapacity(int minimum);

		public:
			StringBuffer();
			StringBuffer(const char*);
			StringBuffer(const String&);
			virtual ~StringBuffer() {}

			virtual Appendable& append(jchar c);
			virtual Appendable& append(const CharSequence& cseq);

			StringBuffer& append(bool b);
			StringBuffer& append(jint i);
			StringBuffer& append(char c);
			StringBuffer& append(const char*);
			StringBuffer& append(const String& s);
			StringBuffer& append(const StringBuffer& s);
			StringBuffer& append(const Object* obj);

			bool instanceof(const char* class_name)const throw()
			{
				if(strcmp("StringBuffer", class_name)== 0)
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
		typedef CSmartPtr<StringBuffer>		StringBufferPtr;
	}
}

#endif

#endif
