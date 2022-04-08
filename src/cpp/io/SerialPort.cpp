#include "SerialPort.h"

#define BUFFER_EMPTY_CHECK 0x20

SerialPort::SerialPort(unsigned short com) : SerialPort(com,
														DEFAULT_CONFIGURATION,
														DEFAULT_BUFFER_CONFIGURATION,
														DEFAULT_MODEM_CONFIGURATION)
{

}

SerialPort::SerialPort(unsigned short com, unsigned char lineConfiguration, unsigned char bufferConfiguration,
					   unsigned char modemConfiguration)
		: _dataPort(SERIAL_DATA_PORT(com)),
		  _fifoCommandPort(SERIAL_FIFO_COMMAND_PORT(com)),
		  _lineCommandPort(SERIAL_LINE_COMMAND_PORT(com)),
		  _modemCommandPort(SERIAL_MODEM_COMMAND_PORT(com)),
		  _lineStatusPort(SERIAL_LINE_STATUS_PORT(com))
{
	this->_lineCommandPort.write(lineConfiguration);
	this->_fifoCommandPort.write(bufferConfiguration);
	this->_modemCommandPort.write(modemConfiguration);
}

void SerialPort::configureBaudRate(unsigned short divisor)
{
	this->_lineCommandPort.write(HIGH_THEN_LOW_BYTE_COMMAND);
	this->_dataPort.writeIntAsChar(divisor >> 8);
	this->_dataPort.writeIntAsChar(divisor);
}

void SerialPort::write(unsigned char c)
{
	while(!this->isFIFOBufferEmpty()); // wait until buffer is empty
	this->_dataPort.write(c);
}

bool SerialPort::isFIFOBufferEmpty()
{
	return (this->_lineStatusPort.read() & BUFFER_EMPTY_CHECK) != 0;
}

unsigned char SerialPort::read()
{
	return this->_dataPort.read();
}
