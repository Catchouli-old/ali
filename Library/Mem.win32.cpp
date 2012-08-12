#include "Mem.h"

#ifdef WIN32

#include <windows.h>

namespace ali
{
	/**
	 * Windows API functions have been used, but malloc() etc could be used like the POSIX version
	 */

	void* alloc(size_t size)
	{
		return HeapAlloc(GetProcessHeap(), 0, size);
	}

	void dealloc(void* src)
	{
		if (src != NULL)
			HeapFree(GetProcessHeap(), 0, src);
	}

	void copy(void* dst, void* src, size_t size)
	{
		CopyMemory(dst, src, size);
	}

	void set(void* dst, size_t size, char value)
	{
		FillMemory(dst, size, value);
	}

	void zero(void* dst, size_t size)
	{
		ZeroMemory(dst, size);
	}
}

#endif
