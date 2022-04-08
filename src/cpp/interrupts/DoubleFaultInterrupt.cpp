#include "DoubleFaultInterrupt.h"
#include "System.h"

void doubleFaultInterrupt(CPUState, StackState)
{
	System::getSystem().getLogger().log(LogType::INFO, "CRITICAL - DOUBLE FAULT");
	System::halt();
}