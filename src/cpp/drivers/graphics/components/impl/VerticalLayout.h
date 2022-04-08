#ifndef OSTEST_VERTICALLAYOUT_H
#define OSTEST_VERTICALLAYOUT_H

#include "Layout.h"
#include "Positioning.h"

class VerticalLayout : public Layout
{
public:
	VerticalLayout();

	void draw(Canvas &canvas) const override;
	void recomputeDimensions() override;

	void setPositioning(Positioning positioning);
private:
	Positioning _positioning;
};


#endif //OSTEST_VERTICALLAYOUT_H
