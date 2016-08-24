#ifndef fader_h
#define fader_h

#include "Widget.h"
#include "ValueChangeHandler.h"
#include <vector>

class cFader : public cWidget
{
private:
	SDL_Texture *mFaderTrackTexture;
	SDL_Texture *mFaderKnobTexture;
	float mValue;
	float mMinValue;
	float mMaxValue;
	float mStep;
	bool mSelected;
	int mMouseX;
	int mMouseY;

	std::vector<iValueChangeHandler*> mValueChangeHandlers;

public:
	cFader(SDL_Renderer *renderer, uint32_t x, uint32_t y, uint32_t width, uint32_t height);
	~cFader();
	virtual void MouseDown(SDL_Event &e);
	virtual void MouseUp(SDL_Event &e);
	virtual void MouseMove(SDL_Event &e);
	void AddValueChangeHandler(iValueChangeHandler *handler);

	virtual void Render(SDL_Renderer *renderer);
};

#endif