#ifndef __FIB_H__
#define __FIB_H__

#include <Thread.h>
#include <Mutex.h>

class Fib
	: public Thread
{
public:
	void run()
	{
		const int n = 45;

		// Calculate nth fibonacci number (in a crude manner)
		value = 1;
		long long u = 0;
		long long t = 0;
		for (int i = 1; i < n; ++i)
		{
			t = u + value;
			u = value;
			value = t;
		}
	}

	long long getValue()
	{
		return value;
	}

private:
	long long value;
};

#endif /* __FIB_H__ */
