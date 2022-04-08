#ifndef CRIOS_NULLFILE_H
#define CRIOS_NULLFILE_H

#include "File.h"

class NullFile : public File
{
public:
	void write(char buffer[], unsigned int size) override;
	unsigned int read(char buffer[], unsigned int size) override;

	const char* getFileName() override;
	unsigned int getFileSize() override;
};


#endif //CRIOS_NULLFILE_H
