#ifndef meter_h
#define meter_h

#include "Widget.h"
#include "AudioCore.h"

class cMeter : public cWidget
{
private:
	SDL_Texture *mMeterOffTexture;
	SDL_Texture *mMeterOnTexture;

	cAudioCore &mAudioCore;

	void CreateTextures(SDL_Renderer *renderer);

	float mMeterValue;

public:
	cMeter() = delete;
	cMeter(SDL_Renderer *renderer, cAudioCore &audioCore, uint32_t x, uint32_t y, uint32_t width, uint32_t height);
	~cMeter();
	virtual void MouseDown(SDL_Event &e){}
	virtual void MouseUp(SDL_Event &e) {}
	virtual void Render(SDL_Renderer *renderer);
};

#endif
