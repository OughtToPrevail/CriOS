#ifndef CRIOS_VFS_H
#define CRIOS_VFS_H


#include "Filesystem.h"
#include "VFSEntry.h"
#include "VFSFilesystem.h"
#include "DirIterator.h"

class VFS : public Filesystem
{
public:
	explicit VFS(VFSFilesystem* filesystem);
	virtual ~VFS();

	File* open(const char* path, FileOpenMode mode) override;
	DirIterator listdir(const char* path);
private:
	VFSEntry* traversePath(const char* path, VFSEntry* current);
	void cleanEntry(VFSEntry* entry);

	VFSEntry* _root;
	VFSFilesystem* _realFileSystem;

	static VFSEntry INVALID_ENTRY;
};


#endif //CRIOS_VFS_H
