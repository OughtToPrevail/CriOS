#ifndef OSTEST_FRAMEBUFFER_H
#define OSTEST_FRAMEBUFFER_H

#include "OutputStream.h"

enum class FrameColor
{
	BLACK,
	BLUE,
	GREEN,
	CYAN,
	RED,
	MAGENTA,
	BROWN,
	LIGHT_GREY,
	DARK_GREY,
	LIGHT_BLUE,
	LIGHT_GREEN,
	LIGHT_CYAN,
	LIGHT_RED,
	LIGHT_MAGENTA,
	LIGHT_BROWN,
	WHITE
};

struct FrameChar
{
	unsigned char c;
	unsigned char foreground: 4;
	unsigned char background: 4;
} __attribute__((packed));

#define FRAMEBUFFER_ROWS (25)
#define FRAMEBUFFER_COLUMNS (80)
#define FRAMEBUFFER_SIZE (FRAMEBUFFER_COLUMNS * FRAMEBUFFER_ROWS)

class FrameBuffer : public OutputStream
{
public:
	FrameBuffer();

	void write(unsigned char c) override;

	void fill(char c);
	void fill(int row, char c);
	void move(int row);
	void move(int row, int column);
	void moveExact(unsigned short position);
	void reset();
	void clear();

	unsigned short getCurrentPosition();

	void setBackground(FrameColor color);
	void setForeground(FrameColor color);
private:
	FrameBuffer(const FrameBuffer&) = delete;  // prevents making copies of this

	FrameChar toFrameChar(unsigned char c);

	int _textCursor;
	FrameColor _background;
	FrameColor _foreground;
};

#endif //OSTEST_FRAMEBUFFER_H
