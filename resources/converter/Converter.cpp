#include <iostream>
#include <fstream>
#include "ColorPalette.h"

struct TGAImageHeader
{
	unsigned char idLength;
	unsigned char colorMapType;
	unsigned char imageType;
	unsigned short firstColorMapEntry;
	unsigned short colorMapLength;
	unsigned char colorMapEntrySize;
	unsigned short xOrigin;
	unsigned short yOrigin;
	unsigned short imageWidth;
	unsigned short imageHeight;
	unsigned char pixelDepth;
	unsigned char imageDescriptor;
} __attribute__((packed));

struct TGAImagePixel
{
	unsigned char blue;
	unsigned char green;
	unsigned char red;
	unsigned char alpha;
};

int main(int argc, char* args[])  // remember first argument is always the command
{
	// Only supports 32 bit TGA with no compression
	if(argc != 3)
	{
		std::cout << "Must get two arguments: input file path and output file path" << std::endl;
		return 1;
	}
	char* input = args[1];
	char* output = args[2];

	std::cout << "File in: " << input << ", File out: " << output << std::endl;

	std::ifstream inputFile(input);

	inputFile.seekg(0, std::ios::end);
	int size = inputFile.tellg();
	inputFile.seekg(0, std::ios::beg);

	std::cout << "Converting " << size << " bytes..." << std::endl;

	char* buffer = new char[size];
	inputFile.read(buffer, size);

	TGAImageHeader* header = reinterpret_cast<TGAImageHeader*>(buffer);
	TGAImagePixel* imagePixels = reinterpret_cast<TGAImagePixel*>(buffer + sizeof(TGAImageHeader));

	char* outputBuffer = new char[sizeof(short) * 2 + (size - sizeof(TGAImageHeader)) / sizeof(TGAImagePixel)];
	unsigned short* outputIntBuffer = reinterpret_cast<unsigned short*>(outputBuffer);
	outputIntBuffer[0] = header->imageWidth;
	outputIntBuffer[1] = header->imageHeight;

	int outputBufferIndex = sizeof(short) * 2;

	for(int y = header->imageHeight - 1; y >= 0; y--)
	{
		for(int x = 0; x < header->imageWidth; x++)
		{
			int pixelIndex = y * header->imageWidth + x;
			TGAImagePixel pixel = imagePixels[pixelIndex];
			if(pixel.alpha == 0)
			{
				outputBuffer[outputBufferIndex++] = TRANSPARENT_INDEX;
				continue;
			}
			const VGAColor& color = ColorPalette::fitPalette(VGAColor(pixel.red >> 2, pixel.green >> 2, pixel.blue >> 2));
			outputBuffer[outputBufferIndex++] = color.getIndex();
		}
	}

	std::cout << "Writing to file..." << std::endl;

	std::ofstream outputFile(output);
	outputFile.write(outputBuffer, outputBufferIndex);
	outputFile.close();

	delete[] buffer;
	delete[] outputBuffer;

	std::cout << "Conversion complete" << std::endl;

	return 0;
}