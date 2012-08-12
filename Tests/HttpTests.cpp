#include "HttpTests.h"

HttpTests::HttpTests()
	: Test("Http")
{

}

void HttpTests::run()
{
	HttpConnection conn;
	HttpResponse response;

	begintest("Create HTTP get request and expect 301 redirection");
		// Server will return a redirect to www.acunliffe.com
		conn.addHeader("Host", "acunliffe.com");

		// Send get request
		response = conn.get("www.acunliffe.com", "/");
	endtest(response.code == "301");

	begintest("Create HTTP get request and expect 200 OK");
		// Clear headers to remove invalid Host
		conn.clearHeaders();

		// Send get request
		response = conn.get("www.acunliffe.com", "/static.html");
	endtest(response.code == "200");

	begintest("Create HTTP get request and check contents");
		// Send get request
		response = conn.get("www.acunliffe.com", "/static.html");
	endtest(response.code == "200" && response.body == "If you can see this, you're blind.");

	begintest("Download 1MB testfile and save to file");
		// Send get request
		response = conn.get("www.acunliffe.com", "/1MB.test");

		response.saveBody("1MB.test");
		ali::File("1MB.test").deleteFile();
	endtest(response.code == "200");
}
