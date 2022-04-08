#include "OSImage.h"

OSImage::OSImage(unsigned char* address) : _address(reinterpret_cast<unsigned char*>(address)), _imagePixels(address), _width(0), _height(0)
{
	unsigned short* header = reinterpret_cast<unsigned short*>(this->_address);
	this->_width = header[0];
	this->_height = header[1];

	this->_imagePixels = reinterpret_cast<unsigned char*>(this->_address + sizeof(unsigned short) * 2);
}

unsigned char* OSImage::getImagePixels() const
{
	return this->_imagePixels;
}

unsigned short OSImage::getWidth() const
{
	return _width;
}

unsigned short OSImage::getHeight() const
{
	return _height;
}
