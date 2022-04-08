#include "PICInterrupts.h"

// https://wiki.osdev.org/PIC

#define PIC1_CMD 0x20
#define PIC1_DATA (PIC1_CMD + 1)
#define PIC2_CMD 0xA0
#define PIC2_DATA (PIC2_CMD + 1)

// Slave PIC is connected at interrupt 2 (starts from 0, so it's the third wire, and as each bit indicates a wire, this will be the 3rd wire)
#define SLAVE_PIC_WIRE 0b100
// Indicator - https://stanislavs.org/helppc/8259.html
#define MASTER_PIC_ATTACHED 0b10

// Initializes the pic
#define PIC_INIT 0x10
// Tells the init that a ICW4 initialization isn't required https://k.lse.epita.fr/internals/8259a_controller.html
#define PIC_USE_ICW4 0x01
#define PIC_ICW4_8086	0x01
// Acknowledges a PIC interrupt
#define PIC_ACKNOWLEDGE 0x20

PICInterrupts::PICInterrupts() : _pic1Command(PIC1_CMD), _pic1Data(PIC1_DATA), _pic2Command(PIC2_CMD), _pic2Data(PIC2_DATA)
{
	this->initPIC(this->_pic1Command, this->_pic1Data, PIC1_OFFSET, SLAVE_PIC_WIRE);
	this->initPIC(this->_pic2Command, this->_pic2Data, PIC2_OFFSET, MASTER_PIC_ATTACHED);
}

void PICInterrupts::initPIC(IOPort& cmdPort, IOPort& dataPort, unsigned char offset, unsigned char wireInfo)
{
	int mask = dataPort.read();

	cmdPort.write(PIC_INIT | PIC_USE_ICW4);
	dataPort.write(offset);
	dataPort.write(wireInfo);
	dataPort.write(PIC_ICW4_8086);

	dataPort.write(mask);
}

void PICInterrupts::acknowledgePICInterrupt(PIC pic)
{
	this->_pic1Command.write(PIC_ACKNOWLEDGE); // Always acknowledge PIC1 because it forwards to PIC2
	if(pic == PIC::PIC2)
	{
		this->_pic2Command.write(PIC_ACKNOWLEDGE);
	}
}

PICInterrupts& PICInterrupts::getPICInterrupts()
{
	static PICInterrupts picInterrupts;
	return picInterrupts;
}

void pic1Interrupt(CPUState, StackState)
{
	PICInterrupts::getPICInterrupts().acknowledgePICInterrupt(PIC::PIC1);
}

void pic2Interrupt(CPUState, StackState)
{
	PICInterrupts::getPICInterrupts().acknowledgePICInterrupt(PIC::PIC2);
}
