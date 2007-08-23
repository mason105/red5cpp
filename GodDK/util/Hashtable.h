

#ifndef _CLASS_GOD_UTIL_HASHTABLE_H
#define _CLASS_GOD_UTIL_HASHTABLE_H

#ifdef __cplusplus

#include "lang/Cloneable.h"
#include "lang/Integer.h"
#include "lang/IllegalStateException.h"
#include "lang/NullPointerException.h"
#include "lang/OutOfMemoryError.h"
#include "lang/UnsupportedOperationException.h"
#include "util/Map.h"
#include "util/AbstractSet.h"
#include "util/ConcurrentModificationException.h"
#include <iostream>
#include <hash_set>
#include <hash_map>
#include <set>
using namespace std;
using namespace goddk::lang;
using namespace goddk::util;


namespace goddk {
	namespace util {
		/*!\ingroup CXX_UTIL_m
		 */
		template<class K, class V> class Hashtable :  public virtual Map<K,V>, public virtual Cloneable
		{
		private:
			class Entry :  public virtual Map<K,V>::Entry, public virtual Cloneable
			{
			public:
				jint hash;
				K* key;
				V* value;
				Entry* next;

				Entry(jint hash, K* key, V* value, Entry* next = 0) : hash(hash), key(key), value(value), next(next)
				{
				}
				Entry(const Entry& copy) : hash(copy.hash), key(copy.key), value(copy.value), next(copy.next ? new Entry(*copy.next) : 0)
				{
				}
				virtual ~Entry() {}

				virtual Object* clone() const throw (CloneNotSupportedExceptionPtr)
				{
					return (Object*)new Entry(*this);
				}
				virtual bool equals(const void* e0) const throw ()
				{
					class Map<K,V>::Entry* e = (class Map<K,V>::Entry*)e0;
					if (this == e)
						return true;

					return (key ? key->equals(e->getKey()) : (e->getKey() == 0)) &&
						(value ? value->equals(e->getValue()) : (e->getValue() == 0));
				}
				virtual bool equals(const ObjectImpl* obj) const throw ()
				{
					if ((const Object*)this == obj)
						return true;

					if (obj)
					{
						const class Map<K,V>::Entry* e = dynamic_cast<const class Map<K,V>::Entry*>(obj);
						if (e)
							return (key ? key->equals(e->getKey()) : (e->getKey() == 0)) &&
								(value ? value->equals(e->getValue()) : (e->getValue() == 0));
					}
					return false;
				}
				virtual K* getKey() const
				{
					return key;
				}
				virtual V* getValue() const
				{
					return value;
				}
				virtual jint hashCode() const throw ()
				{
					return hash ^ (value ? value->hashCode() : 0);
				}
				virtual V* setValue(V* val)
				{
					if (val)
					{
						V* result = value;

						value = val;

						return result;
					}
					else
						THROWEXCEPTIONPTR(NullPointerException)
				}
				virtual string toString() const throw ()
				{
					StringBuilder tmp;

					return tmp.append(key).append('=').append(value).toString();
				}
			};

			class HashIter : public virtual Object
			{
			private:
				      Hashtable* _ht;
				const Hashtable* _const_ht;

			protected:
				Entry* next;
				Entry* current;
				jint index;
				jint expect;

			protected:
				HashIter(Hashtable* h) : _ht(h), _const_ht(h)
				{
					expect = _const_ht->_modCount;
					index = _const_ht->_table.size();
					next = current = 0;
					if (_const_ht->_count)
						while ((index > 0) && ((next = _const_ht->_table[--index]) == 0));
				}
				HashIter(const Hashtable* h) : _ht(0), _const_ht(h)
				{
					expect = _const_ht->_modCount;
					index = _const_ht->_table.size();
					next = current = 0;
					if (_const_ht->_count)
						while ((index > 0) && ((next = _const_ht->_table[--index]) == 0));
				}

			public:
				virtual ~HashIter() {}

				virtual bool hasNext() throw ()
				{
					if (_const_ht->_modCount != expect)
						return false;
					return (next != 0) && GodIsValidAddress(next, sizeof(Entry));
				}
				Entry* nextEntry() throw (NoSuchElementExceptionPtr, ConcurrentModificationExceptionPtr)
				{
					if (_const_ht->_modCount != expect)
						THROWEXCEPTIONPTR(ConcurrentModificationException)

					Entry* e = next;
					if (!e)
						THROWEXCEPTIONPTR(NoSuchElementException)

					next = e->next;
					while (!next && index > 0)
						next = _const_ht->_table[--index];

					return current = e;
				}
				virtual void remove()
				{
					if (!_ht)
						THROWEXCEPTIONPTR1(UnsupportedOperationException,"Cannot remove items through const iterator");

					if (!current)
						THROWEXCEPTIONPTR(IllegalStateException)

					if (_ht->_modCount != expect)
						THROWEXCEPTIONPTR(ConcurrentModificationException)

					K* key = current->key;

					current = 0;

					Entry* e = _ht->removeEntryForKey(key);
					if (e)
					{
						collection_remove(e->key);
						collection_remove(e->value);

						delete e;
					}

					expect = _ht->_modCount;
				}
			};

			class EntryIter : public virtual HashIter, public virtual Iterator<class Map<K,V>::Entry>
			{
			public:
				EntryIter(Hashtable* h) : HashIter(h)
				{
				}
				EntryIter(const Hashtable* h) : HashIter(h)
				{
				}
				virtual ~EntryIter() {}

				virtual bool hasNext() throw ()
				{
					return HashIter::hasNext();
				}
				virtual class Map<K,V>::Entry* next() throw (NoSuchElementExceptionPtr)
				{
					return this->nextEntry();
				}
				virtual void remove()
				{
					HashIter::remove();
				}
			};

			class KeyIter : public virtual HashIter, public virtual Iterator<K>
			{
			public:
				KeyIter(Hashtable* h) : HashIter(h)
				{
				}
				KeyIter(const Hashtable* h) : HashIter(h)
				{
				}
				virtual ~KeyIter() {}

				virtual bool hasNext() throw ()
				{
					return HashIter::hasNext();
				}
				virtual K* next() throw (NoSuchElementExceptionPtr)
				{
					return this->nextEntry()->key;
				}
				virtual void remove()
				{
					HashIter::remove();
				}
			};

			class ValueIter : public virtual HashIter, public virtual Iterator<V>
			{
			public:
				ValueIter(Hashtable* h) : HashIter(h)
				{
				}
				ValueIter(const Hashtable* h) : HashIter(h)
				{
				}
				virtual ~ValueIter() {}

				virtual bool hasNext() throw ()
				{
					return HashIter::hasNext();
				}
				virtual V* next() throw (NoSuchElementExceptionPtr)
				{
					return this->nextEntry()->value;
				}
				virtual void remove()
				{
					HashIter::remove();
				}
			};

			class EntrySet : public virtual AbstractSet<class Map<K,V>::Entry>
			{
			private:
				Hashtable*_ht;

			public:
				EntrySet(Hashtable* h) : _ht(h)
				{
				}
				virtual ~EntrySet() {}

				virtual jint size() const throw ()
				{
					return _ht->size();
				}
				virtual Iterator<class Map<K,V>::Entry>* iterator()
				{
					return new EntryIter(_ht);
				}
				virtual Iterator<class Map<K,V>::Entry>* iterator() const
				{
					return new EntryIter(_ht);
				}
			};

			class KeySet : public virtual AbstractSet<K>
			{
			private:
				Hashtable* _ht;

			public:
				KeySet(Hashtable* h) : _ht(h)
				{
				}
				virtual ~KeySet() {}

				virtual jint size() const throw ()
				{
					return _ht->size();
				}
				virtual Iterator<K>* iterator()
				{
					return new KeyIter(_ht);
				}
				virtual Iterator<K>* iterator() const
				{
					return new KeyIter(_ht);
				}
			};

			class ValueCollection : public AbstractCollection<V>
			{
			private:
				Hashtable* _ht;

			public:
				ValueCollection(Hashtable* h) : _ht(h)
				{
				}
				virtual ~ValueCollection() {}

				virtual jint size() const throw ()
				{
					return _ht->size();
				}
				virtual Iterator<V>* iterator()
				{
					return new ValueIter(_ht);
				}
				virtual Iterator<V>* iterator() const
				{
					return new ValueIter(_ht);
				}
			};

		private:
			array<Entry*> _table;
			jint _count;
			jint _threshold;
			jfloat _loadFactor;
			jint _modCount;

			mutable bool _hashing;
			mutable Set<class Map<K,V>::Entry>* _entries;
			mutable Set<K>* _keys;
			mutable Collection<V>* _values;

		protected:
			Entry* removeEntryForKey(const K* key)
			{
				jint hash = key->hashCode();
				jint index = (hash & Integer::MAX_VALUE) % _table.size();
				Entry* prev = 0;
				for (Entry* e = _table[index]; e; prev = e, e = e->next)
					if (hash == e->hash && key->equals(e->key))
					{
						_modCount++;

						if (prev)
							prev->next = e->next;
						else
							_table[index] = e->next;

						_count--;

						return e;
					}
				return 0;
			}

		public:
			Hashtable(jint initialCapacity = 30, jfloat loadFactor = 0.75)
			{
				if (initialCapacity < 0 || loadFactor <= 0.0)
					THROWEXCEPTIONPTR(NullPointerException)

				if (initialCapacity == 0)
					initialCapacity = 1;

				_table.resize(initialCapacity);
				_threshold = (jint)(initialCapacity * (_loadFactor = loadFactor));

				_count = 0;
				_modCount = 0;

				_entries = 0;
				_keys = 0;
				_values = 0;

				_hashing = false;
			}
			Hashtable(const Hashtable& copy) : _table(copy._table.size())
			{
				_loadFactor = copy._loadFactor;
				_threshold = copy._threshold;

				_count = 0;
				_modCount = 0;

				_entries = 0;
				_keys = 0;
				_values = 0;

				_hashing = false;

				putAll(copy);
			}
			virtual ~Hashtable()
			{
				clear();

				delete _entries;
				delete _keys;
				delete _values;
			}
			bool instanceof(const char* class_name)const throw()
			{
				if(strcmp("Hashtable", class_name)== 0)
					return true;
				else if(strcmp("Map", class_name)== 0)
					return true;
				else
					return __super::instanceof(class_name);
			}

			virtual void clear()
			{
				//synchronized (this)
				{
					_modCount++;

					for (jint index = _table.size(); index-- > 0; )
					{
						for (Entry* e = _table[index]; e; )
						{
							Entry *tmp = e->next;

							collection_remove(e->key);
							collection_remove(e->value);

							delete e;

							e = tmp;
						}
						_table[index] = 0;
					}
					_count = 0;
				}
			}
			virtual Object* clone() const throw (CloneNotSupportedExceptionPtr)
			{
				Object* result = 0;

				//synchronized (this)
				{
					result = new Hashtable(*this);
				}
				return result;
			}
			virtual bool contains(const Object* obj) const
			{
				const V* value = dynamic_cast<const V*>(obj);
				if (value)
					return containsValue(value);
				else
					return false;
			}
			virtual bool containsKey(const K* key) const
			{
				if (!key)
					THROWEXCEPTIONPTR(NullPointerException)

				//synchronized (this)
				{
					jint index = (key->hashCode() & Integer::MAX_VALUE) % _table.size();
					for (Entry* e = _table[index]; e; e = e->next)
						if (e->key->equals(key))
							return true;
				}
				return false;
			}
			virtual bool containsValue(const V* value) const
			{
				if (!value)
					THROWEXCEPTIONPTR(NullPointerException)

				//synchronized (this)
				{
					for (jint i = 0; i < _table.size(); i++)
						for (Entry* e = _table[i]; e; e = e->next)
							if (e->value->equals(value))
								return true;
				}
				return false;
			}
			virtual Set<class Map<K,V>::Entry>& entrySet()
			{
				if (!_entries)
				{
					//synchronized (this)
					{
						if (!_entries)
							_entries = new EntrySet(this);
					}
				}
				return *_entries;
			}
			virtual const Set<class Map<K,V>::Entry>& entrySet() const
			{
				if (!_entries)
				{
					//synchronized (this)
					{
						if (!_entries)
							_entries = new EntrySet(const_cast<Hashtable*>(this));
					}
				}
				return *_entries;
			}
			virtual bool equals(const ObjectImpl* obj) const throw ()
			{
				if (this == obj)
					return true;

				if (obj)
				{
					const Map<K,V>* map = dynamic_cast<const Map<K,V>*>(obj);
					if (map)
					{
						//synchronized (this)
						{
							if (_count != map->size())
								return false;

							try
							{
								bool result = true;
								Iterator<class Map<K,V>::Entry>* mit = map->entrySet().iterator();
								assert(mit != 0);
								while (mit->hasNext())
								{
									class Map<K,V>::Entry* me = mit->next();
									K* key = me->getKey();
									V* value = me->getValue();
									if (value)
									{
										if (!(map->get(key) == 0 && map->containsKey(key)))
										{
											result = false;
											break;
										}
									}
									else
									{
										if (!value->equals(map->get(key)))
										{
											result = false;
											break;
										}
									}
								}
								delete mit;
								return result;
							}
							catch (Exception&)
							{
							}
						}
					}
				}
				return false;
			}
			virtual V* get(const K* key) const
			{
				if (key)
				{
					//synchronized (this)
					{
						jint index = (key->hashCode() & Integer::MAX_VALUE) % _table.size();
						for (Entry* e = _table[index]; e; e = e->next)
							if (e->key->equals(key))
								return e->value;
					}
					return 0;
				}
				else
					THROWEXCEPTIONPTR(NullPointerException)
			}
			virtual jint hashCode() const throw ()
			{
				jint result = 0;

				//synchronized (this)
				{
					if (_count == 0 || _hashing)
						return 0;

					_hashing = true;

					for (jint i = 0; i < _table.size(); i++)
						for (Entry* e = _table[i]; e; e = e->next)
							result += e->key->hashCode() ^ e->value->hashCode();

					_hashing = false;
				}

				return result;
			}
			virtual bool isEmpty() const throw ()
			{
				bool result = true;

				//synchronized (this)
				{
					result = (_count == 0);
				}
				return result;
			}
			virtual Set<K>& keySet()
			{
				if (_keys)
				{
					//synchronized (this)
					{
						if (!_keys)
							_keys = new KeySet(this);
					}
				}
				return *_keys;
			}
			virtual const Set<K>& keySet() const
			{
				if (_keys)
				{
					//synchronized (this)
					{
						if (!_keys)
							_keys = new KeySet(const_cast<Hashtable*>(this));
					}
				}
				return *_keys;
			}
			virtual V* put(K* key, V* value)
			{
				if (key && value)
				{
					jint hash = key->hashCode();

					//synchronized (this)
					{
						jint index = (hash & Integer::MAX_VALUE) % _table.size();

						for (Entry* e = _table[index]; e != 0; e = e->next)
						{
							if (key->equals(e->key))
							{
								// Existing key
								V* result = e->value;
								e->value = value;

								collection_attach(value);
								collection_detach(result);

								//god
								//collection_remove(key);

								return result;
							}
						}

						// Non-existing key
						_modCount++;

						if (_count >= _threshold)
						{
							// Re-hash
							jint oldsize = _table.size();

							if (oldsize == Integer::MAX_VALUE)
								throw OutOfMemoryError();

							jint newsize = (_table.size() << 1) + 1;

							// test if overflow occured
							if (newsize < oldsize)
								newsize = Integer::MAX_VALUE;

							array<Entry*> retable(newsize);

							for (jint i = oldsize; i-- > 0; )
							{
								for (Entry* e = _table[i]; e != 0; )
								{
									Entry* tmp = e->next;

									index = (e->hash & Integer::MAX_VALUE) % newsize;
									e->next = retable[index];
									retable[index] = e;
									e = tmp;
								}
							}

							// Swap retable and _table contents
							_table.swap(retable);

							_threshold = (jint)(newsize * _loadFactor);

							index = (hash & Integer::MAX_VALUE) % _table.size();
						}

						Entry* tmp = _table[index];
						_table[index] = new Hashtable::Entry(hash, key, value, tmp);
						_count++;
						collection_attach(key);
						collection_attach(value);
					}
					return 0;
				}
				else
				{
					if(value == NULL)
					{
						V* result = remove(key);
						//god
						//collection_remove(key);

						return result;

					}
					else
						THROWEXCEPTIONPTR(NullPointerException)
				}
			}
			virtual void putAll(const Map<K,V>& m)
			{
				Iterator<class Map<K,V>::Entry>* mit = m.entrySet().iterator();
				assert(mit != 0);
				while (mit->hasNext())
				{
					class Map<K,V>::Entry* e = mit->next();
					V* tmp = put(e->getKey(), e->getValue());
					collection_rcheck(tmp);
				}
				delete mit;
			}
			virtual V* remove(const K* key)
			{
				if (key)
				{
					Entry* e = removeEntryForKey(key);
					if (e)
					{
						V* result = e->value;

						collection_remove(e->key);
						collection_detach(result);

						delete e;

						return result;
					}
					return 0;
				}
				else
					THROWEXCEPTIONPTR(NullPointerException)
			}
			virtual jint size() const throw ()
			{
				jint result = 0;

				//synchronized (this)
				{
					result = _count;
				}
				return result;
			}
			virtual Collection<V>& values()
			{
				if (!_values)
				{
					//synchronized (this)
					{
						if (!_values)
							_values = new ValueCollection(this);
					}
				}
				return *_values;
			}
			virtual const Collection<V>& values() const
			{
				if (!_values)
				{
					//synchronized (this)
					{
						if (!_values)
							_values = new ValueCollection(const_cast<Hashtable*>(this));
					}
				}
				return *_values;
			}
		};

