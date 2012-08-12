#ifndef __ADDRLOOKUPEXCEPTION_H__
#define __ADDRLOOKUPEXCEPTION_H__

#include <exception>

namespace ali
{
	/**
	 * An exception thrown if an address lookup fails
	 */
	class AddrLookupException
		: public std::exception
	{

	};
}

#endif /* __ADDRLOOKUPEXCEPTION_H__ */
