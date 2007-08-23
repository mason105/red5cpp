

#ifndef _CLASS_GOD_NIO_BYTEORDER_H
#define _CLASS_GOD_NIO_BYTEORDER_H

#ifdef __cplusplus

#include "lang/String.h"
using namespace goddk::lang;

#ifdef BIG_ENDIAN
# undef BIG_ENDIAN
#endif
#ifdef LITTLE_ENDIAN
# undef LITTLE_ENDIAN
#endif

namespace goddk {
	namespace nio {
		class  ByteOrder : public Object
		{
		private:
			String _name;

			ByteOrder(const String& name);

		public:
			static const ByteOrder BIG_ENDIAN;
			static const ByteOrder LITTLE_ENDIAN;

			static const ByteOrder& nativeOrder();

		public:
			virtual ~ByteOrder() {}

			virtual string toString() const throw ();
		};
		typedef CSmartPtr<ByteOrder>		ByteOrderPtr;
	}
}

#endif

#endif
