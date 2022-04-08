#ifndef OSTEST_CPPSUPPORT_H
#define OSTEST_CPPSUPPORT_H

// Taken from: https://wiki.osdev.org/C_PlusPlus

extern "C"
{
// Needed for pure virtual functions - https://wiki.osdev.org/C_PlusPlus#Pure_virtual_functions
void __cxa_pure_virtual();

void _init(void);
void _fini(void);
};

namespace __cxxabiv1
{
	/* guard variables */

	/* The ABI requires a 64-bit type.  */
	__extension__ typedef int __guard __attribute__((mode(__DI__)));

	extern "C"
	{
	int __cxa_guard_acquire(__guard*);
	void __cxa_guard_release(__guard*);
	void __cxa_guard_abort(__guard*);
	}
}

void* operator new(unsigned int size);
void* operator new[](unsigned int size);
void operator delete(void* p);
void operator delete(void* p, unsigned int size);
void operator delete[](void* p);
void operator delete[](void* p, unsigned int size);

#endif //OSTEST_CPPSUPPORT_H
