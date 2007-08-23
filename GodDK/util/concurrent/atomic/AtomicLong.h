#pragma once
#include "lang/Number.h"
#include "lang/NumberFormatException.h"
using namespace goddk::lang;
namespace goddk {
	namespace util {
		namespace concurrent {
				namespace Atomic{
				class AtomicLong:
					public virtual Number
				{
				public:
					AtomicLong(void);
					AtomicLong(jlong initialValue);
					~AtomicLong(void);
					bool instanceof(const char* class_name)const throw()
					{
						if(strcmp("AtomicLong", class_name)== 0)
							return true;
						else
							return __super::instanceof(class_name);
					}
					jlong get() const {
						return value;
					}
					void set(jlong newValue) {
						value = newValue;
					}
					jlong getAndSet(jlong newValue) {
						while (true) {
							jlong current = get();
							if (compareAndSet(current, newValue))
								return current;
						}
					}
					boolean compareAndSet(jlong expect, jlong update) {
						if(valueOffset  == expect)
						{
							valueOffset = update;
							return true;
						}
						else
							return false;
					}
					boolean weakCompareAndSet(jlong expect, jlong update) {
						return compareAndSet(expect, update);
					}
					jlong getAndIncrement() {
						while (true) {
							jlong current = get();
							jlong next = current + 1;
							if (compareAndSet(current, next))
								return current;
						}
					}
					jlong getAndDecrement() {
						while (true) {
							jlong current = get();
							jlong next = current - 1;
							if (compareAndSet(current, next))
								return current;
						}
					}
					jlong getAndAdd(jlong delta) {
						while (true) {
							jlong current = get();
							jlong next = current + delta;
							if (compareAndSet(current, next))
								return current;
						}
					}
					jlong incrementAndGet() {
						for (;;) {
							jlong current = get();
							jlong next = current + 1;
							if (compareAndSet(current, next))
								return next;
						}
					}
					jlong decrementAndGet() {
						for (;;) {
							jlong current = get();
							jlong next = current - 1;
							if (compareAndSet(current, next))
								return next;
						}
					}
					jlong addAndGet(jlong delta) {
						for (;;) {
							jlong current = get();
							jlong next = current + delta;
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
					volatile jlong value;
					jlong	 valueOffset;
				};
				typedef CSmartPtr<AtomicLong> AtomicLongPtr;
}
}
}
}