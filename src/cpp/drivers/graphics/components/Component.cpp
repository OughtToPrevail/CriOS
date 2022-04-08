#include "Component.h"

Component::Component()
		: _background(ColorPalette::transparent()), _visible(true), _x(0), _y(0), _width(0), _height(0),
		  _explicitSize(false), _layoutParams(), _focused(false), _hovered(false), _invalidated(true)
{

}

void Component::drawComponent(Canvas& canvas) const
{
	if(!this->_visible)
	{
		return;
	}
	if(this->_background != ColorPalette::transparent())
	{
		canvas.drawRect(0, 0, this->_width, this->_height, this->_background);
	}
	this->draw(canvas);
}

void Component::draw(Canvas& canvas) const
{
	(void) canvas;
}

void Component::setBackground(const VGAColor& color)
{
	this->_background = color;
}

void Component::setVisibility(bool visible)
{
	this->_visible = visible;
}

void Component::setSize(unsigned int width, unsigned int height)
{
	this->_width = width;
	this->_height = height;
	this->_explicitSize = true;
}

void Component::clearSizePreferences()
{
	this->_explicitSize = false;
	this->_invalidated = true;
}

unsigned int Component::getX() const
{
	return this->_x;
}

unsigned int Component::getY() const
{
	return this->_y;
}

unsigned int Component::getWidth() const
{
	return this->_width;
}

unsigned int Component::getHeight() const
{
	return this->_height;
}

void Component::recomputeDimensions()
{
	this->_invalidated = false;
}

void Component::updateLocation(unsigned int x, unsigned int y)
{
	this->_x = x;
	this->_y = y;
}

void Component::setFocused(bool focused)
{
	this->_focused = focused;
}

bool Component::isFocused() const
{
	return this->_focused;
}

void Component::setHovered(bool hovered)
{
	this->_hovered = hovered;
}

bool Component::isHovered() const
{
	return this->_hovered;
}

bool Component::contains(unsigned int x, unsigned int y)
{
	return this->getX() <= x && (this->getX() + this->getWidth()) >= x &&
           this->getY() <= y && (this->getY() + this->getHeight()) >= y;
}

void Component::setLayoutParams(const LayoutParams& layoutParams)
{
	this->_layoutParams = layoutParams;
}

const LayoutParams& Component::getLayoutParams() const
{
	return this->_layoutParams;
}

bool Component::isInvalidated() const
{
	return this->_invalidated;
}

bool Component::hasExplicitSize() const
{
	return this->_explicitSize;
}

bool Component::isLayout() const
{
	return false;
}

bool Component::isAutonomousComponent() const
{
	return true;
}

void Component::addEventHandler(EventType eventType, EventHandler eventHandler)
{
	this->_eventHandlers.put(eventType, eventHandler);
}

void Component::callEvent(const Event& event)
{
	EventHandler* eventHandler = this->_eventHandlers.get(event.getType());
	if(eventHandler != nullptr)
	{
		(*eventHandler)(event);
	}
}
