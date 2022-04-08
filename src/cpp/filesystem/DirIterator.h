#ifndef CRIOS_DIRITERATOR_H
#define CRIOS_DIRITERATOR_H

#include "VFSEntry.h"

class DirIterator
{
public:
	explicit DirIterator(VFSEntry* parent);

	const char* next();
	bool hasNext();
private:
	VFSEntry* _parent;
	unsigned int _index;
};

#endif //CRIOS_DIRITERATOR_H
