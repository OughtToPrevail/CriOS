#include "NullFile.h"

void NullFile::write(char* buffer, unsigned int size)
{
	(void) buffer;
	(void) size;
}

unsigned int NullFile::read(char* buffer, unsigned int size)
{
	(void) buffer;
	(void) size;
	return 0;
}

const char* NullFile::getFileName()
{
	return "NullFile";
}

unsigned int NullFile::getFileSize()
{
	return 0;
}
