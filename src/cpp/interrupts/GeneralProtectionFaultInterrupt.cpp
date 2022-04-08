#include "GeneralProtectionFaultInterrupt.h"
#include "System.h"

void generalProtectionFaultInterrupt(CPUState c, StackState s)
{
	(void) c;
	(void) s;
	System::getSystem().getLogger().log(LogType::INFO, "CRITICAL - PROTECTION FAULT");
	System::halt();
}
