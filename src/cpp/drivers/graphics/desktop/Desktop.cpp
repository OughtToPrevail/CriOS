#include "Desktop.h"

Desktop::Desktop()
{
	this->_programsGrid.setSize(VGA_WIDTH, VGA_HEIGHT - 20);
	this->_taskbar.setSize(VGA_WIDTH, 20);

	this->add(this->_programsGrid);
	this->add(this->_taskbar);
}
