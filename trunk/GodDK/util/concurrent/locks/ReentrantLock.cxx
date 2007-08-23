#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "lang/Thread.h"
using goddk::lang::Thread;

#include "util/concurrent/locks/ReentrantLock.h"

using namespace goddk::util::concurrent::locks;

ReentrantLock::Cond::Cond(Object* lock) : lock(lock)
{
}

void ReentrantLock::Cond::await() throw (InterruptedExceptionPtr)
{
	lock->wait(0);
}

void ReentrantLock::Cond::awaitUninterruptibly()
{
	while (true)
	{
		try
		{
			lock->wait(0);

			return;
		}
		catch (InterruptedException&)
		{
		}
	}
}

void ReentrantLock::Cond::signal()
{
	lock->notify();
}

void ReentrantLock::Cond::signalAll()
{
	lock->notifyAll();
}

ReentrantLock::ReentrantLock(bool fair)
{
	monitor = Monitor::getInstance(fair);
}

void ReentrantLock::lock()
{
	Thread* t = Thread::currentThread();

	if (t)
	{
		t->_state = Thread::BLOCKED;
		t->_monitoring = monitor;
	}

	monitor->lock();

	if (t)
	{
		t->_state = Thread::RUNNABLE;
		t->_monitoring = t->monitor;
	}
}

void ReentrantLock::lockInterruptibly() throw (InterruptedExceptionPtr)
{
	bool interrupted = false;

	Thread* t = Thread::currentThread();

	if (t)
	{
		t->_state = Thread::BLOCKED;
		t->_monitoring = monitor;
	}

	try
	{
		monitor->lockInterruptibly();
	}
	catch (InterruptedException&)
	{
		interrupted = true;
	}

	if (t)
	{
		t->_state = Thread::RUNNABLE;
		t->_monitoring = t->monitor;
	}

	if (interrupted)
		throw InterruptedException();
}

Condition* ReentrantLock::newCondition()
{
	return new Cond(this);
}

bool ReentrantLock::tryLock()
{
	bool result;

	Thread* t = Thread::currentThread();

	if (t)
	{
		t->_state = Thread::BLOCKED;
		t->_monitoring = monitor;
	}

	result = monitor->tryLock();

	if (t)
	{
		t->_state = Thread::RUNNABLE;
		t->_monitoring = t->monitor;
	}

	return result;
}

void ReentrantLock::unlock()
{
	monitor->unlock();
}
