
#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "nio/ByteOrder.h"

using namespace goddk::nio;

ByteOrder::ByteOrder(const String& name) : _name(name)
{
}

const ByteOrder ByteOrder::BIG_ENDIAN("BIG_ENDIAN");
const ByteOrder ByteOrder::LITTLE_ENDIAN("LITTLE_ENDIAN");

const ByteOrder& ByteOrder::nativeOrder()
{
	#if WORDS_BIGENDIAN
	return BIG_ENDIAN;
	#else
	return LITTLE_ENDIAN;
	#endif
}

string ByteOrder::toString() const throw ()
{
	
	return "";
}
