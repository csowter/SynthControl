#ifndef button_h
#define button_h

#include "Widget.h"

class cButton : public cWidget
{
private:
	uint32_t mColour;
public:
	cButton(uint32_t x, uint32_t y, uint32_t width, uint32_t height);
	virtual void Render(SDL_Surface *surface);
	virtual void MouseEvent(SDL_Event &e);
};


#endif