#include "Layout.h"

Layout::Layout() : Component(), _children()
{

}

void Layout::add(Component& component)
{
	this->add(&component);
}

void Layout::add(Component* component)
{
	this->_children.pushBack(component);
	this->_invalidated = true;
}

void Layout::recomputeDimensions()
{
	this->updateChildren();
	this->_invalidated = false;
}

void Layout::updateChildren()
{
	for(Component* component : this->_children)
	{
		if(component->isLayout())
		{
			Layout* layout = static_cast<Layout*>(component);
			layout->updateChildren();
		}
		if(component->isInvalidated() && !component->hasExplicitSize())
		{
			component->recomputeDimensions();
		}
	}
}

bool Layout::isLayout() const
{
	return true;
}

bool Layout::isAutonomousComponent() const
{
	return false;
}

Vector<Component*>& Layout::getChildren()
{
	return this->_children;
}
