#ifndef _TEMPLATE_GOD_ARRAY_H
#define _TEMPLATE_GOD_ARRAY_H

#include "gcommon.h"
#include "lang/Object.h"
using namespace goddk::lang;

#ifdef __cplusplus

#include <new>
#include <cstring>
#include <cstdlib>

namespace goddk {
	template<typename T> class array;
	template<typename T> array<T> operator+(const array<T>&, const array<T>&);

	/*!\brief A basic array class.
	 * \warning Only use this class for arrays of primitive types or pointers.
	 */
	template<typename T> class array:
	public virtual Object
	{
		friend array<T> operator+ <> (const array<T>&, const array<T>&);

	protected:
		T* _data;
		int _size;

	public:
		array() throw ()
		{
			_data = 0;
			_size = 0;
		}
		array(int size) throw (std::bad_alloc)
		{
			if (size > 0)
			{
				_data = (T*) calloc(size, sizeof(T));
				if (_data == 0)
					throw std::bad_alloc();
			}
			else
				_data = 0;
			_size = size;
		}
		array(const T* data, int size) throw (std::bad_alloc)
		{
			if (size > 0)
			{
				_data = (T*) malloc(size * sizeof(T));
				if (_data == 0)
					throw std::bad_alloc();
				_size = size;
				memcpy(_data, data, _size * sizeof(T));
			}
			else
			{
				_data = 0;
				_size = 0;
			}
		}
		array(const array& copy) throw (std::bad_alloc)
		{
			if (copy._size)
			{
				_data = (T*) malloc(copy._size * sizeof(T));
				if (_data == 0)
					throw std::bad_alloc();
				_size = copy._size;
				memcpy(_data, copy._data, _size * sizeof(T));
			}
			else
			{
				_data = 0;
				_size = 0;
			}
		}
		~array() throw ()
		{
			if (_data)
			{
				free(_data);
				_data = 0;
			}
		}

		Object* clone() const throw ()
		{
			return (Object* )new array(*this);
		}
		const array& operator=(const array& set) throw (std::bad_alloc)
		{
			resize(set._size);
			if (_size)
				memcpy(_data, set._data, _size * sizeof(T));

			return *this;
		}
		bool operator==(const array& cmp) const throw ()
		{
			if (_size != cmp._size)
				return false;

			if (_size == 0 && cmp._size == 0)
				return true;

			return !::memcmp(_data, cmp._data, _size * sizeof(T));
		}
		bool operator!=(const array& cmp) const throw ()
		{
			if (_size != cmp._size)
				return true;

			if (_size == 0 && cmp._size == 0)
				return false;

			return memcmp(_data, cmp._data, _size * sizeof(T));
		}
		inline T* data() throw ()
		{
			return _data;
		}
		inline const T* data() const throw ()
		{
			return _data;
		}
		inline int size() const throw ()
		{
			return _size;
		}
		void fill(T val) throw ()
		{
			for (int i = 0; i < _size; i++)
				_data[i] = val;
		}
		void replace(T* data, int size) throw ()
		{
			if (_data)
				free(_data);

			_data = data;
			_size = size;
		}
		void swap(array& swp) throw ()
		{
			T* tmp_data = swp._data;
			int tmp_size = swp._size;

			swp._data = _data;
			swp._size = _size;

			_data = tmp_data;
			_size = tmp_size;
		}
		void resize(int newsize) throw (std::bad_alloc)
		{
			if (newsize > 0)
			{
				if (newsize != _size)
				{
					_data = (T*) (_data ? realloc(_data, newsize * sizeof(T)) : calloc(newsize, sizeof(T)));
					if (_data == 0)
						throw std::bad_alloc();
				}
			}
			else
			{
				if (_data)
				{
					free(_data);
					_data = 0;
				}
			}
			_size = newsize;
		}
		inline T& operator[](int _n) throw ()
		{
			return _data[_n];
		}
		inline const T operator[](int _n) const throw ()
		{
			return _data[_n];
		}
		const array& operator+=(const array& rhs) throw ()
		{
			if (rhs._size)
			{
				int _curr = _size;
				resize(_size+rhs._size);
				memcpy(_data+_curr, rhs._data, rhs._size * sizeof(T));
			}
			return *this;
		}
		const array& add(T rhs) throw ()
		{
		
			{
				int _curr = _size;
				resize(_size+1);
				memcpy(_data+_curr, &rhs, sizeof(T));
			}
			return *this;
		}
	};

	template<typename T> array<T> operator+(const array<T>& lhs, const array<T>& rhs)
	{
		array<T> _con(lhs._size + rhs._size);

		if (lhs._size)
			memcpy(_con._data, lhs._data, lhs._size * sizeof(T));
		if (rhs._size)
			memcpy(_con._data + lhs._size, rhs._data, rhs._size * sizeof(T));

		return _con;
	}

	typedef array<byte> bytearray;
	typedef array<jbyte> jbytearray;
	typedef array<jchar> jchararray;
	typedef array<jint>	  jintarray;
	typedef array<jlong> jlongarray;
	typedef array<jdouble> jdoublearray;
}
using namespace goddk;

#endif

#endif
