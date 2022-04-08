#ifndef CRIOS_VFSFILESYSTEM_H
#define CRIOS_VFSFILESYSTEM_H

#include "VFSEntry.h"
#include "Filesystem.h"

class VFSFilesystem
{
public:
	virtual File* open(VFSEntry* entry, FileOpenMode mode) = 0;

	virtual VFSEntry* createVFSTree() = 0;
};


#endif //CRIOS_VFSFILESYSTEM_H
