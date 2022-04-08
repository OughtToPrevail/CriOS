#include "Memory.h"
#include "VideoGraphicsArray.h"

// VGA Tutorial - https://www.youtube.com/watch?v=N68cYNWZgy8
// Register docs - https://01.org/sites/default/files/documentation/ilk_ihd_os_vol3_part1r2_0.pdf
// DAC - https://www.phatcode.net/res/224/files/html/ch34/34-05.html, https://bos.asmhackers.net/docs/vga_without_bios/docs/palettesetting.pdf

/*
 Will use 320x200 with 256 colors
 See all modes: https://en.wikipedia.org/wiki/Video_Graphics_Array#Standard_graphics_modes
 Comparison between 320x240 and 640x480: https://upload.wikimedia.org/wikipedia/commons/f/f8/Torak.gif
 Values taken from - https://files.osdev.org/mirrors/geezer/osd/graphics/modes.c (g_320x200x256)
 */

/*
 0 - Uses CGA instead of MDA (allows for more colors),
 1 - Allows memory access to VGA
 2:3 - set default clock for CRT
 4 - reserved
 5 - page select (unused in this mode of VGA)
 6 - changed HSYNC Polarity to negative
 7 - left VSYNC Polarity as default
*/
#define MISC_OUTPUT 0b1100011

// Sequencer
// resets the sequencer and sets the plane mask and memory mode
#define SEQUENCER_INPUT_COUNT 5
unsigned char SEQUENCER_SETTINGS[SEQUENCER_INPUT_COUNT] = {
		0x03, 0x01, 0x0F, 0x00, 0x0E
};

// (CRTC - cathode ray tube controller)
// controls different values, all available in the Intel specification above,
// basically a lot are related to text so they are 0 and others are related to addressing
#define CRTC_INPUT_COUNT 25
unsigned char CRTC_SETTINGS[CRTC_INPUT_COUNT] = {
		0x5F, 0x4F, 0x50, 0x82, 0x54, 0x80, 0xBF, 0x1F,
		0x00, 0x41, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x9C, 0x0E, 0x8F, 0x28, 0x40, 0x96, 0xB9, 0xA3,
		0xFF
};
// (GC - graphics controller)
// Enables various options in the GC, most importantly the graphics control
#define GC_INPUT_COUNT 9
unsigned char GC_SETTINGS[GC_INPUT_COUNT] = {
		0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x05, 0x0F,
		0xFF
};

// (AC - attribute controller)
// Enables certain capabilities of the VGA and declares we use 16 color bits
#define AC_INPUT_COUNT 22
unsigned char AC_SETTINGS[AC_INPUT_COUNT] = {
		0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
		0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
		0x41, 0x00, 0x0F, 0x00, 0x00
};

#define VGA_MEMORY (reinterpret_cast<unsigned char*>(0xA0000))

VideoGraphicsArray::VideoGraphicsArray() :
		_activated(false),
		_miscWritePort(0x3C2),
		_crtcIndexPort(0x3D4),
		_crtcDataPort(0x3D5),
		_sequencerIndexPort(0x3C4),
		_sequencerDataPort(0x3C5),
		_graphicsControllerIndexPort(0x3CE),
		_graphicsControllerDataPort(0x3CF),
		_attributeControllerIndexPort(0x3C0),
		_attributeControllerWritePort(0x3C0),
		_attributeControllerResetPort(0x3DA),
		_dacMaskPort(0x3C6),
		_dacWriteIndexPort(0x3C8),
		_dacDataPort(0x3C9)
{
}

void VideoGraphicsArray::activate()
{
	this->_miscWritePort.write(MISC_OUTPUT);

	this->writeBytes(this->_sequencerDataPort, this->_sequencerIndexPort, SEQUENCER_SETTINGS, SEQUENCER_INPUT_COUNT);

	this->writeBytes(this->_crtcDataPort, this->_crtcIndexPort, CRTC_SETTINGS, CRTC_INPUT_COUNT);
	this->writeBytes(this->_graphicsControllerDataPort, this->_graphicsControllerIndexPort, GC_SETTINGS, GC_INPUT_COUNT);
	this->writeBytes(this->_attributeControllerWritePort, this->_attributeControllerIndexPort, AC_SETTINGS, AC_INPUT_COUNT);

	this->_attributeControllerResetPort.read();
	this->_attributeControllerIndexPort.write(0x20);

	// map color palette
	this->_dacMaskPort.write(0xFF);
	this->_dacWriteIndexPort.write(0);
	for(int i = 0; i < COLOR_COUNT; i++)
	{
		const VGAColor& color = ColorPalette::getColorPalette()[i];
		this->_dacDataPort.write(color.getRed());
		this->_dacDataPort.write(color.getGreen());
		this->_dacDataPort.write(color.getBlue());
	}

	this->_activated = true;
}

void VideoGraphicsArray::writeBytes(IOPort dataPort, IOPort indexPort, unsigned char bytes[], int size)
{
	for(int i = 0; i < size; i++)
	{
		indexPort.write(i);
		dataPort.write(bytes[i]);
	}
}

void VideoGraphicsArray::writeBackBuffer(unsigned char backBuffer[]) const
{
	if(!this->_activated)
	{
		return;
	}
	Memory::memcpy(VGA_MEMORY, backBuffer, VGA_BUFFER_SIZE, VGA_BUFFER_SIZE);
}
