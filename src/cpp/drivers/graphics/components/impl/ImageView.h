#ifndef OSTEST_IMAGEVIEW_H
#define OSTEST_IMAGEVIEW_H

#include "Component.h"

class ImageView : public Component
{
public:
	ImageView();

	void draw(Canvas &canvas) const override;

	void setImage(const OSImage& image);

	void recomputeDimensions() override;
private:
	const OSImage* _image;
};


#endif //OSTEST_IMAGEVIEW_H
