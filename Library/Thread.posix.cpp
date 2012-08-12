#include "Thread.h"

#ifndef WIN32

#include <pthread.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>

#include "Mem.h"

namespace ali
{
	static void sigusr1Handler(int sig);

	void Thread::start()
	{
		if (thread == NULL)
		{
			// Initialise thread handle
			thread = ali::alloc(sizeof(pthread_t));
			ali::zero(thread, sizeof(pthread_t));

			running = true;

			// Create thread and pass this pointer to it
			int result = pthread_create((pthread_t*)thread, NULL, threadProc, this);

			// If failed
			if (result != 0)
			{
				ali::dealloc((pthread_t*)thread);
				thread = NULL;
				running = false;
			}
		}
	}

	bool Thread::wait()
	{
		if (thread != NULL)
		{
			int result = pthread_join(*(pthread_t*)thread, NULL);

			if (result == 0)
				return true;
		}

		return false;
	}

	void* Thread::threadProc(void* thread)
	{
		// Get thread instance
		Thread* instance = (Thread*)thread;

		// Run
		instance->run();

		// Running end
		instance->running = false;

		// Clean up handle
		ali::dealloc((pthread_t*)instance->thread);
		instance->thread = NULL;

		return 0;
	}

	void Thread::terminate()
	{
		if (thread != NULL)
		{
			pthread_cancel(*(pthread_t*)thread);
		}
	}

	// Interrupt nanosleep
	static void sigusr1Handler(int sig)
	{
		signal(sig, sigusr1Handler);
		return;
	}
}

#endif
