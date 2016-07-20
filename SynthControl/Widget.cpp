#include "Widget.h"

cWidget::cWidget(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
{
	mBoundingRectangle.x = x;
	mBoundingRectangle.y = y;
	mBoundingRectangle.w = width;
	mBoundingRectangle.h = height;
}

void cWidget::Render(SDL_Surface *surface)
{
	SDL_Surface *widgetSurface = SDL_CreateRGBSurface(0, mBoundingRectangle.w, mBoundingRectangle.h,
		32, 0xff000000, 0x00ff0000, 0x000000ff00, 0x000000ff);
	
	SDL_Rect Rect;
	Rect.x = 0;
	Rect.y = 0;
	Rect.w = mBoundingRectangle.w;
	Rect.h = mBoundingRectangle.h;

	SDL_FillRect(widgetSurface, &Rect, 0xff0000ff);

	SDL_BlitSurface(widgetSurface, &Rect, surface, &mBoundingRectangle);

	SDL_FreeSurface(widgetSurface);
}