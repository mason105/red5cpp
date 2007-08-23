

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "lang/Double.h"
#include "lang/String.h"
using goddk::lang::String;

#include <unicode/numfmt.h>

using namespace goddk::lang;

const jdouble Double::MIN_VALUE = (((jlong) 1) << 63);
const jdouble Double::MAX_VALUE = ~(((jlong) 1) << 63);

String Double::toString(jdouble i) throw ()
{
	char tmp[21];

	#if SIZE_LONG == 4
	sprintf(tmp, "%f", i);
	#else
	sprintf(tmp, "%f", i);
	#endif

	return String(tmp);
}

String Double::toHexString(jdouble i) throw ()
{
	char tmp[18];

	#if SIZEOF_LONG == 4
	sprintf(tmp, "%x", i);
	#else
	sprintf(tmp, "%x", i);
	#endif

	return String(tmp);
}

String Double::toOctalString(jdouble i) throw ()
{
	char tmp[23];

	#if SIZEOF_INT == 4
	sprintf(tmp, "%o", i);
	#else
	sprintf(tmp, "%o", i);
	#endif

	return String(tmp);
}

jdouble Double::parseDouble(const String& s) throw (NumberFormatExceptionPtr)
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

		return fmt.getDouble();
	}
	else
		THROWEXCEPTIONPTR1(RuntimeException,"unable to create ICU NumberFormat instance");
}

Double::Double(jdouble value) throw () : _val(value)
{
}

Double::Double(const String& s) throw (NumberFormatExceptionPtr) : _val(parseDouble(s))
{
}

jint Double::hashCode() const throw ()
{
	return _val;
}

jbyte Double::byteValue() const throw ()
{
	return  _val;
}

jshort Double::shortValue() const throw ()
{
	return (jshort) _val;
}

jint Double::intValue() const throw ()
{
	return (jint)_val;
}

jlong Double::longValue() const throw ()
{
	return (jlong) _val;
}
jfloat Double::floatValue() const throw ()
{
	return (jfloat)_val;
}
jdouble Double::doubleValue() const throw ()
{
	return (jdouble)_val;
}
jint Double::compareTo(const Double& i) const throw ()
{
	if (_val == i._val)
		return 0;
	else if (_val < i._val)
		return -1;
	else
		return 1;
}
bool Double::instanceof(const char* class_name)const throw()
{
	if(String("Double").compareTo(class_name) == 0)
		return true;
	else
		return __super::instanceof(class_name);
}
bool Double::equals(const ObjectImpl* obj) const throw ()
{
	if(__super::equals(obj))
		return true;
	if(!obj->instanceof("Double"))
		return false;
	const Double *p = dynamic_cast<const Double*>(obj);
	if(p->_val == this->_val)
		return true;
	else
		return false;
}
string Double::toString() const throw ()
{
	char tmp[12];

	#if SIZE_LONG == 4
	sprintf(tmp, "%f", _val);
	#else
	sprintf(tmp, "%f", _val);
	#endif

	return string(tmp);
}
Double* Double::valueOf(jdouble value) throw ()
{
	return new Double(value);
}
