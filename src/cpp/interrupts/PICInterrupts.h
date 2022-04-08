#ifndef OSTEST_PICINTERRUPTS_H
#define OSTEST_PICINTERRUPTS_H

#include "IOPort.h"
#include "InterruptHandler.h"

#define PIC_SIZE (8)
#define PIC1_OFFSET (0x20)
#define PIC2_OFFSET (PIC1_OFFSET + PIC_SIZE)

enum class PIC
{
	PIC1,
	PIC2
};

class PICInterrupts
{
public:
	static PICInterrupts& getPICInterrupts();

	void acknowledgePICInterrupt(PIC pic);

private:
	PICInterrupts();

	void initPIC(IOPort& cmdPort, IOPort& dataPort, unsigned char offset, unsigned char wireInfo);

	IOPort _pic1Command;
	IOPort _pic1Data;
	IOPort _pic2Command;
	IOPort _pic2Data;
};

extern "C"
{
void pic1Interrupt(CPUState, StackState);
void pic2Interrupt(CPUState, StackState);
}

#endif //OSTEST_PICINTERRUPTS_H
