#include "File.h"

namespace ali
{
	File::File()
		: opened(false), filename(NULL), file(NULL), fd(-1)
	{

	}

	File::File(const char* filename, bool create, bool append, bool lock)
		: opened(false), filename(NULL), file(NULL), fd(-1)
	{
		open(filename, create, append, lock);
	}

	File::~File()
	{
		close();
		ali::dealloc(this->filename);
	}

	bool File::isOpen()
	{
		return opened;
	}
}
