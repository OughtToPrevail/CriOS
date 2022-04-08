#include "GraphicsManager.h"
#include "System.h"

GraphicsManager::GraphicsManager() : _vga(), _canvas(this->_vga), _desktop(), _mouseCursor(), _eventManager(this->_mouseCursor), _focusManager(&this->_desktop, this->_mouseCursor)
{
}

void GraphicsManager::enable()
{
	this->_vga.activate();
}

void GraphicsManager::update()
{
	this->_focusManager.updateFocus();
	this->_eventManager.callAllEvents(&this->_desktop);
	this->_desktop.updateChildren();
	this->_desktop.drawComponent(this->_canvas);
	this->_mouseCursor.draw(this->_canvas);  // always draw cursor last
	this->_canvas.writeToGraphics();
}

VGACanvas& GraphicsManager::getCanvas()
{
	return this->_canvas;
}

MouseCursor& GraphicsManager::getCursor()
{
	return this->_mouseCursor;
}

EventManager& GraphicsManager::getEventManager()
{
	return this->_eventManager;
}

FocusManager& GraphicsManager::getFocusManager()
{
	return this->_focusManager;
}
