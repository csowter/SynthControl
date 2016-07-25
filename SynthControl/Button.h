#ifndef button_h
#define button_h

#include "Widget.h"
#include "MouseEventHandler.h"
#include <vector>
#include <algorithm>

class cButton : public cWidget
{
protected:
	SDL_Texture *mPressedTexture;
	SDL_Texture *mUnpressedTexture;
	bool mPressed;
	std::vector<iMouseEventHandler *> mEventHandlers;
public:
	cButton(SDL_Renderer *renderer, uint32_t x, uint32_t y, uint32_t width, uint32_t height);
	~cButton();
	virtual void Render(SDL_Renderer *renderer);
	virtual void MouseDown(SDL_Event &e);
	virtual void MouseUp(SDL_Event &e);
	void AddEventHandler(iMouseEventHandler *handler) { mEventHandlers.push_back(handler); }
	void RemoveEventHandler(iMouseEventHandler *handler){ mEventHandlers.erase(std::remove(mEventHandlers.begin(), mEventHandlers.end(), handler), mEventHandlers.end()); };
};

#endif