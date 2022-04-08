#ifndef OSTEST_MOUSECURSOR_H
#define OSTEST_MOUSECURSOR_H

#include "Component.h"

class MouseCursor : public Component
{
public:
	MouseCursor();

	void moveTo(unsigned int x, unsigned int y);
	void moveBy(int relX, int relY);
	void draw(Canvas &canvas) const override;
};


#endif //OSTEST_MOUSECURSOR_H
