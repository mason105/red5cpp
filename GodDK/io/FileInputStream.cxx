

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#if HAVE_ERRNO_H
# include <errno.h>
#endif

#include "io/FileInputStream.h"
#include "lang/Integer.h"
using goddk::lang::Integer;
#include "lang/String.h"
using goddk::lang::String;
#include "lang/NullPointerException.h"
using goddk::lang::NullPointerException;

using namespace goddk::io;

FileInputStream::FileInputStream(File* fob)
{
	_f = fopen(fob->getAbsolutePath().toString().c_str(), "rb");
	if(_f == 0)
		THROWEXCEPTIONPTR1(IOException,::strerror(errno));
	_fobj = fob;
	collection_attach(_fobj);

	_mark = -1;
}

FileInputStream::~FileInputStream()
{
	close();
}

int FileInputStream::available() throw (IOExceptionPtr)
{
	if (!_f)
		THROWEXCEPTIONPTR1(IOException,"not a valid file handle");

	long _curr, _size;

	if ((_curr = ftell(_f)) == -1)
		#if HAVE_ERRNO_H
		THROWEXCEPTIONPTR1(IOException,::strerror(errno));
		#else
		THROWEXCEPTIONPTR1(IOException,"ftell failed");
		#endif

	if (fseek(_f, 0, SEEK_END))
		#if HAVE_ERRNO_H
		THROWEXCEPTIONPTR1(IOException,::strerror(errno));
		#else
		THROWEXCEPTIONPTR1(IOException,"fseek failed");
		#endif

	if ((_size = ftell(_f)) == -1)
		#if HAVE_ERRNO_H
		THROWEXCEPTIONPTR1(IOException,::strerror(errno));
		#else
		THROWEXCEPTIONPTR1(IOException,"ftell failed");
		#endif

	if (fseek(_f, _curr, SEEK_SET))
		#if HAVE_ERRNO_H
		THROWEXCEPTIONPTR1(IOException,::strerror(errno));
		#else
		THROWEXCEPTIONPTR1(IOException,"fseek failed");
		#endif

	if ((_size - _curr) > Integer::MAX_VALUE)
		return Integer::MAX_VALUE;
	else
		return (int)(_size - _curr);
}

void FileInputStream::close() throw (IOExceptionPtr)
{
	if(_fobj)
	{
		collection_remove(_fobj);
		_fobj  = 0;
	}
	if(_f)
	{
		fclose(_f);
		_f = 0;
	}
	
}

void FileInputStream::mark(int readlimit) throw ()
{
	if (_f)
		_mark = ftell(_f);
}

bool FileInputStream::markSupported() throw ()
{
	return true;
}

int FileInputStream::read() throw (IOExceptionPtr)
{
	if (!_f)
		THROWEXCEPTIONPTR1(IOException,"not a valid file handle");

	return fgetc(_f);
}

int FileInputStream::read(byte* data, int offset, int length) throw (IOExceptionPtr)
{
	if (!_f)
		THROWEXCEPTIONPTR1(IOException,"not a valid file handle");

	if (!data)
		THROWEXCEPTIONPTR(NullPointerException)

	int rc = fread(data+offset, 1, length, _f);

	if (rc == 0)
		return -1;

	return rc;
}

int FileInputStream::read(bytearray& b) throw (IOExceptionPtr)
{
	return read(b.data(), 0, b.size());
}
jint FileInputStream::read(ByteBuffer* buf) throw (IOExceptionPtr)
{
	int rem = buf->limit() - buf->position();
	jint result = read(buf->array().data(), buf->position(), rem);
	if(result > 0)
		buf->skip(result);
	return result;
}
void FileInputStream::reset() throw (IOExceptionPtr)
{
	if (!_f)
		THROWEXCEPTIONPTR1(IOException,"not a valid file handle");

	if (_mark < 0)
		THROWEXCEPTIONPTR1(IOException,"not a valid mark");

	if (fseek(_f, _mark, SEEK_SET))
		#if HAVE_ERRNO_H
		THROWEXCEPTIONPTR1(IOException,::strerror(errno));
		#else
		THROWEXCEPTIONPTR1(IOException,"fseek failed");
		#endif
}

int FileInputStream::skip(int n) throw (IOExceptionPtr)
{
	if (!_f)
		THROWEXCEPTIONPTR1(IOException,"not a valid file handle");

	int _avail = available();

	if (n > _avail)
		n = _avail;

	if (fseek(_f, (long) n, SEEK_CUR))
		#if HAVE_ERRNO_H
		THROWEXCEPTIONPTR1(IOException,::strerror(errno));
		#else
		THROWEXCEPTIONPTR1(IOException,"fseek failed");
		#endif

	return n;
}
__int64 FileInputStream::position()
{
	if(!_f)
		return 0;
	return ftell(_f);
}
__int64 FileInputStream::position(__int64 pos)
{
	if(!_f)
	{
		THROWEXCEPTIONPTR1(IOException,"fseek failed");
		return 0;
	}
	if (fseek(_f, (long) pos, SEEK_SET))
#if HAVE_ERRNO_H
		THROWEXCEPTIONPTR1(IOException,::strerror(errno));
#else
		THROWEXCEPTIONPTR1(IOException,"fseek failed");
#endif
	return pos;
}
__int64 FileInputStream::size()
{
	if(!_fobj)
		return 0;
	return _fobj->length();
}