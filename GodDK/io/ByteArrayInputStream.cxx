

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "io/ByteArrayInputStream.h"
#include "lang/NullPointerException.h"
using goddk::lang::NullPointerException;

using namespace goddk::io;

ByteArrayInputStream::ByteArrayInputStream(const bytearray& b) : _buf(b)
{
	_count = _buf.size();
	_mark = 0;
	_pos = 0;
}

ByteArrayInputStream::ByteArrayInputStream(const byte* data, jint offset, jint length) : _buf(data+offset, length)
{
	_count = _buf.size();
	_mark = 0;
	_pos = 0;
}

ByteArrayInputStream::~ByteArrayInputStream()
{
}

jint ByteArrayInputStream::available() throw (IOExceptionPtr)
{
	return _count - _pos;
}

void ByteArrayInputStream::close() throw (IOExceptionPtr)
{
}

void ByteArrayInputStream::mark(jint readlimit) throw ()
{
	_mark = _pos;
}

bool ByteArrayInputStream::markSupported() throw ()
{
	return true;
}

jint ByteArrayInputStream::read() throw (IOExceptionPtr)
{
	register jint rc = -1;

	synchronized (this)
	{
		if (_pos < _count)
			rc = _buf[_pos++];
	}

	return rc;
}

jint ByteArrayInputStream::read(byte* data, jint offset, jint length) throw (IOExceptionPtr)
{
	if (!data)
		THROWEXCEPTIONPTR(NullPointerException)

	synchronized (this)
	{
		if (_pos >= _count)
			return -1;

		if (_pos + length > _count)
			length = _count - _pos;

		if (length == 0)
			return 0;

		memcpy(data+offset, _buf.data()+_pos, length);
		_pos += length;
	}

	return length;
}

jint ByteArrayInputStream::read(bytearray& b) throw (IOExceptionPtr)
{
	return read(b.data(), 0, b.size());
}

void ByteArrayInputStream::reset() throw (IOExceptionPtr)
{
	synchronized (this)
	{
		_pos = _mark;
	}
}

jint ByteArrayInputStream::skip(jint n) throw (IOExceptionPtr)
{
	synchronized (this)
	{
		if (_pos + n > _count)
			n = _count - _pos;
		_pos += n;
	}
	return n;
}
