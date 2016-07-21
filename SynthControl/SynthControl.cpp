#include "SynthControl.h"
#include <cstdio>
#include <algorithm>
#include "Button.h"

cSynthControl::cSynthControl()
	: button1(0, 0, 25, 25), button2(0, 50, 25, 25)
{
	mWindow = SDL_CreateWindow("Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, cSynthControl::WindowInitialWidth, cSynthControl::WindowInitialHeight, SDL_WINDOW_SHOWN);
	
	if(mWindow == NULL)
	{
		printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		return;
	}

	mSurface = SDL_GetWindowSurface(mWindow);
	mRenderer = SDL_GetRenderer(mWindow);

	mWidgets.push_back(&button1);
	mWidgets.push_back(&button2);

	Run();
}

void cSynthControl::Run()
{
	mRunning = true;
	while(mRunning)
	{
		HandleEvents();

		RenderWidgets();
		
		SDL_UpdateWindowSurface(mWindow);
	}
}

void cSynthControl::RenderWidgets()
{
	SDL_Rect rect = { 0, 0, cSynthControl::WindowInitialWidth, cSynthControl::WindowInitialHeight };
	SDL_FillRect(mSurface, &rect, 0x00000000);
	std::for_each(mWidgets.begin(), mWidgets.end(), [this](cWidget *widget){ widget->Render(mSurface); });
}

void cSynthControl::KeyDown(SDL_Event &)
{
#ifdef KEY_DEBUG
	printf("Key down %s\r\n", SDL_GetKeyName(e.key.keysym.sym));
#endif
}

void cSynthControl::KeyUp(SDL_Event &e)
{
#ifdef KEY_DEBUG
	printf("Key up %s\r\n", SDL_GetKeyName(e.key.keysym.sym));
#endif
	if(e.key.keysym.sym == SDLK_h)
		std::for_each(mWidgets.begin(), mWidgets.end(), [this](cWidget *widget){ widget->SetVisible(false); });
	else if(e.key.keysym.sym == SDLK_s)
		std::for_each(mWidgets.begin(), mWidgets.end(), [this](cWidget *widget){ widget->SetVisible(true); });
}

void cSynthControl::MouseButtonDown(SDL_Event &e)
{
	std::for_each(mWidgets.begin(), mWidgets.end(), [&](cWidget *widget){ widget->MouseDown(e); });
#ifdef MOUSE_DEBUG
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
#endif
}

void cSynthControl::MouseButtonUp(SDL_Event &e)
{
	std::for_each(mWidgets.begin(), mWidgets.end(), [&](cWidget *widget){ widget->MouseUp(e); });
#ifdef MOUSE_DEBUG
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
#endif
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
	SDL_DestroyRenderer(mRenderer);
	SDL_DestroyWindow(mWindow);
}
