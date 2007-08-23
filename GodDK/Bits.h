#pragma	  once

#include "array.h"
#include "lang/Comparable.h"
#include "nio/Buffer.h"
#include "nio/ByteOrder.h"
#include "nio/ReadOnlyBufferException.h"
#include "lang/UnsupportedOperationException.h"
using namespace goddk::lang;
using namespace goddk::nio;

namespace goddk {
	namespace nio {
class ByteBuffer;
class Bits
{
public:
	Bits();

	static byte _get(jlong v, int i)
	{
		byte tmp[8];
		memcpy(tmp, &v, sizeof(v));
		return tmp[i];
	}
	static void _put(jlong* v,int i, byte b){
		byte tmp[8];
		memcpy(tmp, v, sizeof(jlong));
		tmp[i] = b;
		memcpy(v, tmp, sizeof(jlong));
	}

	static jshort swap(jshort x) {
		return (jshort)((x << 8) |
			((x >> 8) & 0xff));
	}

	static jchar swap(jchar x) {
		return (jchar)((x << 8) |
			((x >> 8) & 0xff));
	}

	static jint swap(jint x) {
		return (jint)((swap((jshort)x) << 16) |
			(swap((jshort)(x >> 16)) & 0xffff));
	}

	static jlong swap(jlong x) {
		return (jlong)(((jlong)swap((jint)(x)) << 32) |
			((jlong)swap((jint)(x >> 32)) & 0xffffffffL));
	}

	
	// -- get/put jchar --

	static  jchar makeChar(jbyte b1, jbyte b0) {
		return (jchar)((b1 << 8) | (b0 & 0xff));
	}

	static jchar getCharL(ByteBuffer* bb, jint bi);

	static jchar getCharL(jlong a) {
		return makeChar(_get(a , 1),
			_get(a , 0));
	}

	static jchar getCharB(ByteBuffer* bb, jint bi);

	static jchar getCharB(jlong a) {
		return makeChar(_get(a , 0),
			_get(a , 1));
	}

	static jchar getChar(ByteBuffer* bb, jint bi, bool bigEndian) {
		return (bigEndian ? getCharB(bb, bi) : getCharL(bb, bi));
	}

	static jchar getChar(jlong a, bool bigEndian) {
		return (bigEndian ? getCharB(a) : getCharL(a));
	}

	 static jbyte jchar1(jchar x) { return (jbyte)(x >> 8); }
	 static jbyte jchar0(jchar x) { return (jbyte)(x >> 0); }

	static void putCharL(ByteBuffer* bb, jint bi, jchar x);

	static void putCharL(jlong a, jchar x) {
		_put(&a , 0, jchar0(x));
		_put(&a ,+ 1, jchar1(x));
	}
	static void putCharB(ByteBuffer* bb, jint bi, jchar x);

	static void putCharB(jlong a, jchar x) {
		_put(&a , 0, jchar1(x));
		_put(&a , 1, jchar0(x));
	}

	static void putChar(ByteBuffer* bb, jint bi, jchar x, bool bigEndian) {
		if (bigEndian)
			putCharB(bb, bi, x);
		else
			putCharL(bb, bi, x);
	}

	static void putChar(jlong a, jchar x, bool bigEndian) {
		if (bigEndian)
			putCharB(a, x);
		else
			putCharL(a, x);
	}

	
	// -- get/put jshort --

	static  jshort makeShort(jbyte b1, jbyte b0) {
		return (jshort)((b1 << 8) | (b0 & 0xff));
	}

	static jshort getShortL(ByteBuffer* bb, jint bi);

	static jshort getShortL(jlong a) {
		return makeShort(_get(a , 1),
			_get(a, 0));
	}

	static jshort getShortB(ByteBuffer* bb, jint bi);

	static jshort getShortB(jlong a) {
		return makeShort(_get(a, 0),
			_get(a , 1));
	}

	static jshort getShort(ByteBuffer* bb, jint bi, bool bigEndian) {
		return (bigEndian ? getShortB(bb, bi) : getShortL(bb, bi));
	}

	static jshort getShort(jlong a, bool bigEndian) {
		return (bigEndian ? getShortB(a) : getShortL(a));
	}

	 static jbyte jshort1(jshort x) { return (jbyte)(x >> 8); }
	 static jbyte jshort0(jshort x) { return (jbyte)(x >> 0); }

	static void putShortL(ByteBuffer* bb, jint bi, jshort x);

	static void putShortL(jlong a, jshort x) {
		_put(&a , 0, jshort0(x));
		_put(&a , 1, jshort1(x));
	}

	static void putShortB(ByteBuffer* bb, jint bi, jshort x);

	static void putShortB(jlong a, jshort x) {
		_put(&a , 0, jshort1(x));
		_put(&a , 1, jshort0(x));
	}

