#include "CPPSupport.h"
#include "System.h"
#include "InterruptTable.h"
#include "GDTLoader.h"
#include "Memory.h"
#include "MemoryManagement.h"
#include "Usermode.h"
#include "TSSManager.h"
#include "Multiboot.h"
#include "DirIterator.h"
#include "String.h"

#define WAIT_BETWEEN_FEATURES (3000)
#define WAIT_BETWEEN_MINOR (500)
#define BUFFER_SIZE (255)

void printPreInitializedFeatures();
void welcomeShell();
void testLogger();
void testTextMode();
void testGraphicsMode();
void testVFS();
void testScheduler();


extern "C"
{
	int criosMain(Multiboot* multiboot, unsigned int stackStart, unsigned int stackSize)
	{
		ModuleEntry initrdFSEntry = MultibootUtility::getModule(multiboot, 0);
		// Paging must be initialized first
		static IdentityPaging paging;
		paging.enablePaging();
		MemoryManagement::initHeap();

		System& system = System::getSystem();
		system.getUserInterruptHardware().enablePSInterrupts(); // do it before interrupts are actually set up
#ifdef GRAPHICS
		Mouse& mouse = system.getMouse();
		mouse.enableMouse();
#endif
		unsigned short cs = GDTLoader::loadGDT();
		InterruptTable::registerInterrupts(cs);

		welcomeShell();
		printPreInitializedFeatures();
		testLogger();

		system.createVFS(initrdFSEntry);
		testVFS();

		system.getScheduler().initKernel(stackStart, stackSize);
		testScheduler();

		TSSManager::setKernelStack((unsigned int) MemoryManagement::malloc(4096));
		Usermode::jumpIntoUsermode();
		// now in user mode
		system.getLogger().log(LogType::INFO, "Now in user mode! Can I still log?");
		system.getShell().writeLine("\nEntering User Mode...\n      Now in user mode!\n\n");

#ifdef GRAPHICS
		testGraphicsMode();
#else
		testTextMode();
#endif
		return 0;
	}
}


void welcomeShell()
{
	Shell& shell = System::getSystem().getShell();

	shell.writeLine("\n"
					"                                                 ,---. \n"
					",--.   ,--.      ,--.                            |   | \n"
					"|  |   |  |,---. |  |,---. ,---. ,--,--,--.,---. |  .' \n"
					"|  |.'.|  | .-. :|  | .--'| .-. ||        | .-. :|  |  \n"
					"|   ,'.   |  `--.|  | `--.' '-' '|  |  |  |  `--.`--'  \n"
					"'--'   '--'`----'`--'`---' `---' `--`--`--'`----'.--.  \n"
					",--------.                                       '--'  \n"
					"'--.  .--',---.                                        \n"
					"   |  |  | .-. |                                       \n"
					"   |  |  ' '-' '                                       \n"
					"   `--'   `---'                                        \n"
					" ,-----.       ,--. ,-----.  ,---.                     \n"
					"'  .--.|,--.--.`--''  .-.  ''   .-'                    \n"
					"|  |    |  .--',--.|  | |  |`.  `-.                    \n"
					"'  '--'||  |   |  |'  '-'  '.-'    |                   \n"
					" `-----'`--'   `--' `-----' `-----'                    \n"
					"                                                       ");
	System::getSystem().getPIT().wait(2000);
}


void printPreInitializedFeatures()
{
	Shell& shell = System::getSystem().getShell();
	shell.writeLine("\n\nInstalling Virtual Memory - paging and heap...");

	ProgrammableIntervalTimer& timer = System::getSystem().getPIT();
	timer.wait(WAIT_BETWEEN_MINOR);
	shell.writeLine("\n\nInstalling GDT - Global Descriptor Table...");
	timer.wait(WAIT_BETWEEN_MINOR);
	shell.writeLine("\n\nInstalling IDT - Interrupt Descriptor Table...");

	timer.wait(WAIT_BETWEEN_MINOR);
	shell.writeLine("\n\nUsing PIT waiting for 3 seconds");

	timer.wait(WAIT_BETWEEN_FEATURES);
}

