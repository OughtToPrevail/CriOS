#include "OutputStream.h"
#include "String.h"
#include "VAArgs.h"

#define MAX_BUFFER_LENGTH 512

void OutputStream::write(char c)
{
	this->write(static_cast<unsigned char>(c));
}

void OutputStream::writeShort(unsigned short s)
{
	this->write(static_cast<unsigned char>(s));
	this->write(static_cast<unsigned char>(s >> 8));
}

void OutputStream::writeIntAsChar(int i)
{
	this->write(static_cast<unsigned char>(i & 0xFF));
}

void OutputStream::writeBytes(const char* arr, int size)
{
	for(int i = 0; i < size; i++)
	{
		this->write(arr[i]);
	}
}

void OutputStream::writeString(const char* str)
{
	int length = String::strlen(str);
	this->writeBytes(str, length);
}

void OutputStream::writeLine()
{
	this->write('\n');
}

void OutputStream::writeLine(const char* str)
{
	this->writeString(str);
	this->writeLine();
}

void OutputStream::writeLineWithFormatting(const char* str, ...)
{
	VAArgs args(&str, sizeof(char*));
	char buffer[MAX_BUFFER_LENGTH];
	String::sprintf(buffer, MAX_BUFFER_LENGTH, str, args);

	this->writeString(buffer);
	this->writeLine();
}
