
#ifndef _CLASS_DATE_H
#define _CLASS_DATE_H

#ifdef __cplusplus

#include "lang/Cloneable.h"
#include "lang/String.h"
using namespace goddk::lang;

namespace goddk {
	namespace util {
		/*!\ingroup CXX_UTIL_m
		 */
		class  Date :  public virtual  Cloneable, public virtual Comparable<Date>
		{
		private:
			jlong _time;

		public:
			Date() throw ();
			Date(jlong) throw ();
			virtual ~Date() {}

			virtual Object* clone() const throw ();

			virtual bool equals(const ObjectImpl* obj) const throw ();
			bool equals(const Date& d) const throw ();

			virtual jint compareTo(const Date& anotherDate) const throw ();
			virtual jint hashCode() const throw ();
			virtual string toString() const throw ();

			bool after(const Date&) const throw ();
			bool before(const Date&) const throw ();

			jlong getTime() const throw ();
			void setTime(jlong) throw ();
		};
		typedef CSmartPtr<Date>		DatePtr;
	}
}

#endif

#endif
