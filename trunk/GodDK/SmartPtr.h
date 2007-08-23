#pragma once
#include "lang/ObjectImpl.h"
using namespace goddk::lang;

//////////////////////////////////////////////////////////////////////////
inline bool GodIsValidAddress(const void* p, size_t nBytes =  1,
							  bool bReadWrite = true)
{
	return ((p != NULL) && !IsBadReadPtr(p, nBytes) &&
		(!bReadWrite || !IsBadWritePtr(const_cast<void*>(p), nBytes)));
}

template < typename T >
class CSmartPtr
{
public:
	T*    pData;     

public:
	CSmartPtr() : pData(0)
	{
	}
	CSmartPtr(int intValue) : pData(0)
	{
	}
	CSmartPtr(T* pValue) : pData(pValue)
	{
		AddRef();
	}
	CSmartPtr(const T* pValue) : pData((T*)pValue)
	{
		AddRef();
	}
	CSmartPtr(const CSmartPtr<T>& sp) : pData(sp.pData)
	{
		AddRef();
	}

	~CSmartPtr()
	{
		Release();
	}
	void AddRef()
	{
		if(pData)
			collection_attach(pData);
	}
	void Release()
	{
		T* pTemp = pData;
		if (pTemp)
		{
			pData = NULL;
			collection_remove(pTemp);
		}
	}

	T& operator* ()  const throw()
	{
		return *pData;
	}

	T* operator-> ()  const throw()
	{
		return pData;
	}
	operator T*() const throw()
	{
		return pData;
	}
	template <typename Q>
	operator Q*() const throw()
	{
		return dynamic_cast<Q*>(pData);
	}
	template <typename Q>
	operator CSmartPtr<Q>() const throw()
	{
		return CSmartPtr<Q>(dynamic_cast<Q*>(pData));
	}
	T** operator&() throw()
	{
		return &pData;
	}
	bool operator!() const throw()
	{
		return (pData == NULL);
	}
	bool operator<(T* pT) const throw()
	{
		return pData < pT;
	}
	bool operator==(T* pT) const throw()
	{
		return pData == pT;
	}
	T* RawData()
	{
		return pData;
	}
	void Attach(T* p2) throw()
	{
		if (pData)
			Release();
		pData = p2;
	}
	T* Detach() throw()
	{
		T* pt = pData;
		pData = NULL;
		return pt;
	}
	bool IsNull()
	{
		return pData == 0 ? true:false;
	}
	bool IsNoNull()
	{
		return pData != 0 ? true:false;
	}
	T* operator=(T* lp) throw()
	{
		if(lp)
			collection_attach(lp);
		Release();
		pData = static_cast<T*>(lp);
		return pData;
	}
	CSmartPtr<T>& operator = (const CSmartPtr<T>& sp)
	{
		if (this != &sp)
		{
			Release();
			pData = sp.pData;
			AddRef();
		}
		return *this;
	}
	template <typename Q>
	CSmartPtr<T>& operator = (const CSmartPtr<Q>& sp)
	{
		{
			Release();
			pData = dynamic_cast<T*>(sp.pData);
			AddRef();
		}
		return *this;
	}
};
#define SAFERELEASEOBJ(x) if(x){collection_remove(x);x=0;}

//////////////////////////////////////////////////////////////////////////
#define SAFERELEASEOBJ(x) if(x){collection_remove(x);x=0;}
//////////////////////////////////////////////////////////////////////////
#define  THROWEXCEPTIONPTR(e) \
{\
	e##Ptr exception;\
	exception.Attach(new e);\
	throw  exception;\
}

#define  THROWEXCEPTIONPTR1(e, s) \
{\
	e##Ptr exception;\
	exception.Attach(new e(s));\
	throw  exception;\
}
