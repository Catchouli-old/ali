#ifndef __MEMTEST_H__
#define __MEMTEST_H__

#include "Test.h"

#include <Mem.h>

class MemTests
	: public Test
{
public:
	MemTests();

	void run();
};

#endif /* __MEMTEST_H__ */
