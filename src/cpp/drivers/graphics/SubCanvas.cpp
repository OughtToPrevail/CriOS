#include "SubCanvas.h"

SubCanvas::SubCanvas(Canvas& canvas, unsigned int offsetX, unsigned int offsetY) : _canvas(canvas), _offsetX(offsetX), _offsetY(offsetY)
{

}

void SubCanvas::setPixel(unsigned int x, unsigned int y, unsigned char pixelColor)
{
	this->_canvas.setPixel(this->_offsetX + x, this->_offsetY + y, pixelColor);
}
