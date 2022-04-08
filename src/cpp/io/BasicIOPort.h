#ifndef OSTEST_BASICIOPORT_H
#define OSTEST_BASICIOPORT_H

extern "C"
{
	void basicIOPort_sendByte(unsigned char value, unsigned short port);
	unsigned char basicIOPort_recvByte(unsigned short port);
}

#endif //OSTEST_BASICIOPORT_H
