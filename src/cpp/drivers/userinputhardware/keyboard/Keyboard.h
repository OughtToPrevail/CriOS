#ifndef OSTEST_KEYBOARD_H
#define OSTEST_KEYBOARD_H

#include "IOPort.h"
#include "KeyboardKey.h"
#include "UserInputHardware.h"

enum class KeyboardEventType
{
	PRESSED,
	RELEASED,
	ERROR
};

struct KeyboardEvent
{
	const KeyboardKey& keyboardKey;
	KeyboardEventType eventType;
};

class Keyboard
{
public:
	explicit Keyboard(UserInputHardware& userInputHardware);

	void alertKeyInterrupt();
private:
	static void alertKeyEvent(unsigned char scanCode);
	void handleKeyEvent(unsigned char scanCode);
	static KeyboardEvent toEvent(unsigned char scanCode);

	UserInputHardware& _userInputHardware;
	KeyboardState _currentState;
};


#endif //OSTEST_KEYBOARD_H
