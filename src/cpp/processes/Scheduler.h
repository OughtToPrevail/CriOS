#ifndef CRIOS_SCHEDULER_H
#define CRIOS_SCHEDULER_H

#define MAX_AMOUNT_OF_PROCESSES_RUNNING_SIMULTANEOUSLY 100

#include "Process.h"
#include "Vector.h"

class Scheduler
{
public:
	Scheduler();
	~Scheduler() = default;

	void changeProcess();
	void contextSwitch(Process* process);
	unsigned int fork();
	void endProcess(unsigned int processID);
	unsigned int getCurrentProcessPID();
	unsigned int getTotalProcesses();

	void initKernel(unsigned int kernelStack, unsigned int kernelStackSize);

private:
	Vector<Process*> _allExistingProcesses;
	unsigned int _currentRunningProcessIndex;
	unsigned int _kernelStack;
	unsigned int _kernelStackSize;
	bool _firstChangeProcess;

	bool setNewProcessState(int processIndex);
	void addNewProcess(Process* newProcess);
	void removeProcess(int processIndex);
};

#endif //CRIOS_SCHEDULER_H
