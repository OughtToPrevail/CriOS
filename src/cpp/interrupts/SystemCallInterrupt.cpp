#include "SystemCallInterrupt.h"
#include "Syscall.h"
#include "System.h"

void systemCallInterrupt(CPUState state, StackState)
{
	switch(state.eax)
	{
		case SYSCALL_LOG:
			System::getSystem().getLogger().logStringKernel((const char*) state.ebx);
			break;
		case SYSCALL_GET_CURSOR:
			state.eax = System::getSystem().getTextCursor().getCursorPosition();
			break;
		case SYSCALL_SET_CURSOR:
			System::getSystem().getTextCursor().setCursorPosition(state.ebx);
			break;
		default:
			System::getSystem().getLogger().logStringKernel("SYSTEM CALL UNKNOWN\n");
			break;
	}
}
