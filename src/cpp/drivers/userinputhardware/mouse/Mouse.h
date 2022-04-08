#ifndef OSTEST_MOUSE_H
#define OSTEST_MOUSE_H

#include "UserInputHardware.h"
#include "Event.h"

struct MousePacket
{
	unsigned char buttonLeft:1;
	unsigned char buttonRight:1;
	unsigned char buttonMiddle:1;
	unsigned char alwaysOne:1;
	unsigned char xAxisSignBit:1;
	unsigned char yAxisSignBit:1;
	unsigned char xAxisOverflowBit:1;
	unsigned char yAxisOverflowBit:1;
	unsigned char movementX;
	unsigned char movementY;
} __attribute__((packed));

class Mouse
{
public:
	explicit Mouse(UserInputHardware& userInputHardware);
	void enableMouse();

	void alertMouseInterrupt();
private:
	static void alertMouseData(unsigned char mouseData);
	void handleMouseData(unsigned char mouseData);
	bool updateButtonState(EventType eventType, bool active, bool& downState);

	UserInputHardware& _userInputHardware;
	int _packetByte;
	unsigned char _mousePacket[sizeof(MousePacket)];

	bool _mouseLeftDown;
	bool _mouseMiddleDown;
	bool _mouseRightDown;
	unsigned long long _lastClick;
};


#endif //OSTEST_MOUSE_H
