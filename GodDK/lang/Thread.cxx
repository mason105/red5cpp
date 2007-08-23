
#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#if !WIN32 && HAVE_TIME_H
# include <time.h>
#endif

#if HAVE_ERRNO_H
# include <errno.h>
#endif

#include "lang/Thread.h"
#include "lang/String.h"
#include "lang/StringBuilder.h"
#include "lang/RuntimeException.h"
using namespace goddk::lang;

Thread::thread_map Thread::_tmap;

bc_mutex_t Thread::_tmap_lock = Thread::init();

#if WIN32
Thread Thread::_main("main", GetCurrentThreadId());
#elif HAVE_SYNCH_H
Thread Thread::_main("main", thr_self());
#elif HAVE_PTHREAD_H
Thread Thread::_main("main", pthread_self());
#else
# error
#endif

#if WIN32
DWORD Thread::start_routine(void* args)
#else
void* Thread::start_routine(void* args)
#endif
{
	register Thread* t = (Thread*) args;

	#if WIN32
	if (WaitForSingleObject(_tmap_lock, INFINITE) != WAIT_OBJECT_0)
		THROWEXCEPTIONPTR1(RuntimeException,"WaitForSingleObject failed");
	#elif HAVE_SYNCH_H
	if (mutex_lock(&_tmap_lock))
		THROWEXCEPTIONPTR1(RuntimeException,"mutex_lock failed");
	#elif HAVE_PTHREAD_H
	if (pthread_mutex_lock(&_tmap_lock))
		THROWEXCEPTIONPTR1(RuntimeException,"pthread_mutex_lock failed");
	#else
	# error
	#endif

	_tmap[t->_tid] = t;

	#if WIN32
	if (!ReleaseMutex(_tmap_lock))
		THROWEXCEPTIONPTR1(RuntimeException,"ReleaseMutex failed");
	#elif HAVE_SYNCH_H
	if (mutex_unlock(&_tmap_lock))
		THROWEXCEPTIONPTR1(RuntimeException,"mutex_unlock failed");
	#elif HAVE_PTHREAD_H
	if (pthread_mutex_unlock(&_tmap_lock))
		THROWEXCEPTIONPTR1(RuntimeException,"pthread_mutex_unlock failed");
	#else
	# error
	#endif
	if(t->_target)
		t->_target->run();
	else
	{
		t->run();
	}

	if (!t->_daemon)
	{
		t->monitor->lock();
		t->_state = Thread::TERMINATED;
		t->_joiner->lock();
		t->_joiner->notifyAll();
		t->_joiner->unlock();
		t->monitor->unlock();
	}

	return 0;
}
void Thread::uninit()
{
	if(_tmap_lock)
	{
		CloseHandle(_tmap_lock);
		_tmap_lock = 0;
	}
}
bc_mutex_t Thread::init()
{
	bc_mutex_t lock;

	#if WIN32
	if (!(lock = CreateMutex(NULL, FALSE, NULL)))
		THROWEXCEPTIONPTR1(RuntimeException,"CreateMutex failed");
	#elif HAVE_SYNCH_H
	if (mutex_init(&lock, USYNC_THREAD, 0))
		THROWEXCEPTIONPTR1(RuntimeException,"mutex_init failed");
	#elif HAVE_PTHREAD_H
	if (pthread_mutex_init(&lock, 0))
		THROWEXCEPTIONPTR1(RuntimeException,"pthread_mutex_init failed");
	#else
	# error
	#endif

	_tmap[_main._tid] = &_main;

	return lock;
}

