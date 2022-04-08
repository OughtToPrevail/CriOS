#include "KeyboardInterrupt.h"
#include "PICInterrupts.h"
#include "System.h"

void keyboardInterrupt(CPUState, StackState)
{
	System::getSystem().getLogger().log(LogType::INFO, "Received keyboard input");
	System::getSystem().getKeyboard().alertKeyInterrupt();
	PICInterrupts::getPICInterrupts().acknowledgePICInterrupt(PIC::PIC1);
}
