#include "Mem.h"

#ifndef WIN32

#include <stdlib.h>
#include <string.h>

namespace ali
{
	void* alloc(size_t size)
	{
		return malloc(size);
	}

	void dealloc(void* src)
	{
		free(src);
	}

	void copy(void* dst, void* src, size_t size)
	{
		memcpy(dst, src, size);
	}

	void set(void* dst, size_t size, char value)
	{
		memset(dst, value, size);
	}

	void zero(void* dst, size_t size)
	{
		memset(dst, 0, size);
	}
}

#endif
