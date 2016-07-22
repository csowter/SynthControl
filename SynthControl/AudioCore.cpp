#include "AudioCore.h"
#include <SDL.h>
#include <cstdio>

cAudioCore::cAudioCore()
	: mSine(1000.0f, 48000)
{
	OpenAudioDevice();
}

cAudioCore::~cAudioCore()
{

}

static void audioCallback(void *userData, Uint8 *audioStream, int len)
{
	Sinusoid *generator = (Sinusoid *)userData;
	float *floatStream = (float *)audioStream;
	for (int i = 0; i < len / sizeof(float); i++)
	{
		*floatStream = generator->NextSample() / 2;
		floatStream++;
	}
}

void cAudioCore::OpenAudioDevice()
{
	SDL_AudioSpec audioSpecDesired;
	SDL_AudioSpec audioSpecActual;

	audioSpecDesired.freq = 48000;
	audioSpecDesired.format = AUDIO_F32;
	audioSpecDesired.channels = 2;
	audioSpecDesired.callback = audioCallback;
	audioSpecDesired.userdata = &mSine;
	audioSpecDesired.samples = 1024;

	SDL_AudioDeviceID device = SDL_OpenAudioDevice(NULL, 0, &audioSpecDesired, &audioSpecActual, SDL_AUDIO_ALLOW_ANY_CHANGE);
	int NumberOFDevices = SDL_GetNumAudioDevices(0);
	for (int i = 0; i < NumberOFDevices; i++)
		printf("Audio device %d: %s\r\n", i, SDL_GetAudioDeviceName(i, 0));
	if (device == 0)
	{
		printf("Failed to open audio: %s\n", SDL_GetError());
	}
	else
	{
		printf("opened Audio device %d: %s", device, SDL_GetAudioDeviceName(device, 0));
	}
	SDL_PauseAudioDevice(device, 0);
}

