#ifndef CRIOS_PAGEFAULTINTERRUPT_H
#define CRIOS_PAGEFAULTINTERRUPT_H

#include "InterruptHandler.h"

#define PAGE_FAULT_INTERRUPT 0xE

extern "C"
{
void pageFaultInterrupt(CPUState, StackState);
}

#endif //CRIOS_PAGEFAULTINTERRUPT_H
