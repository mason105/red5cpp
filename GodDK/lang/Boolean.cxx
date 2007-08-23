
#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "lang/Boolean.h"
#include "lang/String.h"
using goddk::lang::String;

#include <unicode/numfmt.h>

using namespace goddk::lang;

 Boolean Boolean::VALUE_TRUE(1);
 Boolean Boolean::VALUE_FALSE(0);

String Boolean::toString(jbyte i) throw ()
{
	char tmp[12];

	#if SIZE_LONG == 4
	sprintf(tmp, "%d", i);
	#else
	sprintf(tmp, "%ld", i);
	#endif

	return String(tmp);
}

String Boolean::toHexString(jbyte i) throw ()
{
	char tmp[10];

	#if SIZEOF_LONG == 4
	sprintf(tmp, "%x", i);
	#else
	sprintf(tmp, "%lx", i);
	#endif

	return String(tmp);
}

String Boolean::toOctalString(jbyte i) throw ()
{
	char tmp[13];

	#if SIZEOF_INT == 4
	sprintf(tmp, "%o", i);
	#else
	sprintf(tmp, "%lo", i);
	#endif

	return String(tmp);
}

jbyte Boolean::parseBoolean(const String& s) throw (NumberFormatExceptionPtr)
{
	UErrorCode status = U_ZERO_ERROR;

	NumberFormat* nf = NumberFormat::createInstance(status);

	if (nf)
	{
		Formattable fmt((int32_t) 0);

		nf->parse(s.toUnicodeString(), fmt, status);

		delete nf;

		if (U_FAILURE(status))
			THROWEXCEPTIONPTR1(NumberFormatException, "unable to parse string to jint value");

		return fmt.getLong();
	}
	else
		THROWEXCEPTIONPTR1(RuntimeException,"unable to create ICU NumberFormat instance");
}

Boolean::Boolean(jbyte value) throw () : _val(value)
{
}

Boolean::Boolean(const String& s) throw (NumberFormatExceptionPtr) : _val(parseBoolean(s))
{
}

jint Boolean::hashCode() const throw ()
{
	return _val;
}

jbyte Boolean::byteValue() const throw ()
{
	return  _val;
}

jshort Boolean::shortValue() const throw ()
{
	return (jshort) _val;
}

jint Boolean::intValue() const throw ()
{
	return (jint)_val;
}

jlong Boolean::longValue() const throw ()
{
	return (jlong) _val;
}
jfloat Boolean::floatValue() const throw ()
{
	return (jfloat)_val;
}
jdouble Boolean::doubleValue() const throw ()
{
	return (jdouble)_val;
}
jint Boolean::compareTo(const Boolean& i) const throw ()
{
	if (_val == i._val)
		return 0;
	else if (_val < i._val)
		return -1;
	else
		return 1;
}
bool Boolean::instanceof(const char* class_name)const throw()
{
	if(String("Boolean").compareTo(class_name) == 0)
		return true;
	else
		return __super::instanceof(class_name);
}
bool Boolean::equals(const ObjectImpl* obj) const throw ()
{
	if(__super::equals(obj))
		return true;
	if(!obj->instanceof("Boolean"))
		return false;
	const Boolean *p = dynamic_cast<const Boolean*>(obj);
	if(p->_val == this->_val)
		return true;
	else
		return false;
}
string Boolean::toString() const throw ()
{
	char tmp[12];

	#if SIZE_LONG == 4
	sprintf(tmp, "%d", _val);
	#else
	sprintf(tmp, "%ld", _val);
	#endif

	return string(tmp);
}
Boolean* Boolean::valueOf(jbyte value) throw ()
{
	return new Boolean(value);
}
