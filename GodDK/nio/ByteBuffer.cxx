
#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "nio/ByteBuffer.h"
#include "bits.h"

using namespace goddk::nio;
const int nMaxCapacity = 65536;

ByteBuffer::fakebytearray::~fakebytearray()
{
	_data = 0;
	_size = 0;
}
void ByteBuffer::fakebytearray::set(byte* data, size_t size)throw ()
{
	_data = data;
	_size = size;
}

ByteBuffer::ByteBuffer(size_t capacity) throw (std::bad_alloc) : Buffer(capacity, capacity, false)
{
	bOutData = false;

	if(capacity > nMaxCapacity)
			throw std::bad_alloc();
	bigEndian = true;
	if(capacity > 0)
	{
		_data = (byte*) malloc(capacity);
		if (!_data)
			throw std::bad_alloc();

	}
	else
	{
		_data = 0;
	}
	_fake.set(_data, _capacity);
}
ByteBuffer::ByteBuffer(const byte* data, size_t capacity): Buffer(capacity, capacity, false)
{
	bOutData = false;

	if(capacity > nMaxCapacity)
		throw std::bad_alloc();
	bigEndian = true;

	_data = (byte*) malloc(capacity);
	if (!_data)
		throw std::bad_alloc();

	_fake.set(_data, _capacity);

	memcpy(_data, data, capacity);


	position(capacity);
}
ByteBuffer::~ByteBuffer()
{
	if (_data && !bOutData && GodIsValidAddress(_data))
	{
		free(_data);
		_data = 0;
	}
}
ByteBuffer* ByteBuffer::wrap(const byte* data, size_t capacity)
{
	ByteBuffer* buf = new ByteBuffer(0);
	buf->bOutData	= true;
	buf->_capacity	= capacity;
	buf->_limit		= capacity;
	buf->_position	= 0;
	buf->_marked	= false;
	buf->_readonly	= true;
	buf->_offset	= 0;
	buf->_mark		= 0;
	buf->_data		= (byte*)data;
	buf->_fake.set(buf->_data, buf->_capacity);
	
	return buf;
}
ByteBuffer* ByteBuffer::allocateDirect(size_t capacity) throw (std::bad_alloc)
{
	return new ByteBuffer(capacity);
}
ByteBuffer* ByteBuffer::allocate(const byte* data, size_t capacity) throw (std::bad_alloc)
{
	return new ByteBuffer(data, capacity);
}
ByteBuffer* ByteBuffer::allocate(size_t capacity) throw (std::bad_alloc)
{
	return new ByteBuffer(capacity);
}
ByteBuffer* ByteBuffer::wrap(bytearray* v)
{
	return new ByteBuffer(v->data(), v->size());
}
bytearray& ByteBuffer::array() throw (ReadOnlyBufferException, UnsupportedOperationException)
{
//	if (_readonly)
//		throw ReadOnlyBufferException();

	return _fake;
}

const bytearray& ByteBuffer::array() const throw (UnsupportedOperationException)
{
	return _fake;
}

size_t ByteBuffer::arrayOffset() const throw (ReadOnlyBufferException, UnsupportedOperationException)
{
//	if (_readonly)
//		throw ReadOnlyBufferException();

	return _position;
}
ByteBufferPtr ByteBuffer::asReadOnlyBuffer()
{
	ByteBuffer* bb = duplicate();
	bb->_readonly = true;
	ByteBufferPtr result;
	result.Attach(bb);
	return result;
}
void ByteBuffer::fill(byte v, size_t size)
{
	if(_position > _capacity - size || _readonly)
		THROWEXCEPTIONPTR1(IllegalArgumentException,"position greater than limit");
	for (int i = _position; i < (size+_position); i++)
		_data[i] = v;
	_position += size;
}
void ByteBuffer::put(bytearray& bytes, int pos ,int len)  throw()
{
	autoExpand(len);

	if(_position > _capacity - len || _readonly)
		THROWEXCEPTIONPTR1(IllegalArgumentException,"position greater than limit");
	memcpy(&_data[_position],&bytes[pos] , len);
	_position += len;
}
void ByteBuffer::put(bytearray& bytes)  throw()
{
	autoExpand(bytes.size());

	if(_position > _capacity - bytes.size() || _readonly)
		THROWEXCEPTIONPTR1(IllegalArgumentException,"position greater than limit");
	memcpy(&_data[_position],&bytes[0] , bytes.size());
	_position += bytes.size();
}
void ByteBuffer::put(ByteBuffer* in)  throw()
{
	autoExpand(in->remaining());

	int pos = in->position();
	int lim = in->limit();
	int rem = lim - pos;
	if(rem > remaining())
		rem = remaining();
	if(!in || _position > (int)_capacity - rem || _readonly)
		THROWEXCEPTIONPTR1(IllegalArgumentException,"position greater than limit");

	memcpy(&_data[_position],& (in->array().data()[pos]), rem);
	_position += rem;
	in->position(pos + rem);

}



