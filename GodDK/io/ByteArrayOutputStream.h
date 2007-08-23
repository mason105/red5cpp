
#ifndef _CLASS_GOD_IO_BYTEARRAYOUTPUTSTREAM_H
#define _CLASS_GOD_IO_BYTEARRAYOUTPUTSTREAM_H

#ifdef __cplusplus

#include "io/OutputStream.h"
using namespace goddk::io;

namespace goddk {
	namespace io {
		/*!\ingroup CXX_IO_m
		 */
		class  ByteArrayOutputStream : public OutputStream
		{
		protected:
			bytearray buf;
			int       count;

		public:
			ByteArrayOutputStream();
			ByteArrayOutputStream(int size);
			virtual ~ByteArrayOutputStream();

			void reset() throw ();
			int size() throw ();
			bytearray* toByteArray();
			void toByteArray(bytearray& b);
			void toByteArray(byte* data, int offset, int length);
			void writeTo(OutputStream& out) throw (IOExceptionPtr);

			virtual void close() throw (IOExceptionPtr);
			virtual void flush() throw (IOExceptionPtr);
			virtual void write(byte b) throw (IOExceptionPtr);
			virtual void write(const byte* data, int offset, int length) throw (IOExceptionPtr);
			virtual void write(const bytearray& b) throw (IOExceptionPtr);

			bool instanceof(const char* class_name)const throw()
			{
				if(strcmp("ByteArrayOutputStream", class_name)== 0)
					return true;
				else
					return __super::instanceof(class_name);
			}
		};
		typedef CSmartPtr<ByteArrayOutputStream>		ByteArrayOutputStreamPtr;
	}
}

#endif

#endif
