#include "VGAColor.h"
#include "Math.h"

VGAColor::VGAColor() : VGAColor(0, 0, 0)
{

}

VGAColor::VGAColor(unsigned char red, unsigned char green, unsigned char blue) : _index(OUT_OF_TABLE), _red(red), _green(green), _blue(blue)
{

}

VGAColor::VGAColor(unsigned char index, unsigned char red, unsigned char green, unsigned char blue) : _index(index), _red(red), _green(green), _blue(blue)
{

}

int VGAColor::getIndex() const
{
	return _index;
}

unsigned char VGAColor::getRed() const
{
	return _red;
}

unsigned char VGAColor::getGreen() const
{
	return _green;
}

unsigned char VGAColor::getBlue() const
{
	return _blue;
}

int VGAColor::distance(const VGAColor& other) const
{
	// based on this algorithm https://en.wikipedia.org/wiki/Color_difference#sRGB
	return Math::squared(this->_red - other._red) + Math::squared(this->_green - other._green) + Math::squared(this->_blue - other._blue);
}

bool VGAColor::operator==(const VGAColor& rhs) const
{
	return _red == rhs._red &&
		   _green == rhs._green &&
		   _blue == rhs._blue;
}

bool VGAColor::operator!=(const VGAColor& rhs) const
{
	return !(rhs == *this);
}

VGAColor VGAColor::from8Bit(unsigned char red, unsigned char green, unsigned int blue)
{
	return VGAColor(red >> 2, green >> 2, blue >> 2);
}

