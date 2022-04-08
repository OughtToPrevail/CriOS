#ifndef OSTEST_OUTPUTSTREAM_H
#define OSTEST_OUTPUTSTREAM_H


class OutputStream
{
public:
	virtual void write(unsigned char c) = 0;
	virtual void write(char c);
	virtual void writeShort(unsigned short s);
	virtual void writeIntAsChar(int i);
	virtual void writeBytes(const char* arr, int size);
	virtual void writeString(const char* str);
	virtual void writeLine();
	virtual void writeLine(const char* str);
	virtual void writeLineWithFormatting(const char* str, ...);
};

#endif //OSTEST_OUTPUTSTREAM_H
