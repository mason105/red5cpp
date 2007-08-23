

#ifndef _ABSTRACT_CLASS_GOD_NIO_BUFFER_H
#define _ABSTRACT_CLASS_GOD_NIO_BUFFER_H

#ifdef __cplusplus

#include "lang/IllegalArgumentException.h"
#include "lang/IndexOutOfBoundsException.h"
#include "lang/Object.h"
#include "nio/InvalidMarkException.h"
using namespace goddk::lang;
using namespace goddk::nio;

namespace goddk {
	namespace nio {
		class  Buffer : public Object
		{
		protected:
			size_t _capacity;
			size_t _limit;
			size_t _mark;
			size_t _position;
			size_t _offset;
			bool   _marked;
			bool   _readonly;

			Buffer(size_t capacity, size_t limit, bool readonly);

		public:
			virtual ~Buffer() {};
			bool instanceof(const char* class_name)const throw()
			{
				if(strcmp("Buffer", class_name)== 0)
					return true;
				else
					return __super::instanceof(class_name);
			}
			size_t capacity() const throw ();
			Buffer& clear() throw ();
			Buffer& flip() throw ();
			bool hasRemaining() const throw ();
			virtual bool isReadOnly() const throw ();
			size_t limit() const throw ();
			Buffer& limit(size_t newLimit) throw (IllegalArgumentExceptionPtr);
			Buffer& mark() throw ();
			size_t position() const throw ();
			Buffer& position(size_t newPosition) throw (IllegalArgumentExceptionPtr);
			size_t remaining() const throw ();
			Buffer& reset() throw (InvalidMarkException);
			Buffer& rewind() throw ();

			int nextGetIndex() {				// package-private
				if (_position >= _limit)
					THROWEXCEPTIONPTR(IndexOutOfBoundsException)
				return _position++;
			}
			int nextGetIndex(int nb) {			// package-private
				if (_limit - _position < nb)
					THROWEXCEPTIONPTR(IndexOutOfBoundsException)
				int p = _position;
				_position += nb;
				return p;
			}
			int nextPutIndex() {				// package-private
				if (_position >= _limit)
					THROWEXCEPTIONPTR(IndexOutOfBoundsException)
				return _position++;
			}
			int nextPutIndex(int nb) {			// package-private
				if (_limit - _position < nb)
					THROWEXCEPTIONPTR(IndexOutOfBoundsException)
				int p = _position;
				_position += nb;
				return p;
			}
			int checkIndex(int i) {			// package-private
				if ((i < 0) || (i >= _limit))
					THROWEXCEPTIONPTR(IndexOutOfBoundsException)
				return i;
			}
			int checkIndex(int i, int nb) {		// package-private
				if ((i < 0) || (nb > _limit - i))
					THROWEXCEPTIONPTR(IndexOutOfBoundsException)
				return i;
			}
			static void checkBounds(int off, int len, int size) { // package-private
				if ((off | len | (off + len) | (size - (off + len))) < 0)
					THROWEXCEPTIONPTR(IndexOutOfBoundsException)
			}
		};
		typedef CSmartPtr<Buffer>		BufferPtr;
	}
}

#endif

#endif
