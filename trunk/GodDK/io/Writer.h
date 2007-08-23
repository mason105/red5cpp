
#ifndef _ABSTRACT_CLASS_GOD_IO_WRITER_H
#define _ABSTRACT_CLASS_GOD_IO_WRITER_H

#ifdef __cplusplus

#include "lang/Appendable.h"
#include "lang/String.h"
#include "io/Closeable.h"
#include "io/Flushable.h"
using namespace goddk::lang;
using namespace goddk::io;

namespace goddk {
	namespace io {
		/*!\ingroup CXX_IO_m
		 */
		class  Writer : public Object, public virtual Closeable, public virtual Flushable, public virtual Appendable
		{
		protected:
			Object* lock;

			Writer();
			Writer(Object& lock);

		public:
			virtual Writer& append(jchar c) throw (IOExceptionPtr);
			virtual Writer& append(const CharSequence& cseq) throw (IOExceptionPtr);
			bool instanceof(const char* class_name)const throw()
			{
				if(strcmp("Writer", class_name)== 0)
					return true;
				else
					return __super::instanceof(class_name);
			}
			virtual void write(const array<jchar>& cbuf) throw (IOExceptionPtr);
			virtual void write(const jchar* cbuf, jint off, jint len) throw (IOExceptionPtr) = 0;
			virtual void write(jint c) throw (IOExceptionPtr);
			virtual void write(const String& str) throw (IOExceptionPtr);
			virtual void write(const String& str, jint off, jint len) throw (IOExceptionPtr);
		};
		typedef CSmartPtr<Writer>		WriterPtr;
	}
}

#endif

#endif
