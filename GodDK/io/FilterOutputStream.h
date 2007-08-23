

#ifndef _CLASS_GOD_IO_FILTEROUTPUTSTREAM_H
#define _CLASS_GOD_IO_FILTEROUTPUTSTREAM_H

#ifdef __cplusplus

#include "io/OutputStream.h"
using namespace goddk::io;

namespace goddk {
	namespace io {
		/*!\ingroup CXX_IO_m
		 */
		class  FilterOutputStream : public OutputStream
		{
		protected:
			OutputStream& out;

		public:
			FilterOutputStream(OutputStream& out);
			virtual ~FilterOutputStream();
			bool instanceof(const char* class_name)const throw()
			{
				if(strcmp("FilterOutputStream", class_name)== 0)
					return true;
				else
					return __super::instanceof(class_name);
			}
			virtual void close() throw (IOExceptionPtr);
			virtual void flush() throw (IOExceptionPtr);
			virtual void write(byte b) throw (IOExceptionPtr);
			virtual void write(const byte* data, int offset, int length) throw (IOExceptionPtr);
			virtual void write(const bytearray& b) throw (IOExceptionPtr);
		};
		typedef CSmartPtr<FilterOutputStream>		FilterOutputStreamPtr;
	}
}

#endif

#endif
