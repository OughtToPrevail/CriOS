#ifndef CRIOS_TSSMANAGER_H
#define CRIOS_TSSMANAGER_H

#include "GDT.h"


// structure taken from: https://wiki.osdev.org/Getting_to_Ring_3
struct TSSEntry {
	unsigned int prevTSS; // The previous TSS - with hardware task switching these form a kind of backward linked list.
	unsigned int esp0;     // The stack pointer to load when changing to kernel mode.
	unsigned int ss0;      // The stack segment to load when changing to kernel mode.
	// Everything below here is unused.
	unsigned int esp1; // esp and ss 1 and 2 would be used when switching to rings 1 or 2.
	unsigned int ss1;
	unsigned int esp2;
	unsigned int ss2;
	unsigned int cr3;
	unsigned int eip;
	unsigned int eflags;
	unsigned int eax;
	unsigned int ecx;
	unsigned int edx;
	unsigned int ebx;
	unsigned int esp;
	unsigned int ebp;
	unsigned int esi;
	unsigned int edi;
	unsigned int es;
	unsigned int cs;
	unsigned int ss;
	unsigned int ds;
	unsigned int fs;
	unsigned int gs;
	unsigned int ldt;
	unsigned short trap;
	unsigned short iomap;
} __attribute__((packed));


extern "C"
{
void TSSLoad_loadTSS();
}


class TSSManager
{
public:
	static void writeTSS(GDTEntry& entry, unsigned int stackSegment);

	static void setKernelStack(unsigned int stackPointer);
private:
	static TSSEntry _tssEntry;
};


#endif //CRIOS_TSSMANAGER_H
