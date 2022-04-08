#include "PCFFont.h"
#include "Memory.h"
#include "Math.h"
#include "String.h"

// https://fontforge.org/docs/techref/pcf-format.html

#define HEADER_LENGTH 4
#define PCF_METRICS (1<<2)
#define PCF_BITMAPS (1 << 3)
#define PCF_BDF_ENCODINGS (1 << 5)
#define PCF_BYTE_MASK (1 << 2)
#define PCF_GLYPH_PAD_MASK 3
#define PCF_COMPRESSED_METRICS 0x00000100
#define COMPRESSED_OFFSET 0x80

#define NO_PADDING 0
#define SHORT_PADDING 1
#define INT_PADDING 2

#define BITMAP_SIZES_COUNT 4
#define BITS_PER_BYTE 8

PCFFont::PCFFont(unsigned char* address) : _bitmapOffsets(nullptr), _bitmaps(nullptr), _bitmapPadding(0), _bitMapBigEndian(false), _glpyhIndices(nullptr), _glpyhIndicesBigEndian(false), _metricsCompressed(false), _metricsBigEndian(false), _unCompressedMetrics(nullptr), _compressedMetrics(nullptr)
{
	unsigned int* intAddress = reinterpret_cast<unsigned int*>(address + HEADER_LENGTH);

	unsigned int tableCount = Memory::ensureLittleEndian(*intAddress);
	TOCEntry* tocEntries = reinterpret_cast<TOCEntry*>(intAddress + 1);
	for(unsigned int i = 0; i < tableCount; i++)
	{
		TOCEntry& entry = tocEntries[i];
		unsigned int type = Memory::ensureLittleEndian<unsigned int>(entry.type);
		unsigned char* tableAddress = address + Memory::ensureLittleEndian<unsigned int>(entry.offset);
		unsigned int* intTableAddress = reinterpret_cast<unsigned int*>(tableAddress);
		unsigned int format = Memory::ensureLittleEndian<unsigned int>(*intTableAddress);
		intTableAddress++;
		bool bigEndian = format & PCF_BYTE_MASK;
		if(type & PCF_BITMAPS)
		{
			parseBitmapTable(intTableAddress, format, bigEndian);
		} else if(type & PCF_BDF_ENCODINGS)
		{
			parseEncodings(intTableAddress, bigEndian);
		} else if(type & PCF_METRICS)
		{
			parseMetrics(intTableAddress, format, bigEndian);
		}
	}
}

void PCFFont::parseBitmapTable(unsigned int* address, unsigned int format, bool bigEndian)
{
	unsigned int glyphCount = Memory::ensureEndian<unsigned int>(*address, bigEndian);
	address++;
	this->_bitmapOffsets = address;
	this->_bitmaps = reinterpret_cast<unsigned char*>(this->_bitmapOffsets + glyphCount + BITMAP_SIZES_COUNT);
	switch(format & PCF_GLYPH_PAD_MASK)
	{
		case NO_PADDING:
			this->_bitmapPadding = 0;
			break;
		case SHORT_PADDING:
			this->_bitmapPadding = sizeof(short);
			break;
		case INT_PADDING:
			this->_bitmapPadding = sizeof(int);
			break;
	}
	this->_bitMapBigEndian = bigEndian;
}

void PCFFont::parseEncodings(unsigned int* address, bool bigEndian)
{
	short* shortAddress = reinterpret_cast<short*>(address);
	shortAddress += 5;  // skip XFontStruct values
	this->_glpyhIndices = shortAddress;
	this->_glpyhIndicesBigEndian = bigEndian;
}

void PCFFont::parseMetrics(unsigned int* address, unsigned int format, bool bigEndian)
{
	this->_metricsCompressed = format & PCF_COMPRESSED_METRICS;
	unsigned short* currAddress = reinterpret_cast<unsigned short*>(address) + 1; // skip metrics count
	if(this->_metricsCompressed)
	{
		this->_compressedMetrics = reinterpret_cast<CompressedMetrics*>(currAddress);
	} else
	{
		this->_unCompressedMetrics = reinterpret_cast<UncompressedMetrics*>(currAddress);
	}
	this->_metricsBigEndian = bigEndian;
}

PCFCharacter PCFFont::getCharacter(unsigned char c) const
{
	short glyphIndex = Memory::ensureEndian<short>(this->_glpyhIndices[c], this->_glpyhIndicesBigEndian);
	unsigned int offset = Memory::ensureEndian<unsigned int>(this->_bitmapOffsets[glyphIndex], this->_bitMapBigEndian);
	PCFCharacter character{};
	character.bitmap = this->_bitmaps + offset;
	if(this->_metricsCompressed)
	{
		CompressedMetrics& metrics = this->_compressedMetrics[glyphIndex];
		character.width = metrics.characterWidth - COMPRESSED_OFFSET;
		character.ascent = metrics.characterAscent - COMPRESSED_OFFSET;
		character.descent = metrics.characterDescent - COMPRESSED_OFFSET;
	} else
	{
		UncompressedMetrics& metrics = this->_unCompressedMetrics[glyphIndex];
		character.width = Memory::ensureEndian<short>(metrics.characterWidth, this->_metricsBigEndian);
		character.ascent = Memory::ensureEndian<short>(metrics.characterAscent, this->_metricsBigEndian);
		character.descent = Memory::ensureEndian<short>(metrics.characterDescent, this->_metricsBigEndian);
	}
	if(character.width < BITS_PER_BYTE)
	{
		character.bytesPerPixelLine = Math::max<unsigned char>(this->_bitmapPadding, 1);
	} else
	{
		character.bytesPerPixelLine = character.width / BITS_PER_BYTE + this->_bitmapPadding;
	}
	return character;
}

TextDimensions PCFFont::measureText(const char* text) const
{
	int stringLength = String::strlen(text);
	TextDimensions dimensions{};
	for(int i = 0; i < stringLength; i++)
	{
		PCFCharacter character = this->getCharacter(text[i]);
		dimensions.width += character.width;
		dimensions.height = Math::max<unsigned int>(dimensions.height, character.descent + character.ascent);
	}
	return dimensions;
}

bool PCFCharacter::isPixelColored(unsigned char x, unsigned char y) const
{
	return this->bitmap[this->bytesPerPixelLine * y + x / BITS_PER_BYTE] & PixelMask[x % BITS_PER_BYTE];
}
