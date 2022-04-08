#ifndef OSTEST_LABEL_H
#define OSTEST_LABEL_H

#include "Component.h"

class Label : public Component
{
public:
	Label();

	void draw(Canvas& canvas) const override;
	void recomputeDimensions() override;

	void setText(const char* text);
	void setForeground(const VGAColor& foreground);
private:
	const char* _text;
	VGAColor _foreground;
};


#endif //OSTEST_LABEL_H
