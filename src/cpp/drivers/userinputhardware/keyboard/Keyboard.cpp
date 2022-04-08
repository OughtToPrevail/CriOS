#include "Keyboard.h"
#include "System.h"

#define KEY_RELEASE 0x80

Keyboard::Keyboard(UserInputHardware& userInputHardware) : _userInputHardware(userInputHardware), _currentState()
{
	userInputHardware.setKeyboardCallback(Keyboard::alertKeyEvent);
}

void Keyboard::alertKeyInterrupt()
{
	this->_userInputHardware.read();
}

void Keyboard::alertKeyEvent(unsigned char scanCode)
{
	System::getSystem().getKeyboard().handleKeyEvent(scanCode);
}

void Keyboard::handleKeyEvent(unsigned char scanCode)
{
	KeyboardEvent event = toEvent(scanCode);
	const KeyCode& keyCode = event.keyboardKey.applyCondition(this->_currentState);
	const char* name = keyCode.getName();
	System::getSystem().getLogger().log(LogType::INFO, "Keyboard key: %s", name);

	KeyboardState& state = this->_currentState;
	if(event.eventType == KeyboardEventType::PRESSED)
	{
		if(keyCode == KeyCode::CAPS_LOCK)
		{
			state.capsLockActive = !state.capsLockActive;
		} else if(keyCode == KeyCode::NUM_LOCK)
		{
			state.numLockActive = !state.numLockActive;
		} else if(keyCode == KeyCode::LEFT_SHIFT || keyCode == KeyCode::RIGHT_SHIFT)
		{
			state.shiftActive = true;
		}
	}

	if(event.eventType == KeyboardEventType::RELEASED && (keyCode == KeyCode::LEFT_SHIFT ||
														  keyCode == KeyCode::RIGHT_SHIFT))
	{
		state.shiftActive = false;
	}

	if(event.eventType == KeyboardEventType::PRESSED)
	{
#ifdef GRAPHICS
		System::getSystem().getGraphicsManager().getEventManager().queueEvent(Event(EventType::KEYBOARD, EventCondition::FOCUSED));
#else
		System::getSystem().getShell().handleKeyPress(keyCode);
#endif
	}
}

KeyboardEvent Keyboard::toEvent(unsigned char scanCode)
{
	if(scanCode == 0)
	{
		return KeyboardEvent{KeyboardKey::NO_KEY, KeyboardEventType::ERROR};
	}
	KeyboardEventType eventType = KeyboardEventType::PRESSED;
	if(scanCode & KEY_RELEASE)
	{
		scanCode = scanCode & (0xFF ^ KEY_RELEASE);  // remove key release
		eventType = KeyboardEventType::RELEASED;
	}
	if(scanCode > KEYBOARD_KEYS_COUNT)
	{
		return KeyboardEvent{KeyboardKey::NO_KEY, KeyboardEventType::ERROR};
	}
	const KeyboardKey& key = KeyboardKey::fromScanCode(scanCode);
	return {key, eventType};
}
