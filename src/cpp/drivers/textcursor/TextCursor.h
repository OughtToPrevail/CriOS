#ifndef OSTEST_TEXTCURSOR_H
#define OSTEST_TEXTCURSOR_H

#include "IOPort.h"

class TextCursor
{
public:
	TextCursor();

	void setCursorPosition(unsigned short pos);
	void setCursorPosition(int row, int column);
	unsigned short getCursorPosition();

	void disable();
private:
	IOPort _commandPort;
	IOPort _dataPort;
};


#endif //OSTEST_TEXTCURSOR_H
