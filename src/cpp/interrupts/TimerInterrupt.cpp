#include "TimerInterrupt.h"
#include "PICInterrupts.h"
#include "System.h"


void timerInterrupt(CPUState, StackState)
{
	System::getSystem().getPIT().alertTick();
	PICInterrupts::getPICInterrupts().acknowledgePICInterrupt(PIC::PIC1);
	Scheduler& myScheduler = System::getSystem().getScheduler();
	myScheduler.changeProcess();
}

