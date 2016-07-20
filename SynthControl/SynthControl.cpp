#include "SynthControl.h"
#include <cstdio>
#include "Widget.h"

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
		cWidget w1(0,0,10,10);
		cWidget w2(10, 10, 10, 10);

		w1.Render(mSurface); 
		w2.Render(mSurface);

		SDL_UpdateWindowSurface(mWindow);
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

void cSynthControl::MouseButtonDown(SDL_Event &e)
{
	switch(e.button.button)
	{
	case SDL_BUTTON_LEFT:
		printf("Left Mouse Down\r\n");
		break;
	case SDL_BUTTON_MIDDLE:
		printf("Middle Mouse Down\r\n");
		break;
	case SDL_BUTTON_RIGHT:
		printf("Right Mouse Down\r\n");
		break;
	}
}

void cSynthControl::MouseButtonUp(SDL_Event &e)
{
	switch(e.button.button)
	{
	case SDL_BUTTON_LEFT:
		printf("Left Mouse Up\r\n");
		break;
	case SDL_BUTTON_MIDDLE:
		printf("Middle Mouse Up\r\n");
		break;
	case SDL_BUTTON_RIGHT:
		printf("Right Mouse Up\r\n");
		break;
	}
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
		case SDL_MOUSEBUTTONDOWN:
			MouseButtonDown(e);
			break;
		case SDL_MOUSEBUTTONUP:
			MouseButtonUp(e);
			break;
		}
	}
}

cSynthControl::~cSynthControl()
{
	SDL_DestroyWindow(mWindow);
}
