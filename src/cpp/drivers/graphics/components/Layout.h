#ifndef OSTEST_LAYOUT_H
#define OSTEST_LAYOUT_H

#include "Component.h"
#include "Vector.h"

class Layout : public Component
{
public:
	Layout();

	virtual void add(Component& component);
	virtual void add(Component* component);

	void recomputeDimensions() override;
	virtual void updateChildren();

	bool isLayout() const override;
	bool isAutonomousComponent() const override;

	Vector<Component*>& getChildren();
protected:
	Vector<Component*> _children;
};


#endif //OSTEST_LAYOUT_H
