#ifndef OSTEST_VIDEOGRAPHICSARRAY_H
#define OSTEST_VIDEOGRAPHICSARRAY_H

#include "IOPort.h"
#include "VGAColor.h"
#include "ColorPalette.h"

#define VGA_WIDTH 320
#define VGA_HEIGHT 200
#define VGA_BUFFER_SIZE (VGA_WIDTH * VGA_HEIGHT)

class VideoGraphicsArray
{
public:
	VideoGraphicsArray();

	void activate();

	void writeBackBuffer(unsigned char backBuffer[]) const;
private:
	void writeBytes(IOPort dataPort, IOPort indexPort, unsigned char bytes[], int size);

	bool _activated;
	IOPort _miscWritePort;
	IOPort _crtcIndexPort;
	IOPort _crtcDataPort;
	IOPort _sequencerIndexPort;
	IOPort _sequencerDataPort;
	IOPort _graphicsControllerIndexPort;
	IOPort _graphicsControllerDataPort;
	IOPort _attributeControllerIndexPort;
	IOPort _attributeControllerWritePort;
	IOPort _attributeControllerResetPort;
	IOPort _dacMaskPort;
	IOPort _dacWriteIndexPort;
	IOPort _dacDataPort;
};

#endif //OSTEST_VIDEOGRAPHICSARRAY_H
