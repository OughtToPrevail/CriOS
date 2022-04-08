#ifndef OSTEST_COLORPALETTE_H
#define OSTEST_COLORPALETTE_H

#include "VGAColor.h"

#define COLOR_COUNT 256
#define TRANSPARENT_INDEX (COLOR_COUNT - 1)

class ColorPalette
{
public:
	static const VGAColor* getColorPalette();
	static const VGAColor& fitPalette(const VGAColor& color);
	static const VGAColor& transparent();
private:
	static const VGAColor _colorPalette[COLOR_COUNT];
};


#endif //OSTEST_COLORPALETTE_H
