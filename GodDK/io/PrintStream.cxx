

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "io/PrintStream.h"
#include "lang/String.h"
using goddk::lang::String;
#include "lang/IllegalArgumentException.h"
using goddk::lang::IllegalArgumentException;

#define MAX_BYTES_PER_CHARACTER	8

using namespace goddk::io;

PrintStream::PrintStream(OutputStream& out, bool autoflush, const char* encoding) : FilterOutputStream(out)
{
	UErrorCode status = U_ZERO_ERROR;

	_loc = ucnv_open(encoding, &status);
	if (U_FAILURE(status))
		THROWEXCEPTIONPTR1(IllegalArgumentException,"invalid encoding");

	_closed = false;
	_error = false;
	_flush = autoflush;
}

PrintStream::~PrintStream()
{
	ucnv_close(_loc);
}

void PrintStream::close() throw ()
{
	try
	{
		out.close();
		_closed = true;
	}
	catch (IOException&)
	{
		_error = true;
	}
}

void PrintStream::flush() throw ()
{
	if (!_closed)
	{
		try
		{
			out.flush();
		}
		catch (IOException&)
		{
			_error = true;
		}
	}
}

void PrintStream::write(byte b) throw ()
{
	if (!_closed)
	{
		try
		{
			out.write(b);
		}
		catch (IOException&)
		{
			_error = true;
		}
	}
}

void PrintStream::write(const byte* data, size_t offset, size_t length) throw ()
{
	if (!_closed)
	{
		try
		{
			out.write(data, offset, length);
		}
		catch (IOException&)
		{
			_error = true;
		}
	}
}

void PrintStream::print(const UChar* str, size_t length) throw ()
{
	if (!_closed)
	{
		try
		{
			UErrorCode status = U_ZERO_ERROR;

			// pre-flighting
			size_t need = ucnv_fromUChars(_loc, 0, 0, str, length, &status);
			if (U_FAILURE(status))
				if (status != U_BUFFER_OVERFLOW_ERROR)
					THROWEXCEPTIONPTR(IOException);

			byte* buffer = new byte[need];

			status = U_ZERO_ERROR;

			try
			{
				ucnv_fromUChars(_loc, (char*) buffer, need, str, length, &status);
				if (status != U_STRING_NOT_TERMINATED_WARNING)
					THROWEXCEPTIONPTR(IOException);

				out.write(buffer, 0, need);

				if (_flush)
				{
					for (size_t i = 0; i < length; i++)
						if (str[i] == 0xA)
							out.flush();
				}

				delete[] buffer;
			}
			catch (IOException&)
			{
				delete[] buffer;
				throw;
			}
		}
		catch (IOException&)
		{
			_error = true;
		}
	}
}

void PrintStream::print(bool b) throw ()
{
	static const String* STR_TRUE = 0;
	static const String* STR_FALSE = 0;

	if (!_closed)
	{
		if (b)
		{
			if (!STR_FALSE)
				STR_FALSE = new String("true");

			print(*STR_TRUE);
		}
		else
		{
			if (!STR_FALSE)
				STR_FALSE = new String("false");

			print(*STR_FALSE);
		}
	}
}

void PrintStream::print(jchar ch) throw ()
{
	if (!_closed)
	{
		char buffer[MAX_BYTES_PER_CHARACTER];

		try	
		{
			UErrorCode status = U_ZERO_ERROR;

			// do conversion of one character
			size_t used = ucnv_fromUChars(_loc, buffer, 8, &ch, 1, &status);
			if (U_FAILURE(status))
				THROWEXCEPTIONPTR1(IOException,"failure in ucnv_fromUChars");

			out.write((const byte*) buffer, 0, used);

			// check if we need to flush
			if (_flush && ch == 0xA)
				out.flush();
		}
		catch (IOException&)
		{
			_error = true;
		}
	}
}

void PrintStream::print(jshort x) throw ()
{
	if (!_closed)
	{
		char tmp[7];
		int rc;

		#if SIZEOF_int == 4
		rc = sprintf(tmp, "%hd", x);
		#else
		rc = sprintf(tmp, "%d", x);	
		#endif

		if (rc < 0)
			write((const byte*) tmp, 0, (size_t) rc);
	}
}

void PrintStream::print(jint x) throw ()
{
	if (!_closed)
	{
		char tmp[11];
		int rc;

		#if SIZEOF_INT == 4
		rc = sprintf(tmp, "%d", x);
		#else
		rc = sprintf(tmp, "%ld", x);
		#endif

		if (rc > 0)
			write((const byte*) tmp, 0, (size_t) rc);
	}
}

void PrintStream::print(jlong x) throw ()
{
	if (!_closed)
	{
		char tmp[21];
		int rc;

		#if WIN32
		rc = sprintf(tmp, "%I64d", x);
		#elif SIZEOF_LONG == 8
		rc = sprintf(tmp, "%ld", x);
		#elif HAVE_LONG_LONG
		rc = sprintf(tmp, "%lld", x);
		#else
		# error
		#endif

		if (rc > 0)
			write((const byte*) tmp, 0, (size_t) rc);
	}
}

void PrintStream::print(const array<jchar>& chars) throw ()
{
	print(chars.data(), chars.size());
}

void PrintStream::print(const String& str) throw ()
{
	const array<jchar>& tmp = str.toCharArray();

	print(tmp.data(), tmp.size());
}

void PrintStream::println() throw ()
{
	if (!_closed)
	{
		#if WIN32
		print((jchar) 0xD);
		print((jchar) 0xA);
		#else
		print((jchar) 0xA);
		#endif
	}
}

void PrintStream::println(bool b) throw ()
{
	if (!_closed)
	{
		print(b);
		println();
	}
}

void PrintStream::println(jshort x) throw ()
{
	if (!_closed)
	{
		print(x);
		println();
	}
}

void PrintStream::println(jint x) throw ()
{
	if (!_closed)
	{
		print(x);
		println();
	}
}

void PrintStream::println(jlong x) throw ()
{
	if (!_closed)
	{
		print(x);
		println();
	}
}

void PrintStream::println(const array<jchar>& chars) throw ()
{
	if (!_closed)
	{
		print(chars);
		println();
	}
}

void PrintStream::println(const String& str) throw ()
{
	if (!_closed)
	{
		print(str);
		println();
	}
}
