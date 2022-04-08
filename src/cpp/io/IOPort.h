#ifndef OSTEST_IOPORT_H
#define OSTEST_IOPORT_H

#include "OutputStream.h"
#include "InputStream.h"

class IOPort : public OutputStream, public InputStream
{
public:
	explicit IOPort(unsigned short port);

	void write(unsigned char c) override;
	unsigned char read() override;
private:
	unsigned short _port;
};


#endif //OSTEST_IOPORT_H
