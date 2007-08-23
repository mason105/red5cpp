

#ifndef _CLASS_BYTEBUFFER_H
#define _CLASS_BYTEBUFFER_H

#ifdef __cplusplus

#include "array.h"
#include "lang/Comparable.h"
#include "nio/Buffer.h"
#include "nio/ByteOrder.h"
#include "nio/ReadOnlyBufferException.h"
#include "lang/UnsupportedOperationException.h"
#include "bits.h"
using namespace goddk::nio;
using namespace goddk::lang;

/* Note: be careful; we have to derive a MappedByteBuffer class from this one
 * (which contains an mmap-ed fd)
 */

namespace goddk {
	namespace nio {
		class ByteBuffer;
		typedef CSmartPtr<ByteBuffer>		ByteBufferPtr;

		class ByteBuffer : public Buffer, public Comparable<ByteBuffer>
		{
		private:
			class fakebytearray : public bytearray
			{
			public:
				~fakebytearray();

				void set(byte* data, size_t size) throw ();
			};

			fakebytearray _fake;
			byte* _data;
			bool _free;
			bool bAutoExpand;
			bool bOutData;
			bool bigEndian;

			ByteBuffer(const byte*, size_t);
			ByteBuffer(size_t capacity) throw (std::bad_alloc);

		public:
			virtual ~ByteBuffer();
			bool instanceof(const char* class_name)const throw()
			{
				if(strcmp("ByteBuffer", class_name)== 0)
					return true;
				else
					return __super::instanceof(class_name);
			}
			static ByteBuffer* allocate(size_t capacity) throw (std::bad_alloc);
			static ByteBuffer* allocate(const byte* data, size_t capacity) throw (std::bad_alloc);
			static ByteBuffer* allocateDirect(size_t capacity) throw (std::bad_alloc);
			static ByteBuffer* wrap(const byte* data, size_t capacity) throw (std::bad_alloc);
			static ByteBuffer* wrap(bytearray* v);

			bytearray& array() throw (ReadOnlyBufferExceptionPtr, UnsupportedOperationExceptionPtr);
			const bytearray& array() const throw (UnsupportedOperationExceptionPtr);
			ByteBuffer* buf() throw (ReadOnlyBufferExceptionPtr, UnsupportedOperationExceptionPtr){return this;}
			size_t arrayOffset() const throw (ReadOnlyBufferExceptionPtr, UnsupportedOperationExceptionPtr);

			ByteBufferPtr asReadOnlyBuffer();

			virtual bool isDirect() const throw ();
			bool isAutoExpand(){
				return bAutoExpand;
			}
			bool hasArray() const throw ();

			const ByteOrder& order() const throw ();
			void order(ByteOrder& o)  throw ();

			virtual int compareTo(const ByteBuffer& compare) const throw ();
			ByteBuffer* expand( int expectedRemaining );
			ByteBuffer* expand( int pos, int expectedRemaining );
			ByteBuffer* capacity1( int newCapacity );
			ByteBuffer* capacity0( int newCapacity );
	
			byte _get(int i) {			
				return _data[i];
			}
			void _put(int i, byte b) {		
				_data[i] = b;
			}
			void setAutoExpand(bool v)
			{
				bAutoExpand = v;
			}
			void fill(byte v, size_t size) throw();
			void put(bytearray& bytes)  throw();
			void put(bytearray& bytes, int pos ,int len)  throw();
			void get(bytearray& bytes)  throw();
			void get(bytearray& bytes, int pos ,int len)  throw();
			void put(ByteBuffer* in)  throw();

