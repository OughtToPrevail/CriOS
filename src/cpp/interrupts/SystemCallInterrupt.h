#ifndef CRIOS_SYSTEMCALLINTERRUPT_H
#define CRIOS_SYSTEMCALLINTERRUPT_H

#include "InterruptHandler.h"

#define SYSTEM_CALL_FAULT_INTERRUPT 0x80

extern "C"
{
void systemCallInterrupt(CPUState, StackState);
};


#endif //CRIOS_SYSTEMCALLINTERRUPT_H
