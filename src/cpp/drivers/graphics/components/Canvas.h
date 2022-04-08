#ifndef OSTEST_CANVAS_H
#define OSTEST_CANVAS_H

#include "VGAColor.h"
#include "Resources.h"

class Canvas
{
public:
	virtual void setPixel(unsigned int x, unsigned int y, unsigned char pixelColor) = 0;
	virtual void setPixel(unsigned int x, unsigned int y, const VGAColor& color);

	virtual void drawRect(unsigned int x, unsigned int y, unsigned int width, unsigned int height, const VGAColor& color);
	virtual void drawImage(unsigned int x, unsigned int y, const OSImage& image);
	// any non-zero value in the pattern is drawn in the specified color
	virtual void drawPattern(unsigned int x, unsigned int y, unsigned int width, unsigned int height, const char* pattern, const VGAColor& color);

	virtual void drawText(unsigned int x, unsigned int y, const char* text, const VGAColor& foreground);
	virtual void drawText(unsigned int x, unsigned int y, const char* text, const VGAColor& foreground, const PCFFont& font);
};


#endif //OSTEST_CANVAS_H
