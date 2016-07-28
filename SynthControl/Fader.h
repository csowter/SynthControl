#ifndef fader_h
#define fader_h

#include "Widget.h"

class cFader : public cWidget
{
private:
	SDL_Texture *mFaderTrackTexture;
	SDL_Texture *mFaderKnobTexture;
	int32_t mValue;
	bool mSelected;
	int mMouseX;
	int mMouseY;

public:
	cFader(SDL_Renderer *renderer, uint32_t x, uint32_t y, uint32_t width, uint32_t height);
	~cFader();
	virtual void MouseDown(SDL_Event &e);
	virtual void MouseUp(SDL_Event &e);
	virtual void MouseMove(SDL_Event &e);

	virtual void Render(SDL_Renderer *renderer);
};

#endif