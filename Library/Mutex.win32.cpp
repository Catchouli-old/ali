#include "Mutex.h"

#ifdef WIN32

#include <windows.h>

namespace ali
{
	Mutex::Mutex()
		: handle(NULL)
	{
		handle = CreateMutex(NULL, FALSE, NULL);
	}

	Mutex::~Mutex()
	{
		if (handle != NULL)
		{
			CloseHandle(handle);
		}
	}

	void Mutex::wait()
	{
		if (handle != NULL)
		{
			WaitForSingleObject(handle, INFINITE);
		}
	}

	bool Mutex::trywait()
	{
		if (handle != NULL)
		{
			DWORD result = WaitForSingleObject(handle, 0);

			if (result == WAIT_OBJECT_0)
				return true;
		}

		return false;
	}

	bool Mutex::release()
	{
		if (handle != NULL)
		{
			return (ReleaseMutex(handle) != 0);
		}

		return false;
	}
}

#endif
