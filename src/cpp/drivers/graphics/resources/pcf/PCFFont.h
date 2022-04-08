#ifndef OSTEST_PCFFONT_H
#define OSTEST_PCFFONT_H

// mask whether a pixel is active or not in the font line
static const unsigned char PixelMask[] = {
	1 << 7,
	1 << 6,
	1 << 5,
	1 << 4,
	1 << 3,
	1 << 2,
	1 << 1,
	1 << 0
};

struct TOCEntry
{
	unsigned int type;
	unsigned int format;
	unsigned int size;
	unsigned int offset;
} __attribute__((packed));

struct PCFCharacter
{
	unsigned char* bitmap;
	unsigned short width;
	unsigned short ascent;
	unsigned short descent;
	unsigned int bytesPerPixelLine;

	bool isPixelColored(unsigned char x, unsigned char y) const;
};

struct CompressedMetrics
{
	unsigned char leftSidedBearing;
	unsigned char rightSidedBearing;
	unsigned char characterWidth;
	unsigned char characterAscent;
	unsigned char characterDescent;
} __attribute__((packed));

struct UncompressedMetrics
{
	short leftSidedBearing;
	short rightSidedBearing;
	short characterWidth;
	short characterAscent;
	short characterDescent;
	unsigned short characterAttributes;
} __attribute__((packed));

struct TextDimensions
{
	unsigned int width;
	unsigned int height;
};

class PCFFont
{
public:
	explicit PCFFont(unsigned char* address);

	PCFCharacter getCharacter(unsigned char c) const;

	TextDimensions measureText(const char* text) const;
private:
	void parseBitmapTable(unsigned int* address, unsigned int format, bool bigEndian);
	void parseEncodings(unsigned int* address, bool bigEndian);
	void parseMetrics(unsigned int* address, unsigned int format, bool bigEndian);

	unsigned int* _bitmapOffsets;
	unsigned char* _bitmaps;
	unsigned char _bitmapPadding;
	bool _bitMapBigEndian;
	short* _glpyhIndices;
	bool _glpyhIndicesBigEndian;
	bool _metricsCompressed;
	bool _metricsBigEndian;
	UncompressedMetrics* _unCompressedMetrics;
	CompressedMetrics* _compressedMetrics;
};


#endif //OSTEST_PCFFONT_H
