#ifndef __MEMORY_H__
#define __MEMORY_H__

#include <cstring>

namespace ali
{
	// Allocate size bytes of memory on heap
	void* alloc(size_t size);

	// Free memory at src
	void dealloc(void* src);

	// Copy memory from one location to another
	void copy(void* dst, void* src, size_t size);

	// Set memory block to a specific value
	void set(void* dst, size_t size, char value);

	// Set memory block to a specific value
	void zero(void* dst, size_t size);
}

#endif /* __MEMORY_H__ */
