#ifndef CRIOS_FILE_H
#define CRIOS_FILE_H


class File
{
public:
	virtual void write(char buffer[], unsigned int size) = 0;
	virtual unsigned int read(char buffer[], unsigned int size) = 0;

	virtual const char* getFileName() = 0;
	virtual unsigned int getFileSize() = 0;
};


#endif //CRIOS_FILE_H
