#ifndef CRIOS_PAGING_H
#define CRIOS_PAGING_H


struct PageDirectoryEntry
{
	unsigned char present:1;  // 1 present, 0 not present, produces page fault
	unsigned char readWrite:1;  // 1 read write enabled
	unsigned char user:1;  // 1 user created, accessible by all, 0 supervisor mode, only accessable by kernel
	unsigned char pageWriteThrough:1;  // 1 - use write through, 0 - use write-back
	unsigned char pageCacheDisable:1;  // 1 - disabled page caching, 0 - page caching used
	unsigned char accessed:1;  // unused by OS
	unsigned char ignored:1;
	unsigned char pageSize:1;  // 1 - 4 MiB, 0 - 4 KiB
	unsigned char global:1;  // 1 - to not invalidate entry on mov
	unsigned char osData:3;  // 3 bits the OS can use
	unsigned int pageTableAddress:20;  // address to the frame
} __attribute__((packed));


struct PageTableEntry
{
	unsigned char present:1;  // 1 present, 0 not present, produces page fault
	unsigned char readWrite:1;  // 1 read write enabled
	unsigned char user:1;  // 1 user created, accessible by all, 0 supervisor mode, only accessable by kernel
	unsigned char pageWriteThrough:1;  // 1 - use write through, 0 - use write-back
	unsigned char pageCacheDisable:1;  // 1 - disabled page caching, 0 - page caching used
	unsigned char accessed:1;  // unused by OS
	unsigned char dirty:1;  // whether the page was written to
	unsigned char pageSize:1;  // 1 - 4 MiB, 0 - 4 KiB
	unsigned char global:1;  // 1 - to not invalidate entry on mov
	unsigned char osData:3;  // 3 bits the OS can use
	unsigned int pageFrameAddress:20;  // address to the frame
} __attribute__((packed));


#define PAGE_DIRECTORY_ENTRIES_COUNT (1024)
#define PAGE_TABLE_ENTRIES_COUNT (1024)


struct PageTable
{
	PageTableEntry entries[PAGE_TABLE_ENTRIES_COUNT] __attribute__((aligned(4096)));
};


class Paging
{
public:
	Paging();

	void enablePaging();
protected:
	virtual void setupPaging() = 0;

	PageTable _tables[PAGE_DIRECTORY_ENTRIES_COUNT];  // this will be a pointer to the tables in the directory
	PageDirectoryEntry _directory[PAGE_DIRECTORY_ENTRIES_COUNT] __attribute__((aligned(4096)));  // this will be the actual page directory
};

extern "C"
{
	void paging_setPagingDirectory(unsigned int pageTableAddress);
	void paging_enablePaging();
}


#endif //CRIOS_PAGING_H
