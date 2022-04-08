#ifndef CRIOS_DOUBLEFAULTINTERRUPT_H
#define CRIOS_DOUBLEFAULTINTERRUPT_H

#include "InterruptHandler.h"

#define DOUBLE_FAULT_INTERRUPT 0x8

extern "C"
{
	void doubleFaultInterrupt(CPUState, StackState);
}

#endif //CRIOS_DOUBLEFAULTINTERRUPT_H
