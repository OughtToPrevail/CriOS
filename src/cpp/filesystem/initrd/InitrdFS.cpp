#include "InitrdFS.h"
#include "NullFile.h"
#include "String.h"
#include "Memory.h"

InitrdFS::InitrdFS(const ModuleEntry& module)
{
	this->_fsStructure.totalFiles = *((unsigned int*) module.startAddress);
	this->_fsStructure.files = new InitrdFileStructure[this->_fsStructure.totalFiles]{};
	unsigned int position = module.startAddress + sizeof(unsigned int);
	for(unsigned int i = 0; i < this->_fsStructure.totalFiles; i++)
	{
		InitrdFileStructure& structure = this->_fsStructure.files[i];
		structure.size = *((unsigned int*) position);
		position += sizeof(unsigned int);
		structure.name = (char*) position;
		position += String::strlen(structure.name) + 1;
		structure.content = (char*) position;
		position += structure.size;
	}
}

File* InitrdFS::open(VFSEntry* entry, FileOpenMode mode)
{
	if(entry->fileSystemEntry == nullptr || mode == FileOpenMode::READ_AND_WRITE)
	{
		return new NullFile();
	}
	return new InitrdFile((InitrdFileStructure*) entry->fileSystemEntry);
}

VFSEntry* InitrdFS::createVFSTree()
{
	VFSEntry* root = new VFSEntry{"root", {}, nullptr, true};
	for(unsigned int i = 0; i < _fsStructure.totalFiles; i++)
	{
		InitrdFileStructure& structure = this->_fsStructure.files[i];
		root->children.pushBack(new VFSEntry{structure.name, {}, &structure, true});
	}
	return root;
}
