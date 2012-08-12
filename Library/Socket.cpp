#include "Socket.h"

#define NULL 0

namespace ali
{
	Socket::Socket()
		: sock(0), connected(false), address(NULL), currentAddress(NULL)
	{

	}

	Socket::Socket(const char* addr, const char* port)
		: sock(0), connected(false), address(NULL), currentAddress(NULL)
	{
		connect(addr, port);
	}

	bool Socket::getConnected()
	{
		return connected;
	}
}
