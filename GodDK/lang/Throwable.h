
#ifndef _CLASS_GOD_LANG_THROWABLE_H
#define _CLASS_GOD_LANG_THROWABLE_H

#include "gcommon.h"
#include "lang/Object.h"
using namespace goddk::lang;

#ifdef __cplusplus

namespace goddk {
	namespace lang {
		/* forward declaration
		 */
		class  String;
		
		class  Throwable:
			public virtual Object
		{
		protected:
			String* _msg;
			const Throwable* _cause;
			volatile  int _ref_count;	
		public:
			Throwable();
			Throwable(const char* message);
			Throwable(const String* message);
			Throwable(const String* message, const Throwable* cause);
			Throwable(const Throwable* cause);
			virtual ~Throwable();

			const String* getMessage() const throw ();
			const Throwable* getCause() const throw ();

			Throwable& initCause(const Throwable&);


		};
		typedef CSmartPtr<Throwable>		ThrowablePtr;
	}
}

#endif

#endif
