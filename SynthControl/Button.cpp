#include "Button.h"
#include <cstdio>

cButton::cButton(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
	: cWidget(x, y, width, height), mColour(0xff0000ff)
{
	mSurface = SDL_CreateRGBSurface(0, mBoundingRectangle.w, mBoundingRectangle.h,
		32, 0xff000000, 0x00ff0000, 0x000000ff00, 0x000000ff);
}

cButton::~cButton()
{
	SDL_FreeSurface(mSurface);
}

void cButton::Render(SDL_Surface *surface)
{
	if(!mVisible)
		return;

	SDL_Rect Rect;
	Rect.x = 0;
	Rect.y = 0;
	Rect.w = mBoundingRectangle.w;
	Rect.h = mBoundingRectangle.h;

	SDL_FillRect(mSurface, &Rect, mColour);
	SDL_BlitSurface(mSurface, &Rect, surface, &mBoundingRectangle);
}

void cButton::MouseDown(SDL_Event &)
{
	int x, y;
	SDL_GetMouseState(&x, &y);

	if(ContainsPoint(x, y))
		mColour = 0x00FF00FF; 
}

void cButton::MouseUp(SDL_Event &)
{
	mColour = 0xFF0000FF;
}
