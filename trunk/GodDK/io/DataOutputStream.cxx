

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "io/DataOutputStream.h"

#include <iostream>
#include <unicode/ustream.h>

using namespace goddk::io;

DataOutputStream::DataOutputStream(OutputStream& out) : FilterOutputStream(out)
{
	_utf = 0;
	written = 0;
}

DataOutputStream::~DataOutputStream()
{
	if (_utf)
		ucnv_close(_utf);
}

jint DataOutputStream::size() const throw ()
{
	return written;
}

void DataOutputStream::write(byte b) throw (IOExceptionPtr)
{
	synchronized (this)
	{
		out.write(b);
		written++;
	}
}

void DataOutputStream::write(const byte* data, jint offset, jint length) throw (IOExceptionPtr)
{
	if (length)
	{
		synchronized (this)
		{
			out.write(data, offset, length);
			written += length;
		}
	}
}

void DataOutputStream::write(const bytearray& b) throw (IOExceptionPtr)
{
	write(b.data(), 0, b.size());
}

void DataOutputStream::writeBoolean(bool b) throw (IOExceptionPtr)
{
	synchronized (this)
	{
		out.write(b ? 1 : 0);
		written++;
	}
}

void DataOutputStream::writeByte(byte b) throw (IOExceptionPtr)
{
	synchronized (this)
	{
		out.write(b);
		written++;
	}
}

void DataOutputStream::writeShort(jshort s) throw (IOExceptionPtr)
{
	synchronized (this)
	{
		out.write((s >>  8)       );
		written++;
		out.write((s      ) & 0xff);
		written++;
	}
}

void DataOutputStream::writeInt(jint i) throw (IOExceptionPtr)
{
	synchronized (this)
	{
		out.write((i >> 24)       );
		written++;
		out.write((i >> 16) & 0xff);
		written++;
		out.write((i >>  8) & 0xff);
		written++;
		out.write((i      ) & 0xff);
		written++;
	}
}

#if defined(_MSC_VER)
# pragma optimize("",off)
#endif
void DataOutputStream::writeLong(jlong l) throw (IOExceptionPtr)
{
	synchronized (this)
	{
		out.write((l >> 56)       );
		written++;
		out.write((l >> 48) & 0xff);
		written++;
		out.write((l >> 40) & 0xff);
		written++;
		out.write((l >> 32) & 0xff);
		written++;
		out.write((l >> 24) & 0xff);
		written++;
		out.write((l >> 16) & 0xff);
		written++;
		out.write((l >>  8) & 0xff);
		written++;
		out.write((l      ) & 0xff);
		written++;
	}
}
#if defined(_MSC_VER)
# pragma optimize("",on)
#endif

void DataOutputStream::writeChar(jint v) throw (IOExceptionPtr)
{
	synchronized (this)
	{
		out.write((v >> 8) && 0xff);
		written++;
		out.write((v     ) && 0xff);
		written++;
	}
}

void DataOutputStream::writeChars(const String& str) throw (IOExceptionPtr)
{
	const array<jchar>& src = str.toCharArray();

	synchronized (this)
	{
		for (jint i = 0; i < src.size(); i++)
		{
			out.write((src[i] >> 8) & 0xff);
			written++;
			out.write((src[i]     ) & 0xff);
			written++;
		}
	}
}

void DataOutputStream::writeUTF(const String& str) throw (IOExceptionPtr)
{
	UErrorCode status = U_ZERO_ERROR;

	if (!_utf)
	{
		// UTF-8 converter lazy initialization
		_utf = ucnv_open("UTF-8", &status);
		if (U_FAILURE(status))
			THROWEXCEPTIONPTR1(IOException,"unable to open ICU UTF-8 converter");
	}

	const array<jchar>& src = str.toCharArray();

	// the expected status code here is U_BUFFER_OVERFLOW_ERROR
	jint need = ucnv_fromUChars(_utf, 0, 0, src.data(), src.size(), &status);
	if (U_FAILURE(status))
		if (status != U_BUFFER_OVERFLOW_ERROR)
			THROWEXCEPTIONPTR1(IOException,"ucnv_fromUChars failed");

	if (need > 0xffff)
		THROWEXCEPTIONPTR1(IOException,"String length >= 64K");

	byte* buffer = new byte[need];

	status = U_ZERO_ERROR;

	// the expected status code here is U_STRING_NOT_TERMINATED_WARNING
	ucnv_fromUChars(_utf, (char*) buffer, need, src.data(), src.size(), &status);
	if (status != U_STRING_NOT_TERMINATED_WARNING)
	{
		delete[] buffer;
		THROWEXCEPTIONPTR1(IOException,"ucnv_fromUChars failed");
	}

	// everything ready for the critical section
	try
	{
		synchronized (this)
		{
			out.write((need >>  8) & 0xff);
			written++;
			out.write((need      ) & 0xff);
			written++;
			out.write(buffer, 0, need);
			written += need;
		}
	}
	catch (IOException&)
	{
		delete[] buffer;
		throw;
	}
}
