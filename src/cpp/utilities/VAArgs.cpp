#include "VAArgs.h"

VAArgs::VAArgs(void* start, int size) : _currentPosition(reinterpret_cast<char*>(start) + size)
{

}