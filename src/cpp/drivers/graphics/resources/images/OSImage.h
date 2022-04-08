#ifndef OSTEST_OSIMAGE_H
#define OSTEST_OSIMAGE_H

#include "VGAColor.h"
#include "ColorPalette.h"

class OSImage
{
public:
	explicit OSImage(unsigned char* address);

	unsigned char* getImagePixels() const;
	unsigned short getWidth() const;
	unsigned short getHeight() const;
private:
	unsigned char* _address;
	unsigned char* _imagePixels;
	unsigned short _width;
	unsigned short _height;
};

#endif //OSTEST_OSIMAGE_H
