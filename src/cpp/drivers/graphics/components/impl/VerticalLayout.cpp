#include "VerticalLayout.h"
#include "SubCanvas.h"
#include "Math.h"

VerticalLayout::VerticalLayout() : _positioning(Positioning::LEFT)
{

}

void VerticalLayout::draw(Canvas& canvas) const
{
	Component::draw(canvas);
	unsigned int y = 0;
	for(Component* component : this->_children)
	{
		unsigned int x;
		switch(this->_positioning)
		{
			case Positioning::CENTER:
				x = this->_width / 2 - component->getWidth() / 2;
				break;
			case Positioning::RIGHT:
				x = this->_width - component->getWidth() - component->getLayoutParams().getMargin();
				break;
			case Positioning::LEFT:
			case Positioning::TOP:
			case Positioning::BOTTOM:
				x = component->getLayoutParams().getMargin();
				break;
		}
		SubCanvas componentCanvas(canvas, x, y);
		component->updateLocation(this->getX() + x, this->getY() + y);
		component->drawComponent(componentCanvas);
		y += component->getHeight();
	}
}

void VerticalLayout::recomputeDimensions()
{
	unsigned int maxWidth = 0;
	unsigned int height = 0;
	for(Component* component : this->_children)
	{
		maxWidth = Math::max<unsigned int>(maxWidth, component->getWidth());
		height += component->getHeight();
	}
	this->_width = maxWidth;
	this->_height = height;
}

void VerticalLayout::setPositioning(Positioning positioning)
{
	this->_positioning = positioning;
}
