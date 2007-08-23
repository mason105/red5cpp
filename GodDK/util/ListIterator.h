
#ifndef _INTERFACE_GOD_UTIL_LISTITERATOR_H
#define _INTERFACE_GOD_UTIL_LISTITERATOR_H

#ifdef __cplusplus

#include "util/Iterator.h"
using namespace goddk::util;

namespace goddk {
	namespace util {
		/*!\ingroup CXX_UTIL_m
		 */
		template<class E> class ListIterator : public virtual Iterator<E>
		{
		public:
			virtual void add(E* e) = 0;
			virtual bool hasNext() throw () = 0;
			virtual bool hasPrevious() throw () = 0;
			virtual E* next() throw (NoSuchElementExceptionPtr) = 0;
			virtual int nextIndex() throw () = 0;
			virtual E* previous() throw (NoSuchElementExceptionPtr) = 0;
			virtual int previousIndex() throw () = 0;
			virtual void remove() = 0;
			virtual void set(E* e) = 0;
		};
	}
}

#endif

#endif
