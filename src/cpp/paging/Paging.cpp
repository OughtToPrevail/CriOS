#include "Paging.h"


Paging::Paging() : _tables(), _directory()
{
}

void Paging::enablePaging()
{
	this->setupPaging();
	paging_setPagingDirectory((unsigned int) this->_directory);
	paging_enablePaging();
}
