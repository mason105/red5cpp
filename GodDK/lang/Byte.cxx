
#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "lang/Byte.h"
#include "lang/String.h"
using goddk::lang::String;

#include <unicode/numfmt.h>

using namespace goddk::lang;


String Byte::toString(jbyte i) throw ()
{
	char tmp[12];

	#if SIZE_LONG == 4
	sprintf(tmp, "%d", i);
	#else
	sprintf(tmp, "%ld", i);
	#endif

	return String(tmp);
}

String Byte::toHexString(jbyte i) throw ()
{
	char tmp[10];

	#if SIZEOF_LONG == 4
	sprintf(tmp, "%x", i);
	#else
	sprintf(tmp, "%lx", i);
	#endif

	return String(tmp);
}

String Byte::toOctalString(jbyte i) throw ()
{
	char tmp[13];

	#if SIZEOF_INT == 4
	sprintf(tmp, "%o", i);
	#else
	sprintf(tmp, "%lo", i);
	#endif

	return String(tmp);
}

jbyte Byte::parseByte(const String& s) throw (NumberFormatExceptionPtr)
{
	UErrorCode status = U_ZERO_ERROR;

	NumberFormat* nf = NumberFormat::createInstance(status);

	if (nf)
	{
		Formattable fmt((int32_t) 0);

		nf->parse(s.toUnicodeString(), fmt, status);

		delete nf;

		if (U_FAILURE(status))
			THROWEXCEPTIONPTR1(NumberFormatException,"unable to parse string to jint value");

		return fmt.getLong();
	}
	else
		THROWEXCEPTIONPTR1(RuntimeException,"unable to create ICU NumberFormat instance");
}

Byte::Byte(jbyte value) throw () : _val(value)
{
}

Byte::Byte(const String& s) throw (NumberFormatExceptionPtr) : _val(parseByte(s))
{
}

jint Byte::hashCode() const throw ()
{
	return _val;
}

jbyte Byte::byteValue() const throw ()
{
	return  _val;
}

jshort Byte::shortValue() const throw ()
{
	return (jshort) _val;
}

jint Byte::intValue() const throw ()
{
	return (jint)_val;
}

jlong Byte::longValue() const throw ()
{
	return (jlong) _val;
}
jfloat Byte::floatValue() const throw ()
{
	return (jfloat)_val;
}
jdouble Byte::doubleValue() const throw ()
{
	return (jdouble)_val;
}
jint Byte::compareTo(const Byte& i) const throw ()
{
	if (_val == i._val)
		return 0;
	else if (_val < i._val)
		return -1;
	else
		return 1;
}
bool Byte::instanceof(const char* class_name)const throw()
{
	if(String("Byte").compareTo(class_name) == 0)
		return true;
	else
		return __super::instanceof(class_name);
}
bool Byte::equals(const ObjectImpl* obj) const throw ()
{
	if(__super::equals(obj))
		return true;
	if(!obj->instanceof("Byte"))
		return false;
	const Byte *p = dynamic_cast<const Byte*>(obj);
	if(p->_val == this->_val)
		return true;
	else
		return false;
}
string Byte::toString() const throw ()
{
	char tmp[12];

	#if SIZE_LONG == 4
	sprintf(tmp, "%d", _val);
	#else
	sprintf(tmp, "%ld", _val);
	#endif

	return string(tmp);
}
Byte* Byte::valueOf(jbyte value) throw ()
{
	return new Byte(value);
}
