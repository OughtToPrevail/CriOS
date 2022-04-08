#include "InitrdFile.h"
#include "Memory.h"
#include "Math.h"

InitrdFile::InitrdFile(InitrdFileStructure* structure) : _structure(structure), _position(0)
{

}

void InitrdFile::write(char* buffer, unsigned int size)
{
	(void) buffer;
	(void) size;
}

unsigned int InitrdFile::read(char* buffer, unsigned int size)
{
	unsigned int read = Memory::memcpy((unsigned char*) buffer,
									   (const unsigned char*) this->_structure->content + this->_position,
									   size,
									   this->_structure->size - this->_position);
	this->_position += read;
	return read;
}

const char* InitrdFile::getFileName()
{
	return this->_structure->name;
}

unsigned int InitrdFile::getFileSize()
{
	return this->_structure->size;
}
