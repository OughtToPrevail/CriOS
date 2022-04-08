#ifndef CRIOS_VFSENTRY_H
#define CRIOS_VFSENTRY_H

#include "Vector.h"


struct VFSEntry
{
	const char* name;
	Vector<VFSEntry*> children;
	void* fileSystemEntry;
	bool valid;
};

#endif //CRIOS_VFSENTRY_H
