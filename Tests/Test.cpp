#include "Test.h"

Test::Test(std::string name)
	: testsRun(0), testsSucceeded(0)
{
	this->name = name;
}

std::string Test::getName()
{
	return name;
}

int Test::getTestsRun()
{
	return testsRun;
}

int Test::getTestsSucceeded()
{
	return testsSucceeded;
}
