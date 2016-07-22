#ifndef synthcontrol_h
#define synthcontrol_h

#include <SDL.h>
#include <cstdint>
#include <vector>

#include "Sinusoid.h"
class cWidget;

class cSynthControl
{
private:
	static const uint32_t WindowInitialWidth = 640;
	static const uint32_t WindowInitialHeight = 640;

	SDL_Window *mWindow;
	SDL_Surface *mSurface;
	SDL_Renderer *mRenderer;
	bool mRunning;

	std::vector<cWidget *> mWidgets;

	Sinusoid mSine;

public:
	cSynthControl();
	~cSynthControl();
	void Run();
private:
	void CreateWidgets();
	void RenderWidgets();
	void HandleEvents();
	void KeyDown(SDL_Event &e);
	void KeyUp(SDL_Event &e);
	void MouseButtonDown(SDL_Event &e);
	void MouseButtonUp(SDL_Event &e);

	void Button1(SDL_Event &e);

	void CreateAudioDevice();
};

#endif