#pragma once
#include "lang/Object.h"
#include "lang/Long.h"
#include "lang/thread.h"

using namespace goddk::lang;

namespace goddk {
	namespace util {
		namespace concurrent {
			class TimeUnit;
			typedef CSmartPtr<TimeUnit>  TimeUnitPtr;

			class TimeUnit:
				public virtual Object
			{
			public:
				TimeUnit(void);
				~TimeUnit(void);
				bool instanceof(const char* class_name)const throw()
				{
					if(strcmp("TimeUnit", class_name)== 0)
						return true;
					else
						return __super::instanceof(class_name);
				}
				static const jlong C0 = 1L;
				static const jlong C1 = C0 * 1000L;
				static const jlong C2 = C1 * 1000L;
				static const jlong C3 = C2 * 1000L;
				static const jlong C4 = C3 * 60L;
				static const jlong C5 = C4 * 60L;
				static const jlong C6 = C5 * 24L;

				static const jlong MAX = Long::MAX_VALUE;

				virtual jlong toNanos(jlong d)   = 0;
				virtual jlong toMicros(jlong d)  = 0;
				virtual jlong toMillis(jlong d)  = 0;
				virtual jlong toSeconds(jlong d) = 0;
				virtual jlong toMinutes(jlong d) = 0;
				virtual jlong toHours(jlong d)   = 0;
				virtual jlong toDays(jlong d)    = 0;
				virtual jlong convert(jlong d, TimeUnitPtr u)= 0;
				virtual int excessNanos(jlong d, jlong m)= 0;

				static jlong x(jlong d, jlong m, jlong over) {
					if (d >  over) return Long::MAX_VALUE;
					if (d < -over) return Long::MIN_VALUE;
					return d * m;
				}

				void timedWait(ObjectPtr obj, jlong timeout)
					throw (InterruptedExceptionPtr) 
				{
						if (timeout > 0) 
						{
							jlong ms = toMillis(timeout);
							int ns = excessNanos(timeout, ms);
							obj->wait(ms);
						}
				}
				void timedJoin(ThreadPtr thread, jlong timeout)
					throw (InterruptedExceptionPtr)
				{
						if (timeout > 0) 
						{
							jlong ms = toMillis(timeout);
							int ns = excessNanos(timeout, ms);
							thread->join();
						}
				}
				void sleep(jlong timeout) throw (InterruptedExceptionPtr) 
				{
					if (timeout > 0) 
					{
						jlong ms = toMillis(timeout);
						int ns = excessNanos(timeout, ms);
						Thread::sleep(ms);
					}
				}
			};

			class TimeUnit_NANOSECONDS:
				public virtual TimeUnit
			{
			public:
				virtual jlong toNanos(jlong d)   { return d; }
				virtual jlong toMicros(jlong d)  { return d/(C1/C0); }
				virtual jlong toMillis(jlong d)  { return d/(C2/C0); }
				virtual jlong toSeconds(jlong d) { return d/(C3/C0); }
				virtual jlong toMinutes(jlong d) { return d/(C4/C0); }
				virtual jlong toHours(jlong d)   { return d/(C5/C0); }
				virtual jlong toDays(jlong d)    { return d/(C6/C0); }
				virtual jlong convert(jlong d, TimeUnitPtr u) { return u->toNanos(d); }
				virtual int excessNanos(jlong d, jlong m) { return (int)(d - (m*C2)); }
			};

			class TimeUnit_MICROSECONDS:
				public virtual TimeUnit
			{
			public:
				virtual jlong toNanos(jlong d)   { return x(d, C1/C0, MAX/(C1/C0)); }
				virtual jlong toMicros(jlong d)  { return d; }
				virtual jlong toMillis(jlong d)  { return d/(C2/C1); }
				virtual jlong toSeconds(jlong d) { return d/(C3/C1); }
				virtual jlong toMinutes(jlong d) { return d/(C4/C1); }
				virtual jlong toHours(jlong d)   { return d/(C5/C1); }
				virtual jlong toDays(jlong d)    { return d/(C6/C1); }
				virtual jlong convert(jlong d, TimeUnitPtr u) { return u->toMicros(d); }
				int excessNanos(jlong d, jlong m) { return (int)((d*C1) - (m*C2)); }
			};

