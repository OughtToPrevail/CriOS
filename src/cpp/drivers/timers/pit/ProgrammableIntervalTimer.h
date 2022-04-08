#ifndef OSTEST_PROGRAMMABLEINTERVALTIMER_H
#define OSTEST_PROGRAMMABLEINTERVALTIMER_H

// https://wiki.osdev.org/Programmable_Interval_Timer
// https://www.youtube.com/watch?v=DuqxVmVGQSU

#include "IOPort.h"

struct PITCommand
{
	unsigned char bcd:1;
	unsigned char mode:3;
	unsigned char accessMode:2;
	unsigned char channel:2;
};

class ProgrammableIntervalTimer
{
public:
	ProgrammableIntervalTimer();

	void alertTick();
	void wait(unsigned int ms);
	void waitPrecise(unsigned int microseconds);

	unsigned long long getCurrentTime();
private:
	IOPort _pitCommand;
	IOPort _channel0Data;
	volatile unsigned long long _currentTime;  // in microseconds
};

#endif //OSTEST_PROGRAMMABLEINTERVALTIMER_H
