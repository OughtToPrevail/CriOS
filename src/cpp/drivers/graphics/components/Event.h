#ifndef OSTEST_EVENT_H
#define OSTEST_EVENT_H

#include "Function.h"

enum EventType
{
	INVALID_EVENT,
	LEFT_CLICK,
	MIDDLE_CLICK,
	RIGHT_CLICK,
	DOUBLE_CLICK,
	MOUSE_MOVE,
	ENTER,
	LEAVE,
	KEYBOARD
};

enum EventCondition
{
	INVALID_CONDITION,
	FOCUSED,
	MOUSE_HOVER
};

class Event
{
public:
	Event();
	explicit Event(EventType eventType, EventCondition condition);

	EventType getType() const;
	EventCondition getEventCondition() const;
private:
	EventType _eventType;
	EventCondition _eventCondition;
};

typedef Function<void(const Event&)> EventHandler;

#endif //OSTEST_EVENT_H
