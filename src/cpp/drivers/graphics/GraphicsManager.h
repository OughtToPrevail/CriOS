#ifndef OSTEST_GRAPHICSMANAGER_H
#define OSTEST_GRAPHICSMANAGER_H

#include "VideoGraphicsArray.h"
#include "VGACanvas.h"
#include "Desktop.h"
#include "MouseCursor.h"
#include "EventManager.h"
#include "FocusManager.h"

class GraphicsManager
{
public:
	GraphicsManager();

	void update();

	VGACanvas& getCanvas();
	MouseCursor& getCursor();
	EventManager& getEventManager();
	FocusManager& getFocusManager();

	void enable();

private:
	VideoGraphicsArray _vga;
	VGACanvas _canvas;
	Desktop _desktop;
	MouseCursor _mouseCursor;
	EventManager _eventManager;
	FocusManager _focusManager;
};


#endif //OSTEST_GRAPHICSMANAGER_H
