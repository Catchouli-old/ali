#ifndef __THREADTESTS_H__
#define __THREADTESTS_H__

#include "Test.h"
#include "Fib.h"
#include "MutexWaiter.h"

class ThreadTests
	: public Test
{
public:
	ThreadTests();

	void run();
};

#endif /* __THREADTESTS_H__ */
