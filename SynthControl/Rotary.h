#ifndef rotary_h
#define rotary_h

#include "Widget.h"

class cRotary : public cWidget
{
private:
	SDL_Texture *mTexture;
	bool mSelected;
	int mRotation;

	int mMouseX;
	int mMouseY;

	void CreateTexture(SDL_Renderer *renderer, uint32_t diameter);
public:
	cRotary(SDL_Renderer *renderer, uint32_t x, uint32_t y, uint32_t diameter);
	~cRotary();

	virtual void MouseDown(SDL_Event &e);
	virtual void MouseUp(SDL_Event &e);
	virtual void MouseMove(SDL_Event &e);

	virtual void Render(SDL_Renderer *renderer);
};

#endif
