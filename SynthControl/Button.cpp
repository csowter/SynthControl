#include "Button.h"
#include <cstdio>

cButton::cButton(SDL_Renderer *renderer, uint32_t x, uint32_t y, uint32_t width, uint32_t height, void(*eventHandler)(SDL_Event &e))
	: cWidget(x, y, width, height), mEventHandler(eventHandler)
{
	SDL_Surface *Surface = SDL_CreateRGBSurface(0, mBoundingRectangle.w, mBoundingRectangle.h,
		32, 0xff000000, 0x00ff0000, 0x000000ff00, 0x000000ff);

	mPressedTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, width, height);
	mUnpressedTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, width, height);

	SDL_Rect Rect;
	Rect.x = 0;
	Rect.y = 0;
	Rect.w = mBoundingRectangle.w;
	Rect.h = mBoundingRectangle.h;

	SDL_FillRect(Surface, &Rect, 0xFF0000FF);
	mUnpressedTexture = SDL_CreateTextureFromSurface(renderer, Surface);
	SDL_FillRect(Surface, &Rect, 0x00FF00FF);
	mPressedTexture = SDL_CreateTextureFromSurface(renderer, Surface);

	SDL_FreeSurface(Surface);
}

cButton::~cButton()
{

}

void cButton::Render(SDL_Renderer *renderer)
{
	SDL_Texture *texture = mPressed ? mPressedTexture : mUnpressedTexture;
	SDL_RenderCopy(renderer, texture, NULL, &mBoundingRectangle);
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

	SDL_Surface *Surface = SDL_CreateRGBSurface(0, mBoundingRectangle.w, mBoundingRectangle.h,
		32, 0xff000000, 0x00ff0000, 0x000000ff00, 0x000000ff);
	uint32_t colour = 0xFF0000FF;
	SDL_FillRect(Surface, &Rect, colour);
	SDL_BlitSurface(Surface, &Rect, surface, &mBoundingRectangle);
	SDL_FreeSurface(Surface);
}

void cButton::MouseDown(SDL_Event &e)
{
	int x, y;
	SDL_GetMouseState(&x, &y);

	if(ContainsPoint(x, y))
	{
		mPressed = true;
		if(mEventHandler != nullptr)
			mEventHandler(e);
	}
}

void cButton::MouseUp(SDL_Event &)
{
	mPressed = false;
}

