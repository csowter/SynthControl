#include "Button.h"
#include <cstdio>

cButton::cButton(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
	: cWidget(x, y, width, height), mColour(0xff0000ff)
{

}

void cButton::Render(SDL_Surface *surface)
{
	SDL_Surface *widgetSurface = SDL_CreateRGBSurface(0, mBoundingRectangle.w, mBoundingRectangle.h,
		32, 0xff000000, 0x00ff0000, 0x000000ff00, 0x000000ff);

	SDL_Rect Rect;
	Rect.x = 0;
	Rect.y = 0;
	Rect.w = mBoundingRectangle.w;
	Rect.h = mBoundingRectangle.h;

	SDL_FillRect(widgetSurface, &Rect, mColour);
	SDL_BlitSurface(widgetSurface, &Rect, surface, &mBoundingRectangle);

	SDL_FreeSurface(widgetSurface);
}

void cButton::MouseEvent(SDL_Event &e)
{
	uint32_t rgb = (mColour & 0xffffff00) >> 8;
	rgb >>= 1;
	mColour &= 0x000000ff;
	mColour |= (rgb << 8);

	printf("ButtonPress\r\n");
}

