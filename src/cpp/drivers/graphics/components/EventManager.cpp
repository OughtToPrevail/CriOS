#include "EventManager.h"

EventManager::EventManager(const MouseCursor& mouseCursor) : _callingEvents(false), _mouseCursor(mouseCursor)
{

}

void EventManager::queueEvent(const Event& event)
{
	if(this->_callingEvents)
	{
		this->_pendingEvents.pushBack(event);
		return;
	}
	this->_events.pushBack(event);
}

void EventManager::callAllEvents(Layout* mainLayout)
{
	if(this->_pendingEvents.empty() && this->_events.empty())
	{
		return;
	}
	this->_callingEvents = true;
	this->_events.pushAll(this->_pendingEvents);
	this->_pendingEvents.clear();

	this->callEvents(mainLayout);

	this->_events.clear();
	this->_callingEvents = false;
}

void EventManager::callEvents(Layout* parent)
{
	unsigned int cursorX = this->_mouseCursor.getX();
	unsigned int cursorY = this->_mouseCursor.getY();
	this->callComponentEvents(parent);
	for(Component* component : parent->getChildren())
	{
		// checks if it's within bounding box of component
		if(component->contains(cursorX, cursorY))
		{
			if(!component->isHovered())
			{
				component->setHovered(true);
				component->callEvent(Event(EventType::ENTER, EventCondition::MOUSE_HOVER));
			}
		} else if(component->isHovered())
		{
			component->setHovered(false);
			component->callEvent(Event(EventType::LEAVE, EventCondition::MOUSE_HOVER));
		}
		if(component->isLayout())
		{
			this->callEvents(static_cast<Layout*>(component));
		} else
		{
			this->callComponentEvents(component);
		}
	}
}

void EventManager::callComponentEvents(Component* component)
{
	for(const Event& event : this->_events)
	{
		switch(event.getEventCondition())
		{
			case EventCondition::MOUSE_HOVER:
				if(!component->isHovered())
				{
					continue;
				}
				break;
			case EventCondition::FOCUSED:
				if(!component->isFocused())
				{
					continue;
				}
				break;
			case EventCondition::INVALID_CONDITION:
				continue;
		}
		component->callEvent(event);
	}
}
