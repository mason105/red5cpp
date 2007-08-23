
#ifndef _CLASS_GOD_IO_PUSHBACKINPUTSTREAM_H
#define _CLASS_GOD_IO_PUSHBACKINPUTSTREAM_H

#ifdef __cplusplus

#include "io/FilterInputStream.h"
using namespace goddk::io;

namespace goddk {
	namespace io {
		/*!\ingroup CXX_IO_m
		 */
		class  PushbackInputStream : public FilterInputStream
		{
		private:
			bool _closed;

		protected:
			bytearray buf;
			jint pos;

		public:
			PushbackInputStream(InputStream& in, jint size = 1);
			virtual ~PushbackInputStream();
			bool instanceof(const char* class_name)const throw()
			{
				if(strcmp("PushbackInputStream", class_name)== 0)
					return true;
				else
					return __super::instanceof(class_name);
			}
			virtual jint available() throw (IOExceptionPtr);
			virtual void close() throw (IOExceptionPtr);
			virtual bool markSupported() throw ();
			virtual jint read() throw (IOExceptionPtr);
			virtual jint read(byte* data, jint offset, jint length) throw (IOExceptionPtr);
			virtual jint skip(jint n) throw (IOExceptionPtr);

			void unread(byte) throw (IOExceptionPtr);
			void unread(const byte* data, jint offset, jint length) throw (IOExceptionPtr);
			void unread(const bytearray& b) throw (IOExceptionPtr);
		};
		typedef CSmartPtr<PushbackInputStream>		PushbackInputStreamPtr;
	}
}

#endif

#endif
