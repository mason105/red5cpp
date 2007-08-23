
#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "lang/Long.h"
#include "lang/String.h"
using goddk::lang::String;

#include <unicode/numfmt.h>

using namespace goddk::lang;

const jlong Long::MIN_VALUE = (((jlong) 1) << 63);
const jlong Long::MAX_VALUE = ~MIN_VALUE;

String Long::toString(jlong l) throw ()
{
	char tmp[21];

	#if WIN32
	sprintf(tmp, "%I64d", l);
	#elif SIZE_LONG == 8
	sprintf(tmp, "%ld", l);
	#elif HAVE_LONG_LONG
	sprintf(tmp, "%lld", l);
	#else
	# error
	#endif

	return String(tmp);
}

String Long::toHexString(jlong l) throw ()
{
	char tmp[18];

	#if WIN32
	sprintf(tmp, "%I64x", l);
	#elif SIZEOF_LONG == 8
	sprintf(tmp, "%lx", l);
	#elif HAVE_LONG_LONG
	sprintf(tmp, "%llx", l);
	#else
	# error
	#endif

	return String(tmp);
}

String Long::toOctalString(jlong l) throw ()
{
	char tmp[23];

	#if WIN32
	sprintf(tmp, "%I64o", l);
	#elif SIZEOF_LONG == 8
	sprintf(tmp, "%lo", l);
	#elif HAVE_LONG_LONG
	sprintf(tmp, "%llo", l);
	#else
	# error
	#endif

	return String(tmp);
}

jlong Long::parseLong(const String& s) throw (NumberFormatExceptionPtr)
{
	UErrorCode status = U_ZERO_ERROR;

	NumberFormat* nf = NumberFormat::createInstance(status);

	if (nf)
	{
		Formattable fmt((int64_t) 0);

		nf->parse(s.toUnicodeString(), fmt, status);

		delete nf;

		if (U_FAILURE(status))
			THROWEXCEPTIONPTR1(NumberFormatException,"unable to parse string to jlong value");

		return fmt.getInt64();
	}
	else
		THROWEXCEPTIONPTR1(RuntimeException,"unable to create ICU NumberFormat instance");
}

Long::Long(jlong value) throw () : _val(value)
{
}

Long::Long(const String& s) throw (NumberFormatExceptionPtr) : _val(parseLong(s))
{
}

jint Long::hashCode() const throw ()
{
	return (jint) _val ^ (jint)(_val >> 32);
}

jbyte Long::byteValue() const throw ()
{
	return (jbyte) _val;
}

jshort Long::shortValue() const throw ()
{
	return (jshort) _val;
}

jint Long::intValue() const throw ()
{
	return (jint) _val;
}

jlong Long::longValue() const throw ()
{
	return _val;
}
jfloat Long::floatValue() const throw ()
{
	return (jfloat)_val;
}
jdouble Long::doubleValue() const throw ()
{
	return (jdouble)_val;
}
jint Long::compareTo(const Long& l) const throw ()
{
	if (_val == l._val)
		return 0;
	else if (_val < l._val)
		return -1;
	else
		return 1;
}
bool Long::equals(const ObjectImpl* obj) const throw ()
{
	if(__super::equals(obj))
		return true;
	if(!obj->instanceof("Long"))
		return false;
	const Long *p = dynamic_cast<const Long*>(obj);
	if(p->_val == this->_val)
		return true;
	else
		return false;
}
string Long::toString() const throw ()
{
	char tmp[21];

	#if WIN32
	sprintf(tmp, "%I64d", _val);
	#elif SIZE_LONG == 8
	sprintf(tmp, "%ld", _val);
	#elif HAVE_LONG_LONG
	sprintf(tmp, "%lld", _val);
	#else
	# error
	#endif

	return string(tmp);
}
Long* Long::valueOf(jlong value)  throw ()
{
	return new Long(value);
}