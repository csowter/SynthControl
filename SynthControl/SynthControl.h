#ifndef synthcontrol_h
#define synthcontrol_h

#include <SDL.h>
#include <cstdint>



class cSynthControl
{
private:
	static const uint32_t WindowInitialWidth = 640;
	static const uint32_t WindowInitialHeight = 640;

	SDL_Window *mWindow;
	SDL_Surface *mSurface;
	bool mRunning;

public:
	cSynthControl();
	~cSynthControl();
	void Run();
private:
	void HandleEvents();
	void KeyDown(SDL_Event &e);
	void KeyUp(SDL_Event &e);
	void MouseButtonDown(SDL_Event &e);
	void MouseButtonUp(SDL_Event &e);
};

#endif