			class TimeUnit_MILLISECONDS:
				public virtual TimeUnit
			{
			public:
				virtual jlong toNanos(jlong d)   { return x(d, C2/C0, MAX/(C2/C0)); }
				virtual jlong toMicros(jlong d)  { return x(d, C2/C1, MAX/(C2/C1)); }
				virtual jlong toMillis(jlong d)  { return d; }
				virtual jlong toSeconds(jlong d) { return d/(C3/C2); }
				virtual jlong toMinutes(jlong d) { return d/(C4/C2); }
				virtual jlong toHours(jlong d)   { return d/(C5/C2); }
				virtual jlong toDays(jlong d)    { return d/(C6/C2); }
				virtual jlong convert(jlong d, TimeUnitPtr u) { return u->toMillis(d); }
				int excessNanos(jlong d, jlong m) { return 0; }
			};

			class TimeUnit_SECONDS:
				public virtual TimeUnit
			{
			public:
				virtual jlong toNanos(jlong d)   { return x(d, C3/C0, MAX/(C3/C0)); }
				virtual jlong toMicros(jlong d)  { return x(d, C3/C1, MAX/(C3/C1)); }
				virtual jlong toMillis(jlong d)  { return x(d, C3/C2, MAX/(C3/C2)); }
				virtual jlong toSeconds(jlong d) { return d; }
				virtual jlong toMinutes(jlong d) { return d/(C4/C3); }
				virtual jlong toHours(jlong d)   { return d/(C5/C3); }
				virtual jlong toDays(jlong d)    { return d/(C6/C3); }
				virtual jlong convert(jlong d, TimeUnitPtr u) { return u->toSeconds(d); }
				int excessNanos(jlong d, jlong m) { return 0; }
			};

			class TimeUnit_MINUTES:
				public virtual TimeUnit
			{
			public:
				virtual jlong toNanos(jlong d)   { return x(d, C4/C0, MAX/(C4/C0)); }
				virtual jlong toMicros(jlong d)  { return x(d, C4/C1, MAX/(C4/C1)); }
				virtual jlong toMillis(jlong d)  { return x(d, C4/C2, MAX/(C4/C2)); }
				virtual jlong toSeconds(jlong d) { return x(d, C4/C3, MAX/(C4/C3)); }
				virtual jlong toMinutes(jlong d) { return d; }
				virtual jlong toHours(jlong d)   { return d/(C5/C4); }
				virtual jlong toDays(jlong d)    { return d/(C6/C4); }
				virtual jlong convert(jlong d, TimeUnitPtr u) { return u->toMinutes(d); }
				int excessNanos(jlong d, jlong m) { return 0; }
			};

			class TimeUnit_HOURS:
				public virtual TimeUnit
			{
			public:
				virtual jlong toNanos(jlong d)   { return x(d, C5/C0, MAX/(C5/C0)); }
				virtual jlong toMicros(jlong d)  { return x(d, C5/C1, MAX/(C5/C1)); }
				virtual jlong toMillis(jlong d)  { return x(d, C5/C2, MAX/(C5/C2)); }
				virtual jlong toSeconds(jlong d) { return x(d, C5/C3, MAX/(C5/C3)); }
				virtual jlong toMinutes(jlong d) { return x(d, C5/C4, MAX/(C5/C4)); }
				virtual jlong toHours(jlong d)   { return d; }
				virtual jlong toDays(jlong d)    { return d/(C6/C5); }
				virtual jlong convert(jlong d, TimeUnitPtr u) { return u->toHours(d); }
				int excessNanos(jlong d, jlong m) { return 0; }
			};

			class TimeUnit_DAYS:
				public virtual TimeUnit
			{
			public:
				virtual jlong toNanos(jlong d)   { return x(d, C6/C0, MAX/(C6/C0)); }
				virtual jlong toMicros(jlong d)  { return x(d, C6/C1, MAX/(C6/C1)); }
				virtual jlong toMillis(jlong d)  { return x(d, C6/C2, MAX/(C6/C2)); }
				virtual jlong toSeconds(jlong d) { return x(d, C6/C3, MAX/(C6/C3)); }
				virtual jlong toMinutes(jlong d) { return x(d, C6/C4, MAX/(C6/C4)); }
				virtual jlong toHours(jlong d)   { return x(d, C6/C5, MAX/(C6/C5)); }
				virtual jlong toDays(jlong d)    { return d; }
				virtual jlong convert(jlong d, TimeUnitPtr u) { return u->toDays(d); }
				int excessNanos(jlong d, jlong m) { return 0; }
			};
		}
	}
}