#include "TextCursor.h"
#include "FrameBuffer.h"

#define COMMAND_PORT 0x3D4
#define DATA_PORT 0x3D5
#define HIGH_BYTE_COMMAND static_cast<unsigned char>(14)
#define LOW_BYTE_COMMAND static_cast<unsigned char>(15)
#define DISABLE_DATA static_cast<unsigned char>(0x20)

TextCursor::TextCursor() : _commandPort(COMMAND_PORT), _dataPort(DATA_PORT)
{

}

void TextCursor::setCursorPosition(unsigned short pos)
{
	this->_commandPort.write(HIGH_BYTE_COMMAND);
	this->_dataPort.writeIntAsChar(pos >> 8);
	this->_commandPort.write(LOW_BYTE_COMMAND);
	this->_dataPort.writeIntAsChar(pos);
}

void TextCursor::setCursorPosition(int row, int column)
{
	this->setCursorPosition(row * FRAMEBUFFER_COLUMNS + column);
}

unsigned short TextCursor::getCursorPosition()
{
	unsigned short pos = 0;
	this->_commandPort.write(HIGH_BYTE_COMMAND);
	pos |= static_cast<unsigned short>(this->_dataPort.read()) << 8;
	this->_commandPort.write(LOW_BYTE_COMMAND);
	pos |= this->_dataPort.read();
	return pos;
}

void TextCursor::disable()
{
	this->_commandPort.write(HIGH_BYTE_COMMAND);
	this->_dataPort.write(DISABLE_DATA);
}



