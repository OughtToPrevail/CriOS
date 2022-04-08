#include "Hash.h"

unsigned int Hash::hash(int x)
{
	return Hash::hash(static_cast<unsigned int>(x));
}

unsigned int Hash::hash(unsigned int x)
{
	return x;
}