void testLogger()
{
	System& system = System::getSystem();
	Logger& logger = system.getLogger();
	Shell& shell = system.getShell();

	logger.log(LogType::INFO, "Test log");
	logger.log(LogType::DEBUG, "Debug log");
	logger.log(LogType::ERROR, "Error!");
	logger.log(LogType::ERROR, "Error because of %d and %s and %c wooow", 5, "this as well", 'o');
	logger.log(LogType::WARNING, "Size of long is: %d", sizeof(long long));
	logger.log(LogType::INFO, "Process is %s", Memory::isBigEndian() ? "big endian" : "little endian");
	int x = 987654321;
	logger.log(LogType::DEBUG, "Looooooong int: %d", x);

	shell.writeLine("\n\nTesting Log...");
	shell.writeLine("      Check out your console log to see the results!");

	System::getSystem().getPIT().wait(WAIT_BETWEEN_FEATURES);
}

void testScheduler()
{
	System& system = System::getSystem();
	Shell& shell = system.getShell();
	Scheduler& myScheduler = system.getScheduler();
	shell.writeLine("\nTesting Scheduler...");
	unsigned int processPID = myScheduler.fork();
	Logger& logger = system.getLogger();
	logger.log(LogType::INFO, "What is my pid before: %d", myScheduler.getCurrentProcessPID());
	// May be out of sync here so writing to the shell at the same time and causing it to be merged, so we're just waiting a second if it's PID 1
	system.getPIT().wait(myScheduler.getCurrentProcessPID() * 1000);
	shell.writeLineWithFormatting("      What is my pid before: %d", myScheduler.getCurrentProcessPID());
	system.getPIT().wait(WAIT_BETWEEN_FEATURES);  // let the fork run for 3 seconds to make sure context switches don't cause any errors
	logger.log(LogType::INFO, "What is my pid after: %d", myScheduler.getCurrentProcessPID());
	shell.writeLineWithFormatting("      What is my pid after: %d", myScheduler.getCurrentProcessPID());
	if(myScheduler.getCurrentProcessPID() == processPID)
	{
		myScheduler.endProcess(processPID);
	}
	while(myScheduler.getTotalProcesses() > 1);  // wait until process has ended to not enter into user mode yet

	System::getSystem().getPIT().wait(WAIT_BETWEEN_FEATURES);
}

void testVFS()
{
	System& system = System::getSystem();
	Shell& shell = system.getShell();
	VFS* vfs = system.getVFS();
	(void) vfs;
	DirIterator iterator = vfs->listdir("/");
	shell.writeLine("\n\nTesting File System...");
	while(iterator.hasNext())
	{
		const char* name = iterator.next();
		char filePath[BUFFER_SIZE];
		String::sprintf(filePath, BUFFER_SIZE, "%s/%s", "/root", name);
		File* file = vfs->open(filePath, FileOpenMode::READ);
		char buffer[BUFFER_SIZE];
		unsigned int total = file->read(buffer, BUFFER_SIZE);
		buffer[total] = 0;
		system.getLogger().log(LogType::INFO, "File Content in %s: %s", name, buffer);
		shell.writeLineWithFormatting("      File Content in %s: %s", name, buffer);
	}

	System::getSystem().getPIT().wait(WAIT_BETWEEN_FEATURES);
}

void testTextMode()
{
	System& system = System::getSystem();
	Shell& shell = system.getShell();
	shell.writeLine("CriOS Shell");
	shell.writeString("> ");

	while(true);
}

void testGraphicsMode()
{
	System& system = System::getSystem();
	system.getGraphicsManager().enable();
	ProgrammableIntervalTimer& timer = system.getPIT();
	while(true)
	{
		system.getGraphicsManager().update();
		timer.wait(10);
	}
}