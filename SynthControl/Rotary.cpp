#include "Rotary.h"
#include <cstdio>

cRotary::cRotary(SDL_Renderer *renderer, uint32_t x, uint32_t y, uint32_t diameter)
	: cWidget(x,y, diameter, diameter)
{
	mTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, diameter, diameter);
	SDL_SetRenderTarget(renderer, mTexture);

	SDL_SetRenderDrawColor(renderer, 255, 255, 40, 255);

	SDL_Rect rect = { 0,0,mBoundingRectangle.w, mBoundingRectangle.h };
	
	SDL_RenderDrawLine(renderer, 50, 6, 50, 20);
	{
		int x0 = 50, y0 = 50;
		int x = 45;
		int y = 0;
		int err = 0;

		while (x >= y)
		{

			SDL_RenderDrawPoint(renderer, x0 + x, y0 + y);
			SDL_RenderDrawPoint(renderer, x0 + y, y0 + x);
			SDL_RenderDrawPoint(renderer, x0 - y, y0 + x);
			SDL_RenderDrawPoint(renderer, x0 - x, y0 + y);
			SDL_RenderDrawPoint(renderer, x0 - x, y0 - y);
			SDL_RenderDrawPoint(renderer, x0 - y, y0 - x);
			SDL_RenderDrawPoint(renderer, x0 + y, y0 - x);
			SDL_RenderDrawPoint(renderer, x0 + x, y0 - y);

			y += 1;
			err += 1 + 2 * y;
			if (2 * (err - x) + 1 > 0)
			{
				x -= 1;
				err += 1 - 2 * x;
			}
		}
	}

	SDL_SetRenderTarget(renderer, NULL);	
}

cRotary::~cRotary()
{
	SDL_DestroyTexture(mTexture);
}

void cRotary::MouseDown(SDL_Event &e)
{
	int x, y;
	SDL_GetMouseState(&x, &y);

	if (ContainsPoint(x, y))
	{
		mSelected = true;
		mMouseX = x;
		mMouseY = y;
	}
}

void cRotary::MouseUp(SDL_Event &e)
{
	mSelected = false;
}

void cRotary::MouseMove(SDL_Event &e)
{
	if (!mSelected)
		return;
	
	int x, y;
	SDL_GetMouseState(&x, &y);

	int delta = (x - mMouseX) + (mMouseY - y); 
	mMouseX = x;
	mMouseY = y;
	mRotation += delta;

	if (mRotation > 359) mRotation = 0;
	if (mRotation < -359) mRotation = 0;
}

void cRotary::Render(SDL_Renderer *renderer)
{
	if (!mVisible)
		return;
	
	SDL_Point centre = {50, 50};
	double d = (double)mRotation;

	SDL_Rect rect = { 0,0,mBoundingRectangle.w, mBoundingRectangle.h };
	
	SDL_RenderCopyEx(renderer, mTexture, &rect, &mBoundingRectangle, d, &centre, SDL_FLIP_NONE);
}