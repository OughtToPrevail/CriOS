#ifndef OSTEST_FOCUSMANAGER_H
#define OSTEST_FOCUSMANAGER_H

#include "Component.h"
#include "MouseCursor.h"
#include "Layout.h"

class FocusManager
{
public:
	FocusManager(Layout* mainLayout, const MouseCursor& mouseCursor);

	void queueFocusUpdate();
	void updateFocus();
private:
	Component* findLowestComponent(Layout* layout, unsigned int x, unsigned int y);

	unsigned int _lastFocusUpdateX;
	unsigned int _lastFocusUpdateY;
	bool _pendingFocusUpdate;
	bool _updatingFocus;
	Component* _currentlyFocused;
	Layout* _mainLayout;
	const MouseCursor& _mouseCursor;
};


#endif //OSTEST_FOCUSMANAGER_H
