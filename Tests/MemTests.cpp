#include "MemTests.h"

#include <Socket.h>

MemTests::MemTests()
	: Test("Memory")
{

}

void MemTests::run()
{
	// Whether the current test succeded
	bool success = false;

	// A test structure
	const unsigned int length = 64;
	struct TestStruct
	{
		char data[length];
	};
	
	// Pointers to instances
	TestStruct* testInstance = NULL;
	TestStruct* testInstance2 = NULL;

	// Size of structure
	int size = sizeof(TestStruct);

	begintest("Allocate " << size << " bytes of memory");
		testInstance = (TestStruct*)ali::alloc(size);
	endtest(testInstance != NULL);

	begintest("Deallocate previous " << size << " bytes of memory");
		dealloc(testInstance);
		testInstance = NULL;
	endtest(testInstance == NULL);
	
	const int value = 1;
	begintest("Allocate " << size << " bytes and fill with " << value << "s");
		testInstance = (TestStruct*)ali::alloc(size);
		ali::set(testInstance, size, value);

		// Check all values were set right
		success = true;
		for (unsigned int i = 0; i < 64; ++i)
		{
			if (testInstance->data[i] != value)
			{
				success = false;
				break;
			}
		}
	endtest(success);

	begintest("Create second instance and fill it with 0s");
		testInstance2 = (TestStruct*)ali::alloc(size);
		ali::zero(testInstance2, size);

		// Check all values zeroed
		success = true;
		for (unsigned int i = 0; i < 64; ++i)
		{
			if (testInstance2->data[i] != 0)
			{
				success = false;
				break;
			}
		}
	endtest(success);

	begintest("Copy second instance over first");
		ali::copy(testInstance, testInstance2, size);

		// Check all values are now 0
		success = true;
		for (unsigned int i = 0; i < 64; ++i)
		{
			if (testInstance->data[i] != 0)
			{
				success = false;
				break;
			}
		}
	endtest(success);

	begintest("Deallocating null pointer");
		ali::dealloc(NULL);
	endtest(true);

	// Clean up memory
	ali::dealloc(testInstance);
	ali::dealloc(testInstance2);
}