		template<class E>
		class HashSet : public virtual AbstractSet<E>
		{
		private:
			std::hash_set<E*>	_s;

		public:
			class HashSetItr:public virtual Iterator<E>
			{
			public:
				HashSetItr(std::hash_set<E*>* s)
				{
					__s = s;
					_it = __s->begin();
					_oldit = _it;
				}
				HashSetItr(const std::hash_set<E*>* s)
				{
					__s = (std::hash_set<E*>*)s;
					_it = __s->begin();
					_oldit = _it;
				}
				virtual bool hasNext() throw ()
				{
					return _it != __s->end();
				}
				virtual E* next() throw (NoSuchElementExceptionPtr)
				{
					E* v   = *_it;
					_oldit = _it;
					_it ++;
					return v;
				}
				virtual void remove()
				{
					if(_oldit != __s->end())
					{
						E* v = *_oldit;
						collection_detach(v);
						__s->erase(_oldit);
					}
				}
			protected:
				 std::hash_set<E*>* __s;
				typedef typename hash_set<E*>::iterator hsit;
				hsit _it;
				hsit _oldit;
			};
			HashSet()
			{
				
			}
			virtual ~HashSet() 
			{
				clear();
			}
			virtual bool add(E* e)
			{
				_s.insert(e);
				collection_attach(e);
				return true;
			}
			virtual void clear() 
			{
				typedef typename hash_set<E*>::iterator hsit;
				hsit _it = _s.begin();
				for(; _it != _s.end(); _it++)
				{
					E* v = *_it;
					collection_detach(v);
				}
			}
			virtual jint size() const throw ()
			{
				return _s.size();
			}
			virtual Iterator<E>* iterator()
			{
				return new HashSetItr(&_s);
			}
			virtual Iterator<E>* iterator() const
			{
				return new HashSetItr(&_s);
			}
		};
	}
}

#endif

#endif
