#include "FrameBuffer.h"

#define FRAME_BUFFER ((FrameChar*) 0x000B8000)

FrameBuffer::FrameBuffer() : _textCursor(0), _background(FrameColor::BLACK), _foreground(FrameColor::WHITE)
{
}

void FrameBuffer::write(unsigned char c)
{
	if(c == '\n')
	{
		this->_textCursor += FRAMEBUFFER_COLUMNS - this->_textCursor % FRAMEBUFFER_COLUMNS; // fill in till the end of the line
	}
	while(this->_textCursor >= FRAMEBUFFER_SIZE)
	{
		// move all lines 1 up
		for(unsigned int i = FRAMEBUFFER_COLUMNS; i < FRAMEBUFFER_SIZE; i++)
		{
			FRAME_BUFFER[i - FRAMEBUFFER_COLUMNS] = FRAME_BUFFER[i];
		}
		for(unsigned int i = FRAMEBUFFER_SIZE - FRAMEBUFFER_COLUMNS; i < FRAMEBUFFER_SIZE; i++)
		{
			FRAME_BUFFER[i] = FrameChar{0, 0, 0};
		}
		this->_textCursor -= FRAMEBUFFER_COLUMNS;
	}
	if(c == '\n')
	{
		return;
	}
	FRAME_BUFFER[this->_textCursor] = this->toFrameChar(c);
	this->_textCursor++;
}

void FrameBuffer::fill(char c)
{
	for(int i = 0; i < FRAMEBUFFER_ROWS; i++)
	{
		fill(i, c);
	}
}

void FrameBuffer::fill(int row, char c)
{
	for(int i = 0; i < FRAMEBUFFER_COLUMNS; i++)
	{
		FRAME_BUFFER[row * FRAMEBUFFER_ROWS + i] = this->toFrameChar(c);
	}
}

void FrameBuffer::move(int row)
{
	this->_textCursor = row * FRAMEBUFFER_COLUMNS;
}

void FrameBuffer::move(int row, int column)
{
	this->_textCursor = row * FRAMEBUFFER_COLUMNS + column;
}

void FrameBuffer::moveExact(unsigned short position)
{
	this->_textCursor = position;
}

void FrameBuffer::reset()
{
	this->move(0);
}

void FrameBuffer::clear()
{
	this->_background = FrameColor::BLACK;
	this->_foreground = FrameColor::WHITE;
	fill('\0');
	this->move(0);
}

unsigned short FrameBuffer::getCurrentPosition()
{
	return this->_textCursor;
}

void FrameBuffer::setBackground(FrameColor color)
{
	this->_background = color;
}

void FrameBuffer::setForeground(FrameColor color)
{
	this->_foreground = color;
}

FrameChar FrameBuffer::toFrameChar(unsigned char c)
{
	return {static_cast<unsigned char>(c),
			static_cast<unsigned char>(this->_foreground),
			static_cast<unsigned char>(this->_background)};
}
