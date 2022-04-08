#include "Event.h"

Event::Event() : Event(EventType::INVALID_EVENT, EventCondition::INVALID_CONDITION)
{

}

Event::Event(EventType eventType, EventCondition eventCondition) : _eventType(eventType), _eventCondition(eventCondition)
{

}

EventType Event::getType() const
{
	return this->_eventType;
}

EventCondition Event::getEventCondition() const
{
	return _eventCondition;
}
