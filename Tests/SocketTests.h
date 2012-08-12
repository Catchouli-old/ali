#ifndef __HTTPTEST_H__
#define __HTTPTEST_H__

#include "Test.h"

#include <Socket.h>
#include <HttpConnection.h>

class SocketTests
	: public Test
{
public:
	SocketTests();

	void run();
};

#endif /* __HTTPTEST_H__ */
