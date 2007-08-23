

#ifndef _ABSTRACT_CLASS_GOD_UTIL_ABSTRACTLIST_H
#define _ABSTRACT_CLASS_GOD_UTIL_ABSTRACTLIST_H

#ifdef __cplusplus

#include "util/AbstractCollection.h"
#include "util/List.h"
#include "lang/IllegalStateException.h"
#include "util/ConcurrentModificationException.h"
using namespace goddk::util;

namespace goddk {
	namespace util {
		/*!\ingroup CXX_UTIL_m
		 * \warning class E must be a subclass of Object
		 */
		template<class E> class AbstractList : public virtual AbstractCollection<E>, public virtual List<E>
		{
		private:
			class Iter :  public virtual Iterator<E>
			{
			private:
				      AbstractList*       _list;
				const AbstractList* _const_list;
				jint _pos;
				jint _last;
				jint _expect;

			public:
				Iter(AbstractList* list) : _list(list), _const_list(list)
				{
					_pos = 0;
					_last = -1;
					_expect = _const_list->modCount;
				}
				Iter(const AbstractList* list) : _list(0), _const_list(list)
				{
					_pos = 0;
					_last = -1;
					_expect = _const_list->modCount;
				}
				virtual ~Iter() {}

				virtual bool hasNext() throw ()
				{
					return _pos < _const_list->size();
				}
				virtual E* next() throw (NoSuchElementExceptionPtr)
				{
					if (_expect != _const_list->modCount)
						THROWEXCEPTIONPTR(ConcurrentModificationException)

					try
					{
						E* e = _const_list->get(_pos);
						_last = _pos++;
						return e;
					}
					catch (IndexOutOfBoundsException&)
					{
						if (_expect != _const_list->modCount)
							THROWEXCEPTIONPTR(ConcurrentModificationException)

						THROWEXCEPTIONPTR(NoSuchElementException)
					}
				}
				virtual void remove()
				{
					if (!_list)
						THROWEXCEPTIONPTR1(UnsupportedOperationException,"Cannot remove items in a const iterator");

					if (_last == -1)
						THROWEXCEPTIONPTR(IllegalStateException)

					if (_expect != _list->modCount)
						THROWEXCEPTIONPTR(ConcurrentModificationException)

					try
					{
						E* e = _list->remove(_last);
						if (e)
	 						collection_rcheck(e);
						if (_last < _pos)
							_pos--;
						_last = -1;
						_expect = _list->modCount;
					}
					catch (IndexOutOfBoundsException&)
					{
						THROWEXCEPTIONPTR(ConcurrentModificationException)
					}
				}
			};

			class ListIter : public virtual ListIterator<E>
			{
			private:
				      AbstractList*       _list;
				const AbstractList* _const_list;
				jint _pos;
				jint _last;
				jint _expect;

			public:
				ListIter(AbstractList* list, jint index) throw (IndexOutOfBoundsExceptionPtr) : _list(list), _const_list(list)
				{
					if (index < 0 || index > list->size())
						throw IndexOutOfBoundsException();

					_pos = index;
					_last = -1;
					_expect = _const_list->modCount;
				}
				ListIter(const AbstractList* list, jint index) throw (IndexOutOfBoundsExceptionPtr) : _list(0), _const_list(list)
				{
					if (index < 0 || index > list->size())
						throw IndexOutOfBoundsException();

					_pos = index;
					_last = -1;
					_expect = _const_list->modCount;
				}
				virtual ~ListIter() {}

				virtual void add(E* e)
				{
					if (!_list)
						THROWEXCEPTIONPTR1(UnsupportedOperationException,"Cannot add items in a const iterator");

					if (_expect != _list->modCount)
						THROWEXCEPTIONPTR(ConcurrentModificationException)

					try
					{
						_list->add(_pos++, e);
						_last = -1;
						_expect = _list->modCount;
					}
					catch (IndexOutOfBoundsException&)
					{
						THROWEXCEPTIONPTR(ConcurrentModificationException)
					}
				}
				virtual bool hasNext() throw ()
				{
					return _pos < _const_list->size();
				}
				virtual bool hasPrevious() throw ()
				{
					return _pos > 0;
				}
				virtual E* next() throw (NoSuchElementExceptionPtr)
				{
					if (_expect != _const_list->modCount)
						THROWEXCEPTIONPTR(ConcurrentModificationException)

					try
					{
						E* e = _const_list->get(_pos);
						_last = _pos++;
						return e;
					}
					catch (IndexOutOfBoundsException&)
					{
						if (_expect != _const_list->modCount)
							THROWEXCEPTIONPTR(ConcurrentModificationException)

						THROWEXCEPTIONPTR(NoSuchElementException)
					}
				}
				virtual jint nextIndex() throw ()
				{
					return _pos;
				}
				virtual E* previous() throw (NoSuchElementExceptionPtr)
				{
					if (_expect != _const_list->modCount)
						THROWEXCEPTIONPTR(ConcurrentModificationException)

					try
					{
						E* e = _const_list->get(_pos-1);
						_last = _pos--;
						return e;
					}
					catch (IndexOutOfBoundsException&)
					{
						if (_expect != _const_list->modCount)
							THROWEXCEPTIONPTR(ConcurrentModificationException)

						THROWEXCEPTIONPTR(NoSuchElementException)
					}
				}
				virtual jint previousIndex() throw ()
				{
					return _pos-1;
				}
				virtual void remove()
				{
					if (!_list)
						THROWEXCEPTIONPTR1(UnsupportedOperationException,"Cannot remove items in a const iterator");

					if (_last == -1)
						THROWEXCEPTIONPTR(IllegalStateException)

					if (_expect != _list->modCount)
						THROWEXCEPTIONPTR(ConcurrentModificationException)

					try
					{
						E* e = _list->remove(_last);
						if (e)
							collection_rcheck(e);
						if (_last < _pos)
							_pos--;
						_last = -1;
						_expect = _list->modCount;
					}
					catch (IndexOutOfBoundsException&)
					{
						THROWEXCEPTIONPTR(ConcurrentModificationException)
					}
				}
				virtual void set(E* e)
				{
					if (!_list)
						THROWEXCEPTIONPTR1(UnsupportedOperationException,"Cannot set items in a const iterator");

					if (_last == -1)
						THROWEXCEPTIONPTR(IllegalStateException)

					if (_expect != _list->modCount)
						THROWEXCEPTIONPTR(ConcurrentModificationException)

					try
					{
						_list->set(_last, e);
						_expect = _list->modCount;
					}
					catch (IndexOutOfBoundsException&)
					{
						THROWEXCEPTIONPTR(ConcurrentModificationException)
					}
				}
			};

		protected:
			jint modCount;

		protected:
			AbstractList()
			{
				modCount = 0;
			}

		public:
			virtual ~AbstractList() {}
			bool instanceof(const char* class_name)const throw()
			{
				if(strcmp("AbstractList", class_name)== 0)
					return true;
				else if(strcmp("List", class_name)== 0)
					return true;
				else
					return __super::instanceof(class_name);
			}
			virtual bool add(E* e)
			{
				add(size(), e);
				return true;
			}
			virtual void add(jint index, E* e)
			{
				THROWEXCEPTIONPTR(UnsupportedOperationException)
			}
			virtual bool addAll(jint index, const Collection<E>& c)
			{
				bool result = false;
				jint pos = c.size();
				Iterator<E>* cit = c.iterator();
				assert(cit != 0);
				while (--pos >= 0)
				{
					add(index++, cit->next());
					result = true;
				}
				delete cit;
				return result;
			}
			virtual void clear()
			{
				while (size())
				{
					E* e = remove(0);
					if (e)
						collection_rcheck(e);
				}
			}
			virtual bool equals(const ObjectImpl* obj) const throw ()
			{
				if (this == obj)
					return true;

				if (obj)
				{
					const AbstractList<E>* abs = dynamic_cast<const AbstractList<E>*>(obj);
					if (abs)
					{
						bool result = true;

						jint pos1 = size(), pos2 = abs->size();

						ListIterator<E>* lit1 = listIterator();
						assert(lit1 != 0);
						ListIterator<E>* lit2 = abs->listIterator();
						assert(lit2 != 0);

						while (--pos1 >= 0 && --pos2 >= 0)
						{
							if (!AbstractCollection<E>::equals(lit1->next(), lit2->next()))
							{
								result = false;
								break;
							}
						}

						if (result)
						{
							// if either of the iterators has any elements left, the lists differ
							result = (pos1 < 0) && (pos2 < 0);
						}

						delete lit1;
						delete lit2;

						return result;
					}
				}
				return false;
			}
			virtual E* get(jint index) const throw (IndexOutOfBoundsExceptionPtr) = 0;
			virtual jint hashCode() const throw ()
			{
				register jint pos = size(), result = 1;
				Iterator<E>* it = iterator();
				assert(it != 0);
				while (--pos >= 0)
				{
					E* e = it->next();
					result *= 31;
					if (e)
						result += e->hashCode();
				}
				delete it;
				return result;
			}
			virtual jint indexOf(const E* e) const
			{
				jint pos = size(), result = -1;
				ListIterator<E>* lit = listIterator();
				assert(lit != 0);
				while (--pos >= 0)
				{
					if (AbstractCollection<E>::equals(e, lit->next()))
					{
						result = lit->previousIndex();
						break;
					}
				}
				delete lit;
				return result;
			}
			virtual Iterator<E>* iterator()
			{
				return new Iter(this);
			}
			virtual Iterator<E>* iterator() const
			{
				return new Iter(this);
			}
			virtual jint lastIndexOf(const E* e) const
			{
				jint result = -1;
				ListIterator<E>* lit = listIterator(size());
				assert(lit != 0);
				while (lit->hasPrevious())
				{
					if (AbstractCollection<E>::equals(e, lit->previous()))
					{
						result = lit->nextIndex();
						break;
					}
				}
				delete lit;
				return result;
			}
			virtual ListIterator<E>* listIterator(jint index = 0) throw (IndexOutOfBoundsExceptionPtr)
			{
				return new ListIter(this, index);
			}
			virtual ListIterator<E>* listIterator(jint index = 0) const throw (IndexOutOfBoundsExceptionPtr)
			{
				return new ListIter(this, index);
			}
			virtual E* remove(jint index)
			{
				THROWEXCEPTIONPTR(UnsupportedOperationException)
			}
			virtual E* set(jint index, E* e)
			{
				THROWEXCEPTIONPTR(UnsupportedOperationException)
			}
			virtual jint size() const throw () = 0;
		};
	}
}

#endif

#endif
