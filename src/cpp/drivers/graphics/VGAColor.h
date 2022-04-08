#ifndef OSTEST_VGACOLOR_H
#define OSTEST_VGACOLOR_H

#define OUT_OF_TABLE -1

class VGAColor  // should be supplied as 6 bit
{
public:
	VGAColor();
	VGAColor(unsigned char red, unsigned char green, unsigned char blue);
	VGAColor(unsigned char index, unsigned char red, unsigned char green, unsigned char blue);

	int getIndex() const;
	unsigned char getRed() const;
	unsigned char getGreen() const;
	unsigned char getBlue() const;

	int distance(const VGAColor& other) const;

	bool operator==(const VGAColor& rhs) const;
	bool operator!=(const VGAColor& rhs) const;

	static VGAColor from8Bit(unsigned char red, unsigned char green, unsigned blue);
private:
	unsigned int _index;
	unsigned char _red;
	unsigned char _green;
	unsigned char _blue;
};



#endif //OSTEST_VGACOLOR_H
