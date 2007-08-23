
#ifndef _INTERFACE_GOD_UTIL_QUEUE_H
#define _INTERFACE_GOD_UTIL_QUEUE_H

#ifdef __cplusplus

#include "util/Collection.h"
#include "util/ArrayList.h"
using namespace goddk::util;

namespace goddk {
	namespace util {
		/*!\ingroup CXX_UTIL_m
		 */
		template<class E> class Queue : public virtual Collection<E>
		{
		public:
			virtual E* element() = 0;
			virtual bool offer(E*) = 0;
			virtual E* peek() = 0;
			virtual E* poll() = 0;
			virtual E* remove(jint index = 0) throw (IndexOutOfBoundsExceptionPtr) = 0;
		};

		template<class E> class LinkedList :
		public virtual ArrayList<E>, 
			public virtual Queue<E>
		{
		public:
			bool instanceof(const char* class_name)const throw()
			{
				if(strcmp("LinkedList", class_name)== 0)
					return true;
				else if(strcmp("Queue", class_name)== 0)
					return true;
				else
					return ArrayList<E>::instanceof(class_name);
			}
			virtual E* element()
			{
				if(size() == 0)
					return 0;
				return get(0);
			}
			virtual bool offer(E* e)
			{
				return add(e);
			}
			virtual E* peek()
			{
				return element();
			}
			virtual E* poll()
			{
				if(size() == 0)
					return 0;
				return remove((jint)0);
			}
			virtual E* remove(jint index = 0) throw (IndexOutOfBoundsExceptionPtr)
			{
				return ArrayList<E>::remove(0);
			}
		};

		template<class E> class Stack : public virtual Collection<E>
		{
		public:
			virtual E* push(E*) = 0;
			virtual E* pop() = 0;
		};

		template<class E> class StackList :
		public virtual ArrayList<E>, 
			public virtual Stack<E>
		{
		public:
			bool instanceof(const char* class_name)const throw()
			{
				if(strcmp("StackList", class_name)== 0)
					return true;
				else if(strcmp("Stack", class_name)== 0)
					return true;
				else
					return ArrayList<E>::instanceof(class_name);
			}
			virtual E* push(E* e)
			{
				add(e);
				return e;
			}
			virtual E* pop()
			{
			  if(size() == 0)
				  return 0;
			  return ArrayList<E>::remove(size() - 1);
			}
		};
	}
}

#endif

#endif
