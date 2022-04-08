#ifndef OSTEST_SUBCANVAS_H
#define OSTEST_SUBCANVAS_H

#include "Canvas.h"
#include "VGACanvas.h"

class SubCanvas : public Canvas
{
public:
	SubCanvas(Canvas& canvas, unsigned int offsetX, unsigned int offsetY);

	void setPixel(unsigned int x, unsigned int y, unsigned char pixelColor) override;
private:
	Canvas& _canvas;
	unsigned int _offsetX;
	unsigned int _offsetY;
};


#endif //OSTEST_SUBCANVAS_H
