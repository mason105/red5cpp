#include "bits.h"
#include "nio/bytebuffer.h"
using goddk::nio::ByteBuffer;
namespace goddk {
	namespace nio {
		void *
			swapBytes(void *word, int size);
Bits::Bits()
{

}
jchar Bits::getCharL(ByteBuffer* bb, jint bi) {
	return makeChar(bb->_get(bi + 1),
		bb->_get(bi + 0));
}
jchar Bits::getCharB(ByteBuffer* bb, jint bi) {
	return makeChar(bb->_get(bi + 0),
		bb->_get(bi + 1));
}
void Bits::putCharL(ByteBuffer* bb, jint bi, jchar x) {
	bb->_put(bi + 0, jchar0(x));
	bb->_put(bi + 1, jchar1(x));
}
void Bits::putCharB(ByteBuffer* bb, jint bi, jchar x) {
	bb->_put(bi + 0, jchar1(x));
	bb->_put(bi + 1, jchar0(x));
}
jshort Bits::getShortL(ByteBuffer* bb, jint bi) {
	return makeShort(bb->_get(bi + 1),
		bb->_get(bi + 0));
}
jshort Bits::getShortB(ByteBuffer* bb, jint bi) {
	return makeShort(bb->_get(bi + 0),
		bb->_get(bi + 1));
}
void Bits::putShortL(ByteBuffer* bb, jint bi, jshort x) {
	bb->_put(bi + 0, jshort0(x));
	bb->_put(bi + 1, jshort1(x));
}
void Bits::putShortB(ByteBuffer* bb, jint bi, jshort x) {
	bb->_put(bi + 0, jshort1(x));
	bb->_put(bi + 1, jshort0(x));
}
jint Bits::getIntL(ByteBuffer* bb, jint bi) {
	return makeInt(bb->_get(bi + 3),
		bb->_get(bi + 2),
		bb->_get(bi + 1),
		bb->_get(bi + 0));
}
jint Bits::getIntB(ByteBuffer* bb, jint bi) {
	return makeInt(bb->_get(bi + 0),
		bb->_get(bi + 1),
		bb->_get(bi + 2),
		bb->_get(bi + 3));
}
void Bits::putIntL(ByteBuffer* bb, jint bi, jint x) {
	bb->_put(bi + 3, jint3(x));
	bb->_put(bi + 2, jint2(x));
	bb->_put(bi + 1, jint1(x));
	bb->_put(bi + 0, jint0(x));
}
void Bits::putIntB(ByteBuffer* bb, jint bi, jint x) {
	bb->_put(bi + 0, jint3(x));
	bb->_put(bi + 1, jint2(x));
	bb->_put(bi + 2, jint1(x));
	bb->_put(bi + 3, jint0(x));
}
jlong Bits::getLongL(ByteBuffer* bb, jint bi) {
	return makeLong(bb->_get(bi + 7),
		bb->_get(bi + 6),
		bb->_get(bi + 5),
		bb->_get(bi + 4),
		bb->_get(bi + 3),
		bb->_get(bi + 2),
		bb->_get(bi + 1),
		bb->_get(bi + 0));
	
}
jlong Bits::getLongB(ByteBuffer* bb, jint bi) {
	return makeLong(bb->_get(bi + 0),
		bb->_get(bi + 1),
		bb->_get(bi + 2),
		bb->_get(bi + 3),
		bb->_get(bi + 4),
		bb->_get(bi + 5),
		bb->_get(bi + 6),
		bb->_get(bi + 7));

}
void Bits::putLongL(ByteBuffer* bb, jint bi, jlong x) {
	bb->_put(bi + 7, jlong7(x));
	bb->_put(bi + 6, jlong6(x));
	bb->_put(bi + 5, jlong5(x));
	bb->_put(bi + 4, jlong4(x));
	bb->_put(bi + 3, jlong3(x));
	bb->_put(bi + 2, jlong2(x));
	bb->_put(bi + 1, jlong1(x));
	bb->_put(bi + 0, jlong0(x));
}
void Bits::putLongB(ByteBuffer* bb, jint bi, jlong x) {
	bb->_put(bi + 0, jlong7(x));
	bb->_put(bi + 1, jlong6(x));
	bb->_put(bi + 2, jlong5(x));
	bb->_put(bi + 3, jlong4(x));
	bb->_put(bi + 4, jlong3(x));
	bb->_put(bi + 5, jlong2(x));
	bb->_put(bi + 6, jlong1(x));
	bb->_put(bi + 7, jlong0(x));
}
jdouble Bits::getDoubleL(ByteBuffer* bb, jint bi) {
	byte tmp[8];
	for(int i = 0; i < 8; i ++)
		tmp[ i] = bb->_get(bi + i);
	jdouble v;
	memcpy(&v, tmp, 8);
	return v;
}
jdouble Bits::getDoubleB(ByteBuffer* bb, jint bi) {
	byte tmp[8];
	for(int i = 0; i < 8; i ++)
		tmp[7 -i] = bb->_get(bi + i);
	jdouble v;
	memcpy(&v, tmp, 8);
	return v;
}
void Bits::putDoubleL(ByteBuffer* bb, jint bi, jdouble x) {
	byte tmp[8];
	memcpy(tmp, &x, 8);
	for(int i = 0; i < 8; i ++)
		bb->_put(bi + i, tmp[i]);

}
void Bits::putDoubleB(ByteBuffer* bb, jint bi, jdouble x) {
	byte tmp[8];
	memcpy(tmp, &x, 8);
	swapBytes(tmp, 8);
	for(int i = 0; i < 8; i ++)
		bb->_put(bi + i, tmp[i]);
}
void *
swapBytes(void *word, int size)
{
	union {
		uint16_t s;
		struct {
			uint8_t c0;
			uint8_t c1;
		} c;
	} u;

	u.s = 1;
	if (u.c.c0 == 0) {
		// Big-endian machine: do nothing
		return word;
	}

	// Little-endian machine: byte-swap the word

	// A conveniently-typed pointer to the source data
	unsigned char *x = static_cast<unsigned char *>(word);

	switch (size) {
	case 2: // 16-bit integer
		{
			unsigned char c;
			c=x[0]; x[0]=x[1]; x[1]=c;
			break;
		}
	case 4: // 32-bit integer
		{
			unsigned char c;
			c=x[0]; x[0]=x[3]; x[3]=c;
			c=x[1]; x[1]=x[2]; x[2]=c;
			break;
		}
	case 8: // 64-bit integer
		{
			unsigned char c;
			c=x[0]; x[0]=x[7]; x[7]=c;
			c=x[1]; x[1]=x[6]; x[6]=c;
			c=x[2]; x[2]=x[5]; x[5]=c;
			c=x[3]; x[3]=x[4]; x[4]=c;
			break;
		}
	}

	return word;
}

}
}