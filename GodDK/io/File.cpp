#include "file.h"
#include <io.h>
#include <SYS/STAT.H>
#include <direct.h>
#include <fcntl.h>
namespace goddk {
	namespace io {
		char *  god_strdup (const char * string)
		{
			char *memory;

			if (!string)
				return(NULL);

			if (memory = (char*)malloc(strlen(string) + 2))
				return(strcpy(memory,string));

			return(NULL);
		}
		File::File(const char* path)
		{
			_path = god_strdup(path);
		}
		File::~File()
		{
			if(_path)
				free(_path);
		}
		bool File::isFile()
		{
			struct _stat sbuf;
			if (_stat(_path, &sbuf) != 0)
				return false;
			return (sbuf.st_mode & S_IFREG) == S_IFREG;
		}
		bool File::isDirectory()
		{
			struct _stat sbuf;
			if (_stat(_path, &sbuf) != 0)
				return false;
			return (sbuf.st_mode & S_IFDIR) == S_IFDIR;
		}
		bool File::canRead()
		{
			return _access(_path, R_OK) == 0;
		}
		bool File::canWrite()
		{
			return _access(_path, W_OK) == 0;
		}
		bool File::exists()
		{		
			return _access(_path, F_OK)  == 0;
		}	
		bool File::createNewFile(bool bOnlyRead) throw (IOExceptionPtr)
		{
			if (exists() == true)
				return false;

			int erg = _open(_path, O_CREAT | O_EXCL, S_IREAD | S_IWRITE);
			if (erg == -1)
				return false;
			_close(erg);
			return true;
		}
		bool File::mkdirs(int mode)
		{
			if (exists() == true)
				return true;
			if (mkdir(mode) == true)
				return true;
			
			String fname = getAbsolutePath();
			int lpos = fname.lastIndexOf('/');
			if (lpos == 0 || lpos == -1) 
			{
				lpos = fname.lastIndexOf('\\');
				if (lpos == 0 || lpos == -1) 
					return false;
			}
			string str(_path);
			str = str.substr(0, lpos).c_str();
			if (File(str.c_str()).mkdirs(mode) == false)
				return false;
			return mkdir(mode);
		}
		bool File::mkdir(int mode)
		{
			if (exists() == true)
				return false;
		
			return ::_mkdir(_path) == 0;
		}

		bool File::delete_f()
		{		
			if (exists() == false)
				return false;

			if (isDirectory())
				return _rmdir(_path) == 0; 
			return _unlink(_path) == 0;
		}
		jlong File::length()
		{
			struct _stat sbuf;
			if (_stat(_path, &sbuf) != 0)
				return 0;
			if (_stat(_path, &sbuf) != 0)
				return 0;
			return sbuf.st_size;
		}
		String File::getAbsolutePath()
		{
			return String(_path);
		}
		const char* GetFileName(char* lpszFilePath)   
		{   
			char*  p = strrchr(lpszFilePath,   '\\');   
			if(p==0 ) 
			{
				p = strrchr(lpszFilePath,   '/');   
				if(p==0 )
					return   0;
			}
			return   ++p; 
		}   

		String File::getName()
		{
			char *p = (char *)GetFileName(_path);
			if(p == 0)
				return String(_path);
			char* tmp = god_strdup(p);
			//p = strrchr(tmp, '.'); 
			//if(p)
			//	*p = 0;
			 String	result(tmp);
			 free(tmp);
			 return result;
		}
		FilePtr File::getParentFile()
		{
			char* tmp_path = god_strdup(_path);
			char*  p = strrchr(tmp_path,   '\\');   
			if(p==0 ) 
			{
				p = strrchr(tmp_path,   '/');   
				if(p==0 )
				{
					free(tmp_path);
					return   0;
				}
			}
			*p = 0;

			FilePtr result;
			result.Attach(new File(tmp_path));
			free(tmp_path);
			return result;
		}
	}
}