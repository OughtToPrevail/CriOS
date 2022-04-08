#include "Canvas.h"
#include "String.h"

void Canvas::setPixel(unsigned int x, unsigned int y, const VGAColor& color)
{
	this->setPixel(x, y, color.getIndex());
}

void Canvas::drawRect(unsigned int x, unsigned int y, unsigned int width, unsigned int height, const VGAColor& color)
{
	unsigned int endWidth = x + width;
	unsigned int endHeight = y + height;
	for(; y < endHeight; y++)
	{
		for(unsigned int currX = x; currX < endWidth; currX++)
		{
			this->setPixel(currX, y, color);
		}
	}
}

void Canvas::drawImage(unsigned int x, unsigned int y, const OSImage& image)
{
	unsigned int endWidth = x + image.getWidth();
	unsigned int endHeight = y + image.getHeight();
	unsigned char* imagePixels = image.getImagePixels();
	unsigned int pixelIndex = 0;
	for(; y < endHeight; y++)
	{
		for(unsigned int currX = x; currX < endWidth; currX++)
		{
			unsigned char pixelColor = imagePixels[pixelIndex++];
			this->setPixel(currX, y, pixelColor);
		}
	}
}

void Canvas::drawPattern(unsigned int x, unsigned int y, unsigned int width, unsigned int height, const char* pattern,
						 const VGAColor& color)
{
	unsigned int endWidth = x + width;
	unsigned int endHeight = y + height;
	for(unsigned int currY = y; currY < endHeight; currY++)
	{
		for(unsigned int currX = x; currX < endWidth; currX++)
		{
			if(pattern[(currY - y) * width + (currX - x)])
			{
				this->setPixel(currX, currY, color);
			}
		}
	}
}

void Canvas::drawText(unsigned int x, unsigned int y, const char* text, const VGAColor& foreground)
{
	this->drawText(x, y, text, foreground, Resources::DEFAULT_FONT);
}

void Canvas::drawText(unsigned int x, unsigned int y, const char* text, const VGAColor& foreground, const PCFFont& font)
{
	int stringLength = String::strlen(text);
	unsigned int baselineY = y;
	for(int i = 0; i < stringLength; i++)
	{
		PCFCharacter character = font.getCharacter(text[i]);
		unsigned int charY;
		for(charY = 0, y = baselineY < character.descent ? 0 : baselineY - character.descent; y < baselineY + character.ascent; y++, charY++)
		{
			for(unsigned char charX = 0; charX < character.width; charX++)
			{
				if(character.isPixelColored(charX, charY))
				{
					this->setPixel(x + charX, y, foreground);
				}
			}
		}
		x += character.width;
	}
}
