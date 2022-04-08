#ifndef OSTEST_USERINPUTHARDWARE_H
#define OSTEST_USERINPUTHARDWARE_H

#include "IOPort.h"

typedef void(*Callback)(unsigned char);

#define STATUS_EMPTY 0
#define KEYBOARD_DATA 0
#define MOUSE_DATA 1

struct UserInputStatus  // https://github.com/qb40/keyboardcontroller
{
	unsigned char outputBufferStatus:1;  // 1 full, 0 empty
	unsigned char inputBufferStatus:1;
	unsigned char systemFlag:1;
	unsigned char commandOrData:1;
	unsigned char keyboardLocked:1;  // 0 locked, 1 unlocked
	unsigned char keyboardOrMouse:1; // 0 keyboard, 1 mouse
	unsigned char timeout:1;  // 0 ok, 1 timeout
	unsigned char parityError:1;  // 0 ok, 1 error
} __attribute__((packed));

struct UserInputValue
{
	UserInputStatus status;
	unsigned char value;
};

class UserInputHardware  // for keyboard & mouse
{
public:
	UserInputHardware();

	void setKeyboardCallback(Callback callback);
	void setMouseCallback(Callback callback);

	void enablePSInterrupts();

	void read();
	void writeMouse(unsigned char val);

	UserInputValue readValue(); // read without callback
private:

	IOPort _dataPort;
	IOPort _commandPort;

	Callback _keyboardCallback;
	Callback _mouseCallback;
};


#endif //OSTEST_USERINPUTHARDWARE_H
