#include "HttpConnection.h"

namespace ali
{
	HttpConnection::HttpConnection()
	{

	}

	HttpResponse HttpConnection::get(std::string address, std::string path, std::string port)
	{
		std::stringstream result;

		connect(address.c_str(), port.c_str());

		// Send request type
		send("GET ");

		// Send path
		send(path.c_str());

		// Send protocol (HTTP 1.1)
		send(" HTTP/1.1");
		send(CRLF);

		// Check if custom address specified and send host otherwise
		// (required for HTTP 1.1)
		HeaderMap::iterator lb = headers.lower_bound("Host");

		// If no host found
		if (lb == headers.end())
		{
			send("Host: ");
			send(address.c_str());
			send(CRLF);
		}

		// Persistent connections not supported
		send("Connection: close");
		send(CRLF);

		// Send other headers
		for (HeaderMap::iterator it = headers.begin(); it != headers.end(); ++it)
		{
			// Send key
			send(it->first.c_str());
			send(": ");

			// Send value
			send(it->second.c_str());
			send(CRLF);
		}

		// Send blank line to complete request
		send(CRLF);

		// Read full response
		int length = 0;
		char buffer[255];
		while ((length = read(buffer, 255)))
		{
			result.write(buffer, length);
		}

		// Parse response
		HttpResponse response(address, path, port);
		response.parse(result.str());

		return response;
	}

	void HttpConnection::addHeader(std::string key, std::string value)
	{
		headers[key] = value;
	}

	void HttpConnection::clearHeaders()
	{
		headers.clear();
	}
}
