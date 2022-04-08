#ifndef CRIOS_SHELL_H
#define CRIOS_SHELL_H

#include "OutputStream.h"
#include "KeyCode.h"

class Shell : public OutputStream
{
public:
	void handleKeyPress(const KeyCode& keyCode);

	void write(unsigned char c) override;
	void deleteChar();
};

#endif //CRIOS_SHELL_H
