#ifndef OSTEST_SERIALPORT_H
#define OSTEST_SERIALPORT_H

#include "IOPort.h"
#include "InputStream.h"
#include "OutputStream.h"

// https://wiki.osdev.org/Serial_Ports

// Taken from littleosbook

// sends actual data
#define SERIAL_DATA_PORT(base) (base)
// acts as a buffer in case we're sending data faster than the line can handle
#define SERIAL_FIFO_COMMAND_PORT(base) (base + 2)
// commands for the line
#define SERIAL_LINE_COMMAND_PORT(base) (base + 3)
// configures we are ready to send data
#define SERIAL_MODEM_COMMAND_PORT(base) (base + 4)
// used for getting status of FIFO queue (whether it's empty, if yes, we can transmit more data, if not, we have to wait)
#define SERIAL_LINE_STATUS_PORT(base) (base + 5)

// How a short should be structured when sent (first the most significant bits, then the least significant bits)
#define HIGH_THEN_LOW_BYTE_COMMAND 0x80

// Defines a data length of 8 bits, no parity bits (for error checks), one stop bit (indicates the end of a frame)
// and without break control
#define DEFAULT_CONFIGURATION 0x03
// Enables a FIFO buffer of 14 bytes and clears all data already in it
// (TODO: can't find out why this is recommended, but seems widely used, both by the littleosbook and by the osdev community,
//  apparently the wikibook on serial programming defined it but can't find it online)
#define DEFAULT_BUFFER_CONFIGURATION 0xC7
// Enables the port only for writing, useful especially for using the port for debugging
#define DEFAULT_MODEM_CONFIGURATION 0x03

// taken from osdev
#define COM1 0x3F8
#define COM2 0x2F8
#define COM3 0x3E8
#define COM4 0x2E8

class SerialPort : public OutputStream, public InputStream
{
public:
	explicit SerialPort(unsigned short com);
	SerialPort(unsigned short com, unsigned char lineConfiguration, unsigned char bufferConfiguration,
			   unsigned char modemConfiguration);

	/**
	 * Divides the default baud rate (115200) by the specified divisor
	 *
	 * @param divisor the divisor for the default baud rate
	 */
	void configureBaudRate(unsigned short divisor);

	void write(unsigned char c) override;
	unsigned char read() override;
private:
	IOPort _dataPort;
	IOPort _fifoCommandPort;
	IOPort _lineCommandPort;
	IOPort _modemCommandPort;
	IOPort _lineStatusPort;

	bool isFIFOBufferEmpty();
};


#endif //OSTEST_SERIALPORT_H
