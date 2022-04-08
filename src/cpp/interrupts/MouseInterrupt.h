#ifndef OSTEST_MOUSEINTERRUPT_H
#define OSTEST_MOUSEINTERRUPT_H

#include "InterruptHandler.h"

#define MOUSE_INTERRUPT_CODE 0x2C

extern "C"
{
void mouseInterrupt(CPUState, StackState);
};

#endif //OSTEST_MOUSEINTERRUPT_H