void ByteBuffer::get(bytearray& bytes)  throw()
{
	if(_position > _capacity - bytes.size())
		THROWEXCEPTIONPTR1(IllegalArgumentException,"position greater than limit");
	memcpy(&bytes[0], &_data[_position], bytes.size());
	_position += bytes.size();
}
void ByteBuffer::get(bytearray& bytes, int pos ,int len)  throw()
{
	if(_position > _capacity - len)
		THROWEXCEPTIONPTR1(IllegalArgumentException,"position greater than limit");
	memcpy(&bytes[pos], &_data[_position], len);
	_position += len;
}

jushort ByteBuffer::getUnsignedShort()  throw()
{
	return getShort() & 0xffff;
}

ByteBuffer* ByteBuffer::compact()throw()
{
	memmove(&_data[ix(0)], &_data[ix(position())], remaining());
	position(remaining());
	limit(capacity());
	return this;
}
ByteBuffer* ByteBuffer::slice()throw()
{
	memcpy(&_data[ix(0)], &_data[ix(position())], remaining());
	position(remaining());
	limit(capacity());
	return this;
}
ByteBuffer* ByteBuffer::duplicate()throw()
{
	ByteBuffer *newbuf = ByteBuffer::allocate(capacity());
	newbuf->_capacity = this->_capacity;
	newbuf->_limit = this->_limit;
	newbuf->_mark = this->_mark;
	newbuf->_position = this->_position;
	newbuf->_marked = this->_marked;
	newbuf->_readonly = this->_readonly;
	memcpy(newbuf->_data, this->_data, limit());
	return  newbuf;
}
int ByteBuffer::skip(int n) throw ()
{

	if (n == 0)
		return 0;

	int canskip = _limit - _position;

	if (canskip > 0)
	{
		if (n < canskip)
		{
			canskip = n;
		}
		_position += canskip;
		n -= canskip;
	}

	if (n > 0)
	{
		canskip += n;
		_position += n;
	}

	return canskip;
}
bool ByteBuffer::isDirect() const throw ()
{
	return true;
}

bool ByteBuffer::hasArray() const throw ()
{
	return !_readonly;
}

int ByteBuffer::compareTo(const ByteBuffer& compare) const throw ()
{
	if (_capacity == 0)
	{
		if (compare._capacity == 0)
		{
			return 0;
		}
		else
		{
			return -1;
		}
	}
	else
	{
		if (compare._capacity == 0)
		{
			return 1;
		}
		else if (_capacity == compare._capacity)
		{
			return memcmp(_data, compare._data, _capacity);
		}
		else if (_capacity < compare._capacity)
		{
			if (memcmp(_data, compare._data, _capacity) == 0)
				return 1;
			else
				return -1;
		}
		else
		{
			if (memcmp(_data, compare._data, compare._capacity) == 0)
				return -1;
			else
				return 1;
		}
	}
}

const ByteOrder& ByteBuffer::order() const throw ()
{
	return bigEndian ? ByteOrder::BIG_ENDIAN : ByteOrder::LITTLE_ENDIAN;
}
void ByteBuffer::order(ByteOrder& o)  throw ()
{

}
ByteBuffer*	ByteBuffer::autoExpand( int expectedRemaining )
{
	if( isAutoExpand() )
	{
		expand( expectedRemaining );
	}
	return this;
}
ByteBuffer* ByteBuffer::expand( int expectedRemaining )
{
	return expand( position(), expectedRemaining );
}
ByteBuffer* ByteBuffer::expand( int pos, int expectedRemaining )
{
	int end = pos + expectedRemaining;
	if( end > capacity() )
	{
		capacity1( end );
	}

	if( end > limit() )
	{
		buf()->limit( end );
	}
	return this;
}
ByteBuffer* ByteBuffer::capacity1( int newCapacity )
{
	if( newCapacity > capacity() )
	{
		int pos = position();
		int lim = limit();
		
		capacity0( newCapacity );
		buf()->limit( lim );
		if( _mark >= 0 )
		{
			buf()->position( _mark );
			buf()->mark();
		}
		buf()->position( pos );
		
	}

	return this;
}
ByteBuffer* ByteBuffer::capacity0( int newCapacity )
{
	byte* _newdata = (byte*) malloc(newCapacity);
	if (!_newdata)
		throw std::bad_alloc();

	memcpy(_newdata, _data, _capacity);
	free(_data);
	_data = _newdata;

	_capacity = newCapacity;
	_fake.set(_data, _capacity);
	return this;
}