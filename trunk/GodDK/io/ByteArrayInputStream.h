

#ifndef _CLASS_GOD_IO_BYTEARRAYINPUTSTREAM_H
#define _CLASS_GOD_IO_BYTEARRAYINPUTSTREAM_H

#ifdef __cplusplus

#include "io/InputStream.h"
using namespace goddk::io;

namespace goddk {
	namespace io {
		/*!\ingroup CXX_IO_m
		 */
		class  ByteArrayInputStream : public InputStream
		{
		protected:
			bytearray _buf;
			jint      _count;
			jint      _mark;
			jint      _pos;

		public:
			ByteArrayInputStream(const byte* data, jint offset, jint length);
			ByteArrayInputStream(const bytearray& b);
			virtual ~ByteArrayInputStream();

			virtual jint available() throw (IOExceptionPtr);
			virtual void close() throw (IOExceptionPtr);
			virtual void mark(jint readlimit) throw ();
			virtual bool markSupported() throw ();
			virtual jint read() throw (IOExceptionPtr);
			virtual jint read(byte* data, jint offset, jint length) throw (IOExceptionPtr);
			virtual jint read(bytearray& b) throw (IOExceptionPtr);
			virtual void reset() throw (IOExceptionPtr);
			virtual jint skip(jint n) throw (IOExceptionPtr);
			bool instanceof(const char* class_name)const throw()
			{
				if(strcmp("ByteArrayInputStream", class_name)== 0)
					return true;
				else
					return __super::instanceof(class_name);
			}
		};
		typedef CSmartPtr<ByteArrayInputStream>		ByteArrayInputStreamPtr;
	}
}

#endif

#endif
