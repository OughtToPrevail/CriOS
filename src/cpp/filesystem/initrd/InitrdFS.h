#ifndef CRIOS_INITRDFS_H
#define CRIOS_INITRDFS_H


#include "VFSFilesystem.h"
#include "Multiboot.h"
#include "InitrdFile.h"

struct InitrdFSStructure
{
	unsigned int totalFiles;
	InitrdFileStructure* files;
};

class InitrdFS : public VFSFilesystem
{
public:
	explicit InitrdFS(const ModuleEntry& module);

	File* open(VFSEntry* entry, FileOpenMode mode) override;

	VFSEntry* createVFSTree() override;
private:
	InitrdFSStructure _fsStructure;
};


#endif //CRIOS_INITRDFS_H
