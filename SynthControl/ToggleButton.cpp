#include "ToggleButton.h"

cToggleButton::cToggleButton(SDL_Renderer *renderer, uint32_t x, uint32_t y, uint32_t width, uint32_t height)
	: cButton(renderer, x, y, width, height)
{

}
cToggleButton::~cToggleButton()
{

}

void cToggleButton::MouseDown(SDL_Event &e)
{
	int x, y;
	SDL_GetMouseState(&x, &y);

	if(ContainsPoint(x, y))
	{
		mPressed = !mPressed;
		std::for_each(mEventHandlers.begin(), mEventHandlers.end(), [&](iMouseEventHandler *handler){handler->MouseDown(e); });
	}
}
void cToggleButton::MouseUp(SDL_Event &e)
{}