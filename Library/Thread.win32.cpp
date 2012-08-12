#include "Thread.h"

#ifdef WIN32

#include <windows.h>

namespace ali
{
	void Thread::start()
	{
		if (thread == NULL)
		{
			// Create thread and pass this pointer to it
			DWORD id;
			thread = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)threadFunc, this, 0, &id);
			running = true;
		}
	}

	bool Thread::wait()
	{
		if (thread != NULL)
		{
			DWORD result = WaitForSingleObject(thread, INFINITE);

			// If wait successful, return true
			if (result == WAIT_OBJECT_0)
				return true;
		}

		return false;
	}

	unsigned long Thread::threadFunc(void* thread)
	{
		// Get thread instance
		Thread* instance = (Thread*)thread;

		// Set running
		instance->running = true;
		
		// Run
		instance->run();

		// Running end
		instance->running = false;

		// Clean up handle
		CloseHandle(instance->thread);
		instance->thread = NULL;

		return 0;
	}

	void Thread::terminate()
	{
		if (thread != NULL)
		{
			TerminateThread(thread, 0);
		}
	}
}

#endif
