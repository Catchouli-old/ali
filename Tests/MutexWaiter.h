#ifndef __MUTEXWAITER_H__
#define __MUTEXWAITER_H__

#include <Thread.h>
#include <Mutex.h>

class MutexWaiter
	: public Thread
{
public:
	void run()
	{
		if (mutex != NULL)
		{
			mutex->wait();
			mutex->release();
		}
	}

	void setMutex(Mutex* m)
	{
		mutex = m;
	}

private:
	Mutex* mutex;
};

#endif /* __MUTEXWAITER_H__ */
