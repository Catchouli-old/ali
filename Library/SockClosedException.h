#ifndef __SOCKCLOSEDEXCEPTION_H__
#define __SOCKCLOSEDEXCEPTION_H__

#include <exception>

namespace ali
{
	/**
	 * An exception thrown if the socket is closed unexpectedly
	 */
	class SockClosedException
		: public std::exception
	{

	};
}

#endif /* __SOCKCLOSEDEXCEPTION_H__ */
