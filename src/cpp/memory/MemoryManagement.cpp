#include "MemoryManagement.h"

// padding at the end of the kernel so the heap leaves some space in case of bugs
#define KERNEL_PADDING (1024)

extern unsigned int linkerEnd;

// Based on Implicit List allocating method - https://www.youtube.com/watch?v=74s0m4YoHgM

unsigned int MemoryManagement::heapStart = 0;

void MemoryManagement::initHeap()
{
	MemoryManagement::heapStart = linkerEnd + KERNEL_PADDING;  // room before
	MemoryManagement::modifyHeapFlag(MemoryManagement::heapStart, 0, false);
}

void MemoryManagement::modifyHeapFlag(unsigned int address, unsigned int size, bool allocated)
{
	HeapFlag* heapFlag = MemoryManagement::getHeapFlag(address);
	heapFlag->size = size >> 1;
	heapFlag->allocated = allocated;
}

unsigned int MemoryManagement::align(unsigned int size)
{
	// A way to make sure the size is even (rounds up), leaving the first bit as the allocated flag.

	// This works by first adding one, then "removing it" by pushing it out of the number with >> 1
	// and then returning it as always 0 with << 1, so if it was 2 (10) it would become 3 (11) then be pushed (01) then
	// become 2 (10)
	// But if it were uneven, like 3 (011) it would become 4 (100) then pushed 2 (010) and then pushed back 4 (100) and
	// so it's been rounded up to 4
	return ((size + 1) >> 1) << 1;
}

HeapFlag* MemoryManagement::getHeapFlag(unsigned int address)
{
	return reinterpret_cast<HeapFlag*>(reinterpret_cast<char*>(address));
}

unsigned int MemoryManagement::getSize(HeapFlag* heapFlag)
{
	return heapFlag->size << 1;
}

void* MemoryManagement::malloc(unsigned int size)
{
	if(MemoryManagement::heapStart == 0) // not initialized
	{
		return nullptr;
	}
	// find first fit block
	size = MemoryManagement::align(size); // align size first

	unsigned int current = MemoryManagement::heapStart;
	// iterate until we find a block that's not allocated and has enough size
	while(true)
	{
		HeapFlag* heapFlag = MemoryManagement::getHeapFlag(current);
		unsigned int heapFlagSize = MemoryManagement::getSize(heapFlag);
		if(heapFlagSize != 0 && (heapFlag->allocated || heapFlagSize < size))
		{
			current += sizeof(HeapFlag) + heapFlagSize;
			continue;
		}

		unsigned int allocatedBlock = current + sizeof(HeapFlag);
		unsigned int splitBlockSize = heapFlagSize - size;
		if(heapFlagSize == 0)  // at the end of the list
		{
			splitBlockSize = 0;
		}
		modifyHeapFlag(current, size, true);
		modifyHeapFlag(allocatedBlock + size * sizeof(char), splitBlockSize, false);
		return reinterpret_cast<void*>(allocatedBlock);
	}
}

void MemoryManagement::free(void* p)
{
	HeapFlag* heapFlag = getHeapFlag(reinterpret_cast<unsigned int>(p) - sizeof(HeapFlag));
	heapFlag->allocated = false;
}

void* malloc(unsigned int size)
{
	return MemoryManagement::malloc(size);
}

void free(void* p)
{
	MemoryManagement::free(p);
}
