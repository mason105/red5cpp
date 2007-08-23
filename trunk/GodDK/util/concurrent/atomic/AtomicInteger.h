#pragma once
#include "lang/Number.h"
#include "lang/NumberFormatException.h"
using namespace goddk::lang;
namespace goddk {
	namespace util {
		namespace concurrent {
			namespace Atomic{
class AtomicInteger:
	public virtual Number
{
public:
	AtomicInteger(void);
	AtomicInteger(jint initialValue);
	~AtomicInteger(void);
	bool instanceof(const char* class_name)const throw()
	{
		if(strcmp("AtomicInteger", class_name)== 0)
			return true;
		else
			return __super::instanceof(class_name);
	}
	jint get() const {
		return value;
	}
	void set(jint newValue) {
		value = newValue;
	}
	jint getAndSet(jint newValue) {
		while (true) {
			jint current = get();
			if (compareAndSet(current, newValue))
				return current;
		}
	}
	boolean compareAndSet(jint expect, jint update) {
		if(valueOffset  == expect)
		{
			valueOffset = update;
			return true;
		}
		else
			return false;
	}
	boolean weakCompareAndSet(jint expect, jint update) {
		return compareAndSet(expect, update);
	}
	jint getAndIncrement() {
		while (true) {
			jint current = get();
			jint next = current + 1;
			if (compareAndSet(current, next))
				return current;
		}
	}
	jint getAndDecrement() {
		while (true) {
			jint current = get();
			jint next = current - 1;
			if (compareAndSet(current, next))
				return current;
		}
	}
	jint getAndAdd(jint delta) {
		while (true) {
			jint current = get();
			jint next = current + delta;
			if (compareAndSet(current, next))
				return current;
		}
	}
	jint incrementAndGet() {
		for (;;) {
			jint current = get();
			jint next = current + 1;
			if (compareAndSet(current, next))
				return next;
		}
	}
	jint decrementAndGet() {
		for (;;) {
			jint current = get();
			jint next = current - 1;
			if (compareAndSet(current, next))
				return next;
		}
	}
	jint addAndGet(jint delta) {
		for (;;) {
			jint current = get();
			jint next = current + delta;
			if (compareAndSet(current, next))
				return next;
		}
	}
	virtual jbyte jbyteValue()  const throw (){
		return (jbyte)get();
	}

	virtual jint jintValue()  const throw (){
		return (jint)get();
	}

	virtual jlong jlongValue()  const throw (){
		return (jlong)get();
	}
	virtual jshort jshortValue()  const throw (){
		return (jshort)get();
	}
	virtual jfloat floatValue()  const throw (){
		return (jfloat)get();
	}

	virtual jdouble doubleValue()  const throw (){
		return (jdouble)get();
	}
private:
	volatile jint value;
	jint	 valueOffset;
};
typedef CSmartPtr<AtomicInteger> AtomicIntegerPtr;
}
}
}
}