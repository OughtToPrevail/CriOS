#include "Math.h"

int Math::squared(int x)
{
	return x * x;
}

unsigned int Math::abs(int x)
{
	return x >= 0 ? x : -x;
}

int Math::ceil(double x)
{
	int asInt = static_cast<int>(x);
	if(asInt == x)  // if it doesn't need rounding (already the same as int as it is double)
	{
		return asInt;
	}
	return asInt + 1;  // if it does, round up, so just add 1
}
