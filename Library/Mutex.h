#ifndef __MUTEX_H__
#define __MUTEX_H__

namespace ali
{
	class Mutex
	{
	public:
		Mutex();
		~Mutex();

		// Wait for mutex indefinitely
		void wait();

		// Return instantly if mutex unavailable
		bool trywait();

		bool release();

	private:
		void* handle;
	};
}

#endif
