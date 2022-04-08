#ifndef OSTEST_GRIDLAYOUT_H
#define OSTEST_GRIDLAYOUT_H

#include "Layout.h"

class GridLayoutParams : public LayoutParams
{
public:
	GridLayoutParams(unsigned int gridX, unsigned int gridY, unsigned int margin=0);

	unsigned int getGridX() const;
	unsigned int getGridY() const;
private:
	unsigned int _gridX;
	unsigned int _gridY;
};

class GridLayout : public Layout
{
public:
	GridLayout();

	virtual void setGridBounds(unsigned int horizontalElements, unsigned int verticalElements);

	void draw(Canvas& canvas) const override;

	void recomputeDimensions() override;
private:
	void computeBoxSize();

	unsigned int _horizontalElements;
	unsigned int _verticalElements;

	unsigned int _componentBoxWidth;
	unsigned int _componentBoxHeight;
};


#endif //OSTEST_GRIDLAYOUT_H
