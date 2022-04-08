#ifndef OSTEST_COMPONENT_H
#define OSTEST_COMPONENT_H

#include "VGACanvas.h"
#include "Theme.h"
#include "LayoutParams.h"
#include "Map.h"
#include "Event.h"

class Component
{
public:
	Component();

	virtual void drawComponent(Canvas& canvas) const;
	virtual void draw(Canvas& canvas) const;  // should be overriden by subclasses but not required

	virtual void setBackground(const VGAColor& color);
	virtual void setVisibility(bool visible);

	virtual void setSize(unsigned int width, unsigned int height);
	virtual void clearSizePreferences();
	virtual unsigned int getX() const;
	virtual unsigned int getY() const;
	virtual unsigned int getWidth() const;
	virtual unsigned int getHeight() const;
	virtual void recomputeDimensions();  // available for override
	virtual void updateLocation(unsigned int x, unsigned int y); // called by layout
	virtual void setFocused(bool focused);
	virtual bool isFocused() const;
	virtual void setHovered(bool hovered);
	virtual bool isHovered() const;
	virtual bool contains(unsigned int x, unsigned int y);

	virtual void setLayoutParams(const LayoutParams& layoutParams);
	virtual const LayoutParams& getLayoutParams() const;

	virtual bool isInvalidated() const;
	virtual bool hasExplicitSize() const;

	virtual bool isLayout() const;
	virtual bool isAutonomousComponent() const;

	virtual void callEvent(const Event& event);
	virtual void addEventHandler(EventType eventType, EventHandler eventHandler);
protected:
	Map<EventType, EventHandler> _eventHandlers;

	VGAColor _background;
	bool _visible;

	unsigned int _x;
	unsigned int _y;
	unsigned int _width;
	unsigned int _height;
	bool _explicitSize;
	LayoutParams _layoutParams;

	bool _focused;
	bool _hovered;

	bool _invalidated;
};

#endif //OSTEST_COMPONENT_H
