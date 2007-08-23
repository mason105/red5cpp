

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "lang/String.h"
#include "lang/Character.h"
#include "lang/Integer.h"
#include "lang/Long.h"

using namespace goddk::lang;

#include <assert.h>
#include <unicode/ustdio.h>
#include <unicode/ustring.h>

String::String(array<jchar>& swapWith)
{
	assert(swapWith.size() <= Integer::MAX_VALUE);

	_value.swap(swapWith);
}

String::String(const array<jchar>& lhs, const array<jchar>& rhs) : _value(lhs.size() + rhs.size())
{
	assert(_value.size() <= Integer::MAX_VALUE);

	if (lhs.size())
		memcpy(_value.data(), lhs.data(), lhs.size() * sizeof(jchar));
	if (rhs.size())
		memcpy(_value.data() + lhs.size(), rhs.data(), rhs.size() * sizeof(jchar));
}

String::String()
{
}

String::String(char c) : _value(1)
{
	u_charsToUChars(&c, _value.data(), 1);
}

String::String(jchar c) : _value(&c, 1)
{
}

String::String(const char* value) : _value(::strlen(value))
{
	assert(_value.size() <= Integer::MAX_VALUE);

	u_charsToUChars(value, _value.data(), _value.size());
}

String::String(const jchar* value, int offset, int length) : _value(value+offset, length)
{
	assert(_value.size() <= Integer::MAX_VALUE);
}

String::String(const array<jchar>& copy) : _value(copy)
{
	assert(_value.size() <= Integer::MAX_VALUE);
}

String::String(const String& copy) : _value(copy._value)
{
	assert(_value.size() <= Integer::MAX_VALUE);
}

String::String(const UnicodeString& copy) : _value((int) copy.length())
{
	assert(_value.size() <= Integer::MAX_VALUE);

	copy.extract(0, copy.length(), _value.data());
}
array<char>* String::toByteArray()  throw ()
{
	UErrorCode status = U_ZERO_ERROR;
	UConverter* loc;

	loc = ucnv_open(0, &status);
	if (U_FAILURE(status))
		THROWEXCEPTIONPTR1(RuntimeException,"ucnv_open failed");

	int need = ucnv_fromUChars(loc, 0, 0, _value.data(), _value.size(), &status);
	if (U_FAILURE(status))
		if (status != U_BUFFER_OVERFLOW_ERROR)
			THROWEXCEPTIONPTR1(RuntimeException,"ucnv_fromUChars failed");

	char* out = new char[need+1];
	memset(out, 0, need+1);

	status = U_ZERO_ERROR;

	ucnv_fromUChars(loc, out, need+1, _value.data(), _value.size(), &status);
	if (U_FAILURE(status))
		THROWEXCEPTIONPTR1(RuntimeException,"ucnv_fromUChars failed");


	ucnv_close(loc);

	array<char>* result = new array<char>(strlen(out));
	memcpy(result->data(), out, strlen(out));
	delete out;
	return result;
}
const char*	 String::ByteData() throw()
{

	UErrorCode status = U_ZERO_ERROR;
	UConverter* loc;

	loc = ucnv_open(0, &status);
	if (U_FAILURE(status))
		THROWEXCEPTIONPTR1(RuntimeException,"ucnv_open failed");

	int need = ucnv_fromUChars(loc, 0, 0, _value.data(), _value.size(), &status);
	if (U_FAILURE(status))
		if (status != U_BUFFER_OVERFLOW_ERROR)
			THROWEXCEPTIONPTR1(RuntimeException,"ucnv_fromUChars failed");

	char* out = new char[need+1];
	memset(out, 0, need+1);

	status = U_ZERO_ERROR;

	ucnv_fromUChars(loc, out, need+1, _value.data(), _value.size(), &status);
	if (U_FAILURE(status))
		THROWEXCEPTIONPTR1(RuntimeException,"ucnv_fromUChars failed");


	ucnv_close(loc);

	return out;
}
String& String::operator=(const String& copy)
{
	_value = copy._value;

	assert(_value.size() <= Integer::MAX_VALUE);

	return *this;
}

int String::compareTo(const String& str) const throw ()
{
	int result;

	register int tlen = _value.size(), alen = str._value.size(), min;

	if (tlen < alen)
	{
		min = tlen;
		result = -1;
	}
	else if (tlen > alen)
	{
		min = alen;
		result = 1;
	}
	else
	{
		min = tlen;
		result = 0;
	}

	if (min > 0)
	{
		register const jchar *tdata = _value.data(), *adata = str._value.data();
		register int tmp;

		do
		{
			tmp = (int) *(tdata++) - (int) *(adata++);
			if (tmp)
				return tmp;
		} while (--min > 0);
	}

	return result;
}

