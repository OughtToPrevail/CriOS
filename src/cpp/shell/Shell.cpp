#include "Shell.h"
#include "System.h"

void Shell::handleKeyPress(const KeyCode& keyCode)
{
	if(keyCode == KeyCode::BACKSPACE)
	{
		this->deleteChar();
	} else if(keyCode.isASCII())
	{
		this->write(keyCode.asASCII());
	}
}

void Shell::write(unsigned char c)
{
	FrameBuffer& buffer = System::getSystem().getFrameBuffer();
	unsigned int cursorPosition = Syscall::syscall(SYSCALL_GET_CURSOR);
	buffer.moveExact(cursorPosition);
	buffer.write(c);
	Syscall::syscall(SYSCALL_SET_CURSOR, buffer.getCurrentPosition());
}

void Shell::deleteChar()
{
	TextCursor& textCursor = System::getSystem().getTextCursor();
	int newPosition = textCursor.getCursorPosition() - 1;
	if(newPosition < 0)
	{
		return;
	}
	textCursor.setCursorPosition(newPosition);
	this->write(' ');
	textCursor.setCursorPosition(newPosition);
}
