#ifndef CRIOS_PROCESS_H
#define CRIOS_PROCESS_H

#define STACK_SIZE (16384)


struct ProcessState
{
	unsigned int ebp;
	unsigned int esp;
	unsigned int instructionPointer; //eip
};

class Process
{
public:
	Process(unsigned int pid, unsigned int stack, unsigned int stackSize, ProcessState newProcessState);
	~Process();

	ProcessState getProcessState();
	void setProcessState(ProcessState newProcessState);
	unsigned int getStack() const;
	unsigned int getStackSize() const;

	unsigned int getPID();

	static unsigned int generateNewUniquePID();
private:
	//process ID
	unsigned int _pID;
	unsigned int _stack;
	unsigned int _stackSize;
	ProcessState _processState;
};


#endif //CRIOS_PROCESS_H
