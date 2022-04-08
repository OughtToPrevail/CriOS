#include "ImageView.h"

ImageView::ImageView() : _image(nullptr)
{
}

void ImageView::draw(Canvas& canvas) const
{
	Component::draw(canvas);
	canvas.drawImage(0, 0, *this->_image);
}

void ImageView::setImage(const OSImage& image)
{
	this->_image = &image;
	this->_invalidated = true;
}

void ImageView::recomputeDimensions()
{
	if(this->_image == nullptr)
	{
		this->_width = 0;
		this->_height = 0;
		return;
	}
	this->_width = this->_image->getWidth();
	this->_height = this->_image->getHeight();
	this->_invalidated = false;
}
