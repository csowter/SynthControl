#include "SynthControl.h"
#include <cstdio>
#include <algorithm>
#include <random>
#include "Button.h"

cSynthControl::cSynthControl()
{
	mWindow = SDL_CreateWindow("Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, cSynthControl::WindowInitialWidth, cSynthControl::WindowInitialHeight, SDL_WINDOW_SHOWN);
	
	if(mWindow == NULL)
	{
		printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		return;
	}

	mSurface = SDL_GetWindowSurface(mWindow);
	mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED);

	CreateWidgets();

	CreateAudioDevice();

	Run();
}

void cSynthControl::CreateWidgets()
{
	mWidgets.push_back(new cButton(mRenderer, 0, 600, 40, 40, [](SDL_Event &e){ printf("Button 1\r\n"); }));
	mWidgets.push_back(new cButton(mRenderer, 50, 600, 40, 40, [](SDL_Event &e){ printf("Button 2\r\n"); }));
	mWidgets.push_back(new cButton(mRenderer, 100, 600, 40, 40, [](SDL_Event &e){ printf("Button 3\r\n"); }));
	mWidgets.push_back(new cButton(mRenderer, 150, 600, 40, 40, [](SDL_Event &e){ printf("Button 4\r\n"); }));
	mWidgets.push_back(new cButton(mRenderer, 200, 600, 40, 40, [](SDL_Event &e){ printf("Button 5\r\n"); }));
	mWidgets.push_back(new cButton(mRenderer, 250, 600, 40, 40, [](SDL_Event &e){ printf("Button 6\r\n"); }));
	mWidgets.push_back(new cButton(mRenderer, 300, 600, 40, 40, [](SDL_Event &e){ printf("Button 7\r\n"); }));
	mWidgets.push_back(new cButton(mRenderer, 350, 600, 40, 40, [](SDL_Event &e){ printf("Button 8\r\n"); }));
	mWidgets.push_back(new cButton(mRenderer, 400, 600, 40, 40, [](SDL_Event &e){ printf("Button 9\r\n"); }));
	mWidgets.push_back(new cButton(mRenderer, 450, 600, 40, 40, [](SDL_Event &e){ printf("Button 10\r\n"); }));
	mWidgets.push_back(new cButton(mRenderer, 500, 600, 40, 40, [](SDL_Event &e){ printf("Button 11\r\n"); }));
	mWidgets.push_back(new cButton(mRenderer, 550, 600, 40, 40, [](SDL_Event &e){ printf("Button 12\r\n"); }));
	mWidgets.push_back(new cButton(mRenderer, 600, 600, 40, 40, [](SDL_Event &e){ printf("Button 13\r\n"); }));
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
	SDL_Rect rect = { 0, 0, cSynthControl::WindowInitialWidth, cSynthControl::WindowInitialHeight };
	SDL_FillRect(mSurface, &rect, 0x00000000);
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

static void audioCallback(void *userData, Uint8 *audioStream, int len)
{
	static int16_t mBuffer[256] = {};
	static std::random_device mRandom;
	printf("%d\r\n", len);

	for(uint32_t i = 0; i < len; i++)
	{
		mBuffer[i] = mRandom();
		mBuffer[i] -= (0xffff / 2);

		((uint16_t *)audioStream)[i] = mBuffer[i];
	}

	SDL_MixAudio(audioStream, (Uint8 *)mBuffer, len, SDL_MIX_MAXVOLUME);

}

void cSynthControl::CreateAudioDevice()
{
	SDL_AudioSpec audioSpecDesired;
	SDL_AudioSpec audioSpecActual;

	audioSpecDesired.freq = 48000;
	audioSpecDesired.format = AUDIO_S16;
	audioSpecDesired.channels = 2;
	audioSpecDesired.callback = audioCallback;
	audioSpecDesired.userdata = 0;
	audioSpecDesired.samples = 256;

	SDL_AudioDeviceID device = SDL_OpenAudioDevice(SDL_GetAudioDeviceName(0, 0), 0, &audioSpecDesired, &audioSpecActual, SDL_AUDIO_ALLOW_ANY_CHANGE);
	int NumberOFDevices = SDL_GetNumAudioDevices(0);
	for(int i = 0; i < NumberOFDevices; i++)
	printf("Audio device %d: %s\r\n", i, SDL_GetAudioDeviceName(i, 0));
	if(device == 0)
	{
		printf("Failed to open audio: %s\n", SDL_GetError());
	}
	else
	{
		printf("opened Audio device %d: %s", device, SDL_GetAudioDeviceName(device, 0));
	}
	SDL_PauseAudio(0);
}