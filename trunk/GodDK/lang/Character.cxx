

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "lang/Character.h"

using namespace goddk::lang;

const jchar Character::MIN_VALUE = (jchar) 0;
const jchar Character::MAX_VALUE = (jchar) 0xFFFF;

const jchar Character::MIN_HIGH_SURROGATE = (jchar) 0xD800;
const jchar Character::MAX_HIGH_SURROGATE = (jchar) 0xDBFF;
const jchar Character::MIN_LOW_SURROGATE = (jchar) 0xDC00;
const jchar Character::MAX_LOW_SURROGATE = (jchar) 0xDFFF;
const jchar Character::MIN_SURROGATE = MIN_HIGH_SURROGATE;
const jchar Character::MAX_SURROGATE = MAX_LOW_SURROGATE;

const jint Character::MIN_SUPPLEMENTARY_CODE_POINT = 0x10000;
const jint Character::MIN_CODE_POINT = 0;
const jint Character::MAX_CODE_POINT = 0x10FFFF;

const jint Character::MIN_RADIX = 2;
const jint Character::MAX_RADIX = 36;

String Character::toString(jchar c) throw ()
{
	return String(&c, 0, 1);
}

bool Character::isHighSurrogate(jchar c) throw ()
{
	return c >= MIN_HIGH_SURROGATE && c <= MAX_HIGH_SURROGATE;
}

bool Character::isLowSurrogate(jchar c) throw ()
{
	return c >= MIN_LOW_SURROGATE && c <= MAX_LOW_SURROGATE;
}

Character::Character(jchar value) throw () : _val(value)
{
}

jint Character::hashCode() const throw ()
{
	return _val;
}

jint Character::compareTo(const Character& c) const throw ()
{
	if (_val == c._val)
		return 0;
	else if (_val < c._val)
		return -1;
	else
		return 1;
}

string Character::toString() const throw ()
{
	String str(_val);
	const char* tmp = str.ByteData();
	string result(tmp);
	delete tmp;
	return result;
	
}
