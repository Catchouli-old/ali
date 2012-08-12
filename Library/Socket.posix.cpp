#include "Socket.h"

#ifndef WIN32

#define NULL 0

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#include "Mem.h"

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
		ali::zero(&hints, sizeof(hints));
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

			if (result == -1)
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
		if (sock != 0)
		{
			::close(sock);
			connected = false;
			sock = 0;
		}
	}

	/**
	 * Close this socket for sending
	 */
	void Socket::endSend()
	{
		if (sock != 0)
		{
			int result = shutdown(sock, SHUT_WR);
			if (result == -1)
			{
				close();
				throw SockClosedException();
			}
		}
	}

	/**
	 * Attepmts to connect initialised socket
	 */
	bool Socket::connect()
	{
		sock = socket(currentAddress->ai_family, currentAddress->ai_socktype, currentAddress->ai_protocol);
		if (sock < 0)
		{
			throw CreateSocketException();
			currentAddress = NULL;
			return false;
		}

		// Connect socket
		int result = ::connect(sock, currentAddress->ai_addr, (int)currentAddress->ai_addrlen);
		if (result < 0)
		{
			::close(sock);
			sock = 0;

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

		int result = getaddrinfo(addr, port, hints, &addressInfo);
		if (result)
		{
			throw AddrLookupException();
		}

		return addressInfo;
	}
}

#endif
