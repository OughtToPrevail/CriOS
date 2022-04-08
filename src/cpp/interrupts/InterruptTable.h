#ifndef OSTEST_INTERRUPTTABLE_H
#define OSTEST_INTERRUPTTABLE_H

#include "InterruptHandler.h"

// Interrupt table is also called IDT (Interrupt Descriptor Table)

#define IDT_SIZE 256
#define INTERRUPT_HANDLER_TYPE (0xE)

struct IDTEntry // Interrupt Handler Entry, https://wiki.osdev.org/Interrupt_Descriptor_Table
{
	IDTEntry() : offset1(0), segmentSelector(0), unused(0), type(0), dpl(0), p(0), offset2(0)
	{

	}

	IDTEntry(InterruptHandler handler, unsigned short codeSegment) : IDTEntry()
	{
		this->init(handler, codeSegment);
	}

	void init(InterruptHandler handler, unsigned short codeSegment)
	{
		this->offset1 = (unsigned int) handler & 0xFFFF;
		this->offset2 = (unsigned int) handler >> 16;
		this->segmentSelector = codeSegment;
		this->type = INTERRUPT_HANDLER_TYPE;
		this->p = 1;
	}

	unsigned short offset1;
	unsigned short segmentSelector;
	unsigned char unused:8;
	unsigned char type:5;
	unsigned char dpl:2;
	unsigned char p:1;
	unsigned short offset2;
} __attribute__((packed));

struct IDTR
{
	unsigned short limit;
	unsigned int base;
} __attribute__((packed));

extern "C"
{
	void loadInterruptTable(IDTR idtr);
}

class InterruptTable
{
public:
	static void registerInterrupts(unsigned short cs);
private:
	static void loadInterruptEntry(int index, InterruptHandler handler, unsigned short cs);

	static IDTR idtr;
	__attribute__((aligned(0x10)))
	static IDTEntry idt[IDT_SIZE]; // aligned for performance (according to https://wiki.osdev.org/Interrupts_tutorial)
};

#endif //OSTEST_INTERRUPTTABLE_H
