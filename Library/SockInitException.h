#ifndef __SOCKINITEXCEPTION_H__
#define __SOCKINITEXCEPTION_H__

#include <exception>

namespace ali
{
	/**
	 * An exception thrown if the socket library fails to initialise
	 */
	class SockInitException
		: public std::exception
	{

	};
}

#endif /* __SOCKINITEXCEPTION_H__ */