	static void putShort(ByteBuffer* bb, jint bi, jshort x, bool bigEndian) {
		if (bigEndian)
			putShortB(bb, bi, x);
		else
			putShortL(bb, bi, x);
	}

	static void putShort(jlong a, jshort x, bool bigEndian) {
		if (bigEndian)
			putShortB(a, x);
		else
			putShortL(a, x);
	}

	
	// -- get/put jint --

	static  jint makeInt(jbyte b3, jbyte b2, jbyte b1, jbyte b0) {
		return (jint)((((b3 & 0xff) << 24) |
			((b2 & 0xff) << 16) |
			((b1 & 0xff) <<  8) |
			((b0 & 0xff) <<  0)));
	}

	static jint getIntL(ByteBuffer* bb, jint bi);

	static jint getIntL(jlong a) {
		return makeInt(_get(a , 3),
			_get(a , 2),
			_get(a , 1),
			_get(a , 0));
	}

	static jint getIntB(ByteBuffer* bb, jint bi);

	static jint getIntB(jlong a) {
		return makeInt(_get(a , 0),
			_get(a , 1),
			_get(a , 2),
			_get(a , 3));
	}

	static jint getInt(ByteBuffer* bb, jint bi, bool bigEndian) {
		return (bigEndian ? getIntB(bb, bi) : getIntL(bb, bi));
	}

	static jint getInt(jlong a, bool bigEndian) {
		return (bigEndian ? getIntB(a) : getIntL(a));
	}

	 static jbyte jint3(jint x) { return (jbyte)(x >> 24); }
	 static jbyte jint2(jint x) { return (jbyte)(x >> 16); }
	 static jbyte jint1(jint x) { return (jbyte)(x >>  8); }
	 static jbyte jint0(jint x) { return (jbyte)(x >>  0); }

	static void putIntL(ByteBuffer* bb, jint bi, jint x);

	static void putIntL(jlong a, jint x) {
		_put(&a , 3, jint3(x));
		_put(&a , 2, jint2(x));
		_put(&a , 1, jint1(x));
		_put(&a , 0, jint0(x));
	}

	static void putIntB(ByteBuffer* bb, jint bi, jint x);

	static void putIntB(jlong a, jint x) {
		_put(&a , 0, jint3(x));
		_put(&a , 1, jint2(x));
		_put(&a , 2, jint1(x));
		_put(&a , 3, jint0(x));
	}

	static void putInt(ByteBuffer* bb, jint bi, jint x, bool bigEndian) {
		if (bigEndian)
			putIntB(bb, bi, x);
		else
			putIntL(bb, bi, x);
	}

	static void putInt(jlong a, jint x, bool bigEndian) {
		if (bigEndian)
			putIntB(a, x);
		else
			putIntL(a, x);
	}

	
	// -- get/put jlong --

	static  jlong makeLong(jbyte b7, jbyte b6, jbyte b5, jbyte b4,
		jbyte b3, jbyte b2, jbyte b1, jbyte b0)
	{
		return ((((jlong)b7 & 0xff) << 56) |
			(((jlong)b6 & 0xff) << 48) |
			(((jlong)b5 & 0xff) << 40) |
			(((jlong)b4 & 0xff) << 32) |
			(((jlong)b3 & 0xff) << 24) |
			(((jlong)b2 & 0xff) << 16) |
			(((jlong)b1 & 0xff) <<  8) |
			(((jlong)b0 & 0xff) <<  0));
	}

	static jlong getLongL(ByteBuffer* bb, jint bi);

	static jlong getLongL(jlong a) {
		return makeLong(_get(a , 7),
			_get(a , 6),
			_get(a , 5),
			_get(a , 4),
			_get(a , 3),
			_get(a , 2),
			_get(a , 1),
			_get(a , 0));
	}

	static jlong getLongB(ByteBuffer* bb, jint bi);

	static jlong getLongB(jlong a) {
		return makeLong(_get(a , 0),
			_get(a , 1),
			_get(a , 2),
			_get(a , 3),
			_get(a , 4),
			_get(a , 5),
			_get(a , 6),
			_get(a , 7));
	}
	static jlong getLong(ByteBuffer* bb, jint bi, bool bigEndian) {
		return (bigEndian ? getLongB(bb, bi) : getLongL(bb, bi));
	}

	static jlong getLong(jlong a, bool bigEndian) {
		return (bigEndian ? getLongB(a) : getLongL(a));
	}

	 static jbyte jlong7(jlong x) { return (jbyte)(x >> 56); }
	 static jbyte jlong6(jlong x) { return (jbyte)(x >> 48); }
	 static jbyte jlong5(jlong x) { return (jbyte)(x >> 40); }
	 static jbyte jlong4(jlong x) { return (jbyte)(x >> 32); }
	 static jbyte jlong3(jlong x) { return (jbyte)(x >> 24); }
	 static jbyte jlong2(jlong x) { return (jbyte)(x >> 16); }
	 static jbyte jlong1(jlong x) { return (jbyte)(x >>  8); }
	 static jbyte jlong0(jlong x) { return (jbyte)(x >>  0); }

