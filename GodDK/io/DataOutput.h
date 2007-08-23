

#ifndef _INTERFACE_GOD_IO_DATAOUTPUT_H
#define _INTERFACE_GOD_IO_DATAOUTPUT_H

#ifdef __cplusplus

#include "lang/String.h"
#include "io/IOException.h"
using namespace goddk::lang;
using namespace goddk::io;

namespace goddk {
	namespace io {
		/*!\ingroup CXX_IO_m
		 */
		class  DataOutput
		{
		public:
			virtual ~DataOutput() {}

			virtual void write(const bytearray& b) throw (IOExceptionPtr) = 0;
			virtual void write(const byte* data, jint offset, jint length) throw (IOExceptionPtr) = 0;
			virtual void write(byte v) throw (IOExceptionPtr) = 0;
			virtual void writeBoolean(bool v) throw (IOExceptionPtr) = 0;
			virtual void writeByte(byte v) throw (IOExceptionPtr) = 0;
			virtual void writeChars(const String& s) throw (IOExceptionPtr) = 0;
			virtual void writeInt(jint v) throw (IOExceptionPtr) = 0;
			virtual void writeLong(jlong v) throw (IOExceptionPtr) = 0;
			virtual void writeShort(jshort v) throw (IOExceptionPtr) = 0;
			virtual void writeUTF(const String& str) throw (IOExceptionPtr) = 0;
		};
	}
}

#endif

#endif
