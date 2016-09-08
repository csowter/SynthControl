#include "Meter.h"

cMeter::cMeter(SDL_Renderer *renderer, cAudioCore &audioCore, uint32_t meterIndex, uint32_t x, uint32_t y, uint32_t width, uint32_t height)
: cWidget(x, y, width, height), mAudioCore(audioCore), mMeterIndex(meterIndex)
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

	SDL_Rect rect;
	rect.w = GetBounds().w;
	rect.x = 0;

	//red
	SDL_SetRenderTarget(renderer, mMeterOffTexture);
	SDL_SetRenderDrawColor(renderer, 55, 0, 0, 255);
	SDL_RenderClear(renderer);

	//green
	SDL_SetRenderDrawColor(renderer, 0, 55, 0, 255);
	rect.y = GetBounds().h - 0.7f * GetBounds().h;
	rect.h = 0.7f * GetBounds().h;
	SDL_RenderFillRect(renderer, &rect);

	//amber
	SDL_SetRenderDrawColor(renderer, 55, 55, 0, 255);
	rect.y = GetBounds().h - 0.9f * GetBounds().h;
	rect.h = 0.2f * GetBounds().h;
	SDL_RenderFillRect(renderer, &rect);

	//red
	SDL_SetRenderTarget(renderer, mMeterOnTexture);
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderClear(renderer);

	SDL_SetRenderDrawColor(renderer, 0, 185, 0, 255);
	rect.y = GetBounds().h - 0.7f * GetBounds().h;
	rect.h = 0.7f * GetBounds().h;
	SDL_RenderFillRect(renderer, &rect);

	//amber
	SDL_SetRenderDrawColor(renderer, 155, 155, 0, 255);
	rect.y = GetBounds().h - 0.9f * GetBounds().h;
	rect.h = 0.2f * GetBounds().h;
	SDL_RenderFillRect(renderer, &rect);

	SDL_SetRenderTarget(renderer, NULL);
}

void cMeter::Render(SDL_Renderer *renderer) 
{
	if (!mVisible)
		return;

	float newMeterValue = mAudioCore.GetMeterValue(mMeterIndex);

	mMeterValue = newMeterValue;

	SDL_RenderCopy(renderer, mMeterOffTexture, NULL, &mBoundingRectangle);

	SDL_Rect srcOnRectangle = { 0, mBoundingRectangle.h - (mMeterValue * mBoundingRectangle.h), mBoundingRectangle.w, mMeterValue * mBoundingRectangle.h };
	SDL_Rect dstOnRectangle = { mBoundingRectangle.x, mBoundingRectangle.y + mBoundingRectangle.h - (mMeterValue * mBoundingRectangle.h) + 1, mBoundingRectangle.w, mMeterValue * mBoundingRectangle.h };
	SDL_RenderCopy(renderer, mMeterOnTexture, &srcOnRectangle, &dstOnRectangle);
}