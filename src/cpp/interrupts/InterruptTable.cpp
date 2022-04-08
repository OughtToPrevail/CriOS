#include "InterruptTable.h"
#include "System.h"
#include "GDT.h"
#include "PICInterrupts.h"
#include "TimerInterrupt.h"
#include "KeyboardInterrupt.h"
#include "MouseInterrupt.h"
#include "PageFaultInterrupt.h"
#include "GeneralProtectionFaultInterrupt.h"
#include "DoubleFaultInterrupt.h"
#include "SystemCallInterrupt.h"

IDTR InterruptTable::idtr = IDTR();
IDTEntry InterruptTable::idt[IDT_SIZE] = {};

extern "C"
{
	void divisionByZero(CPUState, StackState)
	{
		System::getSystem().getLogger().log(LogType::ERROR, "Division by 0");
		System::halt();
	}
}

extern "C"
{
void interruptHandler0x0();
void interruptHandler0x20();
void interruptHandler0x21();
void interruptHandler0x2C();
void interruptHandler0xE();
void interruptHandler0xD();
void interruptHandler0x8();
void interruptHandler0x80();
void interruptHandlerPIC1();
void interruptHandlerPIC2();
}

void InterruptTable::registerInterrupts(unsigned short cs)
{
	InterruptTable::idtr.base = (unsigned int) &InterruptTable::idt[0];
	InterruptTable::idtr.limit = (unsigned short) sizeof(IDTEntry) * IDT_SIZE - 1;

	loadInterruptEntry(0, &interruptHandler0x0, cs);
	PICInterrupts::getPICInterrupts(); // will initialize the PIC interrupts
	for(int i = PIC1_OFFSET; i < PIC1_OFFSET + PIC_SIZE; i++)
	{
		loadInterruptEntry(i, &interruptHandlerPIC1, cs);
	}
	for(int i = PIC2_OFFSET; i < PIC2_OFFSET + PIC_SIZE; i++)
	{
		loadInterruptEntry(i, &interruptHandlerPIC2, cs);
	}

	loadInterruptEntry(TIMER_INTERRUPT_CODE, &interruptHandler0x20, cs);
	loadInterruptEntry(KEYBOARD_INTERRUPT_CODE, &interruptHandler0x21, cs);
	loadInterruptEntry(MOUSE_INTERRUPT_CODE, &interruptHandler0x2C, cs);
	loadInterruptEntry(PAGE_FAULT_INTERRUPT, &interruptHandler0xE, cs);
	loadInterruptEntry(GENERAL_PROTECTION_FAULT_INTERRUPT, &interruptHandler0xD, cs);
	loadInterruptEntry(DOUBLE_FAULT_INTERRUPT, &interruptHandler0x8, cs);
	loadInterruptEntry(SYSTEM_CALL_FAULT_INTERRUPT, &interruptHandler0x80, cs);
	InterruptTable::idt[SYSTEM_CALL_FAULT_INTERRUPT].dpl = USER_RING;

	loadInterruptTable(InterruptTable::idtr);

/*
	// Test for interrupts (division by zero)
	int x = 1;
	int y = 0;
	int z = x / y;
	(void) z;
 */
}

void InterruptTable::loadInterruptEntry(int index, InterruptHandler handler, unsigned short cs)
{
	InterruptTable::idt[index].init(handler, cs);
}
