

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "nio/Buffer.h"
#include "lang/String.h"
using goddk::lang::String;

using namespace goddk::nio;

Buffer::Buffer(size_t capacity, size_t limit, bool readonly)
{
	_capacity = capacity;
	_limit = limit;
	_position = 0;
	_marked = false;
	_readonly = readonly;
	_offset = 0;
	_mark = 0;
}

size_t Buffer::capacity() const throw ()
{
	return _capacity;
}

Buffer& Buffer::clear() throw ()
{
	_limit = _capacity;
	_position = 0;
	_marked = false;

	return *this;
}

Buffer& Buffer::flip() throw ()
{
	_limit = _position;
	_position = 0;
	_marked = false;

	return *this;
}

bool Buffer::hasRemaining() const throw ()
{
	return (_position < _limit);
}

bool Buffer::isReadOnly() const throw ()
{
	return _readonly;
}

Buffer& Buffer::limit(size_t newLimit) throw (IllegalArgumentExceptionPtr)
{
	if (newLimit > _capacity)
		THROWEXCEPTIONPTR1(IllegalArgumentException,"limit greater than capacity");

	_limit = newLimit;

	if (_marked && (_mark > _limit))
		_marked = false;
	if (_position > _limit) _position = _limit;

	return *this;
}
size_t Buffer::limit() const throw ()
{
	return _limit;
}
Buffer& Buffer::mark() throw ()
{
	_marked = true;
	_mark = _position;

	return *this;
}

size_t Buffer::position() const throw ()
{
	return _position;
}

Buffer& Buffer::position(size_t newPosition) throw (IllegalArgumentExceptionPtr)
{
	if (newPosition > _limit)
		THROWEXCEPTIONPTR1(IllegalArgumentException,"position greater than limit");

	_position = newPosition;

	if (_marked && (_mark > _limit))
		_marked = false;

	return *this;
}

size_t Buffer::remaining() const throw ()
{
	return (_limit - _position);
}

Buffer& Buffer::reset() throw (InvalidMarkException)
{
	if (!_marked)
		throw InvalidMarkException();

	_position = _mark;

	return *this;
}

Buffer& Buffer::rewind() throw ()
{
	_position = _mark = 0;

	return *this;
}
