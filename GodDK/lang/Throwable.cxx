

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif


#include "lang/Throwable.h"
#include "lang/String.h"
#include "lang/IllegalStateException.h"
using namespace goddk::lang;

Throwable::Throwable() : _msg(0)
{
	printf("exception\n");
	_ref_count = 1;
	_cause = this;
}

Throwable::Throwable(const char* message) : _msg(message ? new String(message) : 0)
{
	printf("exception\n");
	_ref_count = 1;
	_cause = this;
}

Throwable::Throwable(const String* message) : _msg(message ? new String(*message) : 0)
{
	printf("exception\n");
	_ref_count = 1;
	_cause = this;
}

Throwable::Throwable(const String* message, const Throwable* cause) : _msg(message ? new String(*message) : 0), _cause(cause)
{
	printf("exception\n");
	_ref_count = 1;
}

Throwable::Throwable(const Throwable* cause) : _cause(cause)
{
	printf("exception\n");
	_ref_count = 1;
	if (_cause && _cause->_msg)
		_msg = new String(*_cause->_msg);
	else
		_msg = 0;
}

Throwable::~Throwable()
{
	if(_msg)
		collection_detach(_msg);
	_msg = 0;
}

const String* Throwable::getMessage() const throw ()
{
	if(_msg)
		collection_attach(_msg);
	return _msg;
}

const Throwable* Throwable::getCause() const throw ()
{
	return _cause;
}

Throwable& Throwable::initCause(const Throwable& cause)
{
	if (_cause)
		throw IllegalStateException("cause was already specified");

	_cause = &cause;

	return *this;
}
