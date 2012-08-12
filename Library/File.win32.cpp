#include "File.h"

#ifdef WIN32

#include <windows.h>

namespace ali
{
	/**
	 * Similar to memory, some posix functions can be used here too,
	 * but for the sake of multi-platform programming I've used windows API calls here
	 */

	bool File::exists(const char* filename)
	{
		// Check if file exists
		DWORD attributes = GetFileAttributes(filename);

		// If file doesn't exist
		if (attributes == 0xFFFFFFFF)
			return false;
		
		return true;
	}

	bool File::open(const char* filename, bool create, bool append, bool lock)
	{
		// Make sure no other file is open
		if (isOpen())
		{
			close();

			ali::dealloc(this->filename);
		}

		// If append == true, attempt to open file for appending
		int access = GENERIC_READ | GENERIC_WRITE;
		
		if (append)
			access |= FILE_APPEND_DATA;

		// If create == true, create file if nonexistent
		int creation = 0;
		if (create)
		{
			if (File::exists(filename))
			{
				creation = OPEN_ALWAYS;
			}
			else
			{
				creation = CREATE_NEW;
			}
		}
		else
		{
			creation = OPEN_ALWAYS;
		}

		// If lock == true, lock file for reading/writing/deletion
		int security = (lock ? 0 : FILE_SHARE_DELETE | FILE_SHARE_READ | FILE_SHARE_WRITE);

		file = CreateFile(	filename,				// The filename
							access,					// Preferred access
							security,				// Whether to lock file
							NULL,
							creation,				// Whether to create if not existent
							FILE_ATTRIBUTE_NORMAL,	// Normal attributes
							NULL);

		if (file == INVALID_HANDLE_VALUE)
		{
			// Reinitialize handle
			file = NULL;

			throw OpenFileException();

			return false;
		}
		else
		{
			opened = true;

			// Save filename
			int size = strlen(filename) + 1;
			this->filename = (char*)ali::alloc(size);
			ali::copy(this->filename, (char*)filename, size);
		}

		return true;
	}

	void File::flush()
	{
		if (file != NULL)
		{
			FlushFileBuffers(file);
		}
	}

	void File::close()
	{
		if (file != NULL)
		{
			FlushFileBuffers(file);

			file = NULL;
			opened = false;
			CloseHandle(file);
		}
	}

	int File::getLength()
	{
		if (file != NULL)
		{
			// Get current position
			DWORD position = SetFilePointer(file, 0, 0, FILE_CURRENT);

			// Get length
			int length = SetFilePointer(file, 0, 0, FILE_END);
		
			// Move back to corrent position
			SetFilePointer(file, length, 0, FILE_BEGIN);

			return length;
		}

		return 0;
	}

	int File::read(char* buffer, int length, int start)
	{
		if (file != NULL)
		{
			// Read whole file if length == -1
			if (length == -1)
			{
				length = getLength();
				start = 0;
			}

			SetFilePointer(file, start, 0, FILE_BEGIN);

			DWORD bytesRead = 0;
			BOOL success = ReadFile(file,				// File handle
									(void*)buffer,		// Buffer to read to
									length,				// Number of bytes to read
									&bytesRead,			// Pointer to bytes actually read
									NULL);

			int test = GetLastError();
			if (success)
			{
				// Write null terminator
				buffer[length] = 0;

				return bytesRead;
			}
		}

		return 0;
	}

	int File::write(const char* buffer, int length)
	{
		if (file != NULL)
		{
			if (length == -1)
			{
				length = strlen(buffer);
			}

			DWORD bytesWritten = 0;
			BOOL success = WriteFile(	file,
										(void*)buffer,
										length,
										&bytesWritten,
										NULL);

			int error = GetLastError();
			
			if (success)
				return bytesWritten;
		}

		return 0;
	}

	void File::deleteFile()
	{
		if (file != NULL)
		{
			// Delete file
			DeleteFile(filename);

			// Flush and close handle
			close();

			// Free up memory from filename
			ali::dealloc(filename);
			filename = NULL;
		}
	}
}

#endif
