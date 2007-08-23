
#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "io/FilterOutputStream.h"

using namespace goddk::io;

FilterOutputStream::FilterOutputStream(OutputStream& out) : out(out)
{
}

FilterOutputStream::~FilterOutputStream()
{
}

void FilterOutputStream::close() throw (IOExceptionPtr)
{
	try
	{
		flush();
	}
	catch (IOException)
	{
		// ignore
	}
	out.close();
}

void FilterOutputStream::flush() throw (IOExceptionPtr)
{
	out.flush();
}

void FilterOutputStream::write(byte b) throw (IOExceptionPtr)
{
	out.write(b);
}

void FilterOutputStream::write(const byte* data, int offset, int len) throw (IOExceptionPtr)
{
	out.write(data, offset, len);
}

void FilterOutputStream::write(const bytearray& b) throw (IOExceptionPtr)
{
	out.write(b.data(), 0, b.size());
}
