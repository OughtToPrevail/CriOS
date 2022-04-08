#ifndef OSTEST_KEYBOARDINTERRUPT_H
#define OSTEST_KEYBOARDINTERRUPT_H

#include "InterruptHandler.h"

#define KEYBOARD_INTERRUPT_CODE 0x21

extern "C"
{
void keyboardInterrupt(CPUState, StackState);
}

#endif //OSTEST_KEYBOARDINTERRUPT_H
