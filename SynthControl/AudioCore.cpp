#include "AudioCore.h"
#include <SDL.h>
#include <cstdio>


float pitch[] =
{
	261.63f,
	277.18f,
	293.66f,
	311.13f,
	329.63f,
	349.23f,
	369.99f,
	392.00f,
	415.30f,
	440.0f,
	466.16f,
	493.88f
};

cAudioCore::cAudioCore()
{
	for(uint32_t i = 0; i < 12; i++)
	{
		mOscillators[i].SetType(cOscillator::eType::Sine);
		mOscillators[i].SetSampleRate(48000);
		mOscillators[i].SetFrequency(pitch[i]);
		mOscillators[i].SetMute(true);
	}
	OpenAudioDevice();
}

cAudioCore::~cAudioCore()
{

}

void cAudioCore::MuteOscillators(bool mute, int oscillator)
{
	mOscillators[oscillator].SetMute(mute);
}

static void audioCallback(void *userData, Uint8 *audioStream, int len)
{
	cOscillator *generator = (cOscillator *)userData;
	float *floatStream = (float *)audioStream;
	for (int i = 0; i < len / sizeof(float); i++)
	{
		float sample = 0.0f;
		for(uint32_t i = 0; i < 12; i++)
			sample += generator[i].NextSample();
		*floatStream = sample / 20;
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
	audioSpecDesired.userdata = mOscillators;
	audioSpecDesired.samples = 512;

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

