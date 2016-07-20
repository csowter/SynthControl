#include "Widget.h"

cWidget::cWidget(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
{
	mBoundingRectangle.x = x;
	mBoundingRectangle.y = y;
	mBoundingRectangle.w = width;
	mBoundingRectangle.h = height;
}

bool cWidget::ContainsPoint(uint32_t x, uint32_t y)
{
	return (x >= mBoundingRectangle.x && x < mBoundingRectangle.x + mBoundingRectangle.w) && (y >= mBoundingRectangle.y && y < mBoundingRectangle.y + mBoundingRectangle.h);
}