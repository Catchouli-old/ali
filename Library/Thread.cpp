#include "Thread.h"

namespace ali
{
	Thread::Thread()
		: running(false), thread(0)
	{

	}

	bool Thread::isRunning()
	{
		return running;
	}
}
