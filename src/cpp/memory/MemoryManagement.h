#ifndef OSTEST_MEMORYMANAGEMENT_H
#define OSTEST_MEMORYMANAGEMENT_H

struct HeapFlag
{
	unsigned char allocated:1;
	unsigned int size:31;
} __attribute__((packed));

class MemoryManagement
{
public:
	static void initHeap();

	static void* malloc(unsigned int size);
	static void free(void* p);
private:
	static unsigned int heapStart;

	static void modifyHeapFlag(unsigned int address, unsigned int size, bool allocated);
	static unsigned int align(unsigned int size);
	static unsigned int getSize(HeapFlag* heapFlag);
	static HeapFlag* getHeapFlag(unsigned int address);
};

void* malloc(unsigned int size);
void free(void* p);

#endif //OSTEST_MEMORYMANAGEMENT_H
