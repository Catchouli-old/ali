#include "FileTests.h"

FileTests::FileTests()
	: Test("File")
{
	// Seed random number generator with current time
	srand((unsigned int)time(NULL));
}

void FileTests::run()
{
	bool success = false;

	// Generate random strings
	char* filename = generateString(20);
	char* randomString = generateString(100);

	begintest("Create file with random name: " << filename);
		File file(filename);
	endtest(file.isOpen());

	begintest("Write 100 bytes to file");
		int bytesWritten = file.write(randomString);
	endtest(bytesWritten == 100);

	begintest("Close file");
		file.close();
	endtest(!file.isOpen());

	begintest("Open same file by default constructor + call to open()");
		File file2;
		file2.open(filename, false);
	endtest(file2.isOpen());

	begintest("Delete file and check it doesn't exist");
		file2.deleteFile();
	endtest(!File::exists(filename));

	// Generate new filename and string
	ali::dealloc(filename);
	ali::dealloc(randomString);
	filename = generateString(20);
	randomString = generateString(200);

	begintest("Write to file and then read it again");
		success = false;

		// Write to a file
		file.open(filename);
		file.write(randomString);
		file.close();
		file.open(filename);

		// Allocate memory for buffer
		int read = 0;
		char* buffer = (char*)ali::alloc(file.getLength()+1);

		// If read more than 0 bytes
		if ((read = file.read(buffer)) > 0)
		{
			// If read string is identical to written string, success = true
			success = (strcmp(buffer, randomString) == 0);
		}
		
		// Clean up test
		ali::dealloc(buffer);
		file.deleteFile();
	endtest(success);

	// Clean up files
	file.close();
	file2.close();

	// Clean up memory
	ali::dealloc(filename);
	ali::dealloc(randomString);
}
