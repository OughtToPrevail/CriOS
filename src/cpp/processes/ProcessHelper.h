#ifndef CRIOS_PROCESSHELPER_H
#define CRIOS_PROCESSHELPER_H

#include "Process.h"


template<class T>
class ProcessHelper
{
public:
	static void copyArray(T* src, unsigned int srcSize, T* dst, unsigned int dstSize, unsigned int amountToCopy);//returns if copied successfully
	static void clearArray(T* arr, unsigned int sizeArray);
};


template<class T>
void ProcessHelper<T>::clearArray(T* arr, unsigned int sizeArray)
{
	for(unsigned int i = 0; i < sizeArray; i++)
	{
		arr[i] = 0;
	}
}


template<class T>
void ProcessHelper<T>::copyArray(T* src, unsigned int srcSize, T* dst, unsigned int dstSize, unsigned int amountToCopy)
{
	for(unsigned int i = 0; i < amountToCopy && i < srcSize && i < dstSize; i++)
	{
		dst[i] = src[i];
	}
}

#endif //CRIOS_PROCESSHELPER_H
