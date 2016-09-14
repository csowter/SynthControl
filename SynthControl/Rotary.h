#ifndef rotary_h
#define rotary_h

#include "Widget.h"
#include <vector>
#include "ValueChangeHandler.h"

class cRotary : public cWidget
{
private:
	SDL_Texture *mTexture;
	bool mSelected;
	int mRotation;

	int mMouseX;
	int mMouseY;

	float mValue;
	float mMin;
	float mMax;
	int mStartRotation;
	int mStopRotation;

	std::vector<iValueChangeHandler*> mValueChangeHandlers;

	void CreateTexture(SDL_Renderer *renderer, uint32_t diameter);
public:
	cRotary(SDL_Renderer *renderer, uint32_t x, uint32_t y, uint32_t diameter);
	~cRotary();

	virtual void MouseDown(SDL_Event &e);
	virtual void MouseUp(SDL_Event &e);
	virtual void MouseMove(SDL_Event &e);

	virtual void Render(SDL_Renderer *renderer);

	void AddValueChangeHandler(iValueChangeHandler *handler);
};

#endif
