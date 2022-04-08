#include "FocusManager.h"

FocusManager::FocusManager(Layout* mainLayout, const MouseCursor& mouseCursor) : _lastFocusUpdateX(0),
															 _lastFocusUpdateY(0),
															 _pendingFocusUpdate(false),
															 _updatingFocus(false),
															 _currentlyFocused(mainLayout),
															 _mainLayout(mainLayout),
															 _mouseCursor(mouseCursor)
{

}

void FocusManager::queueFocusUpdate()
{
	if(this->_updatingFocus)  // make sure to not change values while updating focus
	{
		return;
	}
	this->_lastFocusUpdateX = this->_mouseCursor.getX();
	this->_lastFocusUpdateY = this->_mouseCursor.getY();
	this->_pendingFocusUpdate = true;
}

void FocusManager::updateFocus()
{
	if(this->_pendingFocusUpdate)
	{
		this->_updatingFocus = true;

		Component* component = this->findLowestComponent(this->_mainLayout, this->_lastFocusUpdateX, this->_lastFocusUpdateY);
		if(component != this->_currentlyFocused)
		{
			this->_currentlyFocused->setFocused(false);
			component->setFocused(true);
			this->_currentlyFocused = component;
		}

		this->_pendingFocusUpdate = false;
		this->_updatingFocus = false;
	}
}

Component* FocusManager::findLowestComponent(Layout* layout, unsigned int x, unsigned int y)
{
	for(Component* component : layout->getChildren())
	{
		if(component->contains(x, y))
		{
			if(component->isLayout() && !component->isAutonomousComponent())
			{
				return findLowestComponent(static_cast<Layout*>(component), x, y);
			}
			return component;
		}
	}
	return layout;
}
