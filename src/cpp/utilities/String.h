#ifndef OSTEST_STRING_H
#define OSTEST_STRING_H

#include "VAArgs.h"

class String
{
public:
	static int strlen(const char* str);
	static bool strcmp(const char* s1, const char* s2);
	static bool strcmp(const char* s1, const char* s2, unsigned int len1, unsigned int len2);
	static unsigned int strcpy(char dst[], const char src[], unsigned int dstSize);
	static int insert(char* output, int index, int maxOutputSize, char input);
	static int insert(char* output, int index, int maxOutputSize, const char* input);
	static int insert(char* output, int index, int maxOutputSize, int input);
	static void sprintf(char* output, int maxOutputSize, const char* input, ...);
	static void sprintf(char* output, int maxOutputSize, const char* input, VAArgs args);
};


#endif //OSTEST_STRING_H
