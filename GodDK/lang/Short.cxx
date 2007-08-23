

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "lang/Short.h"
#include "lang/String.h"
using goddk::lang::String;

#include <unicode/numfmt.h>

using namespace goddk::lang;

const jint Short::MIN_VALUE = (((jint) 1) << 31);
const jint Short::MAX_VALUE = ~MIN_VALUE;

String Short::toString(jshort i) throw ()
{
	char tmp[12];

	#if SIZE_LONG == 4
	sprintf(tmp, "%d", i);
	#else
	sprintf(tmp, "%ld", i);
	#endif

	return String(tmp);
}

String Short::toHexString(jshort i) throw ()
{
	char tmp[10];

	#if SIZEOF_LONG == 4
	sprintf(tmp, "%x", i);
	#else
	sprintf(tmp, "%lx", i);
	#endif

	return String(tmp);
}

String Short::toOctalString(jshort i) throw ()
{
	char tmp[13];

	#if SIZEOF_INT == 4
	sprintf(tmp, "%o", i);
	#else
	sprintf(tmp, "%lo", i);
	#endif

	return String(tmp);
}

jshort Short::parseShort(const String& s) throw (NumberFormatExceptionPtr)
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

Short::Short(jshort value) throw () : _val(value)
{
}

Short::Short(const String& s) throw (NumberFormatExceptionPtr) : _val(parseShort(s))
{
}

jint Short::hashCode() const throw ()
{
	return _val;
}

jbyte Short::byteValue() const throw ()
{
	return (jbyte) _val;
}

jshort Short::shortValue() const throw ()
{
	return (jshort) _val;
}

jint Short::intValue() const throw ()
{
	return _val;
}

jlong Short::longValue() const throw ()
{
	return (jlong) _val;
}
jfloat Short::floatValue() const throw ()
{
	return (jfloat)_val;
}
jdouble Short::doubleValue() const throw ()
{
	return (jdouble)_val;
}
jint Short::compareTo(const Short& i) const throw ()
{
	if (_val == i._val)
		return 0;
	else if (_val < i._val)
		return -1;
	else
		return 1;
}
bool Short::instanceof(const char* class_name)const throw()
{
	if(String("Short").compareTo(class_name) == 0)
		return true;
	else
		return __super::instanceof(class_name);
}
bool Short::equals(const ObjectImpl* obj) const throw ()
{
	if(__super::equals(obj))
		return true;
	if(!obj->instanceof("Short"))
		return false;
	const Short *p = dynamic_cast<const Short*>(obj);
	if(p->_val == this->_val)
		return true;
	else
		return false;
}
string Short::toString() const throw ()
{
	char tmp[12];

	#if SIZE_LONG == 4
	sprintf(tmp, "%d", _val);
	#else
	sprintf(tmp, "%ld", _val);
	#endif

	return string(tmp);
}
Short* Short::valueOf(jshort value) throw ()
{
	return new Short(value);
}
