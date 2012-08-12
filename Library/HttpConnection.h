#ifndef __HTTPCONNECTION_H__
#define __HTTPCONNECTION_H__

#include <iostream>
#include <string>
#include <sstream>
#include <map>

#include "Socket.h"
#include "HttpResponse.h"

#define CRLF "\r\n"

namespace ali
{
	class HttpConnection
		: protected Socket
	{
	public:
		HttpConnection();

		// Make a HTTP/1.1 GET request
		HttpResponse get(std::string address, std::string path, std::string port = "80");

		// Add a header to be sent with requests
		void addHeader(std::string key, std::string value);

		// Clear all headers
		void clearHeaders();

	private:
		HeaderMap headers;
	};
}

#endif /* __HTTPCONNECTION_H__ */
