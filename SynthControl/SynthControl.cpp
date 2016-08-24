#include "SynthControl.h"
#include <cstdio>
#include <algorithm>
#include <random>
#include "ToggleButton.h"
#include "Rotary.h"
#include "MouseEventHandler.h"
#include "Fader.h"
#include "ValueChangeHandler.h"

cSynthControl::cSynthControl()
{
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);
	mWindow = SDL_CreateWindow("Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, cSynthControl::WindowInitialWidth, cSynthControl::WindowInitialHeight, SDL_WINDOW_SHOWN);
	
	if(mWindow == NULL)
	{
		printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		return;
	}

	mSurface = SDL_GetWindowSurface(mWindow);
	mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED);

	CreateWidgets();

	Run();
}

class ButtonHandler : public iMouseEventHandler
{
private:
	cAudioCore &mAudioCore;
	bool mMute;
	int mOscillator;
public:
	ButtonHandler(cAudioCore &audio, int oscillator)
		: mAudioCore(audio), mMute(false), mOscillator(oscillator)
	{}

	void MouseDown(SDL_Event &e)
	{
		mAudioCore.MuteOscillators(mMute, mOscillator);
		mMute = !mMute;
	}
};

class cSwitchOscillatorHandler : public iMouseEventHandler
{
private:
	cAudioCore &mAudioCore;
	int mOscillator;
public:
	cSwitchOscillatorHandler(cAudioCore &audio, int oscillator)
		: mAudioCore(audio), mOscillator(oscillator)
	{}

	void MouseDown(SDL_Event &e)
	{
		mAudioCore.SwitchOscillator(mOscillator);
	}
};

class cFaderHandler : public iValueChangeHandler
{
private:
	cAudioCore &mAudioCore;
	int mOscillator;
public:
	cFaderHandler(cAudioCore &audio, int oscillator)
		: mAudioCore(audio), mOscillator(oscillator)
	{}

	void ValueChange(float newValue)
	{
		mAudioCore.SetGain(mOscillator, newValue);
	}
};

void cSynthControl::CreateWidgets()
{
	for(int i = 0; i < 12; i++)
	{
		cButton *muteButton = new cToggleButton(mRenderer, i * 50, 600, 40, 40);
		ButtonHandler *handler = new ButtonHandler(mAudioCore, i);
		muteButton->AddEventHandler(handler);
		mWidgets.push_back(muteButton);

		cButton *oscillatorTypeButton = new cToggleButton(mRenderer, i * 50, 500, 40, 40);
		cSwitchOscillatorHandler *switchHandler = new cSwitchOscillatorHandler(mAudioCore, i);
		oscillatorTypeButton->AddEventHandler(switchHandler);
		mWidgets.push_back(oscillatorTypeButton);

		mWidgets.push_back(new cRotary(mRenderer, i * 50, 550, 40));
		
		cFader *fader = new cFader(mRenderer, i * 50, 380, 40, 100);
		fader->AddValueChangeHandler(new cFaderHandler(mAudioCore, i));
		mWidgets.push_back(fader);
	}
}

void cSynthControl::Run()
{
	mRunning = true;
	while(mRunning)
	{
		HandleEvents();

		RenderWidgets();

		SDL_RenderPresent(mRenderer);

		SDL_Delay(10);
	}
}

void cSynthControl::RenderWidgets()
{
	SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255);
	SDL_RenderClear(mRenderer);
	std::for_each(mWidgets.begin(), mWidgets.end(), [this](cWidget *widget){ widget->Render(mRenderer); });
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

void cSynthControl::MouseMove(SDL_Event &e)
{
	std::for_each(mWidgets.begin(), mWidgets.end(), [&](cWidget *widget) { widget->MouseMove(e); });
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
		case SDL_MOUSEMOTION:
			MouseMove(e);
			break;
		}
	}
}

cSynthControl::~cSynthControl()
{
	SDL_DestroyRenderer(mRenderer);
	SDL_DestroyWindow(mWindow);
}
