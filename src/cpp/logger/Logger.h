#ifndef OSTEST_LOGGER_H
#define OSTEST_LOGGER_H

#include "SerialPort.h"
#include "Syscall.h"

enum class LogType
{
	DEBUG,
	INFO,
	WARNING,
	ERROR
};

class Logger
{
public:
	Logger();

	void log(LogType logType, const char* log, ...);

	void logStringKernel(const char* log);
private:
	SerialPort _serialPort;
};


#endif //OSTEST_LOGGER_H
