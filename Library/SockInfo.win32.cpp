#include "SockInfo.h"

#ifdef WIN32

#include <winsock2.h>

namespace ali
{
	SockInfo::SockInfo()
	{
		WSADATA data;
		int initFailed = WSAStartup(MAKEWORD(2, 2), &data);
		
		// If initialisation failed
		if (initFailed)
		{
			// Throw exception
			throw SockInitException();
		}
	}

	SockInfo::~SockInfo()
	{
		WSACleanup();
	}
}

#endif
