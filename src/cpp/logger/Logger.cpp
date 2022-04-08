#include "Logger.h"
#include "VAArgs.h"
#include "String.h"

#define MAX_LOG_LENGTH 512

Logger::Logger() : _serialPort(COM1)
{

}

void Logger::log(LogType logType, const char* log, ...)
{
	VAArgs args(&log, sizeof(char*));
	char buffer[MAX_LOG_LENGTH];
	char sysCallBuffer[MAX_LOG_LENGTH];
	const char* logTypeName;
	String::sprintf(buffer, MAX_LOG_LENGTH, log, args);

	switch(logType)
	{
		case LogType::DEBUG:
			logTypeName = "DEBUG";
			break;
		case LogType::INFO:
			logTypeName = "INFO";
			break;
		case LogType::WARNING:
			logTypeName = "WARNING";
			break;
		case LogType::ERROR:
			logTypeName = "ERROR";
			break;
		default:
			logTypeName = "UNKNOWN";
			break;
	}
	String::sprintf(sysCallBuffer, MAX_LOG_LENGTH, "%s: %s\n", logTypeName, buffer);
	Syscall::syscall(SYSCALL_LOG, sysCallBuffer);
}

void Logger::logStringKernel(const char* log)
{
	this->_serialPort.writeString(log);
}

