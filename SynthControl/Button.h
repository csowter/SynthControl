#ifndef button_h
#define button_h

#include "Widget.h"

class cButton : public cWidget
{
private:
	uint32_t mColour;
	SDL_Surface *mSurface;
public:
	cButton(uint32_t x, uint32_t y, uint32_t width, uint32_t height);
	~cButton();
	virtual void Render(SDL_Surface *surface);
	virtual void MouseDown(SDL_Event &e);
	virtual void MouseUp(SDL_Event &e);
};


#endif