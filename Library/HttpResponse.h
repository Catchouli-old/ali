#ifndef __HTTPRESPONSE_H__
#define __HTTPRESPONSE_H__

#include <algorithm>
#include <string>
#include <sstream>
#include <map>

#include "File.h"

typedef std::map<std::string, std::string> HeaderMap;

namespace ali
{
	class HttpResponse
	{
	public:
		HttpResponse();
		HttpResponse(std::string address, std::string path, std::string port);

		// Parse a Http response
		void parse(std::string response);

		// Save body as file
		void saveBody(std::string filename);

		std::string address, path, port;

		// The full response as a string
		std::string full;

		// The parsed response
		std::string protocol, code;
		HeaderMap headers;
		std::string body;
	};
}

#endif /* __HTTPRESPONSE_H__ */
