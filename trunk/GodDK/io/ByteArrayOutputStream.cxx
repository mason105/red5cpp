

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "io/ByteArrayOutputStream.h"
#include "lang/NullPointerException.h"
using goddk::lang::NullPointerException;

using namespace goddk::io;

ByteArrayOutputStream::ByteArrayOutputStream() : buf(32)
{
	count = 0;
}

ByteArrayOutputStream::ByteArrayOutputStream(jint size) : buf(size)
{
	count = 0;
}

ByteArrayOutputStream::~ByteArrayOutputStream()
{
}

void ByteArrayOutputStream::reset() throw ()
{
	count = 0;
}

jint ByteArrayOutputStream::size() throw ()
{
	return count;
}

bytearray* ByteArrayOutputStream::toByteArray()
{
	bytearray* result = new bytearray();

	toByteArray(*result);

	return result;
}

void ByteArrayOutputStream::toByteArray(bytearray& b)
{
	synchronized (this)
	{
		b.resize(count);
		memcpy(b.data(), buf.data(), count);
	}
}

void ByteArrayOutputStream::toByteArray(byte* data, jint offset, jint length)
{
	if (!data)
		THROWEXCEPTIONPTR(NullPointerException)

	synchronized (this)
	{
		memcpy(data+offset, buf.data(), length < count ? length : count);
	}
}

void ByteArrayOutputStream::close() throw (IOExceptionPtr)
{
}

void ByteArrayOutputStream::flush() throw (IOExceptionPtr)
{
}

void ByteArrayOutputStream::write(byte b) throw (IOExceptionPtr)
{
	synchronized (this)
	{
		jint newcount = count+1;
		jint actualsz = buf.size();

		if (actualsz < newcount)
		{
			if (actualsz == 0)
				buf.resize(32);
			else
				buf.resize(actualsz << 1);
		}

		buf[count++] = b;
	}
}

void ByteArrayOutputStream::write(const byte* data, jint offset, jint length) throw (IOExceptionPtr)
{
	if (length)
	{
		if (!data)
			THROWEXCEPTIONPTR(NullPointerException)

		synchronized (this)
		{
			jint newcount = count + length;
			jint actualsz = buf.size();

			if (newcount > actualsz)
				buf.resize(newcount > (actualsz << 1) ? newcount : (actualsz << 1));
	
			memcpy(buf.data()+count, data, length);
			count += length;
		}
	}
}

void ByteArrayOutputStream::write(const bytearray& b) throw (IOExceptionPtr)
{
	write(b.data(), 0, b.size());
}

void ByteArrayOutputStream::writeTo(OutputStream& out) throw (IOExceptionPtr)
{
	if (count)
	{
		synchronized (this)
		{
			out.write(buf.data(), 0, count);
		}
	}
}
