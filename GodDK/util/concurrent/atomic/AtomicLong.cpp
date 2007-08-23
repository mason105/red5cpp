#include ".\atomiclong.h"
namespace goddk {
	namespace util {
		namespace concurrent {
			namespace Atomic{
				AtomicLong::AtomicLong()
				{
					value = 0;
					valueOffset = value;
				}

				AtomicLong::AtomicLong(jlong initialValue)
				{
					value = initialValue;
					valueOffset = value;
				}

				AtomicLong::~AtomicLong(void)
				{
				}
			}
		}
	}
}