
#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "io/Writer.h"
#include "lang/IllegalArgumentException.h"
using goddk::lang::IllegalArgumentException;
#include "lang/NullPointerException.h"
using goddk::lang::NullPointerException;

using namespace goddk::io;

Writer::Writer()
{
	lock = this;
}

Writer::Writer(Object& lock) : lock(&lock)
{
}


Writer& Writer::append(jchar c) throw (IOExceptionPtr)
{
	write(c);

	return *this;
}

Writer& Writer::append(const CharSequence& cseq) throw (IOExceptionPtr)
{
	write(String(cseq.toString().c_str()));

	return *this;
}

void Writer::write(jint c) throw (IOExceptionPtr)
{
	synchronized (lock)
	{
		jchar tmp = c;

		write(&tmp, 0, 1);
	}
}

void Writer::write(const array<jchar>& cbuf) throw (IOExceptionPtr)
{
	synchronized (lock)
	{
		write(cbuf.data(), 0, cbuf.size());
	}
}

void Writer::write(const String& str) throw (IOExceptionPtr)
{
	synchronized (lock)
	{
		const array<jchar>& tmp = str.toCharArray();

		write(tmp.data(), 0, tmp.size());
	}
}

void Writer::write(const String& str, jint off, jint len) throw (IOExceptionPtr)
{
	if (off < 0 || len < 0 || off + len >= str.length())
		THROWEXCEPTIONPTR(NullPointerException)

	synchronized (lock)
	{
		const array<jchar>& tmp = str.toCharArray();

		write(tmp.data(), off, len);
	}
}
