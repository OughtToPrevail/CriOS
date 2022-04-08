#include "GridLayout.h"
#include "Math.h"
#include "SubCanvas.h"

GridLayout::GridLayout() : _horizontalElements(0), _verticalElements(0), _componentBoxWidth(0), _componentBoxHeight(0)
{

}

void GridLayout::setGridBounds(unsigned int horizontalElements, unsigned int verticalElements)
{
	this->_horizontalElements = horizontalElements;
	this->_verticalElements = verticalElements;
}

void GridLayout::draw(Canvas& canvas) const
{
	Component::draw(canvas);
	for(Component* component : this->_children)
	{
		const GridLayoutParams& gridLayoutParams = static_cast<const GridLayoutParams&>(component->getLayoutParams());
		unsigned int x = this->_componentBoxWidth * gridLayoutParams.getGridX() + gridLayoutParams.getMargin();
		unsigned int y = this->_componentBoxHeight * gridLayoutParams.getGridY() + gridLayoutParams.getMargin();
		SubCanvas componentCanvas(canvas, x, y);
		component->updateLocation(this->getX() + x, this->getY() + y);
		component->drawComponent(componentCanvas);
	}
}

void GridLayout::recomputeDimensions()
{
	Layout::recomputeDimensions();
	this->computeBoxSize();
	this->_width = this->_componentBoxWidth * this->_horizontalElements;
	this->_height = this->_componentBoxHeight * this->_verticalElements;
}

void GridLayout::computeBoxSize()
{
	unsigned int maxComponentWidth = 0;
	unsigned int maxComponentHeight = 0;
	for(Component* component : this->_children)
	{
		maxComponentWidth = Math::max<unsigned int>(maxComponentWidth, component->getWidth());
		maxComponentHeight = Math::max<unsigned int>(maxComponentHeight, component->getHeight());
	}
	this->_componentBoxWidth = maxComponentWidth;
	this->_componentBoxHeight = maxComponentHeight;
}

GridLayoutParams::GridLayoutParams(unsigned int gridX, unsigned int gridY, unsigned int margin)
		: LayoutParams(margin), _gridX(gridX), _gridY(gridY)
{
}

unsigned int GridLayoutParams::getGridX() const
{
	return _gridX;
}

unsigned int GridLayoutParams::getGridY() const
{
	return _gridY;
}
