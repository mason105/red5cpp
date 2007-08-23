

#ifndef _ABSTRACT_CLASS_GOD_IO_OUTPUTSTREAM_H
#define _ABSTRACT_CLASS_GOD_IO_OUTPUTSTREAM_H

#ifdef __cplusplus

#include "array.h"
#include "lang/Object.h"
#include "io/Closeable.h"
#include "io/Flushable.h"
using namespace goddk::lang;
using namespace goddk::io;

namespace goddk {
	namespace io {
		/*!\ingroup CXX_IO_m
		 */
		class  OutputStream : public Object, public virtual Closeable, public virtual Flushable
		{
		public:
			virtual ~OutputStream() {}
			bool instanceof(const char* class_name)const throw()
			{
				if(strcmp("OutputStream", class_name)== 0)
					return true;
				else
					return __super::instanceof(class_name);
			}
			virtual void close() throw (IOExceptionPtr);
			virtual void flush() throw (IOExceptionPtr);
			virtual void write(byte b) throw (IOExceptionPtr) = 0;
			virtual void write(const byte* data, int offset, int length) throw (IOExceptionPtr);
			virtual void write(const bytearray& b) throw (IOExceptionPtr);
		};
		typedef CSmartPtr<OutputStream>		OutputStreamPtr;
	}
}

#endif

#endif