Thread* Thread::find(bc_threadid_t id)
{
	Thread* result = 0;

	#if WIN32
	if (WaitForSingleObject(_tmap_lock, INFINITE) != WAIT_OBJECT_0)
		THROWEXCEPTIONPTR1(RuntimeException,"WaitForSingleObject failed");
	#elif HAVE_SYNCH_H
	if (mutex_lock(&_tmap_lock))
		THROWEXCEPTIONPTR1(RuntimeException,"mutex_lock failed");
	#elif HAVE_PTHREAD_H
	if (pthread_mutex_lock(&_tmap_lock))
		THROWEXCEPTIONPTR1(RuntimeException,"pthread_mutex_lock failed");
	#else
	# error
	#endif

	thread_map_iterator it = _tmap.find(id);
	if (it != _tmap.end())
		result = it->second;

	#if WIN32
	if (!ReleaseMutex(_tmap_lock))
		THROWEXCEPTIONPTR1(RuntimeException,"ReleaseMutex failed");
	#elif HAVE_SYNCH_H
	if (mutex_unlock(&_tmap_lock))
		THROWEXCEPTIONPTR1(RuntimeException,"mutex_unlock failed");
	#elif HAVE_PTHREAD_H
	if (pthread_mutex_unlock(&_tmap_lock))
		THROWEXCEPTIONPTR1(RuntimeException,"pthread_mutex_unlock failed");
	#else
	# error
	#endif

	return result;
}

Thread* Thread::currentThread()
{
	#if WIN32
	return find(GetCurrentThreadId());
	#elif HAVE_SYNCH_H
	return find(thr_self());
	#elif HAVE_PTHREAD_H
	return find(pthread_self());
	#else
	# error
	#endif
}

void Thread::sleep(jlong millis) throw (InterruptedExceptionPtr)
{
	Object sleeper;

	synchronized (sleeper)
	{
		sleeper.wait(millis);
	}
}

void Thread::yield()
{
	#if WIN32
	SwitchToThread();
	#elif HAVE_THREAD_H
	thr_yield();
	#elif HAVE_SCHED_H
	sched_yield();
	#endif
}

Thread::Thread(const String& name, bc_threadid_t id) : _name(name)
{
	_target = this;
	_stacksize = 0;
	_daemon = true;
	_interrupted = false;
	_state = Thread::RUNNABLE;
	_monitoring = monitor = Monitor::getInstance();
	_joiner = Monitor::getInstance();
}

Thread::Thread()
{
	_target = this;
	_stacksize = 0;
	_daemon = false;
	_interrupted = false;
	_state = Thread::NEW;
	_monitoring = monitor = Monitor::getInstance();
	_joiner = Monitor::getInstance();
}

Thread::Thread(const String& name) : _name(name)
{
	_target = this;
	_stacksize = 0;
	_daemon = false;
	_interrupted = false;
	_state = Thread::NEW;
	_monitoring = monitor = Monitor::getInstance();
	_joiner = Monitor::getInstance();
}

Thread::Thread(Runnable& target) : _target(&target)
{
	_stacksize = 0;
	_daemon = false;
	_interrupted = false;
	_state = Thread::NEW;
	_monitoring = monitor = Monitor::getInstance();
	_joiner = Monitor::getInstance();
}

Thread::Thread(Runnable& target, const String& name) : _target(&target), _name(name)
{
	_stacksize = 0;
	_daemon = false;
	_interrupted = false;
	_state = Thread::NEW;
	_monitoring = monitor = Monitor::getInstance();
	_joiner = Monitor::getInstance();
}

Thread::Thread(Runnable& target, const String& name, size_t stacksize) : _target(&target), _name(name)
{
	_stacksize = stacksize;
	_daemon = false;
	_interrupted = false;
	_state = Thread::NEW;
	_monitoring = monitor = Monitor::getInstance();
	_joiner = Monitor::getInstance();
}

