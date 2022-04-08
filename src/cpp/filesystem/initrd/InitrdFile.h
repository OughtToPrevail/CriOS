#ifndef CRIOS_INITRDFILE_H
#define CRIOS_INITRDFILE_H

#include "File.h"

struct InitrdFileStructure
{
	unsigned int size;
	char* name;
	char* content;
};


class InitrdFile : public File
{
public:
	InitrdFile(InitrdFileStructure* structure);

	void write(char buffer[], unsigned int size) override;
	unsigned int read(char buffer[], unsigned int size) override;

	const char* getFileName() override;
	unsigned int getFileSize() override;

private:
	InitrdFileStructure* _structure;
	unsigned int _position;
};


#endif //CRIOS_INITRDFILE_H
