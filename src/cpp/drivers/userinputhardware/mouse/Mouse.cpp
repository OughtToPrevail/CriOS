#include "Mouse.h"
#include "System.h"
#include "Math.h"
#include "TimeFormat.h"

// https://wiki.osdev.org/PS/2_Mouse#Mouse_Device_Over_PS.2F2
#define USE_DEFAULT_SETTINGS 0xF6
#define ENABLE_DATA_REPORTING 0xF4

#define UNSIGNED_CHAR_TOTAL_VALUES (1 << 8)

#define TOO_LARGE 100

// time in microseconds for double click
#define TIME_FOR_DOUBLE_CLICK MS_TO_MICROSECONDS(500)

Mouse::Mouse(UserInputHardware& userInputHardware) : _userInputHardware(userInputHardware), _packetByte(0), _mousePacket(), _mouseLeftDown(false), _mouseMiddleDown(false), _mouseRightDown(false), _lastClick(0)
{
	this->_userInputHardware.setMouseCallback(&Mouse::alertMouseData);
}

void Mouse::enableMouse()
{
	this->_userInputHardware.writeMouse(USE_DEFAULT_SETTINGS);
	this->_userInputHardware.writeMouse(ENABLE_DATA_REPORTING);
}

void Mouse::alertMouseInterrupt()
{
	this->_userInputHardware.read();
}

void Mouse::alertMouseData(unsigned char mouseData)
{
	System::getSystem().getMouse().handleMouseData(mouseData);
}

void Mouse::handleMouseData(unsigned char mouseData)
{
	this->_mousePacket[this->_packetByte++] = mouseData;
	if(this->_packetByte == sizeof(MousePacket))
	{
		this->_packetByte = 0;
		MousePacket* mousePacket = reinterpret_cast<MousePacket*>(this->_mousePacket);
		if(!mousePacket->alwaysOne)
		{
			return;
		}
		if(mousePacket->xAxisOverflowBit || mousePacket->yAxisOverflowBit)  // discard packet if either overflow, https://wiki.osdev.org/Mouse_Input#Format_of_First_3_Packet_Bytes
		{
			return;
		}
		int x = mousePacket->movementX;
		int y = mousePacket->movementY;
		if(mousePacket->xAxisSignBit)
		{
			x -= UNSIGNED_CHAR_TOTAL_VALUES;
		}
		if(mousePacket->yAxisSignBit)
		{
			y -= UNSIGNED_CHAR_TOTAL_VALUES;
		}
		if(Math::abs(x) > TOO_LARGE || Math::abs(y) > TOO_LARGE)
		{
			System::getSystem().getLogger().log(LogType::WARNING, "Received cursor packet with high values: %d, %d (Packet Info: movementX=%d movementY=%d, status byte=%d)", x, y, static_cast<int>(mousePacket->movementX), static_cast<int>(mousePacket->movementY), static_cast<int>(this->_mousePacket[0]));
			return; // packet x y are too big so are ignored
		}
		GraphicsManager& graphicsManager = System::getSystem().getGraphicsManager();
		graphicsManager.getCursor().moveBy(x, -y);
		graphicsManager.getEventManager().queueEvent(Event(EventType::MOUSE_MOVE, EventCondition::MOUSE_HOVER));

		if(this->updateButtonState(EventType::LEFT_CLICK, mousePacket->buttonLeft, this->_mouseLeftDown))
		{
			unsigned long long currentTime = System::getSystem().getPIT().getCurrentTime();
			if(this->_lastClick + TIME_FOR_DOUBLE_CLICK > currentTime)
			{
				graphicsManager.getEventManager().queueEvent(Event(EventType::DOUBLE_CLICK, EventCondition::MOUSE_HOVER));
				this->_lastClick = 0;  // reset last click so u have to double click again to get a double click event
			} else
			{
				this->_lastClick = currentTime;
			}
			graphicsManager.getFocusManager().queueFocusUpdate();
		}
		this->updateButtonState(EventType::RIGHT_CLICK, mousePacket->buttonRight, this->_mouseRightDown);
		this->updateButtonState(EventType::MIDDLE_CLICK, mousePacket->buttonMiddle, this->_mouseMiddleDown);
	}
}

bool Mouse::updateButtonState(EventType eventType, bool active, bool& downState)
{
	if(active != downState)
	{
		downState = active;
		if(downState)
		{
			System::getSystem().getGraphicsManager().getEventManager().queueEvent(Event(eventType, EventCondition::MOUSE_HOVER));
			return true;
		}
	}
	return false;
}
