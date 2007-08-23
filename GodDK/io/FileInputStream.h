
#ifndef _CLASS_GOD_IO_FILEINPUTSTREAM_H
#define _CLASS_GOD_IO_FILEINPUTSTREAM_H

#include <stdio.h>

#ifdef __cplusplus

#include "io/InputStream.h"
#include "io/File.h"
#include "nio/ByteBuffer.h"
using namespace goddk::io;
using namespace goddk::nio;

namespace goddk {
	namespace io {
		/*!\ingroup CXX_IO_m
		 */
		class  FileInputStream : public InputStream
		{
		private:
			FILE* _f;
			File* _fobj;
			long _mark;

		public:
			FileInputStream(File* fob);
			virtual ~FileInputStream();
			bool instanceof(const char* class_name)const throw()
			{
				if(strcmp("FileInputStream", class_name)== 0)
					return true;
				else
					return __super::instanceof(class_name);
			}
			virtual jint available() throw (IOExceptionPtr);
			virtual void close() throw (IOExceptionPtr);
			virtual void mark(jint readlimit) throw ();
			virtual bool markSupported() throw ();
			virtual jint read() throw (IOExceptionPtr);
			virtual jint read(byte* data, jint offset, jint length) throw (IOExceptionPtr);
			virtual jint read(bytearray&) throw (IOExceptionPtr);
			virtual jint read(ByteBuffer* buf) throw (IOExceptionPtr);
			virtual void reset() throw (IOExceptionPtr);
			virtual jint skip(jint n) throw (IOExceptionPtr);

			__int64 position();
			__int64 position(__int64 pos);
			__int64 size();
			virtual FileInputStream* getChannel(){
				return this;
			}
		};
		typedef CSmartPtr<FileInputStream>		FileInputStreamPtr;
	}
}

#endif

#endif
