#include "Socket.h"

#ifdef WIN32

#include <winsock2.h>
#include <ws2tcpip.h>

namespace ali
{
	Socket::~Socket()
	{
		close();

		if (address != NULL)
			freeaddrinfo(address);
	}

	void Socket::connect(const char* addr, const char* port)
	{
		// Default hints
		addrinfo hints;
		memset(&hints, 0, sizeof(hints));
		hints.ai_family = AF_UNSPEC;
		hints.ai_socktype = SOCK_STREAM;
		hints.ai_protocol = IPPROTO_TCP;

		// Look up address
		if (address != NULL)
			freeaddrinfo(address);
		address = lookup(addr, port, &hints);

		// Create socket
		currentAddress = address;
		connected = connect();
	}

	void Socket::send(const char* buffer)
	{
		if (connected)
		{
			int result = ::send(sock, buffer, strlen(buffer), 0);

			if (result == SOCKET_ERROR)
			{
				close();
				throw SockClosedException();
			}
		}
	}

	int Socket::read(char* buffer, int length)
	{
		if (connected)
		{
			int result = ::recv(sock, buffer, length-1, 0);
			if (result > 0)
			{
				buffer[result] = 0;
			}

			return result;
		}

		return 0;
	}

	/**
	 * Close this socket
	 */
	void Socket::close()
	{
		if (sock != INVALID_SOCKET)
		{
			closesocket(sock);
			connected = false;
			sock = INVALID_SOCKET;
		}
	}

	/**
	 * Close this socket for sending
	 */
	void Socket::endSend()
	{
		int result = shutdown(sock, SD_SEND);
		if (result == SOCKET_ERROR)
		{
			close();
			throw SockClosedException();
		}
	}

	/**
	 * Attepmts to connect initialised socket
	 */
	bool Socket::connect()
	{
		sock = socket(currentAddress->ai_family, currentAddress->ai_socktype, currentAddress->ai_protocol);
		if (sock == INVALID_SOCKET)
		{
			throw CreateSocketException();
			currentAddress = NULL;
			return false;
		}

		// Connect socket
		int result = ::connect(sock, currentAddress->ai_addr, (int)currentAddress->ai_addrlen);
		if (result == SOCKET_ERROR)
		{
			closesocket(sock);
			sock = INVALID_SOCKET;

			return false;
		}

		return true;
	}

	/**
	 * Attempt to resolve address
	 */
	addrinfo* Socket::lookup(const char* addr, const char* port, addrinfo* hints)
	{
		addrinfo* addressInfo;

		int lookupFailed = getaddrinfo(addr, port, hints, &addressInfo);
		if (lookupFailed)
		{
			throw AddrLookupException();
		}

		return addressInfo;
	}

	// A static member of Socket which automatically initialises
	// and cleans up sockets at the start and end of the program
	SockInfo Socket::init;
}

#endif
