
#ifndef _CLASS_GOD_LANG_OBJECT_H
#define _CLASS_GOD_LANG_OBJECT_H


#include "lang/ObjectImpl.h"
#include "SmartPtr.h"

#include <string>
using namespace std;

#ifdef __cplusplus

namespace goddk {
	namespace util {
		namespace concurrent {
			namespace locks {
				class  ReentrantLock;
			}
		}
	}
	namespace lang {
		
		/*!\ingroup CXX_LANG_m
		 */
		class  Object:
			public virtual ObjectImpl
		{
			friend class Thread;
			friend class goddk::util::concurrent::locks::ReentrantLock;

			friend void collection_attach(ObjectImpl*) throw ();
			/*!\brief This function is used inside a collection to indicate that
			*  the object has been detached to it.
			*/

			friend void collection_detach(ObjectImpl*) throw ();
			/*!\brief This function is used inside a collection to detach the
			*  object, and delete it if no longer attached to any other
			*  collections.
			*/

			friend void collection_remove(ObjectImpl*) throw ();
			/*!\brief This function checks if an object needs to be recycled:
			*  the object is deleted if no longer attached to any collection.
			*/

			friend void collection_rcheck(ObjectImpl*) throw ();

		protected:
			/*!\brief This class is used to emulate Java's lock/wait/notify
			 *  methods.
			 */
			class Monitor
			{
				friend class Object;

			protected:
				bc_threadid_t         _owner;
				bc_threadid_t         _interruptee;
				bc_mutex_t            _lock;
				volatile unsigned int _lock_count;

				inline void internal_state_lock();

				inline void internal_state_unlock();

				Monitor();

			public:
				virtual ~Monitor() {}

				virtual void interrupt(bc_threadid_t) = 0;
				virtual bool interrupted(bc_threadid_t);
				virtual bool isInterrupted(bc_threadid_t);
				virtual bool isLocked();
				virtual void lock() = 0;
				virtual void lockInterruptibly() throw (...) = 0;
				virtual bool tryLock() = 0;
				virtual void notify() = 0;
				virtual void notifyAll() = 0;
				virtual void unlock() = 0;
				virtual void wait(jlong timeout) throw (...) = 0;

				static Monitor* getInstance(bool fair = false);
			};

		private:
			/*!\brief A Non-fair Monitor
			 */
			class NonfairMonitor : public Monitor
			{
			private:
				#if WIN32
				HANDLE        _lock_sig; // semaphore
				bool          _lock_sig_all;
				HANDLE        _lock_sig_all_done; // event
				unsigned int  _lock_wthreads;
				HANDLE        _notify_sig; // semaphore
				bool          _notify_sig_all;
				HANDLE        _notify_sig_all_done; // event
				unsigned int  _notify_wthreads;
				#else
				bc_cond_t     _lock_sig;
				unsigned int  _lock_wthreads;
				bc_cond_t     _notify_sig;
				unsigned int  _notify_wthreads;
				#endif

			public:
				NonfairMonitor();
				virtual ~NonfairMonitor();

				virtual void interrupt(bc_threadid_t);
				virtual void lock();
				virtual void lockInterruptibly() throw (...);
				virtual bool tryLock();
				virtual void unlock();
				virtual void notify();
				virtual void notifyAll();
				virtual void wait(jlong timeout) throw (...);
			};

			class FairMonitor : public Monitor
			{
			private:
				struct waiter
				{
					bc_threadid_t owner;
					unsigned int  lock_count;
					bc_cond_t     event;
					waiter*       next;
					waiter*       prev;

					waiter(bc_threadid_t owner, unsigned int lock_count);
					~waiter();
				};

				waiter* _lock_head;
				waiter* _lock_tail;
				waiter* _notify_head;
				waiter* _notify_tail;

			public:
				FairMonitor();
				virtual ~FairMonitor();

				virtual void interrupt(bc_threadid_t);
				virtual void lock();
				virtual void lockInterruptibly() throw (...);
				virtual bool tryLock();
				virtual void unlock();
				virtual void notify();
				virtual void notifyAll();
				virtual void wait(jlong timeout) throw (...);
			};

		private:
			
			volatile  int _ref_count;
			char		  _userFlag;
		private:
			
			mutable Monitor* monitor;

		public:
		
			class  Synchronizer
			{
			private:
				Object* _ref;
				bool _once;
				bool _zeroRefCount;
			public:
				Synchronizer(const Object* obj);
				Synchronizer(const Object& obj);
				~Synchronizer();

				bool checkonce();
			};

		
			#define synchronized(obj) for (Object::Synchronizer _s(obj); _s.checkonce(); )

			static void uninit();
		private:
			static bc_mutex_t _init_lock;
			static bc_mutex_t init();

		private:
			void lock() const;
			void unlock() const;

		protected:

		public:
			Object();
			virtual ~Object();
			DECLARE_CLASSNAME("Object")
			
			char getUserFlag(){
				return _userFlag;
			}
			void setUserFlag(char v){
				_userFlag = v;
			}
			virtual Object* clone() const throw (...);
			virtual bool instanceof(const char* class_name)const throw();
			virtual bool equals(const ObjectImpl* obj) const throw ();
			virtual jint hashCode() const throw ();
			void notify() const;
			void notifyAll() const;
			virtual string toString() const throw ();
			void wait(jlong millis = 0) const throw (...);

			virtual void attachRef();
			virtual void detachRef();
			virtual void removeRef();
			virtual void rcheckRef();

		};
		
		typedef CSmartPtr<Object> ObjectPtr;
	}
}

#endif

#endif
