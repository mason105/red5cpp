

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "io/InputStream.h"
#include "lang/String.h"
using goddk::lang::String;
#include "lang/NullPointerException.h"
using goddk::lang::NullPointerException;

using namespace goddk::io;

jint InputStream::available() throw (IOExceptionPtr)
{
	return 0;
}

void InputStream::close() throw (IOExceptionPtr)
{
}

void InputStream::mark(jint readlimit) throw ()
{
}

bool InputStream::markSupported() throw ()
{
	return false;
}

jint InputStream::read(bytearray& b) throw (IOExceptionPtr)
{
	return read(b.data(), 0, b.size());
}

jint InputStream::read(byte* data, jint offset, jint length) throw (IOExceptionPtr)
{
	if (!data)
		THROWEXCEPTIONPTR(NullPointerException)

	jint b = read();
	if (b < 0)
		return -1;

	data[offset] = (byte) b;

	jint i = 1;
	try
	{
		while (i < length)
		{
			b = read();
			if (b < 0)
				break;
			data[offset+i++] = (byte) b;
		}
	}
	catch (IOException&)
	{
		// ignore
	}
	return i;
}

jint InputStream::skip(jint n) throw (IOExceptionPtr)
{
	jint remaining = n;

	byte skip[2048];

	while (remaining > 0)
	{
		jint rc = read(skip, 0, remaining > 2048 ? 2048 : remaining);
		if (rc < 0)
			break;
		remaining -= rc;
	}

	return n - remaining;
}

void InputStream::reset() throw (IOExceptionPtr)
{
	THROWEXCEPTIONPTR1(IOException,"reset not supported");
}
