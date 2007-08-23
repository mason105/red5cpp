

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "io/PushbackInputStream.h"
#include "lang/String.h"
using goddk::lang::String;
#include "lang/NullPointerException.h"
using goddk::lang::NullPointerException;

using namespace goddk::io;

PushbackInputStream::PushbackInputStream(InputStream& in, int size) : FilterInputStream(in), buf(size)
{
	_closed = false;
	pos = 0;
}

PushbackInputStream::~PushbackInputStream()
{
}

int PushbackInputStream::available() throw (IOExceptionPtr)
{
	if (_closed)
		THROWEXCEPTIONPTR1(IOException,"Stream closed");

	return in.available() + (buf.size() - pos);
}

void PushbackInputStream::close() throw (IOExceptionPtr)
{
	if (!_closed)
	{
		in.close();
		_closed = true;
	}
}

int PushbackInputStream::read() throw (IOExceptionPtr)
{
	if (_closed)
		THROWEXCEPTIONPTR1(IOException,"Stream closed");

	if (pos < buf.size())
		return buf[pos++];

	return in.read();
}

bool PushbackInputStream::markSupported() throw ()
{
	return false;
}

int PushbackInputStream::read(byte* data, int offset, int length) throw (IOExceptionPtr)
{
	if (!data)
		THROWEXCEPTIONPTR(NullPointerException)

	if (_closed)
		THROWEXCEPTIONPTR1(IOException,"Stream closed");

	if (length == 0)
		return 0;

	int buffered = buf.size() - pos;

	if (buffered > 0)
	{
		if (length < buffered)
			buffered = length;

		memcpy(data+offset, buf.data()+pos, buffered);

		pos += buffered;
		offset += buffered;
		length -= buffered;
	}

	if (length > 0)
	{
		int rc = in.read(data, offset, length);
		if (rc < 0)
			if (buffered == 0)
				return -1; // nothing in buffer and nothing read
			else
				return buffered; // something in buffer and nothing read

		return buffered + rc; // something in buffer and something read
	}

	return buffered; // everything was in buffer
}

int PushbackInputStream::skip(int n) throw (IOExceptionPtr)
{
	if (_closed)
		THROWEXCEPTIONPTR1(IOException,"Stream closed");

	if (n == 0)
		return 0;

	int canskip = buf.size() - pos;

	if (canskip > 0)
	{
		if (n < canskip)
		{
			// more in buffer than we need to skip
			canskip = n;
		}
		pos += canskip;
		n -= canskip;
	}

	if (n > 0)
	{
		// apparently we didn't have enough in the buffer
		canskip += in.skip(n);
	}

	return canskip;
}

void PushbackInputStream::unread(byte b) throw (IOExceptionPtr)
{
	if (_closed)
		THROWEXCEPTIONPTR1(IOException,"Stream closed");

	if (pos == 0)
		THROWEXCEPTIONPTR1(IOException,"Pushback buffer is full");

	buf[--pos] = b;
}

void PushbackInputStream::unread(const bytearray& b) throw (IOExceptionPtr)
{
	unread(b.data(), 0, b.size());
}

void PushbackInputStream::unread(const byte* data, int offset, int length) throw (IOExceptionPtr)
{
	if (!data)
		THROWEXCEPTIONPTR(NullPointerException)

	pos -= length;

	memcpy(buf.data()+pos, data+offset, length);
}
