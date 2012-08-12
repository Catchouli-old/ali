#ifndef __OPENFILEEXCEPTION_H__
#define __OPENFILEEXCEPTION_H__

#include <exception>

namespace ali
{
	/**
	 * An exception thrown if an attempt to open a file fails
	 */
	class OpenFileException
		: public std::exception
	{

	};
}

#endif /* __OPENFILEEXCEPTION_H__ */
