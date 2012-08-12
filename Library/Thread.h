#ifndef __THREAD_H__
#define __THREAD_H__

namespace ali
{
	class Thread
	{
	public:
		Thread();

		// Start thread
		void start();

		// Get if running
		bool isRunning();

		// Wait for thread to end
		bool wait();

		// Terminate the thread straight away (avoid unless necessary)
		void terminate();

	private:
		virtual void run() = 0;

		// Whether the thread is still running
		bool running;

		// Thread handle
		void* thread;

		// Windows thread function
		static unsigned long threadFunc(void* ptr);
		friend unsigned long threadFunc(void* ptr);

		// POSIX thread function
		static void* threadProc(void* ptr);
		friend void* threadProc(void* ptr);
	};
}

#endif /* __THREAD_H__ */
