#ifndef synthcontrol_h
#define synthcontrol_h

#include <SDL.h>
#include <cstdint>
#include <vector>

#include "Button.h"

class cSynthControl
{
private:
	static const uint32_t WindowInitialWidth = 640;
	static const uint32_t WindowInitialHeight = 640;

	SDL_Window *mWindow;
	SDL_Surface *mSurface;
	SDL_Renderer *mRenderer;
	bool mRunning;


	cButton button1;
	cButton button2;

	std::vector<cWidget *> mWidgets;

public:
	cSynthControl();
	~cSynthControl();
	void Run();
private:
	void RenderWidgets();
	void HandleEvents();
	void KeyDown(SDL_Event &e);
	void KeyUp(SDL_Event &e);
	void MouseButtonDown(SDL_Event &e);
	void MouseButtonUp(SDL_Event &e);
};

#endif