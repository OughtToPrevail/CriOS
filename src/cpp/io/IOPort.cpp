#include "IOPort.h"
#include "BasicIOPort.h"

IOPort::IOPort(unsigned short port) : _port(port)
{

}

void IOPort::write(unsigned char c)
{
	basicIOPort_sendByte(c, this->_port);
}

unsigned char IOPort::read()
{
	return basicIOPort_recvByte(this->_port);
}
