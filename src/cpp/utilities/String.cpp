#include "String.h"
#include "VAArgs.h"

int String::strlen(const char* str)
{
	int len = 0;
	while(str[len] != '\0')
	{
		len++;
	}
	return len;
}

bool String::strcmp(const char* s1, const char* s2)
{
	return String::strcmp(s1, s2, String::strlen(s1), String::strlen(s2));
}

bool String::strcmp(const char* s1, const char* s2, unsigned int len1, unsigned int len2)
{
	if(len1 != len2)
	{
		return false;
	}
	for(unsigned int i = 0; i < len1; i++)
	{
		if(s1[i] != s2[i])
		{
			return false;
		}
	}
	return true;
}

unsigned int String::strcpy(char* dst, const char* src, unsigned int dstSize)
{
	unsigned int srcLen = String::strlen(src) + 1;
	unsigned int i;
	for(i = 0; i < dstSize && i < srcLen; i++)
	{
		dst[i] = src[i];
	}
	return i;
}

int String::insert(char* output, int index, int maxOutputSize, char input)
{
	if(index >= maxOutputSize)
	{
		return 0;
	}
	output[index] = input;
	return 1;
}

int String::insert(char* output, int index, int maxOutputSize, const char* input)
{
	int inputIndex = 0;
	int inputLength = String::strlen(input);
	for(; index < maxOutputSize && inputIndex < inputLength; index++, inputIndex++)
	{
		output[index] = input[inputIndex];
	}
	return inputIndex;
}

int String::insert(char* output, int index, int maxOutputSize, int input)
{
	int originalIndex = index;
	if(input < 0)
	{
		input = -input;
		String::insert(output, index++, maxOutputSize, '-');
	}
	int originalInput = input;
	int digits = 0;
	input /= 10;
	while(input > 0)
	{
		input /= 10;
		digits++;
	}
	input = originalInput;
	do  // loop even if 0 just once so it will show the first 0
	{
		String::insert(output, originalIndex + digits - (index - originalIndex), maxOutputSize, static_cast<char>('0' + input % 10));
		index++;
		input /= 10;
	} while(input > 0);
	return index - originalIndex;
}

#define PRINTF_SPECIAL_CHAR '%'
#define PRINTF_CHAR 'c'
#define PRINTF_STR 's'
#define PRINTF_INT 'd'

void String::sprintf(char* output, int maxOutputSize, const char* input, ...)
{
	VAArgs args(&input, sizeof(char*));

	String::sprintf(output, maxOutputSize, input, args);
}

void String::sprintf(char* output, int maxOutputSize, const char* input, VAArgs args)
{
	int outputIndex = 0;
	int length = String::strlen(input);
	bool lastSpecialChar = false;
	for(int i = 0; i < length; i++)
	{
		char c = input[i];
		if(lastSpecialChar)
		{
			switch(c)
			{
				case PRINTF_SPECIAL_CHAR:
					outputIndex += String::insert(output, outputIndex, maxOutputSize, PRINTF_SPECIAL_CHAR);
					break;
				case PRINTF_CHAR:
					outputIndex += String::insert(output, outputIndex, maxOutputSize, args.nextArg<char>());
					break;
				case PRINTF_STR:
					outputIndex += String::insert(output, outputIndex, maxOutputSize, args.nextArg<const char*>());
					break;
				case PRINTF_INT:
					outputIndex += String::insert(output, outputIndex, maxOutputSize, args.nextArg<int>());
					break;
				default:
					outputIndex += String::insert(output, outputIndex, maxOutputSize, '?');  // unknown
					break;
			}
			lastSpecialChar = false;
		} else if(c == PRINTF_SPECIAL_CHAR)
		{
			lastSpecialChar = true;
		} else
		{
			outputIndex += String::insert(output, outputIndex, maxOutputSize, c);
		}
	}
	if(outputIndex >= maxOutputSize)
	{
		outputIndex = maxOutputSize - 1;
	}
	output[outputIndex] = 0;
}
