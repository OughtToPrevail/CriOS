#include "Label.h"

Label::Label() : _text(""), _foreground(ColorPalette::getColorPalette()[0])
{
}

void Label::draw(Canvas& canvas) const
{
	Component::draw(canvas);
	canvas.drawText(0, 0, this->_text, this->_foreground);
}

void Label::recomputeDimensions()
{
	TextDimensions dimensions = Resources::DEFAULT_FONT.measureText(this->_text);
	this->_width = dimensions.width;
	this->_height = dimensions.height;
	this->_invalidated = false;
}

void Label::setText(const char* text)
{
	this->_text = text;
	this->_invalidated = true;
}

void Label::setForeground(const VGAColor& foreground)
{
	this->_foreground = foreground;
	this->_invalidated = true;
}
