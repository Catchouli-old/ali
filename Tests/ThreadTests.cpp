#include "ThreadTests.h"



#include <iostream>
ThreadTests::ThreadTests()
	: Test("Thread")
{

}

void ThreadTests::run()
{
	bool success = false;

	begintest("Create new thread instance");
		Fib fib;
	endtest(!fib.isRunning());

	begintest("Run thread and wait for it to finish");
		success = false;
		fib.start();
		fib.wait();

		if (fib.getValue() == 1134903170 && !fib.isRunning())
			success = true;
	endtest(success);

	begintest("Create mutex and bind it")
		Mutex mutex;
	endtest(mutex.trywait());

	begintest("Release mutex");
	endtest(mutex.release());

	begintest("Run thread that waits for mutex without mutex locked");
		success = false;

		// Create thread and run it
		MutexWaiter m;
		m.setMutex(&mutex);
		m.start();

		// See if thread ends
		if (m.wait())
			success = true;
	endtest(success);

	begintest("Run thread that waits for mutex with mutex locked");
		success = false;

		// Lock mutex
		mutex.wait();

		// Run mutex waiter
		m.start();

		// Check if it's returned yet
		if (m.isRunning())
		{
			// Release mutex
			mutex.release();

			// Check if it's returned now
			if (m.wait())
			{
				success = true;
			}
		}
	endtest(success);

	return;
}
