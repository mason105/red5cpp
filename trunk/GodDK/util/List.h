
#ifndef _INTERFACE_GOD_UTIL_LIST_H
#define _INTERFACE_GOD_UTIL_LIST_H

#ifdef __cplusplus

#include "util/Collection.h"
#include "util/ListIterator.h"
using namespace goddk::util;

namespace goddk {
	namespace util {
		/*!\ingroup CXX_UTIL_m
		 */
		template <class E> class List : public virtual Collection<E>
		{
		public:
			virtual ~List() {}

			virtual void add(jint index, E* e) = 0;
			virtual bool addAll(jint index, const Collection<E>& c) = 0;
			virtual E* get(jint index) const throw (IndexOutOfBoundsExceptionPtr) = 0;
			virtual jint indexOf(const E* e) const = 0;
			virtual jint lastIndexOf(const E* e) const = 0;
			virtual ListIterator<E>* listIterator(jint index = 0) throw (IndexOutOfBoundsExceptionPtr) = 0;
			virtual ListIterator<E>* listIterator(jint index = 0) const throw (IndexOutOfBoundsExceptionPtr) = 0;
			virtual E* remove(jint index) = 0;
			virtual E* set(jint index, E* e) = 0;
		//	virtual List<E> subList(jint fromIndex, jint toIndex) const = 0;
		};
	}
}

#endif

#endif
