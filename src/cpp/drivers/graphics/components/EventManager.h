#ifndef OSTEST_EVENTMANAGER_H
#define OSTEST_EVENTMANAGER_H

#include "Vector.h"
#include "Event.h"
#include "Layout.h"
#include "MouseCursor.h"

class EventManager
{
public:
	explicit EventManager(const MouseCursor& mouseCursor);

	void queueEvent(const Event& event);
	void callAllEvents(Layout* mainLayout);
private:
	void callEvents(Layout* parent);
	void callComponentEvents(Component* component);

	Vector<Event> _events;
	Vector<Event> _pendingEvents;  // events pending to be added to events because they're being added while callEvents is happening
	bool _callingEvents;
	const MouseCursor& _mouseCursor;
};

#endif //OSTEST_EVENTMANAGER_H
