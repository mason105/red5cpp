
#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "lang/Float.h"
#include "lang/String.h"
using goddk::lang::String;

#include <unicode/numfmt.h>

using namespace goddk::lang;

const jfloat Float::MIN_VALUE = (((jint) 1) << 31);
const jfloat Float::MAX_VALUE = ~(((jint) 1) << 31);

String Float::toString(jfloat i) throw ()
{
	char tmp[12];

	#if SIZE_LONG == 4
	sprintf(tmp, "%f", i);
	#else
	sprintf(tmp, "%d", i);
	#endif

	return String(tmp);
}

String Float::toHexString(jfloat i) throw ()
{
	char tmp[10];

	#if SIZEOF_LONG == 4
	sprintf(tmp, "%x", i);
	#else
	sprintf(tmp, "%x", i);
	#endif

	return String(tmp);
}

String Float::toOctalString(jfloat i) throw ()
{
	char tmp[13];

	#if SIZEOF_INT == 4
	sprintf(tmp, "%o", i);
	#else
	sprintf(tmp, "%o", i);
	#endif

	return String(tmp);
}

jfloat Float::parseFloat(const String& s) throw (NumberFormatExceptionPtr)
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

Float::Float(jfloat value) throw () : _val(value)
{
}

Float::Float(const String& s) throw (NumberFormatExceptionPtr) : _val(parseFloat(s))
{
}

jint Float::hashCode() const throw ()
{
	return _val;
}

jbyte Float::byteValue() const throw ()
{
	return (jbyte) _val;
}

jshort Float::shortValue() const throw ()
{
	return (jshort) _val;
}

jint Float::intValue() const throw ()
{
	return _val;
}

jlong Float::longValue() const throw ()
{
	return (jlong) _val;
}
jfloat Float::floatValue() const throw ()
{
	return (jfloat)_val;
}
jdouble Float::doubleValue() const throw ()
{
	return (jdouble)_val;
}
jint Float::compareTo(const Float& i) const throw ()
{
	if (_val == i._val)
		return 0;
	else if (_val < i._val)
		return -1;
	else
		return 1;
}
bool Float::instanceof(const char* class_name)const throw()
{
	if(String("Float").compareTo(class_name) == 0)
		return true;
	else
		return __super::instanceof(class_name);
}
bool Float::equals(const ObjectImpl* obj) const throw ()
{
	if(__super::equals(obj))
		return true;
	if(!obj->instanceof("Float"))
		return false;
	const Float *p = dynamic_cast<const Float*>(obj);
	if(p->_val == this->_val)
		return true;
	else
		return false;
}
string Float::toString() const throw ()
{
	char tmp[12];

	#if SIZE_LONG == 4
	sprintf(tmp, "%f", _val);
	#else
	sprintf(tmp, "%d", _val);
	#endif

	return string(tmp);
}
Float* Float::valueOf(jfloat value) throw ()
{
	return new Float(value);
}
