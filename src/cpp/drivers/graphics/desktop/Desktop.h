#ifndef OSTEST_DESKTOP_H
#define OSTEST_DESKTOP_H

#include "VerticalLayout.h"
#include "ProgramsGrid.h"
#include "Taskbar.h"

class Desktop : public VerticalLayout
{
public:
	Desktop();
private:
	ProgramsGrid _programsGrid;
	Taskbar _taskbar;
};


#endif //OSTEST_DESKTOP_H
