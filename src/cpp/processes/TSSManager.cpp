#include "TSSManager.h"


TSSEntry TSSManager::_tssEntry = TSSEntry();

void TSSManager::writeTSS(GDTEntry& entry, unsigned int stackSegment)
{
	unsigned int base = (unsigned int) &TSSManager::_tssEntry;
	unsigned int limit = sizeof(TSSEntry);

	entry.limit = limit;
	entry.base = base;
	entry.accessed = 1; // indicates TSS
	entry.readOrWrite = 0;
	entry.conformingOrExpandDown = 0; // always 0 in TSS
	entry.code = 1;
	entry.codeDataSegment = 0; // indicates TSS
	entry.dpl = USER_RING;
	entry.present = 1;
	entry.limit1 = (limit & (0xF << 16)) >> 16; // isolate top nibble (only the last 4 bits of limit)
	entry.available = 0;
	entry.long_mode = 0;
	entry.big = 0;
	entry.gran = 0;
	entry.base1 = (base & (0xFF << 24)) >> 24;  // like with limit1 except whole last byte

	TSSManager::_tssEntry.ss0 = stackSegment;
	TSSManager::_tssEntry.iomap = sizeof(TSSEntry);
}

void TSSManager::setKernelStack(unsigned int stackPointer)
{
	TSSManager::_tssEntry.esp0 = stackPointer;
}
