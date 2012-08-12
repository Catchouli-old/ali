#ifndef __FILE_H_
#define __FILE_H_

#include "Mem.h"
#include "OpenFileException.h"

namespace ali
{
	// Represents a file
	class File
	{
	public:
		File();
		File(const char* filename, bool create = true, bool append = true, bool lock = false);
		~File();

		// Check if file exists
		static bool exists(const char* filename);

		// Open or create file
		bool open(const char* filename, bool create = true, bool append = true, bool lock = false);

		// Flush changes
		void flush();

		// Close handle
		void close();

		// Get if open
		bool isOpen();

		// Get length
		int getLength();

		// Reads up to length bytes - read whole file if length = -1
		int read(char* buffer, int length = -1, int start = 0);

		// Write over file
		int write(const char* buffer, int length = -1);

		// Delete file
		void deleteFile();

	private:
		// Whether there's a file open
		bool opened;
		char* filename;

		// File handle
		void* file;
		int fd;
	};
}

#endif /* __FILE_H_ */
