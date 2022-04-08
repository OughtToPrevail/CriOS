#include "System.h"
#include "Halt.h"
#include "InitrdFS.h"

System::System() : _keyboard(this->_userInputHardware), _mouse(this->_userInputHardware), _vfs(nullptr)
{

}

Scheduler& System::getScheduler()
{
	return System::_scheduler;
}

FrameBuffer& System::getFrameBuffer()
{
	return this->_frameBuffer;
}

TextCursor& System::getTextCursor()
{
	return this->_textCursor;
}

UserInputHardware& System::getUserInterruptHardware()
{
	return this->_userInputHardware;
}

Keyboard& System::getKeyboard()
{
	return this->_keyboard;
}

Mouse& System::getMouse()
{
	return this->_mouse;
}

GraphicsManager& System::getGraphicsManager()
{
	return this->_graphicsManager;
}

Shell& System::getShell()
{
	return this->_shell;
}

Logger& System::getLogger()
{
	return this->_logger;
}

ProgrammableIntervalTimer& System::getPIT()
{
	return this->_timer;
}

void System::createVFS(ModuleEntry entry)
{
	this->_initrdFs = new InitrdFS(entry);
	this->_vfs = new VFS(this->_initrdFs);
}

VFS* System::getVFS()
{
	return this->_vfs;
}

void System::halt()
{
	Halt_callHalt();
}

