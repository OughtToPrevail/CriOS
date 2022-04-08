#include "ProgramsGrid.h"
#include "Resources.h"
#include "DesktopProgram.h"

#define PROGRAMS_GRID_SIZE 10

ProgramsGrid::ProgramsGrid() : _textEditor("Text Editor", Resources::Notepad)
{
	this->setGridBounds(PROGRAMS_GRID_SIZE, PROGRAMS_GRID_SIZE);
	this->setBackground(Theme::DESKTOP_BACKGROUND);

	this->_textEditor.setLayoutParams(GridLayoutParams{0, 0, 5});
	this->add(this->_textEditor);
}

void ProgramsGrid::draw(Canvas& canvas) const
{
	canvas.drawImage(0, 0, Resources::thisisfine);  // set desktop background
	GridLayout::draw(canvas);
}
