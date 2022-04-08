#ifndef OSTEST_GDTLOADER_H
#define OSTEST_GDTLOADER_H

#include "GDT.h"

extern "C"
{
void GDTLoad_loadGDT(GDT gdt);
};

#define TOTAL_SEGMENTS (6)

class GDTLoader
{
public:
	static unsigned short loadGDT();
private:
	static void loadEmptyGDTEntry(int index, unsigned char ring, bool isCode);

	static GDT gdt;
	static GDTEntry gdtTable[TOTAL_SEGMENTS];
};


#endif //OSTEST_GDTLOADER_H
