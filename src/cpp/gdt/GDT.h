#ifndef CRIOS_GDT_H
#define CRIOS_GDT_H

struct GDT
{
	unsigned short size;
	unsigned int address;
} __attribute__((packed));

struct GDTEntry
{
	unsigned short limit; // 0:15
	unsigned int base:24;  // 0:23
	unsigned char accessed:1;
	unsigned char readOrWrite:1;  // read - code, write - data
	unsigned char conformingOrExpandDown:1;  // conforming - code, expand down - data
	unsigned char code:1;
	unsigned char codeDataSegment:1;
	unsigned char dpl:2;
	unsigned char present:1;
	unsigned char limit1:4;  // 16:19
	unsigned char available:1;
	unsigned char long_mode:1;
	unsigned char big:1;
	unsigned char gran:1;
	unsigned char base1; // 24:31
} __attribute__((packed));

#define KERNEL_RING (0)
#define USER_RING (3)

#endif //CRIOS_GDT_H