Thread::~Thread()
{
	if (!_daemon)
	{
		if (_state != Thread::NEW)
		{
			join();

			#if WIN32
			if (WaitForSingleObject(_thr, INFINITE) != WAIT_OBJECT_0)
				THROWEXCEPTIONPTR1(RuntimeException,"WaitForSingleObject failed");
			if (!CloseHandle(_thr))
				THROWEXCEPTIONPTR1(RuntimeException,"CloseHandle failed");
			#elif HAVE_THREAD_H
			if (thr_join(_tid, 0, 0))
				THROWEXCEPTIONPTR1(RuntimeException,"thr_join failed");
			#elif HAVE_PTHREAD_H
			if (pthread_join(_tid, 0))
				THROWEXCEPTIONPTR1(RuntimeException,"pthread_join failed");
			#endif
		}

		#if WIN32
		if (WaitForSingleObject(_tmap_lock, INFINITE) != WAIT_OBJECT_0)
			THROWEXCEPTIONPTR1(RuntimeException,"WaitForSingleObject failed");
		#elif HAVE_SYNCH_H
		if (mutex_lock(&_tmap_lock))
			THROWEXCEPTIONPTR1(RuntimeException,"mutex_lock failed");
		#elif HAVE_PTHREAD_H
		if (pthread_mutex_lock(&_tmap_lock))
			THROWEXCEPTIONPTR1(RuntimeException,"pthread_mutex_lock failed");
		#else
		# error
		#endif

		_tmap.erase(_tid);

		#if WIN32
		if (!ReleaseMutex(_tmap_lock))
			THROWEXCEPTIONPTR1(RuntimeException,"ReleaseMutex failed");
		#elif HAVE_SYNCH_H
		if (mutex_unlock(&_tmap_lock))
			THROWEXCEPTIONPTR1(RuntimeException,"mutex_unlock failed");
		#elif HAVE_PTHREAD_H
		if (pthread_mutex_unlock(&_tmap_lock))
			THROWEXCEPTIONPTR1(RuntimeException,"pthread_mutex_unlock failed");
		#else
		# error
		#endif
	}

	if(_joiner)
	{
		delete _joiner;
		_joiner = 0;
	}
	_state = Thread::NEW;
}
void Thread::kill(jint timeout)
{
	if (!_daemon)
	{
		if (_state != Thread::NEW)
		{
			join(timeout);

#if WIN32
			if (WaitForSingleObject(_thr, timeout) != WAIT_OBJECT_0)
				TerminateThread(_thr, 0xffff);
			if (!CloseHandle(_thr))
				THROWEXCEPTIONPTR1(RuntimeException,"CloseHandle failed");
#elif HAVE_THREAD_H
			if (thr_join(_tid, 0, 0))
				THROWEXCEPTIONPTR1(RuntimeException,"thr_join failed");
#elif HAVE_PTHREAD_H
			if (pthread_join(_tid, 0))
				THROWEXCEPTIONPTR1(RuntimeException,"pthread_join failed");
#endif
		}

#if WIN32
		if (WaitForSingleObject(_tmap_lock, INFINITE) != WAIT_OBJECT_0)
			THROWEXCEPTIONPTR1(RuntimeException,"WaitForSingleObject failed");
#elif HAVE_SYNCH_H
		if (mutex_lock(&_tmap_lock))
			THROWEXCEPTIONPTR1(RuntimeException,"mutex_lock failed");
#elif HAVE_PTHREAD_H
		if (pthread_mutex_lock(&_tmap_lock))
			THROWEXCEPTIONPTR1(RuntimeException,"pthread_mutex_lock failed");
#else
# error
#endif

		_tmap.erase(_tid);

#if WIN32
		if (!ReleaseMutex(_tmap_lock))
			THROWEXCEPTIONPTR1(RuntimeException,"ReleaseMutex failed");
#elif HAVE_SYNCH_H
		if (mutex_unlock(&_tmap_lock))
			THROWEXCEPTIONPTR1(RuntimeException,"mutex_unlock failed");
#elif HAVE_PTHREAD_H
		if (pthread_mutex_unlock(&_tmap_lock))
			THROWEXCEPTIONPTR1(RuntimeException,"pthread_mutex_unlock failed");
#else
# error
#endif
	}

	if(_joiner)
	{
		delete _joiner;
		_joiner = 0;
	}
	_state = Thread::NEW;
}
void Thread::start() throw (IllegalThreadStateExceptionPtr)
{
	monitor->lock();
	if (_state != Thread::NEW)
	{
		monitor->unlock();
		THROWEXCEPTIONPTR1(IllegalThreadStateException,"Thread was already started");
	}

	#if WIN32
	if (!(_thr = CreateThread(NULL, _stacksize, (LPTHREAD_START_ROUTINE) start_routine, this, 0, &_tid)))
		THROWEXCEPTIONPTR1(RuntimeException,"CreateThread failed");
	#else
	# if HAVE_THREAD_H
	if (thr_create(0, _stacksize, start_routine, this, _daemon ? THR_DAEMON : 0, &_tid))
		THROWEXCEPTIONPTR1(RuntimeException,"thr_create failed");
	# elif HAVE_PTHREAD_H
	if (_stacksize || _daemon)
	{
		pthread_attr_t attr;

		if (pthread_attr_init(&attr))
			THROWEXCEPTIONPTR1(RuntimeException,"pthread_attr_init failed");

		if (_stacksize)
			if (pthread_attr_setstacksize(&attr, _stacksize))
				THROWEXCEPTIONPTR1(RuntimeException,"pthread_attr_setstacksize failed");

		if (_daemon)
			if (pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED))
				THROWEXCEPTIONPTR1(RuntimeException,"pthread_attr_setdetachstate failed");

		if (pthread_create(&_tid, &attr, start_routine, this))
			THROWEXCEPTIONPTR1(RuntimeException,"pthread_create failed");

		if (pthread_attr_destroy(&attr))
			THROWEXCEPTIONPTR1(RuntimeException,"pthread_attr_destroy failed");
	}
	else
	{
		if (pthread_create(&_tid, 0, start_routine, this))
			THROWEXCEPTIONPTR1(RuntimeException,"pthread_create failed");
	}
	# else
	#  error
	# endif
	_thr = _tid;
	#endif

	_state = Thread::RUNNABLE;

	monitor->unlock();
}

