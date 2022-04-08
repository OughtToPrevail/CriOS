#include "IdentityPaging.h"

#define PAGE_SIZE (4096)


void IdentityPaging::setupPaging()
{
	unsigned int memoryLocation = 0;
	for(unsigned int i = 0; i < PAGE_DIRECTORY_ENTRIES_COUNT; i++)
	{
		PageTable& table = this->_tables[i];
		PageDirectoryEntry& directoryEntry = this->_directory[i];
		directoryEntry.present = 1;
		directoryEntry.readWrite = 1;
		directoryEntry.user = 1;  // TODO: Change it so not all memory is user accessible
		directoryEntry.pageSize = 0;
		directoryEntry.pageTableAddress = ((unsigned int) table.entries) >> 12;
		for(PageTableEntry& tableEntry : table.entries)
		{
			tableEntry.present = 1;
			tableEntry.readWrite = 1;
			tableEntry.user = 1;
			tableEntry.pageSize = 0;
			tableEntry.pageFrameAddress = memoryLocation >> 12;
			memoryLocation += PAGE_SIZE;
		}
	}
}
