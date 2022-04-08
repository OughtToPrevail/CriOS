#ifndef OSTEST_INTERRUPTHANDLER_H
#define OSTEST_INTERRUPTHANDLER_H

struct CPUState
{
	unsigned int ds;
	unsigned int edi;
	unsigned int esi;
	unsigned int ebp;
	unsigned int esp;
	unsigned int ebx;
	unsigned int edx;
	unsigned int ecx;
	unsigned int eax;
};

struct StackState
{
	unsigned int errorCode;
	unsigned int eip;
	unsigned int cs;
	unsigned int eflags;
	unsigned int useresp;
	unsigned int ss;
};

typedef void(*InterruptHandler)();

#endif //OSTEST_INTERRUPTHANDLER_H