jchar String::charAt(int index) const throw ()
{
	if ((index < 0) || (index >= _value.size()))
		THROWEXCEPTIONPTR(IndexOutOfBoundsException);

	return _value[index];
}

int String::compareToIgnoreCase(const String& str) const throw ()
{
	return toUnicodeString().caseCompare(str.toUnicodeString(), 0);
}

String String::concat(const String& str) const throw ()
{
	return String(_value, str._value);
}

bool String::contains(const CharSequence& seq) const throw ()
{
	return indexOf(String(seq.toString().c_str())) >= 0;
}

bool String::contentEquals(const CharSequence& seq) const throw ()
{
	register int tlen = _value.size();

	if (tlen != seq.length())
		return false;

	for (int i = 0; i < tlen; i++)
		if (_value[i] != seq.charAt(i))
			return false;

	return true;
}

bool String::endsWith(const String& suffix) const throw ()
{
	register int tlen = _value.size(), slen = suffix._value.size();

	if (slen > tlen)
		return false;

	const jchar *tdata = _value.data() + tlen - slen, *sdata = suffix._value.data();

	while (slen > 0)
	{
		if (*(tdata++) != *(sdata++))
			return false;
		slen--;
	}

	return true;
}

bool String::equals(const ObjectImpl* obj) const throw ()
{
	if (this == obj)
		return true;

	if (obj)
	{
		const String* s = dynamic_cast<const String*>(obj);
		if (s)
			return compareTo(*s) == 0;
	}

	return false;
}

bool String::equals(const String& str) const throw ()
{
	return compareTo(str) == 0;
}

bool String::equalsIgnoreCase(const String& str) const throw ()
{
	if (this == &str)
		return true;

	return compareToIgnoreCase(str) == 0;
}

int String::indexOf(int ch, int fromIndex) const throw ()
{
	if (ch < 0)
		return -1;

	if ((fromIndex < 0) || (fromIndex >= _value.size()))
		return -1;

	if (ch < Character::MIN_SUPPLEMENTARY_CODE_POINT)
	{	// it's a regular jchar
		for (int i = fromIndex; i < _value.size(); i++)
			if (_value[i] == ch)
				return i;
		return -1;
	}

	/*!\todo
	if (ch <= 0x10ffff)
	{	// convert this to two jchars
	}
	*/

	return -1;
}
int String::lastIndexOf(int ch, int fromIndex) const throw ()
{
	if (ch < 0)
		return -1;

	if ((fromIndex < 0) || (fromIndex >= _value.size()))
		return -1;

	int index = -1;
	if (ch < Character::MIN_SUPPLEMENTARY_CODE_POINT)
	{	// it's a regular jchar
		for (int i = fromIndex; i < _value.size(); i++)
			if (_value[i] == ch)
				 index = i;
		return index;
	}

	return index;
}

int String::indexOf(const String& str, int fromIndex) const throw ()
{
	register int tlen = _value.size(), slen = str._value.size();

	assert(tlen <= Integer::MAX_VALUE);

	if (fromIndex >= tlen)
		return (slen == 0) ? (int) tlen : -1;

	assert(fromIndex <= Integer::MAX_VALUE);

	if (slen == 0)
		return fromIndex;

	int max = tlen - slen;

	for (int i = fromIndex; i <= max; i++)
	{
		// find the first character
		while (_value[i] != str._value[0])
		{
			if (i < max)
				i++;
			else
				return -1;
		}

		// find the rest
		int j = i + 1;
		int last = i + slen;
		for (int k = 1; (j < last) && _value[j] == str._value[k]; j++, k++);

		if (j == last)
			return i;
	}

	return -1;
}

jint String::hashCode() const throw ()
{
	register jint result = 0;

	for (int i = 0; i < _value.size(); i++)
		result = (result * 31) + _value[i];

	return result;
}

int String::length() const throw ()
{
	return _value.size();
}

bool String::startsWith(const String& prefix, int offset) const throw ()
{
	register int tlen = _value.size(), plen = prefix._value.size();

	assert(offset <= Integer::MAX_VALUE);

	if (offset + plen > tlen)
		return false;

	const jchar *tdata = _value.data() + offset, *pdata = prefix._value.data();

	while (plen > 0)
	{
		if (*(tdata++) != *(pdata++))
			return false;
		plen--;
	}

	return true;
}

CharSequence* String::subSequence(int beginIndex, int endIndex) const throw (IndexOutOfBoundsExceptionPtr)
{
	assert(beginIndex <= Integer::MAX_VALUE);
	assert(endIndex <= Integer::MAX_VALUE);

	if (beginIndex > endIndex || endIndex > _value.size())
		THROWEXCEPTIONPTR(IndexOutOfBoundsException);

	if (beginIndex == 0 && endIndex == _value.size())
		return new String(*this);
	else
		return new String(_value.data(), beginIndex, endIndex - beginIndex);
}

