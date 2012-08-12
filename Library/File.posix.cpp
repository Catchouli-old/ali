#include "File.h"

#ifndef WIN32

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

namespace ali
{

	bool File::exists(const char* filename)
	{
		// Check if file exists
		static struct stat stats;

		stat(filename, &stats);

		if (S_ISREG(stats.st_mode))
			return true;

		return false;
	}

	bool File::open(const char* filename, bool create, bool append, bool lock)
	{
		if (isOpen())
		{
			close();

			ali::dealloc(this->filename);
		}

		// Set mode
		int oflag = O_RDWR;

		if (create)
			oflag |= O_CREAT;

		if (append)
			oflag |= O_APPEND;

		// Open file descriptor
		fd = ::open(filename, oflag, S_IRWXU);

		if (fd == -1)
		{
			// Reinitialize fd
			fd = -1;

			throw OpenFileException();

			return false;
		}

		opened = true;

		int size = strlen(filename) + 1;
		this->filename = (char*)ali::alloc(size);
		ali::copy(this->filename, (char*)filename, size);

		return true;
	}

	void File::flush()
	{

	}

	void File::close()
	{
		if (fd != -1)
		{
			fd = -1;
			opened = false;
			::close(fd);
		}
	}

	int File::getLength()
	{
		if (fd != -1)
		{
			// Get current position
			off_t position = lseek(fd, 0, SEEK_CUR);

			// Get length
			off_t length = lseek(fd, 0, SEEK_END);

			// Move back
			lseek(fd, position, SEEK_SET);

			return length;
		}

		return 0;
	}

	int File::read(char* buffer, int length, int start)
	{
		if (fd != -1)
		{
			// Read whole file if length == -1
			if (length == -1)
			{
				length = getLength();
				start = 0;
			}

			// Read
			ssize_t read = pread(fd, buffer, length, start);

			if (read >= 0)
			{
				buffer[length] = 0;

				return read;
			}
		}

		return 0;
	}

	int File::write(const char* buffer, int length)
	{
		if (fd != -1)
		{
			// Write whole buffer if length == -1
			if (length == -1)
			{
				length = strlen(buffer);
			}

			ssize_t bytes = ::write(fd, buffer, length);

			if (bytes >= 0)
				return bytes;
		}

		return 0;
	}

	void File::deleteFile()
	{
		if (fd != -1)
		{
			// Delete file
			unlink(filename);

			// Close handle
			close();

			// Free up memory from filename
			ali::dealloc(filename);
			filename = NULL;
		}
	}
}

#endif
