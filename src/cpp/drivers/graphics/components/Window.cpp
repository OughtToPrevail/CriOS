#include "Window.h"

Window::Window(Layout* layout)
{
	// TODO: Add title bar
	this->add(layout);
}

bool Window::isAutonomousComponent() const
{
	return true;
}
