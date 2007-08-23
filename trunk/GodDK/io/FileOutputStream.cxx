

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#if HAVE_ERRNO_H
# include <errno.h>
#endif

#include "io/FileOutputStream.h"
#include "lang/String.h"
using goddk::lang::String;
#include "lang/NullPointerException.h"
using goddk::lang::NullPointerException;
#include <io.h>
#include <SYS/STAT.H>
#include <direct.h>
#include <fcntl.h>
using namespace goddk::io;


FileOutputStream::FileOutputStream(File* f, bool append)
{
	_fd = _open(f->getAbsolutePath().toString().c_str(), O_CREAT|O_WRONLY|_O_BINARY);
	if(_fd == -1)
		THROWEXCEPTIONPTR1(IOException,::strerror(errno));
	_append = append;
	if(_append)
		position(size());
}
FileOutputStream::~FileOutputStream()
{
	close();
}

void FileOutputStream::close() throw (IOExceptionPtr)
{
	if(_fd != -1)
	{
		_close(_fd);
		_fd = -1;
	}
}

void FileOutputStream::flush() throw (IOExceptionPtr)
{
	if (_fd == -1)
		THROWEXCEPTIONPTR1(IOException,"no valid file handle to flush");

	if (::_commit(_fd) == -1)
		THROWEXCEPTIONPTR1(IOException, "flush()");
}

void FileOutputStream::write(byte b) throw (IOExceptionPtr)
{
	if (_fd == -1)
		THROWEXCEPTIONPTR1(IOException,"no valid file handle to write");

	if (::_write(_fd, &b, 1) == -1)
		THROWEXCEPTIONPTR1(IOException, "FileOutputStream::write()");

}

void FileOutputStream::write(const byte* data, int offset, int length) throw (IOExceptionPtr)
{
	if (length)
	{
		if (!data)
			THROWEXCEPTIONPTR(NullPointerException)

		if (_fd == -1)
			THROWEXCEPTIONPTR1(IOException,"no valid file handle to write");

		if (::_write(_fd, data+offset, length) == -1)
			THROWEXCEPTIONPTR1(IOException, "FileOutputStream::write()");
	}
}

void FileOutputStream::write(const bytearray& b) throw (IOExceptionPtr)
{
	write(b.data(), 0, b.size());
}
jint FileOutputStream::write(ByteBuffer* buf) throw (IOExceptionPtr)
{
	int rem = buf->limit() - buf->position();
	write(buf->array().data(), buf->position(), rem);
	buf->skip(rem);
	return rem;
}
__int64 FileOutputStream::position()
{
	if (_fd == -1)
		return 0;
	return _tell(_fd);
}
__int64 FileOutputStream::position(__int64 pos)
{
	if (_fd == -1)
	{
		THROWEXCEPTIONPTR1(IOException,"fseek failed");
		return 0;
	}
	if (_lseeki64(_fd, (long) pos, SEEK_SET) == -1)
#if HAVE_ERRNO_H
		THROWEXCEPTIONPTR1(IOException,::strerror(errno));
#else
		THROWEXCEPTIONPTR1(IOException,"fseek failed");
#endif
	return pos;
}
__int64 FileOutputStream::size()
{
	if (_fd == -1)
		return 0;
	return _filelength(_fd);
}