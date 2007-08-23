

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "lang/Integer.h"
#include "lang/String.h"
using goddk::lang::String;

#include <unicode/numfmt.h>

using namespace goddk::lang;

const jint Integer::MIN_VALUE = (((jint) 1) << 31);
const jint Integer::MAX_VALUE = ~MIN_VALUE;

String Integer::toString(jint i) throw ()
{
	char tmp[12];

	#if SIZE_LONG == 4
	sprintf(tmp, "%d", i);
	#else
	sprintf(tmp, "%ld", i);
	#endif

	return String(tmp);
}

String Integer::toHexString(jint i) throw ()
{
	char tmp[10];

	#if SIZEOF_LONG == 4
	sprintf(tmp, "%x", i);
	#else
	sprintf(tmp, "%lx", i);
	#endif

	return String(tmp);
}

String Integer::toOctalString(jint i) throw ()
{
	char tmp[13];

	#if SIZEOF_INT == 4
	sprintf(tmp, "%o", i);
	#else
	sprintf(tmp, "%lo", i);
	#endif

	return String(tmp);
}

jint Integer::parseInteger(const String& s) throw (NumberFormatExceptionPtr)
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

Integer::Integer(jint value) throw () : _val(value)
{
}

Integer::Integer(const String& s) throw (NumberFormatExceptionPtr) : _val(parseInteger(s))
{
}

jint Integer::hashCode() const throw ()
{
	return _val;
}

jbyte Integer::byteValue() const throw ()
{
	return (jbyte) _val;
}

jshort Integer::shortValue() const throw ()
{
	return (jshort) _val;
}

jint Integer::intValue() const throw ()
{
	return _val;
}

jlong Integer::longValue() const throw ()
{
	return (jlong) _val;
}
jfloat Integer::floatValue() const throw ()
{
	return (jfloat)_val;
}
jdouble Integer::doubleValue() const throw ()
{
	return (jdouble)_val;
}
jint Integer::compareTo(const Integer& i) const throw ()
{
	if (_val == i._val)
		return 0;
	else if (_val < i._val)
		return -1;
	else
		return 1;
}
bool Integer::instanceof(const char* class_name)const throw()
{
	if(String("Integer").compareTo(class_name) == 0)
		return true;
	else
		return __super::instanceof(class_name);
}
bool Integer::equals(const ObjectImpl* obj) const throw ()
{
	if(__super::equals(obj))
		return true;
	if(!obj->instanceof("Integer"))
		return false;
	const Integer *p = dynamic_cast<const Integer*>(obj);
	if(p->_val == this->_val)
		return true;
	else
		return false;
}
string Integer::toString() const throw ()
{
	char tmp[12];

	#if SIZE_LONG == 4
	sprintf(tmp, "%d", _val);
	#else
	sprintf(tmp, "%ld", _val);
	#endif

	return string(tmp);
}
Integer* Integer::valueOf(jint value) throw ()
{
	return new Integer(value);
}
