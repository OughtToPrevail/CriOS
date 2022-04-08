#include "InputStream.h"

char InputStream::readSigned()
{
	return static_cast<char>(this->read());
}

void InputStream::readBytes(char arr[], int size)
{
	for(int i = 0; i < size; i++)
	{
		arr[i] = this->readSigned();
	}
}

void InputStream::readString(char* str, int maxSize)
{
	char c;
	int len = 0;
	while((c = this->readSigned()) != '\0' && len < maxSize)
	{
		str[len++] = c;
	}
}
