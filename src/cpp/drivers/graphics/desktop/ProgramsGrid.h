#ifndef OSTEST_PROGRAMSGRID_H
#define OSTEST_PROGRAMSGRID_H

#include "Component.h"
#include "GridLayout.h"
#include "DesktopProgram.h"

class ProgramsGrid : public GridLayout
{
public:
	ProgramsGrid();

	void draw(Canvas &canvas) const override;
private:
	DesktopProgram _textEditor;  // TODO: has to be a field for now as it's used as a pointer so has to be kept in memory, in the future possibly use a vector?
};


#endif //OSTEST_PROGRAMSGRID_H
