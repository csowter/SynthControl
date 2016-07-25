#ifndef togglebutton_h
#define togglebutton_h

#include "Button.h"

class cToggleButton : public cButton
{
private:

public:
	cToggleButton(SDL_Renderer *renderer, uint32_t x, uint32_t y, uint32_t width, uint32_t height);
	~cToggleButton();
	virtual void MouseDown(SDL_Event &e);
	virtual void MouseUp(SDL_Event &e);
};

#endif