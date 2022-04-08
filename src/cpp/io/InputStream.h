#ifndef OSTEST_INPUTSTREAM_H
#define OSTEST_INPUTSTREAM_H


class InputStream
{
public:
	virtual unsigned char read() = 0;
	virtual char readSigned();
	virtual void readBytes(char arr[], int size);
	virtual void readString(char* str, int maxSize);
};


#endif //OSTEST_INPUTSTREAM_H
