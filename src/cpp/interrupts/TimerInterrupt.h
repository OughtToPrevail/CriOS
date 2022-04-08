#ifndef OSTEST_TIMERINTERRUPT_H
#define OSTEST_TIMERINTERRUPT_H

#include "InterruptHandler.h"

#define TIMER_INTERRUPT_CODE 0x20

extern "C"
{
void timerInterrupt(CPUState, StackState);
};



#endif //OSTEST_TIMERINTERRUPT_H