String String::substring(int beginIndex) const throw (IndexOutOfBoundsExceptionPtr)
{
	assert(beginIndex <= Integer::MAX_VALUE);

	if (beginIndex > _value.size())
		THROWEXCEPTIONPTR(IndexOutOfBoundsException);

	if (beginIndex == 0)
		return *this;
	else
		return String(_value.data(), beginIndex, _value.size() - beginIndex);
}

String String::substring(int beginIndex, int endIndex) const throw (IndexOutOfBoundsExceptionPtr)
{
	assert(beginIndex <= Integer::MAX_VALUE);
	assert(endIndex <= Integer::MAX_VALUE);

	if (beginIndex > endIndex || endIndex > _value.size())
		THROWEXCEPTIONPTR(IndexOutOfBoundsException);

	if (beginIndex == 0 && endIndex == _value.size())
		return *this;
	else
		return String(_value.data(), beginIndex, endIndex - beginIndex);
}

const array<jchar>& String::toCharArray() const throw ()
{
	return _value;
}

String String::toLowerCase() const throw ()
{
	return String(toUnicodeString().toLower());
}

String String::toUpperCase() const throw ()
{
	return String(toUnicodeString().toUpper());
}
String String::trim()
{
	return String(toUnicodeString().trim());
}
string String::toString() const throw ()
{	
	String sss(*this);
	const char* tmp = sss.ByteData();
	string str(tmp);
	delete tmp;
	return str;
}

UnicodeString String::toUnicodeString() const throw ()
{
	return UnicodeString(_value.data(), (int32_t) _value.size());
}

String String::valueOf(bool b)
{
	if (b)
		return String("true");
	else
		return String("false");
}

String String::valueOf(jint i)
{
	return Integer::toString(i);
}

String String::valueOf(jlong l)
{
	return Long::toString(l);
}

String goddk::lang::operator+(const String& s1, const String& s2)
{
	return s1.concat(s2);
}

bool goddk::lang::operator<(const String& s1, const String& s2)
{
	return (s1.compareTo(s2) < 0);
}

std::ostream& goddk::lang::operator<<(std::ostream& stream, const String* str)
{
	if (str)
		return stream << (*str);
	else
		return stream << "null";
}

std::ostream& goddk::lang::operator<<(std::ostream& stream, const String& str)
{
	const array<jchar>& src = str.toCharArray();

	if (src.size())
	{
		UErrorCode status = U_ZERO_ERROR;
		UConverter* loc;

		loc = ucnv_open(0, &status);
		if (U_FAILURE(status))
			THROWEXCEPTIONPTR1(RuntimeException,"ucnv_open failed");

		int need = ucnv_fromUChars(loc, 0, 0, src.data(), src.size(), &status);
		if (U_FAILURE(status))
			if (status != U_BUFFER_OVERFLOW_ERROR)
				THROWEXCEPTIONPTR1(RuntimeException,"ucnv_fromUChars failed");

		char* out = new char[need+1];

		status = U_ZERO_ERROR;

		ucnv_fromUChars(loc, out, need+1, src.data(), src.size(), &status);
		if (U_FAILURE(status))
			THROWEXCEPTIONPTR1(RuntimeException,"ucnv_fromUChars failed");

		stream << out;

		delete[] out;

		ucnv_close(loc);
	}

	return stream;
}
array<String*>  String::split(jint ch)
{
	UErrorCode status = U_ZERO_ERROR;
	UConverter* loc;

	loc = ucnv_open(0, &status);
	if (U_FAILURE(status))
		THROWEXCEPTIONPTR1(RuntimeException,"ucnv_open failed");

	int need = ucnv_fromUChars(loc, 0, 0, _value.data(), _value.size(), &status);
	if (U_FAILURE(status))
		if (status != U_BUFFER_OVERFLOW_ERROR)
			THROWEXCEPTIONPTR1(RuntimeException,"ucnv_fromUChars failed");



	array<String*>  as;
	char* tmp = new char[need+1];
	memset(tmp, 0, need+1);
	char* tmp1 = new char[need+1];
	memset(tmp1, 0, need+1);

	status = U_ZERO_ERROR;
	ucnv_fromUChars(loc, tmp, need+1, _value.data(), _value.size(), &status);
	if (U_FAILURE(status))
		THROWEXCEPTIONPTR1(RuntimeException,"ucnv_fromUChars failed");
	ucnv_close(loc);

	int k = 0;
	for(int i = 0; i < strlen(tmp); i ++)
	{
		if(tmp[i] == ch)
		{
			tmp1[k] = 0;
			as.add(new String(tmp1));
			k = 0;
		}
		else
		{
			tmp1[k] = tmp[i];
			k ++;
		}
	}
	if(k != 0)
	{
		tmp1[k] = 0;
		as.add(new String(tmp1));
	}

	delete tmp;
	delete tmp1;

	return as;
}