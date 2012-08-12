#ifndef __SockInfo_H__
#define __SockInfo_H__

#include "SockInitException.h"

namespace ali
{
	class Socket;

	/**
	 * Initialise sockets
	 * Called at the start of program execution
	 */
	class SockInfo
	{
	private:
		// Init
		SockInfo();

		// Cleanup
		~SockInfo();

		friend class Socket;
	};
}

#endif /* __SockInfo_H__ */
