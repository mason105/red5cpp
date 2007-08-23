#pragma	  once


#include "lang/String.h"
#include "io/IOException.h"
using namespace goddk::lang;
using namespace goddk::io;

namespace goddk {
	namespace io {
#ifndef R_OK
#  define R_OK    4              
#  define W_OK    2             
#  define X_OK    1              
#  define F_OK    0           
#endif
		class File;
		typedef CSmartPtr<File>		FilePtr;

		class File:
			public virtual Object
		{
		public:
			File(const char* path);
			virtual ~File();
			bool instanceof(const char* class_name)const throw()
			{
				if(strcmp("File", class_name)== 0)
					return true;
				else
					return __super::instanceof(class_name);
			}
		
			bool isFile();
			bool isDirectory();
			bool canRead();
			bool canWrite();
			bool exists();
			bool delete_f();
			bool mkdirs(int mode = 0777);
			bool mkdir(int mode = 0777);
			bool createNewFile(bool bOnlyRead = true) throw (IOExceptionPtr);
			jlong length();

			FilePtr getParentFile();

			String getAbsolutePath();
			String getName();
		protected:
			char* _path;
		};
	
	}
}