
#ifndef _ABSTRACT_CLASS_GOD_UTIL_ABSTRACTCOLLECTION_H
#define _ABSTRACT_CLASS_GOD_UTIL_ABSTRACTCOLLECTION_H

#ifdef __cplusplus

#include "lang/Comparable.h"
#include "lang/StringBuilder.h"
#include "lang/CloneNotSupportedException.h"
#include "lang/InterruptedException.h"
#include "lang/IllegalMonitorStateException.h"
#include "lang/RuntimeException.h"
#include "lang/ClassCastException.h"
#include "lang/UnsupportedOperationException.h"
#include "util/Collection.h"
using namespace goddk::lang;
using namespace goddk::util;

namespace goddk {
	namespace util {
		/*!\ingroup CXX_UTIL_m
		 * \warning See the description of goddk::util:Collection for limitations
		 *  on template parameter class E.
		 */
		template<class E> class AbstractCollection :  public virtual Collection<E>
		{
		protected:
			AbstractCollection() {}

			static inline bool equals(const E* e1, const E* e2)
			{
				if (e1 && e2)
					return e1->equals(e2);
				else
					return e1 == e2;
			}

		public:
			virtual ~AbstractCollection() {}
			bool instanceof(const char* class_name)const throw()
			{
				if(strcmp("AbstractCollection", class_name)== 0)
					return true;
				else if(strcmp("Collection", class_name)== 0)
					return true;
				else
					return __super::instanceof(class_name);
			}
			virtual bool add(E* e)
			{
				THROWEXCEPTIONPTR(UnsupportedOperationException)
			}
			virtual bool addAll(const Collection<E>& c)
			{
				bool result = false;
				jint pos = c.size();
				Iterator<E>* it = iterator();
				assert(it != 0);
				while (--pos >= 0)
					result |= add(it->next());
				delete it;
				return result;
			}
			virtual void clear()
			{
				jint pos = size();
				Iterator<E>* it = iterator();
				assert(it != 0);
				while (--pos >= 0)
				{
					it->next();
					it->remove();
				}
				delete it;
			}
			virtual bool contains(const E* e) const
			{
				bool result = false;
				jint pos = size();
				Iterator<E>* it = iterator();
				assert(it != 0);
				while (--pos >= 0)
				{
					if (equals(e, it->next()))
					{
						result = true;
						break;
					}
				}
				delete it;
				return result;
			}
			virtual bool containsAll(const Collection<E>& c) const
			{
				bool result = true;
				jint pos = c.size();
				Iterator<E>* cit = c.iterator();
				assert(cit != 0);
				while (--pos >= 0)
					if (!contains(cit->next()))
					{
						result = false;
						break;
					}
				delete cit;
				return result;
			}
			virtual bool equals(const ObjectImpl* obj) const throw ()
			{
				return Object::equals(obj);
			}
			virtual jint hashCode() const throw ()
			{
				return Object::hashCode();
			}
			virtual bool isEmpty() const throw ()
			{
				return size() == 0;
			}
			virtual Iterator<E>* iterator() = 0;
			virtual Iterator<E>* iterator() const = 0;
			virtual bool remove(const E* e)
			{
				bool result = false;
				jint pos = size();
				Iterator<E>* it = iterator();
				assert(it != 0);
				while (--pos >= 0)
				{
					if (equals(e, it->next()))
					{
						it->remove();
						result = true;
						break;
					}
				}
				delete it;
				return result;
			}
			virtual bool removeAll(const Collection<E>& c)
			{
				bool result = false;
				jint pos = size();
				Iterator<E>* it = iterator();
				assert(it != 0);
				while (--pos >= 0)
					if (c.contains(it->next()))
					{
						it->remove();
						result = true;
						break;
					}
				delete it;
				return result;
			}
			virtual bool retainAll(const Collection<E>& c)
			{
				bool result = false;
				jint pos = c.size();
				Iterator<E>* it = c.iterator();
				assert(it != 0);
				while (--pos >= 0)
					if (!c.contains(it->next()))
					{
						it->remove();
						result = true;
						break;
					}
				delete it;
				return result;
			}
			virtual jint size() const throw () = 0;
			virtual array<E*> toArray() const
			{
				jint pos = size();
				array<E*> result(pos);
				Iterator<E>* it = iterator();
				assert(it != 0);
				for (jint i = 0; --pos >= 0; i++)
					result[i] = it->next();
				delete it;
				return result;
			}
			virtual string toString() const throw ()
			{
				Iterator<E>* it = iterator();
				assert(it != 0);

				StringBuilder buf("[");

				for (jint pos = size(); pos > 0; pos--)
				{
					E* e = it->next();
					if (reinterpret_cast<const void*>(e) == reinterpret_cast<const void*>(this))
						buf.append("(this Collection)");
					else
						buf.append(e);

					if (pos > 1)
						buf.append(", ");
				}
				delete it;

				buf.append("]");

				return buf.toString();
			}
		};
	}
}

#endif

#endif
