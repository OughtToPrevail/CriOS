#ifndef CRIOS_SYSCALL_H
#define CRIOS_SYSCALL_H

#include "VAArgs.h"

#define SYSCALL_LOG (0)
#define SYSCALL_GET_CURSOR (1)
#define SYSCALL_SET_CURSOR (2)

extern "C"
{
unsigned int sysCall(unsigned int sysCallNumber, unsigned int param1, unsigned int param2, unsigned int param3);
}

class Syscall
{
public:
	template<class P1 = unsigned int, class P2 = unsigned int, class P3 = unsigned int>
	static unsigned int syscall(unsigned int sysCallNumber, P1 param1 = 0, P2 param2 = 0, P3 param3 = 0);
};

template<class P1, class P2, class P3>
unsigned int Syscall::syscall(unsigned int sysCallNumber, P1 param1, P2 param2, P3 param3)
{
	return sysCall(sysCallNumber, (unsigned int) param1, (unsigned int) param2, (unsigned int) param3);
}


#endif //CRIOS_SYSCALL_H
