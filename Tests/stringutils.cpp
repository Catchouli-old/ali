#include "stringutils.h"

#include <random>
#include <Mem.h>

char* generateString(unsigned int length)
{
	if (length > 0)
	{
		// Alphanumeric lookup table
		static const char alphanumeric[] = 
			"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
		static const int characters = sizeof(alphanumeric) - 1;
		
		// Allocate memory for string + 1 character for null terminator
		char* string = (char*)ali::alloc(length+1);

		// Loop through each character in resultant string
		for (unsigned int i = 0; i < length; ++i)
		{
			// Pick random character from table
			string[i] = alphanumeric[rand() % characters];
		}

		// Add null terminator
		string[length] = 0;

		return string;
	}

	return NULL;
}
