#include "VFS.h"
#include "String.h"
#include "DirIterator.h"

VFSEntry VFS::INVALID_ENTRY{"", {}, nullptr, false};

VFS::VFS(VFSFilesystem* filesystem) : _root(filesystem->createVFSTree()), _realFileSystem(filesystem)
{

}

VFS::~VFS()
{
	this->cleanEntry(this->_root);
}

File* VFS::open(const char* path, FileOpenMode mode)
{
	(void) mode;
	VFSEntry* entry = this->traversePath(path, this->_root);
	return this->_realFileSystem->open(entry, mode);
}

VFSEntry* VFS::traversePath(const char* path, VFSEntry* current)
{
	if(path[0] != '/')
	{
		return &VFS::INVALID_ENTRY;
	}
	unsigned int len = String::strlen(path);
	if(len <= 1)
	{
		return current;
	}
	unsigned int pathLen = len - 1;
	for(unsigned int i = 1; i < len; i++)
	{
		if(path[i] == '/')
		{
			pathLen = i - 1;
		}
	}
	if(String::strcmp(path + 1, current->name, pathLen, String::strlen(current->name)))
	{
		if(pathLen + 1 == len)
		{
			return current;
		}
		for(VFSEntry* entry : current->children)
		{
			VFSEntry* res = VFS::traversePath(path + 1 + pathLen, entry);
			if(res->valid)
			{
				return res;
			}
		}
	}
	return &VFS::INVALID_ENTRY;
}

void VFS::cleanEntry(VFSEntry* entry)
{
	for(VFSEntry* other : entry->children)
	{
		this->cleanEntry(other);
	}
	delete entry;
}

DirIterator VFS::listdir(const char* path)
{
	VFSEntry* entry = traversePath(path, this->_root);
	return DirIterator(entry);
}
