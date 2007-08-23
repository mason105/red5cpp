

#ifndef _CLASS_GOD_IO_FILTERINPUTSTREAM_H
#define _CLASS_GOD_IO_FILTERINPUTSTREAM_H

#ifdef __cplusplus

#include "io/InputStream.h"
using namespace goddk::io;

namespace goddk {
	namespace io {
		/*!\ingroup CXX_IO_m
		 */
		class  FilterInputStream : public InputStream
		{
		protected:
			InputStream& in;

		public:
			FilterInputStream(InputStream& in);
			virtual ~FilterInputStream();
			bool instanceof(const char* class_name)const throw()
			{
				if(strcmp("FilterInputStream", class_name)== 0)
					return true;
				else
					return __super::instanceof(class_name);
			}
			virtual jint available() throw (IOExceptionPtr);
			virtual void close() throw (IOExceptionPtr);
			virtual void mark(jint) throw ();
			virtual bool markSupported() throw ();
			virtual jint read() throw (IOExceptionPtr);
			virtual jint read(byte* data, jint offset, jint length) throw (IOExceptionPtr);
			virtual jint read(bytearray& b) throw (IOExceptionPtr);
			virtual void reset() throw (IOExceptionPtr);
			virtual jint skip(jint) throw (IOExceptionPtr);
		};
		typedef CSmartPtr<FilterInputStream>		FilterInputStreamPtr;
	}
}

#endif

#endif
