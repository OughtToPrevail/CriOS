#include "DirIterator.h"

DirIterator::DirIterator(VFSEntry* parent) : _parent(parent), _index(0)
{

}

const char* DirIterator::next()
{
	VFSEntry* childEntry = this->_parent->children[this->_index++];
	return childEntry->name;
}

bool DirIterator::hasNext()
{
	return this->_index < this->_parent->children.size();
}
