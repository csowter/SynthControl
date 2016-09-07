#include "Fader.h"
#include <algorithm>

cFader::cFader(SDL_Renderer *renderer, uint32_t x, uint32_t y, uint32_t width, uint32_t height)
	: cWidget(x, y, width, height), mValue(0.25f), mMinValue(0.0f), mMaxValue(1.0f), mStep(0.01f)
{
	mFaderTrackTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, width, height);
	mFaderKnobTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_TARGET, width, 2);

	SDL_SetRenderTarget(renderer, mFaderTrackTexture);
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

	SDL_RenderDrawLine(renderer, (width / 2) - 1, 0, (width / 2) - 1, height);
	SDL_RenderDrawLine(renderer, (width / 2), 0, (width / 2), height);
	SDL_RenderDrawLine(renderer, (width / 2) + 1, 0, (width / 2) + 1, height);

	SDL_SetRenderTarget(renderer, mFaderKnobTexture);
	SDL_RenderDrawLine(renderer, 2, 0, width - 4, 0);
	SDL_RenderDrawLine(renderer, 2, 1, width - 4, 1);

	SDL_SetRenderTarget(renderer, NULL);
}

cFader::~cFader()
{
	SDL_DestroyTexture(mFaderTrackTexture);
	SDL_DestroyTexture(mFaderKnobTexture);
}

void cFader::MouseDown(SDL_Event &e)
{
	int x, y;
	SDL_GetMouseState(&x, &y);

	if(ContainsPoint(x, y))
	{
		mSelected = true;
		mMouseX = x;
		mMouseY = y;
	}
}

void cFader::MouseUp(SDL_Event &e)
{
	mSelected = false;
}

void cFader::MouseMove(SDL_Event &e)
{
	if(!mSelected)
		return;

	int x, y;
	SDL_GetMouseState(&x, &y);

	int delta = (x - mMouseX) + (mMouseY - y);
	mMouseX = x;
	mMouseY = y;

	mValue += delta * mStep;

	if(mValue > mMaxValue) mValue = mMaxValue;
	if(mValue < mMinValue) mValue = mMinValue;

	std::for_each(mValueChangeHandlers.begin(), mValueChangeHandlers.end(), [&](iValueChangeHandler *handler) {handler->ValueChange(mValue); });
}

void cFader::Render(SDL_Renderer *renderer)
{
	if(!mVisible)
		return;
	SDL_RenderCopy(renderer, mFaderTrackTexture, NULL, &mBoundingRectangle);

	SDL_Rect knobRect = { mBoundingRectangle.x, mBoundingRectangle.y + (mBoundingRectangle.h - (int)(mValue / mStep)), mBoundingRectangle.w, 2 };
	SDL_RenderCopy(renderer, mFaderKnobTexture, NULL, &knobRect);
}

void cFader::AddValueChangeHandler(iValueChangeHandler *handler)
{
	mValueChangeHandlers.push_back(handler);
	handler->ValueChange(mValue);
}