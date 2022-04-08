#ifndef OSTEST_MEMORY_H
#define OSTEST_MEMORY_H

class Memory
{
public:
	static unsigned int memcpy(unsigned char* dst, const unsigned char* src, unsigned int dstSize, unsigned int srcSize);

	static unsigned short swap(unsigned short value);
	static short swap(short value);
	static unsigned int swap(unsigned int value);
	static int swap(int value);
	static unsigned long long swap(unsigned long long value);
	static long long swap(long long value);

	template<class T>
	static T ensureBigEndian(T value);
	template<class T>
	static T ensureLittleEndian(T value);
	template<class T>
	static T ensureEndian(T value, bool bigEndian);

	static bool isBigEndian();
private:
	static int ONE_VALUE;  // simply used for checking if big endian
	static bool MEMORY_BIG_ENDIAN;
};

template<class T>
T Memory::ensureBigEndian(T value)
{
	if(Memory::isBigEndian())
	{
		return value;
	}
	return swap(value);
}

template<class T>
T Memory::ensureLittleEndian(T value)
{
	if(Memory::isBigEndian())
	{
		return swap(value);
	}
	return value;
}

template<class T>
T Memory::ensureEndian(T value, bool bigEndian)
{
	if(bigEndian)
	{
		return Memory::ensureBigEndian<T>(value);
	}
	return Memory::ensureLittleEndian<T>(value);
}

#endif //OSTEST_MEMORY_H
