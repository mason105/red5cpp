#pragma	  once
#include "gcommon.h"
namespace goddk
{
	namespace lang
	{
		class ObjectImpl
		{
		public:
			virtual void attachRef() = 0;
			virtual void detachRef() = 0;
			virtual void removeRef() = 0;
			virtual void rcheckRef() = 0;
			virtual bool equals(const ObjectImpl* obj) const throw () = 0;
			virtual bool instanceof(const char* class_name)const throw()  = 0;
			virtual jint hashCode()  const throw ()= 0;
			virtual const char* GetClassName() = 0;
		};
		void collection_attach(ObjectImpl*) throw ();
		void collection_detach(ObjectImpl*) throw ();
		void collection_remove(ObjectImpl*) throw ();
		void collection_rcheck(ObjectImpl*) throw ();
	}
}
#define DECLARE_CLASSNAME(x)	virtual const char* GetClassName(){return x;}