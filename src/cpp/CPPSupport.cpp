#include "CPPSupport.h"
#include "MemoryManagement.h"

void __cxa_pure_virtual()
{
}

typedef void (*ctor_dtor)(void);  // either constructor or destructor

extern ctor_dtor initArrayStart[];
extern ctor_dtor initArrayEnd[];
extern ctor_dtor finiArrayStart[];
extern ctor_dtor finiArrayEnd[];

void _init(void)
{
	for (ctor_dtor* p = initArrayStart; p != initArrayEnd; ++p)
	{
		(*p)();
	}
}

void _fini(void)
{
	for(ctor_dtor* p = finiArrayStart; p != finiArrayEnd; ++p)
	{
		(*p)();
	}
}

int __cxxabiv1::__cxa_guard_acquire(__cxxabiv1::__guard* g)
{
	return !*(char *)(g);
}

void __cxxabiv1::__cxa_guard_release(__cxxabiv1::__guard* g)
{
	*(char *)g = 1;
}

void __cxxabiv1::__cxa_guard_abort(__cxxabiv1::__guard*)
{

}

void* operator new(unsigned int size)
{
	return malloc(size);
}

void* operator new[](unsigned int size)
{
	return operator new(size);
}

void operator delete(void* p)
{
	free(p);
}

void operator delete(void* p, unsigned int size)
{
	(void) size;
	free(p);
}

void operator delete[](void* p)
{
	operator delete(p);
}

void operator delete[](void* p, unsigned int size)
{
	operator delete(p, size);
}