const String& Thread::getName() const throw ()
{
	return _name;
}

Thread::State Thread::getState() const throw ()
{
	return _state;
}

void Thread::interrupt()
{
	monitor->lock();

	if (_state == Thread::WAITING || _state == Thread::TIMED_WAITING)
		_monitoring->interrupt(_tid);
	else
		_interrupted = true;

	monitor->unlock();
}

bool Thread::interrupted()
{
	if (_monitoring->interrupted(_tid) || _interrupted)
	{
		_interrupted = false;
		return true;
	}
	return false;
}

bool Thread::isAlive() const throw ()
{
	switch (_state)
	{
	case Thread::NEW:
	case Thread::TERMINATED:
		return false;
	default:
		return true;
	}
}

bool Thread::isDaemon() const throw ()
{
	return _daemon;
}

bool Thread::isInterrupted() const throw ()
{
	return _interrupted || _monitoring->isInterrupted(_tid);
}

void Thread::join() throw (InterruptedExceptionPtr)
{
	monitor->lock();
	if (_state != Thread::NEW)
	{
		while (_state != Thread::TERMINATED)
		{
			monitor->unlock();
			_joiner->lock();
			_joiner->wait(0);
			_joiner->unlock();
			monitor->lock();
		}
	}
	monitor->unlock();
}
void Thread::join(jint timeout) throw (InterruptedExceptionPtr)
{
	monitor->lock();
	if (_state != Thread::NEW)
	{
		while (_state != Thread::TERMINATED)
		{
			monitor->unlock();
			_joiner->lock();
			_joiner->wait(timeout);
			_joiner->unlock();
			monitor->lock();
		}
	}
	monitor->unlock();
}

void Thread::run()
{
}

void Thread::setDaemon(bool on) throw (IllegalThreadStateExceptionPtr)
{
	if (_state != NEW)
		THROWEXCEPTIONPTR1(IllegalThreadStateException,"Thread was already started");

	_daemon = on;
}

string Thread::toString() const throw ()
{
	return StringBuilder("Thread[").append(getName()).append("]").toString();
}
