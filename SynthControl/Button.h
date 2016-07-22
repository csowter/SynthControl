#ifndef button_h
#define button_h

#include "Widget.h"

class cButton : public cWidget
{
private:
	SDL_Texture *mPressedTexture;
	SDL_Texture *mUnpressedTexture;
	bool mPressed;
	void(*mEventHandler)(SDL_Event &e);
public:
	cButton(SDL_Renderer *renderer, uint32_t x, uint32_t y, uint32_t width, uint32_t height, void(*eventHandler)(SDL_Event &e) = [](SDL_Event &) {});
	~cButton();
	virtual void Render(SDL_Renderer *renderer);
	virtual void MouseDown(SDL_Event &e);
	virtual void MouseUp(SDL_Event &e);
};


#endif