	static void putLongL(ByteBuffer* bb, jint bi, jlong x);

	static void putLongL(jlong a, jlong x) {
		_put(&a , 7, jlong7(x));
		_put(&a , 6, jlong6(x));
		_put(&a , 5, jlong5(x));
		_put(&a , 4, jlong4(x));
		_put(&a , 3, jlong3(x));
		_put(&a , 2, jlong2(x));
		_put(&a , 1, jlong1(x));
		_put(&a , 0, jlong0(x));
	}

	static void putLongB(ByteBuffer* bb, jint bi, jlong x);

	static void putLongB(jlong a, jlong x) {
		_put(&a , 0, jlong7(x));
		_put(&a , 1, jlong6(x));
		_put(&a , 2, jlong5(x));
		_put(&a , 3, jlong4(x));
		_put(&a , 4, jlong3(x));
		_put(&a , 5, jlong2(x));
		_put(&a , 6, jlong1(x));
		_put(&a , 7, jlong0(x));
	}

	static void putLong(ByteBuffer* bb, jint bi, jlong x, bool bigEndian) {
		if (bigEndian)
			putLongB(bb, bi, x);
		else
			putLongL(bb, bi, x);
	}

	static void putLong(jlong a, jlong x, bool bigEndian) {
		if (bigEndian)
			putLongB(a, x);
		else
			putLongL(a, x);
	}

	
	// -- get/put float --

	static float getFloatL(ByteBuffer* bb, jint bi) {
		return (float)(getIntL(bb, bi));
	}

	static float getFloatL(jlong a) {
		return (float)(getIntL(a));
	}

	static float getFloatB(ByteBuffer* bb, jint bi) {
		return (float)(getIntB(bb, bi));
	}

	static float getFloatB(jlong a) {
		return (float)(getIntB(a));
	}

	static float getFloat(ByteBuffer* bb, jint bi, bool bigEndian) {
		return (bigEndian ? getFloatB(bb, bi) : getFloatL(bb, bi));
	}

	static float getFloat(jlong a, bool bigEndian) {
		return (bigEndian ? getFloatB(a) : getFloatL(a));
	}

	static void putFloatL(ByteBuffer* bb, jint bi, float x) {
		putIntL(bb, bi, (jint)(x));
	}

	static void putFloatL(jlong a, float x) {
		putIntL(a, (jint)(x));
	}

	static void putFloatB(ByteBuffer* bb, jint bi, float x) {
		putIntB(bb, bi, (jint)(x));
	}

	static void putFloatB(jlong a, float x) {
		putIntB(a, (jint)(x));
	}

	static void putFloat(ByteBuffer* bb, jint bi, float x, bool bigEndian) {
		if (bigEndian)
			putFloatB(bb, bi, x);
		else
			putFloatL(bb, bi, x);
	}

	static void putFloat(jlong a, float x, bool bigEndian) {
		if (bigEndian)
			putFloatB(a, x);
		else
			putFloatL(a, x);
	}

	
	// -- get/put jdouble --

	static jdouble getDoubleL(ByteBuffer* bb, jint bi);

	static jdouble getDoubleL(jlong a) {
		return (jdouble)(getLongL(a));
	}

	static jdouble getDoubleB(ByteBuffer* bb, jint bi);

	static jdouble getDoubleB(jlong a) {
		return (jdouble)(getLongB(a));
	}

	static jdouble getDouble(ByteBuffer* bb, jint bi, bool bigEndian) {
		return (bigEndian ? getDoubleB(bb, bi) : getDoubleL(bb, bi));
	}

	static jdouble getDouble(jlong a, bool bigEndian) {
		return (bigEndian ? getDoubleB(a) : getDoubleL(a));
	}

	static void putDoubleL(ByteBuffer* bb, jint bi, jdouble x) ;

	static void putDoubleL(jlong a, jdouble x) {
		putLongL(a, (jlong)(x));
	}

	static void putDoubleB(ByteBuffer* bb, jint bi, jdouble x);

	static void putDoubleB(jlong a, jdouble x) {
		putLongB(a, (jlong)(x));
	}

	static void putDouble(ByteBuffer* bb, jint bi, jdouble x, bool bigEndian) {
		if (bigEndian)
			putDoubleB(bb, bi, x);
		else
			putDoubleL(bb, bi, x);
	}

	static void putDouble(jlong a, jdouble x, bool bigEndian) {
		if (bigEndian)
			putDoubleB(a, x);
		else
			putDoubleL(a, x);
	}

};
}
}