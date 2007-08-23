#include ".\atomicinteger.h"
namespace goddk {
	namespace util {
		namespace concurrent {
			namespace Atomic{
AtomicInteger::AtomicInteger()
{
	value = 0;
	valueOffset = value;
}

AtomicInteger::AtomicInteger(jint initialValue)
{
	value = initialValue;
	valueOffset = value;
}

AtomicInteger::~AtomicInteger(void)
{
}
			}
		}
	}
}