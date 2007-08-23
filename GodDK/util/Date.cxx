


#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "timestamp.h"
#include "util/Date.h"
#include "lang/NullPointerException.h"
using goddk::lang::NullPointerException;

#include <unicode/datefmt.h>

namespace {
	#if WIN32
	__declspec(thread) DateFormat* format = 0;
	#else
	__thread DateFormat* format = 0;
	#endif
}

using namespace goddk::util;

Date::Date() throw ()
{
	_time = timestamp();
}

Date::Date(jlong time) throw ()
{
	_time = time;
}

bool Date::equals(const ObjectImpl* obj) const throw ()
{
	if (this == obj)
		return true;

	if (obj)
	{
		const Date* d = dynamic_cast<const Date*>(obj);
		if (d)
			return _time == d->_time;
	}

	return false;
}

bool Date::equals(const Date& d) const throw ()
{
	return _time == d._time;
}

Object* Date::clone() const throw ()
{
	return (Object*)new Date(_time);
}

jint Date::compareTo(const Date& d) const throw ()
{
	if (_time == d._time)
		return 0;
	else if (_time < d._time)
		return -1;
	else
		return 1;
}

jint Date::hashCode() const throw ()
{
	return (jint) _time ^ (jint)(_time >> 32);
}

bool Date::after(const Date& cmp) const throw ()
{
	return _time > cmp._time;
}

bool Date::before(const Date& cmp) const throw ()
{
	return _time < cmp._time;
}

jlong Date::getTime() const throw ()
{
	return _time;
}

void Date::setTime(jlong time) throw ()
{
	_time = time;
}

string Date::toString() const throw ()
{
	if (!format)
		format = DateFormat::createDateTimeInstance();
	if(!format)
		THROWEXCEPTIONPTR1(NullPointerException,"");

	UnicodeString tmp;
	String str(format->format((UDate) _time, tmp));
	
	delete format;
	format = 0;

	return str.toString();
}
