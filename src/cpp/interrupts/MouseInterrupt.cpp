#include "MouseInterrupt.h"
#include "System.h"
#include "PICInterrupts.h"

void mouseInterrupt(CPUState, StackState)
{
	System::getSystem().getMouse().alertMouseInterrupt();
	PICInterrupts::getPICInterrupts().acknowledgePICInterrupt(PIC::PIC2);
}