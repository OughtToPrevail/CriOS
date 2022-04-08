#ifndef OSTEST_VAARGS_H
#define OSTEST_VAARGS_H


class VAArgs
{
public:
	explicit VAArgs(void* start, int size);

	template<class T>
	T nextArg();
private:
	char* _currentPosition;
};

template<class T>
T VAArgs::nextArg()
{
	T* val = reinterpret_cast<T*>(this->_currentPosition);
	this->_currentPosition += sizeof(T);
	return *val;
}

#endif //OSTEST_VAARGS_H
