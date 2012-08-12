#include <iostream>
#include <vector>
#include <exception>
#include <cassert>

#include "HttpConnection.h"

#include "MemTests.h"
#include "FileTests.h"
#include "SocketTests.h"
#include "HttpTests.h"
#include "ThreadTests.h"

int main(int argc, char** argv)
{
	// Run tests
	std::vector<Test*> tests;

	// Create tests
	tests.push_back(new MemTests());
	tests.push_back(new FileTests());
	tests.push_back(new SocketTests());
	tests.push_back(new HttpTests());
	tests.push_back(new ThreadTests());

	// Run all tests
	int failed = 0;
	for (std::vector<Test*>::iterator it = tests.begin(); it != tests.end(); ++it)
	{
		Test* test = *it;

		std::cout << "Running " << test->getName() << " tests." << std::endl;

		// Run test
		test->run();

		std::cout << "Finished running " << test->getTestsRun() << " tests, "
			<< test->getTestsSucceeded() << " succeeded" << std::endl << std::endl;

		// Update failed
		failed += (test->getTestsRun() - test->getTestsSucceeded());
	}

	// If any tests failed
	if (failed > 0)
	{
		std::cout << failed << " tests failed" << std::endl;
	}

	// Clean up memory
	for (std::vector<Test*>::iterator it = tests.begin(); it != tests.end(); ++it)
	{
		delete *it;
	}

	// Wait for user input
	std::cout << std::endl << "All tests complete. Press return to continue.";
	std::cin.get();
	return 0;
}
