
#ifndef _INTERFACE_GOD_UTIL_MAP_H
#define _INTERFACE_GOD_UTIL_MAP_H

#ifdef __cplusplus

#include "util/Set.h"
using namespace goddk::util;

namespace goddk {
	namespace util {
		/*!\ingroup CXX_UTIL_m
		 */
		template<class K, class V> class Map:
		public virtual Object
		{
		public:
			class Entry
			{
			public:
				virtual ~Entry() {}

				virtual bool equals(const void* e) const throw () = 0;
				virtual bool equals(const ObjectImpl* obj) const throw () = 0;
				virtual K* getKey() const = 0;
				virtual V* getValue() const = 0;
				virtual jint hashCode() const throw () = 0;
				virtual V* setValue(V*) = 0;
			};

		public:
			virtual ~Map() {}

			virtual void clear() = 0;
			virtual bool containsKey(const K* key) const = 0;
			virtual bool containsValue(const V* value) const = 0;
			virtual Set<class Entry>& entrySet() = 0;
			virtual const Set<class Entry>& entrySet() const = 0;
			virtual Set<K>& keySet() = 0;
			virtual const Set<K>& keySet() const = 0;
			virtual bool equals(const ObjectImpl* obj) const throw () = 0;
			virtual V* get(const K* key) const = 0;
			virtual jint hashCode() const throw () = 0;
			virtual bool isEmpty() const = 0;
			virtual V* put(K* key, V* value) = 0;
			virtual void putAll(const Map<K,V>& m) = 0;
			virtual V* remove(const K* key) = 0;
			virtual jint size() const throw () = 0;
			virtual Collection<V>& values() = 0;
			virtual const Collection<V>& values() const = 0;
		};
	}
}

#endif

#endif
