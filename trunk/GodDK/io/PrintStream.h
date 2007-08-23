
#ifndef _CLASS_GOD_IO_PRINTSTREAM_H
#define _CLASS_GOD_IO_PRINTSTREAM_H

#ifdef __cplusplus

#include "io/FilterOutputStream.h"
using namespace goddk::io;

#include <unicode/ucnv.h>

namespace goddk {
	namespace io {
		/*!\ingroup CXX_IO_m
		 */
		class  PrintStream : public FilterOutputStream
		{
		private:
			bool _closed;
			bool _error;
			bool _flush;
			UConverter* _loc;

			void print(const UChar*, size_t) throw ();

		protected:
			void setError() throw ();

		public:
			PrintStream(OutputStream& out, bool autoflush = false, const char* encoding = 0);
			virtual ~PrintStream();
			bool instanceof(const char* class_name)const throw()
			{
				if(strcmp("PrintStream", class_name)== 0)
					return true;
				else
					return __super::instanceof(class_name);
			}
			virtual void close() throw ();
			virtual void flush() throw ();
			virtual void write(byte b) throw ();
			virtual void write(const byte* data, size_t offset, size_t length) throw ();

			bool checkError() throw ();
			void print(bool) throw ();
			void print(jchar) throw ();
			void print(jint) throw ();
			void print(jlong) throw ();
			void print(jshort) throw ();
	//		void print(jfloat) throw ();
	//		void print(jdouble) throw ();
	//		void print(const char*) throw ();
			void print(const array<jchar>&) throw ();
			void print(const String&) throw ();
			void println() throw ();
			void println(bool) throw ();
			void println(jchar) throw ();
			void println(jint) throw ();
			void println(jlong) throw ();
			void println(jshort) throw ();
	//		void println(jfloat) throw ();
	//		void println(jdouble) throw ();
	//		void println(const char*) throw ();
			void println(const array<jchar>&) throw ();
			void println(const String&) throw ();
		};
		typedef CSmartPtr<PrintStream>		PrintStreamPtr;
	}
}

#endif

#endif
