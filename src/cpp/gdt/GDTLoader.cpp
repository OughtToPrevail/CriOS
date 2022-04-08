#include "GDTLoader.h"
#include "TSSManager.h"

// The offset is 16 because it's 8 bytes for each segment and there is a null segment and code segment before
#define CODE_SEGMENT_OFFSET (0x8)
#define DATA_SEGMENT_OFFSET (0x10)

GDT GDTLoader::gdt = GDT();
GDTEntry GDTLoader::gdtTable[TOTAL_SEGMENTS] = {};

unsigned short GDTLoader::loadGDT()
{
	GDTLoader::loadEmptyGDTEntry(1, KERNEL_RING, true);
	GDTLoader::loadEmptyGDTEntry(2, KERNEL_RING, false);

	GDTLoader::loadEmptyGDTEntry(3, USER_RING, true);
	GDTLoader::loadEmptyGDTEntry(4, USER_RING, false);

	GDTEntry& entry = GDTLoader::gdtTable[5];
	TSSManager::writeTSS(entry, DATA_SEGMENT_OFFSET);

	GDTLoader::gdt.address = (unsigned int) &GDTLoader::gdtTable[0];
	GDTLoader::gdt.size = sizeof(GDTEntry) * TOTAL_SEGMENTS - 1;
	GDTLoad_loadGDT(GDTLoader::gdt);
	TSSLoad_loadTSS();

	return CODE_SEGMENT_OFFSET;
}

void GDTLoader::loadEmptyGDTEntry(int index, unsigned char ring, bool isCode)
{
	GDTEntry& entry = GDTLoader::gdtTable[index];
	entry.limit = 0xFFFF;
	entry.base = 0;
	entry.present = 1;
	entry.dpl = ring;
	entry.code = isCode;
	entry.conformingOrExpandDown = 0;
	entry.codeDataSegment = 1;
	entry.readOrWrite = 1;
	entry.accessed = 0;
	entry.available = 0;
	entry.long_mode = 0;
	entry.big = 1;
	entry.gran = 1;
	entry.limit1 = 0xF;
	entry.base1 = 0;
}
