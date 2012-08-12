#ifndef __FILETESTS_H__
#define __FILETESTS_H__

#include "Test.h"
#include "stringutils.h"

#include <random>
#include <File.h>

class FileTests
	: public Test
{
public:
	FileTests();

	void run();
};

#endif /* __FILETESTS_H__ */
