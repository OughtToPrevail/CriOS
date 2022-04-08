#ifndef OSTEST_SYSTEM_H
#define OSTEST_SYSTEM_H

#include "FrameBuffer.h"
#include "TextCursor.h"
#include "Keyboard.h"
#include "Logger.h"
#include "GraphicsManager.h"
#include "Mouse.h"
#include "ProgrammableIntervalTimer.h"
#include "Shell.h"
#include "IdentityPaging.h"
#include "VFS.h"
#include "InitrdFS.h"
#include "Multiboot.h"
#include "Scheduler.h"

class System
{
public:
	static System& getSystem()
	{
		static System instance;

		return instance;
	}

	FrameBuffer& getFrameBuffer();
	TextCursor& getTextCursor();
	UserInputHardware& getUserInterruptHardware();
	Keyboard& getKeyboard();
	Mouse& getMouse();
	GraphicsManager& getGraphicsManager();
	Shell& getShell();
	Logger& getLogger();
	ProgrammableIntervalTimer& getPIT();
	Scheduler& getScheduler();

	void createVFS(ModuleEntry entry);
	VFS* getVFS();

	static void halt();
private:
	System();

	FrameBuffer _frameBuffer;
	TextCursor _textCursor;
	UserInputHardware _userInputHardware;
	Keyboard _keyboard;
	Mouse _mouse;
	GraphicsManager _graphicsManager;
	Shell _shell;
	Logger _logger;
	ProgrammableIntervalTimer _timer;
	Scheduler _scheduler;
	VFS* _vfs;
	InitrdFS* _initrdFs;
};


#endif //OSTEST_SYSTEM_H
