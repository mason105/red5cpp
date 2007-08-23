

#ifndef _CLASS_GOD_IO_FILEOUTPUTSTREAM_H
#define _CLASS_GOD_IO_FILEOUTPUTSTREAM_H

#ifdef __cplusplus

#include "io/OutputStream.h"
#include "io/File.h"
#include "nio/ByteBuffer.h"
using namespace goddk::io;

namespace goddk {
	namespace io {
		/*!\ingroup CXX_IO_m
		 */
		class  FileOutputStream : public OutputStream
		{
		private:
			int	  _fd;
			bool  _append;
		public:
			FileOutputStream(File* fobj, bool append = false);
			virtual ~FileOutputStream();
			bool instanceof(const char* class_name)const throw()
			{
				if(strcmp("FileOutputStream", class_name)== 0)
					return true;
				else
					return __super::instanceof(class_name);
			}
			virtual void close() throw (IOExceptionPtr);
			virtual void flush() throw (IOExceptionPtr);
			virtual void write(byte b) throw (IOExceptionPtr);
			virtual void write(const byte* data, int offset, int length) throw (IOExceptionPtr);
			virtual void write(const bytearray& b) throw (IOExceptionPtr);
			virtual jint write(ByteBuffer* buf) throw (IOExceptionPtr);
			__int64 position();
			__int64 position(__int64 pos);
			__int64 size();
			virtual FileOutputStream* getChannel(){
				return this;
			}
		};
		typedef CSmartPtr<FileOutputStream>		FileOutputStreamPtr;
	}
}

#endif

#endif