			jchar getChar() {
				return Bits::getChar(this, ix(nextGetIndex(2)), bigEndian);
			}
			jchar getChar(jint i) {
				return Bits::getChar(this, ix(checkIndex(i, 2)), bigEndian);
			}
			ByteBuffer* putChar(jchar x) {
				Bits::putChar(this, ix(nextPutIndex(2)), x, bigEndian);
				return this;
			}
			ByteBuffer* putChar(jint i, jchar x) {
				Bits::putChar(this, ix(checkIndex(i, 2)), x, bigEndian);
				return this;
			}
			jshort getShort() {
				return Bits::getShort(this, ix(nextGetIndex(2)), bigEndian);
			}
			jshort getShort(jint i) {
				return Bits::getShort(this, ix(checkIndex(i, 2)), bigEndian);
			}
			ByteBuffer* putShort(jshort x) {
				Bits::putShort(this, ix(nextPutIndex(2)), x, bigEndian);
				return this;
			}
			ByteBuffer* putShort(jint i, jshort x) {
				Bits::putShort(this, ix(checkIndex(i, 2)), x, bigEndian);
				return this;
			}
			jint getInt() {
				return Bits::getInt(this, ix(nextGetIndex(4)), bigEndian);
			}
			jint getInt(jint i) {
				return Bits::getInt(this, ix(checkIndex(i, 4)), bigEndian);
			}
			ByteBuffer* putInt(jint x) {
				Bits::putInt(this, ix(nextPutIndex(4)), x, bigEndian);
				return this;
			}
			ByteBuffer* putInt(jint i, jint x) {
				Bits::putInt(this, ix(checkIndex(i, 4)), x, bigEndian);
				return this;
			}
			jlong getLong() {
				return Bits::getLong(this, ix(nextGetIndex(8)), bigEndian);
			}
			jlong getLong(jint i) {
				return Bits::getLong(this, ix(checkIndex(i, 8)), bigEndian);
			}
			ByteBuffer* putLong(jlong x) {

				Bits::putLong(this, ix(nextPutIndex(8)), x, bigEndian);
				return this;
			}
			ByteBuffer* putLong(jint i, jlong x) {
				Bits::putLong(this, ix(checkIndex(i, 8)), x, bigEndian);
				return this;
			}
			jfloat getFloat() {
				return Bits::getFloat(this, ix(nextGetIndex(4)), bigEndian);
			}
			jfloat getFloat(jint i) {
				return Bits::getFloat(this, ix(checkIndex(i, 4)), bigEndian);
			}
			ByteBuffer* putFloat(jfloat x) {
				Bits::putFloat(this, ix(nextPutIndex(4)), x, bigEndian);
				return this;
			}
			ByteBuffer* putFloat(jint i, jfloat x) {
				Bits::putFloat(this, ix(checkIndex(i, 4)), x, bigEndian);
				return this;
			}
			jdouble getDouble() {
				return Bits::getDouble(this, ix(nextGetIndex(8)), bigEndian);
			}
			jdouble getDouble(jint i) {
				return Bits::getDouble(this, ix(checkIndex(i, 8)), bigEndian);
			}
			ByteBuffer* putDouble(jdouble x) {
				Bits::putDouble(this, ix(nextPutIndex(8)), x, bigEndian);
				return this;
			}
			ByteBuffer* putDouble(jint i, jdouble x) {
				Bits::putDouble(this, ix(checkIndex(i, 8)), x, bigEndian);
				return this;
			}

			ByteBuffer* put(byte x) {
				_data[ix(nextPutIndex())] = x;
				return this;
			}
			ByteBuffer* put(int i, byte x) {
				_data[ix(checkIndex(i))] = x;
				return this;
			}
			byte get() {
				return _data[ix(nextGetIndex())];
			}
			byte get(int i) {
				return _data[ix(checkIndex(i))];
			}

			jushort getUnsignedShort()  throw();

			int skip(int n)throw ();

			ByteBuffer* compact()throw();
			ByteBuffer* slice()throw();
			ByteBuffer* duplicate()throw();

			int ix(int i) {
				return i + _offset;
			}
			protected:
			ByteBuffer*	autoExpand( int expectedRemaining );
		};
	}
}

#endif

#endif
