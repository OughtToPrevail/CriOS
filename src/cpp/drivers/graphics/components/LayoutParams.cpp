#include "LayoutParams.h"

LayoutParams::LayoutParams(unsigned int margin) : _margin(margin)
{

}

unsigned int LayoutParams::getMargin() const
{
	return _margin;
}
