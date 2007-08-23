

#ifndef _CLASS_GOD_IO_DATAOUTPUTSTREAM_H
#define _CLASS_GOD_IO_DATAOUTPUTSTREAM_H

#ifdef __cplusplus

#include "io/DataOutput.h"
#include "io/FilterOutputStream.h"
using namespace goddk::io;

#include <unicode/ucnv.h>

namespace goddk {
	namespace io {
		/*!\ingroup CXX_LANG_m
		 */
		class  DataOutputStream : public FilterOutputStream, public virtual DataOutput
		{
		private:
			UConverter* _utf;

		protected:
			jint written;

		public:
			DataOutputStream(OutputStream& out);
			virtual ~DataOutputStream();
			bool instanceof(const char* class_name)const throw()
			{
				if(strcmp("DataOutputStream", class_name)== 0)
					return true;
				else
					return __super::instanceof(class_name);
			}
			jint size() const throw ();

			virtual void write(byte b) throw (IOExceptionPtr);
			virtual void write(const byte* data, int offset, int length) throw (IOExceptionPtr);
			virtual void write(const bytearray& b) throw (IOExceptionPtr);
			virtual void writeBoolean(bool v) throw (IOExceptionPtr);
			virtual void writeByte(byte v) throw (IOExceptionPtr);
			virtual void writeChar(jint v) throw (IOExceptionPtr);
			virtual void writeChars(const String& s) throw (IOExceptionPtr);
			virtual void writeInt(jint v) throw (IOExceptionPtr);
			virtual void writeLong(jlong v) throw (IOExceptionPtr);
			virtual void writeShort(jshort v) throw (IOExceptionPtr);
			virtual void writeUTF(const String& str) throw (IOExceptionPtr);

		};
		typedef CSmartPtr<DataOutputStream>		DataOutputStreamPtr;
	}
}

#endif

#endif
