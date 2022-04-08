#include "MouseCursor.h"
#include "Resources.h"

MouseCursor::MouseCursor()
{
	this->_x  = VGA_WIDTH / 2;
	this->_y = VGA_HEIGHT / 2;
	this->setSize(Resources::MouseCursor.getWidth(), Resources::MouseCursor.getHeight());
}

void MouseCursor::moveTo(unsigned int x, unsigned int y)
{
	this->_x = x;
	this->_y = y;
}

void MouseCursor::moveBy(int relX, int relY)
{
	if(relX < 0 && this->_x < Math::abs(relX))
	{
		this->_x = 0;
	} else if(this->_x + relX >= VGA_WIDTH - this->getWidth())
	{
		this->_x = VGA_WIDTH - this->getWidth();
	} else
	{
		this->_x += relX;
	}
	if(relY < 0 && this->_y < Math::abs(relY))
	{
		this->_y = 0;
	} else if(this->_y + relY >= VGA_HEIGHT - this->getHeight())
	{
		this->_y = VGA_HEIGHT - this->getHeight();
	} else
	{
		this->_y += relY;
	}
}

void MouseCursor::draw(Canvas& canvas) const
{
	Component::draw(canvas);
	canvas.drawImage(this->_x, this->_y, Resources::MouseCursor);
}
