#include "Memory.h"

// idea from https://stackoverflow.com/questions/12791864/c-program-to-check-little-vs-big-endian
int Memory::ONE_VALUE = 1;
bool Memory::MEMORY_BIG_ENDIAN = reinterpret_cast<char*>(&Memory::ONE_VALUE)[0] != Memory::ONE_VALUE;  // in big endian the higher memory ([3]) will be 1

unsigned int Memory::memcpy(unsigned char* dst, const unsigned char* src, unsigned int dstSize, unsigned int srcSize)
{
	unsigned int i;
	for(i = 0; i < srcSize && i < dstSize; i++)
	{
		dst[i] = src[i];
	}
	return i;
}

unsigned short Memory::swap(unsigned short value)
{
	return __builtin_bswap16(value);
}

short Memory::swap(short value)
{
	return static_cast<short>(Memory::swap(static_cast<unsigned short>(value)));
}

unsigned int Memory::swap(unsigned int value)
{
	return __builtin_bswap32(value);
}

int Memory::swap(int value)
{
	return static_cast<int>(Memory::swap(static_cast<unsigned int>(value)));
}

unsigned long long Memory::swap(unsigned long long value)
{
	return __builtin_bswap64(value);
}

long long Memory::swap(long long value)
{
	return static_cast<long long>(Memory::swap(static_cast<unsigned long long>(value)));
}

bool Memory::isBigEndian()
{
	return Memory::MEMORY_BIG_ENDIAN;
}

