#include "objectimpl.h"
using namespace goddk::lang;

void goddk::lang::collection_attach(ObjectImpl* obj) throw ()
{
	assert(obj != 0);

	obj->attachRef();
}

void goddk::lang::collection_detach(ObjectImpl* obj) throw ()
{
	assert(obj != 0);
	obj->detachRef();
}

void goddk::lang::collection_remove(ObjectImpl* obj) throw ()
{
	assert(obj != 0);
	obj->removeRef();
}

void goddk::lang::collection_rcheck(ObjectImpl* obj) throw ()
{
	assert(obj != 0);
	obj->rcheckRef();

}
