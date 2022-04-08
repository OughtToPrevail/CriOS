#include <BasicIOPort.h>
#include "UserInputHardware.h"

// https://wiki.osdev.org/%228042%22_PS/2_Controller#PS.2F2_Controller_Commands
#define ENABLE_MOUSE_DEVICE 0xA8
#define CONFIGURE_COMMAND 0x60
// https://wiki.osdev.org/%228042%22_PS/2_Controller#PS.2F2_Controller_Configuration_Byte
#define CONFIGURATION_COMMAND 0b01000011

#define MOUSE_COMMAND 0xD4

UserInputHardware::UserInputHardware() : _dataPort(0x60), _commandPort(0x64), _keyboardCallback(nullptr), _mouseCallback(nullptr)
{

}

void UserInputHardware::setKeyboardCallback(Callback callback)
{
	this->_keyboardCallback = callback;
}

void UserInputHardware::setMouseCallback(Callback callback)
{
	this->_mouseCallback = callback;
}

void UserInputHardware::enablePSInterrupts()
{
	this->_commandPort.write(ENABLE_MOUSE_DEVICE);

	this->_commandPort.write(CONFIGURE_COMMAND);
	this->_dataPort.write(CONFIGURATION_COMMAND);
}

void UserInputHardware::writeMouse(unsigned char val)
{
	this->_commandPort.write(MOUSE_COMMAND);
	this->_dataPort.write(val);
	this->readValue();  // read acknowledgment and ignore it
}

void UserInputHardware::read()
{
	UserInputValue data = this->readValue();
	if(data.status.keyboardOrMouse == KEYBOARD_DATA)
	{
		this->_keyboardCallback(data.value);
	} else if(data.status.keyboardOrMouse == MOUSE_DATA)
	{
		this->_mouseCallback(data.value);
	}
}

UserInputValue UserInputHardware::readValue()
{
	while(true)
	{
		unsigned char commandData = this->_commandPort.read();
		UserInputStatus* status = reinterpret_cast<UserInputStatus*>(&commandData);
		if(status->outputBufferStatus != STATUS_EMPTY)
		{
			unsigned char data = this->_dataPort.read();
			return {*status, data};
		}
	}
}

