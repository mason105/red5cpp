
#ifndef _CLASS_PROPERTIES_H
#define _CLASS_PROPERTIES_H

#ifdef __cplusplus

#include "io/InputStream.h"
#include "io/OutputStream.h"
#include "lang/String.h"
#include "util/Enumeration.h"
#include "util/Hashtable.h"
using namespace goddk::io;
using namespace goddk::lang;
using namespace goddk::util;

namespace goddk {
	namespace util {
		/*!\ingroup CXX_UTIL_m
		 */
		class  Properties : public virtual Hashtable<Object,Object>
		{
		private:
			class Names : public virtual Enumeration<const String>
			{
			private:
				array<String*> _list;
				jint _pos;

			public:
				Names(Hashtable<Object,Object>& h);
				virtual ~Names();

				virtual bool hasMoreElements() throw ();
				virtual const String* nextElement() throw (NoSuchElementExceptionPtr);
			};

			void enumerate(Hashtable<Object,Object>& h) const;

		protected:
			const Properties* defaults;

		public:
			Properties();
			Properties(const Properties& copy);
			Properties(const Properties* defaults);
			virtual ~Properties() {}
			bool instanceof(const char* class_name)const throw()
			{
				if(strcmp("Properties", class_name)== 0)
					return true;
				else
					return __super::instanceof(class_name);
			}
			const String* getProperty(const String& key) const throw ();
			const String* getProperty(const String& key, const String& defaultValue) const throw ();

			/*!\warning If this method returns a non-null value, make sure
			 *  you pass it to goddk::lang::collection_rcheck(), which will delete
			 *  it if it's no longer attached to any other collection.
			 */
			Object* setProperty(const String& key, const String& value);

			Enumeration<const String>* propertyNames() const;

			void load(InputStream& in) throw (IOExceptionPtr);
			/*!\todo rewrite this method using an OutputWriter after obtaining all
			 *  keys through the enumerate method
			 */
			void store(OutputStream& out, const String& header) throw (IOExceptionPtr);
		};
		typedef CSmartPtr<Properties>		PropertiesPtr;
	}
}

#endif

#endif
