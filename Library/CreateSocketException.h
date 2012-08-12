#ifndef __CREATESOCKETEXCEPTION_H__
#define __CREATESOCKETEXCEPTION_H__

#include <exception>

namespace ali
{
	/**
	 * An exception thrown if an attempt to create a socket fails
	 */
	class CreateSocketException
		: public std::exception
	{

	};
}

#endif /* __CREATESOCKETEXCEPTION_H__ */
