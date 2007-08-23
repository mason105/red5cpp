

#ifndef _CLASS_GOD_IO_DATAINPUTSTREAM_H
#define _CLASS_GOD_IO_DATAINPUTSTREAM_H

#ifdef __cplusplus

#include "io/DataInput.h"
#include "io/FilterInputStream.h"
using namespace goddk::io;

#include <unicode/ucnv.h>

namespace goddk {
	namespace io {
		/*!\ingroup CXX_IO_m
		 */
		class  DataInputStream : public FilterInputStream, public virtual DataInput
		{
		private:
			bool _del;
			InputStream* _pin;
			UConverter* _utf;
			UConverter* _loc;

		public:
			DataInputStream(InputStream& in);
			virtual ~DataInputStream();

			virtual bool readBoolean() throw (IOExceptionPtr);
			virtual jbyte readByte() throw (IOExceptionPtr);
			virtual jchar readChar() throw (IOExceptionPtr);
			virtual void readFully(byte* data, jint offset, jint length) throw (IOExceptionPtr);
			virtual void readFully(bytearray& b) throw (IOExceptionPtr);
			virtual jint readInt() throw (IOExceptionPtr);
			virtual String readLine() throw (IOExceptionPtr);
			virtual jlong readLong() throw (IOExceptionPtr);
			virtual jshort readShort() throw (IOExceptionPtr);
			virtual jint readUnsignedByte() throw (IOExceptionPtr);
			virtual jint readUnsignedShort() throw (IOExceptionPtr);
			virtual String readUTF() throw (IOExceptionPtr);
			virtual jint skipBytes(jint n) throw (IOExceptionPtr);

			bool instanceof(const char* class_name)const throw()
			{
				if(strcmp("DataInputStream", class_name)== 0)
					return true;
				else
					return __super::instanceof(class_name);
			}
		};
		typedef CSmartPtr<DataInputStream>		DataInputStreamPtr;
	}
}

#endif

#endif
