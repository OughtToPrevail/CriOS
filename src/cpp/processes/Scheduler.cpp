#include "Scheduler.h"
#include "schedulerHelper.h"
#include "System.h"
#include "ProcessHelper.h"
#include "MemoryManagement.h"

#define CONTEXT_SWITCH_EIP (1234567)

Scheduler::Scheduler()
		: _currentRunningProcessIndex(0), _kernelStack(0), _kernelStackSize(0), _firstChangeProcess(true)
{
}

void Scheduler::initKernel(unsigned int kernelStack, unsigned int kernelStackSize)
{
	this->_kernelStack = kernelStack;
	this->_kernelStackSize = kernelStackSize;
	unsigned int ebp = scheduler_getEBP();
	unsigned int esp = scheduler_getESP();
	unsigned int eip = scheduler_getEIP();
	if(eip == CONTEXT_SWITCH_EIP)
	{
		return;  // at this point, the kernel itself is a process
	}
	// register the kernel as a process
	this->addNewProcess(new Process(0, kernelStack, kernelStack, {ebp, esp, eip}));
	while(true);  // wait to be interrupted
}

/*Scheduler::~Scheduler()
{
	this->_allExistingProcesses.deleteVector();
}*/

void Scheduler::addNewProcess(Process* newProcess)
{
	this->_allExistingProcesses.pushBack(newProcess);

	Logger& logger = System::getSystem().getLogger();
	logger.log(LogType::INFO, "Added new process: %d", newProcess->getPID());
}

void Scheduler::removeProcess(int processIndex)
{
	unsigned int processPid = this->_allExistingProcesses[processIndex]->getPID();
	this->_allExistingProcesses.erase(processIndex);

	Logger& logger = System::getSystem().getLogger();
	logger.log(LogType::INFO, "Removed process: %d", processPid);
	Shell& shell = System::getSystem().getShell();
	shell.writeLineWithFormatting("      Removed process: %d", processPid);
}

void Scheduler::endProcess(unsigned int processID)
{
	asm volatile("cli");  // an interrupt while ending a process could cause the process to run while ending it
	bool isCurrent = getCurrentProcessPID() == processID;
	for(unsigned int i = 0; i < this->_allExistingProcesses.size(); i++)
	{
		if(processID == this->_allExistingProcesses[i]->getPID())
		{
			removeProcess((int) i);
			break;
		}
	}
	if(isCurrent)
	{
		this->_currentRunningProcessIndex = 0;
		this->_firstChangeProcess = true;
	}
	asm volatile("sti");
	if(isCurrent)
	{
		while(true);  // the process has ended, so it will just wait to be interrupted and replaced
	}
}

unsigned int Scheduler::getCurrentProcessPID()
{
	return this->_allExistingProcesses[this->_currentRunningProcessIndex]->getPID();
}

unsigned int Scheduler::getTotalProcesses()
{
	return this->_allExistingProcesses.size();
}

void Scheduler::changeProcess()
{
	if(this->_allExistingProcesses.empty())
	{
		return;
	}
	if(this->_firstChangeProcess)
	{
		this->_firstChangeProcess = false;
	} else
	{
		if(this->setNewProcessState((int) this->_currentRunningProcessIndex))
		{
			return;
		}
		this->_currentRunningProcessIndex++;
		if(this->_currentRunningProcessIndex >= this->_allExistingProcesses.size())
		{
			this->_currentRunningProcessIndex = 0;
		}
	}
	Process* currentProcess = this->_allExistingProcesses[this->_currentRunningProcessIndex];
	this->contextSwitch(currentProcess);
}


bool Scheduler::setNewProcessState(int processIndex)
{
	unsigned int ip = scheduler_getEIP();
	if(ip == CONTEXT_SWITCH_EIP)
	{
		return true;
	}
	ProcessState state = {scheduler_getEBP(), scheduler_getESP(), ip};
	this->_allExistingProcesses[processIndex]->setProcessState(state);
	return false;
}

unsigned int Scheduler::fork()
{
	/*
	 * Limitations: This fork currently only supports a fork inside the kernel and not another fork.
	 * To add support for this we'll have to copy the fork stack which we didn't have enough time to get around
	 * to implementing (although it wouldn't be too difficult)
	 */

	// Disable interrupts during fork to make sure nothing goes unexpected
	asm volatile("cli");

	unsigned int currentEsp = scheduler_getESP();
	unsigned int currentEbp = scheduler_getEBP();

	unsigned int stackMaxSize = this->_kernelStackSize;
	unsigned int stackDataSize = this->_kernelStack - currentEsp;
	unsigned int ebpDistance = currentEbp - currentEsp - 4;  // -4 to ignore extra getEBP on stack;

	unsigned char* newEsp = (unsigned char*) MemoryManagement::malloc(STACK_SIZE);
	newEsp += STACK_SIZE;  // stack always starts at the end

	unsigned int pid = Process::generateNewUniquePID();
	ProcessHelper<unsigned char>::copyArray((unsigned char*) currentEsp,
											stackMaxSize,
											newEsp - stackDataSize,
											STACK_SIZE,
											stackDataSize);

	unsigned int eip = scheduler_getEIP();
	if(eip == CONTEXT_SWITCH_EIP)
	{
		return pid;  // child process returning to its pid as the pid matches
	}
	unsigned int actualNewEsp = ((unsigned int) newEsp) - stackDataSize + 4;
	Process* newProcess = new Process(pid,
									  (unsigned int) newEsp,
									  STACK_SIZE,
									  ProcessState{actualNewEsp + ebpDistance, actualNewEsp, eip});
	this->addNewProcess(newProcess);
	asm volatile("sti");  // done forking, re-enable interrupts
	return pid;
}

void Scheduler::contextSwitch(Process* process)
{
	ProcessState processState = process->getProcessState();
	/*
	Logger& logger = System::getSystem().getLogger();
	logger.log(LogType::DEBUG, "I am %d", process->getPID());
	*/
	scheduler_contextSwitch(processState.instructionPointer, processState.esp, processState.ebp);
}
