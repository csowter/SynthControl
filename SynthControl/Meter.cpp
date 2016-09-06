#include "Meter.h"

cMeter::cMeter(SDL_Renderer *renderer, cAudioCore &audioCore, uint32_t x, uint32_t y, uint32_t width, uint32_t height)
: cWidget(x, y, width, height), mAudioCore(audioCore)
{
	CreateTextures(renderer);
}

cMeter::~cMeter()
{
	SDL_DestroyTexture(mMeterOnTexture);
	SDL_DestroyTexture(mMeterOffTexture);
}

void cMeter::CreateTextures(SDL_Renderer *renderer)
{
	mMeterOffTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, GetBounds().w, GetBounds().h);
	mMeterOnTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, GetBounds().w, GetBounds().h);

	SDL_SetRenderTarget(renderer, mMeterOffTexture);
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderClear(renderer);

	SDL_SetRenderTarget(renderer, mMeterOnTexture);
	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
	SDL_RenderClear(renderer);

	SDL_SetRenderTarget(renderer, NULL);
}

void cMeter::Render(SDL_Renderer *renderer) 
{
	if (!mVisible)
		return;

	float newMeterValue = mAudioCore.GetLeftMeterValue();

	if (newMeterValue > mMeterValue)
		mMeterValue = newMeterValue;
	else if (newMeterValue < mMeterValue)
		mMeterValue -= 0.005f;

	SDL_RenderCopy(renderer, mMeterOffTexture, NULL, &mBoundingRectangle);

	SDL_Rect srcOnRectangle = { 0, 0, mBoundingRectangle.w, mMeterValue * mBoundingRectangle.h };
	SDL_Rect dstOnRectangle = { mBoundingRectangle.x, mBoundingRectangle.y + mBoundingRectangle.h - (mMeterValue * mBoundingRectangle.h), mBoundingRectangle.w, mMeterValue * mBoundingRectangle.h };
	SDL_RenderCopy(renderer, mMeterOnTexture, &srcOnRectangle, &dstOnRectangle);
}