#ifndef __SOCKET_H__
#define __SOCKET_H__

#include "SockInfo.h"
#include "AddrLookupException.h"
#include "CreateSocketException.h"
#include "SockClosedException.h"

// Forward declarations for socket types
struct addrinfo;
typedef unsigned int SOCKET;

namespace ali
{
	/**
	 * A simple client socket class that implements blocking sockets
	 */
	class Socket
	{
	public:
		Socket();
		Socket(const char* addr, const char* port);
		~Socket();

		// Resolve addre	ss and create socket
		void connect(const char* addr, const char* port);

		// Send contents of buffer over socket
		void send(const char* buffer);

		// Perform a blocked read into buffer
		int read(char* buffer, int length);

		// Whether the socket is connected
		bool getConnected();

		// Close socket completely
		void close();

		// Close socket for sending
		void endSend();

		// Look up address
		static addrinfo* lookup(const char* addr, const char* port, addrinfo* hints);

	private:
		bool connect();

		SOCKET sock;
		bool connected;
		addrinfo* address;
		addrinfo* currentAddress;

		// Static member which automatically initialises sockets
		static SockInfo init;
	};
}


#endif /* __SOCKET_H__ */
