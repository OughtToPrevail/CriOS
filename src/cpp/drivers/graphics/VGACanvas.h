#ifndef OSTEST_VGACANVAS_H
#define OSTEST_VGACANVAS_H

#include "VideoGraphicsArray.h"
#include "Canvas.h"

class VGACanvas : public Canvas
{
public:
	explicit VGACanvas(const VideoGraphicsArray& vga);

	void setPixel(unsigned int x, unsigned int y, unsigned char pixelColor) override;

	void writeToGraphics();
private:
	const VideoGraphicsArray& _vga;
	unsigned char _backBuffer[VGA_BUFFER_SIZE];
};


#endif //OSTEST_VGACANVAS_H
