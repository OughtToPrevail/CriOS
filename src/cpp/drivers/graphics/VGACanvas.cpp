#include "VGACanvas.h"

VGACanvas::VGACanvas(const VideoGraphicsArray& vga) : _vga(vga), _backBuffer()
{

}

void VGACanvas::setPixel(unsigned int x, unsigned int y, unsigned char pixelColor)
{
	if(pixelColor == TRANSPARENT_INDEX)
	{
		return;
	}
	this->_backBuffer[y * VGA_WIDTH + x] = pixelColor;
}

void VGACanvas::writeToGraphics()
{
	this->_vga.writeBackBuffer(this->_backBuffer);
}
