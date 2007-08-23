
#ifndef _ABSTRACT_CLASS_GOD_IO_INPUTSTREAM_H
#define _ABSTRACT_CLASS_GOD_IO_INPUTSTREAM_H

#ifdef __cplusplus

#include "array.h"
#include "io/IOException.h"
#include "lang/Object.h"
using namespace goddk::lang;
using namespace goddk::io;

namespace goddk {
	namespace io {
		/*!\ingroup CXX_IO_m
		 */
		class  InputStream : public Object
		{
		public:
			virtual ~InputStream() {};
			bool instanceof(const char* class_name)const throw()
			{
				if(strcmp("InputStream", class_name)== 0)
					return true;
				else
					return __super::instanceof(class_name);
			}
			virtual jint available() throw (IOExceptionPtr);
			virtual void close() throw (IOExceptionPtr);
			virtual void mark(jint readlimit) throw ();
			virtual bool markSupported() throw ();
			virtual jint read() throw (IOExceptionPtr) = 0;
			virtual jint read(byte* data, jint offset, jint length) throw (IOExceptionPtr);
			virtual jint read(bytearray& b) throw (IOExceptionPtr);
			virtual void reset() throw (IOExceptionPtr);
			virtual jint skip(jint n) throw (IOExceptionPtr);
		};
		typedef CSmartPtr<InputStream>		InputStreamPtr;
	}
}

#endif

#endif
