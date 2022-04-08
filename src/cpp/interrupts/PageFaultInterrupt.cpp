#include "PageFaultInterrupt.h"
#include "System.h"

void pageFaultInterrupt(CPUState, StackState)
{
	System::getSystem().getLogger().log(LogType::ERROR, "CRITICAL - PAGE FAULT");
	System::getSystem().halt();
}