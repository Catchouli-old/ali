#include "HttpResponse.h"

namespace ali
{
	HttpResponse::HttpResponse()
	{

	}

	HttpResponse::HttpResponse(std::string address, std::string path, std::string port)
		: address(address), path(path), port(port)
	{

	}

	void HttpResponse::parse(std::string response)
	{
		// Store full response
		full = response;

		// Iterate through response line by line
		std::stringstream ss(full);
		
		// Status
		bool gotResponse = false;
		bool gotHeaders = false;

		std::string line;
		int start = 0;
		while (std::getline(ss, line, '\n'))
		{
			// Remove trailing \r
			std::replace(line.end()-1, line.end(), '\r', '\0');

			if (!gotResponse)
			{
				// Parse response
				std::stringstream res(line);

				// Get protocol and code
				res >> protocol;
				res >> code;

				gotResponse = true;
			}
			else if (!gotHeaders)
			{
				// Check if we have a blank line (headers are over)
				if (line[0] == '\0')
				{
					gotHeaders = true;

					// Store position
					start = (int)ss.tellg();
				}
				else
				{
					// Parse header
					std::stringstream header(line);
					std::string key, value;

					// Get key and value
					header >> key;
					header >> value;

					// Remove trailing : from key
					std::replace(key.end()-1, key.end(), ':', '\0');

					// Insert into headers map
					headers[key] = value;
				}
			}
		}

		// Get remaining body
		ss.clear();
		HeaderMap::iterator lb = headers.lower_bound("Content-Length");

		if (lb != headers.end())
		{
			// Get length
			int length = atoi(lb->second.c_str());

			if (length > 0)
			{
				// Save contents
				body.resize(length);
				body = std::string(response, start, length-1);
			}
		}
	}

	void HttpResponse::saveBody(std::string filename)
	{
		// Find content length
		HeaderMap::iterator lb = headers.lower_bound("Content-Length");
		
		if (lb != headers.end())
		{
			int length = atoi(lb->second.c_str());

			if (length > 0)
			{
				File file(filename.c_str());
				file.write(body.c_str(), length);
				file.close();
			}
		}

	}
}
