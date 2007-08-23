
#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "io/OutputStream.h"
#include "lang/NullPointerException.h"
using goddk::lang::NullPointerException;

using namespace goddk::io;

void OutputStream::close() throw (IOExceptionPtr)
{
}

void OutputStream::flush() throw (IOExceptionPtr)
{
}

void OutputStream::write(const byte* data, int offset, int length) throw (IOExceptionPtr)
{
	if (length)
	{
		if (!data)
			THROWEXCEPTIONPTR(NullPointerException)

		for (int i = 0; i < length; i++)
			write(data[offset+i]);
	}
}

void OutputStream::write(const bytearray& b) throw (IOExceptionPtr)
{
	write(b.data(), 0, b.size());
}
