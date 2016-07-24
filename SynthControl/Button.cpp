#include "Button.h"
#include <cstdio>

cButton::cButton(SDL_Renderer *renderer, uint32_t x, uint32_t y, uint32_t width, uint32_t height, void(*eventHandler)(SDL_Event &e))
	: cWidget(x, y, width, height), mEventHandler(eventHandler)
{
	SDL_Rect Rect;
	Rect.x = 0;
	Rect.y = 0;
	Rect.w = mBoundingRectangle.w;
	Rect.h = mBoundingRectangle.h;

	mUnpressedTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, width, height);
	mPressedTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, width, height);

	SDL_SetRenderTarget(renderer, mUnpressedTexture);
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderFillRect(renderer, &Rect);

	SDL_SetRenderTarget(renderer, mPressedTexture);
	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
	SDL_RenderFillRect(renderer, &Rect);

	SDL_SetRenderTarget(renderer, NULL);
}

cButton::~cButton()
{
	SDL_DestroyTexture(mPressedTexture);
	SDL_DestroyTexture(mUnpressedTexture);
}

void cButton::Render(SDL_Renderer *renderer)
{
	if (!mVisible)
		return;
	SDL_Texture *texture = mPressed ? mPressedTexture : mUnpressedTexture;
	SDL_RenderCopy(renderer, texture, NULL, &mBoundingRectangle);
}

void cButton::MouseDown(SDL_Event &e)
{
	int x, y;
	SDL_GetMouseState(&x, &y);

	if(ContainsPoint(x, y))
	{
		mPressed = true;
		mEventHandler(e);
	}
}

void cButton::MouseUp(SDL_Event &)
{
	mPressed = false;
}

