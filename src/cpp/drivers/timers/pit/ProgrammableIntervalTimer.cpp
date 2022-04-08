#include "ProgrammableIntervalTimer.h"
#include "TimeFormat.h"

#define PIT_COMMAND_PORT 0x43
#define CHANNEL_0_PORT 0x40

#define BCD_BINARY_COUNTER 0
#define RATE_GENERATOR 0b010
#define READ_WRITE 0b11
// Channel descriptions: https://wiki.osdev.org/Programmable_Interval_Timer#Channel_0, only 0 connects to interrupts
#define CHANNEL_0 0

#define PIT_DEFAULT_HZ 1193182
#define REQUIRED_HZ 1000

ProgrammableIntervalTimer::ProgrammableIntervalTimer() : _pitCommand(PIT_COMMAND_PORT), _channel0Data(CHANNEL_0_PORT), _currentTime(0)
{
	PITCommand command{};
	command.bcd = BCD_BINARY_COUNTER;
	command.mode = RATE_GENERATOR;
	command.accessMode = READ_WRITE;
	command.channel = CHANNEL_0;
	this->_pitCommand.write(*reinterpret_cast<unsigned char*>(&command));
	// Explanation on divisor: https://en.wikibooks.org/wiki/X86_Assembly/Programmable_Interval_Timer
	short divisor = PIT_DEFAULT_HZ / REQUIRED_HZ;
	this->_channel0Data.write(divisor & 0xFF);
	this->_channel0Data.write((divisor >> 8) & 0xFF);
}

#define LATCH ((PIT_DEFAULT_HZ + (REQUIRED_HZ / 2)) / REQUIRED_HZ)

void ProgrammableIntervalTimer::alertTick()
{
	this->_currentTime += LATCH;
}

void ProgrammableIntervalTimer::wait(unsigned int ms)
{
	this->waitPrecise(MS_TO_MICROSECONDS(ms));
}

void ProgrammableIntervalTimer::waitPrecise(unsigned int microseconds)
{
	unsigned long long start = this->_currentTime;
	while(this->_currentTime - start < microseconds);
}

unsigned long long ProgrammableIntervalTimer::getCurrentTime()
{
	return this->_currentTime;
}
