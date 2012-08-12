#include "Mutex.h"

#ifndef WIN32

#include <pthread.h>

#include "Mem.h"

namespace ali
{
	Mutex::Mutex()
		: handle(NULL)
	{
		handle = ali::alloc(sizeof(pthread_mutex_t));
		ali::zero(handle, sizeof(pthread_mutex_t));

		int result = pthread_mutex_init((pthread_mutex_t*)handle, NULL);

		// If failed
		if (result != 0)
		{
			ali::dealloc(handle);
			handle = NULL;
		}
	}

	Mutex::~Mutex()
	{
		if (handle != NULL)
		{
			pthread_mutex_destroy((pthread_mutex_t*)handle);
			ali::dealloc(handle);
			handle = NULL;
		}
	}

	void Mutex::wait()
	{
		if (handle != NULL)
		{
			pthread_mutex_lock((pthread_mutex_t*)handle);
		}
	}

	bool Mutex::trywait()
	{
		if (handle != NULL)
		{
			int result = pthread_mutex_trylock((pthread_mutex_t*)handle);

			if (result == 0)
				return true;
		}

		return false;
	}

	bool Mutex::release()
	{
		if (handle != NULL)
		{
			int result = pthread_mutex_unlock((pthread_mutex_t*)handle);

			if (result == 0)
				return true;
		}

		return false;
	}
}

#endif
