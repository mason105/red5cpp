

#ifndef _CLASS_GOD_LANG_THREAD_H
#define _CLASS_GOD_LANG_THREAD_H

#ifdef __cplusplus

#include "lang/String.h"
#include "lang/Runnable.h"
#include "lang/IllegalThreadStateException.h"
#include "lang/CloneNotSupportedException.h"
#include "lang/InterruptedException.h"
#include "lang/IllegalMonitorStateException.h"
#include "lang/RuntimeException.h"
using namespace goddk::lang;

#include <map>
using std::map;

namespace goddk {
	namespace lang {
		/*!\ingroup CXX_LANG_m
		 */
		class  Thread : public virtual Object, public virtual Runnable
		{
			friend class Object;
			friend class goddk::util::concurrent::locks::ReentrantLock;

			friend void MonitorEnter(const Object*);
			friend void MonitorExit(const Object*) throw (IllegalMonitorStateException);

		public:
			/*!\ingroup CXX_LANG_m
			 */
			enum  State
			{
				NEW,
				RUNNABLE,
				BLOCKED,
				WAITING,
				TIMED_WAITING,
				TERMINATED
			};

		private:
			Runnable* _target;
			String    _name;

			bc_thread_t   _thr;
			bc_threadid_t _tid;
			size_t        _stacksize;
			bool          _daemon;
			bool          _interrupted;

			State         _state;
			Monitor*      _monitoring;
			Monitor*      _joiner;

			#if WIN32
			static DWORD WINAPI start_routine(void*);
			#else
			static void* start_routine(void*);
			#endif

			void terminate();

		private:
			typedef map<bc_threadid_t,Thread*> thread_map;
			typedef map<bc_threadid_t,Thread*>::iterator thread_map_iterator;

			static thread_map _tmap;
			static bc_mutex_t _tmap_lock;
			static bc_mutex_t init();

			static Thread _main;

			static Thread* find(bc_threadid_t);

		public:
			static void sleep(jlong millis) throw (InterruptedExceptionPtr);
			static void yield();

			static Thread* currentThread();

		private:
			Thread(const String&, bc_threadid_t);

		public:
			Thread();
			Thread(const String& name);
			Thread(Runnable& target);
			Thread(Runnable& target, const String& name);
			Thread(Runnable& target, const String& name, size_t stacksize);
			virtual ~Thread();
			static void uninit();

			virtual void run();
			virtual string toString() const throw ();

			const String& getName() const throw ();
			Thread::State getState() const throw ();
			void interrupt();
			bool interrupted();
			bool isAlive() const throw ();
			bool isDaemon() const throw ();
			bool isInterrupted() const throw ();
			void join() throw (InterruptedExceptionPtr);
			void join(jint timeout) throw (InterruptedExceptionPtr);
			void setDaemon(bool on) throw (IllegalThreadStateExceptionPtr);
			void start() throw (IllegalThreadStateExceptionPtr);
			void kill(jint timeout);
			virtual void attachRef()
			{
				return Object::attachRef();
			}
			virtual void detachRef()
			{
				return Object::detachRef();
			}
			virtual void removeRef()
			{
				return Object::removeRef();
			}
			virtual void rcheckRef()
			{
				return Object::rcheckRef();
			}
			virtual bool equals(const ObjectImpl* obj) const throw ()
			{
				return Object::equals(obj);
			}

			bool instanceof(const char* class_name)const throw()
			{
				if(strcmp("Thread", class_name)== 0)
					return true;
				else if(Runnable::instanceof(class_name))
					return true;
				else
					return Object::instanceof(class_name);
			}
			virtual jint hashCode() const throw ()
			{
				return Object::hashCode();

			}
		};
		typedef CSmartPtr<Thread>		ThreadPtr;
	}
}

#endif

#endif
