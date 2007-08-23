
#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "io/FilterInputStream.h"

using namespace goddk::io;

FilterInputStream::FilterInputStream(InputStream& in) : in(in)
{
}

FilterInputStream::~FilterInputStream()
{
}

int FilterInputStream::available() throw (IOExceptionPtr)
{
	return in.available();
}

void FilterInputStream::close() throw (IOExceptionPtr)
{
	in.close();
}

void FilterInputStream::mark(int readlimit) throw ()
{
	synchronized (this)
	{
		in.mark(readlimit);
	}
}

bool FilterInputStream::markSupported() throw ()
{
	return in.markSupported();
}

int FilterInputStream::read() throw (IOExceptionPtr)
{
	return in.read();
}

int FilterInputStream::read(byte* data, int offset, int len) throw (IOExceptionPtr)
{
	return in.read(data, offset, len);
}

int FilterInputStream::read(bytearray& b) throw (IOExceptionPtr)
{
	return in.read(b);
}

void FilterInputStream::reset() throw (IOExceptionPtr)
{
	synchronized (this)
	{
		in.reset();
	}
}

int FilterInputStream::skip(int n) throw (IOExceptionPtr)
{
	return in.skip(n);
}
