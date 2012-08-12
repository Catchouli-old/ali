#include "SocketTests.h"

SocketTests::SocketTests()
	: Test("Socket")
{

}

void SocketTests::run()
{
	begintest("Create socket using default constructor");
		Socket sock;
	endtest(!sock.getConnected());

	begintest("Attempt connection to google server");
		sock.connect("google.com", "80");
	endtest(sock.getConnected());

	begintest("Close socket for sending");
		sock.endSend();
	endtest(sock.getConnected());

	begintest("Close connection");
		sock.close();
	endtest(!sock.getConnected());

	begintest("Create socket using connect constructor");
		Socket sock2("google.com", "80");
	endtest(sock2.getConnected());
}
