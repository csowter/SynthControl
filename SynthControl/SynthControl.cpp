#include "SynthControl.h"
#include <cstdio>

cSynthControl::cSynthControl()
{
	mWindow = SDL_CreateWindow("Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, cSynthControl::WindowInitialWidth, cSynthControl::WindowInitialHeight, SDL_WINDOW_SHOWN);
	if(mWindow == NULL)
	{
		printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		return;
	}

	mSurface = SDL_GetWindowSurface(mWindow);
	Run();
}

void cSynthControl::Run()
{
	mRunning = true;
	while(mRunning)
	{
		HandleEvents();
	}
}

void cSynthControl::KeyDown(SDL_Event &e)
{
	printf("Key down %s\r\n", SDL_GetKeyName(e.key.keysym.sym));
}

void cSynthControl::KeyUp(SDL_Event &e)
{
	printf("Key up %s\r\n", SDL_GetKeyName(e.key.keysym.sym));
}

void cSynthControl::HandleEvents()
{
	SDL_Event e;
	while(SDL_PollEvent(&e) != 0)
	{
		switch(e.type)
		{
		case SDL_QUIT:
			mRunning = false;
			break;
		case SDL_KEYDOWN:
			KeyDown(e);
			break;
		case SDL_KEYUP:
			KeyUp(e);
			break;
		}
	}
}

cSynthControl::~cSynthControl()
{
	SDL_DestroyWindow(mWindow);
}
