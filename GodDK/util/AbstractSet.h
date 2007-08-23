

#ifndef _ABSTRACT_CLASS_GOD_UTIL_ABSTRACTSET_H
#define _ABSTRACT_CLASS_GOD_UTIL_ABSTRACTSET_H

#ifdef __cplusplus

#include "util/AbstractCollection.h"
#include "util/Set.h"
using namespace goddk::util;

namespace goddk {
	namespace util {
		/*!\ingroup CXX_UTIL_m
		 * \warning See the description of goddk::util:Collection for limitations
         *  on template parameter class E.
		 */
		template<class E> class AbstractSet : public virtual AbstractCollection<E>, public virtual Set<E>
		{
		public:
			AbstractSet() {}

			bool instanceof(const char* class_name)const throw()
			{
				if(strcmp("AbstractSet", class_name)== 0)
					return true;
				else if(strcmp("AbstractCollection", class_name)== 0)
					return true;
				else if(strcmp("Set", class_name)== 0)
					return true;
				else
					return __super::instanceof(class_name);
			}
			virtual bool equals(const ObjectImpl* obj) const throw ()
			{
				if (this == obj)
					return true;

				if (obj)
				{
					if (!dynamic_cast<const Set<E>*>(obj))
						return false;

					const Collection<E>* c = dynamic_cast<const Collection<E>*>(obj);
					if (c->size() != size())
						return false;

					return containsAll(*c);
				}
				return false;
			}
			virtual jint hashCode() const throw ()
			{
				jint pos = size(), result = 0;
				Iterator<E>* it = iterator();
				assert(it != 0);
				while (--pos >= 0)
				{
					E* e = it->next();
					result += e->hashCode();
				}
				delete it;
				return result;
			}
			virtual Iterator<E>* iterator() = 0;
			virtual Iterator<E>* iterator() const = 0;
			virtual bool removeAll(const Collection<E>& c)
			{
				bool result = false;
				jint pos = size(), cpos = c.size();
				if (pos > cpos)
				{
					Iterator<E>* it = c.iterator();
					assert(it != 0);
					while (--cpos >= 0)
						result |= AbstractCollection<E>::remove(it->next());
					delete it;
				}
				else
				{
					Iterator<E>* it = iterator();
					assert(it != 0);
					while (--pos >= 0)
						if (c.contains(it->next()))
						{
							it->remove();
							result = true;
						}
					delete it;
				}
				return result;
			}
			virtual jint size() const throw () = 0;
		};
	}
}

#endif

#endif
