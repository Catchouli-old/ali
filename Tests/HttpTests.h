#ifndef __HTTPTESTS_H__
#define __HTTPTESTS_H__

#include "Test.h"

#include <HttpConnection.h>

class HttpTests
	: public Test
{
public:
	HttpTests();

	void run();
};

#endif /* __HTTPTESTS_H__ */
