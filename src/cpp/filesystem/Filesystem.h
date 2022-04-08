#ifndef CRIOS_FILESYSTEM_H
#define CRIOS_FILESYSTEM_H

#include "File.h"

enum class FileOpenMode
{
	READ,
	READ_AND_WRITE
};

class Filesystem
{
public:
	virtual File* open(const char* path, FileOpenMode mode) = 0;
};


#endif //CRIOS_FILESYSTEM_H
