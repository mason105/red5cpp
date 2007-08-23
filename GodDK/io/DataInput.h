

#ifndef _INTERFACE_GOD_IO_DATAINPUT_H
#define _INTERFACE_GOD_IO_DATAINPUT_H

#ifdef __cplusplus

#include "lang/String.h"
#include "io/IOException.h"
using namespace goddk::lang;
using namespace goddk::io;
namespace goddk {
	namespace io {
		/*!\ingroup CXX_IO_m
		 */
		class  DataInput
		{
		public:
			virtual ~DataInput() {}

			virtual bool readBoolean() throw (IOExceptionPtr) = 0;
			virtual jbyte readByte() throw (IOExceptionPtr) = 0;
			virtual jchar readChar() throw (IOExceptionPtr) = 0;
			virtual void readFully(byte* data, jint offset, jint length) = 0;
			virtual void readFully(bytearray& b) = 0;
			virtual jint readInt() throw (IOExceptionPtr) = 0;
			virtual String readLine() throw (IOExceptionPtr) = 0;
			virtual jlong readLong() throw (IOExceptionPtr) = 0;
			virtual jshort readShort() throw (IOExceptionPtr) = 0;
			virtual jint readUnsignedByte() throw (IOExceptionPtr) = 0;
			virtual jint readUnsignedShort() throw (IOExceptionPtr) = 0;
			virtual String readUTF() throw (IOExceptionPtr) = 0;
			virtual jint skipBytes(jint n) throw (IOExceptionPtr) = 0;
			
		};
	}
}

#endif

#endif
