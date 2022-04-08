#include "Process.h"
#include "ProcessHelper.h"
#include "MemoryManagement.h"
#include "System.h"

Process::Process(unsigned int pid, unsigned int stack, unsigned int stackSize, ProcessState newProcessState)
		: _pID(pid), _stack(stack), _stackSize(stackSize),
		  _processState(newProcessState)
{
}

unsigned int Process::getPID()
{
	return this->_pID;
}

Process::~Process()
{
	unsigned int* espPtr = (unsigned int*) (this->_processState.esp);
	ProcessHelper<unsigned int>::clearArray(espPtr, this->_stackSize);
	free(espPtr);
	//remove process from scheduler
}

void Process::setProcessState(ProcessState newProcessState)
{
	this->_processState = newProcessState;
}

ProcessState Process::getProcessState()
{
	return this->_processState;
}

unsigned int Process::getStack() const
{
	return this->_stack;
}

unsigned int Process::getStackSize() const
{
	return this->_stackSize;
}

unsigned int Process::generateNewUniquePID()
{
	static unsigned int pIDCounter = 0;
	pIDCounter++;
	return pIDCounter;
}
